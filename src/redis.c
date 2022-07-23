#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <hiredis/hiredis.h>
#include<fcntl.h>

int main()
{
  redisContext *conn;
  redisReply *reply;
  const char *hostname = "127.0.0.1";
  const int port = 6379;
  char password[100] = "";
  struct timeval timeout = { 1, 500000 }; // 1.5 seconds
  int env, size, i, j;
  char tmp[100];

  env  = open("../.env" , O_RDONLY) ;
  
  if(env == -1)
    {
      printf("\nImpossible d'ouvrir le fichier .env");
      return 84;
    }

  size = read(env, tmp, 100);

  if(!size)
    return 84;
  //printf("%d", size);

  for(i = 0; i < size; i++)
    {
      
      if(!strncmp(tmp+i, "DB_PASSWORD = ", 14))
	{
	  i += 14;
	  j = i;
	  
	  while(tmp[j] != '"')
	    j++;

	  i = ++j;

	  while(tmp[j] != '"')
	    j++;
	  
	  strncpy(password, tmp+i, j-i);
	}      
    }

  conn = redisConnectWithTimeout(hostname, port, timeout);
  if (conn == NULL || conn->err)
    {
      if (conn)
	{
	  printf("Erreur de connexion: %s\n", conn->errstr);
	  redisFree(conn);
	}
      else
	{
	  printf("Erreur de connexion: impossible d'allouer le contexte redis\n");
	}
      return 0;
    }
  
  /* AUTH */
  reply = redisCommand(conn, "AUTH %s", password);
  freeReplyObject(reply);
     
  return 0;
}
