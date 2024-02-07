#include "rand64-sw.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
/* Software implementation.  */

/* Input stream containing random bytes.  */
FILE *urandstream;

/* Initialize the software rand64 implementation.  */
void
software_rand64_init (void)
{
  urandstream = fopen ("/dev/random", "r");
  if (! urandstream){
    fprintf (stderr, "ERROR\n");
    exit(1);
  }
}
void
software_randF_init(char * ptr)
{
  urandstream = fopen (ptr, "r");
  if (! urandstream){
    fprintf (stderr, "ERROR1\n");
    exit(1);
  }
}

/* Return a random value, using software operations.  */
unsigned long long
software_rand64 (void)
{
  unsigned long long int x;
  if (fread (&x, sizeof x, 1, urandstream) != 1){
    fprintf (stderr, "ERROR2\n");
    exit(1);
  }
  return x;
}
unsigned long long
software_rand48 (void)
{
  struct drand48_data rand_data={0};
  srand48_r(time(NULL),&rand_data);
  long rand_num=0;
  mrand48_r(&rand_data,&rand_num);
  return rand_num;
}
/* Finalize the software rand64 implementation.  */
void
software_rand64_fini (void)
{
  fclose (urandstream);
}
