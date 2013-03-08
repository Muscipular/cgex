#ifndef __CHAR_BASE_H__
#define __CHAR_BASE_H__

#include "version.h"
#include "skill.h"
#include "title.h"
/*#include "magicinfo.h"*/
#include "addressbook.h"

#define CHAR_DELIMITER "\n"

#define NONCHAR_DELIMITER "|"

#define STATUSSENDDELIMITER "|"

#define CHAR_MAXGOLDHAVE    (100*10000)
#define CHAR_MAXBANKGOLDHAVE    (1000*10000)
#define CHAR_MAXFMBANKGOLDHAVE	(10000*10000)

#ifdef _NEW_MANOR_LAW
#define MAX_PERSONAL_MOMENTUM 10000000
#endif
#ifdef _PERSONAL_FAME	// Arminius 8.30: 家族個人聲望
#define MAX_PERSONALFAME 100000000
#endif
#ifdef _PROFESSION_SKILL			// WON ADD 人物職業技能
#define CHAR_SKILLMAXHAVE   26		// 職業技能上限
#else
#define CHAR_SKILLMAXHAVE   5
#endif

#ifdef _STREET_VENDOR
#define MAX_SELL_ITEM 20					// 道具加寵物共可賣二十個
#endif
#define CHAR_TITLEMAXHAVE   30

#define NULLSKILL   "0"

#define CHAR_MAXPETHAVE         5
#define CHAR_MAXPERSONAGOLD		50000000

#ifdef _ADD_POOL_ITEM			   // WON ADD 增加可寄放的道具
#define CHAR_MAXPOOLPETHAVE         15
#else
#define CHAR_MAXPOOLPETHAVE         10
#endif

#define CHAR_MAXPETSKILLHAVE       7
#define CHAR_PARTYMAX           5
#define	CHAR_MAXATTRIB			100
#define CHAR_MAXUPLEVEL			200
#define	CHAR_MAXDUELPOINT		100000000
#define CHAR_DEFAULTMAXAI		(60)
#define CHAR_MAXVARIABLEAI		(100*100)
#define CHAR_MINVARIABLEAI		(-100*100)
#define CHAR_POISONSTRING           "中毒"
#define CHAR_RECOVERPOISONSTRING    "解毒了"
#define CHAR_PARALYSISSTRING        "麻痺了"
#define CHAR_RECOVERPARALYSISSTRING "麻醉退了"
#define CHAR_SILENCESTRING          "無法念魔法了"
#define CHAR_RECOVERSILENCESTRING   "可以念魔法了"
#define CHAR_STONESTRING            "石化了"
#define CHAR_RECOVERSTONESTRING     "變靈活了"
#define CHAR_DARKNESSSTRING         "四周不見了"
#define CHAR_RECOVERDARKNESSSTRING  "四周出現了"
#define CHAR_CONFUSIONSTRING        "陷入恐慌"
#define CHAR_RECOVERCONFUSIONSTRING "恢復正常"

#ifdef _SAF_MAKE
#define CHAR_DEFAULTSEESIZ  23+4
#else
#define CHAR_DEFAULTSEESIZ  23
#endif
#define MAP_CHAR_DEFAULTSEESIZ      (CHAR_DEFAULTSEESIZ+4)


typedef enum
{
    CHAR_WhichType = 0,
    CHAR_BaseImageNumber,
    CHAR_BaseBaseImageNumber,
    CHAR_MapId,
    CHAR_Floor,
    CHAR_X,
    CHAR_Y,
    CHAR_Dir,
    CHAR_Lv,
    CHAR_Lp,
    CHAR_Fp,
    CHAR_Vital,
    CHAR_Str,
    CHAR_Tough,
    CHAR_Quick,
    CHAR_Magic,
    CHAR_Luck,
    CHAR_Tribe,
    CHAR_Attrib_Earth,
    CHAR_Attrib_Water,
    CHAR_Attrib_Fire,
    CHAR_Attrib_Wind,
    CHAR_Poison,
    CHAR_Sleep,
    CHAR_Stone,
    CHAR_Drunk,
    CHAR_Confusion,
    CHAR_Amnesia,
    CHAR_Critical,
    CHAR_Counter,
    CHAR_HitRate,
    CHAR_Avoid,
    CHAR_ItemLimit,
    CHAR_SkillSlot,
    CHAR_DeadCount,
    CHAR_DamageCount,
    CHAR_KillPetCount,
    CHAR_LastTimeSetLuck,
    CHAR_Injury,
    CHAR_WalkInterval,
    CHAR_LoopInterval,
    CHAR_Exp,
    CHAR_LevelUpPoint,
    CHAR_ImageType,
    CHAR_NameColor,
    CHAR_AllocPoint,
    CHAR_EatTime,
    CHAR_DataPlaceNumber,
    CHAR_RegistNumber,
    CHAR_MainJob,
    CHAR_JobRank,
    CHAR_JobAncestry,
    CHAR_FaceImageNumber,
    CHAR_Gold,
    CHAR_BankGold,
    CHAR_Stamina,
    CHAR_Dex,
    CHAR_Intelligence,
    CHAR_Charm,
    CHAR_Fame,
    CHAR_EquipTitle,
    CHAR_SavePoint,
    CHAR_DefaultPet,
    CHAR_ChatVolume,
    CHAR_HelpPoint,
    CHAR_LoginCount,
    CHAR_TalkCount,
    CHAR_GetPetCount,
    CHAR_SendMailCount,
    CHAR_MergeItemCount,
    CHAR_WalkCount,
    CHAR_DeadPetCount,
    CHAR_ResurrectPetCount,
    CHAR_HealPetCount,
    CHAR_CaptureCount,
    CHAR_OtherFlg,
    CHAR_FameGetValue,
    CHAR_FameGetTime,
    CHAR_FameAutoDownTime,
    CHAR_SickLevel,
    CHAR_RenewalFlg,
    //略過 Event, Recipe, Album
    CHAR_MaxPoolPetHaveLimit = 137,
    CHAR_MaxPoolItemHaveLimit,
    CHAR_DuelPoint,
    CHAR_PopupNameColor,
    CHAR_Position,
    CHAR_Debugger,
    CHAR_DungeonClr01,
    CHAR_DungeonClr02,
    CHAR_DungeonClr03,
    CHAR_LastSaveTime,
    CHAR_RankDownFlg,
    CHAR_Penalty,
    CHAR_LoginPoint,
    CHAR_FeverResetTime,
    CHAR_FeverHaveTime,
    CHAR_HouseId,
    CHAR_HouseLimit,
    CHAR_TimeOutDungeonId,
    CHAR_TimeOutServerNumber,
    CHAR_OriginalImageNumber,
		CHAR_DATAINTNUM = 157
}CHAR_DATAINT;

typedef enum
{
    CHAR_Name = 0,
    CHAR_OwnTitle,
    CHAR_CdKey,
    CHAR_DATACHARNUM
}CHAR_DATACHAR;

typedef enum
{
    CHAR_ISUNKNOWN, //未知
    CHAR_ISDIE,
    CHAR_ISSHOWBATTLEMSG,
    CHAR_ISPARTY,
    CHAR_ISDUEL,
    CHAR_ISPARTYCHAT,
    CHAR_ISTRADECARD,
    CHAR_ISTRADE,
    CHAR_ISFEVERTIME,
    CHAR_ISFAMILY,
    CHAR_ISDEBUG,
    CHAR_ISNOTENCOUNTER,
    CHAR_FLGNUM,
}CHAR_DATAFLG;


#endif
