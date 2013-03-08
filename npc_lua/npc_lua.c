#include "npc_lua.h"
//#include "util.h"
//#include "char.h"
//#include "char_base.h"
//#include "char_data.h"
//#include "anim_tbl.h"
//#include "object.h"
//#include "battle.h"
//#include "npcutil.h"
//#include "item.h"
//#include "readmap.h"
#ifdef _SAF_LUA_MYSQL
//#include "saacproto_cli.h"
#endif
#include "cg_api.h"

#ifdef _JZ_NEWSCRIPT_LUA

/*
typedef enum
{
	LUAITEM_PREOVERFUNC = ITEM_PREOVERFUNC - ITEM_FIRSTFUNCTION,
	LUAITEM_POSTOVERFUNC = ITEM_POSTOVERFUNC - ITEM_FIRSTFUNCTION,
	LUAITEM_WATCHFUNC = ITEM_WATCHFUNC - ITEM_FIRSTFUNCTION,
	LUAITEM_USEFUNC = ITEM_USEFUNC - ITEM_FIRSTFUNCTION,
	LUAITEM_ATTACHFUNC = ITEM_ATTACHFUNC - ITEM_FIRSTFUNCTION,
	LUAITEM_DETACHFUNC = ITEM_DETACHFUNC - ITEM_FIRSTFUNCTION,
	LUAITEM_DROPFUNC = ITEM_DROPFUNC - ITEM_FIRSTFUNCTION,
	LUAITEM_PICKUPFUNC = ITEM_PICKUPFUNC - ITEM_FIRSTFUNCTION,
#ifdef _Item_ReLifeAct
	LUAITEM_DIERELIFEFUNC = ITEM_DIERELIFEFUNC - ITEM_FIRSTFUNCTION,
#endif
}LUAITEM_FUNC;
*/
lua_State *M_Script_Lua = NULL;	//實例句柄
unsigned int M_Create_Num = 0;
char M_OutErrMsg[1024];

CHAR_DATA_EXTEND_STRUCT* CHAR_DATA_EXTEND;

BATTLE_DATA_EXTEND_STRUCT* BATTLE_DATA_EXTEND;

NL_DATA_EXTEND_STRUCT NL_DATA_EXTEND;

extern lua_const M_Lua_RegConstList[];

static luaL_Reg M_RegList[] = {
	{NULL, NULL},
};

static luaL_Reg NL_RegList[] = {
//NL
	{"GetErrorStr", NPC_Lua_NL_GetErrorStr},
	{"CreateNpc", NPC_Lua_NL_CreateNpc},
	{"DelNpc", NPC_Lua_NL_DelNpc},
//NL事件
	{"RegBattleOverEvent", NPC_Lua_NL_RegBattleOverEvent},
	{"RegBattleStartEvent", NPC_Lua_NL_RegBattleStartEvent},
	{"RegLevelUpEvent", NPC_Lua_NL_RegLevelUpEvent},
	{"RegLoginEvent", NPC_Lua_NL_RegLoginEvent},
	{"RegLoginGateEvent", NPC_Lua_NL_RegLoginGateEvent},
	{"RegLogoutEvent", NPC_Lua_NL_RegLogoutEvent},
	{"RegTalkEvent", NPC_Lua_NL_RegTalkEvent},
	{"RegTitleChangedEvent", NPC_Lua_NL_RegTitleChangedEvent},
	{"RegWarpEvent", NPC_Lua_NL_RegWarpEvent},
	{NULL, NULL},
};

static luaL_Reg Char_RegList[] = {
//獲取數據的接口
	{"FindItemId", NPC_Lua_Char_FindItemId},
	{"FindPetEnemyId", NPC_Lua_Char_FindPetEnemyId},

	{"GetData", NPC_Lua_Char_GetData},
	//{"GetItemId", NPC_Lua_Char_GetItemId},
	{"GetPetEnemyId", NPC_Lua_Char_GetPetEnemyId},
	{"GetItemIndex", NPC_Lua_Char_GetItemIndex},
	{"GetPetIndex", NPC_Lua_Char_GetPetIndex},
	{"GetTeamIndex", NPC_Lua_Char_GetTeamIndex},

//任務旗標
	//{"ClrEvtEnd", NPC_Lua_Char_ClrEvtEnd},
	//{"ClrEvtNow", NPC_Lua_Char_ClrEvtNow},
	//{"ClrClrEvt", NPC_Lua_Char_ClrEvt},
	//{"SetEvtEnd", NPC_Lua_Char_SetEvtEnd},
	//{"SetEvtNow", NPC_Lua_Char_SetEvtNow},
	//{"IsEventEnd", NPC_Lua_Char_IsEventEnd},
	//{"IsEventNow", NPC_Lua_Char_IsEventNow},
	{"NowEvent", NPC_Lua_Char_NowEvent},
	{"EndEvent", NPC_Lua_Char_EndEvent},
	
	
//設置數據的接口
	{"SetData", NPC_Lua_Char_SetData},

//事件設置的接口
	{"SetWalkPreEvent", NPC_Lua_Char_SetWalkPreEvent},
	{"SetWalkPostEvent", NPC_Lua_Char_SetWalkPostEvent},
	//{"SetPreOverEvent", NPC_Lua_Char_SetPreOverEvent},
	{"SetPostOverEvent", NPC_Lua_Char_SetPostOverEvent},
	//{"SetWatchEvent", NPC_Lua_Char_SetWatchEvent},
	{"SetLoopEvent", NPC_Lua_Char_SetLoopEvent},
	{"SetTalkedEvent", NPC_Lua_Char_SetTalkedEvent},
	//{"SetOFFEvent", NPC_Lua_Char_SetOFFEvent},
	//{"SetLookedEvent", NPC_Lua_Char_SetLookedEvent},
	//{"SetItemPutEvent", NPC_Lua_Char_SetItemPutEvent},
	{"SetWindowTalkedEvent", NPC_Lua_Char_SetWindowTalkedEvent},
#ifdef _USER_CHARLOOPS
	//{"SetCharLoopsEvent", NPC_Lua_Char_SetCharLoopsEvent},
	//{"SetBattleProPertyEvent", NPC_Lua_Char_SetBattleProPertyEvent},
#endif
#ifdef _SAF_PET_EVO
	//{"ReLoadPetBASE", NPC_Lua_Char_ReLoadPetBASE},
	//{"PetEvolution", NPC_Lua_Char_PetEvolution},
#endif
	{NULL, NULL},
};

static luaL_Reg Item_RegList[] = {
//獲取數據的接口
	{"GetData", NPC_Lua_Item_GetData},
//設置數據的接口
	{"SetData", NPC_Lua_Item_SetData},
//事件設置的接口
	//{"SetPreOverEvent", NPC_Lua_Item_SetPreOverEvent},
	//{"SetPostOverEvent", NPC_Lua_Item_SetPostOverEvent},
	//{"SetWatchEvent", NPC_Lua_Item_SetWatchEvent},
	//{"SetUseEvent", NPC_Lua_Item_SetUseEvent},
	//{"SetAttachEvent", NPC_Lua_Item_SetAttachEvent},
	//{"SetDetachEvent", NPC_Lua_Item_SetDetachEvent},
	//{"SetDropEvent", NPC_Lua_Item_SetDropEvent},
	//{"SetPickUPEvent", NPC_Lua_Item_SetPickUPEvent},
#ifdef _Item_ReLifeAct
	//{"SetDieReLifeEvent", NPC_Lua_Item_SetDieReLifeEvent},
#endif
//更新道具數據的接口
	{"UpItem", NPC_Lua_Item_UpItem},
	{NULL, NULL},
};


static luaL_Reg Obj_RegList[] = {
//獲取數據的接口
	{"GetType", NPC_Lua_Obj_GetType},
	//{"GetCharType", NPC_Lua_Obj_GetCharType},
	{"GetCharIndex", NPC_Lua_Obj_GetCharIndex},
	{"GetX", NPC_Lua_Obj_GetX},
	{"GetY", NPC_Lua_Obj_GetY},
	{"GetFloor", NPC_Lua_Obj_GetFloor},
	{"GetMapId", NPC_Lua_Obj_GetMapId},

//事件設置的接口
	{"SetType", NPC_Lua_Obj_SetType},
	//{"SetCharType", NPC_Lua_Obj_SetCharType},
	{"SetX", NPC_Lua_Obj_SetX},
	{"SetY", NPC_Lua_Obj_SetY},
	{"SetFloor", NPC_Lua_Obj_SetFloor},
	{"SetMapId", NPC_Lua_Obj_SetMapId},
	{NULL, NULL},
};


static luaL_Reg Battle_RegList[] = {
//獲取數據的接口
	{"GetPlayIndex", NPC_Lua_Battle_GetPlayIndex},

//設置數據的接口
	//{"SetNORisk", NPC_Lua_Battle_SetNORisk},
	//{"SetMod", NPC_Lua_Battle_SetMod},
	//{"SetType", NPC_Lua_Battle_SetType},

//事件設置的接口
	{"SetWinEvent", NPC_Lua_Battle_SetWinEvent},
	{NULL, NULL},
};

static luaL_Reg SQL_RegList[] = {
	{"Run", NPC_Lua_SQL_Run},
	{NULL, NULL},
};


static luaL_Reg NLG_RegList[] = {
//功能接口
#ifdef _SAF_LUAPLUS0712
	//{"UpItem", NPC_Lua_NLG_UpItem},
	//{"GiveItemOne", NPC_Lua_NLG_GiveItemOne},
#endif
#ifdef _SAF_LUAFIREWORK
	//{"FireWork", NPC_Lua_NLG_FireWork},
#endif
	{"CheckInFront", NPC_Lua_NLG_CheckInFront},
	//{"CheckObj", NPC_Lua_NLG_CheckObj},
	{"CharLook", NPC_Lua_NLG_CharLook},
	{"CreateBattle", NPC_Lua_NLG_CreateBattle},
	{"CreateBattlePvP", NPC_Lua_NLG_CreateBattlePvP},
#ifdef _SAF_NEWLUA
	//{"DelItemByIndex", NPC_Lua_NLG_DelItemByIndex},
#endif
	{"DelPet", NPC_Lua_NLG_DelPet},
	{"DelItem", NPC_Lua_NLG_DelItem},
	//{"DischargeParty", NPC_Lua_NLG_DischargeParty},
	
	{"GivePet", NPC_Lua_NLG_GivePet},
	{"GiveItem", NPC_Lua_NLG_GiveItem},
	{"GetOnLinePlayer", NPC_Lua_Char_GetOnLinePlayer},

	{"ShowWindowTalked", NPC_Lua_NLG_ShowWindowTalked},
	{"SetAction", NPC_Lua_NLG_SetAction},

	{"TalkToCli", NPC_Lua_NLG_TalkToCli},
	{"TalkToFloor", NPC_Lua_NLG_TalkToFloor},

	{"UpChar", NPC_Lua_NLG_UpChar},
	//{"UpStateBySecond", NPC_Lua_NLG_UpStateBySecond}, 
	//{"UpStateByThird", NPC_Lua_NLG_UpStateByThird},
	{"UpdateParty", NPC_Lua_NLG_Update_Party},

	{"Warp", NPC_Lua_NLG_Warp},
	{"WalkMove", NPC_Lua_NLG_WalkMove},
	{"WatchEntry", NPC_Lua_NLG_WatchEntry},

	{NULL, NULL},
};

static luaL_Reg Pet_RegList[] = {
	{"GetArtRank", NPC_Lua_Pet_GetArtRank},
	{"SetArtRank", NPC_Lua_Pet_SetArtRank},
	{"UpPet", NPC_Lua_Pet_UpPet},
	{"FullArtRank", NPC_Lua_Pet_FullArtRank},
	{NULL, NULL},
};

static luaL_Reg M_NTIntRegList[] = {
	{"AINew", NPC_Lua_NTInt_New},
	{"AIGet", NPC_Lua_NTInt_Get},
	{"AISet", NPC_Lua_NTInt_Set},
	{"AILen", NPC_Lua_NTInt_Len},
	{NULL, NULL},
};

static SCRIPTREGLIB M_NTInt_Lib[] = {
	{"NTInt", &M_NTIntRegList},
	{NULL, NULL},
};

static SCRIPTREGLIB M_RegLib[] = {
	{"NL", &NL_RegList},
	{"NLG", &NLG_RegList},
	{"Char", &Char_RegList},
	{"Item", &Item_RegList},
	{"Obj", &Obj_RegList},
	{"Battle", &Battle_RegList},
	{"SQL",&SQL_RegList},
	{"Pet",&Pet_RegList},
	{NULL, NULL},
};

static SCRIPTREGCLASS M_RegClass[] = {
	{NULL, NULL, NULL},
};

static char *Array_INL[] = {
	"__index", "__newindex", "__len", NULL
};

static char *Array_GSL[] = {
	"AIGet", "AISet", "AILen", NULL
};

static SCRIPTREGARRAY M_RegArray[] = {
	{
		"Array.NTInt",
		&Array_INL[0],
		&Array_GSL[0],
		&M_NTInt_Lib,
	},
	{
		NULL,
		{NULL},
		{NULL},
		NULL,
	},
};



int NPC_Lua_Init(const char *_DoFile)
{
	int TM_Ret = 0;

	M_Script_Lua = lua_open();
	if (M_Script_Lua == NULL) {
    print("LUAInit: cannot create state: not enough memory\n");
		return -1;
	}
	M_OutErrMsg[0] = '\0';

  //停止垃圾收集
  lua_gc(M_Script_Lua, LUA_GCSTOP, 0);

  luaL_openlibs(M_Script_Lua);

  lua_gc(M_Script_Lua, LUA_GCRESTART, 0);
	
	//設置內置常量
	lua_setconstlist(M_Script_Lua, M_Lua_RegConstList);

	//設置Lua引擎擴展
	print("LUA RegFuncNum:%d\n", NPC_Lua_RegCallEx(M_Script_Lua, M_RegList));
	print("LUA RegLibNum:%d\n", NPC_Lua_RegLibEx(M_Script_Lua, M_RegLib));
	print("LUA RegClassNum:%d\n", NPC_Lua_RegClassEx(M_Script_Lua, M_RegClass));
	print("LUA RegArrayNum:%d\n", NPC_Lua_RegArrayEx(M_Script_Lua, M_RegArray));
	
	//擴展 char data, lua function table
	CHAR_DATA_EXTEND = malloc(sizeof(CHAR_DATA_EXTEND_STRUCT)*(*(int*)0x10D0BEA0));
	if(!malloc){
		print("Malloc CHAR_DATA_EXTEND Err\n");
		return M_Create_Num;
	}
	memset(CHAR_DATA_EXTEND, 0, sizeof(CHAR_DATA_EXTEND_STRUCT)*(*(int*)0x10D0BEA0));
	
	//擴展 battle lua function table
	BATTLE_DATA_EXTEND = malloc(sizeof(BATTLE_DATA_EXTEND_STRUCT)*(*(int*)0x8C89CA4));
	if(!malloc){
		print("Malloc BATTLE_DATA_EXTEND Err\n");
		return M_Create_Num;
	}
	memset(BATTLE_DATA_EXTEND, 0, sizeof(BATTLE_DATA_EXTEND_STRUCT)*(*(int*)0x8C89CA4));
	
	//因應擴展人物資料, 擴展 CHAR_cleanUpChar
	my_mprotect(0x08066B24);
	*(int*)0x08066B24 = (int)my_CHAR_cleanUpChar_memset -4 -0x08066B24;
	
	//擴展 NL庫
	memset(&NL_DATA_EXTEND, 0, sizeof(NL_DATA_EXTEND_STRUCT));

	print("Lua Npc Sript引擎初始化完成\n");
	//加載腳本文件
	TM_Ret = luaL_loadfile(M_Script_Lua, _DoFile);
	if(TM_Ret != 0)
	{
		//失敗-輸出錯誤信息
		print("LoadFile Err :%d(%s)\n", TM_Ret, lua_tostring(M_Script_Lua, -1));
		//出棧
		lua_pop(M_Script_Lua, 1);
		return M_Create_Num;
	}


	
	//執行腳本文件
	TM_Ret = lua_pcall(M_Script_Lua, 0, 0, 0);
	if(TM_Ret != 0)
	{
		//失敗-輸出錯誤信息
		print("Do Lua Err :%d(%s)\n", TM_Ret, lua_tostring(M_Script_Lua, -1));
		//出棧
		lua_pop(M_Script_Lua, 1);
		return M_Create_Num;
	}
	return M_Create_Num;

}


int NPC_Lua_Close(void)
{
	if(M_Script_Lua != NULL)
	{
		lua_close(M_Script_Lua);
		M_Script_Lua = NULL;
	}
	return 0;
}

int NPC_Lua_DoFile(const char *_DoFile)
{
	if(_DoFile == NULL)
	{
		return 0;
	}
	if(M_Script_Lua == NULL)
	{
		print("M_Script_Lua Null!");
		return 1;
	}
	int TM_Ret = luaL_loadfile(M_Script_Lua, _DoFile);
	if(TM_Ret != 0)
	{
		//失敗-輸出錯誤信息
		print("NPC_Lua_DoFile LoadFile Err :%d(%s)\n", TM_Ret, lua_tostring(M_Script_Lua, -1));
		return 1;
	}
	
	TM_Ret = lua_pcall(M_Script_Lua, 0, LUA_MULTRET, 0);
	if(TM_Ret != 0)
	{
		//失敗-輸出錯誤信息
		print("NPC_Lua_DoFile Do Lua Err :%d(%s)\n", TM_Ret, lua_tostring(M_Script_Lua, -1));
		return 1;
	}
	return 0;
}

const char *NPC_Lua_popstring(int _ArgNum)
{
	return lua_tostring(M_Script_Lua, _ArgNum);
}

const char *NPC_Lua_CallFunc(const char *_FuncName, char *_RetBuff, size_t _n)
{
	const char *TM_Ret = NULL;
	if(M_Script_Lua == NULL)
	{
		strcpy_s(_RetBuff, _n, "M_Script_Lua Null!");
		return _RetBuff;
	}
	lua_getglobal(M_Script_Lua, _FuncName);

	if(lua_type(M_Script_Lua, -1) != LUA_TFUNCTION)
	{
		strcpy_s(_RetBuff, _n, "無法執行指定函數。");
		return _RetBuff;
	}
	lua_pcall(M_Script_Lua, 0, 1, 0);
	strcpy_s(_RetBuff, _n, lua_tostring(M_Script_Lua, -1));
	lua_pop(M_Script_Lua, 1);
	return _RetBuff;
}

BOOL NPC_Lua_InitCallBack(int _meptr)
{
	if(M_Script_Lua == NULL)
	{
		print("M_Script_Lua Null!");
		return FALSE;
	}
	int TM_index = *(int*)(_meptr+4);
	if(TM_index == NULL)
	{
		return FALSE;
	}
	int TM_Ret = 0;
	BOOL TM_FuncRet = FALSE;

	int _meIndex = API_CHAR_getCharaIndex(_meptr);
	lua_getglobal(M_Script_Lua, (const char *)CHAR_DATA_EXTEND[TM_index].functable[CHAR_INITFUNC].string);
	lua_pushinteger(M_Script_Lua, (lua_Integer)_meIndex);

	TM_Ret = lua_pcall(M_Script_Lua, 1, 1, 0);
	if(TM_Ret != 0)
	{
		//失敗-輸出錯誤信息
		print("NPC_Lua_InitCallBack Lua Err :%d(%s)\n", TM_Ret, lua_tostring(M_Script_Lua, -1));
		//出棧
		lua_pop(M_Script_Lua, 1);
		return FALSE;
	}
	TM_FuncRet = (BOOL)lua_toboolean(M_Script_Lua, -1);
	lua_pop(M_Script_Lua, 1);
	return TM_FuncRet;
}

BOOL NPC_Lua_WalkPreCallBack(int _meptr, int *_dir, int *_mode, int _dirFix)
{
	if(M_Script_Lua == NULL)
	{
		print("M_Script_Lua Null!");
		return FALSE;
	}
	int TM_index = *(int*)(_meptr+4);
	if(TM_index == NULL)
	{
		return FALSE;
	}
	int TM_Ret = 0;
	BOOL TM_FuncRet = FALSE;
	
	int _meIndex = API_CHAR_getCharaIndex(_meptr);
	lua_getglobal(M_Script_Lua, (const char *)CHAR_DATA_EXTEND[TM_index].functable[CHAR_WALKPREFUNC].string);
	lua_pushinteger(M_Script_Lua, (lua_Integer)_meIndex);
	lua_pushinteger(M_Script_Lua, (lua_Integer)*_dir);
	lua_pushinteger(M_Script_Lua, (lua_Integer)*_mode);
	lua_pushinteger(M_Script_Lua, (lua_Integer)_dirFix);
	

	TM_Ret = lua_pcall(M_Script_Lua, 4, 3, 0);
	if(TM_Ret != 0)
	{
		//失敗-輸出錯誤信息
		print("NPC_Lua_WalkPreCallBack Lua Err :%d(%s)\n", TM_Ret, lua_tostring(M_Script_Lua, -1));
		//出棧
		lua_pop(M_Script_Lua, 1);
		return FALSE;
	}

	TM_FuncRet = (BOOL)lua_toboolean(M_Script_Lua, -1);
	*_dir = (int)lua_tointeger(M_Script_Lua, -2);
	*_mode = (int)lua_tointeger(M_Script_Lua, -3);
	lua_pop(M_Script_Lua, 3);

	return TM_FuncRet;
}

void NPC_Lua_WalkPostCallBack(int _meptr)
{
	if(M_Script_Lua == NULL)
	{
		print("M_Script_Lua Null!");
		return ;
	}
	int TM_index = *(int*)(_meptr+4);
	if(TM_index == NULL)
	{
		return FALSE;
	}
	int TM_Ret = 0;

	int _meIndex = API_CHAR_getCharaIndex(_meptr);
	lua_getglobal(M_Script_Lua, (const char *)CHAR_DATA_EXTEND[TM_index].functable[CHAR_WALKPOSTFUNC].string);
	lua_pushinteger(M_Script_Lua, (lua_Integer)_meIndex);
	
	TM_Ret = lua_pcall(M_Script_Lua, 1, 0, 0);
	if(TM_Ret != 0)
	{
		//失敗-輸出錯誤信息
		print("NPC_Lua_WalkPostCallBack Lua Err :%d(%s)\n", TM_Ret, lua_tostring(M_Script_Lua, -1));
		//出棧
		lua_pop(M_Script_Lua, 1);
		return ;
	}

	return ;
}

/*
void NPC_Lua_PreOverCallBack(int _meindex, int _desindex)
{
	if(M_Script_Lua == NULL)
	{
		print("M_Script_Lua Null!");
		return ;
	}
	Char *TM_char = CHAR_getCharPointer(_meindex);
	if(TM_char == NULL)
	{
		return ;
	}
	int TM_Ret = 0;

	lua_getglobal(M_Script_Lua, (const char *)TM_char->lua_charfunctable[CHAR_PREOVERFUNC].string);
	lua_pushinteger(M_Script_Lua, (lua_Integer)_meindex);
	lua_pushinteger(M_Script_Lua, (lua_Integer)_desindex);

	TM_Ret = lua_pcall(M_Script_Lua, 2, 0, 0);
	if(TM_Ret != 0)
	{
		//失敗-輸出錯誤信息
		print("NPC_Lua_PreOverCallBack Lua Err :%d(%s)\n", TM_Ret, lua_tostring(M_Script_Lua, -1));
		//出棧
		lua_pop(M_Script_Lua, 1);
		return ;
	}

	return ;
}
*/

void NPC_Lua_PostOverCallBack(int _mePtr, int _desPtr)
{
	if(M_Script_Lua == NULL)
	{
		print("M_Script_Lua Null!");
		return ;
	}
	int TM_index = *(int*)(_mePtr+4);
	if(TM_index == NULL)
	{
		return FALSE;
	}
	int TM_Ret = 0;

	int _meIndex = API_CHAR_getCharaIndex(_mePtr);
	int _desIndex = API_CHAR_getCharaIndex(_desPtr);
	lua_getglobal(M_Script_Lua, (const char *)CHAR_DATA_EXTEND[TM_index].functable[CHAR_POSTOVERFUNC].string);
	lua_pushinteger(M_Script_Lua, (lua_Integer)_meIndex);
	lua_pushinteger(M_Script_Lua, (lua_Integer)_desIndex);
	
	TM_Ret = lua_pcall(M_Script_Lua, 2, 0, 0);
	if(TM_Ret != 0)
	{
		//失敗-輸出錯誤信息
		print("NPC_Lua_PostOverCallBack Lua Err :%d(%s)\n", TM_Ret, lua_tostring(M_Script_Lua, -1));
		//出棧
		lua_pop(M_Script_Lua, 1);
		return ;
	}

	return ;
}

/*
void NPC_Lua_WatchCallBack(int _meindex, int _objindex, int _chac, int _x, int _y, int _dir, int *_watchopt, int _watchoptlen)
{
	if(M_Script_Lua == NULL)
	{
		print("M_Script_Lua Null!");
		return ;
	}
	Char *TM_char = CHAR_getCharPointer(_meindex);

	if(TM_char == NULL)
	{
		return ;
	}

	int TM_Ret = 0;
	PARRAY_NTINT TM_Point = NULL;

	lua_getglobal(M_Script_Lua, (const char *)TM_char->lua_charfunctable[CHAR_WATCHFUNC].string);
	lua_pushinteger(M_Script_Lua, (lua_Integer)_meindex);
	lua_pushinteger(M_Script_Lua, (lua_Integer)_objindex);
	lua_pushinteger(M_Script_Lua, (lua_Integer)_chac);
	lua_pushinteger(M_Script_Lua, (lua_Integer)_x);
	lua_pushinteger(M_Script_Lua, (lua_Integer)_y);
	lua_pushinteger(M_Script_Lua, (lua_Integer)_dir);
	if(_watchopt == NULL || _watchoptlen <= 0)
	{
		lua_pushnil(M_Script_Lua);
	}else
	{
		//調用 NTInt 實例化函數
		lua_getglobal(M_Script_Lua, "AINew");
		lua_pushinteger(M_Script_Lua, _watchoptlen);
		TM_Ret = lua_pcall(M_Script_Lua, 1, 1, 0);
	
		if(TM_Ret != 0)
		{
			print("NPC_Lua_WatchCallBack Call AINew Lua Err :%d(%s)\n", TM_Ret, lua_tostring(M_Script_Lua, -1));
			lua_pop(M_Script_Lua, 1);
			lua_pushnil(M_Script_Lua);
		}else
		{
			if( lua_type(M_Script_Lua, -1) == LUA_TUSERDATA )
			{
				PARRAY_NTINT TM_Point = lua_touserdata(M_Script_Lua, -1);
				if(TM_Point != NULL)
				{
					int i = 0;
					for(i = 0; i < _watchoptlen; i++)
					{
						TM_Point->Num[i] = _watchopt[i];
					}
				}
			}else
			{
				lua_pop(M_Script_Lua, 1);
				lua_pushnil(M_Script_Lua);
			}
		}
	}

	//調用用戶設置的回調函數
	TM_Ret = lua_pcall(M_Script_Lua, 7, 0, 0);
	if(TM_Ret != 0)
	{
		//失敗-輸出錯誤信息
		print("NPC_Lua_WatchCallBack Lua Err :%d(%s)\n", TM_Ret, lua_tostring(M_Script_Lua, -1));
		//出棧
		lua_pop(M_Script_Lua, 1);
		return ;
	}
	return ;
}
*/

int NPC_Lua_LoopCallBack(int _meptr)
{
	if(M_Script_Lua == NULL)
	{
		print("M_Script_Lua Null!");
		return FALSE;
	}
	int TM_index = *(int*)(_meptr+4);
	if(TM_index == NULL)
	{
		return FALSE;
	}
	int TM_Ret = 0;
	int TM_FuncRet = 0;

	int _meIndex = API_CHAR_getCharaIndex(_meptr);
	lua_getglobal(M_Script_Lua, (const char *)CHAR_DATA_EXTEND[TM_index].functable[CHAR_LOOPFUNC].string);
	lua_pushinteger(M_Script_Lua, (lua_Integer)_meIndex);
	
	TM_Ret = lua_pcall(M_Script_Lua, 1, 1, 0);
	if(TM_Ret != 0)
	{
		//失敗-輸出錯誤信息
		print("NPC_Lua_LoopCallBack Lua Err :%d(%s)\n", TM_Ret, lua_tostring(M_Script_Lua, -1));
		//出棧
		lua_pop(M_Script_Lua, 1);
		return FALSE;
	}
	TM_FuncRet = (int)lua_tointeger(M_Script_Lua, -1);
	lua_pop(M_Script_Lua, 1);
	return TM_FuncRet;
}

void NPC_Lua_TalkedCallBack(int _meptr, int _toptr)
{
	int TM_Ret = 0;
	if(M_Script_Lua == NULL)
	{
		print("M_Script_Lua Null!");
		return ;
	}
	int TM_index = *(int*)(_meptr+4);
	if(TM_index == NULL)
	{
		return FALSE;
	}

	int _meIndex = API_CHAR_getCharaIndex(_meptr);
	int _toIndex = API_CHAR_getCharaIndex(_toptr);
	lua_getglobal(M_Script_Lua, (const char *)CHAR_DATA_EXTEND[TM_index].functable[CHAR_TALKEDFUNC].string);
	lua_pushinteger(M_Script_Lua, (lua_Integer)_meIndex);
	lua_pushinteger(M_Script_Lua, (lua_Integer)_toIndex);

	TM_Ret = lua_pcall(M_Script_Lua, 2, 0, 0);
	if(TM_Ret != 0)
	{
		//失敗-輸出錯誤信息
		print("NPC_Lua_TalkedCallBack Lua Err :%d(%s)\n", TM_Ret, lua_tostring(M_Script_Lua, -1));
		//出棧
		lua_pop(M_Script_Lua, 1);
		return ;
	}

	return ;
}
/*
void NPC_Lua_OFFCallBack(int _meindex, int _desindex)
{
	if(M_Script_Lua == NULL)
	{
		print("M_Script_Lua Null!");
		return ;
	}
	Char *TM_char = CHAR_getCharPointer(_meindex);
	if(TM_char == NULL)
	{
		return ;
	}
	int TM_Ret = 0;

	lua_getglobal(M_Script_Lua, (const char *)TM_char->lua_charfunctable[CHAR_OFFFUNC].string);
	lua_pushinteger(M_Script_Lua, (lua_Integer)_meindex);
	lua_pushinteger(M_Script_Lua, (lua_Integer)_desindex);
	
	TM_Ret = lua_pcall(M_Script_Lua, 2, 0, 0);
	if(TM_Ret != 0)
	{
		//失敗-輸出錯誤信息
		print("NPC_Lua_OFFCallBack Lua Err :%d(%s)\n", TM_Ret, lua_tostring(M_Script_Lua, -1));
		//出棧
		lua_pop(M_Script_Lua, 1);
		return ;
	}

	return ;
}

void NPC_Lua_LookedCallBack(int _meindex, int _desindex)
{
	if(M_Script_Lua == NULL)
	{
		print("M_Script_Lua Null!");
		return ;
	}
	Char *TM_char = CHAR_getCharPointer(_meindex);
	if(TM_char == NULL)
	{
		return ;
	}
	int TM_Ret = 0;

	lua_getglobal(M_Script_Lua, (const char *)TM_char->lua_charfunctable[CHAR_LOOKEDFUNC].string);
	lua_pushinteger(M_Script_Lua, (lua_Integer)_meindex);
	lua_pushinteger(M_Script_Lua, (lua_Integer)_desindex);
	
	TM_Ret = lua_pcall(M_Script_Lua, 2, 0, 0);
	if(TM_Ret != 0)
	{
		//失敗-輸出錯誤信息
		print("NPC_Lua_LookedCallBack Lua Err :%d(%s)\n", TM_Ret, lua_tostring(M_Script_Lua, -1));
		//出棧
		lua_pop(M_Script_Lua, 1);
		return ;
	}

	return ;
}

BOOL NPC_Lua_ItemPutCallBack(int _meindex, int _itemindex)
{
	if(M_Script_Lua == NULL)
	{
		print("M_Script_Lua Null!");
		return FALSE;
	}
	Char *TM_char = CHAR_getCharPointer(_meindex);
	if(TM_char == NULL)
	{
		return FALSE;
	}
	int TM_Ret = 0;
	BOOL TM_FuncRet = FALSE;

	lua_getglobal(M_Script_Lua, (const char *)TM_char->lua_charfunctable[CHAR_ITEMPUTFUNC].string);
	lua_pushinteger(M_Script_Lua, (lua_Integer)_meindex);
	lua_pushinteger(M_Script_Lua, (lua_Integer)_itemindex);
	
	TM_Ret = lua_pcall(M_Script_Lua, 2, 1, 0);
	if(TM_Ret != 0)
	{
		//失敗-輸出錯誤信息
		print("NPC_Lua_ItemPutCallBack Lua Err :%d(%s)\n", TM_Ret, lua_tostring(M_Script_Lua, -1));
		//出棧
		lua_pop(M_Script_Lua, 1);
		return FALSE;
	}
	TM_FuncRet = (BOOL)lua_toboolean(M_Script_Lua, -1);
	lua_pop(M_Script_Lua, 1);
	return TM_FuncRet;
}
*/

void NPC_Lua_WindowTalkedCallBack(int _meptr, int _talkptr, int _seqno, int _select,const char *_data)
{
	if(M_Script_Lua == NULL)
	{
		print("M_Script_Lua Null!");
		return ;
	}
	
	int TM_index = *(int*)(_meptr+4);
	if(TM_index == NULL)
	{
		return;
	}
	

	int TM_Ret = 0;

	int _meIndex = API_CHAR_getCharaIndex(_meptr);
	int _talkIndex = API_CHAR_getCharaIndex(_talkptr);
	lua_getglobal(M_Script_Lua, (const char *)CHAR_DATA_EXTEND[TM_index].functable[CHAR_WINDOWTALKEDFUNC].string);
	lua_pushinteger(M_Script_Lua, (lua_Integer)_meIndex);
	lua_pushinteger(M_Script_Lua, (lua_Integer)_talkIndex);
	lua_pushinteger(M_Script_Lua, (lua_Integer)_seqno);
	lua_pushinteger(M_Script_Lua, (lua_Integer)_select);
	lua_pushstring(M_Script_Lua, _data);

	TM_Ret = lua_pcall(M_Script_Lua, 5, 0, 0);
	if(TM_Ret != 0)
	{
		//失敗-輸出錯誤信息
		print("NPC_Lua_WindowTalkedCallBack Lua Err :%d(%s)\n", TM_Ret, lua_tostring(M_Script_Lua, -1));
		//出棧
		lua_pop(M_Script_Lua, 1);
		return ;
	}

	return ;
}

/*

#ifdef _USER_CHARLOOPS
int NPC_Lua_CharLoopsCallBack( int _meindex)
{
	if(M_Script_Lua == NULL)
	{
		print("M_Script_Lua Null!");
		return 0;
	}
	Char *TM_char = CHAR_getCharPointer(_meindex);
	if(TM_char == NULL)
	{
		return 0;
	}
	int TM_Ret = 0;
	
	lua_getglobal(M_Script_Lua, (const char *)TM_char->lua_charfunctable[CHAR_LOOPFUNCTEMP1].string);
	lua_pushinteger(M_Script_Lua, (lua_Integer)_meindex);

	TM_Ret = lua_pcall(M_Script_Lua, 1, 1, 0);
	if(TM_Ret != 0)
	{
		//失敗-輸出錯誤信息
		print("NPC_Lua_CharLoopsCallBack Lua Err :%d(%s)\n", TM_Ret, lua_tostring(M_Script_Lua, -1));
		//出棧
		lua_pop(M_Script_Lua, 1);
		return 0;
	}
	TM_Ret = (int)lua_tointeger(M_Script_Lua, -1);
	lua_pop(M_Script_Lua, 1);
	return TM_Ret;
}

int NPC_Lua_BattleProPertyCallBack(int _attackindex, int _defindex, int *_damage, int *_powarray, int _arraynum)
{
	if(M_Script_Lua == NULL)
	{
		print("M_Script_Lua Null!");
		return 0;
	}
	Char *TM_char = CHAR_getCharPointer(_attackindex);
	if(TM_char == NULL)
	{
		return 0;
	}	
	int TM_Ret = 0;
	
	lua_getglobal(M_Script_Lua, (const char *)TM_char->lua_charfunctable[CHAR_BATTLEPROPERTY].string);
	lua_pushinteger(M_Script_Lua, (lua_Integer)_attackindex);
	lua_pushinteger(M_Script_Lua, (lua_Integer)_defindex);
	if(_damage == NULL)
	{
		lua_pushnil(M_Script_Lua);
	}else
	{
		lua_pushinteger(M_Script_Lua, (lua_Integer)*_damage);
	}
	if(_powarray == NULL || _arraynum <= 0)
	{
		lua_pushnil(M_Script_Lua);
	}else
	{
		//調用 NTInt 實例化函數
		lua_getglobal(M_Script_Lua, "AINew");
		lua_pushinteger(M_Script_Lua, _arraynum);
		TM_Ret = lua_pcall(M_Script_Lua, 1, 1, 0);
	
		if(TM_Ret != 0)
		{
			print("NPC_Lua_BattleProPertyCallBack Call AINew Lua Err :%d(%s)\n", TM_Ret, lua_tostring(M_Script_Lua, -1));
			lua_pop(M_Script_Lua, 1);
			lua_pushnil(M_Script_Lua);
		}else
		{
			if( lua_type(M_Script_Lua, -1) == LUA_TUSERDATA )
			{
				PARRAY_NTINT TM_Point = lua_touserdata(M_Script_Lua, -1);
				if(TM_Point != NULL)
				{
					int i = 0;
					for(i = 0; i < _arraynum; i++)
					{
						TM_Point->Num[i] = _powarray[i];
					}
				}
			}else
			{
				lua_pop(M_Script_Lua, 1);
				lua_pushnil(M_Script_Lua);
			}
		}
	}

	TM_Ret = lua_pcall(M_Script_Lua, 4, 1, 0);
	if(TM_Ret != 0)
	{
		//失敗-輸出錯誤信息
		print("NPC_Lua_BattleProPertyCallBack Lua Err :%d(%s)\n", TM_Ret, lua_tostring(M_Script_Lua, -1));
		//出棧
		lua_pop(M_Script_Lua, 1);
		return 0;
	}
	TM_Ret = (int)lua_tointeger(M_Script_Lua, -1);
	if(_damage != NULL)
	{
		*_damage = TM_Ret;
	}
	lua_pop(M_Script_Lua, 1);
	return TM_Ret;
}
#endif

void NPC_Lua_ItemPerOverCallBack(int _itemindex, int _playindex)
{
	if(M_Script_Lua == NULL)
	{
		print("M_Script_Lua Null!");
		return ;
	}
	ITEM_Item *TM_Item = ITEM_getItemPointer(_itemindex);
	if(TM_Item == NULL)
	{
		return ;
	}
	int TM_Ret = 0;

	lua_getglobal(M_Script_Lua, (const char *)TM_Item->lua_charfunctable[LUAITEM_PREOVERFUNC].string);
	lua_pushinteger(M_Script_Lua, (lua_Integer)_itemindex);
	lua_pushinteger(M_Script_Lua, (lua_Integer)_playindex);

	TM_Ret = lua_pcall(M_Script_Lua, 2, 0, 0);
	if(TM_Ret != 0)
	{
		//失敗-輸出錯誤信息
		print("NPC_Lua_ItemPerOverCallBack Lua Err :%d(%s)\n", TM_Ret, lua_tostring(M_Script_Lua, -1));
		//出棧
		lua_pop(M_Script_Lua, 1);
		return ;
	}

	return ;
}

void NPC_Lua_ItemPostOverCallBack(int _itemindex, int _playindex)
{
	if(M_Script_Lua == NULL)
	{
		print("M_Script_Lua Null!");
		return ;
	}
	ITEM_Item *TM_Item = ITEM_getItemPointer(_itemindex);
	if(TM_Item == NULL)
	{
		return ;
	}
	int TM_Ret = 0;

	lua_getglobal(M_Script_Lua, (const char *)TM_Item->lua_charfunctable[LUAITEM_POSTOVERFUNC].string);
	lua_pushinteger(M_Script_Lua, (lua_Integer)_itemindex);
	lua_pushinteger(M_Script_Lua, (lua_Integer)_playindex);

	TM_Ret = lua_pcall(M_Script_Lua, 2, 0, 0);
	if(TM_Ret != 0)
	{
		//失敗-輸出錯誤信息
		print("NPC_Lua_ItemPostOverCallBack Lua Err :%d(%s)\n", TM_Ret, lua_tostring(M_Script_Lua, -1));
		//出棧
		lua_pop(M_Script_Lua, 1);
		return ;
	}

	return ;
}

void NPC_Lua_ItemWatchCallBack(int _meindex, int _objindex, int _chac, int _x, int _y, int _dir, int *_watchopt, int _watchoptlen)
{
	if(M_Script_Lua == NULL)
	{
		print("M_Script_Lua Null!");
		return ;
	}
	ITEM_Item *TM_Item = ITEM_getItemPointer(_meindex);

	if(TM_Item == NULL)
	{
		return ;
	}

	int TM_Ret = 0;
	PARRAY_NTINT TM_Point = NULL;

	lua_getglobal(M_Script_Lua, (const char *)(TM_Item->lua_charfunctable[LUAITEM_WATCHFUNC].string));
	lua_pushinteger(M_Script_Lua, (lua_Integer)_meindex);
	lua_pushinteger(M_Script_Lua, (lua_Integer)_objindex);
	lua_pushinteger(M_Script_Lua, (lua_Integer)_chac);
	lua_pushinteger(M_Script_Lua, (lua_Integer)_x);
	lua_pushinteger(M_Script_Lua, (lua_Integer)_y);
	lua_pushinteger(M_Script_Lua, (lua_Integer)_dir);
	if(_watchopt == NULL || _watchoptlen <= 0)
	{
		lua_pushnil(M_Script_Lua);
	}else
	{
		//調用 NTInt 實例化函數
		lua_getglobal(M_Script_Lua, "AINew");
		lua_pushinteger(M_Script_Lua, _watchoptlen);
		TM_Ret = lua_pcall(M_Script_Lua, 1, 1, 0);
	
		if(TM_Ret != 0)
		{
			print("NPC_Lua_ItemWatchCallBack Call AINew Lua Err :%d(%s)\n", TM_Ret, lua_tostring(M_Script_Lua, -1));
			lua_pop(M_Script_Lua, 1);
			lua_pushnil(M_Script_Lua);
		}else
		{
			if( lua_type(M_Script_Lua, -1) == LUA_TUSERDATA )
			{
				PARRAY_NTINT TM_Point = lua_touserdata(M_Script_Lua, -1);
				if(TM_Point != NULL)
				{
					int i = 0;
					for(i = 0; i < _watchoptlen; i++)
					{
						TM_Point->Num[i] = _watchopt[i];
					}
				}
			}else
			{
				lua_pop(M_Script_Lua, 1);
				lua_pushnil(M_Script_Lua);
			}
		}
	}

	//調用用戶設置的回調函數
	TM_Ret = lua_pcall(M_Script_Lua, 7, 0, 0);
	if(TM_Ret != 0)
	{
		//失敗-輸出錯誤信息
		print("NPC_Lua_ItemWatchCallBack Lua Err :%d(%s)\n", TM_Ret, lua_tostring(M_Script_Lua, -1));
		//出棧
		lua_pop(M_Script_Lua, 1);
		return ;
	}
	return ;
}
#ifdef _SAF_LUA_MYSQL
void NPC_Lua_SQLPushCallBack(int _PlayerIndex, int _NpcIndex, char* _SQLResult)
{
	if(M_Script_Lua == NULL)
	{
		print("M_Script_Lua Null!");
		return ;
	}
	
	if(NPC_Lua_DoFile("./data/npc/lua/sqlprocess.lua") != 0)
	{
		CHAR_talkToCli(_PlayerIndex, -1, "SQL處理腳本加載失敗，原因:", CHAR_COLORRED);
		CHAR_talkToCli(_PlayerIndex, -1, NPC_Lua_popstring(-1), CHAR_COLORRED);
	}else
	{
		int TM_Ret = 0;
		char funcname[12];
		memset(funcname,0,sizeof(funcname));
		sprintf(funcname,"SQL_Process");
		lua_getglobal(M_Script_Lua, (const char *)funcname);
		lua_pushinteger(M_Script_Lua, (lua_Integer)_PlayerIndex);
		lua_pushinteger(M_Script_Lua, (lua_Integer)_NpcIndex);
		lua_pushstring(M_Script_Lua, _SQLResult);
		
		TM_Ret = lua_pcall(M_Script_Lua, 3, 0, 0);
		if(TM_Ret != 0)
		{
			//失敗-輸出錯誤信息
			print("NPC_Lua_SQLPushCallBack Lua Err :%d(%s)\n", TM_Ret, lua_tostring(M_Script_Lua, -1));
			//出棧
			lua_pop(M_Script_Lua, 1);
			return ;
		}
	}
}
#endif
void NPC_Lua_ItemUseCallBack(int _playindex, int _to_charindex, int _haveitemindex)
{
	if(M_Script_Lua == NULL)
	{
		print("M_Script_Lua Null!");
		return ;
	}
	int TM_ItemIndex = CHAR_getItemIndex( _playindex, _haveitemindex);
	ITEM_Item *TM_Item = ITEM_getItemPointer(TM_ItemIndex);
	if(TM_Item == NULL)
	{
		return ;
	}
	int TM_Ret = 0;

	lua_getglobal(M_Script_Lua, (const char *)TM_Item->lua_charfunctable[LUAITEM_USEFUNC].string);
	lua_pushinteger(M_Script_Lua, (lua_Integer)_playindex);
	lua_pushinteger(M_Script_Lua, (lua_Integer)_to_charindex);
	lua_pushinteger(M_Script_Lua, (lua_Integer)_haveitemindex);

	TM_Ret = lua_pcall(M_Script_Lua, 3, 0, 0);
	if(TM_Ret != 0)
	{
		//失敗-輸出錯誤信息
		print("NPC_Lua_ItemUseCallBack Lua Err :%d(%s)\n", TM_Ret, lua_tostring(M_Script_Lua, -1));
		//出棧
		lua_pop(M_Script_Lua, 1);
		return ;
	}

	return ;
}

void NPC_Lua_ItemAttachCallBack(int _playindex, int _itemindex)
{
	if(M_Script_Lua == NULL)
	{
		print("M_Script_Lua Null!");
		return ;
	}
	ITEM_Item *TM_Item = ITEM_getItemPointer(_itemindex);
	if(TM_Item == NULL)
	{
		return ;
	}
	int TM_Ret = 0;

	lua_getglobal(M_Script_Lua, (const char *)TM_Item->lua_charfunctable[LUAITEM_ATTACHFUNC].string);
	lua_pushinteger(M_Script_Lua, (lua_Integer)_playindex);
	lua_pushinteger(M_Script_Lua, (lua_Integer)_itemindex);

	TM_Ret = lua_pcall(M_Script_Lua, 2, 0, 0);
	if(TM_Ret != 0)
	{
		//失敗-輸出錯誤信息
		print("NPC_Lua_ItemAttachCallBack Lua Err :%d(%s)\n", TM_Ret, lua_tostring(M_Script_Lua, -1));
		//出棧
		lua_pop(M_Script_Lua, 1);
		return ;
	}

	return ;
}

void NPC_Lua_ItemDetachCallBack(int _playindex, int _itemindex)
{
	if(M_Script_Lua == NULL)
	{
		print("M_Script_Lua Null!");
		return ;
	}
	ITEM_Item *TM_Item = ITEM_getItemPointer(_itemindex);
	if(TM_Item == NULL)
	{
		return ;
	}
	int TM_Ret = 0;

	lua_getglobal(M_Script_Lua, (const char *)TM_Item->lua_charfunctable[LUAITEM_DETACHFUNC].string);
	lua_pushinteger(M_Script_Lua, (lua_Integer)_playindex);
	lua_pushinteger(M_Script_Lua, (lua_Integer)_itemindex);

	TM_Ret = lua_pcall(M_Script_Lua, 2, 0, 0);
	if(TM_Ret != 0)
	{
		//失敗-輸出錯誤信息
		print("NPC_Lua_ItemDetachCallBack Lua Err :%d(%s)\n", TM_Ret, lua_tostring(M_Script_Lua, -1));
		//出棧
		lua_pop(M_Script_Lua, 1);
		return ;
	}

	return ;
}

void NPC_Lua_ItemDropCallBack(int _playindex, int _itemindex)
{
	if(M_Script_Lua == NULL)
	{
		print("M_Script_Lua Null!");
		return ;
	}
	ITEM_Item *TM_Item = ITEM_getItemPointer(_itemindex);
	if(TM_Item == NULL)
	{
		return ;
	}
	int TM_Ret = 0;

	lua_getglobal(M_Script_Lua, (const char *)TM_Item->lua_charfunctable[LUAITEM_DROPFUNC].string);
	lua_pushinteger(M_Script_Lua, (lua_Integer)_playindex);
	lua_pushinteger(M_Script_Lua, (lua_Integer)_itemindex);

	TM_Ret = lua_pcall(M_Script_Lua, 2, 0, 0);
	if(TM_Ret != 0)
	{
		//失敗-輸出錯誤信息
		print("NPC_Lua_ItemDropCallBack Lua Err :%d(%s)\n", TM_Ret, lua_tostring(M_Script_Lua, -1));
		//出棧
		lua_pop(M_Script_Lua, 1);
		return ;
	}

	return ;
}

void NPC_Lua_ItemPickUPCallBack(int _playindex, int _itemindex)
{
	if(M_Script_Lua == NULL)
	{
		print("M_Script_Lua Null!");
		return ;
	}
	ITEM_Item *TM_Item = ITEM_getItemPointer(_itemindex);
	if(TM_Item == NULL)
	{
		return ;
	}
	int TM_Ret = 0;

	lua_getglobal(M_Script_Lua, (const char *)TM_Item->lua_charfunctable[LUAITEM_PICKUPFUNC].string);
	lua_pushinteger(M_Script_Lua, (lua_Integer)_playindex);
	lua_pushinteger(M_Script_Lua, (lua_Integer)_itemindex);

	TM_Ret = lua_pcall(M_Script_Lua, 2, 0, 0);
	if(TM_Ret != 0)
	{
		//失敗-輸出錯誤信息
		print("NPC_Lua_ItemPickUPCallBack Lua Err :%d(%s)\n", TM_Ret, lua_tostring(M_Script_Lua, -1));
		//出棧
		lua_pop(M_Script_Lua, 1);
		return ;
	}

	return ;
}

#ifdef _Item_ReLifeAct
void NPC_Lua_ItemDieReLifeCallBack(int _playindex, int _itemindex, int _haveitem)
{
	if(M_Script_Lua == NULL)
	{
		print("M_Script_Lua Null!");
		return ;
	}
	ITEM_Item *TM_Item = ITEM_getItemPointer(_itemindex);
	if(TM_Item == NULL)
	{
		return ;
	}
	int TM_Ret = 0;

	lua_getglobal(M_Script_Lua, (const char *)TM_Item->lua_charfunctable[LUAITEM_DIERELIFEFUNC].string);
	lua_pushinteger(M_Script_Lua, (lua_Integer)_playindex);
	lua_pushinteger(M_Script_Lua, (lua_Integer)_itemindex);
	lua_pushinteger(M_Script_Lua, (lua_Integer)_haveitem);

	TM_Ret = lua_pcall(M_Script_Lua, 3, 0, 0);
	if(TM_Ret != 0)
	{
		//失敗-輸出錯誤信息
		print("NPC_Lua_ItemDieReLifeCallBack Lua Err :%d(%s)\n", TM_Ret, lua_tostring(M_Script_Lua, -1));
		//出棧
		lua_pop(M_Script_Lua, 1);
		return ;
	}

	return ;
}
#endif
*/

void NPC_Lua_BattleWinCallBack(int _battleindex, int _createptr)
{
	if(M_Script_Lua == NULL)
	{
		print("M_Script_Lua Null!");
		return ;
	}
	if( !API_BATTLE_CHECKINDEX( _battleindex ) )
	{
		return ;
	}
	
	int TM_Ret = 0;

	int _createIndex = API_CHAR_getCharaIndex(_createptr);
	lua_getglobal(M_Script_Lua, BATTLE_DATA_EXTEND[_battleindex].functable[BATTLE_WIN].string);
	lua_pushinteger(M_Script_Lua, (lua_Integer)_battleindex);
	lua_pushinteger(M_Script_Lua, (lua_Integer)_createIndex);

	TM_Ret = lua_pcall(M_Script_Lua, 2, 0, 0);
	if(TM_Ret != 0)
	{
		//失敗-輸出錯誤信息
		print("NPC_Lua_BattleWinCallBack Lua Err :%d(%s)\n", TM_Ret, lua_tostring(M_Script_Lua, -1));
		//出棧
		lua_pop(M_Script_Lua, 1);
		return ;
	}

	return ;
}

int NPC_GivePet(int TM_Ptr, int TM_EnemyId, int TM_FullPB)
{
	int result; // eax@7
	int v3; // edi@9
	int v5; // ST14_4@11
	int v6; // eax@11
	int v9; // eax@11
	int petPtr; // esi@12
	int v12; // edi@14
	int i;
	
	//計算寵物欄空位
	int petSpaceNum = 0;
	for(i=0; i<5; i++)
	{
		if ( API_CHAR_getHavePetCharPointer(TM_Ptr, i) == 0 )
			petSpaceNum++;
	}

	//寵物欄位已滿
	if ( petSpaceNum == 0 )
	{
		API_CHAR_talkToCli(TM_Ptr, 0, "寵物欄位已滿!", 0, 0);
		return 0;
		
	}
	
	//製作寵物
	int enemyArrayIndex = API_ENEMY_getEnemyArrayFromId(TM_EnemyId);
	if(enemyArrayIndex == -1)
		return 0;
	v9 = API_ENEMY_createEnemy(enemyArrayIndex, 0, 0);
	if ( !v9 )
		return 0;
	petPtr = API_PET_createPetFromCharaIndex(TM_Ptr, v9);
	if ( !petPtr )
		return 0;
	API_CHAR_endCharOneArray(v9);
	//char buf[128];
	//snprintf(buf, 0x40u, "寵物製作完成. 名稱[%s], index[%d]", petPtr + 648, *(int *)(petPtr + 4));
	//API_CHAR_talkToCli(TM_Ptr, 0, buf, 0, 0);
	*(int *)(petPtr + 220) = *(int *)(petPtr + 44);
	
	//滿檔寵, 修改成長率
	if(TM_FullPB){
		int enemyTempArrayIndex = API_ENEMYTEMP_getEnemyTempArray(enemyArrayIndex);
		if(enemyTempArrayIndex<0)
			return 0;
		int addition_d = *(int*)(*(int*)0x10D0E1E0 + 212 * enemyTempArrayIndex + sizeof(int)*1) + 2;
		int vital_d = *(int*)(*(int*)0x10D0E1E0 + 212 * enemyTempArrayIndex + sizeof(int)*4) + 2;
		int str_d = *(int*)(*(int*)0x10D0E1E0 + 212 * enemyTempArrayIndex + sizeof(int)*5) + 2;
		int tough_d = *(int*)(*(int*)0x10D0E1E0 + 212 * enemyTempArrayIndex + sizeof(int)*6) + 2;
		int quick_d = *(int*)(*(int*)0x10D0E1E0 + 212 * enemyTempArrayIndex + sizeof(int)*7) + 2;
		int magic_d = *(int*)(*(int*)0x10D0E1E0 + 212 * enemyTempArrayIndex + sizeof(int)*8) + 2;
		//char buf[128];
		//snprintf(buf, 128, "addition_d:%d, vital_d:%d, str_d:%d, tough_d:%d, quick_d:%d, magic_d:%d", addition_d, vital_d, str_d, tough_d, quick_d, magic_d);
		//API_CHAR_talkToCli(TM_Ptr, 0, buf, 0, 0);
		
		//計算成長率
		int levelUpPoint = ( vital_d << 24 ) + ( str_d << 18 ) + ( tough_d << 12 ) + ( quick_d << 6 ) + ( magic_d << 0 );
		
		int vital_t = ( vital_d +2)*addition_d;
		int str_t = ( str_d +2)*addition_d;
		int tough_t = ( tough_d +2)*addition_d;
		int quick_t = ( quick_d +2)*addition_d;
		int magic_t = ( magic_d +2)*addition_d;
		
		int hp = 20 + ((vital_t * 8 + str_t * 2 + tough_t * 3 + quick_t * 3 + magic_t *  1) / 100);
		int mp = 20 + ((vital_t * 1 + str_t * 2 + tough_t * 2 + quick_t * 2 + magic_t * 10) / 100);
		
		//寫入
		*(int *)(petPtr + 48) = hp;
		*(int *)(petPtr + 1160) = hp;
		*(int *)(petPtr + 52) = mp;
		*(int *)(petPtr + 1164) = mp;
		*(int *)(petPtr + 56) = vital_t;
		*(int *)(petPtr + 60) = str_t;
		*(int *)(petPtr + 64) = tough_t;
		*(int *)(petPtr + 68) = quick_t;
		*(int *)(petPtr + 72) = magic_t;
		//成長率
		*(int *)(petPtr + 192) = levelUpPoint;
	}
	
	//發送更新寵物封包
	for(i=0; i<5; i++)
	{
		result = API_CHAR_getHavePetCharPointer(TM_Ptr, i);
		if ( result )
		{
			API_CHAR_send_KP_String(TM_Ptr, i, -1);
			API_CHAR_send_KP2_String(TM_Ptr, i, -1);
			API_CHAR_sendPetTechData(TM_Ptr, i);
		}
	}
	
	//服務端紀錄
	API_LogPet(TM_Ptr + 712, TM_Ptr + 648, petPtr + 648, petPtr + 680, *(int *)(petPtr + 44), (int)"npc_lua.c:NPC_GivePet", *(int *)(TM_Ptr + 24), *(int *)(TM_Ptr + 28), *(int *)(TM_Ptr + 32), *(int *)(TM_Ptr + 36));

	//char buf[128];
	//snprintf(buf, 128, "%d", petPtr);
	//API_CHAR_talkToCli(TM_Ptr, 0, buf, 0, 0);
	
	return petPtr;
}



int NPC_GiveItem(int charaPtr, int itemid, int itemnum)
{
	int emptyitemindexinchara = -1;
	int itemindex = -1;
	int TM_ItemIndex = -1;
	int TM_RetCount = 0;

	int i;
	for(i=0; i<itemnum; i++)
	{
		emptyitemindexinchara = API_CHAR_findEmptyItemBox( charaPtr );
		if( emptyitemindexinchara < 0 )
		{
			break;
		}

		itemindex = API_ITEM_makeItemAndRegist( itemid );
		if( itemindex != -1 )
		{
			//道具是否可堆疊
			int pileNumMax = API_ITEM_getInt(itemindex, 10);
			if(pileNumMax <= 1)
			{
				TM_RetCount++;
			}
			else
			{
				int todoCount = itemnum - TM_RetCount;
				if(pileNumMax >= todoCount)
				{
					API_ITEM_setInt(itemindex, 9, todoCount);
					TM_RetCount += todoCount;
				}
				else
				{
					API_ITEM_setInt(itemindex, 9, pileNumMax);
					TM_RetCount += pileNumMax;
				}
			}
			
			
			
			API_CHAR_setItemIndex( charaPtr, emptyitemindexinchara, itemindex );
			API_ITEM_setWorkInt(itemindex, 0,-1);
			//ITEM_setWorkInt(itemindex, ITEM_WORKCHARAINDEX, charaPtr);
			API_ITEM_setCharPointer(itemindex, charaPtr);
			API_CHAR_sendItemDataOne( charaPtr, emptyitemindexinchara);
			//紀錄
			API_LogItem(charaPtr + 712, charaPtr + 648, itemid, (int)"GiveItem", *(int *)(charaPtr + 24), *(int *)(charaPtr + 28), *(int *)(charaPtr + 32), *(int *)(charaPtr + 36));
			TM_ItemIndex = itemindex;
		}
		
		//已製作完成指定數量道具
		if(TM_RetCount >= itemnum)
			break;
	}
	
	if(TM_RetCount > 0)
	{
		char TM_Buff[128];
		snprintf(TM_Buff, sizeof(TM_Buff), "獲得 %d 個 %s。", TM_RetCount, API_ITEM_getChar( TM_ItemIndex, 1));
		API_CHAR_talkToCli( charaPtr, 0, TM_Buff, 4, 0);
	}
	
	return TM_RetCount;
}


int NPC_DelPet(int charaPtr, int enemyID, int level, int levelRange)
{
	int petPtr;

	int i = 0;
	do
	{
		petPtr = API_CHAR_getHavePetCharPointer(charaPtr, i);
		if( API_CHAR_CheckCharPointer(petPtr)
			&& (*(int *)(petPtr + 284) == enemyID)
			&& ((levelRange==0 && *(int *)(petPtr + 44) <= level) || (levelRange==1 && *(int *)(petPtr + 44) == level) || (levelRange==2 && *(int *)(petPtr + 44) >= level) )
		)
			break;
		++i;
	}
	while ( i <= 4 );
	
	//沒找到符合條件的寵物
	if ( i == 5 )
	{
		return 0;
	}
	
	//?
	if ( *(int *)(petPtr + 288) == 3 )
		API_PET_stopFieldPet(charaPtr, i);

	//取消正在騎乘的寵物
	if ( *(int *)(charaPtr + 1504) == i )
		API_PET_stopRidePet(charaPtr);
	
	//紀錄刪除寵物資訊
	API_LogPet(
		charaPtr + 712,
		charaPtr + 648,
		petPtr + 648,
		petPtr + 680,
		*(int *)(petPtr + 44),
		(int)"npc_lua.c:NPC_DelPet",
		*(int *)(charaPtr + 24),
		*(int *)(charaPtr + 28),
		*(int *)(charaPtr + 32),
		*(int *)(charaPtr + 36));

	//取消人物和寵物關聯
	API_CHAR_setHavePetCharPointer(charaPtr, i, 0);
	
	//提示交出寵物
	char TM_Buff[128];
	sprintf(TM_Buff, "交出了 %s。" , (char*)(petPtr + 648));
	API_CHAR_talkToCli(charaPtr, 0, TM_Buff, 4, 0);
	
	//?
	if ( (*(int *)(petPtr + 288) & 0xF) == 2 )
	{
		*(int *)(charaPtr + 260) = -1;
	}

	if ( (*(int *)(petPtr + 288)) & 0x10 )
	{
		*(int *)(charaPtr + 1492) = -1;
		API_CHAR_sendCToArroundCharacter(*(int *)(charaPtr + 1360));
	}
	API_CHAR_send_KP_String(charaPtr, i, 1<<24);
	API_CHAR_endCharOneArray(petPtr);
	return 1;
}

int NPC_DelItem(int TM_Ptr, int TM_ItemID, int TM_Num)
{
	if(TM_Num<=1)
		return 0;
	
	int i, itemindex;
	int count = 0;
	char itemName[256];
	for(i=0; i<28; i++)
	{
		itemindex = API_CHAR_getItemIndex(TM_Ptr, i);
		if(itemindex<0) continue;
		if(API_ITEM_getInt(itemindex, 0) != TM_ItemID) continue;
		//紀錄道具名稱
		strcpy(itemName, API_ITEM_getChar( itemindex, 1));
		//道具是否堆疊
		int pileNumMax = API_ITEM_getInt(itemindex, 10);
		int pileNum = API_ITEM_getInt(itemindex, 9);
		if(pileNumMax <= 1 || (pileNumMax>1 && pileNum <= (TM_Num - count)))
		{
			API_LogItem(TM_Ptr + 712, TM_Ptr + 648, TM_ItemID, (int)"DelItem", *(int *)(TM_Ptr + 24), *(int *)(TM_Ptr + 28), *(int *)(TM_Ptr + 32), *(int *)(TM_Ptr + 36));
			API_CHAR_unsetItem(TM_Ptr, i);
			API_CHAR_sendItemDataOne(TM_Ptr, i);
			API_ITEM_endExistItemsOne(itemindex);
			if(pileNumMax <= 1)
				count++;
			else
				count += pileNum;
		}
		else
		{
			API_ITEM_setInt(itemindex, 9, pileNum - (TM_Num - count));
			API_CHAR_sendItemDataOne(TM_Ptr, i);
			count += (TM_Num - count);
		}
		
		//已刪除指定數量道具
		if(count >= TM_Num) break;
	}
	
	if(count > 0)
	{
		char TM_Buff[128];
		snprintf(TM_Buff, sizeof(TM_Buff), "交出 %d 個 %s。", count, itemName);
		API_CHAR_talkToCli( TM_Ptr, 0, TM_Buff, 4, 0);
	}

	return count;

}


int NPC_Lua_CreateVsEnemy(lua_State *_NLL, int _CharaPtr, int _NpcPtr, const char *_DoFunc, PCREATEENEMY _CreateEnemy, int _ARLen, int _Flg)
{
	assert(_CreateEnemy != NULL && _ARLen > 0 && _NLL != NULL);
	
	int v4; // eax@1
	int v6; // edx@3
	int battlePtrBase = *(int*)0x10D69C10; // eax@8
	int battlePtr; // eax@8
	int v10; // edx@8
	int v11; // eax@10
	int v15; // edi@16
	int v18; // ebx@29
	int v19; // edi@40
	int enemyCharPtr; // eax@73
	int v28; // esi@73
	int v29; // edx@77
	int v30; // eax@86
	int v52; // esi@109
	int v53; // ebx@110
	int v54; // esi@115
	int v55; // ebx@116
	int v56; // [sp-8h] [bp-F4h]@43
	int v57; // [sp-4h] [bp-F0h]@43
	int v58; // [sp+10h] [bp-DCh]@1
	int v59; // [sp+14h] [bp-D8h]@16
	int v60; // [sp+14h] [bp-D8h]@67
	int v61; // [sp+18h] [bp-D4h]@1
	int v62; // [sp+1Ch] [bp-D0h]@1
	int v64; // [sp+24h] [bp-C8h]@16
	int v65; // [sp+28h] [bp-C4h]@32
	int battleIndex; // [sp+2Ch] [bp-C0h]@7
	int enemyPosArray[12] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};; // [sp+54h] [bp-98h]@1
	int v76;
	
	int TM_BattleIndex = -1;
	int TM_FieldNO = 0;
	int TM_Ret = 0;
	int TM_Type = 0;
	int i = 0;

	v62 = 1;
	v61 = 0;
	v58 = 0;
	v4 = API_CHAR_CheckCharPointer(_CharaPtr);
	if ( !v4 )
		return -6;
	if ( *(int*)(_CharaPtr + 1672) > 0 )
	{
		v6 = *(int*)(_CharaPtr + 312);
		if ( v6 & 2 )
		{
			*(int*)(_CharaPtr + 20) = *(int*)(_CharaPtr + 644);
			*(int*)(_CharaPtr + 312) = v6 & 0xFFFFFFFD;
			*(int*)(_CharaPtr + 1672) = 0;
			//API_CHAR_complianceParameter(_CharaPtr, _CharaPtr, 1);
			API_CHAR_complianceParameter(_CharaPtr, 1);
			API_CHAR_sendCToArroundCharacter(*(int*)(_CharaPtr + 1360));
		}
	}

	
	if ( *(int*)(_CharaPtr + 1100) )
	{
		API_SYSTEMMSG(_CharaPtr, 0x817C54D);
		return -9;
	}
	API_CHAR_setFlg((int)"battle/battle.c", 2959, _CharaPtr, 0, 0);
	battleIndex = API_BATTLE_CreateBattle();
	if ( battleIndex == -1 )
		return -1;
	*(int*)(battlePtrBase + 5100 * battleIndex + 5084) = _NpcPtr;
	*(int*)(battlePtrBase + 5100 * battleIndex + 44) = 0;
	*(int*)(battlePtrBase + 5100 * battleIndex + 108) = 0; //BATTLE_S_TYPE_PLAYER
	*(int*)(battlePtrBase + 5100 * battleIndex + 2516) = 1; //BATTLE_S_TYPE_ENEMY
	*(int*)(battlePtrBase + 5100 * battleIndex + 16) = 1; //BATTLE_TYPE_P_vs_E
	*(int*)(battlePtrBase + 5100 * battleIndex + 36) = _CharaPtr;
	*(int*)(battlePtrBase + 5100 * battleIndex + 96) = -1;
	//Flg about round 2 battle
	*(int*)(battlePtrBase + 5100 * battleIndex + 56) = -1;
	*(int*)(battlePtrBase + 5100 * battleIndex + 60) = 0;
	*(int*)(battlePtrBase + 5100 * battleIndex + 64) = 0;
	
	battlePtr = battlePtrBase + 5100 * battleIndex;
	v10 = 1;
	do
	{
		*(int*)(battlePtr + 2508) = 0;
		*(int*)(battlePtr + 2512) = 0;
		battlePtr += 2408;
		--v10;
	}
	while ( v10 >= 0 );
	v11 = API_MAP_getfloorIndex(3030, *(int*)(_CharaPtr + 24), *(int*)(_CharaPtr + 28));
	if ( v11 != -1 )
	{
		if ( *(int*)(*(int*)(4 * *(int*)(_CharaPtr + 24) + 0x1116FC34) + (v11 << 7) + 108) )
			goto NPC_Lua_CreateVsEnemy_LABEL_1;
		if ( *(int*)(_CharaPtr + 1556) )
		{
			v54 = 0;
			while ( 1 )
			{
				v55 = API_CHAR_getPartyCharPointer(_CharaPtr, v54);
				if ( API_CHAR_CheckCharPointer(v55) )
				{
					if ( *(int*)(v55 + 1884) <= 6 )
						break;
				}
				++v54;
				if ( v54 > 4 )
					goto NPC_Lua_CreateVsEnemy_LABEL_1;
			}
			v76 = v54 > 4;
		}
		else
		{
			v76 = *(int*)(_CharaPtr + 1884)  > 6;
		}
		if ( v76 )
NPC_Lua_CreateVsEnemy_LABEL_1:
			*(int*)(battlePtrBase + 5100 * battleIndex + 72) |= 0x10u;
	}
	v64 = API_BATTLE_PartyNewEntry(_CharaPtr, battleIndex, 0);
	v59 = *(int*)(_CharaPtr + 44);
	v15 = (v64 == 0);
	if ( *(int*)(_CharaPtr + 1556) == 1 )
	{
		for(v52=1; v52<=4; v52++)
		{
			v53 = *(int*)(_CharaPtr + 4 * v52 + 2132);
			if ( API_CHAR_CheckCharPointer(v53) && *(int*)(v53 + 44) < v59 )
				v59 = *(int*)(v53 + 44);
		}

	}
	
	v18 = 0;
	while ( API_BATTLE_BossCheck(_CreateEnemy[v18].EnemyId) != 1 )
	{
		++v18;
		if ( v18 > 9 )
			goto NPC_Lua_CreateVsEnemy_LABEL_LABEL_2;
	}
	v62 = 5;
NPC_Lua_CreateVsEnemy_LABEL_LABEL_2:
	v65 = API_BATTLE_GetFieldNo(battleIndex, v62, _CharaPtr);
	*(int*)(battlePtrBase + 5100 * battleIndex + 68) = v65;
	if ( v15 )
	{
		API_BATTLE_ListRand((int)enemyPosArray);
		for(i=0; i<_ARLen; i++)
		{
//----------------- Debug Begin-------------------
//char tmp[128];
//sprintf(tmp, "ENEMY_createEnemy_%d EnemyIndex:%d, Level:%d, Range:%d, Position:%d", i, _CreateEnemy[i].EnemyId, _CreateEnemy[i].BaseLevel, _CreateEnemy[i].BaseLevelRange, enemyPosArray[i]);
//API_CHAR_talkToCli(_CharaPtr, 0, tmp, 0, 0);
//----------------- Debug End --------------------
			enemyCharPtr = API_ENEMY_createEnemy(_CreateEnemy[i].EnemyId, _CreateEnemy[i].BaseLevel, _CreateEnemy[i].BaseLevelRange);
			v28 = enemyCharPtr;
			if ( enemyCharPtr )
			{
				v64 = API_BATTLE_NewEntry(enemyCharPtr, battleIndex, 1, enemyPosArray[i]);
				if ( v64 )
					break;
				if ( *(int*)(v28 + 200) > 0 )
					*(int*)(battlePtrBase + 5100 * battleIndex + 20) = 1;
				v29 = *(int*)(v28 + 20);
				if ( (unsigned int)(v29 - 101910) <= 3
					|| (v29 == 101810 && *(int*)(_CharaPtr + 28) == 11032)
					|| (v29 == 107913 && *(int*)(_CharaPtr + 28) == 51100) )
				{
					*(int*)(battlePtrBase + 5100 * battleIndex + 68) = v65;
					v62 = 6;
					v65 = API_BATTLE_GetFieldNo(battleIndex, 6, _CharaPtr);
					v29 = *(int*)(v28 + 20);
				}
				if ( *(int*)(v28 + 44) > v61 )
					v61 = *(int*)(v28 + 44);
				if ( v29 == 10086 )
				{
					*(int*)(v28 + 1136) |= 0x40u;
					v30 = API_CHAR_getUseName(v28);
					fprintf(*(FILE **)0x81A9F80, (const char *)0x817C55D, v30);
				}
				++v58;
			}
		}
	}

	if(_DoFunc != NULL)
	{
		int TM_CallRet = 0;

		if(M_Script_Lua == NULL)
		{
			print("M_Script_Lua Null!");
			goto BATTLE_CreateVsEnemy_End;
		}
		lua_getglobal(_NLL, _DoFunc);
	
		if(lua_type(_NLL, -1) != LUA_TFUNCTION)
		{
			print("無法執行指定函數。");
			goto BATTLE_CreateVsEnemy_End;
		}
		lua_pushinteger(_NLL, (lua_Integer)TM_BattleIndex);
		TM_CallRet = lua_pcall(_NLL, 1, 1, 0);
		if(TM_CallRet != 0)
		{
			//失敗-輸出錯誤信息
			print("NPC_Lua_CreateVsEnemy Lua Err :%d(%s)\n", TM_CallRet, lua_tostring(_NLL, -1));
			//出棧
			lua_pop(_NLL, 1);
			goto BATTLE_CreateVsEnemy_End;
		}
		TM_Type = lua_tointeger(_NLL, -1);
		lua_pop(_NLL, 1);
	}
	
BATTLE_CreateVsEnemy_End:;
	if ( !v58 )
		v64 = 8;
	if ( v62 - 4 <= 2 )
		*(int*)(battlePtrBase + 5100 * battleIndex + 72) |= 4;
	v19 = API_getfdFromChar(_CharaPtr);
	if ( v64 )
	{
		API_BATTLE_ExitAll(battleIndex);
		API_BATTLE_DeleteBattle(battleIndex);
		if ( v19 != -1 )
			API_nrproto_EN_send(v19, 0, v65);
	}
	else
	{
		if ( v19 != -1 )
		{
			if ( *(int*)(battlePtrBase + 5100 * battleIndex + 20) )
			{
				v57 = v65;
				v56 = 7;
			}
			else
			{
				v57 = v65;
				v56 = v62;
			}
			API_nrproto_EN_send(v19, v56, v57);
		}
		
		for(i=1; i<=4; i++)
		{
			int partyMemberCharPtr = *(int*)(_CharaPtr + 2132 + 4 * i );
			if ( API_CHAR_CheckCharPointer(partyMemberCharPtr) )
			{
				if ( *(int*)(partyMemberCharPtr + 1100) != 6 )
				{
					int partyMemberCharFd = API_getfdFromChar(partyMemberCharPtr);
					if ( partyMemberCharFd != -1 )
					{
						API_nrproto_EN_send(partyMemberCharFd, v62, API_BATTLE_GetFieldNo(battleIndex, v62, partyMemberCharPtr));
					}
				}
			}
		}

		
		if ( *(int*)(_CharaPtr + 1536) )
		{
			*(int*)(_CharaPtr + 1532) = 0;
			*(int*)(_CharaPtr + 1536) = 0;
		}
		*(int*)(_CharaPtr + 2404) = 0;
		*(int*)(_CharaPtr + 2408) = 0;
		API_CHAR_updateGraphic(_CharaPtr);
		if ( *(int*)(_CharaPtr + 1392) != -1 )
		{
			API_CHAR_sendWatchEvent(*(int*)(_CharaPtr + 1360), 0, 0, 0, 0);
			*(int*)(_CharaPtr + 1392) = -1;
		}
		API_CHAR_sendBattleEffect(_CharaPtr, 1);
		
		for(i=1; i<=4; i++)
		{
			int partyMemberCharPtr = *(int*)(_CharaPtr + 2132 + 4 * i );
			if ( API_CHAR_CheckCharPointer(partyMemberCharPtr) )
			{
				if ( *(int*)(partyMemberCharPtr + 1536) )
				{
					*(int*)(partyMemberCharPtr + 1532) = 0;
					*(int*)(partyMemberCharPtr + 1536) = 0;
				}
				*(int*)(partyMemberCharPtr + 2404) = 0;
				*(int*)(partyMemberCharPtr + 2408) = 0;
				API_CHAR_updateGraphic(partyMemberCharPtr);
				if ( *(int*)(_CharaPtr + 1392) != -1 )
				{
					API_CHAR_sendWatchEvent(*(int*)(partyMemberCharPtr + 1360), 0, 0, 0, 0);
					*(int*)(partyMemberCharPtr + 1392) = -1;
				}
				API_CHAR_sendBattleEffect(partyMemberCharPtr, 1);
			}
		}
	}
	return battleIndex;
}



int NPC_Lua_CreateVsPlayer(int *_OutBattleIndex, int charaptr1, int charaptr2 )
{
	int battlePtrBase = *(int*)0x10D69C10;
	int v12; // ebx@20
	int v13; // eax@20
	int v17; // esi@28
	int v18; // eax@29
	int v20; // edi@32
	int v21; // ebx@33
	int v22; // esi@35
	int v23; // eax@35
	int v24; // edi@45
	int v25; // ebx@45
	int v26; // edx@49
	int v27; // eax@57
	int v28; // edi@65
	int v29; // zf@71
	int charaptr_leader; // [sp+18h] [bp-34h]@62
	int v37; // [sp+1Ch] [bp-30h]@24
	int side; // [sp+20h] [bp-2Ch]@61
	int battleFieldNo; // [sp+24h] [bp-28h]@9
	int v44; // [sp+24h] [bp-28h]@26
	int battleIndex; // [sp+28h] [bp-24h]@19
	int charaptr1_leader; // [sp+2Ch] [bp-20h]@15
	int charaptr2_leader; // [sp+30h] [bp-1Ch]@18

	if ( !API_CHAR_CheckCharPointer(charaptr1) || !API_CHAR_CheckCharPointer(charaptr2))
		return -6;

	if ( *(int *)(charaptr1 + 1100) || *(int *)(charaptr2 + 1100) )
	{
		API_SYSTEMMSG(charaptr1, "二重戰鬥");
		API_SYSTEMMSG(charaptr2, "二重戰鬥");
		return -9;
	}

	battleFieldNo = API_BATTLE_getBattleFieldNo(*(int *)(charaptr1 + 24), *(int *)(charaptr1 + 28), *(int *)(charaptr1 + 32), *(int *)(charaptr1 + 36));

	if ( *(int *)(charaptr1 + 1100) || *(int *)(charaptr2 + 1100) )
	{
		return -9;
	}

	if(*(int *)(charaptr1 + 1556)==1){
		charaptr1_leader = charaptr1;
	}else if(*(int *)(charaptr1 + 1556)==2){
		charaptr1_leader = *(int *)(charaptr1 + 2132);
	}else{
		charaptr1_leader = charaptr1;
	}

	if(*(int *)(charaptr2 + 1556)==1){
		charaptr2_leader = charaptr2;
	}else if(*(int *)(charaptr2 + 1556)==2){
		charaptr2_leader = *(int *)(charaptr2 + 2132);
	}else{
		charaptr2_leader = charaptr2;
	}

	if ( !API_CHAR_CheckCharPointer(charaptr1_leader) || !API_CHAR_CheckCharPointer(charaptr2_leader))
		return -6;

	if (charaptr1_leader == charaptr2_leader )
		return -10;
		

	
	battleIndex = API_BATTLE_CreateBattle();
	if ( battleIndex < 0 )
		return -1;
	
	*(int *)(battlePtrBase + 5100 * battleIndex + 68) = battleFieldNo;
	*(int *)(battlePtrBase + 5100 * battleIndex + 108) = 0;
	*(int *)(battlePtrBase + 5100 * battleIndex + 2516) = 0;
	*(int *)(battlePtrBase + 5100 * battleIndex + 5084) = charaptr2;
	*(int *)(battlePtrBase + 5100 * battleIndex + 36) = charaptr1;
	*(int *)(battlePtrBase + 5100 * battleIndex + 16) = 2;
	*(int *)(battlePtrBase + 5100 * battleIndex + 20) = 1;
	*(int *)(battlePtrBase + 5100 * battleIndex + 44) = 0;
	v13 = API_MAP_getfloorIndex(11299, *(int *)(charaptr1 + 24), *(int *)(charaptr1 + 28));
	if ( v13 != -1 )
		if ( *(int *)(*(int *)(4 * *(int *)(charaptr1 + 24) + 0x1116FC34) + (v13 << 7) + 108) )
			*(int *)(battlePtrBase + 5100 * battleIndex + 72) |= 0x10u;

			
	for(side=0; side<=1; side++)
	{
		if(side==0) charaptr_leader = charaptr1_leader;
		else charaptr_leader = charaptr2_leader;
		
		v37 = API_BATTLE_PartyNewEntry(charaptr_leader, battleIndex, side);

		*(int *)(battlePtrBase + 5100 * battleIndex + 112) &= 0xFFFFFFFDu;
		*(int *)(battlePtrBase + 5100 * battleIndex + 2508) = 0;
		*(int *)(battlePtrBase + 5100 * battleIndex + 2512) = 0;
		*(int *)(battlePtrBase + 5100 * battleIndex + 2408 + 112) &= 0xFFFFFFFDu;
		*(int *)(battlePtrBase + 5100 * battleIndex + 2408 + 2508) = 0;
		*(int *)(battlePtrBase + 5100 * battleIndex + 2408 + 2512) = 0;

		*(int *)(battlePtrBase + 5100 * battleIndex + 56) = -1;
		v44 = API_BATTLE_GetFieldNo(battleIndex, 2, charaptr1);

		if(v37)
		{
			API_BATTLE_ExitAll(battleIndex);
			API_BATTLE_DeleteBattle(battleIndex);
			v27 = API_getfdFromChar(charaptr_leader);
			if ( v27 != -1 )
				API_nrproto_EN_send(v27, 0, v44);
			return -1;
		}
	}

	for(side=0; side<=1; side++)
	{
		if(side==0) charaptr_leader = charaptr1_leader;
		else charaptr_leader = charaptr2_leader;
		
		v17 = API_getfdFromChar(charaptr_leader);
		if ( v17 != -1 )
		{
			v18 = API_BATTLE_GetFieldNo(battleIndex, 2, charaptr_leader);
			API_nrproto_EN_send(v17, *(int *)(battlePtrBase + 5100 * battleIndex + 16), v18);
		}
		if ( *(int *)(charaptr_leader + 1392) != -1 )
		{
			API_CHAR_sendWatchEvent(*(int *)(charaptr_leader + 1360), 0, 0, 0, 0);
			*(int *)(charaptr1 + 1392) = -1;
		}
		API_CHAR_sendBattleDuel(charaptr_leader, 1);
		v20 = 1;
		do
		{
			v21 = *(int *)(charaptr_leader + 4 * v20 + 2132);
			if ( API_CHAR_CheckCharPointer(v21) && *(int *)(v21 + 1100) != 6 )
			{
				v22 = API_getfdFromChar(v21);
				v23 = API_BATTLE_GetFieldNo(battleIndex, 2, v21);
				if ( v22 != -1 )
					API_nrproto_EN_send(v22, *(int *)(battlePtrBase + 5100 * battleIndex + 16), v23);
				if ( *(int *)(v21 + 1392) != -1 )
				{
					API_CHAR_sendWatchEvent(*(int *)(v21 + 1360), 0, 0, 0, 0);
					*(int *)(v21 + 1392) = -1;
				}
				API_CHAR_sendBattleDuel(v21, 1);
			}
			++v20;
		}
		while ( v20 <= 4 );
	}
		
		
	if ( API_BATTLE_DuelPointCheck(*(int *)(charaptr1 + 28)) == 1 )
	{
		v24 = 0;
		v25 = 0;
		while ( v24 < API_CHAR_getPlayerMaxNum() )
		{
			if ( *(int*)0x10D0BEA0 <= v24 || v24 < 0 )
				v26 = 0;
			else
				v26 = ((*(int *)(v25 + *(int*)0x10D0BEBC) == 0) - 1) & (v25 + *(int*)0x10D0BEBC);
			if ( v26 && *(int *)v26 && *(int *)(v26 + 1676) && !*(int *)(v26 + 1100) )
				API_CHAR_RingWatch(v26);
			v25 += 6100;
			++v24;
		}
	}
		
		
	for(side=0; side<=1; side++)
	{
		if(side==0) charaptr_leader = charaptr1_leader;
		else charaptr_leader = charaptr2_leader;
				
		if(*(int *)(charaptr_leader + 1556))
		{
			v28 = 0;
			while ( 1 )
			{
				v12 = API_CHAR_getPartyCharPointer(charaptr_leader, v28);
				if ( API_CHAR_CheckCharPointer(v12) )
				{
					if ( *(int *)(v12 + 1884) <= 6 )
						break;
				}
				++v28;
				if ( v28 > 4 )
					break;
			}
			v29 = v28 > 4;
		}else{		
			v29 = *(int *)(charaptr_leader + 1884) > 6;
		}
		if ( v29 )
			*(int *)(battlePtrBase + 5100 * battleIndex + 72) |= 0x10u;
	}
	
	*_OutBattleIndex = battleIndex;
	return 0;
}


/*
int NPC_Lua_getBattleFieldNo(int _Floor, int _X, int _Y)
{
	int	tile[2], map[3], iRet;
	if( !MAP_getTileAndObjData( _Floor, _X, _Y, &tile[0], &tile[1] ) )
	{
		return FALSE;
	}
	map[0] = MAP_getImageInt( tile[0], MAP_BATTLEMAP );
	map[1] = MAP_getImageInt( tile[0], MAP_BATTLEMAP2 );
	map[2] = MAP_getImageInt( tile[0], MAP_BATTLEMAP3 );
	iRet = map[RAND( 0, 2 )];
	return iRet;
}
*/
#endif //#ifdef _JZ_NEWSCRIPT_LUA
