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
#ifdef _PERSONAL_FAME	// Arminius 8.30: �a�ڭӤH�n��
#define MAX_PERSONALFAME 100000000
#endif
#ifdef _PROFESSION_SKILL			// WON ADD �H��¾�~�ޯ�
#define CHAR_SKILLMAXHAVE   26		// ¾�~�ޯ�W��
#else
#define CHAR_SKILLMAXHAVE   5
#endif

#ifdef _STREET_VENDOR
#define MAX_SELL_ITEM 20					// �D��[�d���@�i��G�Q��
#endif
#define CHAR_TITLEMAXHAVE   30

#define NULLSKILL   "0"

#define CHAR_MAXPETHAVE         5
#define CHAR_MAXPERSONAGOLD		50000000

#ifdef _ADD_POOL_ITEM			   // WON ADD �W�[�i�H�񪺹D��
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
#define CHAR_POISONSTRING           "���r"
#define CHAR_RECOVERPOISONSTRING    "�Ѭr�F"
#define CHAR_PARALYSISSTRING        "�·��F"
#define CHAR_RECOVERPARALYSISSTRING "�¾K�h�F"
#define CHAR_SILENCESTRING          "�L�k���]�k�F"
#define CHAR_RECOVERSILENCESTRING   "�i�H���]�k�F"
#define CHAR_STONESTRING            "�ۤƤF"
#define CHAR_RECOVERSTONESTRING     "���F���F"
#define CHAR_DARKNESSSTRING         "�|�P�����F"
#define CHAR_RECOVERDARKNESSSTRING  "�|�P�X�{�F"
#define CHAR_CONFUSIONSTRING        "���J���W"
#define CHAR_RECOVERCONFUSIONSTRING "��_���`"

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
    //���L Event, Recipe, Album
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
    CHAR_ISUNKNOWN, //����
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
