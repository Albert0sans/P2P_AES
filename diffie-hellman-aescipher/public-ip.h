#include <iostream>
#include <curl/curl.h>
using namespace std;

size_t getUrlResponse(char* buffer, size_t size, size_t count, string* response);

string get(const string& url) ;
string GetIp();

