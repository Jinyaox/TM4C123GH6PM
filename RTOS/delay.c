#include "delay.h"

void delay(int x){
  int volatile count=x;
  while(count>0){--count;}
  return;
}

int fact(int n){
  if(n==1){return 1;}
  else{
    return n*fact(n-1);
  }
}