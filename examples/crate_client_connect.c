#include <stdio.h>
#include <string.h>
#include <jansson.h>
#include "crateclient.h"

int main(void){
  crate_client *client; json_t *root, *cols, *rows, *row_col_value; int i,j; const char *col;
  
  client = crate_connect("akhil-laptop.intranet.bizense.com", 4200);

  /*crate_sql(client, "CREATE TABLE IF NOT EXISTS locations(id string, date timestamp, description string, kind string, name string, position integer)");  
    crate_sql(client, "insert into locations (id, date, description, kind, name, position) values ('14','2013-09-12T21:43:59.000Z','Blagulon Kappa is the planet to which the police are native.','Planet','Blagulon Kappa',7)"); */
  
  root = crate_sql(client, "select _id,* from locations");
  if(root){
    cols = json_object_get(root, "cols");
    rows = json_object_get(root, "rows");

    for(i=0;i<json_array_size(rows);i++){
      fprintf(stdout, "------- row %d -------\n", i+1);
      for(j=0;j<json_array_size(cols);j++){
	col = json_string_value(json_array_get(cols, j));
	row_col_value = json_array_get(json_array_get(rows, i), j);
	switch(json_typeof(row_col_value)){
	case JSON_STRING :
	  fprintf(stdout, "col %s : %s\n", col, json_string_value(row_col_value));
	  break;
	case JSON_INTEGER :
	  fprintf(stdout, "col %s : %d\n", col, json_integer_value(row_col_value));
	  break;
	case JSON_REAL :
	  fprintf(stdout, "col %s : %f\n", col, json_real_value(row_col_value));
	  break;
	default :
	  fprintf(stdout, "unknown col type %s\n", json_typeof(row_col_value));
	}
      }
    }
  }
}
