/*
 * pingpong.c
 * Authors : Honoré NINTUNZE & Antoine PETIT
 */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "contexte.h"

struct ctx_s ctx_ping;
struct ctx_s ctx_pong;

func_t f_ping;
func_t f_pong;
func_t f_pang;

int main (int argc, char *argv[]) {
  create_ctx(16384, &f_ping, NULL);
  create_ctx(16384, &f_pong, NULL);
  create_ctx(16384, &f_pang, NULL);
  start_schedule();
  exit(EXIT_SUCCESS);
}

void f_ping (void *args) {
  while(1) {
    printf("Ping\n");
  }
}

void f_pong (void *args) {
  while(1) {
    printf("Pong\n");
  }
}

void f_pang (void *args) {
  while(1) {
    printf("Pang\n");
  }
}

