#include <assert.h>
#include "ctaes.h"
#include <vector>
#include <stdio.h>
#include <string.h>

#include <iostream>
#include <iomanip>
#include <sstream>
using namespace std;
string decipher_data(AES256_ctx ctx,string cipher, int N);
string cipher_data(AES256_ctx ctx, string text, int N);
void from_hex(unsigned char* data, int len, const char* hex);
