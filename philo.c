/*
 * philo.c
 * Authors : Honoré NINTUNZE & Antoine PETIT
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contexte.h"

struct sem_s fourchette_un,fourchette_deux,fourchette_trois,fourchette_quatre;

func_t f_philo1;
func_t f_philo2;
func_t f_philo3;
func_t f_philo4;

void mange(char*);
void parle(char*);

int main(int argc, char** argv){

  sem_init(&fourchette_un,1);
  sem_init(&fourchette_deux,1);
  sem_init(&fourchette_trois,1);
  sem_init(&fourchette_quatre,1);
  
  create_ctx(16384, &f_philo1, NULL);
  create_ctx(16384, &f_philo2, NULL);
  create_ctx(16384, &f_philo3, NULL);
  create_ctx(16384, &f_philo4, NULL);
  start_schedule();
  exit(EXIT_SUCCESS);
}

void mange(char* str){
  printf("%s mange\n",str);
}

void parle(char* str){
  printf("%s parle\n",str);
}

void f_philo1 (void *args){
  while(1){
    parle("philo1");
    sem_down(&fourchette_un);
    sem_down(&fourchette_quatre);
    mange("philo1");
    sem_up(&fourchette_quatre);
    sem_up(&fourchette_un);
  }
}

void f_philo2 (void *args){
  while(1){
    parle("philo2");
    sem_down(&fourchette_un);
    sem_down(&fourchette_deux);
    mange("philo2");
    sem_up(&fourchette_deux);
    sem_up(&fourchette_un);
  }
}

void f_philo3 (void *args){
  while(1){
    parle("philo3");
    sem_down(&fourchette_deux);
    sem_down(&fourchette_trois);
    mange("philo3");
    sem_up(&fourchette_trois);
    sem_up(&fourchette_deux);
  }
}

void f_philo4 (void *args){
  while(1){
    parle("philo4");
    sem_down(&fourchette_trois);
    sem_down(&fourchette_quatre);
    mange("philo4");
    sem_up(&fourchette_quatre);
    sem_up(&fourchette_trois);
  }
}
