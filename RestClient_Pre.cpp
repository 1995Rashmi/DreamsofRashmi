 #include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>
#include <curl/curl.h>
#include <fstream>
#include "json/json.h"



using namespace std;

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

int main(void)
{
CURLcode ret;
  CURL *curl;
  struct curl_slist *header;
  string readBuffer;
  string data = "{\"userName\": \"tord+apiclient@precisely.se\", \"password\": \"CqE9pTqxQg6NXqbyaCZoE6b8\"}";
  //cout<<data<<endl;

  header = NULL;
  header = curl_slist_append(header, "Content-Type: application/json");
  header = curl_slist_append(header, "accept: application/json");
 
  curl = curl_easy_init();
  curl_easy_setopt(curl, CURLOPT_URL, "https://api-qa.precisely.se/authenticate");
  curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data.c_str());
  curl_easy_setopt(curl, CURLOPT_HTTPHEADER, header);
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
  ret = curl_easy_perform(curl);
if (ret != CURLE_OK) {
        cerr << "curl_easy_perform() failed: " << curl_easy_strerror(ret) << endl;
      }
  curl_easy_cleanup(curl);
  curl = NULL;
  curl_slist_free_all(header);
  header = NULL;
  cout<<readBuffer<<endl<<endl;
  readBuffer.erase (0,16);
  //cout<<readBuffer<<endl<<endl;
  readBuffer.resize (readBuffer.size () - 71);
  //cout<<readBuffer<<endl<<endl;
 
  /******Download file*********/

 Json::Reader reader;
 Json::Value root;
 Json::StyledStreamWriter writer;
 ofstream outFile;
// fstream outFile;
 system("mkdir -p document_id");


  curl = curl_easy_init();
  data = "{\"email\": \"tord+apiclient@precisely.se\", \"id\":5, \"name\": \"ApiClient\"}";
  string header2 = "Authorization: Bearer " + readBuffer;
  //cout<<header2<<endl<<endl;
  header = curl_slist_append(header, header2.c_str());    
  header = curl_slist_append(header, "accept: application/pdf");
 
  readBuffer.clear();

  //curl_easy_setopt(curl, CURLOPT_URL, "https://api-qa.precisely.se/organizations/5/documents/y5bhWAg/pdf");
  					  
  curl_easy_setopt(curl, CURLOPT_URL, "https://api-qa.precisely.se/organizations/5/documents");
  //curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data.c_str());
  curl_easy_setopt(curl, CURLOPT_HTTPHEADER, header);
  curl_easy_setopt(curl, CURLOPT_HTTPGET, "1L");
  curl_easy_setopt(curl, CURLOPT_TCP_KEEPALIVE, 1L);
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
  
///Responce ithe yeto ah readBuffer........
  ret = curl_easy_perform(curl);
  //cout<<"Otput : "<<readBuffer<<endl;
  outFile.open("document_id//y5bhWAg.txt");
   outFile<<readBuffer;
   outFile.close();
   if(!reader.parse(readBuffer, root)){  //......he function used karun responce la me json file mdh store kel ah
   	cout<<reader.getFormattedErrorMessages();
   	exit(1);
   }else{
        outFile.open("document_id//Precisely.json");
         writer.write(outFile,root);
        outFile.close();
        cout << "The employee list is size " << root.size() << '\n';
        curl = curl_easy_init();
  	//int id=0;
  	struct curl_slist *url;
        for(int i=0; i<root.size(); i++){
         Json::Value id;   
         id = root[i]["id"];  
         cout<<"id = "<<id<<endl;
         string id1 = id.asString();
         string url = "https://api-qa.precisely.se/organizations/5/documents/" + id1 + "/pdf";
         //cout<<url;
         curl = curl_easy_init(); 
         curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
         curl_easy_setopt(curl, CURLOPT_HTTPHEADER, header);
  	 curl_easy_setopt(curl, CURLOPT_HTTPGET, "1L");
  	 curl_easy_setopt(curl, CURLOPT_TCP_KEEPALIVE, 1L);
 	 curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
 	 curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
 	 ret = curl_easy_perform(curl);
 	 //cout<<readBuffer<<endl<<endl;
 	 string path = "document_id//" + id1+ ".txt";
 	 ofstream outfile;
 	 outfile.open(path);
 	 //write(outfile,readBuffer);
 	 outfile<<readBuffer;
 	 if (ret != CURLE_OK) {
        cerr << "curl_easy_perform() failed: " << curl_easy_strerror(ret) << endl;
      }
 	 curl_easy_cleanup(curl);
  	 curl = NULL;
         readBuffer.clear();
        outfile.close();
      }
       
        writer.write(outFile,root);
        outFile.close();
   }
   
if (ret != CURLE_OK) {
        cerr << "curl_easy_perform() failed: " << curl_easy_strerror(ret) << endl;
      }
// printf ("\nFinished curl test.\n");
 curl_easy_cleanup(curl);
  curl = NULL;
  curl_slist_free_all(header);
  header = NULL;
 
  return 0;
  }



