#include "output.h"
#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include <stdlib.h>
bool
writebytes (unsigned long long x, int nbytes,long long block_size)
{
  if (block_size==0){
    do
      {
        if (putchar (x) < 0)
          return false;
        x >>= CHAR_BIT;
        nbytes--;
      }
    while (0 < nbytes);
  }else{
    unsigned long long*ptr=malloc(nbytes*sizeof(long long));
    ptr=&x;
    do
      {
        int written=0;
        if(block_size>nbytes)
          written=write(1,ptr,nbytes%block_size);
        else  
          written=write(1,ptr,block_size);
        x >>= CHAR_BIT;
        nbytes-=written;
      }
    while (0 < nbytes);
  }

  return true;
}
