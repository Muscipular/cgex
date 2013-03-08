#include "version.h"
#include "common.h"

//#include "char.h"
//#include "char_data.h"
#include "char_base.h"
#include "item.h"
#include "battle.h"
#include "object.h"

//0-1999 CHAR_getInt
//2000-3999 CHAR_getChar
//4000-5999 CHAR_getWorkInt
//6000-7999 CHAR_getWorkChar
//8000-9999 CHAR_getFlg
#define LUA_DATALINE0 0
#define LUA_DATALINE1 2000
#define LUA_DATALINE2 4000
#define LUA_DATALINE3 6000
#define LUA_DATALINE4 8000
#define LUA_DATALINE5 10000
#define LUA_DATALINE6 20000

typedef struct __lua_const {
  const char *name;
  unsigned int size;
  int vl;
}lua_const;

lua_const M_Lua_RegConstList[] = {
	{"�ﹳ_����%", sizeof("�ﹳ_����%"), LUA_DATALINE0 + CHAR_WhichType},
	{"�ﹳ_�ζH%", sizeof("�ﹳ_�ζH%"), LUA_DATALINE0 + CHAR_BaseImageNumber},
	{"�ﹳ_���%", sizeof("�ﹳ_���%"), LUA_DATALINE0 + CHAR_BaseBaseImageNumber},
	{"�ﹳ_�a������%", sizeof("�ﹳ_�a������%"), LUA_DATALINE0 + CHAR_MapId},
	{"�ﹳ_�a��%", sizeof("�ﹳ_�a��%"), LUA_DATALINE0 + CHAR_Floor},
	{"�ﹳ_X%", sizeof("�ﹳ_X%"), LUA_DATALINE0 + CHAR_X},
	{"�ﹳ_Y%", sizeof("�ﹳ_Y%"), LUA_DATALINE0 + CHAR_Y},
	{"�ﹳ_��V%", sizeof("�ﹳ_��V%"), LUA_DATALINE0 + CHAR_Dir},
	{"�ﹳ_����%", sizeof("�ﹳ_����%"), LUA_DATALINE0 + CHAR_Lv},
	{"�ﹳ_��%", sizeof("�ﹳ_��%"), LUA_DATALINE0 + CHAR_Lp},
	{"�ﹳ_�]%", sizeof("�ﹳ_�]%"), LUA_DATALINE0 + CHAR_Fp},
	{"�ﹳ_��O%", sizeof("�ﹳ_��O%"), LUA_DATALINE0 + CHAR_Vital},
	{"�ﹳ_�O�q%", sizeof("�ﹳ_�O�q%"), LUA_DATALINE0 + CHAR_Str},
	{"�ﹳ_�j��%", sizeof("�ﹳ_�j��%"), LUA_DATALINE0 + CHAR_Tough},
	{"�ﹳ_�t��%", sizeof("�ﹳ_�t��%"), LUA_DATALINE0 + CHAR_Quick},
	{"�ﹳ_�]�k%", sizeof("�ﹳ_�]�k%"), LUA_DATALINE0 + CHAR_Magic},
	{"�ﹳ_�B%", sizeof("�ﹳ_�B%"), LUA_DATALINE0 + CHAR_Luck},
	{"�ﹳ_�ر�%", sizeof("�ﹳ_�ر�%"), LUA_DATALINE0 + CHAR_Tribe},
	{"�ﹳ_�a�ݩ�%", sizeof("�ﹳ_�a�ݩ�%"), LUA_DATALINE0 + CHAR_Attrib_Earth},
	{"�ﹳ_���ݩ�%", sizeof("�ﹳ_���ݩ�%"), LUA_DATALINE0 + CHAR_Attrib_Water},
	{"�ﹳ_���ݩ�%", sizeof("�ﹳ_���ݩ�%"), LUA_DATALINE0 + CHAR_Attrib_Fire},
	{"�ﹳ_���ݩ�%", sizeof("�ﹳ_���ݩ�%"), LUA_DATALINE0 + CHAR_Attrib_Wind},
	{"�ﹳ_�ܬr%", sizeof("�ﹳ_�ܬr%"), LUA_DATALINE0 + CHAR_Poison},
	{"�ﹳ_�ܺ�%", sizeof("�ﹳ_�ܺ�%"), LUA_DATALINE0 + CHAR_Sleep},
	{"�ﹳ_�ܥ�%", sizeof("�ﹳ_�ܥ�%"), LUA_DATALINE0 + CHAR_Stone},
	{"�ﹳ_�ܾK%", sizeof("�ﹳ_�ܾK%"), LUA_DATALINE0 + CHAR_Drunk},
	{"�ﹳ_�ܶ�%", sizeof("�ﹳ_�ܶ�%"), LUA_DATALINE0 + CHAR_Confusion},
	{"�ﹳ_�ܧ�%", sizeof("�ﹳ_�ܧ�%"), LUA_DATALINE0 + CHAR_Amnesia},
	{"�ﹳ_����%", sizeof("�ﹳ_����%"), LUA_DATALINE0 + CHAR_Critical},
	{"�ﹳ_����%", sizeof("�ﹳ_����%"), LUA_DATALINE0 + CHAR_Counter},
	{"�ﹳ_�R��%", sizeof("�ﹳ_�R��%"), LUA_DATALINE0 + CHAR_HitRate},
	{"�ﹳ_�{��%", sizeof("�ﹳ_�{��%"), LUA_DATALINE0 + CHAR_Avoid},
	{"�ﹳ_�D����%", sizeof("�ﹳ_�D����%"), LUA_DATALINE0 + CHAR_ItemLimit},
	{"�ﹳ_�ޯ���%", sizeof("�ﹳ_�ޯ���%"), LUA_DATALINE0 + CHAR_SkillSlot},
	{"�ﹳ_���`��%", sizeof("�ﹳ_���`��%"), LUA_DATALINE0 + CHAR_DeadCount},
	{"�ﹳ_�ˮ`��%", sizeof("�ﹳ_�ˮ`��%"), LUA_DATALINE0 + CHAR_DamageCount},
	{"�ﹳ_���d��%", sizeof("�ﹳ_���d��%"), LUA_DATALINE0 + CHAR_KillPetCount},
	{"�ﹳ_�e�R�ɶ�%", sizeof("�ﹳ_�e�R�ɶ�%"), LUA_DATALINE0 + CHAR_LastTimeSetLuck},
	{"�ﹳ_����%", sizeof("�ﹳ_����%"), LUA_DATALINE0 + CHAR_Injury},
	{"�ﹳ_����%", sizeof("�ﹳ_����%"), LUA_DATALINE0 + CHAR_WalkInterval},
	{"�ﹳ_�`��%", sizeof("�ﹳ_�`��%"), LUA_DATALINE0 + CHAR_LoopInterval},
	{"�ﹳ_�g��%", sizeof("�ﹳ_�g��%"), LUA_DATALINE0 + CHAR_Exp},
	{"�ﹳ_�ɯ��I%", sizeof("�ﹳ_�ɯ��I%"), LUA_DATALINE0 + CHAR_LevelUpPoint},
	{"�ﹳ_����%", sizeof("�ﹳ_����%"), LUA_DATALINE0 + CHAR_ImageType},
	{"�ﹳ_�W��%", sizeof("�ﹳ_�W��%"), LUA_DATALINE0 + CHAR_NameColor},
	//{"", sizeof(""), LUA_DATALINE0 + CHAR_AllocPoint},
	{"�ﹳ_�Y��%", sizeof("�ﹳ_�Y��%"), LUA_DATALINE0 + CHAR_EatTime},
	//{"", sizeof(""), LUA_DATALINE0 + CHAR_DataPlaceNumber},
	//{"", sizeof(""), LUA_DATALINE0 + CHAR_RegistNumber},
	{"�ﹳ_¾�~%", sizeof("�ﹳ_¾�~%"), LUA_DATALINE0 + CHAR_MainJob},
	{"�ﹳ_¾��%", sizeof("�ﹳ_¾��%"), LUA_DATALINE0 + CHAR_JobRank},
	{"�ﹳ_¾��ID%", sizeof("�ﹳ_¾��ID%"), LUA_DATALINE0 + CHAR_JobAncestry},
	{"�ﹳ_�y%", sizeof("�ﹳ_�y%"), LUA_DATALINE0 + CHAR_FaceImageNumber},
	{"�ﹳ_����%", sizeof("�ﹳ_����%"), LUA_DATALINE0 + CHAR_Gold},
	{"�ﹳ_�Ȧ����%", sizeof("�ﹳ_�Ȧ����%"), LUA_DATALINE0 + CHAR_BankGold},
	{"�ﹳ_�@�O%", sizeof("�ﹳ_�@�O%"), LUA_DATALINE0 + CHAR_Stamina},
	{"�ﹳ_�F��%", sizeof("�ﹳ_�F��%"), LUA_DATALINE0 + CHAR_Dex},
	{"�ﹳ_���O%", sizeof("�ﹳ_���O%"), LUA_DATALINE0 + CHAR_Intelligence},
	{"�ﹳ_�y�O%", sizeof("�ﹳ_�y�O%"), LUA_DATALINE0 + CHAR_Charm},
	{"�ﹳ_�n��%", sizeof("�ﹳ_�n��%"), LUA_DATALINE0 + CHAR_Fame},
	//{"", sizeof(""), LUA_DATALINE0 + CHAR_EquipTitle},
	{"�ﹳ_�O���I%", sizeof("�ﹳ_�O���I%"), LUA_DATALINE0 + CHAR_SavePoint},
	{"�ﹳ_���d%", sizeof("�ﹳ_���d%"), LUA_DATALINE0 + CHAR_DefaultPet},
	{"�ﹳ_��ѶZ��%", sizeof("�ﹳ_��ѶZ��%"), LUA_DATALINE0 + CHAR_ChatVolume},
	//{"", sizeof(""), LUA_DATALINE0 + CHAR_HelpPoint},
	{"�ﹳ_�n������%", sizeof("�ﹳ_�n������%"), LUA_DATALINE0 + CHAR_LoginCount},
	{"�ﹳ_���ܦ���%", sizeof("�ﹳ_���ܦ���%"), LUA_DATALINE0 + CHAR_TalkCount},
	{"�ﹳ_��o�d��%", sizeof("�ﹳ_��o�d��%"), LUA_DATALINE0 + CHAR_GetPetCount},
	{"�ﹳ_�l��%", sizeof("�ﹳ_�l��%"), LUA_DATALINE0 + CHAR_SendMailCount},
	{"�ﹳ_�Ͳ���%", sizeof("�ﹳ_�Ͳ���%"), LUA_DATALINE0 + CHAR_MergeItemCount},
	{"�ﹳ_���ʦ���%", sizeof("�ﹳ_���ʦ���%"), LUA_DATALINE0 + CHAR_WalkCount},
	{"�ﹳ_�d���`��%", sizeof("�ﹳ_�d���`��%"), LUA_DATALINE0 + CHAR_DeadPetCount},
	{"�ﹳ_�d�_����%", sizeof("�ﹳ_�d�_����%"), LUA_DATALINE0 + CHAR_ResurrectPetCount},
	{"�ﹳ_�d�v����%", sizeof("�ﹳ_�d�v����%"), LUA_DATALINE0 + CHAR_HealPetCount},
	{"�ﹳ_�ʦL��%", sizeof("�ﹳ_�ʦL��%"), LUA_DATALINE0 + CHAR_CaptureCount},
	//{"", sizeof(""), LUA_DATALINE0 + CHAR_OtherFlg},
	{"�ﹳ_���n��W��%", sizeof("�ﹳ_���n��W��%"), LUA_DATALINE0 + CHAR_FameGetValue},
	//{"", sizeof(""), LUA_DATALINE0 + CHAR_FameGetTime},
	//{"", sizeof(""), LUA_DATALINE0 + CHAR_FameAutoDownTime},
	{"�ﹳ_����%", sizeof("�ﹳ_����%"), LUA_DATALINE0 + CHAR_SickLevel},
	//{"", sizeof(""), LUA_DATALINE0 + CHAR_RenewalFlg},
	
	//{"", sizeof(""), LUA_DATALINE0 + CHAR_MaxPoolPetHaveLimit},
	//{"", sizeof(""), LUA_DATALINE0 + CHAR_MaxPoolItemHaveLimit},
	{"�ﹳ_DP%", sizeof("�ﹳ_DP%"), LUA_DATALINE0 + CHAR_DuelPoint},
	{"�ﹳ_�ܦ�%", sizeof("�ﹳ_�ܦ�%"), LUA_DATALINE0 + CHAR_PopupNameColor},
	//{"", sizeof(""), LUA_DATALINE0 + CHAR_Position},
	{"�ﹳ_GM%", sizeof("�ﹳ_GM%"), LUA_DATALINE0 + CHAR_Debugger},
	//{"", sizeof(""), LUA_DATALINE0 + CHAR_DungeonClr01},
	//{"", sizeof(""), LUA_DATALINE0 + CHAR_DungeonClr02},
	//{"", sizeof(""), LUA_DATALINE0 + CHAR_DungeonClr03},
	//{"", sizeof(""), LUA_DATALINE0 + CHAR_LastSaveTime},
	//{"", sizeof(""), LUA_DATALINE0 + CHAR_RankDownFlg},
	//{"", sizeof(""), LUA_DATALINE0 + CHAR_Penalty},
	//{"", sizeof(""), LUA_DATALINE0 + CHAR_LoginPoint},
	//{"", sizeof(""), LUA_DATALINE0 + CHAR_FeverResetTime},
	{"�ﹳ_�d��%", sizeof("�ﹳ_�d��%"), LUA_DATALINE0 + CHAR_FeverHaveTime},
	//{"", sizeof(""), LUA_DATALINE0 + CHAR_HouseId},
	//{"", sizeof(""), LUA_DATALINE0 + CHAR_HouseLimit},
	//{"", sizeof(""), LUA_DATALINE0 + CHAR_TimeOutDungeonId},
	//{"", sizeof(""), LUA_DATALINE0 + CHAR_TimeOutServerNumber},
	{"�ﹳ_��l����%", sizeof("�ﹳ_��l����%"), LUA_DATALINE0 + CHAR_OriginalImageNumber},
	
	{"�ﹳ_��W%", sizeof("�ﹳ_��W%"), LUA_DATALINE1 + CHAR_Name},
	{"�ﹳ_�ٸ�%", sizeof("�ﹳ_�ٸ�%"), LUA_DATALINE1 + CHAR_OwnTitle},
	{"�ﹳ_�b��%", sizeof("�ﹳ_�b��%"), LUA_DATALINE1 + CHAR_CdKey},
	
	{"�ﹳ_�����X��%", sizeof("�ﹳ_�����X��%"), LUA_DATALINE4 + CHAR_ISUNKNOWN},
	{"�ﹳ_�O�_�Ԧ�%", sizeof("�ﹳ_�O�_�Ԧ�%"), LUA_DATALINE4 + CHAR_ISDIE},
	{"�ﹳ_�԰��T���}��%", sizeof("�ﹳ_�԰��T���}��%"), LUA_DATALINE4 + CHAR_ISSHOWBATTLEMSG},
	{"�ﹳ_�ն��}��%", sizeof("�ﹳ_�ն��}��%"), LUA_DATALINE4 + CHAR_ISPARTY},
	{"�ﹳ_�M���}��%", sizeof("�ﹳ_�M���}��%"), LUA_DATALINE4 + CHAR_ISDUEL},
	{"�ﹳ_����}��%", sizeof("�ﹳ_����}��%"), LUA_DATALINE4 + CHAR_ISPARTYCHAT},
	{"�ﹳ_�W���}��%", sizeof("�ﹳ_�W���}��%"), LUA_DATALINE4 + CHAR_ISTRADECARD},
	{"�ﹳ_����}��%", sizeof("�ﹳ_����}��%"), LUA_DATALINE4 + CHAR_ISTRADE},
	{"�ﹳ_�O�_���d%", sizeof("�ﹳ_�O�_���d%"), LUA_DATALINE4 + CHAR_ISFEVERTIME},
	{"�ﹳ_�a�ڶ}��%", sizeof("�ﹳ_�a�ڶ}��%"), LUA_DATALINE4 + CHAR_ISFAMILY},
	{"�ﹳ_�����}��%", sizeof("�ﹳ_�����}��%"), LUA_DATALINE4 + CHAR_ISDEBUG},
	{"�ﹳ_���J�Ķ}��%", sizeof("�ﹳ_���J�Ķ}��%"), LUA_DATALINE4 + CHAR_ISNOTENCOUNTER},
	
	{"�ﹳ_�ն��Ҧ�%", sizeof("�ﹳ_�ն��Ҧ�%"), LUA_DATALINE5 + 1556},
	

	
	//getInt
	{"�D��_ID%", sizeof("�D��_ID%"), LUA_DATALINE0 + ITEM_ID},
	{"�D��_��%", sizeof("�D��_��%"), LUA_DATALINE0 + ITEM_BASEIMAGENUMBER},
	{"�D��_����%", sizeof("�D��_����%"), LUA_DATALINE0 + ITEM_COST},
	{"�D��_����%", sizeof("�D��_����%"), LUA_DATALINE0 + ITEM_TYPE},
	{"�D��_����%", sizeof("�D��_����%"), LUA_DATALINE0 + ITEM_HANDS},
	{"�D��_����%", sizeof("�D��_����%"), LUA_DATALINE0 + ITEM_DOUBLECLICK},
	{"�D��_�԰��i��%", sizeof("�D��_�԰��i��%"), LUA_DATALINE0 + ITEM_BATTLEUSE}, //0�����i��
	{"�D��_���|��%", sizeof("�D��_���|��%"), LUA_DATALINE0 + ITEM_COUNT},
	{"�D��_�̤j���|��%", sizeof("�D��_�̤j���|��%"), LUA_DATALINE0 + ITEM_MAXCOUNT},
	{"�D��_����%", sizeof("�D��_����%"), LUA_DATALINE0 + ITEM_RANK},
	{"�D��_�̤j�@�[%", sizeof("�D��_�̤j�@�[%"), LUA_DATALINE0 + ITEM_DUR},
	{"�D��_����%", sizeof("�D��_����%"), LUA_DATALINE0 + ITEM_ATK},
	{"�D��_���m%", sizeof("�D��_���m%"), LUA_DATALINE0 + ITEM_DEF},
	{"�D��_�ӱ�%", sizeof("�D��_�ӱ�%"), LUA_DATALINE0 + ITEM_AGL},
	{"�D��_�믫%", sizeof("�D��_�믫%"), LUA_DATALINE0 + ITEM_MND},
	{"�D��_�^�_%", sizeof("�D��_�^�_%"), LUA_DATALINE0 + ITEM_RCV},
	{"�D��_����%", sizeof("�D��_����%"), LUA_DATALINE0 + ITEM_CRI},
	{"�D��_����%", sizeof("�D��_����%"), LUA_DATALINE0 + ITEM_CTR},
	{"�D��_�R��%", sizeof("�D��_�R��%"), LUA_DATALINE0 + ITEM_HIT},
	{"�D��_�{��%", sizeof("�D��_�{��%"), LUA_DATALINE0 + ITEM_AVD},
	{"�D��_HP%", sizeof("�D��_HP%"), LUA_DATALINE0 + ITEM_LP},
	{"�D��_MP%", sizeof("�D��_MP%"), LUA_DATALINE0 + ITEM_MP},
	
	{"�D��_�y�O%", sizeof("�D��_�y�O%"), LUA_DATALINE0 + ITEM_CHM},
	{"�D��_�ݩʤ@%", sizeof("�D��_�ݩʤ@%"), LUA_DATALINE0 + ITEM_ATTRIBUTE1}, //1 ~ 4, 0�N��L�ݩ�
	{"�D��_�ݩʤG%", sizeof("�D��_�ݩʤG%"), LUA_DATALINE0 + ITEM_ATTRIBUTE2},
	{"�D��_�ݩʤ@��%", sizeof("�D��_�ݩʤ@��%"), LUA_DATALINE0 + ITEM_ATTRIBUTE1VALUE}, // 0 ~ 100, 10�����
	{"�D��_�ݩʤG��%", sizeof("�D��_�ݩʤG��%"), LUA_DATALINE0 + ITEM_ATTRIBUTE2VALUE},
	//{"�D��_�@�O%", sizeof("�D��_�@�O%"), LUA_DATALINE0 + },
	//{"�D��_�F��%", sizeof("�D��_�F��%"), LUA_DATALINE0 + },
	//{"�D��_���O%", sizeof("�D��_���O%"), LUA_DATALINE0 + },
	
	{"�D��_�r��%", sizeof("�D��_�r��%"), LUA_DATALINE0 + ITEM_POISON},
	{"�D��_�Χ�%", sizeof("�D��_�Χ�%"), LUA_DATALINE0 + ITEM_SLEEP},
	{"�D��_�ۧ�%", sizeof("�D��_�ۧ�%"), LUA_DATALINE0 + ITEM_STONE},
	{"�D��_�K��%", sizeof("�D��_�K��%"), LUA_DATALINE0 + ITEM_DRUNK},
	{"�D��_�ç�%", sizeof("�D��_�ç�%"), LUA_DATALINE0 + ITEM_CONFUSION},
	{"�D��_�ѧ�%", sizeof("�D��_�ѧ�%"), LUA_DATALINE0 + ITEM_AMNESIA},
	
	{"�D��_�n�X����%", sizeof("�D��_�n�X����%"), LUA_DATALINE0 + ITEM_LOGOUTDISAPPEAR},
	{"�D��_��a����%", sizeof("�D��_��a����%"), LUA_DATALINE0 + ITEM_DROPDISAPPEAR},
	
	{"�D��_���]%", sizeof("�D��_���]%"), LUA_DATALINE0 + ITEM_RSS},
	
	{"�D��_Ų�w%", sizeof("�D��_Ų�w%"), LUA_DATALINE0 + ITEM_IDENTITY},
	
	{"�D��_�]�\%", sizeof("�D��_�]�\%"), LUA_DATALINE0 + ITEM_ADM},
	

	//getChar
	{"�D��_��Ų�w�W%", sizeof("�D��_��ų�w�W%"), LUA_DATALINE1 + 0},
	{"�D��_�wŲ�w�W%", sizeof("�D��_�wŲ�w�W%"), LUA_DATALINE1 + 1},
	
	//getWorkInt
	{"�D��_����%", sizeof("�D��_����%"), LUA_DATALINE2 + 0},



	{"�D��_�Y��%", sizeof("�D��_�Y��%"), 0},
	{"�D��_����%", sizeof("�D��_����%"), 1},
	{"�D��_�k��%", sizeof("�D��_�k��%"), 2},
	{"�D��_����%", sizeof("�D��_����%"), 3},
	{"�D��_�}��%", sizeof("�D��_�}��%"), 4},
	{"�D��_��1%", sizeof("�D��_��1%"), 5},
	{"�D��_��2%", sizeof("�D��_��2%"), 6},
	{"�D��_����%", sizeof("�D��_����%"), 7},
	{"�D��_1%", sizeof("�D��_1%"), 8 + 0},
	{"�D��_2%", sizeof("�D��_2%"), 8 + 1},
	{"�D��_3%", sizeof("�D��_3%"), 8 + 2},
	{"�D��_4%", sizeof("�D��_4%"), 8 + 3},
	{"�D��_5%", sizeof("�D��_5%"), 8 + 4},
	{"�D��_6%", sizeof("�D��_6%"), 8 + 5},
	{"�D��_7%", sizeof("�D��_7%"), 8 + 6},
	{"�D��_8%", sizeof("�D��_8%"), 8 + 7},
	{"�D��_9%", sizeof("�D��_9%"), 8 + 8},
	{"�D��_10%", sizeof("�D��_10%"), 8 + 9},
	{"�D��_11%", sizeof("�D��_11%"), 8 + 10},
	{"�D��_12%", sizeof("�D��_12%"), 8 + 11},
	{"�D��_13%", sizeof("�D��_13%"), 8 + 12},
	{"�D��_14%", sizeof("�D��_14%"), 8 + 13},
	{"�D��_15%", sizeof("�D��_15%"), 8 + 14},
	{"�D��_16%", sizeof("�D��_16%"), 8 + 15},
	{"�D��_17%", sizeof("�D��_17%"), 8 + 16},
	{"�D��_18%", sizeof("�D��_18%"), 8 + 17},
	{"�D��_19%", sizeof("�D��_19%"), 8 + 18},
	{"�D��_20%", sizeof("�D��_20%"), 8 + 19},

	
	{"�d��_1%", sizeof("�d��_1%"), 0},
	{"�d��_2%", sizeof("�d��_2%"), 1},
	{"�d��_3%", sizeof("�d��_3%"), 2},
	{"�d��_4%", sizeof("�d��_4%"), 3},
	{"�d��_5%", sizeof("�d��_5%"), 4},

	{"����_1%", sizeof("����_1%"), 1},
	{"����_2%", sizeof("����_2%"), 2},
	{"����_3%", sizeof("����_3%"), 3},
	{"����_4%", sizeof("����_4%"), 4},
	
	{"�d��_�馨%", sizeof("�d��_�馨%"), 0},
	{"�d��_�O��%", sizeof("�d��_�O��%"), 1},
	{"�d��_�j��%", sizeof("�d��_�j��%"), 2},
	{"�d��_�t��%", sizeof("�d��_�t��%"), 3},
	{"�d��_�]��%", sizeof("�d��_�]��%"), 4},
	
	
/*
	{"IT_��%", sizeof("IT_��%"), ITEM_FIST},
	{"IT_���Y%", sizeof("IT_���Y%"), ITEM_AXE},
	{"IT_�Ҵ�%", sizeof("IT_�Ҵ�%"), ITEM_CLUB},
	{"IT_�j%", sizeof("IT_�j%"), ITEM_SPEAR},
	{"IT_�}%", sizeof("IT_�}%"), ITEM_BOW},
	{"IT_SHIELD%", sizeof("IT_SHIELD%"), ITEM_SHIELD},
	{"IT_HELM%", sizeof("IT_HELM%"), ITEM_HELM},
	{"IT_ARMOUR%", sizeof("IT_ARMOUR%"), ITEM_ARMOUR},
	{"IT_����%", sizeof("IT_����%"), ITEM_BRACELET},
	{"IT_�־�%", sizeof("IT_�־�%"), ITEM_MUSIC},
	{"IT_����%", sizeof("IT_����%"), ITEM_NECKLACE},
	{"IT_��%", sizeof("IT_��%"), ITEM_RING},
	{"IT_BELT%", sizeof("IT_BELT%"), ITEM_BELT},
	{"IT_����%", sizeof("IT_����%"), ITEM_EARRING},
	{"IT_����%", sizeof("IT_����%"), ITEM_NOSERING},
	{"IT_�@����%", sizeof("IT_�@����%"), ITEM_AMULET},
	{"IT_��L%", sizeof("IT_��L%"), ITEM_OTHER},
	{"IT_�j�ۼ�%", sizeof("IT_�j�ۼ�%"), ITEM_BOOMERANG},
	{"IT_���Y��%", sizeof("IT_���Y��%"), ITEM_BOUNDTHROW},
	{"IT_���Y��%", sizeof("IT_���Y��%"), ITEM_BREAKTHROW},
	{"IT_DISH%", sizeof("IT_DISH%"), ITEM_DISH},
#ifdef _ITEM_INSLAY
	{"IT_����%", sizeof("IT_����%"), ITEM_METAL},
	{"IT_����%", sizeof("IT_����%"), ITEM_JEWEL},
#endif
#ifdef _ITEM_CHECKWARES
	{"IT_�f��%", sizeof("IT_�f��%"), ITEM_WARES},
#endif
#ifdef _ITEM_EQUITSPACE
	{"IT_�y�a%", sizeof("IT_�y�a%"), ITEM_WBELT},
	{"IT_�޵P%", sizeof("IT_�޵P%"), ITEM_WSHIELD},
	{"IT_�c�l%", sizeof("IT_�c�l%"), ITEM_WSHOES},
#endif
#ifdef _EQUIT_NEWGLOVE 
	{"IT_��M%", sizeof("IT_��M%"), ITEM_WGLOVE},
#endif
#ifdef _JZ_PETEQU
	{"IT_�d�Y�M%", sizeof("IT_�d�Y�M%"), ITEM_PET_HEAD},
	{"IT_�d�ͻH%", sizeof("IT_�d�ͻH%"), ITEM_PET_WING},
	{"IT_�d���M%", sizeof("IT_�d���M%"), ITEM_PET_TOOTH},
	{"IT_�d�ݥ�%", sizeof("IT_�d�ݥ�%"), ITEM_PET_BREAST},
	{"IT_�d�I��%", sizeof("IT_�d�I��%"), ITEM_PET_BACK},
	{"IT_�d���M%", sizeof("IT_�d���M%"), ITEM_PET_CLAW},
	{"IT_�d�@�}2%", sizeof("IT_�d�@�}2%"), ITEM_PET_FEET},
	{"IT_�d�@�}4%", sizeof("IT_�d�@�}4%"), ITEM_PET_FEET4},
	{"IT_�d�_�M%", sizeof("IT_�d�_�M%"), ITEM_PET_FIN},
#endif

	{"�a��_�S%", sizeof("�a��_�S%"), FMMEMBER_NONE},
	{"�a��_�@��%", sizeof("�a��_�@��%"), FMMEMBER_MEMBER},
	{"�a��_�ӽ�%", sizeof("�a��_�ӽ�%"), FMMEMBER_APPLY},
	{"�a��_�ڪ�%", sizeof("�a��_�ڪ�%"), FMMEMBER_LEADER},
	{"�a��_����%", sizeof("�a��_����%"), FMMEMBER_ELDER},
	//{"�a��_���q", sizeof("�a��_���q"), FMMEMBER_INVITE},
	//{"�a��_�]��", sizeof("�a��_�]��"), FMMEMBER_BAILEE},
	//{"�a��_�Ʊ�", sizeof("�a��_�Ʊ�"), FMMEMBER_VICELEADER},

	{"����_��%", sizeof("����_��%"), BATTLE_TYPE_NONE},
	{"����_�H��%", sizeof("����_�H��%"), BATTLE_TYPE_P_vs_E},
	{"����_�H�H%", sizeof("����_�H�H%"), BATTLE_TYPE_P_vs_P},
	{"����_�ǩ�%", sizeof("����_�ǩ�%"), BATTLE_TYPE_E_vs_E},
	{"����_�[%", sizeof("����_�[%"), BATTLE_TYPE_WATCH},
	{"����_DP%", sizeof("����_DP%"), BATTLE_TYPE_DP_BATTLE},
	{"����_BOSS%", sizeof("����_BOSS%"), BATTLE_TYPE_BOSS_BATTLE},

	{"�԰�_�L%", sizeof("�԰�_�L%"), BATTLE_MODE_NONE},
	{"�԰�_��%", sizeof("�԰�_��%"), BATTLE_MODE_INIT},
	{"�԰�_��%", sizeof("�԰�_��%"), BATTLE_MODE_BATTLE},
	{"�԰�_����%", sizeof("�԰�_����%"), BATTLE_MODE_FINISH},
	{"�԰�_������%", sizeof("�԰�_������%"), BATTLE_MODE_STOP},
	{"�԰�_�[��%", sizeof("�԰�_�[��%"), BATTLE_MODE_WATCHBC},
	{"�԰�_�[1%", sizeof("�԰�_�[1%"), BATTLE_MODE_WATCHPRE},
	{"�԰�_�[2%", sizeof("�԰�_�[2%"), BATTLE_MODE_WATCHWAIT},
	{"�԰�_�[3%", sizeof("�԰�_�[3%"), BATTLE_MODE_WATCHMOVIE},
	{"�԰�_�[4%", sizeof("�԰�_�[4%"), BATTLE_MODE_WATCHAFTER},

	{"�k��%", sizeof("�k��%"), CHAR_IMAGETYPE_GIRL},
	{"�k��%", sizeof("�k��%"), CHAR_IMAGETYPE_BOY},
	{"�k��%", sizeof("�k��%"), CHAR_IMAGETYPE_CHILDBOY},
	{"�k��%", sizeof("�k��%"), CHAR_IMAGETYPE_CHILDGIRL},
	{"�k�H%", sizeof("�k�H%"), CHAR_IMAGETYPE_MAN},
	{"���k%", sizeof("���k%"), CHAR_IMAGETYPE_WOMAN},
	{"�ѤH%", sizeof("�ѤH%"), CHAR_IMAGETYPE_OLDMAN},
	{"��%", sizeof("��%"), CHAR_IMAGETYPE_DOG},

*/
	
	{"�ﹳ_���a%", sizeof("�ﹳ_���a%"), 1},
	{"�ﹳ_�Ǫ�%", sizeof("�ﹳ_�Ǫ�%"), 2},
	{"�ﹳ_�d��%", sizeof("�ﹳ_�d��%"), 3},

/*

	{"����_�S%", sizeof("����_�S%"), OBJTYPE_NOUSE},
	{"����_�H%", sizeof("����_�H%"), OBJTYPE_CHARA},
	{"����_�D%", sizeof("����_�D%"), OBJTYPE_ITEM},
	{"����_��%", sizeof("����_��%"), OBJTYPE_GOLD},
#ifdef _NPCSERVER_NEW
	{"����_NPC%", sizeof("����_NPC%"), OBJTYPE_NPCSCHARA},
#endif
#ifdef _MAP_WARPPOINT
	{"����_��%", sizeof("����_��%"), OBJTYPE_WARPPOINT},
#endif
*/


	{"�ն�_�S��%", sizeof("�ն�_�S��%"), 0},
	{"�ն�_����%", sizeof("�ն�_����%"), 1},
	{"�ն�_����%", sizeof("�ն�_����%"), 2},


	{"����_�T����%", sizeof("����_�T����%"), 0},
	{"����_��J��%", sizeof("����_��J��%"), 1},
	{"����_��ܮ�%", sizeof("����_��ܮ�%"), 2},
	{"����_�R���%", sizeof("����_�R���%"), 5},
	{"����_�R��%", sizeof("����_�R��%"), 6},
	{"����_���%", sizeof("����_���%"), 7},
	{"����_�Ϯ�%", sizeof("����_�Ϯ�%"), 37},
	
	{"���s_�S%", sizeof("���s_�S%"), 0},
	{"���s_�T�w%", sizeof("���s_�T�w%"), 1 << 0},
	{"���s_����%", sizeof("���s_����%"), 1 << 1},
	{"���s_�O%", sizeof("���s_�O%"), 1 << 2},
	{"���s_�_%", sizeof("���s_�_%"), 1 << 3},
	{"���s_�W�@��%", sizeof("���s_�W�@��%"), 1 << 4},
	{"���s_�U�@��%", sizeof("���s_�U�@��%"), 1 << 5},

	{"���W%", sizeof("���W%"), 0},
	{"�W%", sizeof("�W%"), 1},
	{"�k�W%", sizeof("�k�W%"), 2},
	{"�k%", sizeof("�k%"), 3},
	{"�k�U%", sizeof("�k�U%"), 4},
	{"�U%", sizeof("�U%"), 5},
	{"���U%", sizeof("���U%"), 6},
	{"��%", sizeof("��%"), 7},

	{"�զ�%", sizeof("�զ�%"), 0},
	{"�C��%", sizeof("�C��%"), 1},
	{"����%", sizeof("����%"), 2},
	{"�Ŧ�%", sizeof("�Ŧ�%"), 3},
	{"����%", sizeof("����%"), 4},
	{"���%", sizeof("���%"), 5},
	{"����%", sizeof("����%"), 6},
	{"�Ǧ�%", sizeof("�Ǧ�%"), 7},
	{"�`�Ŧ�%", sizeof("�`�Ŧ�%"), 8},
	{"�`���%", sizeof("�`���%"), 9},
	
	{"�r��_�j%", sizeof("�r��_�j%"), 2},
	{"�r��_��%", sizeof("�r��_��%"), 0},
	{"�r��_�p%", sizeof("�r��_�p%"), 1},

	{NULL, 0, 0},
};

