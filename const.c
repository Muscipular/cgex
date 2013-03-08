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
	{"對像_類型%", sizeof("對像_類型%"), LUA_DATALINE0 + CHAR_WhichType},
	{"對像_形象%", sizeof("對像_形象%"), LUA_DATALINE0 + CHAR_BaseImageNumber},
	{"對像_原形%", sizeof("對像_原形%"), LUA_DATALINE0 + CHAR_BaseBaseImageNumber},
	{"對像_地圖類型%", sizeof("對像_地圖類型%"), LUA_DATALINE0 + CHAR_MapId},
	{"對像_地圖%", sizeof("對像_地圖%"), LUA_DATALINE0 + CHAR_Floor},
	{"對像_X%", sizeof("對像_X%"), LUA_DATALINE0 + CHAR_X},
	{"對像_Y%", sizeof("對像_Y%"), LUA_DATALINE0 + CHAR_Y},
	{"對像_方向%", sizeof("對像_方向%"), LUA_DATALINE0 + CHAR_Dir},
	{"對像_等級%", sizeof("對像_等級%"), LUA_DATALINE0 + CHAR_Lv},
	{"對像_血%", sizeof("對像_血%"), LUA_DATALINE0 + CHAR_Lp},
	{"對像_魔%", sizeof("對像_魔%"), LUA_DATALINE0 + CHAR_Fp},
	{"對像_體力%", sizeof("對像_體力%"), LUA_DATALINE0 + CHAR_Vital},
	{"對像_力量%", sizeof("對像_力量%"), LUA_DATALINE0 + CHAR_Str},
	{"對像_強度%", sizeof("對像_強度%"), LUA_DATALINE0 + CHAR_Tough},
	{"對像_速度%", sizeof("對像_速度%"), LUA_DATALINE0 + CHAR_Quick},
	{"對像_魔法%", sizeof("對像_魔法%"), LUA_DATALINE0 + CHAR_Magic},
	{"對像_運%", sizeof("對像_運%"), LUA_DATALINE0 + CHAR_Luck},
	{"對像_種族%", sizeof("對像_種族%"), LUA_DATALINE0 + CHAR_Tribe},
	{"對像_地屬性%", sizeof("對像_地屬性%"), LUA_DATALINE0 + CHAR_Attrib_Earth},
	{"對像_水屬性%", sizeof("對像_水屬性%"), LUA_DATALINE0 + CHAR_Attrib_Water},
	{"對像_火屬性%", sizeof("對像_火屬性%"), LUA_DATALINE0 + CHAR_Attrib_Fire},
	{"對像_風屬性%", sizeof("對像_風屬性%"), LUA_DATALINE0 + CHAR_Attrib_Wind},
	{"對像_抗毒%", sizeof("對像_抗毒%"), LUA_DATALINE0 + CHAR_Poison},
	{"對像_抗睡%", sizeof("對像_抗睡%"), LUA_DATALINE0 + CHAR_Sleep},
	{"對像_抗石%", sizeof("對像_抗石%"), LUA_DATALINE0 + CHAR_Stone},
	{"對像_抗醉%", sizeof("對像_抗醉%"), LUA_DATALINE0 + CHAR_Drunk},
	{"對像_抗亂%", sizeof("對像_抗亂%"), LUA_DATALINE0 + CHAR_Confusion},
	{"對像_抗忘%", sizeof("對像_抗忘%"), LUA_DATALINE0 + CHAR_Amnesia},
	{"對像_必殺%", sizeof("對像_必殺%"), LUA_DATALINE0 + CHAR_Critical},
	{"對像_反擊%", sizeof("對像_反擊%"), LUA_DATALINE0 + CHAR_Counter},
	{"對像_命中%", sizeof("對像_命中%"), LUA_DATALINE0 + CHAR_HitRate},
	{"對像_閃躲%", sizeof("對像_閃躲%"), LUA_DATALINE0 + CHAR_Avoid},
	{"對像_道具欄%", sizeof("對像_道具欄%"), LUA_DATALINE0 + CHAR_ItemLimit},
	{"對像_技能欄%", sizeof("對像_技能欄%"), LUA_DATALINE0 + CHAR_SkillSlot},
	{"對像_死亡數%", sizeof("對像_死亡數%"), LUA_DATALINE0 + CHAR_DeadCount},
	{"對像_傷害數%", sizeof("對像_傷害數%"), LUA_DATALINE0 + CHAR_DamageCount},
	{"對像_殺寵數%", sizeof("對像_殺寵數%"), LUA_DATALINE0 + CHAR_KillPetCount},
	{"對像_占卜時間%", sizeof("對像_占卜時間%"), LUA_DATALINE0 + CHAR_LastTimeSetLuck},
	{"對像_受傷%", sizeof("對像_受傷%"), LUA_DATALINE0 + CHAR_Injury},
	{"對像_移間%", sizeof("對像_移間%"), LUA_DATALINE0 + CHAR_WalkInterval},
	{"對像_循時%", sizeof("對像_循時%"), LUA_DATALINE0 + CHAR_LoopInterval},
	{"對像_經驗%", sizeof("對像_經驗%"), LUA_DATALINE0 + CHAR_Exp},
	{"對像_升級點%", sizeof("對像_升級點%"), LUA_DATALINE0 + CHAR_LevelUpPoint},
	{"對像_圖類%", sizeof("對像_圖類%"), LUA_DATALINE0 + CHAR_ImageType},
	{"對像_名色%", sizeof("對像_名色%"), LUA_DATALINE0 + CHAR_NameColor},
	//{"", sizeof(""), LUA_DATALINE0 + CHAR_AllocPoint},
	{"對像_吃時%", sizeof("對像_吃時%"), LUA_DATALINE0 + CHAR_EatTime},
	//{"", sizeof(""), LUA_DATALINE0 + CHAR_DataPlaceNumber},
	//{"", sizeof(""), LUA_DATALINE0 + CHAR_RegistNumber},
	{"對像_職業%", sizeof("對像_職業%"), LUA_DATALINE0 + CHAR_MainJob},
	{"對像_職階%", sizeof("對像_職階%"), LUA_DATALINE0 + CHAR_JobRank},
	{"對像_職類ID%", sizeof("對像_職類ID%"), LUA_DATALINE0 + CHAR_JobAncestry},
	{"對像_臉%", sizeof("對像_臉%"), LUA_DATALINE0 + CHAR_FaceImageNumber},
	{"對像_金幣%", sizeof("對像_金幣%"), LUA_DATALINE0 + CHAR_Gold},
	{"對像_銀行金幣%", sizeof("對像_銀行金幣%"), LUA_DATALINE0 + CHAR_BankGold},
	{"對像_耐力%", sizeof("對像_耐力%"), LUA_DATALINE0 + CHAR_Stamina},
	{"對像_靈巧%", sizeof("對像_靈巧%"), LUA_DATALINE0 + CHAR_Dex},
	{"對像_智力%", sizeof("對像_智力%"), LUA_DATALINE0 + CHAR_Intelligence},
	{"對像_魅力%", sizeof("對像_魅力%"), LUA_DATALINE0 + CHAR_Charm},
	{"對像_聲望%", sizeof("對像_聲望%"), LUA_DATALINE0 + CHAR_Fame},
	//{"", sizeof(""), LUA_DATALINE0 + CHAR_EquipTitle},
	{"對像_記錄點%", sizeof("對像_記錄點%"), LUA_DATALINE0 + CHAR_SavePoint},
	{"對像_戰寵%", sizeof("對像_戰寵%"), LUA_DATALINE0 + CHAR_DefaultPet},
	{"對像_聊天距離%", sizeof("對像_聊天距離%"), LUA_DATALINE0 + CHAR_ChatVolume},
	//{"", sizeof(""), LUA_DATALINE0 + CHAR_HelpPoint},
	{"對像_登陸次數%", sizeof("對像_登陸次數%"), LUA_DATALINE0 + CHAR_LoginCount},
	{"對像_說話次數%", sizeof("對像_說話次數%"), LUA_DATALINE0 + CHAR_TalkCount},
	{"對像_獲得寵數%", sizeof("對像_獲得寵數%"), LUA_DATALINE0 + CHAR_GetPetCount},
	{"對像_郵數%", sizeof("對像_郵數%"), LUA_DATALINE0 + CHAR_SendMailCount},
	{"對像_生產數%", sizeof("對像_生產數%"), LUA_DATALINE0 + CHAR_MergeItemCount},
	{"對像_走動次數%", sizeof("對像_走動次數%"), LUA_DATALINE0 + CHAR_WalkCount},
	{"對像_寵死亡數%", sizeof("對像_寵死亡數%"), LUA_DATALINE0 + CHAR_DeadPetCount},
	{"對像_寵復活數%", sizeof("對像_寵復活數%"), LUA_DATALINE0 + CHAR_ResurrectPetCount},
	{"對像_寵治療數%", sizeof("對像_寵治療數%"), LUA_DATALINE0 + CHAR_HealPetCount},
	{"對像_封印數%", sizeof("對像_封印數%"), LUA_DATALINE0 + CHAR_CaptureCount},
	//{"", sizeof(""), LUA_DATALINE0 + CHAR_OtherFlg},
	{"對像_日聲望上限%", sizeof("對像_日聲望上限%"), LUA_DATALINE0 + CHAR_FameGetValue},
	//{"", sizeof(""), LUA_DATALINE0 + CHAR_FameGetTime},
	//{"", sizeof(""), LUA_DATALINE0 + CHAR_FameAutoDownTime},
	{"對像_掉魂%", sizeof("對像_掉魂%"), LUA_DATALINE0 + CHAR_SickLevel},
	//{"", sizeof(""), LUA_DATALINE0 + CHAR_RenewalFlg},
	
	//{"", sizeof(""), LUA_DATALINE0 + CHAR_MaxPoolPetHaveLimit},
	//{"", sizeof(""), LUA_DATALINE0 + CHAR_MaxPoolItemHaveLimit},
	{"對像_DP%", sizeof("對像_DP%"), LUA_DATALINE0 + CHAR_DuelPoint},
	{"對像_話色%", sizeof("對像_話色%"), LUA_DATALINE0 + CHAR_PopupNameColor},
	//{"", sizeof(""), LUA_DATALINE0 + CHAR_Position},
	{"對像_GM%", sizeof("對像_GM%"), LUA_DATALINE0 + CHAR_Debugger},
	//{"", sizeof(""), LUA_DATALINE0 + CHAR_DungeonClr01},
	//{"", sizeof(""), LUA_DATALINE0 + CHAR_DungeonClr02},
	//{"", sizeof(""), LUA_DATALINE0 + CHAR_DungeonClr03},
	//{"", sizeof(""), LUA_DATALINE0 + CHAR_LastSaveTime},
	//{"", sizeof(""), LUA_DATALINE0 + CHAR_RankDownFlg},
	//{"", sizeof(""), LUA_DATALINE0 + CHAR_Penalty},
	//{"", sizeof(""), LUA_DATALINE0 + CHAR_LoginPoint},
	//{"", sizeof(""), LUA_DATALINE0 + CHAR_FeverResetTime},
	{"對像_卡時%", sizeof("對像_卡時%"), LUA_DATALINE0 + CHAR_FeverHaveTime},
	//{"", sizeof(""), LUA_DATALINE0 + CHAR_HouseId},
	//{"", sizeof(""), LUA_DATALINE0 + CHAR_HouseLimit},
	//{"", sizeof(""), LUA_DATALINE0 + CHAR_TimeOutDungeonId},
	//{"", sizeof(""), LUA_DATALINE0 + CHAR_TimeOutServerNumber},
	{"對像_原始圖檔%", sizeof("對像_原始圖檔%"), LUA_DATALINE0 + CHAR_OriginalImageNumber},
	
	{"對像_原名%", sizeof("對像_原名%"), LUA_DATALINE1 + CHAR_Name},
	{"對像_稱號%", sizeof("對像_稱號%"), LUA_DATALINE1 + CHAR_OwnTitle},
	{"對像_帳號%", sizeof("對像_帳號%"), LUA_DATALINE1 + CHAR_CdKey},
	
	{"對像_未知旗標%", sizeof("對像_未知旗標%"), LUA_DATALINE4 + CHAR_ISUNKNOWN},
	{"對像_是否戰死%", sizeof("對像_是否戰死%"), LUA_DATALINE4 + CHAR_ISDIE},
	{"對像_戰鬥訊息開關%", sizeof("對像_戰鬥訊息開關%"), LUA_DATALINE4 + CHAR_ISSHOWBATTLEMSG},
	{"對像_組隊開關%", sizeof("對像_組隊開關%"), LUA_DATALINE4 + CHAR_ISPARTY},
	{"對像_決鬥開關%", sizeof("對像_決鬥開關%"), LUA_DATALINE4 + CHAR_ISDUEL},
	{"對像_隊聊開關%", sizeof("對像_隊聊開關%"), LUA_DATALINE4 + CHAR_ISPARTYCHAT},
	{"對像_名片開關%", sizeof("對像_名片開關%"), LUA_DATALINE4 + CHAR_ISTRADECARD},
	{"對像_交易開關%", sizeof("對像_交易開關%"), LUA_DATALINE4 + CHAR_ISTRADE},
	{"對像_是否打卡%", sizeof("對像_是否打卡%"), LUA_DATALINE4 + CHAR_ISFEVERTIME},
	{"對像_家族開關%", sizeof("對像_家族開關%"), LUA_DATALINE4 + CHAR_ISFAMILY},
	{"對像_偵錯開關%", sizeof("對像_偵錯開關%"), LUA_DATALINE4 + CHAR_ISDEBUG},
	{"對像_不遇敵開關%", sizeof("對像_不遇敵開關%"), LUA_DATALINE4 + CHAR_ISNOTENCOUNTER},
	
	{"對像_組隊模式%", sizeof("對像_組隊模式%"), LUA_DATALINE5 + 1556},
	

	
	//getInt
	{"道具_ID%", sizeof("道具_ID%"), LUA_DATALINE0 + ITEM_ID},
	{"道具_圖%", sizeof("道具_圖%"), LUA_DATALINE0 + ITEM_BASEIMAGENUMBER},
	{"道具_價格%", sizeof("道具_價格%"), LUA_DATALINE0 + ITEM_COST},
	{"道具_類型%", sizeof("道具_類型%"), LUA_DATALINE0 + ITEM_TYPE},
	{"道具_雙手%", sizeof("道具_雙手%"), LUA_DATALINE0 + ITEM_HANDS},
	{"道具_雙擊%", sizeof("道具_雙擊%"), LUA_DATALINE0 + ITEM_DOUBLECLICK},
	{"道具_戰鬥可用%", sizeof("道具_戰鬥可用%"), LUA_DATALINE0 + ITEM_BATTLEUSE}, //0為不可用
	{"道具_堆疊數%", sizeof("道具_堆疊數%"), LUA_DATALINE0 + ITEM_COUNT},
	{"道具_最大堆疊數%", sizeof("道具_最大堆疊數%"), LUA_DATALINE0 + ITEM_MAXCOUNT},
	{"道具_等級%", sizeof("道具_等級%"), LUA_DATALINE0 + ITEM_RANK},
	{"道具_最大耐久%", sizeof("道具_最大耐久%"), LUA_DATALINE0 + ITEM_DUR},
	{"道具_攻擊%", sizeof("道具_攻擊%"), LUA_DATALINE0 + ITEM_ATK},
	{"道具_防禦%", sizeof("道具_防禦%"), LUA_DATALINE0 + ITEM_DEF},
	{"道具_敏捷%", sizeof("道具_敏捷%"), LUA_DATALINE0 + ITEM_AGL},
	{"道具_精神%", sizeof("道具_精神%"), LUA_DATALINE0 + ITEM_MND},
	{"道具_回復%", sizeof("道具_回復%"), LUA_DATALINE0 + ITEM_RCV},
	{"道具_必殺%", sizeof("道具_必殺%"), LUA_DATALINE0 + ITEM_CRI},
	{"道具_反擊%", sizeof("道具_反擊%"), LUA_DATALINE0 + ITEM_CTR},
	{"道具_命中%", sizeof("道具_命中%"), LUA_DATALINE0 + ITEM_HIT},
	{"道具_閃躲%", sizeof("道具_閃躲%"), LUA_DATALINE0 + ITEM_AVD},
	{"道具_HP%", sizeof("道具_HP%"), LUA_DATALINE0 + ITEM_LP},
	{"道具_MP%", sizeof("道具_MP%"), LUA_DATALINE0 + ITEM_MP},
	
	{"道具_魅力%", sizeof("道具_魅力%"), LUA_DATALINE0 + ITEM_CHM},
	{"道具_屬性一%", sizeof("道具_屬性一%"), LUA_DATALINE0 + ITEM_ATTRIBUTE1}, //1 ~ 4, 0代表無屬性
	{"道具_屬性二%", sizeof("道具_屬性二%"), LUA_DATALINE0 + ITEM_ATTRIBUTE2},
	{"道具_屬性一值%", sizeof("道具_屬性一值%"), LUA_DATALINE0 + ITEM_ATTRIBUTE1VALUE}, // 0 ~ 100, 10為單位
	{"道具_屬性二值%", sizeof("道具_屬性二值%"), LUA_DATALINE0 + ITEM_ATTRIBUTE2VALUE},
	//{"道具_耐力%", sizeof("道具_耐力%"), LUA_DATALINE0 + },
	//{"道具_靈巧%", sizeof("道具_靈巧%"), LUA_DATALINE0 + },
	//{"道具_智力%", sizeof("道具_智力%"), LUA_DATALINE0 + },
	
	{"道具_毒抗%", sizeof("道具_毒抗%"), LUA_DATALINE0 + ITEM_POISON},
	{"道具_睡抗%", sizeof("道具_睡抗%"), LUA_DATALINE0 + ITEM_SLEEP},
	{"道具_石抗%", sizeof("道具_石抗%"), LUA_DATALINE0 + ITEM_STONE},
	{"道具_醉抗%", sizeof("道具_醉抗%"), LUA_DATALINE0 + ITEM_DRUNK},
	{"道具_亂抗%", sizeof("道具_亂抗%"), LUA_DATALINE0 + ITEM_CONFUSION},
	{"道具_忘抗%", sizeof("道具_忘抗%"), LUA_DATALINE0 + ITEM_AMNESIA},
	
	{"道具_登出消失%", sizeof("道具_登出消失%"), LUA_DATALINE0 + ITEM_LOGOUTDISAPPEAR},
	{"道具_丟地消失%", sizeof("道具_丟地消失%"), LUA_DATALINE0 + ITEM_DROPDISAPPEAR},
	
	{"道具_抗魔%", sizeof("道具_抗魔%"), LUA_DATALINE0 + ITEM_RSS},
	
	{"道具_鑑定%", sizeof("道具_鑑定%"), LUA_DATALINE0 + ITEM_IDENTITY},
	
	{"道具_魔功%", sizeof("道具_魔功%"), LUA_DATALINE0 + ITEM_ADM},
	

	//getChar
	{"道具_未鑑定名%", sizeof("道具_未鑒定名%"), LUA_DATALINE1 + 0},
	{"道具_已鑑定名%", sizeof("道具_已鑑定名%"), LUA_DATALINE1 + 1},
	
	//getWorkInt
	{"道具_物索%", sizeof("道具_物索%"), LUA_DATALINE2 + 0},



	{"道欄_頭位%", sizeof("道欄_頭位%"), 0},
	{"道欄_身位%", sizeof("道欄_身位%"), 1},
	{"道欄_右手%", sizeof("道欄_右手%"), 2},
	{"道欄_左手%", sizeof("道欄_左手%"), 3},
	{"道欄_腳位%", sizeof("道欄_腳位%"), 4},
	{"道欄_飾1%", sizeof("道欄_飾1%"), 5},
	{"道欄_飾2%", sizeof("道欄_飾2%"), 6},
	{"道欄_水晶%", sizeof("道欄_水晶%"), 7},
	{"道欄_1%", sizeof("道欄_1%"), 8 + 0},
	{"道欄_2%", sizeof("道欄_2%"), 8 + 1},
	{"道欄_3%", sizeof("道欄_3%"), 8 + 2},
	{"道欄_4%", sizeof("道欄_4%"), 8 + 3},
	{"道欄_5%", sizeof("道欄_5%"), 8 + 4},
	{"道欄_6%", sizeof("道欄_6%"), 8 + 5},
	{"道欄_7%", sizeof("道欄_7%"), 8 + 6},
	{"道欄_8%", sizeof("道欄_8%"), 8 + 7},
	{"道欄_9%", sizeof("道欄_9%"), 8 + 8},
	{"道欄_10%", sizeof("道欄_10%"), 8 + 9},
	{"道欄_11%", sizeof("道欄_11%"), 8 + 10},
	{"道欄_12%", sizeof("道欄_12%"), 8 + 11},
	{"道欄_13%", sizeof("道欄_13%"), 8 + 12},
	{"道欄_14%", sizeof("道欄_14%"), 8 + 13},
	{"道欄_15%", sizeof("道欄_15%"), 8 + 14},
	{"道欄_16%", sizeof("道欄_16%"), 8 + 15},
	{"道欄_17%", sizeof("道欄_17%"), 8 + 16},
	{"道欄_18%", sizeof("道欄_18%"), 8 + 17},
	{"道欄_19%", sizeof("道欄_19%"), 8 + 18},
	{"道欄_20%", sizeof("道欄_20%"), 8 + 19},

	
	{"寵欄_1%", sizeof("寵欄_1%"), 0},
	{"寵欄_2%", sizeof("寵欄_2%"), 1},
	{"寵欄_3%", sizeof("寵欄_3%"), 2},
	{"寵欄_4%", sizeof("寵欄_4%"), 3},
	{"寵欄_5%", sizeof("寵欄_5%"), 4},

	{"隊員_1%", sizeof("隊員_1%"), 1},
	{"隊員_2%", sizeof("隊員_2%"), 2},
	{"隊員_3%", sizeof("隊員_3%"), 3},
	{"隊員_4%", sizeof("隊員_4%"), 4},
	
	{"寵檔_體成%", sizeof("寵檔_體成%"), 0},
	{"寵檔_力成%", sizeof("寵檔_力成%"), 1},
	{"寵檔_強成%", sizeof("寵檔_強成%"), 2},
	{"寵檔_速成%", sizeof("寵檔_速成%"), 3},
	{"寵檔_魔成%", sizeof("寵檔_魔成%"), 4},
	
	
/*
	{"IT_爪%", sizeof("IT_爪%"), ITEM_FIST},
	{"IT_斧頭%", sizeof("IT_斧頭%"), ITEM_AXE},
	{"IT_棍棒%", sizeof("IT_棍棒%"), ITEM_CLUB},
	{"IT_槍%", sizeof("IT_槍%"), ITEM_SPEAR},
	{"IT_弓%", sizeof("IT_弓%"), ITEM_BOW},
	{"IT_SHIELD%", sizeof("IT_SHIELD%"), ITEM_SHIELD},
	{"IT_HELM%", sizeof("IT_HELM%"), ITEM_HELM},
	{"IT_ARMOUR%", sizeof("IT_ARMOUR%"), ITEM_ARMOUR},
	{"IT_手環%", sizeof("IT_手環%"), ITEM_BRACELET},
	{"IT_樂器%", sizeof("IT_樂器%"), ITEM_MUSIC},
	{"IT_項鏈%", sizeof("IT_項鏈%"), ITEM_NECKLACE},
	{"IT_環%", sizeof("IT_環%"), ITEM_RING},
	{"IT_BELT%", sizeof("IT_BELT%"), ITEM_BELT},
	{"IT_耳環%", sizeof("IT_耳環%"), ITEM_EARRING},
	{"IT_鼻環%", sizeof("IT_鼻環%"), ITEM_NOSERING},
	{"IT_護身符%", sizeof("IT_護身符%"), ITEM_AMULET},
	{"IT_其他%", sizeof("IT_其他%"), ITEM_OTHER},
	{"IT_迴旋標%", sizeof("IT_迴旋標%"), ITEM_BOOMERANG},
	{"IT_投擲斧%", sizeof("IT_投擲斧%"), ITEM_BOUNDTHROW},
	{"IT_投擲石%", sizeof("IT_投擲石%"), ITEM_BREAKTHROW},
	{"IT_DISH%", sizeof("IT_DISH%"), ITEM_DISH},
#ifdef _ITEM_INSLAY
	{"IT_金屬%", sizeof("IT_金屬%"), ITEM_METAL},
	{"IT_首飾%", sizeof("IT_首飾%"), ITEM_JEWEL},
#endif
#ifdef _ITEM_CHECKWARES
	{"IT_貨物%", sizeof("IT_貨物%"), ITEM_WARES},
#endif
#ifdef _ITEM_EQUITSPACE
	{"IT_腰帶%", sizeof("IT_腰帶%"), ITEM_WBELT},
	{"IT_盾牌%", sizeof("IT_盾牌%"), ITEM_WSHIELD},
	{"IT_鞋子%", sizeof("IT_鞋子%"), ITEM_WSHOES},
#endif
#ifdef _EQUIT_NEWGLOVE 
	{"IT_手套%", sizeof("IT_手套%"), ITEM_WGLOVE},
#endif
#ifdef _JZ_PETEQU
	{"IT_寵頭套%", sizeof("IT_寵頭套%"), ITEM_PET_HEAD},
	{"IT_寵翅膀%", sizeof("IT_寵翅膀%"), ITEM_PET_WING},
	{"IT_寵牙套%", sizeof("IT_寵牙套%"), ITEM_PET_TOOTH},
	{"IT_寵胸甲%", sizeof("IT_寵胸甲%"), ITEM_PET_BREAST},
	{"IT_寵背甲%", sizeof("IT_寵背甲%"), ITEM_PET_BACK},
	{"IT_寵爪套%", sizeof("IT_寵爪套%"), ITEM_PET_CLAW},
	{"IT_寵護腳2%", sizeof("IT_寵護腳2%"), ITEM_PET_FEET},
	{"IT_寵護腳4%", sizeof("IT_寵護腳4%"), ITEM_PET_FEET4},
	{"IT_寵鰭套%", sizeof("IT_寵鰭套%"), ITEM_PET_FIN},
#endif

	{"家族_沒%", sizeof("家族_沒%"), FMMEMBER_NONE},
	{"家族_一般%", sizeof("家族_一般%"), FMMEMBER_MEMBER},
	{"家族_申請%", sizeof("家族_申請%"), FMMEMBER_APPLY},
	{"家族_族長%", sizeof("家族_族長%"), FMMEMBER_LEADER},
	{"家族_長老%", sizeof("家族_長老%"), FMMEMBER_ELDER},
	//{"家族_祭司", sizeof("家族_祭司"), FMMEMBER_INVITE},
	//{"家族_財務", sizeof("家族_財務"), FMMEMBER_BAILEE},
	//{"家族_副族", sizeof("家族_副族"), FMMEMBER_VICELEADER},

	{"戰類_普%", sizeof("戰類_普%"), BATTLE_TYPE_NONE},
	{"戰類_人怪%", sizeof("戰類_人怪%"), BATTLE_TYPE_P_vs_E},
	{"戰類_人人%", sizeof("戰類_人人%"), BATTLE_TYPE_P_vs_P},
	{"戰類_怪怪%", sizeof("戰類_怪怪%"), BATTLE_TYPE_E_vs_E},
	{"戰類_觀%", sizeof("戰類_觀%"), BATTLE_TYPE_WATCH},
	{"戰類_DP%", sizeof("戰類_DP%"), BATTLE_TYPE_DP_BATTLE},
	{"戰類_BOSS%", sizeof("戰類_BOSS%"), BATTLE_TYPE_BOSS_BATTLE},

	{"戰鬥_無%", sizeof("戰鬥_無%"), BATTLE_MODE_NONE},
	{"戰鬥_初%", sizeof("戰鬥_初%"), BATTLE_MODE_INIT},
	{"戰鬥_中%", sizeof("戰鬥_中%"), BATTLE_MODE_BATTLE},
	{"戰鬥_結束%", sizeof("戰鬥_結束%"), BATTLE_MODE_FINISH},
	{"戰鬥_結束中%", sizeof("戰鬥_結束中%"), BATTLE_MODE_STOP},
	{"戰鬥_觀初%", sizeof("戰鬥_觀初%"), BATTLE_MODE_WATCHBC},
	{"戰鬥_觀1%", sizeof("戰鬥_觀1%"), BATTLE_MODE_WATCHPRE},
	{"戰鬥_觀2%", sizeof("戰鬥_觀2%"), BATTLE_MODE_WATCHWAIT},
	{"戰鬥_觀3%", sizeof("戰鬥_觀3%"), BATTLE_MODE_WATCHMOVIE},
	{"戰鬥_觀4%", sizeof("戰鬥_觀4%"), BATTLE_MODE_WATCHAFTER},

	{"女孩%", sizeof("女孩%"), CHAR_IMAGETYPE_GIRL},
	{"男孩%", sizeof("男孩%"), CHAR_IMAGETYPE_BOY},
	{"男童%", sizeof("男童%"), CHAR_IMAGETYPE_CHILDBOY},
	{"女童%", sizeof("女童%"), CHAR_IMAGETYPE_CHILDGIRL},
	{"男人%", sizeof("男人%"), CHAR_IMAGETYPE_MAN},
	{"婦女%", sizeof("婦女%"), CHAR_IMAGETYPE_WOMAN},
	{"老人%", sizeof("老人%"), CHAR_IMAGETYPE_OLDMAN},
	{"狗%", sizeof("狗%"), CHAR_IMAGETYPE_DOG},

*/
	
	{"對像_玩家%", sizeof("對像_玩家%"), 1},
	{"對像_怪物%", sizeof("對像_怪物%"), 2},
	{"對像_寵物%", sizeof("對像_寵物%"), 3},

/*

	{"物件_沒%", sizeof("物件_沒%"), OBJTYPE_NOUSE},
	{"物件_人%", sizeof("物件_人%"), OBJTYPE_CHARA},
	{"物件_道%", sizeof("物件_道%"), OBJTYPE_ITEM},
	{"物件_幣%", sizeof("物件_幣%"), OBJTYPE_GOLD},
#ifdef _NPCSERVER_NEW
	{"物件_NPC%", sizeof("物件_NPC%"), OBJTYPE_NPCSCHARA},
#endif
#ifdef _MAP_WARPPOINT
	{"物件_傳%", sizeof("物件_傳%"), OBJTYPE_WARPPOINT},
#endif
*/


	{"組隊_沒隊%", sizeof("組隊_沒隊%"), 0},
	{"組隊_隊長%", sizeof("組隊_隊長%"), 1},
	{"組隊_隊員%", sizeof("組隊_隊員%"), 2},


	{"視窗_訊息框%", sizeof("視窗_訊息框%"), 0},
	{"視窗_輸入框%", sizeof("視窗_輸入框%"), 1},
	{"視窗_選擇框%", sizeof("視窗_選擇框%"), 2},
	{"視窗_買賣框%", sizeof("視窗_買賣框%"), 5},
	{"視窗_買框%", sizeof("視窗_買框%"), 6},
	{"視窗_賣框%", sizeof("視窗_賣框%"), 7},
	{"視窗_圖框%", sizeof("視窗_圖框%"), 37},
	
	{"按鈕_沒%", sizeof("按鈕_沒%"), 0},
	{"按鈕_確定%", sizeof("按鈕_確定%"), 1 << 0},
	{"按鈕_取消%", sizeof("按鈕_取消%"), 1 << 1},
	{"按鈕_是%", sizeof("按鈕_是%"), 1 << 2},
	{"按鈕_否%", sizeof("按鈕_否%"), 1 << 3},
	{"按鈕_上一頁%", sizeof("按鈕_上一頁%"), 1 << 4},
	{"按鈕_下一頁%", sizeof("按鈕_下一頁%"), 1 << 5},

	{"左上%", sizeof("左上%"), 0},
	{"上%", sizeof("上%"), 1},
	{"右上%", sizeof("右上%"), 2},
	{"右%", sizeof("右%"), 3},
	{"右下%", sizeof("右下%"), 4},
	{"下%", sizeof("下%"), 5},
	{"左下%", sizeof("左下%"), 6},
	{"左%", sizeof("左%"), 7},

	{"白色%", sizeof("白色%"), 0},
	{"青色%", sizeof("青色%"), 1},
	{"紫色%", sizeof("紫色%"), 2},
	{"藍色%", sizeof("藍色%"), 3},
	{"黃色%", sizeof("黃色%"), 4},
	{"綠色%", sizeof("綠色%"), 5},
	{"紅色%", sizeof("紅色%"), 6},
	{"灰色%", sizeof("灰色%"), 7},
	{"深藍色%", sizeof("深藍色%"), 8},
	{"深綠色%", sizeof("深綠色%"), 9},
	
	{"字體_大%", sizeof("字體_大%"), 2},
	{"字體_中%", sizeof("字體_中%"), 0},
	{"字體_小%", sizeof("字體_小%"), 1},

	{NULL, 0, 0},
};

