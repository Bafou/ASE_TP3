/*
 * contexte.h
 * Authors : Honoré NINTUNZE & Antoine PETIT
 */
#ifndef CONTEXTE_H
#define CONTEXTE_H

#define MAGIC 0xdeadbeef


typedef void (func_t) (void *);

enum ctx_state_e {
  CTX_READY,
  CTX_ACTIVATED,
  CTX_TERMINATED,
  CTX_LOCKED
};

struct ctx_s {
  void * esp;
  void * ebp;
  func_t * f;
  unsigned char * stack;
  enum ctx_state_e state;
  unsigned int ctx_magic;
  void * args;
  struct ctx_s * next;
  struct ctx_s * previous;
};

struct sem_s {
  int count;
  struct ctx_s *ctx_locked;
};

void switch_to_ctx (struct ctx_s *ctx);

struct ctx_s * create_ctx(int stack_size, func_t f, void * args);

void yield();

void sem_up(struct sem_s *);

void sem_down (struct sem_s *);

void sem_init (struct sem_s *, unsigned int);

#endif
