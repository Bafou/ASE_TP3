/*
 * pingpong.c
 * Authors : Honoré NINTUNZE & Antoine PETIT
 */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "contexte.h"

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


int main (int argc, char *argv[]) {
  create_ctx(16384, &f_ping, NULL);
  create_ctx(16384, &f_pong, NULL);
  create_ctx(16384, &f_pang, NULL);
  start_schedule();
  exit(EXIT_SUCCESS);
}
