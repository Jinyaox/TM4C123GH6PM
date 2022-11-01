#include "bsp.h"
#include <stdint.h>

#define MAX_LEN 32

void get_command(char buf[],int max_len){
  char c;
  int counter=0;
  do{
    c=UART_RX();
    buf[counter]=c;
    counter++;
  }while((c!=0x0d)&&(counter<max_len));
  buf[counter-1]='\n';
  return;
}

int main()
{
  UART_SETUP();
  char buf[MAX_LEN];
  memset(buf,0,MAX_LEN);

  while(1){
    //UART_TX(UART_RX());
    get_command(buf,MAX_LEN);
    print_str(buf);
    //we can do encryption with the buffer now
    memset(buf,0,32);
  }
  return 0;
}