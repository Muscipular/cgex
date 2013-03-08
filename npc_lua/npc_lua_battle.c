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

#ifdef _JZ_NEWSCRIPT_LUA

int NPC_Lua_Battle_GetPlayIndex(lua_State *_NLL)
{
	CheckEx(_NLL, 3);
	//assert(BattleArray != NULL);
	CheckBattleIndexNull(_NLL, 1);
	int TM_battleindex = (int)lua_tointeger(_NLL, 1);
	int TM_side = (int)lua_tointeger(_NLL, 2);
	int TM_num = (int)lua_tointeger(_NLL, 3);
	
	if( API_BATTLE_CHECKINDEX( TM_battleindex ) == 0 )
	{
		LRetErrInt(_NLL , -2, "傳入的索引是無效的。");
	}

	int TM_Battle = *(int*)0x10D69C10 + 5100 * TM_battleindex;

	if(TM_Battle == NULL)
	{
		LRetErrInt(_NLL , -3, "無法獲取指針。");
	}
	int TM_Ret = -1;

	if(TM_side >= 0 && TM_side < 2 && TM_num >=0 && TM_num < 10)
	{
		//根據不同side, 計算結構偏移量
		int sideOffset;
		if(TM_side == 0)
			sideOffset = 0;
		else
			sideOffset = 2408;

		//讀取charaPtr
		int charaPtr = *(int*)(TM_Battle + sideOffset + 120 + 208*TM_num );
		//返回charaIndex
		if(API_CHAR_CheckCharPointer(charaPtr))
			TM_Ret = API_CHAR_getCharaIndex(charaPtr);
		
	
		//TM_Ret = TM_Battle->Side[TM_side].Entry[TM_num].charaindex;
	}else
	{
		LRetErrInt(_NLL , -4, "範圍錯誤。");
	}
	LRetInt(_NLL, TM_Ret);
}

/*
int NPC_Lua_Battle_SetNORisk(lua_State *_NLL)
{
	CheckEx(_NLL, 2);
	assert(BattleArray != NULL);
	CheckBattleIndexNull(_NLL, 1);
	int TM_battleindex = (int)lua_tointeger(_NLL, 1);
	int TM_vl = (int)lua_tointeger(_NLL, 2);
	
	if( BATTLE_CHECKINDEX( TM_battleindex ) == FALSE )
	{
		LRetErrInt(_NLL , -1, "傳入的索引是無效的。");
	}

	BATTLE *TM_Battle = &BattleArray[TM_battleindex];

	if(TM_Battle == NULL)
	{
		LRetErrInt(_NLL , -2, "無法獲取指針。");
	}
	
	int TM_Ret = TM_Battle->norisk;
	TM_Battle->norisk = TM_vl;

	LRetInt(_NLL, TM_Ret);
}

int NPC_Lua_Battle_SetMod(lua_State *_NLL)
{
	CheckEx(_NLL, 2);
	assert(BattleArray != NULL);
	CheckBattleIndexNull(_NLL, 1);
	int TM_battleindex = (int)lua_tointeger(_NLL, 1);
	int TM_vl = (int)lua_tointeger(_NLL, 2);
	
	if( BATTLE_CHECKINDEX( TM_battleindex ) == FALSE )
	{
		LRetErrInt(_NLL , -1, "傳入的索引是無效的。");
	}

	BATTLE *TM_Battle = &BattleArray[TM_battleindex];

	if(TM_Battle == NULL)
	{
		LRetErrInt(_NLL , -2, "無法獲取指針。");
	}
	
	int TM_Ret = TM_Battle->mode;
	TM_Battle->mode = TM_vl;

	LRetInt(_NLL, TM_Ret);
}

int NPC_Lua_Battle_SetType(lua_State *_NLL)
{
	CheckEx(_NLL, 2);
	assert(BattleArray != NULL);
	CheckBattleIndexNull(_NLL, 1);
	int TM_battleindex = (int)lua_tointeger(_NLL, 1);
	int TM_vl = (int)lua_tointeger(_NLL, 2);
	
	if( BATTLE_CHECKINDEX( TM_battleindex ) == FALSE )
	{
		LRetErrInt(_NLL , -1, "傳入的索引是無效的。");
	}

	BATTLE *TM_Battle = &BattleArray[TM_battleindex];

	if(TM_Battle == NULL)
	{
		LRetErrInt(_NLL , -2, "無法獲取指針。");
	}
	
	int TM_Ret = TM_Battle->type;
	TM_Battle->type = TM_vl;

	LRetInt(_NLL, TM_Ret);
}
*/

int NPC_Lua_Battle_SetWinEvent(lua_State *_NLL)
{
	CheckEx(_NLL, 3);
	//assert(BattleArray != NULL);
	CheckBattleIndexNull(_NLL, 3);
	int TM_battleindex = (int)lua_tointeger(_NLL, 3);

	if( !API_BATTLE_CHECKINDEX( TM_battleindex ))
	{
		LRetErrInt(_NLL , -1, "傳入的戰鬥索引是無效的。");
	}

	int TM_Ret = NPC_Lua_GetFuncPoint(_NLL);

	if(lua_tointeger(_NLL, -1) > 0)
	{
		strcpy_s(BATTLE_DATA_EXTEND[TM_battleindex].functable[BATTLE_WIN].string, sizeof(BATTLE_DATA_EXTEND[TM_battleindex].functable[BATTLE_WIN].string), lua_tostring(_NLL, 2));
		*(int*)(*(int*)0x10D69C10 + TM_battleindex*5100 + 5088) = (int)NPC_Lua_BattleWinCallBack;
		//設置以下參數, BATTLE_finish 才會執行callback函數
		*(int*)(*(int*)0x10D69C10 + TM_battleindex*5100 + 40) = 0;
		*(int*)(*(int*)0x10D69C10 + TM_battleindex*5100 + 16) = 1;
	}else{
		BATTLE_DATA_EXTEND[TM_battleindex].functable[BATTLE_WIN].string[0] = 0;
		*(int*)(*(int*)0x10D69C10 + TM_battleindex*5100 + 5088) = 0;
	}

	return TM_Ret;
}

#endif //#ifdef _JZ_NEWSCRIPT_LUA
