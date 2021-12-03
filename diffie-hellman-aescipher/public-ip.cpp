#include "public-ip.h"

size_t getUrlResponse(char* buffer, size_t size, size_t count, string* response) {
    size_t recv_size = size * count;
    response->clear();
    response->append(buffer);
	return recv_size;
}

string get(const string& url) {
    
    string response;
	
	CURL *handle;
	
	handle = curl_easy_init();
	
	curl_easy_setopt(handle, CURLOPT_URL, url.c_str());
	
	curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, &getUrlResponse);
	
  
    curl_easy_setopt(handle, CURLOPT_WRITEDATA, &response);
	
	curl_easy_perform(handle);
	
	curl_easy_cleanup(handle);
	
    return response;
}
string GetIp(){
return get("https://api.ipify.org");}

