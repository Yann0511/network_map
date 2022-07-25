/* inspired from original implementation 
   https://sites.google.com/site/cconcurrencypackage/hopscotch-hashing
   https://www.cs.tau.ac.il/~multi/2015a/chhm.htm
   auteur: gbe
*/

#ifndef __HOPSCOTCH_H__
#define __HOPSCOTCH_H__

#ifdef __cplusplus
extern "C"
{
#endif

#define ADDRANGE 256
#define HOPRANGE 32

  typedef enum
    {
     HSTCH_FULL = 1,
     HSTCH_FOUND,
     HSTCH_NOTFOUND,
     HSTCH_LOCKFAIL,
     HSTCH_INSFAIL,
     HSTCH_EXIST,
    }hopscotch_error;
  
  typedef struct hopscotch hopscotch;
  
  struct bucket{
    void *key;
    void *val;
    int hopinfo;
    // struct rwlock *lock;
  };
  
  struct hopscotch_type{
    unsigned int (*hash)(void*);
    char* (*printkey)(void*);
    int (*kcompare)(void*, void*);
    void* (*kcopy)(void*);
    void* (*vcopy)(void*);
  };
  
  struct hopscotch{
    unsigned int size;
    unsigned int mask;
    int nbits;
    unsigned int nused;
    struct bucket *items;
    struct hopscotch_type type;
  };

  
  extern void hopscotch_type_init(struct hopscotch_type*);
  extern void hopscotch_stats(hopscotch*);
  extern hopscotch* hopscotch_new(int size, struct hopscotch_type*);
  extern void hopscotch_dump(hopscotch*);
  extern int hopscotch_insert(hopscotch *ht, void *key, void *data);
  extern int hopscotch_lookup(hopscotch *ht, void *key, void **val);
  extern int hopscotch_remove(hopscotch *ht, void *key);
  extern void hopscotch_delete(hopscotch *ht);


  
  extern struct bucket* hopscotch_get_bucket_(hopscotch *ht, void *key);
  extern int hopscotch_insert_(struct bucket *buk, int *nused,
			       void *key, void *val,
			       int(*kcompare)(void*, void*),
			       void*(kcopy)(void*),
			       void*(vcopy)(void*));
  extern int hopscotch_lookup_(struct bucket *buk,
			       void *key, void **val,
			       int (*kcompare)(void*, void*));
  extern void hopscotch_remove_(struct bucket *buk, void *key, int*,
				int(*kcompare)(void*, void*));
  
#ifdef __cplusplus
}
#endif

#endif
