#include "AES.h"



string cipher_data(AES256_ctx ctx, string text, int N) {//string de mas de 16 bytes a -----------------------

    string cipher;

    unsigned char buffer[16];
    string buff;
    char* aux;
    while (text.length() % N != 0)
        text.push_back(' ');

    int at,aux2, pre = 0;
    for (uint8_t i = 0; i < text.length() / N; i++) {
        at = pre + N;
        aux2 = at - pre;
        buff = &(text.substr(pre,aux2))[0];

        aux = &buff[0];
       

        AES256_encrypt(&ctx, 1, buffer, (unsigned char*)aux);
        for (auto a : buffer) {
            cipher.push_back(a);
          
        }


        pre = at;

    }



    return cipher;

}

string decipher_data(AES256_ctx ctx,string cipher, int N) {

    string decipher;

    unsigned char buffer[16] = { '0' };
    string buff;
    char* aux;
    

    size_t at, pre = 0,aux2;
    for (int i = 0; i < cipher.length() / N; i++) {
        at = pre + N;
        aux2 = at - pre;
        buff = &(cipher.substr(pre,at))[0];

        aux = &buff[0];
        //cout << "Desciframos" << endl;
        //for (int i = 0; i < 16; i++)
          //  cout << (int)((unsigned char)(aux[i]));

       AES256_decrypt(&ctx, 1, buffer, (unsigned char*)aux);
       //cout<<"resultado="<<endl;
       for (auto a : buffer) {
           decipher.push_back(a);
           
       }





        pre = at;

    }



    return decipher;

}


void from_hex(unsigned char* data, int len, const char* hex) {//convierte a un array de enteros
    int p;
    for (p = 0; p < len; p++) {
        int v = 0;
        int n;
        for (n = 0; n < 2; n++) {
            assert((*hex >= '0' && *hex <= '9') || (*hex >= 'a' && *hex <= 'f'));
            if (*hex >= '0' && *hex <= '9') {
                v |= (*hex - '0') << (4 * (1 - n));
            }
            else {
                v |= (*hex - 'a' + 10) << (4 * (1 - n));
            }
            hex++;

        }
        *(data++) = v;
    }
    assert(*hex == 0);

}



