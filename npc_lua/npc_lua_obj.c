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

int NPC_Lua_Obj_GetType(lua_State *_NLL)
{
	CheckEx(_NLL, 1);
	CheckObjIndexNull(_NLL, 1);
	int TM_index = (int)lua_tointeger(_NLL, 1);
	
	int TM_Ret = API_OBJECT_getType(TM_index);

	LRetInt(_NLL, TM_Ret);
}
/*
int NPC_Lua_Obj_GetCharType(lua_State *_NLL)
{
	CheckEx(_NLL, 1);
	CheckObjIndexNull(_NLL, 1);
	int TM_index = (int)lua_tointeger(_NLL, 1);
	
	int TM_Ret = OBJECT_getchartype(TM_index);

	LRetInt(_NLL, TM_Ret);
}
*/

int NPC_Lua_Obj_GetCharIndex(lua_State *_NLL)
{
	CheckEx(_NLL, 1);
	CheckObjIndexNull(_NLL, 1);
	int TM_index = (int)lua_tointeger(_NLL, 1);
	
	int TM_Ret = API_OBJECT_getIndex(TM_index);

	LRetInt(_NLL, TM_Ret);
}

int NPC_Lua_Obj_GetX(lua_State *_NLL)
{
	CheckEx(_NLL, 1);
	CheckObjIndexNull(_NLL, 1);
	int TM_index = (int)lua_tointeger(_NLL, 1);
	
	int TM_Ret = API_OBJECT_getX(TM_index);

	LRetInt(_NLL, TM_Ret);
}

int NPC_Lua_Obj_GetY(lua_State *_NLL)
{
	CheckEx(_NLL, 1);
	CheckObjIndexNull(_NLL, 1);
	int TM_index = (int)lua_tointeger(_NLL, 1);
	
	int TM_Ret = API_OBJECT_getY(TM_index);

	LRetInt(_NLL, TM_Ret);
}

int NPC_Lua_Obj_GetFloor(lua_State *_NLL)
{
	CheckEx(_NLL, 1);
	CheckObjIndexNull(_NLL, 1);
	int TM_index = (int)lua_tointeger(_NLL, 1);
	
	int TM_Ret = API_OBJECT_getFloor(TM_index);

	LRetInt(_NLL, TM_Ret);
}

int NPC_Lua_Obj_GetMapId(lua_State *_NLL)
{
	CheckEx(_NLL, 1);
	CheckObjIndexNull(_NLL, 1);
	int TM_index = (int)lua_tointeger(_NLL, 1);
	
	int TM_Ret = API_OBJECT_getMapId(TM_index);

	LRetInt(_NLL, TM_Ret);
}

int NPC_Lua_Obj_SetType(lua_State *_NLL)
{
	CheckEx(_NLL, 2);
	CheckObjIndexNull(_NLL, 1);
	int TM_index = (int)lua_tointeger(_NLL, 1);
	int TM_vl = (int)lua_tointeger(_NLL, 2);

	int TM_Ret = API_OBJECT_setType(TM_index, TM_vl);

	LRetInt(_NLL, TM_Ret);
}

/*
int NPC_Lua_Obj_SetCharType(lua_State *_NLL)
{
	CheckEx(_NLL, 2);
	CheckObjIndexNull(_NLL, 1);
	int TM_index = (int)lua_tointeger(_NLL, 1);
	int TM_vl = (int)lua_tointeger(_NLL, 2);

	OBJECT_setchartype(TM_index, TM_vl);

	LRetNull(_NLL);
}
*/

int NPC_Lua_Obj_SetX(lua_State *_NLL)
{
	CheckEx(_NLL, 2);
	CheckObjIndexNull(_NLL, 1);
	int TM_index = (int)lua_tointeger(_NLL, 1);
	int TM_vl = (int)lua_tointeger(_NLL, 2);

	int TM_Ret = API_OBJECT_setX(TM_index, TM_vl);

	LRetInt(_NLL, TM_Ret);
}

int NPC_Lua_Obj_SetY(lua_State *_NLL)
{
	CheckEx(_NLL, 2);
	CheckObjIndexNull(_NLL, 1);
	int TM_index = (int)lua_tointeger(_NLL, 1);
	int TM_vl = (int)lua_tointeger(_NLL, 2);

	int TM_Ret = API_OBJECT_setY(TM_index, TM_vl);

	LRetInt(_NLL, TM_Ret);
}

int NPC_Lua_Obj_SetFloor(lua_State *_NLL)
{
	CheckEx(_NLL, 2);
	CheckObjIndexNull(_NLL, 1);
	int TM_index = (int)lua_tointeger(_NLL, 1);
	int TM_vl = (int)lua_tointeger(_NLL, 2);

	int TM_Ret = API_OBJECT_setFloor(TM_index, TM_vl);

	LRetInt(_NLL, TM_Ret);
}

int NPC_Lua_Obj_SetMapId(lua_State *_NLL)
{
	CheckEx(_NLL, 2);
	CheckObjIndexNull(_NLL, 1);
	int TM_index = (int)lua_tointeger(_NLL, 1);
	int TM_vl = (int)lua_tointeger(_NLL, 2);

	int TM_Ret = API_OBJECT_setMapId(TM_index, TM_vl);

	LRetInt(_NLL, TM_Ret);
}

#endif //#ifdef _JZ_NEWSCRIPT_LUA
