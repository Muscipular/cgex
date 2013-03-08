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
	const char *LibName;				//��Ʈw�W
	luaL_reg *FuncRegList;			//�ݭn���U����Ʈw��ƦC��
}SCRIPTREGLIB,*PSCRIPTREGLIB;

typedef struct __SCRIPTREGCLASS
{
	const char *ClassName;			//�����W
	PSCRIPTREGLIB NewLib;				//�Ω�ӽ�����Ҫ� SCRIPTREGLIB
	luaL_reg *FuncRegList;			//�ݭn���U������ƦC��
}SCRIPTREGCLASS,*PSCRIPTREGCLASS;

typedef struct __SCRIPTREGARRAY
{
	const char *ArrayName;			//�ƲզW
	const char **SetMetaTable;	//�Ω�]�m�Ʋ��T���ʧ@
	const char **SetFuncName;		//�Ω�]�m�Ʋ��T���ʧ@����ƦW�r
	PSCRIPTREGLIB FuncList;			//�Ω��T������ SetMetaTable ���B�z��ƦC��
}SCRIPTREGARRAY,*PSCRIPTREGARRAY;

typedef struct __ARRAY_NTINT
{
	size_t Size;
	int Num[1];
}ARRAY_NTINT,*PARRAY_NTINT;

//�Ы�NPC-��^NPC�ߤ@����
int NPC_Lua_Create(const char *_DoFile, const char *_InitFuncName);

//�R��NPC �ǤJNPC�ߤ@����
int NPC_Lua_Del(int _index);

//�Ыؾ԰�
int NPC_Lua_CreateVsEnemy(lua_State *_NLL, int _CharaIndex, int _NpcIndex, const char *_DoFunc, PCREATEENEMY _CreateEnemy, int _ARLen, int _Flg);
int NPC_Lua_CreateVsPlayer(int *_OutBattleIndex, int charaindex0, int charaindex1);

const char *NPC_Lua_SetErrorStr(const char *ErrStr);

//���U�X�i�եα��f
int NPC_Lua_RegCallEx(lua_State * _NLL, luaL_Reg *_RegList);
//���U�X�i��Ʈw���f
int NPC_Lua_RegLibEx(lua_State * _NLL, PSCRIPTREGLIB _RegLib);
//���U�X�i�����f
int NPC_Lua_RegClassEx(lua_State * _NLL, PSCRIPTREGCLASS _RegClass);
//���U�X�i�Ʋձ��f
int NPC_Lua_RegArrayEx(lua_State * _NLL, PSCRIPTREGARRAY _RegArray);

//�X�i�������f���
//NTInt
int NPC_Lua_NTInt_New(lua_State *_NLL);
int NPC_Lua_NTInt_Get(lua_State *_NLL);
int NPC_Lua_NTInt_Set(lua_State *_NLL);
int NPC_Lua_NTInt_Len(lua_State *_NLL);

//���f���
////////////////////////////////////////////////NL/////////////////////////////////////////////////
int NPC_Lua_NL_GetErrorStr(lua_State *_NLL);						//��^���~�H��
int NPC_Lua_NL_CreateNpc(lua_State *_NLL);							//�Ы�NPC
int NPC_Lua_NL_DelNpc(lua_State *_NLL);									//�R��NPC

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
//�\�౵�f
int NPC_Lua_NLG_CheckInFront(lua_State *_NLL);					//�Ω��ˬd�Y�ӹ�H�O�_�b�Y�ӹ�H���e
int NPC_Lua_NLG_CheckObj(lua_State *_NLL);							//�ˬd�Y�Ӧa�Ϧ�m�O�_����H�s�b
int NPC_Lua_NLG_CharLook(lua_State *_NLL);							//�]�m�H����V(�o�e��s�ʥ])
int NPC_Lua_NLG_CreateBattle(lua_State *_NLL);					//�Ыؾ԰�
int NPC_Lua_NLG_CreateBattlePvP(lua_State *_NLL);				//�Ыت��a�P���a�����

int NPC_Lua_NLG_DelPet(lua_State *_NLL);								//�R�����w���a�d����@�өΦh���d��
int NPC_Lua_NLG_DelItem(lua_State *_NLL);								//�R�����w���a�D����@�өΦh���d��
int NPC_Lua_NLG_DischargeParty(lua_State *_NLL);				//�Ѵ� �ζ�
#ifdef _SAF_NEWLUA
int NPC_Lua_NLG_DelItemByIndex(lua_State *_NLL);	
#endif
int NPC_Lua_NLG_GivePet(lua_State *_NLL);								//�����w���a�@�өΦh���d��
int NPC_Lua_NLG_GiveItem(lua_State *_NLL);							//�����w���a�@�өΦh���d��
int NPC_Lua_Char_GetOnLinePlayer(lua_State *_NLL);			//�����e�b�u�H��

int NPC_Lua_NLG_ShowWindowTalked(lua_State *_NLL);			//�b���w���a�Ȥ����ܫ��w���e�B��������ܮ�
int NPC_Lua_NLG_SetAction(lua_State *_NLL);							//�]�m��H���ʧ@

int NPC_Lua_NLG_TalkToCli(lua_State *_NLL);							//���q���ܡA�i�H������A���H��
int NPC_Lua_NLG_TalkToFloor(lua_State *_NLL);						//��b�Y�@���w�a�Ϥ������a����
#ifdef _SAF_LUAPLUS0712
int NPC_Lua_NLG_UpItem(lua_State *_NLL);
int NPC_Lua_NLG_GiveItemOne(lua_State *_NLL);
int NPC_Lua_NLG_GivePetOne(lua_State *_NLL);
#endif
#ifdef _SAF_LUAFIREWORK
int NPC_Lua_NLG_FireWork(lua_State *_NLL);
#endif
int NPC_Lua_NLG_UpChar(lua_State *_NLL);								//�VNPC�P�򪺪��a�o�eNPC���ƾڧ�s�ʥ]
int NPC_Lua_NLG_UpStateBySecond(lua_State *_NLL);				//�V���w���a�o�e��2�����A��s�ʥ]
int NPC_Lua_NLG_UpStateByThird(lua_State *_NLL);				//�V���w���a�o�e��3�����A��s�ʥ]
int NPC_Lua_NLG_Update_Party(lua_State *_NLL);					//�V���a�Ҧb���ζ������o�e���a�����A��s�ʥ]

int NPC_Lua_NLG_Warp(lua_State *_NLL);									//�ǰe�@�ӹﹳ
int NPC_Lua_NLG_WalkMove(lua_State *_NLL);							//���ʤ@�ӹﹳ
int NPC_Lua_NLG_WatchEntry(lua_State *_NLL);						//�[��

///////////////////////////////////////////////Char////////////////////////////////////////////////
//���ȼлx
//int NPC_Lua_Char_ClrEvtEnd(lua_State *_NLL);						//�]�m�M���������ȼлx
//int NPC_Lua_Char_ClrEvtNow(lua_State *_NLL);						//�]�m�M�����b�����ȼлx
//int NPC_Lua_Char_ClrEvt(lua_State *_NLL);								//�]�m�M�����ȼлx
//int NPC_Lua_Char_IsEventEnd(lua_State *_NLL);						//�ˬd�O�_���������ȼлx
//int NPC_Lua_Char_IsEventNow(lua_State *_NLL);						//�ˬd�O�_���b�������ȼлx
//int NPC_Lua_Char_SetEvtEnd(lua_State *_NLL);						//�]�m���ȼлx���������A
//int NPC_Lua_Char_SetEvtNow(lua_State *_NLL);						//�]�m���ȼлx�����b�����A
int NPC_Lua_Char_NowEvent(lua_State *_NLL);
int NPC_Lua_Char_EndEvent(lua_State *_NLL);


int NPC_Lua_Char_SetData(lua_State *_NLL);							//�]�mChar�ƾ�

//�ƥ�]�m�����f
int NPC_Lua_Char_SetWalkPreEvent(lua_State *_NLL);			//�]�mWalkPre�ƥ��T��
int NPC_Lua_Char_SetWalkPostEvent(lua_State *_NLL);			//�]�mWalkPost�ƥ��T��
int NPC_Lua_Char_SetPreOverEvent(lua_State *_NLL);			//�]�mPreOver�ƥ��T��
int NPC_Lua_Char_SetPostOverEvent(lua_State *_NLL);			//�]�mPostOver�ƥ��T��
int NPC_Lua_Char_SetWatchEvent(lua_State *_NLL);				//�]�mWatch�ƥ��T��
int NPC_Lua_Char_SetLoopEvent(lua_State *_NLL);					//�]�mLoop�ƥ��T��
int NPC_Lua_Char_SetTalkedEvent(lua_State *_NLL);				//�]�mTalked�ƥ��T��
int NPC_Lua_Char_SetOFFEvent(lua_State *_NLL);					//�]�mOFF�ƥ��T��
int NPC_Lua_Char_SetLookedEvent(lua_State *_NLL);				//�]�mLooked�ƥ��T��
int NPC_Lua_Char_SetItemPutEvent(lua_State *_NLL);			//�]�mItemPut�ƥ��T��
int NPC_Lua_Char_SetWindowTalkedEvent(lua_State *_NLL);	//�]�mWindowTalked�ƥ��T��
#ifdef _USER_CHARLOOPS
int NPC_Lua_Char_SetCharLoopsEvent(lua_State *_NLL);		//�]�mCharLoops�ƥ��T��
int NPC_Lua_Char_SetBattleProPertyEvent(lua_State *_NLL);//�]�mBattleProPerty�ƥ��T��
#endif
#ifdef _SAF_PET_EVO
int NPC_Lua_Char_ReLoadPetBASE(lua_State *_NLL);		//�]�mCharLoops�ƥ��T��
int NPC_Lua_Char_PetEvolution(lua_State *_NLL);		//�]�mCharLoops�ƥ��T��
#endif

//����ƾڪ����f
int NPC_Lua_Char_FindItemId(lua_State *_NLL);						//�j�����w�ﹳ���W�O�_�֦��Y�D��ID
int NPC_Lua_Char_FindPetEnemyId(lua_State *_NLL);				//�j�����w�ﹳ���W�O�_�֦��d��Enemy��󪺹���ID

int NPC_Lua_Char_GetData(lua_State *_NLL);							//���Char�ƾ�
int NPC_Lua_Char_GetItemId(lua_State *_NLL);						//������w�ﹳ���W���w��m���D��ID
int NPC_Lua_Char_GetPetEnemyId(lua_State *_NLL);				//������w�ﹳ���W���w��m���d��Enemy��󪺹���ID
int NPC_Lua_Char_GetItemIndex(lua_State *_NLL);					//������w�ﹳ���W���w��m���D�����
int NPC_Lua_Char_GetPetIndex(lua_State *_NLL);					//������w�ﹳ���W���w��m���d���ﹳ����
int NPC_Lua_Char_GetTeamIndex(lua_State *_NLL);					//�����������H����

///////////////////////////////////////////////Item////////////////////////////////////////////////
//����ƾڪ����f
int NPC_Lua_Item_GetData(lua_State *_NLL);							//����D��ƾ�

//�]�m�ƾڪ����f
int NPC_Lua_Item_SetData(lua_State *_NLL);							//����D��ƾ�

//�ƥ�]�m�����f
int NPC_Lua_Item_SetPreOverEvent(lua_State *_NLL);			//�]�mPreOver�ƥ��T��
int NPC_Lua_Item_SetPostOverEvent(lua_State *_NLL);			//�]�mPostOver�ƥ��T��
int NPC_Lua_Item_SetWatchEvent(lua_State *_NLL);				//�]�mWatch�ƥ��T��
int NPC_Lua_Item_SetUseEvent(lua_State *_NLL);					//�]�mUse�ƥ��T��
int NPC_Lua_Item_SetAttachEvent(lua_State *_NLL);				//�]�mAttach�ƥ��T��
int NPC_Lua_Item_SetDetachEvent(lua_State *_NLL);				//�]�mDetach�ƥ��T��
int NPC_Lua_Item_SetDropEvent(lua_State *_NLL);					//�]�mDrop�ƥ��T��
int NPC_Lua_Item_SetPickUPEvent(lua_State *_NLL);				//�]�mPickUP�ƥ��T��
#ifdef _Item_ReLifeAct
int NPC_Lua_Item_SetDieReLifeEvent(lua_State *_NLL);		//�]�mDieReLife�ƥ��T��
#endif

//��s�D��ƾڪ����f
int NPC_Lua_Item_UpItem(lua_State *_NLL);

///////////////////////////////////////////////Obj////////////////////////////////////////////////
//����ƾڪ����f
int NPC_Lua_Obj_GetType(lua_State *_NLL);								//���OBJ������
/*
int NPC_Lua_Obj_GetName(lua_State *_NLL);								//���OBJ���W��
int NPC_Lua_Obj_GetDIR(lua_State *_NLL);								//���OBJ����V
int NPC_Lua_Obj_GetImageNum(lua_State *_NLL);						//���OBJ���ζH��
*/
int NPC_Lua_Obj_GetCharType(lua_State *_NLL);						//���OBJ������Char�ƾڵ��c������
int NPC_Lua_Obj_GetCharIndex(lua_State *_NLL);					//���OBJ������Char�ƾڵ��c������
int NPC_Lua_Obj_GetX(lua_State *_NLL);									//���OBJ��X����
int NPC_Lua_Obj_GetY(lua_State *_NLL);									//���OBJ��Y����
int NPC_Lua_Obj_GetFloor(lua_State *_NLL);							//���OBJ�Ҧb���a�Ͻs��
int NPC_Lua_Obj_GetMapId(lua_State *_NLL);
//int NPC_Lua_Obj_GetDelTime(lua_State *_NLL);						//���OBJ���R���ɶ�

int NPC_Lua_Obj_SetType(lua_State *_NLL);								//���OBJ������
/*
int NPC_Lua_Obj_SetName(lua_State *_NLL);								//���OBJ���W��
int NPC_Lua_Obj_SetDIR(lua_State *_NLL);								//���OBJ����V
int NPC_Lua_Obj_SetImageNum(lua_State *_NLL);						//���OBJ���ζH��
*/
int NPC_Lua_Obj_SetCharType(lua_State *_NLL);						//���OBJ������Char�ƾڵ��c������
int NPC_Lua_Obj_SetX(lua_State *_NLL);									//���OBJ��X����
int NPC_Lua_Obj_SetY(lua_State *_NLL);									//���OBJ��Y����
int NPC_Lua_Obj_SetFloor(lua_State *_NLL);							//���OBJ�Ҧb���a�Ͻs��
int NPC_Lua_Obj_SetMapId(lua_State *_NLL);
//int NPC_Lua_Obj_SetDelTime(lua_State *_NLL);						//���OBJ���R���ɶ�

//////////////////////////////////////////////Battle///////////////////////////////////////////////
//����ƾڪ����f
int NPC_Lua_Battle_GetPlayIndex(lua_State *_NLL);				//����԰��������a����
//�]�m�ƾڪ����f
int NPC_Lua_Battle_SetNORisk(lua_State *_NLL);					//�]�m�O�_�}�ҵL���I�Ҧ�
int NPC_Lua_Battle_SetMod(lua_State *_NLL);							//�]�m�԰��Ҧ��лx
int NPC_Lua_Battle_SetType(lua_State *_NLL);						//�]�m�԰�����
//�ƥ�]�m�����f
int NPC_Lua_Battle_SetWinEvent(lua_State *_NLL);				//�]�mWin�ƥ��T��
///////////////////////////////////////////////SQL/////////////////////////////////////////////////
int NPC_Lua_SQL_Run(lua_State *_NLL);						//�Ω����MySQL���O

///////////////////////////////////////////////Pet/////////////////////////////////////////////////
int NPC_Lua_Pet_GetArtRank(lua_State *_NLL);
int NPC_Lua_Pet_SetArtRank(lua_State *_NLL);
int NPC_Lua_Pet_UpPet(lua_State *_NLL);
int NPC_Lua_Pet_FullArtRank(lua_State *_NLL);

///////////////////////////////////////////////Other///////////////////////////////////////////////
int NPC_Lua_GetFuncPoint(lua_State *_NLL);							//�����ƫ��w

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
//��^�@��nil
#define LRetNull(L) \
{ \
	lua_pushnil(L); \
	LRet(1); \
}

//��^�@��BOOL��LUA����
#define LRetBool(L, b) \
{ \
	lua_pushboolean(L, b); \
	LRet(1); \
}

//��^�@��int��LUA����
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
//�]�m�@�ӿ��~���A�M�@�ӿ��H��
#define LRetErrInt(L, i, c) \
{ \
	lua_pushinteger(L, i); \
	LRetErr(c,1); \
}

//��^�@�Ӧr�Ŧ굹LUA����
#define LRetErrNull(L, c) \
{ \
	lua_pushnil(L); \
	LRetErr(c,1); \
}

//��^�@�Ӧr�Ŧ굹LUA����
#define LRetErrMsg(L, c) \
{ \
	lua_pushstring(L, c); \
	LRetErr(c,1); \
}

//�Ω��ˬd�ѼƬO�_����
#define CheckEx(L, n) \
{	\
	if(lua_gettop(L) != n) \
	{ \
		luaL_argerror(L, 1, "�ѼƼƶq���~"); \
	} \
}

#define CheckEx2(L, t, n) \
{	\
	if(lua_gettop(L) < (t) || lua_gettop(L) > n) \
	{ \
		luaL_argerror(L, 1, "�ѼƼƶq���~"); \
	} \
}

#define CheckIndexNull(L, n) \
{ \
	if(lua_isnil((L), (n))) \
	{ \
		luaL_argerror((L), 1, "�ﹳ���ޤ��ରnil"); \
	} \
}

#define CheckBattleIndexNull(L, n) \
{ \
	if(lua_isnil((L), (n))) \
	{ \
		luaL_argerror((L), 1, "�԰����ޤ��ରnil"); \
	} \
}

#define CheckItemIndexNull(L, n) \
{ \
	if(lua_isnil((L), (n))) \
	{ \
		luaL_argerror((L), 1, "�D����ޤ��ରnil"); \
	} \
}

#define CheckObjIndexNull(L, n) \
{ \
	if(lua_isnil((L), (n))) \
	{ \
		luaL_argerror((L), 1, "������ޤ��ରnil"); \
	} \
}
#endif //#ifndef __NPC_LUA__
