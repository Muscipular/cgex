#ifndef _CG_API_H
#define _CG_API_H

#include <stdlib.h>
#include <string.h>
#include "util.h"

//#define _VERIFY

#define CHARAPTR int
#define CHARAINDEX int
#define OBJINDEX int

#ifdef _VERIFY
extern int info1;
extern char* info1_buf;

extern int info2;
extern char* info2_buf;

extern int info3;
extern char* info3_buf;
#endif

//擴增NL庫 事件資訊
typedef enum
{
	NL_BATTLEOVERFUNC,
	NL_BATTLESTARTFUNC,
//	NL_DROPFUNC,
	NL_LEVELUPFUNC,
	NL_LOGINFUNC,
	NL_LOGINGATEFUNC,
	NL_LOGOUTFUNC,
	NL_TALKFUNC,
	NL_TITLECHANGEFUNC,
	NL_WARPFUNC,
	NL_FUNCTABLENUM,
}NL_FUNCTABLE;

//擴增NL庫 CallBack 事件
typedef struct tagNL_DATA_EXTEND_STRUCT
{
    STRING128 functable[NL_FUNCTABLENUM];
	int use[NL_FUNCTABLENUM];
}NL_DATA_EXTEND_STRUCT;

extern NL_DATA_EXTEND_STRUCT NL_DATA_EXTEND;



//擴增lua char 事件資訊
typedef enum
{
    CHAR_INITFUNC,
	CHAR_WALKPREFUNC,
	CHAR_WALKPOSTFUNC,
	CHAR_LOOPFUNC,
    CHAR_PREOVERFUNC,
    CHAR_POSTOVERFUNC,
	CHAR_TALKEDFUNC,
	CHAR_WINDOWTALKEDFUNC,
	CHAR_FUNCTABLENUM,
}CHAR_FUNCTABLE;

typedef enum
{
    BATTLE_WIN,
	BATTLE_FUNCTABLENUM,
}BATTLE_FUNCTABLE;

//擴充人物 CallBack 事件
typedef struct tagCHAR_DATA_EXTEND_STRUCT
{
    STRING128 functable[CHAR_FUNCTABLENUM];
	int funcAddr[CHAR_FUNCTABLENUM];
}CHAR_DATA_EXTEND_STRUCT;

extern CHAR_DATA_EXTEND_STRUCT* CHAR_DATA_EXTEND;

//擴充 Battle CallBack 事件
typedef struct tagBATTLE_DATA_EXTEND_STRUCT
{
    STRING128 functable[BATTLE_FUNCTABLENUM];
}BATTLE_DATA_EXTEND_STRUCT;

extern BATTLE_DATA_EXTEND_STRUCT* BATTLE_DATA_EXTEND;

//因應擴充人物資料, 擴展 CHAR_cleanUpChar
void my_CHAR_cleanUpChar_memset(int des, int value, int size);

//Util
char *strcpy_s(char *des, size_t n, const char *src);

int my_mprotect(int address);

int getStringFromIndexWithDelim_body( char* src ,char* delim ,int index, char* buf , int buflen, char *file, int line );
#define getStringFromIndexWithDelim( src, delim, index, buf, buflen ) getStringFromIndexWithDelim_body( src, delim, index, buf, buflen, __FILE__, __LINE__ )

int my_CHAR_getChatMagicFuncPointer(const char *cmd, int opt);

//API
int API_NPC_CHECKCREATEINDEX(int a1);

CHARAPTR API_CHAR_getLinkChar(int type);

int API_CHAR_doInitEvent(CHARAPTR a1);

int API_initObjectFromObjectMember(int a1, CHARAPTR a2, int mapid, int floorid, int x, int y);

int API_CHAR_cleanUpChar(CHARAPTR a1);

int API_CHAR_endCharOneArray(CHARAPTR a1);

int API_MAP_sendAroundMapdata(int mapid, int floorid, int x, int y);

int API_CHAR_sendWatchEvent(OBJINDEX a1, int a2, int a3, signed int a4, int a5);

int API_CHAR_sendCToArroundCharacter(OBJINDEX a1);

int API_CHAR_talkToCli(CHARAPTR to, CHARAPTR talker, char* msg, int fontcolor, int fontsize);

int API_CHAR_CharaDelete(CHARAPTR a1);

int API_CHAR_CheckCharPointer(CHARAPTR a1);

//int API_CHAR_complianceParameter(CHARAPTR a1, CHARAPTR a2, int a3);
int API_CHAR_complianceParameter(CHARAPTR a1, int a2);

inline int API_GetCharaPtrFromCharaIndex(CHARAINDEX index);

int API_CHAR_getEnablePlayerMaxNum();

int API_BATTLE_WatchEntry(CHARAPTR watcher, CHARAPTR to);

int API_CHAR_walk(CHARAPTR charptr, int direction, int type);

int API_NPC_Util_charIsInFrontOfChar(CHARAPTR char1, CHARAPTR char2, int distance);

int API_OBJECT_getType(int a1);

int API_OBJECT_getIndex(int a1);

int API_OBJECT_getMapId(int a1);

int API_OBJECT_getFloor(int a1);

int API_OBJECT_getX(int a1);

int API_OBJECT_getY(int a1);

int API_OBJECT_setType(int a1, int a2);

int API_OBJECT_setIndex(int a1, int a2);

int API_OBJECT_setMapId(int a1, int a2);

int API_OBJECT_setFloor(int a1, int a2);

int API_OBJECT_setX(int a1, int a2);

int API_OBJECT_setY(int a1, int a2);

int API_CHAR_sendCharaAtWalk(int a1, int a2, int a3, int a4, int a5, int a6, int a7);

int API_CHAR_getDX(int a1);

int API_CHAR_getDY(int a1);

int API_MAP_objmove(char* a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8, int a9, int a10, int a11);


int API_SYSTEMMSG(int a1, int a2);

int API_CHAR_setFlg(int a1, int a2, int a3, int a4, int a5);

int API_CHAR_getFlg(int a1, int a2, int a3, int a4);

int API_BATTLE_CreateBattle();

int API_MAP_getfloorIndex(int a1, int a2, int a3);

int API_CHAR_getCharPointer(int a1, int a2, int a3);

int API_BATTLE_PartyNewEntry(int a1, int a2, int a3);

int API_ENEMY_getEnemy(int a1, int a2, int a3, int a4, int a5, int a6, int a7);

int API_NPC_Util_getEnemy(int a1, int a2, int a3, int a4, int a5, int a6);

int API_NPC_Util_GetDungeonSeqNo(int a1);

int API_NPC_getWorkPointer(int a1);

int API_ITEMBOX_getMimicEncountArray(int a1);

int API_NPC_ItemboxEX_getEnemy(int a1, int a2, int a3, int a4, int a5, int a6);

int API_ENEMY_getEnemyFromEncountArray(int a1, int a2, int a3, int a4, int a5, int a6);

int API_BATTLE_BossCheck(int a1);

int API_BATTLE_GetFieldNo(int a1, int a2, int a3);

int API_BATTLE_ListRand(int a1);

int API_ENEMY_createEnemy(int a1, int a2, int a3);

int API_BATTLE_NewEntry(int a1, int a2, int a3, int a4);

int API_CHAR_getUseName(int a1);

int API_ITEM_TohelosFloorCheck(int a1);

int API_getfdFromChar(int a1);

int API_BATTLE_ExitAll(int a1);

//usercall
int API_BATTLE_DeleteBattle(int a1);

int API_nrproto_EN_send(int a1, int a2, int a3);

int API_CHAR_updateGraphic(int a1);

int API_CHAR_sendBattleEffect(int a1, int a2);

int API_CHAR_getPartyCharPointer(int a1, int a2);

int API_RAND(int a1, int a2);

int API_ENEMY_getEnemyArrayFromId(int a1);

int API_CHAR_sendAction(int charptr, int action, int mode);

void API_CHAR_processWindow(int charaptr, int seqno, int select, int objindex, char* data );

int API_CHAR_DischargePartyNoMsg(int a1);

int API_CHAR_PartyWarp(int charaptr, int mapid, int floor, int x, int y);

int API_MAP_IsValidCoordinate(int mapid, int floor, int x, int y);

char* API_makePartyParamString(int charaptr, char *buf);

int API_nrproto_PP_send(int fd, char* buf);

int API_CHAR_sendPartyParamAll(int charaptr);

int API_CHAR_sendBattleDuel(int a1, int a2);

int API_CHAR_RingWatch(int a1);

int API_BATTLE_DuelPointCheck(int a1);

int API_CHAR_getPlayerMaxNum();

int API_BATTLE_getBattleFieldNo(int a1, int a2, int a3, int a4);

int API_CHAR_checkEffect(int a1);

int API_CHAR_getChatMagicFuncPointer(const char *cmd, int opt);

int API_CHAR_getHavePetCharPointer(int a1, int a2);

int API_ENEMY_getEnemyNum();

int API_ENEMY_getInt(int a1, int a2);

int API_PET_createPetFromCharaIndex(int a1, int a2);

int API_CHAR_send_KP_String(int a1, int a2, int a3);

int API_CHAR_send_KP2_String(int a1, int a2, int a3);

int API_CHAR_sendPetTechData(int a1, int a2);

int API_ENEMYTEMP_getEnemyTempArray(int a1);

int API_LogPet(int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8, int a9, int a10);

int API_PET_stopFieldPet(int a1, int a2);

int API_PET_stopRidePet(int charaPtr);

int API_CHAR_sendInjuryEffect(int a1);

int API_PET_getHavePetIndex(int a1);

int API_CHAR_getSkillId(int a1, int a2, int a3, int a4);

int API_SKILL_getSkillIndex(int a1);

int API_TECH_setSkillExp(int a1, int a2, int a3, int a4, int a5, int a6, int a7);


int API_CHAR_ObjectDelete(int a1);

int API_CHAR_send_CP2_String(int a1, int a2);

int API_CHAR_setHavePetCharPointer(int a1, int a2, int a3);

int API_CONNECT_isCLI(int a1);

int API_CONNECT_isLOGIN(int a1);

int API_CHAR_walk_init(int a1, int a2, int a3, int a4, int a5);

int _API_MAP_getTopObj(char* file, int line, int mapid, int floor, int x, int y);
#define API_MAP_getTopObj(mapid, floor, x, y) _API_MAP_getTopObj(__FILE__, __LINE__, mapid, floor, x, y)

int API_NEXT_OBJECT(int object);

int API_CHAR_getSameCoordinateObjects(int* objbuf, int siz, int mapid, int ff, int fx, int fy);


int API_CHAR_findEmptyItemBox(int charaPtr);

int  API_ITEM_makeItemAndRegist(int itemID);

int _API_CHAR_setItemIndex(char* file, int line, int charaptr, int pos, int itemindex);
#define API_CHAR_setItemIndex(charaptr, pos, itemindex) _API_CHAR_setItemIndex(__FILE__, __LINE__, charaptr, pos, itemindex)

int _API_CHAR_getItemIndex(char* file, int line, int charaptr, int pos);
#define API_CHAR_getItemIndex(charaptr, pos) _API_CHAR_getItemIndex(__FILE__, __LINE__, charaptr, pos)

int _API_CHAR_unsetItem(char* file, int line, int charaptr, int pos);
#define API_CHAR_unsetItem(charaptr, pos) _API_CHAR_unsetItem(__FILE__, __LINE__, charaptr, pos)

int _API_ITEM_endExistItemsOne(char* file, int line, int itemindex);
#define API_ITEM_endExistItemsOne(itemindex) _API_ITEM_endExistItemsOne(__FILE__, __LINE__, itemindex)

int API_ITEM_setCharPointer(int a1, int a2);

int API_CHAR_sendItemDataOne(int a1, int a2);

int API_LogItem(int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8);

inline int API_CHAR_getCharaIndex(int charaPtr);

int _API_ITEM_CHECKINDEX(char* file, int line, int itemindex);
#define API_ITEM_CHECKINDEX(itemindex) _API_ITEM_CHECKINDEX(__FILE__, __LINE__, itemindex)



int API_ITEM_getInt(int itemindex, int flg);

int API_ITEM_setInt(int itemindex, int flg, int value);

char* API_ITEM_getChar(int itemindex, int flg);

int API_ITEM_setChar(int itemindex, int flg, char* str);

int API_ITEM_getWorkInt(int itemindex, int flg);

int API_ITEM_setWorkInt(int itemindex, int flg, int value);


int API_DB_getMysqlIndex();

int API_DB_releaseMySqlIndex(int a1);

int API_mysql_query(int mysql, char* str);

char* API_mysql_error(int mysql);

int API_mysql_store_result(int mysql);

int API_mysql_num_rows(int mysql_res);

int API_mysql_num_fields(int mysql_res);

char** API_mysql_fetch_row(int mysql_res);

int API_mysql_free_result(int mysql_res);


int API_mysql_init(int mysql);

int API_mysql_real_connect(int mysql, char* ip, char* user, char* pass, char* db, int port, char* unix_socket, long client_flag);

int API_mysql_close(int mysql);

int API_CHAR_getWorkFlg(char* file, int line, int charaPtr, int flg);

#endif