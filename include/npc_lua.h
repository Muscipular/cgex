#ifndef __NPC_LUA__
#define __NPC_LUA__

#include "npc_lua_interface.h"
#include "../luajit/lua.h"
#include "../luajit/lauxlib.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define LUA_DATALINE0 0
#define LUA_DATALINE1 2000
#define LUA_DATALINE2 4000
#define LUA_DATALINE3 6000
#define LUA_DATALINE4 8000
#define LUA_DATALINE5 10000
#define LUA_DATALINE6 20000

#define	BATTLE_ENTRY_MAX 10

typedef struct __CREATEENEMY
{
	int EnemyId;
	int BaseLevel;
	int BaseLevelRange;
}CREATEENEMY,*PCREATEENEMY;

typedef struct __SCRIPTREGLIB
{
	const char *LibName;				//函數庫名
	luaL_reg *FuncRegList;			//需要註冊的函數庫函數列表
}SCRIPTREGLIB,*PSCRIPTREGLIB;

typedef struct __SCRIPTREGCLASS
{
	const char *ClassName;			//類型名
	PSCRIPTREGLIB NewLib;				//用於申請類實例的 SCRIPTREGLIB
	luaL_reg *FuncRegList;			//需要註冊的類函數列表
}SCRIPTREGCLASS,*PSCRIPTREGCLASS;

typedef struct __SCRIPTREGARRAY
{
	const char *ArrayName;			//數組名
	const char **SetMetaTable;	//用於設置數組響應動作
	const char **SetFuncName;		//用於設置數組響應動作的函數名字
	PSCRIPTREGLIB FuncList;			//用於響應對應 SetMetaTable 的處理函數列表
}SCRIPTREGARRAY,*PSCRIPTREGARRAY;

typedef struct __ARRAY_NTINT
{
	size_t Size;
	int Num[1];
}ARRAY_NTINT,*PARRAY_NTINT;

//創建NPC-返回NPC唯一索引
int NPC_Lua_Create(const char *_DoFile, const char *_InitFuncName);

//刪除NPC 傳入NPC唯一索引
int NPC_Lua_Del(int _index);

//創建戰鬥
int NPC_Lua_CreateVsEnemy(lua_State *_NLL, int _CharaIndex, int _NpcIndex, const char *_DoFunc, PCREATEENEMY _CreateEnemy, int _ARLen, int _Flg);
int NPC_Lua_CreateVsPlayer(int *_OutBattleIndex, int charaindex0, int charaindex1);

const char *NPC_Lua_SetErrorStr(const char *ErrStr);

//註冊擴展調用接口
int NPC_Lua_RegCallEx(lua_State * _NLL, luaL_Reg *_RegList);
//註冊擴展函數庫接口
int NPC_Lua_RegLibEx(lua_State * _NLL, PSCRIPTREGLIB _RegLib);
//註冊擴展類接口
int NPC_Lua_RegClassEx(lua_State * _NLL, PSCRIPTREGCLASS _RegClass);
//註冊擴展數組接口
int NPC_Lua_RegArrayEx(lua_State * _NLL, PSCRIPTREGARRAY _RegArray);

//擴展類型接口函數
//NTInt
int NPC_Lua_NTInt_New(lua_State *_NLL);
int NPC_Lua_NTInt_Get(lua_State *_NLL);
int NPC_Lua_NTInt_Set(lua_State *_NLL);
int NPC_Lua_NTInt_Len(lua_State *_NLL);

//接口函數
////////////////////////////////////////////////NL/////////////////////////////////////////////////
int NPC_Lua_NL_GetErrorStr(lua_State *_NLL);						//返回錯誤信息
int NPC_Lua_NL_CreateNpc(lua_State *_NLL);							//創建NPC
int NPC_Lua_NL_DelNpc(lua_State *_NLL);									//刪除NPC

int NPC_Lua_NL_RegBattleOverEvent(lua_State *_NLL);
int NPC_Lua_NL_RegBattleStartEvent(lua_State *_NLL);
int NPC_Lua_NL_RegLevelUpEvent(lua_State *_NLL);
int NPC_Lua_NL_RegLoginEvent(lua_State *_NLL);
int NPC_Lua_NL_RegLoginGateEvent(lua_State *_NLL);
int NPC_Lua_NL_RegLogoutEvent(lua_State *_NLL);
int NPC_Lua_NL_RegTalkEvent(lua_State *_NLL);
int NPC_Lua_NL_RegTitleChangedEvent(lua_State *_NLL);
int NPC_Lua_NL_RegWarpEvent(lua_State *_NLL);

int NPC_Lua_NL_BattleOverCallBack(int _battleindex);
int NPC_Lua_NL_BattleStartCallBack(int _battleindex);
int NPC_Lua_NL_LevelUpCallBack(int _meptr);
int NPC_Lua_NL_LoginCallBack(int _meptr);
int NPC_Lua_NL_LoginGateCallBack(int _meptr);
int NPC_Lua_NL_LogoutCallBack(int _meptr);
int NPC_Lua_NL_TalkCallBack(int _meptr, char* _msg, int _color, int _range, int _size);
int NPC_Lua_NL_TitleChangedCallBack(int _meptr, int _oldTitleID, int _newTitleID);
int NPC_Lua_NL_WarpCallBack(int _meptr, int _mapID, int _floorID, int _x, int _y);

////////////////////////////////////////////////NLG////////////////////////////////////////////////
//功能接口
int NPC_Lua_NLG_CheckInFront(lua_State *_NLL);					//用於檢查某個對象是否在某個對象面前
int NPC_Lua_NLG_CheckObj(lua_State *_NLL);							//檢查某個地圖位置是否有對象存在
int NPC_Lua_NLG_CharLook(lua_State *_NLL);							//設置人物方向(發送更新封包)
int NPC_Lua_NLG_CreateBattle(lua_State *_NLL);					//創建戰鬥
int NPC_Lua_NLG_CreateBattlePvP(lua_State *_NLL);				//創建玩家與玩家的對戰

int NPC_Lua_NLG_DelPet(lua_State *_NLL);								//刪除指定玩家寵物欄一個或多個寵物
int NPC_Lua_NLG_DelItem(lua_State *_NLL);								//刪除指定玩家道具欄一個或多個寵物
int NPC_Lua_NLG_DischargeParty(lua_State *_NLL);				//解散 團隊
#ifdef _SAF_NEWLUA
int NPC_Lua_NLG_DelItemByIndex(lua_State *_NLL);	
#endif
int NPC_Lua_NLG_GivePet(lua_State *_NLL);								//給指定玩家一個或多個寵物
int NPC_Lua_NLG_GiveItem(lua_State *_NLL);							//給指定玩家一個或多個寵物
int NPC_Lua_Char_GetOnLinePlayer(lua_State *_NLL);			//獲取當前在線人數

int NPC_Lua_NLG_ShowWindowTalked(lua_State *_NLL);			//在指定玩家客戶端顯示指定內容、類型的對話框
int NPC_Lua_NLG_SetAction(lua_State *_NLL);							//設置對象的動作

int NPC_Lua_NLG_TalkToCli(lua_State *_NLL);							//普通說話，可以對全伺服器人說
int NPC_Lua_NLG_TalkToFloor(lua_State *_NLL);						//對在某一指定地圖內的玩家說話
#ifdef _SAF_LUAPLUS0712
int NPC_Lua_NLG_UpItem(lua_State *_NLL);
int NPC_Lua_NLG_GiveItemOne(lua_State *_NLL);
int NPC_Lua_NLG_GivePetOne(lua_State *_NLL);
#endif
#ifdef _SAF_LUAFIREWORK
int NPC_Lua_NLG_FireWork(lua_State *_NLL);
#endif
int NPC_Lua_NLG_UpChar(lua_State *_NLL);								//向NPC周圍的玩家發送NPC的數據更新封包
int NPC_Lua_NLG_UpStateBySecond(lua_State *_NLL);				//向指定玩家發送第2類狀態更新封包
int NPC_Lua_NLG_UpStateByThird(lua_State *_NLL);				//向指定玩家發送第3類狀態更新封包
int NPC_Lua_NLG_Update_Party(lua_State *_NLL);					//向玩家所在的團隊成員發送玩家的狀態更新封包

int NPC_Lua_NLG_Warp(lua_State *_NLL);									//傳送一個對像
int NPC_Lua_NLG_WalkMove(lua_State *_NLL);							//移動一個對像
int NPC_Lua_NLG_WatchEntry(lua_State *_NLL);						//觀戰

///////////////////////////////////////////////Char////////////////////////////////////////////////
//任務標誌
//int NPC_Lua_Char_ClrEvtEnd(lua_State *_NLL);						//設置清除結束任務標誌
//int NPC_Lua_Char_ClrEvtNow(lua_State *_NLL);						//設置清除正在做任務標誌
//int NPC_Lua_Char_ClrEvt(lua_State *_NLL);								//設置清除任務標誌
//int NPC_Lua_Char_IsEventEnd(lua_State *_NLL);						//檢查是否結束的任務標誌
//int NPC_Lua_Char_IsEventNow(lua_State *_NLL);						//檢查是否正在做的任務標誌
//int NPC_Lua_Char_SetEvtEnd(lua_State *_NLL);						//設置任務標誌為結束狀態
//int NPC_Lua_Char_SetEvtNow(lua_State *_NLL);						//設置任務標誌為正在做狀態
int NPC_Lua_Char_NowEvent(lua_State *_NLL);
int NPC_Lua_Char_EndEvent(lua_State *_NLL);


int NPC_Lua_Char_SetData(lua_State *_NLL);							//設置Char數據

//事件設置的接口
int NPC_Lua_Char_SetWalkPreEvent(lua_State *_NLL);			//設置WalkPre事件響應
int NPC_Lua_Char_SetWalkPostEvent(lua_State *_NLL);			//設置WalkPost事件響應
int NPC_Lua_Char_SetPreOverEvent(lua_State *_NLL);			//設置PreOver事件響應
int NPC_Lua_Char_SetPostOverEvent(lua_State *_NLL);			//設置PostOver事件響應
int NPC_Lua_Char_SetWatchEvent(lua_State *_NLL);				//設置Watch事件響應
int NPC_Lua_Char_SetLoopEvent(lua_State *_NLL);					//設置Loop事件響應
int NPC_Lua_Char_SetTalkedEvent(lua_State *_NLL);				//設置Talked事件響應
int NPC_Lua_Char_SetOFFEvent(lua_State *_NLL);					//設置OFF事件響應
int NPC_Lua_Char_SetLookedEvent(lua_State *_NLL);				//設置Looked事件響應
int NPC_Lua_Char_SetItemPutEvent(lua_State *_NLL);			//設置ItemPut事件響應
int NPC_Lua_Char_SetWindowTalkedEvent(lua_State *_NLL);	//設置WindowTalked事件響應
#ifdef _USER_CHARLOOPS
int NPC_Lua_Char_SetCharLoopsEvent(lua_State *_NLL);		//設置CharLoops事件響應
int NPC_Lua_Char_SetBattleProPertyEvent(lua_State *_NLL);//設置BattleProPerty事件響應
#endif
#ifdef _SAF_PET_EVO
int NPC_Lua_Char_ReLoadPetBASE(lua_State *_NLL);		//設置CharLoops事件響應
int NPC_Lua_Char_PetEvolution(lua_State *_NLL);		//設置CharLoops事件響應
#endif

//獲取數據的接口
int NPC_Lua_Char_FindItemId(lua_State *_NLL);						//搜索指定對像身上是否擁有某道具ID
int NPC_Lua_Char_FindPetEnemyId(lua_State *_NLL);				//搜索指定對像身上是否擁有寵物Enemy文件的對應ID

int NPC_Lua_Char_GetData(lua_State *_NLL);							//獲取Char數據
int NPC_Lua_Char_GetItemId(lua_State *_NLL);						//獲取指定對像身上指定位置的道具ID
int NPC_Lua_Char_GetPetEnemyId(lua_State *_NLL);				//獲取指定對像身上指定位置的寵物Enemy文件的對應ID
int NPC_Lua_Char_GetItemIndex(lua_State *_NLL);					//獲取指定對像身上指定位置的道具索引
int NPC_Lua_Char_GetPetIndex(lua_State *_NLL);					//獲取指定對像身上指定位置的寵物對像索引
int NPC_Lua_Char_GetTeamIndex(lua_State *_NLL);					//獲取隊員的對象索引

///////////////////////////////////////////////Item////////////////////////////////////////////////
//獲取數據的接口
int NPC_Lua_Item_GetData(lua_State *_NLL);							//獲取道具數據

//設置數據的接口
int NPC_Lua_Item_SetData(lua_State *_NLL);							//獲取道具數據

//事件設置的接口
int NPC_Lua_Item_SetPreOverEvent(lua_State *_NLL);			//設置PreOver事件響應
int NPC_Lua_Item_SetPostOverEvent(lua_State *_NLL);			//設置PostOver事件響應
int NPC_Lua_Item_SetWatchEvent(lua_State *_NLL);				//設置Watch事件響應
int NPC_Lua_Item_SetUseEvent(lua_State *_NLL);					//設置Use事件響應
int NPC_Lua_Item_SetAttachEvent(lua_State *_NLL);				//設置Attach事件響應
int NPC_Lua_Item_SetDetachEvent(lua_State *_NLL);				//設置Detach事件響應
int NPC_Lua_Item_SetDropEvent(lua_State *_NLL);					//設置Drop事件響應
int NPC_Lua_Item_SetPickUPEvent(lua_State *_NLL);				//設置PickUP事件響應
#ifdef _Item_ReLifeAct
int NPC_Lua_Item_SetDieReLifeEvent(lua_State *_NLL);		//設置DieReLife事件響應
#endif

//更新道具數據的接口
int NPC_Lua_Item_UpItem(lua_State *_NLL);

///////////////////////////////////////////////Obj////////////////////////////////////////////////
//獲取數據的接口
int NPC_Lua_Obj_GetType(lua_State *_NLL);								//獲取OBJ的類型
/*
int NPC_Lua_Obj_GetName(lua_State *_NLL);								//獲取OBJ的名稱
int NPC_Lua_Obj_GetDIR(lua_State *_NLL);								//獲取OBJ的方向
int NPC_Lua_Obj_GetImageNum(lua_State *_NLL);						//獲取OBJ的形象號
*/
int NPC_Lua_Obj_GetCharType(lua_State *_NLL);						//獲取OBJ對應的Char數據結構的類型
int NPC_Lua_Obj_GetCharIndex(lua_State *_NLL);					//獲取OBJ對應的Char數據結構的索引
int NPC_Lua_Obj_GetX(lua_State *_NLL);									//獲取OBJ的X坐標
int NPC_Lua_Obj_GetY(lua_State *_NLL);									//獲取OBJ的Y坐標
int NPC_Lua_Obj_GetFloor(lua_State *_NLL);							//獲取OBJ所在的地圖編號
int NPC_Lua_Obj_GetMapId(lua_State *_NLL);
//int NPC_Lua_Obj_GetDelTime(lua_State *_NLL);						//獲取OBJ的刪除時間

int NPC_Lua_Obj_SetType(lua_State *_NLL);								//獲取OBJ的類型
/*
int NPC_Lua_Obj_SetName(lua_State *_NLL);								//獲取OBJ的名稱
int NPC_Lua_Obj_SetDIR(lua_State *_NLL);								//獲取OBJ的方向
int NPC_Lua_Obj_SetImageNum(lua_State *_NLL);						//獲取OBJ的形象號
*/
int NPC_Lua_Obj_SetCharType(lua_State *_NLL);						//獲取OBJ對應的Char數據結構的類型
int NPC_Lua_Obj_SetX(lua_State *_NLL);									//獲取OBJ的X坐標
int NPC_Lua_Obj_SetY(lua_State *_NLL);									//獲取OBJ的Y坐標
int NPC_Lua_Obj_SetFloor(lua_State *_NLL);							//獲取OBJ所在的地圖編號
int NPC_Lua_Obj_SetMapId(lua_State *_NLL);
//int NPC_Lua_Obj_SetDelTime(lua_State *_NLL);						//獲取OBJ的刪除時間

//////////////////////////////////////////////Battle///////////////////////////////////////////////
//獲取數據的接口
int NPC_Lua_Battle_GetPlayIndex(lua_State *_NLL);				//獲取戰鬥中的玩家索引
//設置數據的接口
int NPC_Lua_Battle_SetNORisk(lua_State *_NLL);					//設置是否開啟無風險模式
int NPC_Lua_Battle_SetMod(lua_State *_NLL);							//設置戰鬥模式標誌
int NPC_Lua_Battle_SetType(lua_State *_NLL);						//設置戰鬥類型
//事件設置的接口
int NPC_Lua_Battle_SetWinEvent(lua_State *_NLL);				//設置Win事件響應
///////////////////////////////////////////////SQL/////////////////////////////////////////////////
int NPC_Lua_SQL_Run(lua_State *_NLL);						//用於執行MySQL指令

///////////////////////////////////////////////Pet/////////////////////////////////////////////////
int NPC_Lua_Pet_GetArtRank(lua_State *_NLL);
int NPC_Lua_Pet_SetArtRank(lua_State *_NLL);
int NPC_Lua_Pet_UpPet(lua_State *_NLL);
int NPC_Lua_Pet_FullArtRank(lua_State *_NLL);

///////////////////////////////////////////////Other///////////////////////////////////////////////
int NPC_Lua_GetFuncPoint(lua_State *_NLL);							//獲取函數指針

#define LNweTableInit(L) \
{ \
	lua_newtable(L); \
}

#define LNweTableStr(L, key, value) \
{ \
	lua_pushstring(L, key); \
	lua_pushstring(L, value); \
	lua_settable(L,-3); \
}

#define LNweTableInt(L, key, value) \
{ \
	lua_pushstring(L, key); \
	lua_pushinteger(L, value); \
	lua_settable(L,-3); \
}

#define LRetTable() \
{ \
	return 1; \
}

//////////////////////////////////////////////////////////////////////
#define LRet(r) \
{ \
	NPC_Lua_SetErrorStr(NULL); \
	return r; \
}

#define LRetErr(c,r) \
{ \
	NPC_Lua_SetErrorStr(c); \
	return r; \
}

//////////////////////////////////////////////////////////////////////
//返回一個nil
#define LRetNull(L) \
{ \
	lua_pushnil(L); \
	LRet(1); \
}

//返回一個BOOL給LUA引擎
#define LRetBool(L, b) \
{ \
	lua_pushboolean(L, b); \
	LRet(1); \
}

//返回一個int給LUA引擎
#define LRetInt(L, i) \
{ \
	lua_pushinteger(L, i); \
	LRet(1); \
}

#define LRetMsg(L, c) \
{ \
	lua_pushstring(L, c); \
	LRet(1); \
}
////////////////////////////////////////////////////////////////////
//設置一個錯誤狀態和一個錯信息
#define LRetErrInt(L, i, c) \
{ \
	lua_pushinteger(L, i); \
	LRetErr(c,1); \
}

//返回一個字符串給LUA引擎
#define LRetErrNull(L, c) \
{ \
	lua_pushnil(L); \
	LRetErr(c,1); \
}

//返回一個字符串給LUA引擎
#define LRetErrMsg(L, c) \
{ \
	lua_pushstring(L, c); \
	LRetErr(c,1); \
}

//用於檢查參數是否足夠
#define CheckEx(L, n) \
{	\
	if(lua_gettop(L) != n) \
	{ \
		luaL_argerror(L, 1, "參數數量錯誤"); \
	} \
}

#define CheckEx2(L, t, n) \
{	\
	if(lua_gettop(L) < (t) || lua_gettop(L) > n) \
	{ \
		luaL_argerror(L, 1, "參數數量錯誤"); \
	} \
}

#define CheckIndexNull(L, n) \
{ \
	if(lua_isnil((L), (n))) \
	{ \
		luaL_argerror((L), 1, "對像索引不能為nil"); \
	} \
}

#define CheckBattleIndexNull(L, n) \
{ \
	if(lua_isnil((L), (n))) \
	{ \
		luaL_argerror((L), 1, "戰鬥索引不能為nil"); \
	} \
}

#define CheckItemIndexNull(L, n) \
{ \
	if(lua_isnil((L), (n))) \
	{ \
		luaL_argerror((L), 1, "道具索引不能為nil"); \
	} \
}

#define CheckObjIndexNull(L, n) \
{ \
	if(lua_isnil((L), (n))) \
	{ \
		luaL_argerror((L), 1, "物件索引不能為nil"); \
	} \
}
#endif //#ifndef __NPC_LUA__
