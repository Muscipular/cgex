#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <unistd.h>
#include <dlfcn.h>
#include "cg_api.h"
#include "jump.h"

#define OBJTYPE_CHARA 1


void JUMP_CHAR_walk_move(int charaPtr){
	//再call此jump function之前, 對象已設定完走路之後的座標
	
	//人物重疊事件
	if(*(int*)(charaPtr+12) == 1) //1代表玩家, 只有玩家走動會觸發事件
	{
		int i;
		int objbuf[128];
		int objbufindex=0;
		char tmp[64];
		objbufindex = API_CHAR_getSameCoordinateObjects( objbuf, 128, *(int*)(charaPtr + 24), *(int*)(charaPtr + 28), *(int*)(charaPtr + 32), *(int*)(charaPtr + 36));
		for(i=0; i<objbufindex; i++)
		{
			//定義函數指針
			typedef void (*POSTOFUNC)(int,int);
			POSTOFUNC   pfunc=NULL;
			//獲取object index
			int objindex= objbuf[i];
			int obj_charaIndex = API_OBJECT_getIndex(objindex);
			//排除自己的object
			if(API_GetCharaPtrFromCharaIndex(obj_charaIndex) == charaPtr) continue;
			//開始判斷同位置的物件
			switch( API_OBJECT_getType(objindex) ){
			case OBJTYPE_CHARA: //包含玩家, NPC, 寵物
				pfunc = CHAR_DATA_EXTEND[obj_charaIndex].funcAddr[CHAR_POSTOVERFUNC];
				break;
			default:
				break;
			}
			if( pfunc )
				pfunc(API_GetCharaPtrFromCharaIndex(obj_charaIndex), charaPtr);
		}
	}
}

char JUMP_CHAR_walk_move_SUB[256];

void jump_function(){
	//CHAR_walk_move
	//函數
	my_mprotect((int)JUMP_CHAR_walk_move_SUB);
	*(char*)((int)JUMP_CHAR_walk_move_SUB +  0)= 0x57; //PUSH edi
	*(char*)((int)JUMP_CHAR_walk_move_SUB +  1)= 0xE8; //CALL
	*(int *)((int)JUMP_CHAR_walk_move_SUB +  2)= (int)JUMP_CHAR_walk_move -4 -((int)JUMP_CHAR_walk_move_SUB + 2);
	*(char*)((int)JUMP_CHAR_walk_move_SUB +  6)= 0x83; //ADD esp, 4
	*(char*)((int)JUMP_CHAR_walk_move_SUB +  7)= 0xC4;
	*(char*)((int)JUMP_CHAR_walk_move_SUB +  8)=  0x4;
	*(char*)((int)JUMP_CHAR_walk_move_SUB +  9)= 0x83; //cmp [ebp+var_38], 6
	*(char*)((int)JUMP_CHAR_walk_move_SUB + 10)= 0x7D;
	*(char*)((int)JUMP_CHAR_walk_move_SUB + 11)= 0xC8;
	*(char*)((int)JUMP_CHAR_walk_move_SUB + 12)= 0x06;
	*(char*)((int)JUMP_CHAR_walk_move_SUB + 13)= 0x0F; //jz loc_807C19C
	*(char*)((int)JUMP_CHAR_walk_move_SUB + 14)= 0x84;
	*(int *)((int)JUMP_CHAR_walk_move_SUB + 15)= 0x0807C19C -4 -((int)JUMP_CHAR_walk_move_SUB + 15) ;
	*(char*)((int)JUMP_CHAR_walk_move_SUB + 19)= 0xE9; //jmp loc_0807BDC1
	*(int *)((int)JUMP_CHAR_walk_move_SUB + 20)= 0x0807BDC1 -4 -((int)JUMP_CHAR_walk_move_SUB + 20);
	//jump
	my_mprotect(0x0807BDB7);
	*(char*)(0x0807BDB7)= 0xE9;
	*(int *)(0x0807BDB8)= (int)JUMP_CHAR_walk_move_SUB -4 -0x0807BDB8;

}