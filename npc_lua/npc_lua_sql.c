#include "npc_lua.h"
#include "util.h"
#include "char.h"
#include "char_base.h"
#include "char_data.h"
#include "anim_tbl.h"
#include "object.h"
#include "battle.h"
#include "npcutil.h"
#include "item.h"
#include "readmap.h"
#include "saacproto_cli.h"
#include "cg_api.h"

#ifdef _JZ_NEWSCRIPT_LUA



int NPC_Lua_SQL_Run(lua_State *_NLL)
{
	CheckEx(_NLL, 1);
	char*  sqlStr = NULL;
	sqlStr = lua_tostring(_NLL, 1);
/*
	//TestTable
	LNweTableInit(_NLL);
	LNweTableStr(_NLL, "0_0", "Yo~~~");
	LNweTableStr(_NLL, "0_1", "HaHa~~~");
	LNweTableStr(_NLL, "0_2", "GOGO~~~");
	LRetTable();
*/
	
	char sqlStr_Prefix[32];
	strncpy(sqlStr_Prefix, sqlStr, 10);
	sqlStr_Prefix[10] = '\0';
	int i;
	//轉成小寫
	for(i=0; i<10; i++){
		if(sqlStr_Prefix[i] >= 'A' && sqlStr_Prefix[i] <= 'Z'){
			sqlStr_Prefix[i] = 'a' + (sqlStr_Prefix[i] - 'A');
		}
	}
	
	//int mysqlIndex = API_DB_getMysqlIndex();
	//int mysql = 500 * mysqlIndex + 135962660;
	char mysqlStruct[500];
	int mysql = (int)mysqlStruct;
	int mysql_res;
	char** mysql_row;
	
	API_mysql_init(mysql);
	//API_mysql_real_connect(mysql, "127.0.0.1", "root", "passwd", "crossgate", 0, NULL, 0);
	API_mysql_real_connect(mysql, (char*)0x8C89C14, (char*)0x8C89C34, (char*)0x8C89C54, (char*)0x8C89C74, 0, NULL, 0);

	if(strstr(sqlStr_Prefix, "select")){ //SECECT
		if(!API_mysql_query(mysql, sqlStr)){
			int num_row=0;
			int num_field=0;
			mysql_res = API_mysql_store_result(mysql);
			num_row = API_mysql_num_rows(mysql_res);
			num_field = API_mysql_num_fields(mysql_res);
			if(num_row > 0){
				LNweTableInit(_NLL);
				LNweTableInt(_NLL, "row", num_row);
				LNweTableInt(_NLL, "field", num_field);
				int i;
				for(i=0; i<num_row; i++){
					mysql_row = API_mysql_fetch_row(mysql_res);
					int j;
					for(j=0; j<num_field; j++){
						char keyStr[32];
						sprintf(keyStr, "%d_%d", i, j);
						LNweTableStr(_NLL, keyStr, mysql_row[j]);
					}
				}
				API_mysql_free_result(mysql_res);
				//API_DB_releaseMySqlIndex(mysqlIndex);
				API_mysql_close(mysql);
				LRetTable();
			}else{
				API_mysql_free_result(mysql_res);
				//API_DB_releaseMySqlIndex(mysqlIndex);
				API_mysql_close(mysql);
				LRetErrNull(_NLL, "查無結果。");
			}
		}else{
			char errmsg[1024];
			strcpy(errmsg, API_mysql_error(mysql));
			//API_DB_releaseMySqlIndex(mysqlIndex);
			API_mysql_close(mysql);
			LRetErrNull(_NLL, errmsg);
		}
	
	}else{ //INSERT, DELETE, ...
		int retInt = API_mysql_query(mysql, sqlStr);
		if(retInt == 0){
			//API_DB_releaseMySqlIndex(mysqlIndex);
			API_mysql_close(mysql);
			LRetInt(_NLL, retInt);
		}else{
			char errmsg[1024];
			strcpy(errmsg, API_mysql_error(mysql));
			//API_DB_releaseMySqlIndex(mysqlIndex);
			API_mysql_close(mysql);
			LRetErrInt(_NLL, retInt, errmsg);
		}
	}
}

#endif