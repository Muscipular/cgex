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
//#ifdef _SAF_PET_EVO
//#include "enemy.h"
//#include "readmap.h"
#include "item.h"
//#endif
#include "cg_api.h"
#ifdef _JZ_NEWSCRIPT_LUA

//////////////////////////////////////////////////////////////////////////////
//任務旗標
int NPC_Lua_Char_NowEvent(lua_State *_NLL)
{
	CheckEx2(_NLL, 2, 3);
	CheckIndexNull(_NLL, 1);
	int TM_Top = lua_gettop(_NLL);
	int TM_Index = (int)lua_tointeger(_NLL, 1);
	int TM_Ptr = API_GetCharaPtrFromCharaIndex(TM_Index);
	int TM_EveNo = (int)lua_tointeger(_NLL, 2);

	//設置任務旗標
	if(TM_Top >= 3)
	{
		int TM_Option = (int)lua_tointeger(_NLL, 3);
		if(TM_Option == 0)
		{
			int point=0;
			int array;
			int shift;
			if(TM_EveNo<0 || TM_EveNo>=256)
				LRetErrInt(_NLL , -1, "任務號錯誤。");
			array = TM_EveNo / 32;
			shift = TM_EveNo % 32;
			point = *(int *)(TM_Ptr + 368 + 4*array);
			point = point & ((1<<shift)^(-1));
			*(int *)(TM_Ptr + 368 + 4*array) = point;
		}else
		{
			int point=0;
			int array;
			int shift;
			if(TM_EveNo<0 || TM_EveNo>=256)
				LRetErrInt(_NLL , -1, "任務號錯誤。");
			array = TM_EveNo / 32;
			shift = TM_EveNo % 32;
			point = *(int *)(TM_Ptr + 368 + 4*array);
			point = point | (1<<shift);
			*(int *)(TM_Ptr + 368 + 4*array) = point;
		}
		LRetInt(_NLL, 0);
	}else{
	//查詢任務旗標
		int point=0;
		int array;
		int shift;
		if(TM_EveNo<0 || TM_EveNo>=256)
			LRetErrInt(_NLL , -1, "任務號錯誤。");
		array = TM_EveNo / 32;
		shift = TM_EveNo % 32;
		point = *(int *)(TM_Ptr + 368 + 4*array);
		int ret = 0;
		if( (point & (1<<shift))  == (1<<shift)){
			ret = 1;
		}
		LRetInt(_NLL, ret);
	}
}

int NPC_Lua_Char_EndEvent(lua_State *_NLL)
{
	CheckEx2(_NLL, 2, 3);
	CheckIndexNull(_NLL, 1);
	int TM_Top = lua_gettop(_NLL);
	int TM_Index = (int)lua_tointeger(_NLL, 1);
	int TM_Ptr = API_GetCharaPtrFromCharaIndex(TM_Index);
	int TM_EveNo = (int)lua_tointeger(_NLL, 2);

	//設置任務旗標
	if(TM_Top >= 3)
	{
		int TM_Option = (int)lua_tointeger(_NLL, 3);
		if(TM_Option == 0)
		{
			int point=0;
			int array;
			int shift;
			if(TM_EveNo<0 || TM_EveNo>=256)
				LRetErrInt(_NLL , -1, "任務號錯誤。");
			array = TM_EveNo / 32;
			shift = TM_EveNo % 32;
			point = *(int *)(TM_Ptr + 336 + 4*array);
			point = point & ((1<<shift)^(-1));
			*(int *)(TM_Ptr + 336 + 4*array) = point;
		}else
		{
			int point=0;
			int array;
			int shift;
			if(TM_EveNo<0 || TM_EveNo>=256)
				LRetErrInt(_NLL , -1, "任務號錯誤。");
			array = TM_EveNo / 32;
			shift = TM_EveNo % 32;
			point = *(int *)(TM_Ptr + 336 + 4*array);
			point = point | (1<<shift);
			*(int *)(TM_Ptr + 336 + 4*array) = point;
		}
		LRetInt(_NLL, 0);
	}else{
	//查詢任務旗標
		int point=0;
		int array;
		int shift;
		if(TM_EveNo<0 || TM_EveNo>=256)
			LRetErrInt(_NLL , -1, "任務號錯誤。");
		array = TM_EveNo / 32;
		shift = TM_EveNo % 32;
		point = *(int *)(TM_Ptr + 336 + 4*array);
		int ret = 0;
		if( (point & (1<<shift))  == (1<<shift)){
			ret = 1;
		}
		LRetInt(_NLL, ret);
	}
}

/*
//設置數據的接口
int NPC_Lua_Char_ClrEvtEnd(lua_State *_NLL)
{
	CheckEx2(_NLL, 2, LUA_MINSTACK);
	CheckIndexNull(_NLL, 1);
	int TM_Index = (int)lua_tointeger(_NLL, 1);
	int TM_Max = lua_gettop(_NLL);
	int TM_EveNo = -1;
	int i = 0;
	for(i = 2; i <= TM_Max; i++)
	{
		TM_EveNo = (int)lua_tointeger(_NLL, i);
		NPC_EndEventSetFlgCls(TM_Index, TM_EveNo);
	}

	LRetInt(_NLL, TM_EveNo);
}

int NPC_Lua_Char_ClrEvtNow(lua_State *_NLL)
{
	CheckEx2(_NLL, 2, LUA_MINSTACK);
	CheckIndexNull(_NLL, 1);
	int TM_Index = (int)lua_tointeger(_NLL, 1);
	int TM_Max = lua_gettop(_NLL);
	int TM_EveNo = -1;
	int i = 0;
	for(i = 2; i <= TM_Max; i++)
	{
		TM_EveNo = (int)lua_tointeger(_NLL, i);
		NPC_NowEventSetFlgCls(TM_Index, TM_EveNo);
	}
	LRetInt(_NLL, TM_EveNo);
}

int NPC_Lua_Char_ClrEvt(lua_State *_NLL)
{
	CheckEx2(_NLL, 2, LUA_MINSTACK);
	CheckIndexNull(_NLL, 1);
	int TM_Index = (int)lua_tointeger(_NLL, 1);
	int TM_Max = lua_gettop(_NLL);
	int TM_EveNo = -1;
	int i = 0;
	for(i = 2; i <= TM_Max; i++)
	{
		TM_EveNo = (int)lua_tointeger(_NLL, i);
		NPC_NowEndEventSetFlgCls(TM_Index, TM_EveNo);
	}
	LRetInt(_NLL, TM_EveNo);
}

int NPC_Lua_Char_SetEvtEnd(lua_State *_NLL)
{
	CheckEx2(_NLL, 2, LUA_MINSTACK);
	CheckIndexNull(_NLL, 1);
	int TM_Index = (int)lua_tointeger(_NLL, 1);
	int TM_Max = lua_gettop(_NLL);
	int TM_EveNo = -1;
	int i = 0;
	for(i = 2; i <= TM_Max; i++)
	{
		TM_EveNo = (int)lua_tointeger(_NLL, i);
		NPC_EventSetFlg(TM_Index, TM_EveNo);
	}

	LRetInt(_NLL, TM_EveNo);
}

int NPC_Lua_Char_SetEvtNow(lua_State *_NLL)
{
	CheckEx2(_NLL, 2, LUA_MINSTACK);
	CheckIndexNull(_NLL, 1);
	int TM_Index = (int)lua_tointeger(_NLL, 1);
	int TM_Max = lua_gettop(_NLL);
	int TM_EveNo = -1;
	int i = 0;
	for(i = 2; i <= TM_Max; i++)
	{
		TM_EveNo = (int)lua_tointeger(_NLL, i);
		NPC_NowEventSetFlg(TM_Index, TM_EveNo);
	}

	LRetInt(_NLL, TM_EveNo);
}

int NPC_Lua_Char_IsEventEnd(lua_State *_NLL)
{
	CheckEx(_NLL, 2);
	CheckIndexNull(_NLL, 1);
	int TM_Index = (int)lua_tointeger(_NLL, 1);
	int TM_EventNo = (int)lua_tointeger(_NLL, 2);
	
	BOOL TM_Ret = NPC_EventCheckFlg(TM_Index, TM_EventNo);

	LRetBool(_NLL, TM_Ret);
}

int NPC_Lua_Char_IsEventNow(lua_State *_NLL)
{
	CheckEx(_NLL, 2);
	CheckIndexNull(_NLL, 1);
	int TM_Index = (int)lua_tointeger(_NLL, 1);
	int TM_EventNo = (int)lua_tointeger(_NLL, 2);
	
	BOOL TM_Ret = NPC_NowEventCheckFlg(TM_Index, TM_EventNo);

	LRetBool(_NLL, TM_Ret);
}
*/

int NPC_Lua_Char_SetData(lua_State *_NLL)
{
	CheckEx(_NLL, 3);
	CheckIndexNull(_NLL, 1);
	int TM_Index = (int)lua_tointeger(_NLL, 1);
	int TM_ptr = API_GetCharaPtrFromCharaIndex(TM_Index);
	int TM_Flg = (int)lua_tointeger(_NLL, 2);

	if(TM_Flg >= 0)
	{
		if(TM_Flg < LUA_DATALINE1)
		{
			TM_Flg -= LUA_DATALINE0;
			int TM_IntVal = (int)lua_tointeger(_NLL, 3);
			*(int*)(TM_ptr + (TM_Flg+3)*4) = TM_IntVal;
			LRetInt(_NLL, 1);

		}else if(TM_Flg < LUA_DATALINE2)
		{
			TM_Flg -= LUA_DATALINE1;
			char *TM_CharPoint = (char *)lua_tostring(_NLL, 3);
			strcpy_s((char*)(TM_ptr + 648 + 32*TM_Flg), 32, TM_CharPoint);
			LRetInt(_NLL, 1);
			
/*
		}else if(TM_Flg < LUA_DATALINE3)
		{
			TM_Flg -= LUA_DATALINE2;
			if(TM_Flg == CHAR_WORKOBJINDEX || TM_Flg == CHAR_WORKACTION)
			{
				LRetInt(_NLL, 0);
			}
			int TM_WorkIntVal = (int)lua_tointeger(_NLL, 3);
			int TM_RetInt = CHAR_setWorkInt(TM_Index, TM_Flg, TM_WorkIntVal);
			LRetInt(_NLL, TM_RetInt);
		}else if(TM_Flg < LUA_DATALINE4)
		{
			TM_Flg -= LUA_DATALINE3;
			char *TM_WorkCharPoint = (char *)lua_tostring(_NLL, 3);
			BOOL TM_RetBOOL = CHAR_setWorkChar(TM_Index, TM_Flg, TM_WorkCharPoint);
			LRetBool(_NLL, TM_RetBOOL);
*/
		}else if(TM_Flg < LUA_DATALINE5)
		{
			TM_Flg -= LUA_DATALINE4;
			BOOL TM_BOOLVal = (BOOL)lua_toboolean(_NLL, 3);
			int TM_RetInt = API_CHAR_setFlg((int)"npc_lua_char.c", 0, TM_ptr, TM_Flg, TM_BOOLVal);
			LRetInt(_NLL, TM_RetInt);
		}else if(TM_Flg < LUA_DATALINE6)
		{
			TM_Flg -= LUA_DATALINE5;
			int TM_IntVal = (int)lua_tointeger(_NLL, 3);
			*(int*)(TM_ptr + TM_Flg) = TM_IntVal;
			LRetInt(_NLL, 1);
		}else
		{
			LRetErrNull(_NLL, "傳入的標誌是錯誤的。");
		}
	}
	LRetErrNull(_NLL, "傳入的標誌是錯誤的。");
}

//////////////////////////////////////////////////////////////////////////////
//事件設置的接口
int NPC_Lua_Char_SetWalkPreEvent(lua_State *_NLL)
{
	CheckEx(_NLL, 3);
	CheckIndexNull(_NLL, 3);
	int TM_Index = (int)lua_tointeger(_NLL, 3);
	int TM_ptr = API_GetCharaPtrFromCharaIndex(TM_Index);

	if(!API_CHAR_CheckCharPointer(TM_ptr))
	{
		LRetErrInt(_NLL , -1, "傳入的對象索引是無效的。");
	}
	
	int TM_Ret = NPC_Lua_GetFuncPoint(_NLL);

	if(lua_tointeger(_NLL, -1) > 0)
	{
		strcpy_s(CHAR_DATA_EXTEND[*(int*)(TM_ptr+4)].functable[CHAR_WALKPREFUNC].string, sizeof(CHAR_DATA_EXTEND[*(int*)(TM_ptr+4)].functable[CHAR_WALKPREFUNC].string), lua_tostring(_NLL, 2));
		*(int*)(TM_ptr+5868) = (int)NPC_Lua_WalkPreCallBack;
	}else{
		CHAR_DATA_EXTEND[*(int*)(TM_ptr+4)].functable[CHAR_WALKPREFUNC].string[0] = 0;
		*(int*)(TM_ptr+5868) = 0;
	}
	return TM_Ret;
}

int NPC_Lua_Char_SetWalkPostEvent(lua_State *_NLL)
{
	CheckEx(_NLL, 3);
	CheckIndexNull(_NLL, 3);
	int TM_Index = (int)lua_tointeger(_NLL, 3);
	int TM_ptr = API_GetCharaPtrFromCharaIndex(TM_Index);

	if(!API_CHAR_CheckCharPointer(TM_ptr))
	{
		LRetErrInt(_NLL , -1, "傳入的對象索引是無效的。");
	}
	
	int TM_Ret = NPC_Lua_GetFuncPoint(_NLL);

	if(lua_tointeger(_NLL, -1) > 0)
	{
		strcpy_s(CHAR_DATA_EXTEND[*(int*)(TM_ptr+4)].functable[CHAR_WALKPOSTFUNC].string, sizeof(CHAR_DATA_EXTEND[*(int*)(TM_ptr+4)].functable[CHAR_WALKPOSTFUNC].string), lua_tostring(_NLL, 2));
		*(int*)(TM_ptr+5872) = (int)NPC_Lua_WalkPostCallBack;
	}else{
		CHAR_DATA_EXTEND[*(int*)(TM_ptr+4)].functable[CHAR_WALKPOSTFUNC].string[0] = 0;
		*(int*)(TM_ptr+5872) = 0;
	}
	return TM_Ret;
}

/*
int NPC_Lua_Char_SetPreOverEvent(lua_State *_NLL)
{
	CheckEx(_NLL, 3);
	CheckIndexNull(_NLL, 3);
	int TM_index = (int)lua_tointeger(_NLL, 3);

	Char *TM_char = CHAR_getCharPointer(TM_index);

	if(TM_char == NULL)
	{
		LRetErrInt(_NLL , -1, "傳入的索引是無效的。");
	}
	int TM_Ret = NPC_Lua_GetFuncPoint(_NLL);
	
	if(lua_tointeger(_NLL, -1) > 0)
	{
		if(TM_char->functable[CHAR_PREOVERFUNC] != (void *)NPC_Lua_PreOverCallBack)
		{
			if(TM_char->functable[CHAR_PREOVERFUNC] != NULL)
			{
				TM_char->sur_functable[CHAR_PREOVERFUNC] = TM_char->functable[CHAR_PREOVERFUNC];
				strcpy_s(TM_char->sur_charfunctable[CHAR_PREOVERFUNC].string, sizeof(TM_char->sur_charfunctable[CHAR_PREOVERFUNC].string), TM_char->charfunctable[CHAR_PREOVERFUNC].string);
			}else
			{
				TM_char->sur_functable[CHAR_PREOVERFUNC] = (void *)NULL;
				TM_char->sur_charfunctable[CHAR_PREOVERFUNC].string[0] = '\0';
			}
	
			TM_char->functable[CHAR_PREOVERFUNC] = (void *)NPC_Lua_PreOverCallBack;
			strcpy_s(TM_char->lua_charfunctable[CHAR_PREOVERFUNC].string, sizeof(TM_char->lua_charfunctable[CHAR_PREOVERFUNC].string), lua_tostring(_NLL, 2));
			strcpy_s(TM_char->charfunctable[CHAR_PREOVERFUNC].string, sizeof(TM_char->charfunctable[CHAR_PREOVERFUNC].string), FUNCNAME_PREOVERCALLBACK);
		}
	}else
	{
		if(TM_char->functable[CHAR_PREOVERFUNC] == (void *)NPC_Lua_PreOverCallBack)
		{
			TM_char->lua_charfunctable[CHAR_PREOVERFUNC].string[0] = '\0';
			if(TM_char->sur_functable[CHAR_PREOVERFUNC] == NULL)
			{
				TM_char->functable[CHAR_PREOVERFUNC] = (void *)NULL;
				TM_char->charfunctable[CHAR_PREOVERFUNC].string[0] = '\0';
			}else
			{
				TM_char->functable[CHAR_PREOVERFUNC] = TM_char->sur_functable[CHAR_PREOVERFUNC];
				TM_char->sur_functable[CHAR_PREOVERFUNC] = (void *)NULL;
				strcpy_s(TM_char->charfunctable[CHAR_PREOVERFUNC].string, sizeof(TM_char->charfunctable[CHAR_PREOVERFUNC].string), TM_char->sur_charfunctable[CHAR_PREOVERFUNC].string);
			}
		}
	}
	return TM_Ret;
}
*/

int NPC_Lua_Char_SetPostOverEvent(lua_State *_NLL)
{
	CheckEx(_NLL, 3);
	CheckIndexNull(_NLL, 3);
	int TM_Index = (int)lua_tointeger(_NLL, 3);
	int TM_ptr = API_GetCharaPtrFromCharaIndex(TM_Index);

	if(!API_CHAR_CheckCharPointer(TM_ptr))
	{
		LRetErrInt(_NLL , -1, "傳入的對象索引是無效的。");
	}
	
	int TM_Ret = NPC_Lua_GetFuncPoint(_NLL);

	if(lua_tointeger(_NLL, -1) > 0)
	{
		strcpy_s(CHAR_DATA_EXTEND[*(int*)(TM_ptr+4)].functable[CHAR_POSTOVERFUNC].string, sizeof(CHAR_DATA_EXTEND[*(int*)(TM_ptr+4)].functable[CHAR_POSTOVERFUNC].string), lua_tostring(_NLL, 2));
		//運用擴展的結構
		CHAR_DATA_EXTEND[*(int*)(TM_ptr+4)].funcAddr[CHAR_POSTOVERFUNC] = (int)NPC_Lua_PostOverCallBack;
	}else{
		CHAR_DATA_EXTEND[*(int*)(TM_ptr+4)].functable[CHAR_POSTOVERFUNC].string[0] = 0;
		//運用擴展的結構
		CHAR_DATA_EXTEND[*(int*)(TM_ptr+4)].funcAddr[CHAR_POSTOVERFUNC] = 0;
	}
	return TM_Ret;
}

/*
int NPC_Lua_Char_SetWatchEvent(lua_State *_NLL)
{
	CheckEx(_NLL, 3);
	CheckIndexNull(_NLL, 3);
	int TM_index = (int)lua_tointeger(_NLL, 3);

	Char *TM_char = CHAR_getCharPointer(TM_index);

	if(TM_char == NULL)
	{
		LRetErrInt(_NLL , -1, "傳入的索引是無效的。");
	}
	int TM_Ret = NPC_Lua_GetFuncPoint(_NLL);
	
	if(lua_tointeger(_NLL, -1) > 0)
	{
		if(TM_char->functable[CHAR_WATCHFUNC] != (void *)NPC_Lua_WatchCallBack)
		{
			if(TM_char->functable[CHAR_WATCHFUNC] != NULL)
			{
				TM_char->sur_functable[CHAR_WATCHFUNC] = TM_char->functable[CHAR_WATCHFUNC];
				strcpy_s(TM_char->sur_charfunctable[CHAR_WATCHFUNC].string, sizeof(TM_char->sur_charfunctable[CHAR_WATCHFUNC].string), TM_char->charfunctable[CHAR_WATCHFUNC].string);
			}else
			{
				TM_char->sur_functable[CHAR_WATCHFUNC] = (void *)NULL;
				TM_char->sur_charfunctable[CHAR_WATCHFUNC].string[0] = '\0';
			}
	
			TM_char->functable[CHAR_WATCHFUNC] = (void *)NPC_Lua_WatchCallBack;
			strcpy_s(TM_char->lua_charfunctable[CHAR_WATCHFUNC].string, sizeof(TM_char->lua_charfunctable[CHAR_WATCHFUNC].string), lua_tostring(_NLL, 2));
			strcpy_s(TM_char->charfunctable[CHAR_WATCHFUNC].string, sizeof(TM_char->charfunctable[CHAR_WATCHFUNC].string), FUNCNAME_WATCHCALLBACK);
		}
	}else
	{
		if(TM_char->functable[CHAR_WATCHFUNC] == (void *)NPC_Lua_WatchCallBack)
		{
			TM_char->lua_charfunctable[CHAR_WATCHFUNC].string[0] = '\0';
			if(TM_char->sur_functable[CHAR_WATCHFUNC] == NULL)
			{
				TM_char->functable[CHAR_WATCHFUNC] = (void *)NULL;
				TM_char->charfunctable[CHAR_WATCHFUNC].string[0] = '\0';
			}else
			{
				TM_char->functable[CHAR_WATCHFUNC] = TM_char->sur_functable[CHAR_WATCHFUNC];
				TM_char->sur_functable[CHAR_WATCHFUNC] = (void *)NULL;
				strcpy_s(TM_char->charfunctable[CHAR_WATCHFUNC].string, sizeof(TM_char->charfunctable[CHAR_WATCHFUNC].string), TM_char->sur_charfunctable[CHAR_WATCHFUNC].string);
			}
		}
	}
	return TM_Ret;
}
*/

int NPC_Lua_Char_SetLoopEvent(lua_State *_NLL)
{
	CheckEx(_NLL, 4);
	CheckIndexNull(_NLL, 3);
	int TM_Index = (int)lua_tointeger(_NLL, 3);
	int TM_ptr = API_GetCharaPtrFromCharaIndex(TM_Index);
	int TM_LoopInterval = (int)lua_tointeger(_NLL, 4);
	int TM_RetLoopInterval = -1;
	
	if(!API_CHAR_CheckCharPointer(TM_ptr))
	{
		LRetErrInt(_NLL , -1, "傳入的對象索引是無效的。");
	}
	int TM_Ret = NPC_Lua_GetFuncPoint(_NLL);

	if(lua_tointeger(_NLL, -1) > 0)
	{
		//循環時間
		TM_RetLoopInterval = *(int*)(TM_ptr+172);
		*(int*)(TM_ptr+172) = TM_LoopInterval;
		//循環函數
		strcpy_s(CHAR_DATA_EXTEND[*(int*)(TM_ptr+4)].functable[CHAR_LOOPFUNC].string, sizeof(CHAR_DATA_EXTEND[*(int*)(TM_ptr+4)].functable[CHAR_LOOPFUNC].string), lua_tostring(_NLL, 2));
		*(int*)(TM_ptr+5880) = (int)NPC_Lua_LoopCallBack;
	}else{
		//循環時間
		TM_RetLoopInterval = *(int*)(TM_ptr+172);
		*(int*)(TM_ptr+172) = 0;
		//循環函數
		CHAR_DATA_EXTEND[*(int*)(TM_ptr+4)].functable[CHAR_LOOPFUNC].string[0] = 0;
		*(int*)(TM_ptr+5880) = 0;
	}
	lua_pushinteger(_NLL, TM_RetLoopInterval);
	LRet(TM_Ret + 1);
}

int NPC_Lua_Char_SetTalkedEvent(lua_State *_NLL)
{
	CheckEx(_NLL, 3);
	CheckIndexNull(_NLL, 3);
	int TM_Index = (int)lua_tointeger(_NLL, 3);
	int TM_ptr = API_GetCharaPtrFromCharaIndex(TM_Index);

	if(!API_CHAR_CheckCharPointer(TM_ptr))
	{
		LRetErrInt(_NLL , -1, "傳入的對象索引是無效的。");
	}
	
	int TM_Ret = NPC_Lua_GetFuncPoint(_NLL);

	if(lua_tointeger(_NLL, -1) > 0)
	{
		strcpy_s(CHAR_DATA_EXTEND[*(int*)(TM_ptr+4)].functable[CHAR_TALKEDFUNC].string, sizeof(CHAR_DATA_EXTEND[*(int*)(TM_ptr+4)].functable[CHAR_TALKEDFUNC].string), lua_tostring(_NLL, 2));
		*(int*)(TM_ptr+5888) = (int)NPC_Lua_TalkedCallBack;
	}else{
		CHAR_DATA_EXTEND[*(int*)(TM_ptr+4)].functable[CHAR_TALKEDFUNC].string[0] = 0;
		*(int*)(TM_ptr+5888) = 0;
	}
	return TM_Ret;
}
/*
int NPC_Lua_Char_SetOFFEvent(lua_State *_NLL)
{
	CheckEx(_NLL, 3);
	CheckIndexNull(_NLL, 3);
	int TM_index = (int)lua_tointeger(_NLL, 3);

	Char *TM_char = CHAR_getCharPointer(TM_index);

	if(TM_char == NULL)
	{
		LRetErrInt(_NLL , -1, "傳入的索引是無效的。");
	}
	int TM_Ret = NPC_Lua_GetFuncPoint(_NLL);
	
	if(lua_tointeger(_NLL, -1) > 0)
	{
		if(TM_char->functable[CHAR_OFFFUNC] != (void *)NPC_Lua_OFFCallBack)
		{
			if(TM_char->functable[CHAR_OFFFUNC] != NULL)
			{
				TM_char->sur_functable[CHAR_OFFFUNC] = TM_char->functable[CHAR_OFFFUNC];
				strcpy_s(TM_char->sur_charfunctable[CHAR_OFFFUNC].string, sizeof(TM_char->sur_charfunctable[CHAR_OFFFUNC].string), TM_char->charfunctable[CHAR_OFFFUNC].string);
			}else
			{
				TM_char->sur_functable[CHAR_OFFFUNC] = (void *)NULL;
				TM_char->sur_charfunctable[CHAR_OFFFUNC].string[0] = '\0';
			}
	
			TM_char->functable[CHAR_OFFFUNC] = (void *)NPC_Lua_OFFCallBack;
			strcpy_s(TM_char->lua_charfunctable[CHAR_OFFFUNC].string, sizeof(TM_char->lua_charfunctable[CHAR_OFFFUNC].string), lua_tostring(_NLL, 2));
			strcpy_s(TM_char->charfunctable[CHAR_OFFFUNC].string, sizeof(TM_char->charfunctable[CHAR_OFFFUNC].string), FUNCNAME_OFFCALLBACK);
		}
	}else
	{
		if(TM_char->functable[CHAR_OFFFUNC] == (void *)NPC_Lua_OFFCallBack)
		{
			TM_char->lua_charfunctable[CHAR_OFFFUNC].string[0] = '\0';
			if(TM_char->sur_functable[CHAR_OFFFUNC] == NULL)
			{
				TM_char->functable[CHAR_OFFFUNC] = (void *)NULL;
				TM_char->charfunctable[CHAR_OFFFUNC].string[0] = '\0';
			}else
			{
				TM_char->functable[CHAR_OFFFUNC] = TM_char->sur_functable[CHAR_OFFFUNC];
				TM_char->sur_functable[CHAR_OFFFUNC] = (void *)NULL;
				strcpy_s(TM_char->charfunctable[CHAR_OFFFUNC].string, sizeof(TM_char->charfunctable[CHAR_OFFFUNC].string), TM_char->sur_charfunctable[CHAR_OFFFUNC].string);
			}
		}
	}
	return TM_Ret;
}

int NPC_Lua_Char_SetLookedEvent(lua_State *_NLL)
{
	CheckEx(_NLL, 3);
	CheckIndexNull(_NLL, 3);
	int TM_index = (int)lua_tointeger(_NLL, 3);

	Char *TM_char = CHAR_getCharPointer(TM_index);

	if(TM_char == NULL)
	{
		LRetErrInt(_NLL , -1, "傳入的索引是無效的。");
	}
	int TM_Ret = NPC_Lua_GetFuncPoint(_NLL);
	
	if(lua_tointeger(_NLL, -1) > 0)
	{
		if(TM_char->functable[CHAR_LOOKEDFUNC] != (void *)NPC_Lua_LookedCallBack)
		{
			if(TM_char->functable[CHAR_LOOKEDFUNC] != NULL)
			{
				TM_char->sur_functable[CHAR_LOOKEDFUNC] = TM_char->functable[CHAR_LOOKEDFUNC];
				strcpy_s(TM_char->sur_charfunctable[CHAR_LOOKEDFUNC].string, sizeof(TM_char->sur_charfunctable[CHAR_LOOKEDFUNC].string), TM_char->charfunctable[CHAR_LOOKEDFUNC].string);
			}else
			{
				TM_char->sur_functable[CHAR_LOOKEDFUNC] = (void *)NULL;
				TM_char->sur_charfunctable[CHAR_LOOKEDFUNC].string[0] = '\0';
			}
	
			TM_char->functable[CHAR_LOOKEDFUNC] = (void *)NPC_Lua_LookedCallBack;
			strcpy_s(TM_char->lua_charfunctable[CHAR_LOOKEDFUNC].string, sizeof(TM_char->lua_charfunctable[CHAR_LOOKEDFUNC].string), lua_tostring(_NLL, 2));
			strcpy_s(TM_char->charfunctable[CHAR_LOOKEDFUNC].string, sizeof(TM_char->charfunctable[CHAR_LOOKEDFUNC].string), FUNCNAME_LOOKEDCALLBACK);
		}
	}else
	{
		if(TM_char->functable[CHAR_LOOKEDFUNC] == (void *)NPC_Lua_LookedCallBack)
		{
			TM_char->lua_charfunctable[CHAR_LOOKEDFUNC].string[0] = '\0';
			if(TM_char->sur_functable[CHAR_LOOKEDFUNC] == NULL)
			{
				TM_char->functable[CHAR_LOOKEDFUNC] = (void *)NULL;
				TM_char->charfunctable[CHAR_LOOKEDFUNC].string[0] = '\0';
			}else
			{
				TM_char->functable[CHAR_LOOKEDFUNC] = TM_char->sur_functable[CHAR_LOOKEDFUNC];
				TM_char->sur_functable[CHAR_LOOKEDFUNC] = (void *)NULL;
				strcpy_s(TM_char->charfunctable[CHAR_LOOKEDFUNC].string, sizeof(TM_char->charfunctable[CHAR_LOOKEDFUNC].string), TM_char->sur_charfunctable[CHAR_LOOKEDFUNC].string);
			}
		}
	}
	return TM_Ret;
}

int NPC_Lua_Char_SetItemPutEvent(lua_State *_NLL)
{
	CheckEx(_NLL, 3);
	CheckIndexNull(_NLL, 3);
	int TM_index = (int)lua_tointeger(_NLL, 3);

	Char *TM_char = CHAR_getCharPointer(TM_index);

	if(TM_char == NULL)
	{
		LRetErrInt(_NLL , -1, "傳入的索引是無效的。");
	}
	int TM_Ret = NPC_Lua_GetFuncPoint(_NLL);
	
	if(lua_tointeger(_NLL, -1) > 0)
	{
		if(TM_char->functable[CHAR_ITEMPUTFUNC] != (void *)NPC_Lua_ItemPutCallBack)
		{
			if(TM_char->functable[CHAR_ITEMPUTFUNC] != NULL)
			{
				TM_char->sur_functable[CHAR_ITEMPUTFUNC] = TM_char->functable[CHAR_ITEMPUTFUNC];
				strcpy_s(TM_char->sur_charfunctable[CHAR_ITEMPUTFUNC].string, sizeof(TM_char->sur_charfunctable[CHAR_ITEMPUTFUNC].string), TM_char->charfunctable[CHAR_ITEMPUTFUNC].string);
			}else
			{
				TM_char->sur_functable[CHAR_ITEMPUTFUNC] = (void *)NULL;
				TM_char->sur_charfunctable[CHAR_ITEMPUTFUNC].string[0] = '\0';
			}
	
			TM_char->functable[CHAR_ITEMPUTFUNC] = (void *)NPC_Lua_ItemPutCallBack;
			strcpy_s(TM_char->lua_charfunctable[CHAR_ITEMPUTFUNC].string, sizeof(TM_char->lua_charfunctable[CHAR_ITEMPUTFUNC].string), lua_tostring(_NLL, 2));
			strcpy_s(TM_char->charfunctable[CHAR_ITEMPUTFUNC].string, sizeof(TM_char->charfunctable[CHAR_ITEMPUTFUNC].string), FUNCNAME_ITEMPUTCALLBACK);
		}
	}else
	{
		if(TM_char->functable[CHAR_ITEMPUTFUNC] == (void *)NPC_Lua_ItemPutCallBack)
		{
			TM_char->lua_charfunctable[CHAR_ITEMPUTFUNC].string[0] = '\0';
			if(TM_char->sur_functable[CHAR_ITEMPUTFUNC] == NULL)
			{
				TM_char->functable[CHAR_ITEMPUTFUNC] = (void *)NULL;
				TM_char->charfunctable[CHAR_ITEMPUTFUNC].string[0] = '\0';
			}else
			{
				TM_char->functable[CHAR_ITEMPUTFUNC] = TM_char->sur_functable[CHAR_ITEMPUTFUNC];
				TM_char->sur_functable[CHAR_ITEMPUTFUNC] = (void *)NULL;
				strcpy_s(TM_char->charfunctable[CHAR_ITEMPUTFUNC].string, sizeof(TM_char->charfunctable[CHAR_ITEMPUTFUNC].string), TM_char->sur_charfunctable[CHAR_ITEMPUTFUNC].string);
			}
		}
	}
	return TM_Ret;
}
*/

int NPC_Lua_Char_SetWindowTalkedEvent(lua_State *_NLL)
{
	CheckEx(_NLL, 3);
	CheckIndexNull(_NLL, 3);
	int TM_Index = (int)lua_tointeger(_NLL, 3);
	int TM_ptr = API_GetCharaPtrFromCharaIndex(TM_Index);

	if(!API_CHAR_CheckCharPointer(TM_ptr))
	{
		LRetErrInt(_NLL , -1, "傳入的對象索引是無效的。");
	}
	
	int TM_Ret = NPC_Lua_GetFuncPoint(_NLL);

	if(lua_tointeger(_NLL, -1) > 0)
	{
		strcpy_s(CHAR_DATA_EXTEND[*(int*)(TM_ptr+4)].functable[CHAR_WINDOWTALKEDFUNC].string, sizeof(CHAR_DATA_EXTEND[*(int*)(TM_ptr+4)].functable[CHAR_WINDOWTALKEDFUNC].string), lua_tostring(_NLL, 2));
		*(int*)(TM_ptr+5904) = (int)NPC_Lua_WindowTalkedCallBack;
	}else{
		CHAR_DATA_EXTEND[*(int*)(TM_ptr+4)].functable[CHAR_WINDOWTALKEDFUNC].string[0] = 0;
		*(int*)(TM_ptr+5904) = 0;
	}
	return TM_Ret;
}

/*

#ifdef _USER_CHARLOOPS
int NPC_Lua_Char_SetCharLoopsEvent(lua_State *_NLL)
{
	CheckEx(_NLL, 4);
	CheckIndexNull(_NLL, 3);
	int TM_index = (int)lua_tointeger(_NLL, 3);
	int TM_LoopInterval = (int)lua_tointeger(_NLL, 4);
	int TM_RetLoopInterval = -1;

	Char *TM_char = CHAR_getCharPointer(TM_index);

	if(TM_char == NULL)
	{
		LRetErrInt(_NLL , -1, "傳入的索引是無效的。");
	}
	int TM_Ret = NPC_Lua_GetFuncPoint(_NLL);

	if(lua_tointeger(_NLL, -1) > 0)
	{
		if(TM_char->functable[CHAR_LOOPFUNCTEMP1] != (void *)NPC_Lua_CharLoopsCallBack)
		{
			if(TM_char->functable[CHAR_LOOPFUNCTEMP1] != NULL)
			{
				TM_char->sur_functable[CHAR_LOOPFUNCTEMP1] = TM_char->functable[CHAR_LOOPFUNCTEMP1];
				strcpy_s(TM_char->sur_charfunctable[CHAR_LOOPFUNCTEMP1].string, sizeof(TM_char->sur_charfunctable[CHAR_LOOPFUNCTEMP1].string), TM_char->charfunctable[CHAR_LOOPFUNCTEMP1].string);
			}else
			{
				TM_char->sur_functable[CHAR_LOOPFUNCTEMP1] = (void *)NULL;
				TM_char->sur_charfunctable[CHAR_LOOPFUNCTEMP1].string[0] = '\0';
			}
			TM_RetLoopInterval = CHAR_getInt(TM_index, CHAR_LOOPINTERVAL);
			CHAR_setInt(TM_index, CHAR_LOOPINTERVAL, TM_LoopInterval);
			TM_char->functable[CHAR_LOOPFUNCTEMP1] = (void *)NPC_Lua_CharLoopsCallBack;
			strcpy_s(TM_char->lua_charfunctable[CHAR_LOOPFUNCTEMP1].string, sizeof(TM_char->lua_charfunctable[CHAR_LOOPFUNCTEMP1].string), lua_tostring(_NLL, 2));
			strcpy_s(TM_char->charfunctable[CHAR_LOOPFUNCTEMP1].string, sizeof(TM_char->charfunctable[CHAR_LOOPFUNCTEMP1].string), FUNCNAME_CHARLOOPSCALLBACK);
		}
	}else
	{
		if(TM_char->functable[CHAR_LOOPFUNCTEMP1] == (void *)NPC_Lua_CharLoopsCallBack)
		{
			TM_char->lua_charfunctable[CHAR_LOOPFUNCTEMP1].string[0] = '\0';
			if(TM_char->sur_functable[CHAR_LOOPFUNCTEMP1] == NULL)
			{
				CHAR_setInt(TM_index, CHAR_LOOPINTERVAL, -1);
				TM_char->functable[CHAR_LOOPFUNCTEMP1] = (void *)NULL;
				TM_char->charfunctable[CHAR_LOOPFUNCTEMP1].string[0] = '\0';
			}else
			{
				CHAR_setInt(TM_index, CHAR_LOOPINTERVAL, TM_LoopInterval);
				TM_char->functable[CHAR_LOOPFUNCTEMP1] = TM_char->sur_functable[CHAR_LOOPFUNCTEMP1];
				TM_char->sur_functable[CHAR_LOOPFUNCTEMP1] = (void *)NULL;
				strcpy_s(TM_char->charfunctable[CHAR_LOOPFUNCTEMP1].string, sizeof(TM_char->charfunctable[CHAR_LOOPFUNCTEMP1].string), TM_char->sur_charfunctable[CHAR_LOOPFUNCTEMP1].string);
			}
		}
	}
	lua_pushinteger(_NLL, TM_RetLoopInterval);
	LRet(TM_Ret + 1);
}

int NPC_Lua_Char_SetBattleProPertyEvent(lua_State *_NLL)
{
	CheckEx(_NLL, 3);
	CheckIndexNull(_NLL, 3);
	int TM_index = (int)lua_tointeger(_NLL, 3);

	Char *TM_char = CHAR_getCharPointer(TM_index);

	if(TM_char == NULL)
	{
		LRetErrInt(_NLL , -1, "傳入的索引是無效的。");
	}
	int TM_Ret = NPC_Lua_GetFuncPoint(_NLL);

	if(lua_tointeger(_NLL, -1) > 0)
	{
		if(TM_char->functable[CHAR_BATTLEPROPERTY] != (void *)NPC_Lua_BattleProPertyCallBack)
		{
			if(TM_char->functable[CHAR_BATTLEPROPERTY] != NULL)
			{
				TM_char->sur_functable[CHAR_BATTLEPROPERTY] = TM_char->functable[CHAR_BATTLEPROPERTY];
				strcpy_s(TM_char->sur_charfunctable[CHAR_BATTLEPROPERTY].string, sizeof(TM_char->sur_charfunctable[CHAR_BATTLEPROPERTY].string), TM_char->charfunctable[CHAR_BATTLEPROPERTY].string);
			}else
			{
				TM_char->sur_functable[CHAR_BATTLEPROPERTY] = (void *)NULL;
				TM_char->sur_charfunctable[CHAR_BATTLEPROPERTY].string[0] = '\0';
			}

			TM_char->functable[CHAR_BATTLEPROPERTY] = (void *)NPC_Lua_BattleProPertyCallBack;
			strcpy_s(TM_char->lua_charfunctable[CHAR_BATTLEPROPERTY].string, sizeof(TM_char->lua_charfunctable[CHAR_BATTLEPROPERTY].string), lua_tostring(_NLL, 2));
			strcpy_s(TM_char->charfunctable[CHAR_BATTLEPROPERTY].string, sizeof(TM_char->charfunctable[CHAR_BATTLEPROPERTY].string), FUNCNAME_BATTLEPROPERTYCALLBACK);
		}
	}else
	{
		if(TM_char->functable[CHAR_BATTLEPROPERTY] == (void *)NPC_Lua_BattleProPertyCallBack)
		{
			TM_char->lua_charfunctable[CHAR_BATTLEPROPERTY].string[0] = '\0';
			if(TM_char->sur_functable[CHAR_BATTLEPROPERTY] == NULL)
			{
				TM_char->functable[CHAR_BATTLEPROPERTY] = (void *)NULL;
				TM_char->charfunctable[CHAR_BATTLEPROPERTY].string[0] = '\0';
			}else
			{
				TM_char->functable[CHAR_BATTLEPROPERTY] = TM_char->sur_functable[CHAR_BATTLEPROPERTY];
				TM_char->sur_functable[CHAR_BATTLEPROPERTY] = (void *)NULL;
				strcpy_s(TM_char->charfunctable[CHAR_BATTLEPROPERTY].string, sizeof(TM_char->charfunctable[CHAR_BATTLEPROPERTY].string), TM_char->sur_charfunctable[CHAR_BATTLEPROPERTY].string);
			}
		}
	}
	return TM_Ret;
}
#endif

*/
//////////////////////////////////////////////////////////////////////////////
//獲取數據的接口
int NPC_Lua_Char_GetData(lua_State *_NLL)
{
	CheckEx(_NLL, 2);
	CheckIndexNull(_NLL, 1);
	int TM_Index = (int)lua_tointeger(_NLL, 1);
	int TM_ptr = API_GetCharaPtrFromCharaIndex(TM_Index);
	int TM_Flg = (int)lua_tointeger(_NLL, 2);

	if(TM_Flg >= 0)
	{
		if(TM_Flg < LUA_DATALINE1)
		{
			TM_Flg -= LUA_DATALINE0;
			int TM_RetInt = *(int*)(TM_ptr + (TM_Flg+3)*4);
			
			LRetInt(_NLL, TM_RetInt);

		}else if(TM_Flg < LUA_DATALINE2)
		{
			TM_Flg -= LUA_DATALINE1;
			char *TM_RetPoint = (char*)(TM_ptr + 648 + 32*TM_Flg);
			LRetMsg(_NLL, TM_RetPoint);
/*
		}else if(TM_Flg < LUA_DATALINE3)
		{
			TM_Flg -= LUA_DATALINE2;
			int TM_RetWorkInt = CHAR_getWorkInt(TM_Index, TM_Flg);
			LRetInt(_NLL, TM_RetWorkInt);
		}else if(TM_Flg < LUA_DATALINE4)
		{
			TM_Flg -= LUA_DATALINE3;
			char *TM_RetWorkPoint = CHAR_getWorkChar(TM_Index, TM_Flg);
			LRetMsg(_NLL, TM_RetWorkPoint);
*/
		}else if(TM_Flg < LUA_DATALINE5)
		{
			TM_Flg -= LUA_DATALINE4;
			BOOL TM_RetBOOL = API_CHAR_getFlg((int)"npc_lua_char.c", 0, TM_ptr, TM_Flg);
			LRetBool(_NLL, TM_RetBOOL);
		}else if(TM_Flg < LUA_DATALINE6)
		{
			TM_Flg -= LUA_DATALINE5;
			int TM_RetInt = *(int*)(TM_ptr + TM_Flg);
			LRetInt(_NLL, TM_RetInt);
		}else
		{
			LRetErrNull(_NLL, "傳入的標誌是錯誤的。");
		}
	}
	LRetErrNull(_NLL, "傳入的標誌是錯誤的。");
}

int NPC_Lua_Char_FindItemId(lua_State *_NLL)
{
	CheckEx(_NLL, 2);
	CheckIndexNull(_NLL, 1);
	int TM_Index = (int)lua_tointeger(_NLL, 1);
	int TM_Ptr = API_GetCharaPtrFromCharaIndex(TM_Index);
	int TM_ItemId = (int)lua_tointeger(_NLL, 2);
	int TM_ItemIndex = -1;
	int i = 0;
	
	if(!API_CHAR_CheckCharPointer(TM_Ptr))
	{
		LRetErrInt(_NLL , -1, "傳入的對象索引是無效的。");
	}

	for( i = 0 ; i<28 ; i++ )
	{
		TM_ItemIndex = API_CHAR_getItemIndex(TM_Ptr, i);
		if( API_ITEM_CHECKINDEX(TM_ItemIndex) == 0 )continue;
		if( API_ITEM_getInt(TM_ItemIndex, ITEM_ID) == TM_ItemId) {
			LRetInt(_NLL, i);
		}
	}
	LRetErrInt(_NLL, -2, "找不到指定道具。");
}


int NPC_Lua_Char_FindPetEnemyId(lua_State *_NLL)
{
	CheckEx(_NLL, 2);
	CheckIndexNull(_NLL, 1);
	int TM_Index = (int)lua_tointeger(_NLL, 1);
	int TM_Ptr = API_GetCharaPtrFromCharaIndex(TM_Index);
	int TM_PetId = (int)lua_tointeger(_NLL, 2);
	int i = 0;

	if(!API_CHAR_CheckCharPointer(TM_Ptr))
	{
		LRetErrInt(_NLL , -1, "傳入的對象索引是無效的。");
	}

	for( i = 0 ; i<5 ; i++ )
	{
		int TM_PetPtr = API_CHAR_getHavePetCharPointer(TM_Ptr, i);
		if( ! API_CHAR_CheckCharPointer(TM_PetPtr) ) continue;
		if( *(int *)(TM_PetPtr + 284) == TM_PetId) {
			LRetInt(_NLL, i);
		}
	}
	LRetErrInt(_NLL, -2, "找不到指定寵物。");
}

/*
int NPC_Lua_Char_GetItemId(lua_State *_NLL)
{
	CheckEx(_NLL, 2);
	CheckIndexNull(_NLL, 1);
	int TM_Index = (int)lua_tointeger(_NLL, 1);
	int TM_Pos = (int)lua_tointeger(_NLL, 2);

	if(!CHAR_CHECKINDEX(TM_Index))
	{
		LRetErrInt(_NLL, -1, "傳入的索引是無效的。");
	}

	if(TM_Pos >= 0 && TM_Pos < CHAR_MAXITEMHAVE)
	{
		int TM_ItemIndex = CHAR_getItemIndex(TM_Index, TM_Pos);
		
		if( ITEM_CHECKINDEX(TM_ItemIndex) == FALSE ) LRetErrInt(_NLL, -2, "該道具欄沒有道具。");
		LRetInt(_NLL, ITEM_getInt(TM_ItemIndex, ITEM_ID));
	}
	LRetErrInt(_NLL, -3, "傳入的位置超出道具欄範圍。");
}
*/

int NPC_Lua_Char_GetItemIndex(lua_State *_NLL)
{
	CheckEx(_NLL, 2);
	CheckIndexNull(_NLL, 1);
	int TM_Index = (int)lua_tointeger(_NLL, 1);
	int TM_Ptr = API_GetCharaPtrFromCharaIndex(TM_Index);
	int TM_Pos = (int)lua_tointeger(_NLL, 2);

	if(!API_CHAR_CheckCharPointer(TM_Ptr))
	{
		LRetErrInt(_NLL , -1, "傳入的對象索引是無效的。");
	}

	if(TM_Pos >= 0 && TM_Pos < 28)
	{
		int TM_ItemIndex = API_CHAR_getItemIndex(TM_Ptr, TM_Pos);
		
		if( API_ITEM_CHECKINDEX(TM_ItemIndex) == 0 ) LRetErrInt(_NLL, -2, "該道具欄沒有道具。");
		LRetInt(_NLL, TM_ItemIndex);
	}
	LRetErrInt(_NLL, -3, "傳入的位置超出道具欄範圍。");
}



int NPC_Lua_Char_GetPetEnemyId(lua_State *_NLL)
{
	CheckEx(_NLL, 2);
	CheckIndexNull(_NLL, 1);
	int TM_Index = (int)lua_tointeger(_NLL, 1);
	int TM_Ptr = API_GetCharaPtrFromCharaIndex(TM_Index);
	int TM_Pos = (int)lua_tointeger(_NLL, 2);

	if(!API_CHAR_CheckCharPointer(TM_Ptr))
	{
		LRetErrInt(_NLL , -1, "傳入的對象索引是無效的。");
	}

	if(TM_Pos >= 0 && TM_Pos < 5)
	{
		int TM_PetPtr = API_CHAR_getHavePetCharPointer(TM_Ptr, TM_Pos);
		if( !API_CHAR_CheckCharPointer(TM_PetPtr) ) LRetErrInt(_NLL, -2, "該寵物欄沒有寵物。");
		int PetEnemyId = *(int *)(TM_PetPtr + 284);
		LRetInt(_NLL, PetEnemyId);
	}
	LRetErrInt(_NLL, -3, "傳入的位置超出寵物欄範圍。");
}

int NPC_Lua_Char_GetPetIndex(lua_State *_NLL)
{
	CheckEx(_NLL, 2);
	CheckIndexNull(_NLL, 1);
	int TM_Index = (int)lua_tointeger(_NLL, 1);
	int TM_Ptr = API_GetCharaPtrFromCharaIndex(TM_Index);
	int TM_Pos = (int)lua_tointeger(_NLL, 2);

	if(!API_CHAR_CheckCharPointer(TM_Ptr))
	{
		LRetErrInt(_NLL , -1, "傳入的對象索引是無效的。");
	}

	if(TM_Pos >= 0 && TM_Pos < 5)
	{
		int TM_PetPtr = API_CHAR_getHavePetCharPointer(TM_Ptr, TM_Pos);
		
		if( !API_CHAR_CheckCharPointer(TM_PetPtr) ) LRetErrInt(_NLL, -2, "該寵物欄沒有寵物。");
		int PetIndex = API_CHAR_getCharaIndex(TM_PetPtr);
		LRetInt(_NLL, PetIndex);
	}
	LRetErrInt(_NLL, -3, "傳入的位置超出寵物欄範圍。");
}


int NPC_Lua_Char_GetTeamIndex(lua_State *_NLL)
{
	CheckEx(_NLL, 2);
	CheckIndexNull(_NLL, 1);
	int TM_Index = (int)lua_tointeger(_NLL, 1);
	int TM_Ptr = API_GetCharaPtrFromCharaIndex(TM_Index);
	int TM_Pos = (int)lua_tointeger(_NLL, 2);

	if(!API_CHAR_CheckCharPointer(TM_Ptr))
	{
		LRetErrInt(_NLL , -1, "傳入的對象索引是無效的。");
	}

	if(TM_Pos >= 1 && TM_Pos < 5)
	{
		int TM_ParPtr = *(int *)(TM_Ptr + 2132 + 4*TM_Pos);

		if( !API_CHAR_CheckCharPointer(TM_ParPtr) ) LRetErrInt(_NLL, -2, "該位置沒有隊員。");
		
		int TM_ParIndex = API_CHAR_getCharaIndex(TM_ParPtr);
		LRetInt(_NLL, TM_ParIndex);
	}
	LRetErrInt(_NLL, -3, "傳入的位置超出隊員位置範圍。");
}

/*
#ifdef _SAF_PET_EVO
int NPC_Lua_Char_ReLoadPetBASE(lua_State *_NLL)
{
	int petindex = (int)lua_tointeger(_NLL, 1);
	int charaindex = (int)lua_tointeger(_NLL, 2);
	petindex = Enemy_Evolution(petindex,charaindex,CHAR_getChar(petindex,CHAR_PETID),-1);
	LRetInt(_NLL, petindex );
    return petindex;
}

int NPC_Lua_Char_PetEvolution(lua_State *_NLL)
{
	int petindex = (int)lua_tointeger(_NLL, 1);
	int charaindex = (int)lua_tointeger(_NLL, 2);
	int evobaseid = (int)lua_tointeger(_NLL, 3);
	int image = (int)lua_tointeger(_NLL, 4);
	if(evobaseid < 0){
		LRetInt(_NLL, -1);
		return -1;
	}
	petindex = Enemy_Evolution(petindex,charaindex,evobaseid,image);
	LRetInt(_NLL, petindex );
    return petindex;
}
#endif
*/
#endif //#ifdef _JZ_NEWSCRIPT_LUA
