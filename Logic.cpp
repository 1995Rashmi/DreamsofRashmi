#include <iostream>
#include <string>
#include <curl/curl.h>


int main(void)
{
  CURL *curl;
  CURLcode res;
  std::string readBuffer;

  curl = curl_easy_init();
  if(curl) {
 
    curl_easy_setopt(curl, CURLOPT_URL, "https://api-qa.precisely.se");
    curl_easy_setopt(curl, CURLOPT_HTTPAUTH, (long)CURLAUTH_ANY);
    curl_easy_setopt(curl, CURLOPT_USERNAME, "tord+apiclient@precisely.se");
    curl_easy_setopt(curl, CURLOPT_PASSWORD, "CqE9pTqxQg6NXqbyaCZoE6b8");
    res = curl_easy_perform(curl);
    if(res != CURLE_OK){
      fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res));
 
    
    curl_easy_cleanup(curl);
  }
    curl_easy_cleanup(curl);

    std::cout << readBuffer << std::endl;
  }
  return 0;
}
