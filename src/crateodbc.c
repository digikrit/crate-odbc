
/*
 * Crate ODBC Driver
 */
#include "crateodbc.h"

/*
 * various functions for validating the structures
 */
/* check for valid environment */
static env_data *getenvironment(){
  return NULL;
}
/* check for valid connection */
static conn_data *getconnection(){
  return NULL;
}
/* check for valid cursor */
static cur_data *getcursor(){
  return NULL;
}

/* returns the name of an equivalent crate type for a sql type */
static const char *sqltypetocratetype(const SQLSMALLINT type){
  
  return NULL;
}
/*
 * various functions corresponding to cursor
 */
/* retrieves data from the i_th column in the current row */
static int push_column(){
  return 0;
}
/* get another row of the given cursor */
static int cur_fetch(){
  return 0;
}
/* closes a cursor */
static int cur_close(){
  return 0;
}
/* returns the table with column names */
static int cur_colnames(){
  return 0;
}
/* returns the table with column types */
static int cur_coltypes(){
  return 0;
}
/* creates two tables with the names and the types of the columns */
static void create_colinfo(){

}
/* creates a cursor table and leave it on the top of the stack */
static int create_cursor(){
  return 0;
}

/*
 * various functions corresponding to connections
 */

/* execute the sql statement */
static int conn_execute(){
  return 0;
}
/* create new connection */
static int create_connection(){
  return 0;
}
/* close the connection */
static int conn_close(){
  return 0;
}

/*
 * various functions corresponding to transactions
 */
/* commit the current transaction */
static int conn_commit(){
  return 0;
}
/* rollback the current transaction */
static int conn_rollback(){
  return 0;
}
/* sets the auto commit mode */
static int conn_setautocommit(){
  return 0;
}

/*
 * various functions corresponding to environment
 */
/* connect using environment */
static int env_connect(){
  return 0;
}
/* close the environment */
static int env_close(){
  return 0;
}
/* create environment */
static int create_environment(){
  return 0;
}
/* create metatables */
static void create_metatables(){

}
