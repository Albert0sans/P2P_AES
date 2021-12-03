#include <sodium.h>
#include <iostream>
#include <gmp.h>
#include <gmpxx.h>
using namespace std;

 mpz_class SECURE_TRAND(int bits);
 mpz_class GetSharedKey(mpz_class p, mpz_class pr,mpz_class received);
