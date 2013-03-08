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

extern int StateTable[];

//////////////////////////////////////////////////////////////////////////////
//功能接口
int NPC_Lua_NLG_CheckInFront(lua_State *_NLL)
{
	CheckEx(_NLL, 3);
	CheckIndexNull(_NLL, 1);
	CheckIndexNull(_NLL, 2);
	int TM_SurIndex = (int)lua_tointeger(_NLL, 1);
	int TM_SurPtr = API_GetCharaPtrFromCharaIndex(TM_SurIndex);
	int TM_DesIndex = (int)lua_tointeger(_NLL, 2);
	int TM_DesPtr = API_GetCharaPtrFromCharaIndex(TM_DesIndex);
	int TM_Distance = (int)lua_tointeger(_NLL, 3);

	int TM_Ret = API_NPC_Util_charIsInFrontOfChar(TM_SurPtr, TM_DesPtr, TM_Distance);
	
	LRetBool(_NLL, TM_Ret);
}

/*
int NPC_Lua_NLG_CheckObj(lua_State *_NLL)
{
	CheckEx(_NLL, 3);
	int TM_Floor = (int)lua_tointeger(_NLL, 1);
	int TM_X = (int)lua_tointeger(_NLL, 2);
	int TM_Y = (int)lua_tointeger(_NLL, 3);
	int TM_ObjIndex = -1;
	OBJECT TM_Object = NULL;
	
	for( TM_Object = MAP_getTopObj( TM_Floor, TM_X, TM_Y) ; TM_Object != NULL ; TM_Object = NEXT_OBJECT(TM_Object))
	{
		TM_ObjIndex = GET_OBJINDEX(TM_Object);
		if( !CHECKOBJECTUSE(TM_ObjIndex) )
		{
			continue;
		}
		LRetInt(_NLL, 1);
	}
	LRetInt(_NLL, 0);
}
*/

int NPC_Lua_NLG_CharLook(lua_State *_NLL)
{
	CheckEx(_NLL, 2);
	CheckIndexNull(_NLL, 1);
	int TM_Index = (int)lua_tointeger(_NLL, 1);
	int TM_ptr = API_GetCharaPtrFromCharaIndex(TM_Index);
	int TM_DIR = (int)lua_tointeger(_NLL, 2);
	API_CHAR_walk(TM_ptr, TM_DIR, 1);
	LRetNull(_NLL);
}


int NPC_Lua_NLG_CreateBattle(lua_State *_NLL)
{
	CheckEx2(_NLL, 2, 7);
	CheckIndexNull(_NLL, 1);
	CheckIndexNull(_NLL, 2);
	int TM_Top = lua_gettop(_NLL);
	int TM_i = 0;
	int TM_Flg = 0;

	CREATEENEMY TM_CreateEnemy[BATTLE_ENTRY_MAX];
	int TM_ArLen = 0;

	memset(&TM_CreateEnemy, NULL, sizeof(TM_CreateEnemy));

	int TM_CharIndex = (int)lua_tointeger(_NLL, 1);
	int TM_CharPtr = API_GetCharaPtrFromCharaIndex(TM_CharIndex);
	int TM_NpcIndex = (int)lua_tointeger(_NLL, 2);
	int TM_NpcPtr = API_GetCharaPtrFromCharaIndex(TM_NpcIndex);
	
	char *TM_DoFunc = NULL;

	if(TM_Top >= 3)
	{
		TM_DoFunc = lua_tostring(_NLL, 3);
	}

	if(TM_Top >= 5)
	{
		TM_ArLen = luaL_getn(_NLL, 5);
		TM_ArLen = min(TM_ArLen, BATTLE_ENTRY_MAX);
		for(TM_i = 1; TM_i <= TM_ArLen; TM_i++)
		{
			lua_rawgeti(_NLL, 5, TM_i);
			TM_CreateEnemy[TM_i - 1].BaseLevel = (int)lua_tointeger(_NLL, -1);
			lua_pop(_NLL, 1);
		}
	}
	
	if(TM_Top >= 6)
	{
		TM_ArLen = luaL_getn(_NLL, 6);
		TM_ArLen = min(TM_ArLen, BATTLE_ENTRY_MAX);
		for(TM_i = 1; TM_i <= TM_ArLen; TM_i++)
		{
			lua_rawgeti(_NLL, 6, TM_i);
			TM_CreateEnemy[TM_i - 1].BaseLevelRange = (int)lua_tointeger(_NLL, -1);
			lua_pop(_NLL, 1);
		}
	}

	if(TM_Top >= 7)
	{
		TM_Flg = (int)lua_tointeger(_NLL, 7);
	}

//這個要放在最後
	if(TM_Top >= 4)
	{
		TM_ArLen = luaL_getn(_NLL, 4);
		TM_ArLen = min(TM_ArLen, BATTLE_ENTRY_MAX);
		for(TM_i = 1; TM_i <= TM_ArLen; TM_i++)
		{
			lua_rawgeti(_NLL, 4, TM_i);
			TM_CreateEnemy[TM_i - 1].EnemyId = API_ENEMY_getEnemyArrayFromId((int)lua_tointeger(_NLL, -1));
			lua_pop(_NLL, 1);
		}
	}
//然後再調用創建戰鬥的函數
	int TM_Ret = NPC_Lua_CreateVsEnemy(_NLL, TM_CharPtr, TM_NpcPtr, TM_DoFunc, &TM_CreateEnemy, TM_ArLen, TM_Flg);


	//返回負數表示失敗
	LRetInt(_NLL, TM_Ret);
}


int NPC_Lua_NLG_DelPet(lua_State *_NLL)
{
	CheckEx(_NLL, 4);
	CheckIndexNull(_NLL, 1);
	
	int TM_Index = (int)lua_tointeger(_NLL, 1);
	int TM_Ptr = API_GetCharaPtrFromCharaIndex(TM_Index);
	int TM_PetID = (int)lua_tointeger(_NLL, 2);
	int TM_Level = (int)lua_tointeger(_NLL, 3);
	int TM_LevelRange = (int)lua_tointeger(_NLL, 4);

	int TM_Ret = NPC_DelPet(TM_Ptr, TM_PetID, TM_Level, TM_LevelRange);
	if(TM_Ret < 0)
	{
		char TM_MsgBuff[128];
		snprintf(TM_MsgBuff, sizeof(TM_MsgBuff), "刪除寵物時產生錯誤 錯誤號: %d。", TM_Ret);
		LRetErrInt(_NLL , TM_Ret, TM_MsgBuff);
	}

	LRetInt(_NLL, TM_Ret);
}


int NPC_Lua_NLG_DelItem(lua_State *_NLL)
{
	CheckEx2(_NLL, 2, 3);
	CheckIndexNull(_NLL, 1);
	int TM_Index = (int)lua_tointeger(_NLL, 1);
	int TM_Ptr = API_GetCharaPtrFromCharaIndex(TM_Index);
	int TM_ItemID = (int)lua_tointeger(_NLL, 2);
	int TM_Num = 1;
	
	if(lua_gettop(_NLL) == 3)
	{
		TM_Num = (int)lua_tointeger(_NLL, 3);
	}

	int TM_Ret = NPC_DelItem(TM_Ptr, TM_ItemID, TM_Num);
	
	LRetInt(_NLL, TM_Ret);
}


int NPC_Lua_NLG_DischargeParty(lua_State *_NLL)
{
	CheckEx(_NLL, 1);
	CheckIndexNull(_NLL, 1);
	int TM_Index = (int)lua_tointeger(_NLL, 1);
	int TM_ptr = API_GetCharaPtrFromCharaIndex(TM_Index);

	BOOL TM_Ret = API_CHAR_DischargePartyNoMsg( TM_ptr);

	LRetBool(_NLL, TM_Ret);
}

int NPC_Lua_NLG_GivePet(lua_State *_NLL)
{
	CheckEx2(_NLL, 2, 3);
	CheckIndexNull(_NLL, 1);
	int TM_Index = (int)lua_tointeger(_NLL, 1);
	int TM_Ptr = API_GetCharaPtrFromCharaIndex(TM_Index);
	int TM_EnemyId = (int)lua_tointeger(_NLL, 2);
	int TM_FullPB =0;

	if(lua_gettop(_NLL) >= 3)
	{
		TM_FullPB = (int)lua_tointeger(_NLL, 3);
	}

	int TM_PetPtr = NPC_GivePet(TM_Ptr, TM_EnemyId, TM_FullPB);
	if(TM_PetPtr)
	{
		char TM_Buff[128];
		sprintf(TM_Buff, TM_FullPB? "獲得滿檔 %s。" : "獲得 %s。", (char*)(TM_PetPtr + 648));
		API_CHAR_talkToCli(TM_Ptr, 0, TM_Buff, 4, 0);
	}
	
	int TM_PetIndex = API_CHAR_getCharaIndex(TM_PetPtr);
	LRetInt(_NLL, TM_PetIndex);
}

int NPC_Lua_NLG_GiveItem(lua_State *_NLL)
{
	CheckEx2(_NLL, 2, 3);
	CheckIndexNull(_NLL, 1);
	int TM_Index = (int)lua_tointeger(_NLL, 1);
	int TM_Ptr = API_GetCharaPtrFromCharaIndex(TM_Index);
	int TM_ItemId = (int)lua_tointeger(_NLL, 2);
	int TM_Num = 1;
	int TM_ItemIndex = -1;
	int TM_Int = -1;
	int TM_Count = 0;

	if(lua_gettop(_NLL) == 3)
	{
		TM_Num = (int)lua_tointeger(_NLL, 3);
	}

	TM_Int = NPC_GiveItem( TM_Ptr, TM_ItemId, TM_Num);

	LRetInt(_NLL, TM_Int);

}


int NPC_Lua_NLG_ShowWindowTalked(lua_State *_NLL)
{
	CheckEx2(_NLL, 5, 6);
	CheckIndexNull(_NLL, 1);
	int TM_Top = lua_gettop(_NLL);
	int TM_Index = (int)lua_tointeger(_NLL, 1);
	int TM_ptr = API_GetCharaPtrFromCharaIndex(TM_Index);
	int TM_windowtype = (int)lua_tointeger(_NLL, 2);
	int TM_buttontype = (int)lua_tointeger(_NLL, 3);
	int TM_seqno = (int)lua_tointeger(_NLL, 4);
	char *TM_data = lua_tostring(_NLL, 5);

	if(TM_data == NULL)
	{
		LRetErrInt(_NLL , -1, "對話框內容不能為nil");
	}

	int TM_MePtr = 0;
	int TM_fd = API_getfdFromChar(TM_ptr);

	if(TM_Top == 6)
	{
		CheckIndexNull(_NLL, 6);
		int TM_MeIndex = (int)lua_tointeger(_NLL, 6);
		TM_MePtr = API_GetCharaPtrFromCharaIndex(TM_MeIndex);
	}

	API_nrproto_WN_send(TM_fd, TM_windowtype, TM_buttontype, TM_seqno, API_CHAR_getObjectIndexFromChar(TM_MePtr), TM_data);
	LRetInt(_NLL, 0);
}


int NPC_Lua_NLG_SetAction(lua_State *_NLL)
{
	CheckEx(_NLL, 2);
	CheckIndexNull(_NLL, 1);
	int TM_Index = (int)lua_tointeger(_NLL, 1);
	int TM_Ptr = API_GetCharaPtrFromCharaIndex(TM_Index);
	int TM_Action = (int)lua_tointeger(_NLL, 2);
	
	if(!API_CHAR_CheckCharPointer(TM_Ptr))
	{
		LRetErrInt(_NLL, -1, "傳入的對象索引是無效的。");
	}

	API_CHAR_sendWatchEvent( *(int*)(TM_Ptr + 1360), TM_Action, NULL, 0, 1);
	*(int*)(TM_Ptr + 1392) = TM_Action;

	LRetInt(_NLL, 0);
}


int NPC_Lua_NLG_TalkToCli(lua_State *_NLL)
{
	CheckEx2(_NLL, 2, 5);
	CheckIndexNull(_NLL, 1);
	int TM_Top = lua_gettop(_NLL);
	int TM_toIndex = (int)lua_tointeger(_NLL, 1);
	int TM_toptr = API_GetCharaPtrFromCharaIndex(TM_toIndex);
	char *TM_Msg = lua_tostring(_NLL, 2);
	if(TM_Msg == NULL)
	{
		LRetErrInt(_NLL , -1, "說話內容不能為nil。");
	}

	int TM_color = 0;
	int TM_fontsize = 0;
	int TM_Talkptr = 0;

	if(TM_Top >= 3)
	{
		TM_color = (int)lua_tointeger(_NLL, 3);
	}
	if(TM_Top >= 4)
	{
		TM_fontsize = (int)lua_tointeger(_NLL, 4);
	}
	if(TM_Top == 5)
	{
		CheckIndexNull(_NLL, 5);
		int TM_TalkIndex = (int)lua_tointeger(_NLL, 5);
		if(TM_TalkIndex >= 0)
			TM_Talkptr = API_GetCharaPtrFromCharaIndex(TM_TalkIndex);
	}
	BOOL TM_Ret = FALSE;

	if(TM_toIndex == -1)
	{
		//對全伺服器說話
		int TM_playernum = API_CHAR_getEnablePlayerMaxNum();
		int i = 0;

		for( i = 0 ; i < TM_playernum ; i++)
		{
			int charaptr = API_GetCharaPtrFromCharaIndex(i);
			if( *(int*)charaptr && *(int*)(charaptr + 1400)==1 )
			{
				TM_Ret |= API_CHAR_talkToCli( charaptr, TM_Talkptr, TM_Msg, TM_color, TM_fontsize);
			}
		}
	}else
	{
		//對指定玩家說話
		TM_Ret = API_CHAR_talkToCli(TM_toptr, TM_Talkptr, TM_Msg, TM_color, TM_fontsize);
	}
	if(TM_Ret == TRUE)
	{
		LRetInt(_NLL, 0);
	}else
	{
		LRetErrInt(_NLL , -2, "未知原因導致發送說話失敗。");
	}
}


int NPC_Lua_NLG_TalkToFloor(lua_State *_NLL)
{
	CheckEx2(_NLL, 3, 6);
	
	int TM_Top = lua_gettop(_NLL);
	int TM_mapid = (int)lua_tointeger(_NLL, 1);
	int TM_floor = (int)lua_tointeger(_NLL, 2);
	char *TM_Msg = lua_tostring(_NLL, 3);
	if(TM_Msg == NULL)
	{
		LRetErrInt(_NLL , -1, "說話內容不能為nil。");
	}

	int TM_color = 0;
	int TM_fontsize = 0;
	int TM_TalkPtr = 0;

	if(TM_Top >= 4)
	{
		TM_color = (int)lua_tointeger(_NLL, 4);
	}
	if(TM_Top >= 5)
	{
		TM_fontsize = (int)lua_tointeger(_NLL, 5);
	}
	if(TM_Top == 6)
	{
		CheckIndexNull(_NLL, 6);
		int TM_TalkIndex = (int)lua_tointeger(_NLL, 6);
		if(TM_TalkIndex >= 0)
			TM_TalkPtr = API_GetCharaPtrFromCharaIndex(TM_TalkIndex);
	}

	//指定地圖說話
	BOOL TM_Ret = FALSE;
	int TM_playernum = API_CHAR_getEnablePlayerMaxNum();
	int i = 0;

	for( i = 0 ; i < TM_playernum ; i++)
	{
		int charaptr = API_GetCharaPtrFromCharaIndex(i);
		if( *(int*)charaptr && *(int*)(charaptr + 1400)==1 && *(int*)(charaptr + 24)==TM_mapid  && *(int*)(charaptr + 28)==TM_floor )
		{
			TM_Ret |= API_CHAR_talkToCli( charaptr, TM_TalkPtr, TM_Msg, TM_color, TM_fontsize);
		}
	}




	if(TM_Ret == TRUE)
	{
		LRetInt(_NLL, 0);
	}else
	{
		LRetErrInt(_NLL , -2, "未知原因導致發送說話失敗。");
	}
}

/*
#ifdef _SAF_LUAPLUS0712
int NPC_Lua_NLG_UpItem(lua_State *_NLL)
{
	CheckEx(_NLL, 1);
	CheckIndexNull(_NLL, 1);
	
	int charaindex = (int)lua_tointeger(_NLL,1);
	if( !CHAR_CHECKINDEX( charaindex)){
		return 0;
	}
	int MAX = 27;
	int i= 0;
	for ( i = 0; i <= MAX; i++){
		CHAR_sendItemDataOne( charaindex, i);
	}
	return 0;
}

int NPC_Lua_NLG_GivePetOne(lua_State *_NLL)
{
	CheckEx2(_NLL, 2, 4);
	CheckIndexNull(_NLL, 1);
	int TM_Index = (int)lua_tointeger(_NLL, 1);
	int TM_EnemyId = (int)lua_tointeger(_NLL, 2);
	int TM_Level = 1;
	int TM_PetIndex = -1;
	int TM_Int = -1;

	if(lua_gettop(_NLL) >= 3)
	{
		TM_Level = (int)lua_tointeger(_NLL, 3);
	}
	
	TM_Int = NPC_GivePet(TM_Index, TM_Level, TM_EnemyId);
	if(TM_Int >= 0)
	{
		TM_PetIndex = TM_Int;
		char TM_Buff[128];
		snprintf(TM_Buff, sizeof(TM_Buff), "獲得 1 只 %s。", CHAR_getChar( TM_PetIndex, CHAR_NAME));
		CHAR_talkToCli( TM_Index, -1, TM_Buff, CHAR_COLORYELLOW, 0);
	}
	LRetInt(_NLL, TM_PetIndex);
}

int NPC_Lua_NLG_GiveItemOne(lua_State *_NLL)
{
	CheckEx2(_NLL, 2, 3);
	CheckIndexNull(_NLL, 1);
	int TM_Index = (int)lua_tointeger(_NLL, 1);
	int TM_ItemId = (int)lua_tointeger(_NLL, 2);
	int TM_ItemIndex = -1;
	int TM_Int = -1;
	
	TM_Int = NPC_GiveItem( TM_Index, TM_ItemId);
	
	if(TM_Int >= 0)
	{
		TM_ItemIndex = TM_Int;
		char TM_Buff[128];
		snprintf(TM_Buff, sizeof(TM_Buff), "獲得 1 個 %s。", ITEM_getChar( TM_ItemIndex, ITEM_NAME));
		CHAR_talkToCli( TM_Index, -1, TM_Buff, CHAR_COLORYELLOW, 0);
	}
	LRetInt(_NLL, TM_ItemIndex);
}
#endif
*/

int NPC_Lua_NLG_UpChar(lua_State *_NLL)
{
	CheckEx(_NLL, 1);
	CheckIndexNull(_NLL, 1);
	int TM_Index = (int)lua_tointeger(_NLL, 1);
	int TM_ptr = API_GetCharaPtrFromCharaIndex(TM_Index);
	if(!API_CHAR_CheckCharPointer(TM_ptr))
	{
		LRetErrInt(_NLL, -1, "傳入的對象索引是無效的。");
	}
	
	//更新參數
	if(*(int *)(TM_ptr + 12) == 1){
		API_CHAR_ParamUp(TM_ptr, 0);
		API_CHAR_ParamUp(TM_ptr, 1);
		API_CHAR_ParamUp(TM_ptr, 2);
		API_CHAR_ParamUp(TM_ptr, 3);
		API_CHAR_ParamUp(TM_ptr, 4);
	}
	
	//更新動作
	API_CHAR_sendWatchEvent(*(int*)(TM_ptr + 1360), *(int*)(TM_ptr + 1392), 0, 0, 0);
	
	//更新object資訊
	int old_mapid = API_OBJECT_setMapId(*(int *)(TM_ptr + 1360), *(int *)(TM_ptr + 24));
	int old_floor = API_OBJECT_setFloor(*(int *)(TM_ptr + 1360), *(int *)(TM_ptr + 28));
	int old_x = API_OBJECT_setX(*(int *)(TM_ptr + 1360), *(int *)(TM_ptr + 32));
	int old_y = API_OBJECT_setY(*(int *)(TM_ptr + 1360), *(int *)(TM_ptr + 36));
	if(old_x != *(int *)(TM_ptr + 32) || old_y != *(int *)(TM_ptr + 36)){
		API_MAP_objmove("npc_lua/npc_lua_nlg.c", 0, *(int *)(TM_ptr + 1360), old_mapid, old_floor, old_x, old_y, *(int *)(TM_ptr + 24), *(int *)(TM_ptr + 28), *(int *)(TM_ptr + 32), *(int *)(TM_ptr + 36));
	}
	//傳送object資訊給周圍玩家
	API_CHAR_sendCToArroundCharacter(*(int*)(TM_ptr + 1360));
		
	LRetNull(_NLL);
}

int NPC_Lua_NLG_Warp(lua_State *_NLL)
{
	CheckEx(_NLL, 5);
	CheckIndexNull(_NLL, 1);
	int TM_Index = (int)lua_tointeger(_NLL, 1);
	int TM_Ptr = API_GetCharaPtrFromCharaIndex(TM_Index);
	int TM_MapId = (int)lua_tointeger(_NLL, 2);
	int TM_Floor = (int)lua_tointeger(_NLL, 3);
	int TM_X = (int)lua_tointeger(_NLL, 4);
	int TM_Y = (int)lua_tointeger(_NLL, 5);
	
	BOOL TM_Ret = API_MAP_IsValidCoordinate(TM_MapId, TM_Floor, TM_X, TM_Y);
	if(TM_Ret)
		API_CHAR_PartyWarp(TM_Ptr, TM_MapId, TM_Floor, TM_X, TM_Y);
	
	LRetBool(_NLL, TM_Ret);
}


int NPC_Lua_NLG_WalkMove(lua_State *_NLL)
{
	CheckEx(_NLL, 2);
	CheckIndexNull(_NLL, 1);
	int TM_Index = (int)lua_tointeger(_NLL, 1);
	int TM_Ptr = API_GetCharaPtrFromCharaIndex(TM_Index);
	int TM_DIR = (int)lua_tointeger(_NLL, 2);

	int TM_Ret = API_CHAR_walk(TM_Ptr, TM_DIR, 0);
	//修補NPC類型的Char不會走動的問題 
	*(int*)(TM_Ptr + 1392) = -1;
	if(*(int*)(TM_Ptr + 1100)==0){
		API_CHAR_sendCharaAtWalk(TM_Ptr, *(int*)(TM_Ptr + 24), *(int*)(TM_Ptr + 28), *(int*)(TM_Ptr + 32), *(int*)(TM_Ptr + 36), API_CHAR_getDX(TM_DIR), API_CHAR_getDY(TM_DIR));
		int opt[2] = {100, 0};
		API_CHAR_sendWatchEvent(*(int*)(TM_Ptr + 1360), 1, (int)opt, 1, 1);
	}

	LRetInt(_NLL, TM_Ret);
}

int NPC_Lua_NLG_WatchEntry(lua_State *_NLL)
{
	CheckEx(_NLL, 2);
	CheckIndexNull(_NLL, 1);
	CheckIndexNull(_NLL, 2);
	int TM_Index = (int)lua_tointeger(_NLL, 1);
	int TM_ptr = API_GetCharaPtrFromCharaIndex(TM_Index);
	int TM_ToIndex = (int)lua_tointeger(_NLL, 2);
	int TM_Toptr = API_GetCharaPtrFromCharaIndex(TM_ToIndex);
	if(	API_BATTLE_WatchEntry(TM_ptr, TM_Toptr))
	{
		LRetInt(_NLL, 1);
	}else
	{
		LRetInt(_NLL, 0);
	}
}


int NPC_Lua_Char_GetOnLinePlayer(lua_State *_NLL)
{
	CheckEx(_NLL, 0);
	
	int TM_ret = 0;
	int TM_playernum = API_CHAR_getEnablePlayerMaxNum();
	int i = 0;

	for( i = 0 ; i < TM_playernum ; i++)
	{
		int charaptr = API_GetCharaPtrFromCharaIndex(i);
		if( *(int*)charaptr && *(int*)(charaptr + 12)==1 )
		{
			TM_ret++;
		}
	}
	
	LRetInt(_NLL, TM_ret);
}

/*
int NPC_Lua_NLG_UpStateBySecond(lua_State *_NLL)
{
	CheckEx2(_NLL, 1, 3);
	CheckIndexNull(_NLL, 1);
	int TM_Index = (int)lua_tointeger(_NLL, 1);
	
	if(!CHAR_CHECKINDEX(TM_Index))
	{
		LRetErrInt(_NLL, -1, "傳入的索引是無效的。");
	}

	char TM_Buff[128];
	int TM_fd = getfdFromCharaIndex(TM_Index);
#ifdef _SAF_MAKE
	snprintf(TM_Buff, sizeof(TM_Buff), "FAME|%d|%d|%d", CHAR_getInt(TM_Index,CHAR_FAME)/100, (int)lua_tointeger(_NLL, 2), (int)lua_tointeger(_NLL, 3));
#else
	snprintf(TM_Buff, sizeof(TM_Buff), "FAME|%d", CHAR_getInt(TM_Index,CHAR_FAME)/100);
#endif
	lssproto_S2_send(TM_fd,TM_Buff);
	LRetInt(_NLL, 0);
}

int NPC_Lua_NLG_UpStateByThird(lua_State *_NLL)
{
	CheckEx(_NLL, 2);
	CheckIndexNull(_NLL, 1);
	int TM_Index = (int)lua_tointeger(_NLL, 1);
	int TM_Flg = (int)lua_tointeger(_NLL, 2);
	BOOL TM_Ret = CHAR_send_P_StatusString(TM_Index, TM_Flg);
	LRetBool(_NLL, TM_Ret);
}
*/

int NPC_Lua_NLG_Update_Party(lua_State *_NLL)
{
	CheckEx(_NLL, 1);
	CheckIndexNull(_NLL, 1);
	int TM_Index = (int)lua_tointeger(_NLL, 1);
	int TM_Ptr = API_GetCharaPtrFromCharaIndex(TM_Index);
	API_CHAR_sendPartyParamAll(TM_Ptr);
	LRetNull(_NLL);
}


int NPC_Lua_NLG_CreateBattlePvP(lua_State *_NLL)
{

	CheckEx(_NLL, 2);
	CheckIndexNull(_NLL, 1);
	CheckIndexNull(_NLL, 2);

	int TM_Index1 = (int)lua_tointeger(_NLL, 1);
	int TM_Ptr1 = API_GetCharaPtrFromCharaIndex(TM_Index1);
	int TM_Index2 = (int)lua_tointeger(_NLL, 2);
	int TM_Ptr2 = API_GetCharaPtrFromCharaIndex(TM_Index2);
	
	int TM_Ret = -1;
	int TM_BattleIndex = -1;

	if( *(int *)(TM_Ptr1 + 12)!=1 || *(int *)(TM_Ptr2 + 12)!=1 ){
		LRetErrInt(_NLL, -1, "對像類型不是玩家");
	}

	if( !(*(int *)(TM_Ptr1)) || !(*(int *)(TM_Ptr2)))
	{
		LRetErrInt(_NLL, -2, "對像錯誤");
	}

	TM_Ret = NPC_Lua_CreateVsPlayer(&TM_BattleIndex, TM_Ptr1, TM_Ptr2);
	if(TM_Ret != 0)
	{
		char TM_Buff[64];
		snprintf(TM_Buff, sizeof(TM_Buff), "遭遇失敗！錯誤號:%d", TM_Ret);
		LRetErrInt(_NLL, -4, TM_Buff);
	}
	LRetInt(_NLL, TM_BattleIndex);
}

/*
#ifdef _SAF_NEWLUA
int NPC_Lua_NLG_DelItemByIndex(lua_State *_NLL)
{
	CheckEx(_NLL, 2);
	CheckIndexNull(_NLL, 1);
	CheckIndexNull(_NLL, 2);
	int charaindex = (int)lua_tointeger(_NLL, 1);
	if( CHAR_CHECKINDEX( charaindex ) == FALSE ){
		LRetInt(_NLL, -1);
		return -1;
	}
	int haveitemindex = (int)lua_tointeger(_NLL, 2);
	int itemindex = CHAR_getItemIndex( charaindex, haveitemindex);
	if(!ITEM_CHECKINDEX(itemindex)) {
		LRetInt(_NLL, -1);
		return -1;
	}
	CHAR_DelItem( charaindex, haveitemindex);
	LRetInt(_NLL, 0);
}
#endif
	
#ifdef _SAF_LUAFIREWORK
int NPC_Lua_NLG_FireWork(lua_State *_NLL)
{
	CheckEx(_NLL, 3);
	CheckIndexNull(_NLL, 1);
	CheckIndexNull(_NLL, 2);
	CheckIndexNull(_NLL, 3);

	int charaindex = (int)lua_tointeger(_NLL, 1);
	int image = (int)lua_tointeger(_NLL, 2);
	int flg = (int)lua_tointeger(_NLL, 3);
	
	
	int     i,j,x, y,fl;
	fl = CHAR_getInt(charaindex,CHAR_FLOOR);
	x = CHAR_getInt(charaindex,CHAR_X);
	y = CHAR_getInt(charaindex,CHAR_Y);
	for( i = x-CHAR_DEFAULTSEESIZ/2 ; i <= x+CHAR_DEFAULTSEESIZ/2 ; i++ ){
		for( j = y-CHAR_DEFAULTSEESIZ/2 ; j <= y+CHAR_DEFAULTSEESIZ/2 ;	 j ++ )	{
			OBJECT  object;
			for( object = MAP_getTopObj(fl,i,j) ; object ; object = NEXT_OBJECT(object ) ){
				int charaindex2 = OBJECT_getIndex(GET_OBJINDEX(object));
				if(CHAR_getInt(charaindex2,CHAR_WHICHTYPE)==CHAR_TYPEPLAYER){
					lssproto_ITEM_FIREWORK_send(getfdFromCharaIndex(charaindex2),flg,image,GET_OBJINDEX( MAP_getTopObj(fl,x,y)));
				}
			}
		}
	}

	return 0;
}
#endif
*/

#endif //#ifdef _JZ_NEWSCRIPT_LUA
