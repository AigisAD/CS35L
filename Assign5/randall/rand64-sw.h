#ifndef RAND64_SW // include guard
#define RAND64_SW

/* Software implementation.  */

/* Initialize the software rand64 implementation.  */
void
software_rand64_init (void);

void
software_randF_init(char* ptr);

/* Return a random value, using software operations.  */
unsigned long long
software_rand64 (void);

unsigned long long
software_rand48 (void);

/* Finalize the software rand64 implementation.  */
void
software_rand64_fini (void);

#endif 