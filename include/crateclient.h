/*
 * Crate Client
 */
#include <stdio.h>
#include <curl/curl.h>
#include <string.h>
#include <jansson.h>

typedef struct {
  short   closed;
  CURL    *curl;
  char    *host;
  int     port;
} crate_client;

typedef struct {
  char *memory;
  size_t size;
} dynamic_memory_chunk;

crate_client* crate_connect(char* host, int port);

json_t* crate_sql(crate_client* client, char* stmt);

json_t* crate_bulkSql(crate_client* client, char** stmts);

void crate_close(crate_client* client);
