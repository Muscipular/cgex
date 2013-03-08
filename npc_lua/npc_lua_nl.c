#include "npc_lua.h"
#include "util.h"
#include "char.h"
#include "char_base.h"
#include "anim_tbl.h"
#include "object.h"
#include "net.h"
#include "npcutil.h"
#include "npc_eventaction.h"
#include "battle.h"
#include "readmap.h"
#include "cg_api.h"

#ifdef _JZ_NEWSCRIPT_LUA

extern char M_OutErrMsg[1024];
extern lua_State *M_Script_Lua;
extern unsigned int M_Create_Num;

//////////////////////////////////////////////////////////////////////////////
int NPC_Lua_NL_GetErrorStr(lua_State *_NLL)
{
	CheckEx(_NLL, 0);

	LRetMsg(_NLL, M_OutErrMsg);
}

int NPC_Lua_NL_CreateNpc(lua_State *_NLL)
{
	//參數有2個
	CheckEx(_NLL, 2);
	char *TM_DoFile = lua_tostring(_NLL, 1);
	char *TM_InitFuncName = lua_tostring(_NLL, 2);

	int TM_Ret = NPC_Lua_Create(TM_DoFile, TM_InitFuncName);

	LRet(TM_Ret);
}


int NPC_Lua_NL_DelNpc(lua_State *_NLL)
{
	CheckEx(_NLL, 1);
	CheckIndexNull(_NLL, 1);
	int TM_index = (int)lua_tointeger(_NLL, 1);
	int TM_Ret = NPC_Lua_Del(TM_index);
	LRetInt(_NLL, TM_Ret);
}

///////////////////////////////////////////  設定NL事件   ///////////////////////////////////
int NPC_Lua_NL_RegBattleOverEvent(lua_State *_NLL)
{
	CheckEx(_NLL, 2);

	int TM_Ret = NPC_Lua_GetFuncPoint(_NLL);

	if(lua_tointeger(_NLL, -1) > 0)
	{
		strcpy_s(NL_DATA_EXTEND.functable[NL_BATTLEOVERFUNC].string, sizeof(NL_DATA_EXTEND.functable[NL_BATTLEOVERFUNC].string), lua_tostring(_NLL, 2));
		NL_DATA_EXTEND.use[NL_BATTLEOVERFUNC] = 1;
	}else{
		NL_DATA_EXTEND.use[NL_BATTLEOVERFUNC] = 0;
	}
	return TM_Ret;
}

int NPC_Lua_NL_RegBattleStartEvent(lua_State *_NLL)
{
	CheckEx(_NLL, 2);

	int TM_Ret = NPC_Lua_GetFuncPoint(_NLL);

	if(lua_tointeger(_NLL, -1) > 0)
	{
		strcpy_s(NL_DATA_EXTEND.functable[NL_BATTLESTARTFUNC].string, sizeof(NL_DATA_EXTEND.functable[NL_BATTLESTARTFUNC].string), lua_tostring(_NLL, 2));
		NL_DATA_EXTEND.use[NL_BATTLESTARTFUNC] = 1;
	}else{
		NL_DATA_EXTEND.use[NL_BATTLESTARTFUNC] = 0;
	}
	return TM_Ret;
}

int NPC_Lua_NL_RegLevelUpEvent(lua_State *_NLL)
{
	CheckEx(_NLL, 2);

	int TM_Ret = NPC_Lua_GetFuncPoint(_NLL);

	if(lua_tointeger(_NLL, -1) > 0)
	{
		strcpy_s(NL_DATA_EXTEND.functable[NL_LEVELUPFUNC].string, sizeof(NL_DATA_EXTEND.functable[NL_LEVELUPFUNC].string), lua_tostring(_NLL, 2));
		NL_DATA_EXTEND.use[NL_LEVELUPFUNC] = 1;
	}else{
		NL_DATA_EXTEND.use[NL_LEVELUPFUNC] = 0;
	}
	return TM_Ret;
}

int NPC_Lua_NL_RegLoginEvent(lua_State *_NLL)
{
	CheckEx(_NLL, 2);

	int TM_Ret = NPC_Lua_GetFuncPoint(_NLL);

	if(lua_tointeger(_NLL, -1) > 0)
	{
		strcpy_s(NL_DATA_EXTEND.functable[NL_LOGINFUNC].string, sizeof(NL_DATA_EXTEND.functable[NL_LOGINFUNC].string), lua_tostring(_NLL, 2));
		NL_DATA_EXTEND.use[NL_LOGINFUNC] = 1;
	}else{
		NL_DATA_EXTEND.use[NL_LOGINFUNC] = 0;
	}
	return TM_Ret;
}

int NPC_Lua_NL_RegLoginGateEvent(lua_State *_NLL)
{
	CheckEx(_NLL, 2);

	int TM_Ret = NPC_Lua_GetFuncPoint(_NLL);

	if(lua_tointeger(_NLL, -1) > 0)
	{
		strcpy_s(NL_DATA_EXTEND.functable[NL_LOGINGATEFUNC].string, sizeof(NL_DATA_EXTEND.functable[NL_LOGINGATEFUNC].string), lua_tostring(_NLL, 2));
		NL_DATA_EXTEND.use[NL_LOGINGATEFUNC] = 1;
	}else{
		NL_DATA_EXTEND.use[NL_LOGINGATEFUNC] = 0;
	}
	return TM_Ret;
}

int NPC_Lua_NL_RegLogoutEvent(lua_State *_NLL)
{
	CheckEx(_NLL, 2);

	int TM_Ret = NPC_Lua_GetFuncPoint(_NLL);

	if(lua_tointeger(_NLL, -1) > 0)
	{
		strcpy_s(NL_DATA_EXTEND.functable[NL_LOGOUTFUNC].string, sizeof(NL_DATA_EXTEND.functable[NL_LOGOUTFUNC].string), lua_tostring(_NLL, 2));
		NL_DATA_EXTEND.use[NL_LOGOUTFUNC] = 1;
	}else{
		NL_DATA_EXTEND.use[NL_LOGOUTFUNC] = 0;
	}
	return TM_Ret;
}

int NPC_Lua_NL_RegTalkEvent(lua_State *_NLL)
{
	CheckEx(_NLL, 2);

	int TM_Ret = NPC_Lua_GetFuncPoint(_NLL);

	if(lua_tointeger(_NLL, -1) > 0)
	{
		strcpy_s(NL_DATA_EXTEND.functable[NL_TALKFUNC].string, sizeof(NL_DATA_EXTEND.functable[NL_TALKFUNC].string), lua_tostring(_NLL, 2));
		NL_DATA_EXTEND.use[NL_TALKFUNC] = 1;
	}else{
		NL_DATA_EXTEND.use[NL_TALKFUNC] = 0;
	}
	return TM_Ret;
}

int NPC_Lua_NL_RegTitleChangedEvent(lua_State *_NLL)
{
	CheckEx(_NLL, 2);

	int TM_Ret = NPC_Lua_GetFuncPoint(_NLL);

	if(lua_tointeger(_NLL, -1) > 0)
	{
		strcpy_s(NL_DATA_EXTEND.functable[NL_TITLECHANGEFUNC].string, sizeof(NL_DATA_EXTEND.functable[NL_TITLECHANGEFUNC].string), lua_tostring(_NLL, 2));
		NL_DATA_EXTEND.use[NL_TITLECHANGEFUNC] = 1;
	}else{
		NL_DATA_EXTEND.use[NL_TITLECHANGEFUNC] = 0;
	}
	return TM_Ret;
}

int NPC_Lua_NL_RegWarpEvent(lua_State *_NLL)
{
	CheckEx(_NLL, 2);

	int TM_Ret = NPC_Lua_GetFuncPoint(_NLL);

	if(lua_tointeger(_NLL, -1) > 0)
	{
		strcpy_s(NL_DATA_EXTEND.functable[NL_WARPFUNC].string, sizeof(NL_DATA_EXTEND.functable[NL_WARPFUNC].string), lua_tostring(_NLL, 2));
		NL_DATA_EXTEND.use[NL_WARPFUNC] = 1;
	}else{
		NL_DATA_EXTEND.use[NL_WARPFUNC] = 0;
	}
	return TM_Ret;
}

///////////////////////////////////////////  設定NL事件  CallBack  ///////////////////////////////////
int NPC_Lua_NL_BattleOverCallBack(int _battleindex)
{
	if(M_Script_Lua == NULL)
	{
		print("M_Script_Lua Null!");
		return -1;
	}
	if( !API_BATTLE_CHECKINDEX( _battleindex ) )
	{
		return -2;
	}
	
	int TM_Ret = 0;

	lua_getglobal(M_Script_Lua, NL_DATA_EXTEND.functable[NL_BATTLEOVERFUNC].string);
	lua_pushinteger(M_Script_Lua, (lua_Integer)_battleindex);

	TM_Ret = lua_pcall(M_Script_Lua, 1, 1, 0);
	if(TM_Ret != 0)
	{
		//失敗-輸出錯誤信息
		print("NPC_Lua_NL_BattleOverCallBack Lua Err :%d(%s)\n", TM_Ret, lua_tostring(M_Script_Lua, -1));
		//出棧
		lua_pop(M_Script_Lua, 1);
		return -3;
	}
	
	TM_Ret = (int)lua_tointeger(M_Script_Lua, -1);
	lua_pop(M_Script_Lua, 1);
	return TM_Ret;
}

int NPC_Lua_NL_BattleStartCallBack(int _battleindex)
{
	if(M_Script_Lua == NULL)
	{
		print("M_Script_Lua Null!");
		return -1;
	}
	if( !API_BATTLE_CHECKINDEX( _battleindex ) )
	{
		return -2;
	}
	
	int TM_Ret = 0;

	lua_getglobal(M_Script_Lua, NL_DATA_EXTEND.functable[NL_BATTLESTARTFUNC].string);
	lua_pushinteger(M_Script_Lua, (lua_Integer)_battleindex);

	TM_Ret = lua_pcall(M_Script_Lua, 1, 1, 0);
	if(TM_Ret != 0)
	{
		//失敗-輸出錯誤信息
		print("NPC_Lua_NL_BattleStartCallBack Lua Err :%d(%s)\n", TM_Ret, lua_tostring(M_Script_Lua, -1));
		//出棧
		lua_pop(M_Script_Lua, 1);
		return -3;
	}

	TM_Ret = (int)lua_tointeger(M_Script_Lua, -1);
	lua_pop(M_Script_Lua, 1);
	return TM_Ret;
}

int NPC_Lua_NL_LevelUpCallBack(int _meptr)
{
	if(M_Script_Lua == NULL)
	{
		print("M_Script_Lua Null!");
		return -1;
	}
	int _meIndex = API_CHAR_getCharaIndex(_meptr);
	if(_meIndex < 0)
	{
		return -2;
	}
	int TM_Ret = 0;
	int TM_FuncRet = 0;

	
	lua_getglobal(M_Script_Lua, NL_DATA_EXTEND.functable[NL_LEVELUPFUNC].string);
	lua_pushinteger(M_Script_Lua, (lua_Integer)_meIndex);

	TM_Ret = lua_pcall(M_Script_Lua, 1, 1, 0);
	if(TM_Ret != 0)
	{
		//失敗-輸出錯誤信息
		print("NPC_Lua_NL_LevelUpCallBack Lua Err :%d(%s)\n", TM_Ret, lua_tostring(M_Script_Lua, -1));
		//出棧
		lua_pop(M_Script_Lua, 1);
		return -3;
	}
	TM_FuncRet = (int)lua_tointeger(M_Script_Lua, -1);
	lua_pop(M_Script_Lua, 1);
	return TM_FuncRet;
}

int NPC_Lua_NL_LoginCallBack(int _meptr)
{
	if(M_Script_Lua == NULL)
	{
		print("M_Script_Lua Null!");
		return -1;
	}
	int _meIndex = API_CHAR_getCharaIndex(_meptr);
	if(_meIndex < 0)
	{
		return -2;
	}
	int TM_Ret = 0;
	int TM_FuncRet = 0;

	
	lua_getglobal(M_Script_Lua, NL_DATA_EXTEND.functable[NL_LOGINFUNC].string);
	lua_pushinteger(M_Script_Lua, (lua_Integer)_meIndex);

	TM_Ret = lua_pcall(M_Script_Lua, 1, 1, 0);
	if(TM_Ret != 0)
	{
		//失敗-輸出錯誤信息
		print("NPC_Lua_NL_LoginCallBack Lua Err :%d(%s)\n", TM_Ret, lua_tostring(M_Script_Lua, -1));
		//出棧
		lua_pop(M_Script_Lua, 1);
		return -3;
	}
	TM_FuncRet = (int)lua_tointeger(M_Script_Lua, -1);
	lua_pop(M_Script_Lua, 1);
	return TM_FuncRet;
}

int NPC_Lua_NL_LoginGateCallBack(int _meptr)
{
	if(M_Script_Lua == NULL)
	{
		print("M_Script_Lua Null!");
		return -1;
	}
	int _meIndex = API_CHAR_getCharaIndex(_meptr);
	if(_meIndex < 0)
	{
		return -2;
	}
	int TM_Ret = 0;
	int TM_FuncRet = 0;

	
	lua_getglobal(M_Script_Lua, NL_DATA_EXTEND.functable[NL_LOGINGATEFUNC].string);
	lua_pushinteger(M_Script_Lua, (lua_Integer)_meIndex);

	TM_Ret = lua_pcall(M_Script_Lua, 1, 1, 0);
	if(TM_Ret != 0)
	{
		//失敗-輸出錯誤信息
		print("NPC_Lua_NL_LoginGateCallBack Lua Err :%d(%s)\n", TM_Ret, lua_tostring(M_Script_Lua, -1));
		//出棧
		lua_pop(M_Script_Lua, 1);
		return -3;
	}
	TM_FuncRet = (int)lua_tointeger(M_Script_Lua, -1);
	lua_pop(M_Script_Lua, 1);
	return TM_FuncRet;
}

int NPC_Lua_NL_LogoutCallBack(int _meptr)
{
	if(M_Script_Lua == NULL)
	{
		print("M_Script_Lua Null!");
		return -1;
	}
	int _meIndex = API_CHAR_getCharaIndex(_meptr);
	if(_meIndex < 0)
	{
		return -2;
	}
	int TM_Ret = 0;
	int TM_FuncRet = 0;

	
	lua_getglobal(M_Script_Lua, NL_DATA_EXTEND.functable[NL_LOGOUTFUNC].string);
	lua_pushinteger(M_Script_Lua, (lua_Integer)_meIndex);

	TM_Ret = lua_pcall(M_Script_Lua, 1, 1, 0);
	if(TM_Ret != 0)
	{
		//失敗-輸出錯誤信息
		print("NPC_Lua_NL_LogoutCallBack Lua Err :%d(%s)\n", TM_Ret, lua_tostring(M_Script_Lua, -1));
		//出棧
		lua_pop(M_Script_Lua, 1);
		return -3;
	}
	TM_FuncRet = (int)lua_tointeger(M_Script_Lua, -1);
	lua_pop(M_Script_Lua, 1);
	return TM_FuncRet;
}

int NPC_Lua_NL_TalkCallBack(int _meptr, char* _msg, int _color, int _range, int _size)
{
	if(M_Script_Lua == NULL)
	{
		print("M_Script_Lua Null!");
		return -1;
	}
	int _meIndex = API_CHAR_getCharaIndex(_meptr);
	if(_meIndex < 0)
	{
		return -2;
	}
	int TM_Ret = 0;
	int TM_FuncRet = 0;

	
	lua_getglobal(M_Script_Lua, NL_DATA_EXTEND.functable[NL_TALKFUNC].string);
	lua_pushinteger(M_Script_Lua, (lua_Integer)_meIndex);
	lua_pushstring(M_Script_Lua, _msg);
	lua_pushinteger(M_Script_Lua, (lua_Integer)_color);
	lua_pushinteger(M_Script_Lua, (lua_Integer)_range);
	lua_pushinteger(M_Script_Lua, (lua_Integer)_size);
	

	TM_Ret = lua_pcall(M_Script_Lua, 5, 1, 0);
	if(TM_Ret != 0)
	{
		//失敗-輸出錯誤信息
		print("NPC_Lua_NL_TalkCallBack Lua Err :%d(%s)\n", TM_Ret, lua_tostring(M_Script_Lua, -1));
		//出棧
		lua_pop(M_Script_Lua, 1);
		return -3;
	}
	TM_FuncRet = (int)lua_tointeger(M_Script_Lua, -1);
	lua_pop(M_Script_Lua, 1);
	return TM_FuncRet;
}

int NPC_Lua_NL_TitleChangedCallBack(int _meptr, int _oldTitleID, int _newTitleID)
{
	if(M_Script_Lua == NULL)
	{
		print("M_Script_Lua Null!");
		return -1;
	}
	int _meIndex = API_CHAR_getCharaIndex(_meptr);
	if(_meIndex < 0)
	{
		return -2;
	}
	int TM_Ret = 0;
	int TM_FuncRet = 0;

	
	lua_getglobal(M_Script_Lua, NL_DATA_EXTEND.functable[NL_TITLECHANGEFUNC].string);
	lua_pushinteger(M_Script_Lua, (lua_Integer)_meIndex);
	lua_pushinteger(M_Script_Lua, (lua_Integer)_oldTitleID);
	lua_pushinteger(M_Script_Lua, (lua_Integer)_newTitleID);

	

	TM_Ret = lua_pcall(M_Script_Lua, 3, 1, 0);
	if(TM_Ret != 0)
	{
		//失敗-輸出錯誤信息
		print("NPC_Lua_NL_TitleChangedCallBack Lua Err :%d(%s)\n", TM_Ret, lua_tostring(M_Script_Lua, -1));
		//出棧
		lua_pop(M_Script_Lua, 1);
		return -3;
	}
	TM_FuncRet = (int)lua_tointeger(M_Script_Lua, -1);
	lua_pop(M_Script_Lua, 1);
	return TM_FuncRet;
}

int NPC_Lua_NL_WarpCallBack(int _meptr, int _mapID, int _floorID, int _x, int _y)
{
	if(M_Script_Lua == NULL)
	{
		print("M_Script_Lua Null!");
		return -1;
	}
	int _meIndex = API_CHAR_getCharaIndex(_meptr);
	if(_meIndex < 0)
	{
		return -2;
	}
	int TM_Ret = 0;
	int TM_FuncRet = 0;

	
	lua_getglobal(M_Script_Lua, NL_DATA_EXTEND.functable[NL_WARPFUNC].string);
	lua_pushinteger(M_Script_Lua, (lua_Integer)_meIndex);
	lua_pushinteger(M_Script_Lua, (lua_Integer)_mapID);
	lua_pushinteger(M_Script_Lua, (lua_Integer)_floorID);
	lua_pushinteger(M_Script_Lua, (lua_Integer)_x);
	lua_pushinteger(M_Script_Lua, (lua_Integer)_y);
	

	TM_Ret = lua_pcall(M_Script_Lua, 5, 1, 0);
	if(TM_Ret != 0)
	{
		//失敗-輸出錯誤信息
		print("NPC_Lua_NL_WarpCallBack Lua Err :%d(%s)\n", TM_Ret, lua_tostring(M_Script_Lua, -1));
		//出棧
		lua_pop(M_Script_Lua, 1);
		return -3;
	}
	TM_FuncRet = (int)lua_tointeger(M_Script_Lua, -1);
	lua_pop(M_Script_Lua, 1);
	return TM_FuncRet;
}


#endif //#ifdef _JZ_NEWSCRIPT_LUA
