/*
 * pingpongpang.c
 * Authors : Honoré NINTUNZE & Antoine PETIT
 */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "contexte.h"

struct ctx_s ctx_ping;
struct ctx_s ctx_pong;
struct ctx_s ctx_pang;

func_t f_ping;
func_t f_pong;
func_t f_pang;

int main(int argc, char *argv[])
{
  create_ctx(16384,&f_ping, NULL);
  create_ctx(16384,&f_pong, NULL);
  create_ctx(16384,&f_pang, NULL);
  yield();

  exit(EXIT_SUCCESS);
}

void f_ping(void * arg)
{
  while(1)
    {
      printf("A");
      yield();
      printf("B");
      yield();
      printf("C");
      yield();
    }
}

void f_pong(void * arg)
{
    while(1)
    {
      printf("1");
      yield();
      printf("2");
      yield();
    }
}

void f_pang(void * arg)
{
  int i;
  for(i = 1; i<=100;++i)
    {
      printf(" Pang%d ",i);
      yield();
    }
}
