/* inspired from original implementation 
   https://sites.google.com/site/cconcurrencypackage/hopscotch-hashing
   https://www.cs.tau.ac.il/~multi/2015a/chhm.htm
   auteur: gbe
*/
#include"hopscotch.h"

#include <string.h>
#include <stdlib.h>

#define HSTCH_SELECTED (void*)-1

static int defaultkeycmp(void *a, void *b)
{
  return strcmp(a, b);
}

static void* defaultkeycopy(void *a)
{
  return a;
}

static void* defaultvalcopy(void *a)
{
  return a;
}

static unsigned int djb(void *arg)
{
  char *str = arg;
  unsigned int hash = 5381;

  while(*str)
    hash = ((hash << 5) + hash) ^ *str++;

  return hash;
}

void hopscotch_type_init(struct hopscotch_type *t)
{
  t->hash = djb;
  t->printkey = 0;
  t->kcompare = defaultkeycmp;
  t->kcopy = defaultkeycopy;
  t->vcopy = defaultvalcopy;
}

struct hopscotch*
hopscotch_new(int size, struct hopscotch_type *type)
{
  struct hopscotch *h;
  int i;
  unsigned int mask = 1 ;
  if( 1 >= size)
    return 0;
  
  if(!(h = calloc(1, sizeof(struct hopscotch))))
    return 0;

  for(i = 8*sizeof(size)-1, mask <<= i;
      !(size&mask) && i >= 0; i--, mask >>= 1);

  if((1 << i) < size)
    i++;
  
  h->nbits = i; //ceil(log2(size));
  h->size = (1 << h->nbits) + ADDRANGE;
  h->mask = (1 << h->nbits)-1;
  if(!(h->items = calloc(h->size, sizeof(struct bucket))))
    {
      free(h);
      return 0;
    }
  
  for (i = 0; i < h->size; i++)
    //  (h->items+i)->lock = rwlock_init();
	
  if(type)
    h->type = *type;
  else
    hopscotch_type_init(&h->type);

  return h;
}

void hopscotch_delete(hopscotch *h)
{
  int i;
  
  for (i = 0; i < h->size; i++)
    // free((h->items+i)->lock);
  free(h->items);
  free(h);
}

struct bucket* hopscotch_get_bucket_(hopscotch *ht, void *key)
{
  unsigned int hash;
  
  hash = ht->type.hash(key);
  hash &= ht->mask;

  return ht->items+hash;
}

int hopscotch_lookup_(struct bucket *buk, void *key,
		      void **val, int (*kcompare)(void*, void*))
{
  int i;
  unsigned int mask;
  
  for(mask = 1, i = 0; i < HOPRANGE; i++, mask <<= 1)
    {
      if(buk->hopinfo & mask)
	if(!kcompare(key, (buk+i)->key))
	  {
	    *val = (buk+i)->val;
	    return HSTCH_FOUND;
	  }
    }

  *val = 0;
  
  return 0;
}

static int find_closer_bucket(struct bucket **to, int *distance)
{
  int idx, i, move=-1;
  unsigned mask, info;
  struct bucket *from;
  
  mask = 1;
  idx = HOPRANGE-1 > *distance ? *distance : HOPRANGE-1;
  
  for(; idx > 0; idx--)
    {
      from = *to-idx;
      info = from->hopinfo;
      mask = 1;

      if(from->hopinfo)
	for(i = 0; i < idx; i++, mask <<= 1)
	  if(mask&from->hopinfo)
	    {
	      move = i;
	      break;
	    }

      if(move == -1)
	continue;

       /* if(!rwlock_try_wlock(from->lock)) */
       /* 	return HSTCH_LOCKFAIL; */

      /* from->hopinfo can be modified in another thread */
      if(info == from->hopinfo)
	{
	  (*to)->key = (from+move)->key;
	  (*to)->val = (from+move)->val;
	  from->hopinfo |= (1 << idx);
	  
	  (from+move)->key = HSTCH_SELECTED;
	  (from+move)->val = 0;
	  from->hopinfo &= ~(1 << move);

	  *to = from+move;
	  *distance = *distance - idx + move;
	}
      
      /* rwlock_unlock_wlock(from->lock); */

      return 0;
    }

  return HSTCH_FULL;
}

int hopscotch_lookup(hopscotch *ht, void *key, void **val)
{
  struct bucket *buk;
  int rval;

  buk = hopscotch_get_bucket_(ht, key);
  /* if(!rwlock_try_rlock(buk->lock)) */
  /*   return HSTCH_LOCKFAIL; */

  rval = hopscotch_lookup_(buk, key, val, ht->type.kcompare);
  
  /* rwlock_unlock_rlock(buk->lock); */
  
  return rval;
}

int hopscotch_free_bucket_(struct bucket *buk)
{
  int freeind;
  void *expected = 0;

  for(freeind = 0; freeind < ADDRANGE; freeind++)
    {
      if(buk->key == 0)
	if(__atomic_compare_exchange_n(&buk->key, &expected,
				       HSTCH_SELECTED, 0,
				       __ATOMIC_RELEASE,
				       __ATOMIC_ACQUIRE))
	  /* break; */
	  return freeind;

      buk++;
    }

  /* all buckets are used may be we must resize */
  return -1;
}

int hopscotch_insert_(struct bucket *buk, int *nused,
				   void *key, void *val,
				   int(*kcompare)(void*, void*),
				   void*(kcopy)(void*),
				   void*(vcopy)(void*))
{
  struct bucket *tbuk;
  int rval = 0, idx;
  void *data = 0;

  if(!hopscotch_lookup_(buk, key, &data, kcompare))
    if((idx = hopscotch_free_bucket_(buk)) >= 0)
      {
	tbuk = buk+idx;
	do{

	  if(idx < HOPRANGE)
	    {
	      tbuk->key = kcopy(key);
	      tbuk->val = vcopy(val);
	    
	      buk->hopinfo |= (1 << idx);
	      ++*nused;
	      break;
	    }
	  else
	    {
	      if((rval = find_closer_bucket(&tbuk, &idx)))
		tbuk->key = 0;
	    }
	}while(!rval);
      }
    else
      rval = HSTCH_FULL;
  else
    rval = HSTCH_EXIST;

  return rval;
}

/* returns 0 when success non zero value otherwise */
int hopscotch_insert(hopscotch *ht, void *key, void *val)
{
  struct bucket *start;
  int rval, free;
  
  start = hopscotch_get_bucket_(ht, key);
  
  /* if(!rwlock_try_wlock(start->lock)) */
  /*   return HSTCH_LOCKFAIL; */
  
  rval = hopscotch_insert_(start, &ht->nused, key, val,
			   ht->type.kcompare,
			   ht->type.kcopy,
			   ht->type.vcopy);
  /* rwlock_unlock_wlock(start->lock); */
  
  return rval;
}

void hopscotch_remove_(struct bucket *buk, void *key, int *nused,
		       int(*kcompare)(void*, void*))
{
  int i;
  unsigned int info, mask;
  
  mask = 1;
  info = buk->hopinfo;
  for(i = 0; i < HOPRANGE; ++i, mask <<= 1)
    if(buk->hopinfo & mask)
      if(!kcompare(key, (buk+i)->key))
	{
	  --*nused;
	  (buk+i)->key = 0;
	  (buk+i)->val = 0;
	  buk->hopinfo &= ~(1<<i);
	}
}

int hopscotch_remove(hopscotch *ht, void *key)
{
  struct bucket *start;
  
  start = hopscotch_get_bucket_(ht, key);
  
  /* if(!rwlock_try_wlock(start->lock)) */
  /*   return HSTCH_LOCKFAIL; */

  hopscotch_remove_(start, key, &ht->nused, ht->type.kcompare);
  
  //  rwlock_unlock_wlock(start->lock);

  return 0;
}