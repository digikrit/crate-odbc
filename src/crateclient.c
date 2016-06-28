/*
 * Crate C Client Implementation
 */
#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>
#include "crateclient.h"

/* create and initialize crate client */
crate_client* crate_connect(char* host, int port){    
  crate_client* client;

  /* initialize client */
  curl_global_init(CURL_GLOBAL_ALL);
  client = (crate_client*)malloc(sizeof(crate_client));
  client->curl = curl_easy_init();;
  client->closed = 0;
  client->host = host;
  client->port = port;
  
  return client;
}

static size_t write_memory_callback(void *contents, size_t size, size_t nmemb, void *userp){
  size_t realsize = size * nmemb;
  dynamic_memory_chunk *mem = (dynamic_memory_chunk *)userp;
  
  mem->memory = realloc(mem->memory, mem->size + realsize + 1);
  if(mem->memory == NULL) {
    /* out of memory! */
    printf("not enough memory (realloc returned NULL)\n");
    return 0;
  }
  
  memcpy(&(mem->memory[mem->size]), contents, realsize);
  mem->size += realsize;
  mem->memory[mem->size] = 0;
  
  return realsize;
}

json_t* crate_sql(crate_client* client, char* stmt){
  char url[1024], stmt_json[1024];
  CURLcode res; dynamic_memory_chunk chunk;
  json_t *root; json_error_t error;
  
  chunk.memory = malloc(1);
  chunk.size = 0;
  
  if(client->curl && !client->closed){
    curl_easy_setopt(client->curl, CURLOPT_USERAGENT, "libcurl-agent/1.0");
    curl_easy_setopt(client->curl, CURLOPT_WRITEFUNCTION, write_memory_callback);
    curl_easy_setopt(client->curl, CURLOPT_WRITEDATA, (void *)&chunk);
    
    /* set the url */
    sprintf(url, "http://%s:%i/_sql", client->host, client->port);
    curl_easy_setopt(client->curl, CURLOPT_URL, url);
    fprintf(stdout, "using url for crate : %s\n", url);
    
    /* set the stmt */       
    sprintf(stmt_json, "{\"stmt\": \"%s\"}\n", stmt);
    curl_easy_setopt(client->curl, CURLOPT_POSTFIELDS, stmt_json);
    fprintf(stdout, "using stmt for crate : %s\n", stmt_json);
    
    /* call curl */
    res = curl_easy_perform(client->curl);
    if(res == CURLE_OK){
      fprintf(stdout, "got response from crate : %s\n", chunk.memory);
      root = json_loads(chunk.memory, 0, &error);
      free(chunk.memory);
      return root;
    }
    else fprintf(stderr, "error while executing crate sql statement");
  }
  else fprintf(stderr, "crate client not connected");
  
  return NULL;
}
/* TODO : Implement the crate bulk sql */
json_t* crate_bulkSql(crate_client* client, char** stmts){
  return NULL;
}

/* clean up the client resources */
void crate_close(crate_client* client){
  curl_easy_cleanup(client->curl);
  curl_global_cleanup();
  free(client);
}
