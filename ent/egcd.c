/*
  Author:  Pate Williams (c) 1997

  2.107 Algorithm Extended Euclidean algorithm
  See "Handbook of Applied Cryptography" by
  Alfred J. Menezes et al page 67.
  From http://www.di-mgt.com.au/euclidean.html
*/

#include <stdio.h>

#define DEBUG

void extended_euclid(long a, long b, long *x,
                     long *y, long *d)
/* calculates a * *x + b * *y = gcd(a, b) = *d */
{
  long q, r, x1, x2, y1, y2;

  if (b == 0) {
    *d = a, *x = 1, *y = 0;
    return;
  }
  x2 = 1, x1 = 0, y2 = 0, y1 = 1;
  #ifdef DEBUG
  printf("------------------------------");
  printf("-------------------\n");
  printf("q    r    x    y    a    b    ");
  printf("x2   x1   y2   y1\n");
  printf("------------------------------");
  printf("-------------------\n");
  #endif
  while (b > 0) {
    q = a / b, r = a - q * b;
    *x = x2 - q * x1, *y = y2 - q * y1;
    a = b, b = r;
    x2 = x1, x1 = *x, y2 = y1, y1 = *y;
    #ifdef DEBUG
    printf("%4ld %4ld %4ld %4ld ", q, r, *x, *y);
    printf("%4ld %4ld %4ld %4ld ", a, b, x2, x1);
    printf("%4ld %4ld\n", y2, y1);
    #endif
  }
  *d = a, *x = x2, *y = y2;
  #ifdef DEBUG
  printf("------------------------------");
  printf("-------------------\n");
  #endif
}

/*Check the difference. */
unsigned int modinv(unsigned int u, unsigned int v)
{
    unsigned int inv, u1, u3, v1, v3, t1, t3, q;
    int iter;
    /* Step X1. Initialise */
    u1 = 1;
    u3 = u;
    v1 = 0;
    v3 = v;
    /* Remember odd/even iterations */
    iter = 1;
    /* Step X2. Loop while v3 != 0 */
    while (v3 != 0)
    {
        /* Step X3. Divide and "Subtract" */
        q = u3 / v3;
        t3 = u3 % v3;
        t1 = u1 + q * v1;
        /* Swap */
        u1 = v1; v1 = t1; u3 = v3; v3 = t3;
        iter = -iter;
    }
    /* Make sure u3 = gcd(u,v) == 1 */
    if (u3 != 1)
        return 0;   /* Error: No inverse exists */
    /* Ensure a positive result */
    if (iter < 0)
        inv = v - u1;
    else
        inv = u1;
    return inv;
}

int main(void)
{
  long a = 4864, b = 3458, d, x, y;

  extended_euclid(a, b, &x, &y, &d);
  printf("x = %ld y = %ld d = %ld\n", x, y, d);
  return 0;
}
