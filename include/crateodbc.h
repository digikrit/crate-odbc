#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#if defined(_WIN32)
#include <windows.h>
#include <sqlext.h>
#elif defined(INFORMIX)
#include "infxcli.h"
#elif defined(UNIXODBC)
#include "sql.h"
#include "sqltypes.h"
#include "sqlext.h"
#endif

typedef struct {
  short      closed;
  int        conn_counter;
  SQLHENV    henv;               /* environment handle */
} env_data;


typedef struct {
  short      closed;
  int        cur_counter;
  int        env;                /* reference to environment */
  SQLHDBC    hdbc;               /* database connection handle */
} conn_data;


typedef struct {
  short      closed;
  int        conn;               /* reference to connection */
  int        numcols;            /* number of columns */
  int        coltypes, colnames; /* reference to column information tables */
  SQLHSTMT   hstmt;              /* statement handle */
} cur_data;

#define error(a) ((a) != SQL_SUCCESS && (a) != SQL_SUCCESS_WITH_INFO)
