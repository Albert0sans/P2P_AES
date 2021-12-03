#include "random_l.h"


mpz_class SECURE_TRAND(int bits){

mpz_class a[bits/32],total;
    if (sodium_init() == -1) {
        return 1;
    }
   
    for(int i=0;i<bits/32;i++){
   	 a[i]=randombytes_random();
    
  	 for(int j=0;j<i;j++)
   		 for(int w=0;w<32;w++)
   			 a[i]=a[i]*2;
    
    
    
    total+=a[i];
    }
    
    return total;
}
mpz_class GetSharedKey(mpz_class p, mpz_class pr,mpz_class received){

mpz_class res;
 mpz_powm(res.get_mpz_t(),received.get_mpz_t(),pr.get_mpz_t(),p.get_mpz_t());

return res;

}
