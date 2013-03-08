#include "npc_lua.h"
//#endif
#include "cg_api.h"
#ifdef _JZ_NEWSCRIPT_LUA

//////////////////////////////////////////////////////////////////////////////

int NPC_Lua_Pet_GetArtRank(lua_State *_NLL)
{
	CheckEx(_NLL, 2);
	CheckIndexNull(_NLL, 1);
	int TM_Index = (int)lua_tointeger(_NLL, 1);
	int TM_Ptr = API_GetCharaPtrFromCharaIndex(TM_Index);
	int TM_ArtType = (int)lua_tointeger(_NLL, 2);

	if(!API_CHAR_CheckCharPointer(TM_Ptr))
	{
		LRetErrInt(_NLL , -1, "傳入的對象索引是無效的。");
	}
	
	if(*(int *)(TM_Ptr + 12) != 3 )
	{
		LRetErrInt(_NLL , -2, "傳入的對象並非寵物。");
	}

	if( TM_ArtType >= 0 && TM_ArtType < 5)
	{
		int ret = ((*(int *)(TM_Ptr + 192)) >> ((4-TM_ArtType)*6)) & 0x3F;
		LRetInt(_NLL, ret);
	}
	
	LRetErrInt(_NLL, -3, "ArtType範圍錯誤。");
}

int NPC_Lua_Pet_SetArtRank(lua_State *_NLL)
{
	CheckEx(_NLL, 3);
	CheckIndexNull(_NLL, 1);
	int TM_Index = (int)lua_tointeger(_NLL, 1);
	int TM_Ptr = API_GetCharaPtrFromCharaIndex(TM_Index);
	int TM_ArtType = (int)lua_tointeger(_NLL, 2);
	int TM_ArtVal = (int)lua_tointeger(_NLL, 3);

	if(!API_CHAR_CheckCharPointer(TM_Ptr))
	{
		LRetErrInt(_NLL , -1, "傳入的對象索引是無效的。");
	}
	
	if(*(int *)(TM_Ptr + 12) != 3 )
	{
		LRetErrInt(_NLL , -2, "傳入的對象並非寵物。");
	}
	
	if(TM_ArtVal < 0 ||  TM_ArtVal > 63)
	{
		LRetErrInt(_NLL , -3, "傳入的成長率不介於 0 ~ 63。");
	}
	
	if( TM_ArtType >= 0 && TM_ArtType < 5)
	{
		int point = *(int *)(TM_Ptr + 192);
		int mask = -1 - (63 << (6*(4-TM_ArtType)));
		point = point & mask;
		point = point | (TM_ArtVal << (6*(4-TM_ArtType)));
		*(int *)(TM_Ptr + 192) = point;
		LRetInt(_NLL, 0);
	}
	
	LRetErrInt(_NLL, -4, "ArtType範圍錯誤。");
}

int NPC_Lua_Pet_UpPet(lua_State *_NLL)
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

	if( TM_Pos >= 0 && TM_Pos < 5)
	{
		API_CHAR_send_KP_String(TM_Ptr, TM_Pos, -1);
		API_CHAR_send_KP2_String(TM_Ptr, TM_Pos, -1);
		API_CHAR_sendPetTechData(TM_Ptr, TM_Pos);
		LRetInt(_NLL, 0);
	}else{
		int i;
		for(i=0; i<5; i++){
			API_CHAR_send_KP_String(TM_Ptr, i, -1);
			API_CHAR_send_KP2_String(TM_Ptr, i, -1);
			API_CHAR_sendPetTechData(TM_Ptr, i);
		}
		LRetInt(_NLL, 0);
	}

}

int NPC_Lua_Pet_FullArtRank(lua_State *_NLL)
{
	CheckEx(_NLL, 2);
	CheckIndexNull(_NLL, 1);
	int TM_Index = (int)lua_tointeger(_NLL, 1);
	int TM_Ptr = API_GetCharaPtrFromCharaIndex(TM_Index);
	int TM_ArtType = (int)lua_tointeger(_NLL, 2);

	if(!API_CHAR_CheckCharPointer(TM_Ptr))
	{
		LRetErrInt(_NLL , -1, "傳入的對象索引是無效的。");
	}
	
	if(*(int *)(TM_Ptr + 12) != 3 )
	{
		LRetErrInt(_NLL , -2, "傳入的對象並非寵物。");
	}
	
	if(TM_ArtType < 0 && TM_ArtType >= 5)
	{
		LRetErrInt(_NLL, -3, "ArtType範圍錯誤。");
	}
	

	int TM_EnemyId = *(int *)(TM_Ptr + 284);
	int enemyArrayIndex = API_ENEMY_getEnemyArrayFromId(TM_EnemyId);
	if(enemyArrayIndex < 0){
		LRetErrInt(_NLL, -4, "ENEMY_getEnemyArrayFromId錯誤。");
	}
	
	int enemyTempArrayIndex = API_ENEMYTEMP_getEnemyTempArray(enemyArrayIndex);
	if(enemyTempArrayIndex<0){
		LRetErrInt(_NLL, -5, "ENEMYTEMP_getEnemyTempArray錯誤。");
	}
	
	int ret = *(int*)(*(int*)0x10D0E1E0 + 212 * enemyTempArrayIndex + sizeof(int)*(4 + TM_ArtType)) + 2;
	LRetInt(_NLL, ret);
	
}



#endif //#ifdef _JZ_NEWSCRIPT_LUA
