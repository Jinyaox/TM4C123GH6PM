#include "bsp.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "sha256.h"

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

void encrypt(char* dest, char* source){
  struct tc_sha256_state_struct s;
  (void)tc_sha256_init(&s);
  tc_sha256_update(&s, (uint8_t *) source, strlen(source));
  (void)tc_sha256_final(dest, &s);
  dest[32]='\n'; dest[33]='\0';
}

int main()
{
  UART_SETUP();
  char buf[MAX_LEN];
  char encrypt_buf[34];
  memset(buf,0,MAX_LEN);
  memset(encrypt_buf,0,34);

  while(1){
    get_command(buf,MAX_LEN);
    encrypt(encrypt_buf,buf);
    print_str(encrypt_buf);
    memset(buf,0,32);
    memset(encrypt_buf,0,32);
  }
  return 0;
}