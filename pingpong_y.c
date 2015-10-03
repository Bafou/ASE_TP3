/*
 * pingpong_y.c
 * Authors : Honoré NINTUNZE & Antoine PETIT
 */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "contexte.h"

void f_ping (void *args) {
  while(1) {
    printf("A");
    yield();
    printf("B");
    yield();
    printf("C");
    yield();
  }
}

void f_pong (void *args) {
  while(1) {
    printf("1");
    yield();
    printf("2");
    yield();
  }
}


int main (int argc, char *argv[]) {
  create_ctx(16384, &f_ping, NULL);
  create_ctx(16384, &f_pong, NULL);
  yield();
  exit(EXIT_SUCCESS);
}

