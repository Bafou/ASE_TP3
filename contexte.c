/*
 * contexte.c
 * Authors : Honoré NINTUNZE & Antoine PETIT
 */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "hw_config.h"
#include "contexte.h"
#include "include/hardware.h"

static struct ctx_s *current_ctx = NULL;

/* stack systeme pour gérer les frees sans problème*/
static struct ctx_s *stack_systeme;

void enqueue(struct ctx_s * queue){
  if (!current_ctx){
    queue->next = queue;
    queue->previous = queue;
    current_ctx = queue;
  }
  else {
    struct ctx_s * prev = current_ctx->previous;
    // lier tmp au précédent
    prev->next = queue;
    queue->previous = prev;
    // lier tmp au suivant
    queue->next = current_ctx;
    current_ctx->previous = queue;
  }
}
static void
empty_it(void)
{
    return;
}

static void
timer_it() {
  _out(TIMER_ALARM,0xFFFFFFFE);
  yield();
}

int start_schedule(){
  int i;
  if (init_hardware(HARDWARE_INI)==0) {
    fprintf(stderr, "Error in hardware initialization\n");
    exit(EXIT_FAILURE);
  }
  for (i=0; i<16; i++)
	IRQVECTOR[i] = empty_it;

  IRQVECTOR[TIMER_IRQ] = timer_it;    
  _out(TIMER_PARAM,128+64+32+8); /* reset + alarm on + 8 tick / alarm */
  _out(TIMER_ALARM,0xFFFFFFFE);  /* alarm at next tick (at 0xFFFFFFFF) */

  /* allows all IT */
  _mask(0);
  yield();
}

int init_ctx (struct ctx_s *ctx, int stack_size, func_t *f, void *args) {
  ctx->stack = (unsigned char*) malloc (stack_size);
  if (ctx->stack == NULL) return 0;
  ctx->ebp = &ctx->stack[stack_size - sizeof(void *)];
  ctx->esp = &ctx->stack[stack_size - sizeof(void *)];
  ctx->state = CTX_READY;
  ctx->f = f;
  ctx->args= args;
  ctx->next = NULL;
  ctx->previous = NULL;
  ctx->ctx_magic = MAGIC;
  return 1;
}

struct ctx_s * create_ctx(int stack_size, func_t *f, void * args){
  _mask(15);
  struct ctx_s * tmp = malloc(sizeof(struct ctx_s));
  assert(tmp);
  assert(init_ctx(tmp, stack_size, f, args));

  enqueue(tmp);
  return tmp;
}

int exec_f(struct ctx_s * ctx) {
  current_ctx->state = CTX_ACTIVATED;
  current_ctx->f(current_ctx->args);
  _mask(15);
  current_ctx->state = CTX_TERMINATED;
  // TODO free
  free(current_ctx->stack);
  free(current_ctx);
  
  if(current_ctx->next != current_ctx){
    struct ctx_s * next_ctx = current_ctx->next;
    struct ctx_s * last_ctx = current_ctx->previous;
    current_ctx = NULL;
    last_ctx->next = next_ctx;
    next_ctx->previous = last_ctx;
    switch_to_ctx(next_ctx);
  }
  else {
    printf("\nNo more task to execute\n");
    exit(EXIT_SUCCESS);
  }
}


void switch_to_ctx (struct ctx_s *ctx) {
  _mask(15);
  assert(ctx != NULL);
  assert(ctx->ctx_magic == MAGIC);
  assert(ctx->state== CTX_READY || ctx->state == CTX_ACTIVATED);
  if (current_ctx != NULL) {
    asm ("movl %%ebp, %0":"=r"(current_ctx->ebp));
    asm ("movl %%esp, %0":"=r"(current_ctx->esp));
  }
  current_ctx = ctx;
  asm("movl %0, %%ebp"::"r"(current_ctx->ebp));
  asm("movl %0, %%esp"::"r"(current_ctx->esp));
  _mask(0);
  if (current_ctx->state == CTX_READY) {
    exec_f(current_ctx);//cette fonction ne revient jamais
  }
}

void sem_init (struct sem_s *sem, unsigned int val) {
    sem->count=val;
    sem->ctx_locked=NULL;
}

void sem_down (struct sem_s *sem) {
  _mask(15);
  if (--(sem->count) <0) {
    current_ctx->state = CTX_LOCKED;
    struct ctx_s *next = current_ctx->next;
    //suppression des liens dans l'ordonnanceur
    current_ctx->next->previous = current_ctx->previous;
    current_ctx->previous->next=next;

    //si aucun process n'est bloqué, on ajoute current_ctx
    if (!sem->ctx_locked){
      sem->ctx_locked = current_ctx;
      current_ctx->next = current_ctx->previous = current_ctx;
    }
    //si au moins un process est bloqué, on insère en queue
    else {
      current_ctx->previous = sem->ctx_locked->previous;
      sem->ctx_locked->previous->next = current_ctx;
      current_ctx->next =sem->ctx_locked;
      sem->ctx_locked->previous = current_ctx;
    }
    _mask(0);
    switch_to_ctx(next);
  }
  else{
    _mask(0);
  }
}

void sem_up(struct sem_s * sem){
  _mask(15);
  if (++(sem->count) <=0){
    if (!sem->ctx_locked){
      exit(EXIT_FAILURE);
    }
    else {
      struct ctx_s * tmp = sem->ctx_locked;

      //supression dans la liste des ctx bloqués
      tmp->previous->next = tmp->next;
      tmp->next->previous = tmp->previous;
      sem->ctx_locked = tmp->previous->next;

      //ajout dans la liste des ctx elligibles par l'ordonnanceur
      enqueue(tmp);
      tmp->state = CTX_ACTIVATED;
    }
  }
  _mask(0);
}

void yield(){
  switch_to_ctx(current_ctx->next);
}
