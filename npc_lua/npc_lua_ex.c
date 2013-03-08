#include "npc_lua.h"
//#include "util.h"
//#include "char.h"
//#include "char_base.h"
//#include "anim_tbl.h"
//#include "object.h"
//#include "net.h"
//#include "npcutil.h"
//#include "npc_eventaction.h"
//#include "battle.h"
//#include "readmap.h"
#include "cg_api.h"
#include <pthread.h>

#ifdef _JZ_NEWSCRIPT_LUA

extern char M_OutErrMsg[1024];
extern lua_State *M_Script_Lua;
extern unsigned int M_Create_Num;

//////////////////////////////////////////////////////////////////////////////
int NPC_Lua_RegCallEx(lua_State * _NLL, luaL_Reg *_RegList)
{
	assert(_RegList != NULL && _NLL != NULL);

	int i = 0;
	if((_NLL != NULL) && (_RegList != NULL))
	{
		while(_RegList->func != NULL)
		{
			lua_register(_NLL, _RegList->name, _RegList->func);
			i++;
			_RegList++;
		}
	}
	return i;
}

int NPC_Lua_RegLibEx(lua_State * _NLL, PSCRIPTREGLIB _RegLib)
{
	assert(_RegLib != NULL && _NLL != NULL);

	int i = 0;
	if((_NLL != NULL) && (_RegLib != NULL))
	{
		while(_RegLib->LibName != NULL)
		{
			luaL_openlib(_NLL, _RegLib->LibName, _RegLib->FuncRegList, 0);
			i++;
			_RegLib++;
		}
	}
	return i;
}

int NPC_Lua_RegClassEx(lua_State * _NLL, PSCRIPTREGCLASS _RegClass)
{
	assert(_RegClass != NULL && _NLL != NULL);
	
	int i = 0;
	if((_NLL != NULL) && (_RegClass != NULL))
	{
		while(_RegClass->ClassName != NULL)
		{
			luaL_newmetatable(_NLL, _RegClass->ClassName);
	
			lua_pushstring(_NLL, "__index");
			lua_pushvalue(_NLL, -2);
			lua_settable(_NLL, -3);
	
			luaL_openlib(_NLL, NULL, _RegClass->FuncRegList, 0);
	
			luaL_openlib(_NLL, _RegClass->NewLib , _RegClass->NewLib->FuncRegList, 0);
			
			i++;
			_RegClass++;
		}
	}
	return i;
}

int NPC_Lua_RegArrayEx(lua_State * _NLL, PSCRIPTREGARRAY _RegArray)
{
	assert(_RegArray != NULL && _NLL != NULL);
	
	int i = 0;
	if((_NLL != NULL) && (_RegArray != NULL))
	{
		int j = 0;
		while(_RegArray->ArrayName != NULL)
		{
			luaL_newmetatable(_NLL, _RegArray->ArrayName);
			luaL_openlib(_NLL, _RegArray->FuncList->LibName, _RegArray->FuncList->FuncRegList, 0);

			j = 0;
			while(_RegArray->SetMetaTable[j] != NULL)
			{
				lua_pushstring(_NLL, _RegArray->SetMetaTable[j]);
				lua_pushstring(_NLL, _RegArray->SetFuncName[j]);
				lua_gettable(_NLL, 2);
				lua_settable(_NLL, 1);
				j++;
			}
			i++;
			_RegArray++;
		}
	}
	return i;
}

const char *NPC_Lua_SetErrorStr(const char *ErrStr)
{
	if(ErrStr == NULL)
	{
		M_OutErrMsg[0] = '\0';
		return M_OutErrMsg;
	}
	return (const char *)strcpy_s(M_OutErrMsg, sizeof(M_OutErrMsg), ErrStr);
}


//創建NPC-返回NPC唯一索引
int NPC_Lua_Create(const char *_DoFile, const char *_InitFuncName)
{
	assert(_InitFuncName != NULL);
	
	pthread_mutex_lock((pthread_mutex_t *)0x8C89800);
	int TM_charaptr;
	int TM_objindex;

	//創建Char空間
	TM_charaptr = API_CHAR_getLinkChar(2);
	if(!TM_charaptr)
	{
		pthread_mutex_unlock((pthread_mutex_t *)0x8C89800);
		LRetErrInt(M_Script_Lua, 0, "ERR: CHAR_getLinkChar");
	}
	//清空資料
	API_CHAR_cleanUpChar(TM_charaptr);

	//加載指定的LUA腳本文件
	NPC_Lua_DoFile(_DoFile);
	//取得腳本中定義的初始化函數指針
	lua_getglobal(M_Script_Lua, _InitFuncName);

	if(lua_type(M_Script_Lua, -1) != LUA_TFUNCTION)
	{
		char NPC_Lua_Create_Err_Message[256];
		sprintf(NPC_Lua_Create_Err_Message, "NPC_Lua_Create err: 無法獲取初始化函數指針: %s\n", _InitFuncName);
		print(NPC_Lua_Create_Err_Message);
		lua_pop(M_Script_Lua, 1);
		pthread_mutex_unlock((pthread_mutex_t *)0x8C89800);
		LRetErrInt(M_Script_Lua, 0, "無法獲取初始化函數指針。");
	}else
	{
		//保存函數指針
		lua_pop(M_Script_Lua, 1);
		strcpy_s(CHAR_DATA_EXTEND[*(int*)(TM_charaptr+4)].functable[CHAR_INITFUNC].string, sizeof(CHAR_DATA_EXTEND[*(int*)(TM_charaptr+4)].functable[CHAR_INITFUNC].string), _InitFuncName);
		*(int*)(TM_charaptr+5864) = (int)NPC_Lua_InitCallBack;
	}


	//初始化數據
	//整數
	*(int*)(TM_charaptr + 0) = 1; //use
	*(int*)(TM_charaptr + 12) = 2; //type, 2為npc
	*(int*)(TM_charaptr + 16) = 100000; //BASEIMAGENUMBER
	*(int*)(TM_charaptr + 20) = 100000; //BASEBASEIMAGENUMBER
	*(int*)(TM_charaptr + 24) = 0; //mapid
	*(int*)(TM_charaptr + 28) = 777; //floorid
	*(int*)(TM_charaptr + 32) = 20; //x
	*(int*)(TM_charaptr + 36) = 90; //y
	*(int*)(TM_charaptr + 40) = 3; //direction
	//*(int*)(TM_charaptr + 1556) = 2; //Unknown, something relating to walk
	*(int*)(TM_charaptr + 1560) = 1; //NPC種類
	//字串
	strcpy((char*)(TM_charaptr + 648), "Shen"); //Name
	//執行初始化事件
	API_CHAR_doInitEvent(TM_charaptr);
	//關聯Object
	TM_objindex = API_initObjectFromObjectMember(1, TM_charaptr, *(int*)(TM_charaptr + 24), *(int*)(TM_charaptr + 28), *(int*)(TM_charaptr + 32), *(int*)(TM_charaptr + 36)); //a1類型(NPC:1), a2:Char_index, a3.4地圖, a5.6座標, 返回obj_index
	if(TM_objindex == -1)
	{
		API_CHAR_endCharOneArray(TM_charaptr);
		pthread_mutex_unlock((pthread_mutex_t *)0x8C89800);
		LRetErrInt(M_Script_Lua, 0, "無法實例化NPC對象。");
	}
	*(int*)(TM_charaptr + 1360) = TM_objindex;
	//發送資料給玩家
	API_MAP_sendAroundMapdata(*(int*)(TM_charaptr + 24), *(int*)(TM_charaptr + 28), *(int*)(TM_charaptr + 32), *(int*)(TM_charaptr + 36));
	API_CHAR_sendWatchEvent(TM_objindex, 0, 0, 0, 1);
	API_CHAR_sendCToArroundCharacter(TM_objindex);
		
	pthread_mutex_unlock((pthread_mutex_t *)0x8C89800);
	int TM_charaIndex = API_CHAR_getCharaIndex(TM_charaptr);
	LRetInt(M_Script_Lua, TM_charaIndex);
}

//刪除NPC 傳入NPC唯一索引
int NPC_Lua_Del(int charaIndex)
{
	int charaptr = API_GetCharaPtrFromCharaIndex(charaIndex);
	return API_CHAR_CharaDelete(charaptr);
}


int NPC_Lua_GetFuncPoint(lua_State *_NLL)
{
	CheckEx2(_NLL, 2, LUA_MINSTACK);
	char *TM_DoFile = lua_tostring(_NLL, 1);
	char *TM_FuncName = lua_tostring(_NLL, 2);

	if(TM_DoFile != NULL)
	{
		NPC_Lua_DoFile(TM_DoFile);
	}

	if(TM_FuncName == NULL)
	{
		LRetErrInt(_NLL , -1, "函數名不能為空");
	}

	lua_getglobal(_NLL, TM_FuncName);
	
	if(lua_type(_NLL, -1) != LUA_TFUNCTION)
	{
		LRetErrInt(_NLL , -2, "無法獲取函數指針。");
	}
	LRetInt(_NLL, 1);
}

//////////////////////////////////////////////////////////////////////////////
//擴展類型接口函數
//NTInt
int NPC_Lua_NTInt_New(lua_State *_NLL)
{
	CheckEx(_NLL, 1);

	int TM_Len = luaL_checkint(_NLL, 1);
	if(TM_Len <= 0)
	{
		LRetErrInt(_NLL, -1, "大小不能為0。");
	}

	size_t TM_Bytes = sizeof(size_t) + ( sizeof(int) * TM_Len );
	PARRAY_NTINT TM_Point = (PARRAY_NTINT *)lua_newuserdata(_NLL, TM_Bytes);
	
	if(TM_Point == NULL)
	{
		LRetErrInt(_NLL, -2, "實例化失敗，不能申請內存。");
	}

	luaL_getmetatable(_NLL, "Array.NTInt");
	lua_setmetatable(_NLL, -2);

	TM_Point->Size = TM_Len;

	LRet(1);
}

int NPC_Lua_NTInt_Get(lua_State *_NLL)
{
	CheckEx(_NLL, 2);

	PARRAY_NTINT TM_Point = luaL_checkudata(_NLL, 1, "Array.NTInt");

	if(TM_Point == NULL)
	{
		luaL_argerror(_NLL, 1, "不是 Array.NTInt 數據。");
	}

	int TM_Index = (int)lua_tointeger(_NLL, 2);
	
	if(TM_Index < 1 || TM_Index > TM_Point->Size)
	{
		luaL_argerror(_NLL, 1, "超出數據範圍，不允許\操作。");
	}

	TM_Index--;

	LRetInt(_NLL, TM_Point->Num[TM_Index]);
}

int NPC_Lua_NTInt_Set(lua_State *_NLL)
{
	CheckEx(_NLL, 3);
	
	PARRAY_NTINT TM_Point = luaL_checkudata(_NLL, 1, "Array.NTInt");
	
	if(TM_Point == NULL)
	{
		luaL_argerror(_NLL, 1, "不是 Array.NTInt 數據。");
	}

	int TM_Index = (int)lua_tointeger(_NLL, 2);
	
	if(TM_Index < 1 || TM_Index > TM_Point->Size)
	{
		luaL_argerror(_NLL, 1, "超出數據範圍，不允許\操作。");
	}
	TM_Index--;

	int TM_Num = (int)lua_tointeger(_NLL, 3);

	TM_Point->Num[TM_Index] = TM_Num;

	LRetNull(_NLL);
}

int NPC_Lua_NTInt_Len(lua_State *_NLL)
{
	CheckEx(_NLL, 1);
	
	PARRAY_NTINT TM_Point = luaL_checkudata(_NLL, 1, "Array.NTInt");

	if(TM_Point == NULL)
	{
		luaL_argerror(_NLL, 1, "不是 Array.NTInt 數據。");
	}

	LRetInt(_NLL, TM_Point->Size);
}

#endif //#ifdef _JZ_NEWSCRIPT_LUA
