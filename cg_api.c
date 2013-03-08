#include "cg_api.h"

#define IS_2BYTEWORD( _a_ ) ( (char)(0x80) <= (_a_) && (_a_) <= (char)(0xFF) )
#define min( x,y ) ({typeof(x) __x=(x),__y=(y);(__x < __y) ? __x : __y; })

//Util
char *strcpy_s(char *des, size_t n, const char *src)
{
	if(des == NULL)
	{
		return NULL;
	}
	if(src == NULL || n == 0)
	{
		des[0] = '\0';
		return NULL;
	}

	char *TM_RetChar = des;
	int i = 0;

	while( (*des++ = *src++) )
	{
		i++;
		if( i >= n ) 
		{
			i--;
			break;
		}
	}
	TM_RetChar[i] = '\0';
	return TM_RetChar;
}

char * ScanOneByte( char *src, char delim ){
	// Nuke
	if (!src) return NULL;

        //   »ú  ¤¬¤Ê¤¯¤Ê¤ë¤Þ¤Ç¸¡º÷
        for( ;src[0] != '\0'; src ++ ){
             // Á´³Ñ¤Î£±¥Ð¥¤¥È  ¤«¤É¤¦¤«¤ò¥Á¥§¥Ã¥¯
          if( IS_2BYTEWORD( src[0] ) ){
              // Á´³Ñ¤À¡e¤½¤Î¾ì¹ç¤Ï£±¥Ð¥¤¥ÈÍ¾Ê¬¤Ë¿Ê¤Þ¤»¤ë¡e
              // ¤¿¤À¤·£±¥Ð¥¤¥È¤·¤«¤Ê¤¤¾ì¹ç¤Ï¤½¤¦¤·¤Ê¤¤
              if( src[1] != 0 ){
                  src ++;
              }
              continue;
          }
          //   ³Ñ¤À¤Ã¤¿¡e¤³¤³¤ÇÂÐ¾Ý¤Î  »ú¤È  ³Ó
          if( src[0] == delim ){
              return src;
          }
        }
        // ¥ë¡¼¥×  ¤±¤¿¤é¸«¤Ä¤«¤é¤Ê¤«¤Ã¤¿¡e
        return NULL;
}

char* strncpy2( char* dest, const char* src, size_t n )
{
    if( n > 0 ){
        char*   d = dest;
        const char*   s = src;
        int i;
        for( i=0; i<n ; i++ ){
            if( *(s+i) == 0 ){
                /*  ¥³¥Ô¡¼¤·¶³¤ï¤Ã¤¿¤é NULL   »ú¤ò  ¤ì¤ë   */
                *(d+i) = '\0';
                return dest;
            }
            if( *(s+i) & 0x80 ){
                *(d+i)  = *(s+i);
                i++;
                if( i>=n ){
                    *(d+i-1)='\0';
                    break;
                }
                *(d+i)  = *(s+i);
            }else
                *(d+i) = *(s+i);
        }
    }
    return dest;
}

void strncpysafe( char* dest , const size_t n ,
                  const char* src ,const int length )
{
    /*
     * src ¤«¤é dest ¤Ë length ¥³¥Ô¡¼¤¹¤ë
     * strcpy, strncpy ¤Ç¤Ï dest ¤è¤ê ¥³¥Ô¡¼¤¹¤ë¬¤¤¬
     *   ¤­¤¤»þ¤Ë¸Æ¤Ö¤È,¥á¥â¥ê³°¥¢¥¯¥»¥¹¤¬µ¯¤ë.
     * ¤³¤Î´Ø¿ô¤Ç¤Ï¡bstrlen( src ) ¤È length ¤Î¾®¤µ¤¤¤Û¤¦
     * (  ºÝ¤Ë¥³¥Ô¡¼¤¹¤ë¬¤) ¤È dest ¤Î¥µ¥¤³N¤ò  ¤Ù¤Æ¡b
     * strcpysafe ¤È  ¤¸»ö¤ò¤¹¤ë¡e
     */

    int Short;
    Short = min( strlen( src ) , length );

    /* NULL  »ú ¤ò¹Í  ¤·¤¿  ³Ó */
    if( n < Short + 1 ){
        /*
         * ¥Ð¥Ã¥Õ¥¡¤¬Â­¤ê¤Ê¤¤¤Î¤Ç n - 1(NULL  »ú)
         * ¤Ç strncpy ¤ò¸Æ¤Ö
         */
        strncpy2( dest , src , n-1 );
        dest[n-1]='\0';

    }else if( n <= 0 ){
        return;
    }else{
        /*
         * ¥Ð¥Ã¥Õ¥¡¤Ï½½Ê¬¤Ë¤¢¤ë¤Î¤Ç Short ¤Çstrncpy¤ò¸Æ¤Ö
         * ¤Ê¶³ src ¤Ë¤Ï Short ¤ÎÄ¹¤µ  ¤Ë NULL ¤¬¤Ê¤¤¤Î¤Ç¡b
         * dest ¤Ë¤Ï ÄÉ²Ã¤·¤Æ¶³¤¯¡e
         */

        strncpy2( dest , src , Short );
        dest[Short]= '\0';

    }
}

void strcpysafe( char* dest ,size_t n ,const char* src )
{
    /*
     * src ¤«¤é dest ¤Ø¥³¥Ô¡¼¤¹¤ë.
     * strcpy, strncpy ¤Ç¤Ï dest ¤è¤ê ¥³¥Ô¡¼¤¹¤ë¬¤¤¬
     *   ¤­¤¤»þ¤Ë¸Æ¤Ö¤È,¥á¥â¥ê³°¥¢¥¯¥»¥¹¤¬µ¯¤ë.
     * ¤³¤ì¤ò  ¤°°Ù¤Ë, strncpy ¤¬¤¢¤ë¤¬ strlen( src ) ¤¬ n ¤è¤ê
     *   ¤­¤¤»þ¤Ë¤Ï, dest ¤Î    ¤¬ NULL   »ú¤È¤Ï¤Ê¤é¤Ê¤¤.
     *
     * ¤·¤¿¤¬¤Ã¤Æ dest ¤Î  ¤­¤µ¤è¤ê src ¤Î¤Û¤¦¤¬Ä¹¤¤»þ¤Ë¤Ï
     * n-1 ¤Ç strncpy ¤ò¤¹¤ë. ¾®¤µ¤¤»þ¤Ï¤½¤Î¤Þ¤Þ¥³¥Ô¡¼¤¹¤ë
     *
     * n ¤¬  ¤Î»þ¤Ï¶³¤«¤·¤¯¤Ê¤ë¤Î¤Ç  ¤Î»þ¤Ï ²¿¤â¤·¤Ê¤¤¡e
     *
     */
    // Nuke +1 (08/25): Danger if src=0
    if (!src) {
        *dest = '\0';
        return;
    }
    if( n <= 0 )        /* ²¿¤â¤·¤Ê¤¤   */
        return;

    /*  ¤³¤Î»þÅÀ¤Ç¡b n >= 1 °Ê¾å¤¬·èÄê  */
    /*  NULL  »ú¤ò¹Í  ¤·¤Æ  ³Ó¤¹¤ë  */
    else if( n < strlen( src ) + 1 ){
        /*
         * ¥Ð¥Ã¥Õ¥¡¤¬Â­¤ê¤Ê¤¤¤Î¤Ç n - 1(NULL  »ú)
         * ¤Ç strncpy ¤ò¸Æ¤Ö
         */
        strncpy2( dest , src , n-1 );
        dest[n-1]='\0';
    }else
        strcpy( dest , src );
}

int getStringFromIndexWithDelim_body( char* src ,char* delim ,int index,
                                 char* buf , int buflen ,
                                       char *file, int line )
{//ttom this function all change,copy from the second
    int i;          /* ¥ë¡¼¥×  ¿ô */
    int length =0;  /* ¼è¤ê½Ð¤·¤¿  »ú  ¤ÎÄ¹¤µ */
    int addlen=0;   /* Â­¤µ¤ì¤ëÄ¹¤µ */
    int oneByteMode = 0; /* £±¥Ð¥¤¥È¥â¡¼¥É¤«¡ª */
		char* last;
    if( strlen( delim ) == 1 ){ // ¸¡º÷¤¬£±¥Ð¥¤¥È¤Ê¤é£±¥Ð¥¤¥È¥â¡¼¥É¤Ë¤¹¤ë
        oneByteMode = 1;// ¤½¤ÎºÝ£²¥Ð¥¤¥È  »ú¤Ï¥Á¥§¥Ã¥¯¤·¤Ê¤¤
    }
    for( i =  0 ; i < index ; i ++ ){
    	
         src += addlen;/* ¤ß¤Ä¤«¤Ã¤¿Ä¹¤µ¤òÂ­¤¹ */
      
         if( oneByteMode ){
             // £±¥Ð¥¤¥È¥â¡¼¥É¤À¤Ã¤¿¤é¤³¤Á¤é¤Ç¸¡º÷
             last = ScanOneByte( src, delim[0] );
         }else{
                 last  = strstr( src , delim );  /* ¸«ÉÕ¤±¤ë */
         }
         if( last == NULL ){
            /*
             * ¤ß¤Ä¤«¤é¤Ê¤«¤Ã¤¿¤Î¤Ç¤¹¤Ù¤Æ¥³¥Ô¡¼¤·¤Æ return¡e
            */
            strcpysafe( buf , buflen, src );

            if( i == index - 1 )
                /*¤Á¤ç¤¦¤É¤ß¤Ä¤«¤Ã¤¿*/
                return 1;
                                                                                                           
                /*¤ß¤Ä¤«¤é¤Ê¤«¤Ã¤¿*/
             return 0;
          }
          
          /*
           * ¤ß¤Ä¤«¤Ã¤¿½ê¤È  ½é¤Î°Ì  ¤Îº¹¤òµá¤á¤ë
           * ¤Ä¤Þ¤ê¶èÀÚ¤é¤ì¤Æ¤¤¤ë  »ú  ¤ÎÄ¹¤µ
          */
          length = last - src;
                                           
          /*
           * ±­¤Î¥ë¡¼¥×¤Î°Ù¤Ë¤ß¤Ä¤«¤Ã¤¿Ä¹¤µ¤È delim ¤ÎÄ¹¤µ¤òÂ­¤·¤Æ¶³¤¯
          */
          addlen= length + strlen( delim );
       }
       strncpysafe( buf, buflen , src,length );

       return 1;
}

//API
int API_NPC_CHECKCREATEINDEX(int a1){
	return (*(int ( *)(int))0x0811A81C)(a1);
}

CHARAPTR API_CHAR_getLinkChar(int type){ //NPC type ¬° 2
	return (*(CHARAPTR ( *)(int))0x080669D8)(type);
}

int API_CHAR_doInitEvent(CHARAPTR a1){
	return (*(int ( *)(CHARAPTR))0x080670A8)(a1);
}

int API_initObjectFromObjectMember(int a1, CHARAPTR a2, int mapid, int floorid, int x, int y){
	return (*(int ( *)(int, CHARAPTR, int, int, int, int))0x08056AFC)(a1, a2, mapid, floorid, x, y);
}

int API_CHAR_cleanUpChar(CHARAPTR a1){
	return (*(int ( *)(CHARAPTR))0x08066B0C)(a1);
}

int API_CHAR_endCharOneArray(CHARAPTR a1){
	return (*(int ( *)(CHARAPTR))0x080674BC)(a1);
}

int API_MAP_sendAroundMapdata(int mapid, int floorid, int x, int y){
	return (*(int ( *)(int, int, int, int))0x080F7C9C)(mapid, floorid, x, y);
}

int API_CHAR_sendWatchEvent(OBJINDEX a1, int a2, int a3, int a4, int a5){
	return (*(int ( *)(OBJINDEX, int, int, int, int))0x0806C8B0)(a1, a2, a3, a4, a5);
}

int API_CHAR_sendCToArroundCharacter(OBJINDEX a1){
	return (*(int ( *)(OBJINDEX))0x08076FC4)(a1);
}

int API_CHAR_talkToCli(CHARAPTR to, CHARAPTR talker, char* msg, int fontcolor, int fontsize){
	return (*(int ( *)(CHARAPTR, CHARAPTR, char*, int, int))0x08071D48)(to, talker, msg, fontcolor, fontsize);
}

int API_CHAR_CharaDelete(CHARAPTR a1){
	return (*(int ( *)(CHARAPTR))0x0806CE3C)(a1);
}

int API_CHAR_CheckCharPointer(CHARAPTR a1)
{
	int result; // eax@3

	if ( a1 >= *(int*)0x10D0BEBC && a1 < *(int*)0x10D0BEBC + 6100 * *(int*)0x10D0BEA0 + 0x237AFBC )
	{
		result = 0;
		if ( !((a1 - *(int*)0x10D0BEBC) % 6100) )
			result = *(int*)a1 != 0;
	}
	else
	{
		result = 0;
	}
	return result;
}

/*
int API_CHAR_complianceParameter_sub(int a1, int a2, int a3){
	//signed int __usercall CHAR_complianceParameter<eax>(int a1<ebx>, int a2, int a3)
	__asm__ __volatile__("push %ecx");
	__asm__ __volatile__("push 0x10(%ebp)"); //push a3
	__asm__ __volatile__("push 0x0C(%ebp)"); //push a2
	__asm__ __volatile__("mov 0x08(%ebp), %ebx"); //±Na1¦s¶iebx
	__asm__ __volatile__("mov $0x0806DBC0, %ecx"); //ecx¥Î¨ÓÀx¦s¸õÂà¦ì¸m, ±`¼Æ«e­n¥[$
	__asm__ __volatile__("call %ecx");
	__asm__ __volatile__("pop %ecx");// ¨ú¥N add esp, 4
	__asm__ __volatile__("pop %ecx");// ¨ú¥N add esp, 4
	__asm__ __volatile__("pop %ecx");
}

int API_CHAR_complianceParameter(CHARAPTR a1, CHARAPTR a2, int a3){
	return API_CHAR_complianceParameter_sub(a1, a2, a3);
	//return (*(int ( *)(CHARAPTR, CHARAPTR, int))(int)API_CHAR_complianceParameter_sub)(a1, a2, a3);
}
*/

int API_CHAR_complianceParameter(CHARAPTR a1, int a2){
	return (*(int ( *)(CHARAPTR, int))0x0806DBC0)(a1, a2);
}


inline int API_GetCharaPtrFromCharaIndex(CHARAINDEX index){
	return *(int*)0x10D0BEBC + 6100 * index;
}

int API_CHAR_getEnablePlayerMaxNum()
{
  return *(int*)0x81AA680;
}

int API_BATTLE_WatchEntry(CHARAPTR watcher, CHARAPTR to)
{
	return (*(int ( *)(CHARAPTR, CHARAPTR))0x080B0F74)(watcher, to);
}

int API_CHAR_walk(CHARAPTR charptr, int direction, int type){ //0:move, 1:turn
	return (*(int ( *)(CHARAPTR, int, int))0x0807C3F4)(charptr, direction, type);
}

int API_NPC_Util_charIsInFrontOfChar(CHARAPTR char1, CHARAPTR char2, int distance){
	return (*(int ( *)(CHARAPTR, CHARAPTR, int))0x08116754)(char1, char2, distance);
}

int API_OBJECT_getType(int a1)
{
	int result;

	if ( *(int*)0x81A9FE8 <= a1 || a1 < 0 )
		result = -1;
	else
		result = *(int *)(*(int*)0x81A9FE4 + 52 * a1);
	return result;
}

int API_OBJECT_getIndex(int a1)
{
	return *(int *)(*(int*)0x81A9FE4 + 52 * a1 + 4);
}

int API_OBJECT_getMapId(int a1)
{
	return *(int *)(*(int*)0x81A9FE4 + 52 * a1 + 8);
}

int API_OBJECT_getFloor(int a1)
{
	return *(int *)(*(int*)0x81A9FE4 + 52 * a1 + 20);
}

int API_OBJECT_getX(int a1)
{
	return *(int *)(*(int*)0x81A9FE4 + 52 * a1 + 12);
}

int API_OBJECT_getY(int a1)
{
	return *(int *)(*(int*)0x81A9FE4 + 52 * a1 + 16);
}

int API_OBJECT_setType(int a1, int a2)
{
	int result;

	result = *(int *)(*(int*)0x81A9FE4 + 52 * a1);
	*(int *)(*(int*)0x81A9FE4 + 52 * a1) = a2;
	return result;
}

int API_OBJECT_setIndex(int a1, int a2)
{
	int result;

	result = *(int *)(*(int*)0x81A9FE4 + 52 * a1 + 4);
	*(int *)(*(int*)0x81A9FE4 + 52 * a1 + 4) = a2;
	return result;
}

int API_OBJECT_setMapId(int a1, int a2)
{
	int result;

	result = *(int *)(*(int*)0x81A9FE4 + 52 * a1 + 8);
	*(int *)(*(int*)0x81A9FE4 + 52 * a1 + 8) = a2;
	return result;
}

int API_OBJECT_setFloor(int a1, int a2)
{
	int result;
	
	result = *(int *)(*(int*)0x81A9FE4 + 52 * a1 + 20);
	*(int *)(*(int*)0x81A9FE4 + 52 * a1 + 20) = a2;
	return result;
}

int API_OBJECT_setX(int a1, int a2)
{
	int result;

	result = *(int *)(*(int*)0x81A9FE4 + 52 * a1 + 12);
	*(int *)(*(int*)0x81A9FE4 + 52 * a1 + 12) = a2;
	return result;
}

int API_OBJECT_setY(int a1, int a2)
{
	int result;

	result = *(int *)(*(int*)0x81A9FE4 + 52 * a1 + 16);
	*(int *)(*(int*)0x81A9FE4 + 52 * a1 + 16) = a2;
	return result;
}

int API_CHAR_sendCharaAtWalk(int a1, int a2, int a3, int a4, int a5, int a6, int a7){
	return (*(int ( *)(int, int, int, int, int, int, int))0x0807C9F8)(a1, a2, a3, a4, a5, a6, a7);
}

int API_CHAR_getDX(int a1){
	return (*(int ( *)(int))0x080710D4)(a1);
}

int API_CHAR_getDY(int a1){
	return (*(int ( *)(int))0x08071110)(a1);
}

int API_MAP_objmove(char* a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8, int a9, int a10, int a11){
	return (*(int ( *)(char*, int, int, int, int, int, int, int, int, int, int))0x080F7698)(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11);
}


int API_SYSTEMMSG(int a1, int a2){
	return (*(int ( *)(int, int))0x08071E40)(a1, a2);
}

int API_CHAR_setFlg(int a1, int a2, int a3, int a4, int a5){
	return (*(int ( *)(int, int, int, int, int))0x08065158)(a1, a2, a3, a4, a5);
}

int API_CHAR_getFlg(int a1, int a2, int a3, int a4){
	return (*(int ( *)(int, int, int, int))0x08068E84)(a1, a2, a3, a4);
}

int API_BATTLE_CreateBattle(){
	return (*(int ( *)())0x080A3BC8)();
}

int API_MAP_getfloorIndex(int a1, int a2, int a3){
	return (*(int ( *)(int, int, int))0x080F7E34)(a1, a2, a3);
}


int API_CHAR_getCharPointer(int a1, int a2, int a3){
	return (*(int ( *)(int, int, int))0x08068DFC)(a1, a2, a3);
}

int API_BATTLE_PartyNewEntry(int a1, int a2, int a3){
	return (*(int ( *)(int, int, int))0x080A4A84)(a1, a2, a3);
}

int API_ENEMY_getEnemy(int a1, int a2, int a3, int a4, int a5, int a6, int a7){
	return (*(int ( *)(int, int, int, int, int, int, int))0x08092018)(a1, a2, a3, a4, a5, a6, a7);
}

int API_NPC_Util_getEnemy(int a1, int a2, int a3, int a4, int a5, int a6){
	return (*(int ( *)(int, int, int, int, int, int))0x08129888)(a1, a2, a3, a4, a5, a6);
}

int API_NPC_Util_GetDungeonSeqNo(int a1){
	return (*(int ( *)(int))0x08129044)(a1);
}

int API_NPC_getWorkPointer(int a1){
	return (*(int ( *)(int))0x08117818)(a1);
}

int API_ITEMBOX_getMimicEncountArray(int a1){
	return (*(int ( *)(int))0x080F0124)(a1);
}

int API_NPC_ItemboxEX_getEnemy(int a1, int a2, int a3, int a4, int a5, int a6){
	return (*(int ( *)(int, int, int, int, int, int))0x0814AE40)(a1, a2, a3, a4, a5, a6);
}

int API_ENEMY_getEnemyFromEncountArray(int a1, int a2, int a3, int a4, int a5, int a6){
	return (*(int ( *)(int, int, int, int, int, int))0x08091660)(a1, a2, a3, a4, a5, a6);
}

int API_BATTLE_BossCheck(int a1){
	return (*(int ( *)(int))0x0809273C)(a1);
}

int API_BATTLE_GetFieldNo(int a1, int a2, int a3){
	return (*(int ( *)(int, int, int))0x080A58B0)(a1, a2, a3);
}

int API_BATTLE_ListRand(int a1){
	return (*(int ( *)(int))0x080A57FC)(a1);
}

int API_ENEMY_createEnemy(int a1, int a2, int a3){
	return (*(int ( *)(int, int, int))0x08090DD0)(a1, a2, a3);
}

int API_BATTLE_NewEntry(int a1, int a2, int a3, int a4){
	return (*(int ( *)(int, int, int, int))0x080A3F74)(a1, a2, a3, a4);
}

int API_CHAR_getUseName(int a1){
	return (*(int ( *)(int))0x0806B084)(a1);
}

int API_ITEM_TohelosFloorCheck(int a1){
	return (*(int ( *)(int))0x080EC2F0)(a1);
}

int API_getfdFromChar(int a1){
	return (*(int ( *)(int))0x08050038)(a1);
}

int API_BATTLE_ExitAll(int a1){
	return (*(int ( *)(int))0x080A5510)(a1);
}

//usercall
int API_BATTLE_DeleteBattle(int a1){
	return (*(int ( *)(int))0x080A56E8)(a1);
}

int API_nrproto_EN_send(int a1, int a2, int a3){
	return (*(int ( *)(int, int, int))0x081545FC)(a1, a2, a3);
}

int API_CHAR_updateGraphic(int a1){
	return (*(int ( *)(int))0x0806DA54)(a1);
}

int API_CHAR_sendBattleEffect(int a1, int a2){
	return (*(int ( *)(int, int))0x08077A54)(a1, a2);
}

int API_CHAR_getPartyCharPointer(int a1, int a2){
	return (*(int ( *)(int, int))0x08072190)(a1, a2);
}

int API_RAND(int a1, int a2){
	return (*(int ( *)(int, int))0x0804E950)(a1, a2);
}

int API_ENEMY_getEnemyArrayFromId(int a1){
	return (*(int ( *)(int))0x080904EC)(a1);
}

int API_BATTLE_CHECKINDEX(int index){
	if(index >= *(int*)0x8C89CA4 || index<0) return 0;
	else return 1;
}

int API_CHAR_sendAction(int charptr, int action, int mode){
	return (*(int ( *)(int, int, int))0x080777F0)(charptr, action, mode);
}

void API_CHAR_processWindow(int charaptr, int seqno, int select, int objindex, char* data ){
	(*(void ( *)(int, int, int, int, char*))0x0806ECD4)(charaptr, seqno, select, objindex, data);
}

void API_nrproto_WN_send(int fd,int windowtype,int buttontype,int seqno,int objindex,char* data){
	(*(void ( *)(int, int, int, int, int, char*))0x08156964)(fd, windowtype, buttontype, seqno, objindex, data);
}

int API_CHAR_DischargePartyNoMsg(int a1){
	return (*(int ( *)(int))0x08072D90)(a1);
}

int API_CHAR_ParamUp(int a1, int a2){
	return (*(int ( *)(int, int))0x0806E38C)(a1, a2);
}

int API_CHAR_getObjectIndexFromChar(int charaptr){
	if(API_CHAR_CheckCharPointer(charaptr)) return *(int*)(charaptr + 1360);
	else return -1;
}

int API_CHAR_PartyWarp(int charaptr, int mapid, int floor, int x, int y){
	return (*(int ( *)(int, int, int, int, int))0x08070EF0)(charaptr, mapid, floor, x, y);
}

int API_MAP_IsValidCoordinate(int mapid, int floor, int x, int y){
	return (*(int ( *)(int, int, int, int))0x080F72A0)(mapid, floor, x, y);
}

char* API_makePartyParamString(int charaptr, char *buf){
	return (*(int ( *)(int, char*))0x08077364)(charaptr, buf);
}

int API_nrproto_PP_send(int fd, char* buf){
	return (*(int ( *)(int, char*))0x08155CB4)(fd, buf);
}

int API_CHAR_sendPartyParamAll(int charaptr)
{
	int v9;
	char v10[1024*4];
	char v11[1024*4];
	int i;

	int ret = 0;
	if ( API_CHAR_CheckCharPointer(charaptr) )
	{
		if ( *(int *)(charaptr + 1556) )
		{
			v10[0] = 0;
		
			for(i=0; i<5; i++)
			{
				int patryMemberPtr = API_CHAR_getPartyCharPointer(charaptr, i);
				if ( patryMemberPtr )
				{
					API_makePartyParamString(patryMemberPtr, v11);
					strcat(v10, v11);
				}
			}
		
			for(i=0; i<5; i++)
			{
				int patryMemberPtr = API_CHAR_getPartyCharPointer(charaptr, i);
				if ( patryMemberPtr )
				{
					int fd = API_getfdFromChar(patryMemberPtr);
					if ( fd != -1 )
						API_nrproto_PP_send(fd, v10);
				}
			}
		
			ret = 1;
		}
		else
		{
			ret = 0;
		}
	}
	return ret;
}

int API_CHAR_sendBattleDuel(int a1, int a2){
	return (*(int ( *)(int, int))0x0806F400)(a1, a2);
}

int API_CHAR_RingWatch(int a1){
	return (*(int ( *)(int))0x0808BEBC)(a1);
}

int API_BATTLE_DuelPointCheck(int a1){
	return (*(int ( *)(int))0x080A588C)(a1);
}

int API_CHAR_getPlayerMaxNum()
{
  return *(int*)0x81AA680;
}

int API_BATTLE_getBattleFieldNo(int a1, int a2, int a3, int a4){
	return (*(int ( *)(int, int, int, int))0x080A3D4C)(a1, a2, a3, a4);
}

int API_CHAR_checkEffect(int a1){
	return (*(int ( *)(int))0x080708D4)(a1);
}

int API_CHAR_getChatMagicFuncPointer(const char *cmd, int opt){
	return (*(int ( *)(int, const char *))0x08071184)(cmd, opt);
}

int API_CHAR_getHavePetCharPointer(int a1, int a2){
	return (*(int ( *)(int, int))0x0806A474)(a1, a2);
}

int API_ENEMY_getEnemyNum()
{
  return *(int*)0x81EED24;
}

int API_ENEMY_getInt(int a1, int a2)
{
  return *(int *)(*(int*)0x10D0E180 + 4 * (a2 + 79 * a1));
}

int API_PET_createPetFromCharaIndex(int a1, int a2){
	return (*(int ( *)(int, int))0x08094F8C)(a1, a2);
}

int API_CHAR_send_KP_String(int a1, int a2, int a3){
	return (*(int ( *)(int, int, int))0x08078EB4)(a1, a2, a3);
}

int API_CHAR_send_KP2_String(int a1, int a2, int a3){
	return (*(int ( *)(int, int, int))0x08079414)(a1, a2, a3);
}

int API_CHAR_sendPetTechData(int a1, int a2){
	return (*(int ( *)(int, int))0x08079DE4)(a1, a2);
}

int API_ENEMYTEMP_getEnemyTempArray(int a1){
	return (*(int ( *)(int))0x0808FD08)(a1);
}

int API_LogPet(int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8, int a9, int a10)
{
  return (*(int ( *)(int, int, int, int, int, int, int, int, int, int))0x080582D0)(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10);
}

int API_PET_stopFieldPet(int a1, int a2)
{
	
	int v3;
	int result;
	int v7;
	int v8;
	int v9;

	v3 = API_CHAR_CheckCharPointer(a1);
	result = 0;
	if ( v3 )
	{
		v9 = API_CHAR_getHavePetCharPointer(a1, a2);
		v7 = API_CHAR_CheckCharPointer(v9);
		if ( v7 )
		{
			API_CHAR_ObjectDelete(*(int *)(v9 + 1360));
			v8 = *(int *)(a1 + 12) == 1;
			*(int *)(v9 + 1360) = -1;
			*(int *)(v9 + 288) = 0;
			if ( v8 )
				API_CHAR_send_KP_String(a1, a2, 1<<24);
			API_LogPet(
				a1 + 712,
				a1 + 648,
				v9 + 648,
				v9 + 680,
				*(int *)(v9 + 44),
				(int)"Stop Field Pet",
				*(int *)(a1 + 24),
				*(int *)(a1 + 28),
				*(int *)(a1 + 32),
				*(int *)(a1 + 36));
			result = 1;
		}
	}
	return result;
}



int API_PET_stopRidePet(int charaPtr)
{
	int v2;
	int v3;
	int v5;
	int v6;
	int v7;
	int v8;
	int v9;
	int v10;
	int v11;
	int v12;
	int v13;
	int v14;
	int v15;

	v2 = API_CHAR_CheckCharPointer(charaPtr);
	v3 = 0;
	if ( v2 )
	{
		if ( *(int *)(charaPtr + 12) != 1 )
			return 0;
		v5 = API_CHAR_getHavePetCharPointer(charaPtr, *(int *)(charaPtr + 1504));
		if ( !v5 )
		{
			*(int *)(charaPtr + 1504) = -1;
			*(int *)(charaPtr + 1516) = 100;
			API_CHAR_send_CP2_String(charaPtr, 262144);
			return 0;
		}
		*(int *)(charaPtr + 1504) = -1;
		*(int *)(charaPtr + 1516) = 100;
		v13 = -1;
		v14 = -1;
		v15 = -1;
		API_CHAR_sendWatchEvent(*(int *)(charaPtr + 1360), 70, (int)&v13, 3, 1);
		API_CHAR_sendInjuryEffect(charaPtr);
		API_CHAR_send_CP2_String(charaPtr, 262144);
		v6 = *(int *)(charaPtr + 1100);
		*(int *)(v5 + 1588) = 0;
		if ( v6 && v6 != 6 )
		{
			*(int *)(v5 + 48) = *(int *)(v5 + 1592);
			*(int *)(v5 + 52) = *(int *)(v5 + 1600);
		}
		//API_CHAR_complianceParameter(v5, v5, 1);
		API_CHAR_complianceParameter(v5, 1);
		v7 = API_PET_getHavePetIndex(v5);
		API_CHAR_send_KP_String(charaPtr, v7, 31864);
		v8 = 0;
		while ( API_CHAR_getSkillId("char/pet.c", 1554, charaPtr, v8) != 1009 )
		{
			++v8;
			if ( v8 > 14 )
				goto API_PET_stopRidePet_LABEL_1;
		}
		v9 = API_SKILL_getSkillIndex(1009);
		API_TECH_setSkillExp(charaPtr, v9, v8, *(int *)(charaPtr + 1512) / 5, (int)&v10, (int)&v11, (int)&v12);
API_PET_stopRidePet_LABEL_1:
		*(char *)(charaPtr + 1428) = 0;
		v3 = 1;
	}
	return v3;
}

int API_CHAR_sendInjuryEffect(int a1){
	return (*(int ( *)(int))0x0807722C)(a1);
}

int API_PET_getHavePetIndex(int a1)
{
	int v2;
	int v3;
	int v5;
	int v6;
	int v7;
	
	v2 = API_CHAR_CheckCharPointer(a1);
	v3 = -1;
	if ( v2 )
	{
		v5 = *(int *)(a1 + 1556);
		v6 = API_CHAR_CheckCharPointer(a1);
		v3 = -1;
		if ( v6 )
		{
			v7 = 0;
			while ( API_CHAR_getHavePetCharPointer(v5, v7) != a1 )
			{
				++v7;
				if ( v7 > 4 )
					return -1;
			}
			v3 = v7;
		}
	}
	return v3;
}

int API_CHAR_getSkillId(int a1, int a2, int a3, int a4){
	return (*(int ( *)(int, int, int, int))0x08069738)(a1, a2, a3, a4);
}

int API_SKILL_getSkillIndex(int a1){
	return (*(int ( *)(int))0x081092B0)(a1);
}

int API_TECH_setSkillExp(int a1, int a2, int a3, int a4, int a5, int a6, int a7){
	return (*(int ( *)(int, int, int, int, int, int, int ))0x0810D74C)(a1, a2, a3, a4, a5, a6, a7);
}

int API_CHAR_ObjectDelete(int a1){
	return (*(int ( *)(int))0x0806CDF0)(a1);
}

int API_CHAR_send_CP2_String(int a1, int a2){
	return (*(int ( *)(int, int))0x08078758)(a1, a2);
}

int API_CHAR_setHavePetCharPointer(int a1, int a2, int a3){
	return (*(int ( *)(int, int, int))0x0806A668)(a1, a2, a3);
}

int API_CONNECT_isCLI(int a1)
{
	return *(int *)(*(int *)0x8C8B260 + 139592 * a1 +  4) == 2;
}

int API_CONNECT_isLOGIN(int a1)
{
	return *(int *)(*(int *)0x8C8B260 + 139592 * a1 + 44) == 1;
}

int API_CHAR_walk_init(int a1, int a2, int a3, int a4, int a5){
	return (*(int ( *)(int, int, int, int, int))0x0807C90C)(a1, a2, a3, a4, a5);
}

int _API_MAP_getTopObj(char* file, int line, int mapid, int floor, int x, int y){
	return (*(int ( *)(char*, int, int, int, int, int ))0x080F79A4)(file, line, mapid, floor, x, y);
}

int API_GET_OBJINDEX(int object){
	return *(int *)(object + 48);
}

int API_NEXT_OBJECT(int object){
	return *(int *)(object + 44);
}

int API_CHAR_getSameCoordinateObjects(int* objbuf, int siz, int mapid, int ff, int fx, int fy){
	return (*(int ( *)(int*, int, int, int, int, int))0x0806E184)(objbuf, siz, mapid, ff, fx, fy);
}

int API_CHAR_findEmptyItemBox(int charaPtr){
	return (*(int ( *)(int))0x0807DE6C)(charaPtr);
}

int  API_ITEM_makeItemAndRegist(int itemID){
	return (*(int ( *)(int))0x080E7958)(itemID);
}

int _API_CHAR_setItemIndex(char* file, int line, int charaptr, int pos, int itemindex){
	return (*(int ( *)(char*, int, int, int, int))0x080653A8)(file, line, charaptr, pos, itemindex);
}

int _API_CHAR_getItemIndex(char* file, int line, int charaptr, int pos){
	return (*(int ( *)(char*, int, int, int))0x080690C8)(file, line, charaptr, pos);
}

int _API_CHAR_unsetItem(char* file, int line, int charaptr, int pos){
	return (*(int ( *)(char*, int, int, int))0x080692E4)(file, line, charaptr, pos);
}

int _API_ITEM_endExistItemsOne(char* file, int line, int itemindex){
	return (*(int ( *)(char*, int, int))0x080E3318)(file, line, itemindex);
}

int API_ITEM_setCharPointer(int a1, int a2){
	return (*(int ( *)(int, int))0x080EAD00)(a1, a2);
}

int API_CHAR_sendItemDataOne(int a1, int a2){
	return (*(int ( *)(int, int))0x0807AEEC)(a1, a2);
}

int API_LogItem(int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8){
	return (*(int ( *)(int, int, int, int, int, int, int, int))0x08058244)(a1, a2, a3, a4, a5, a6, a7, a8);
}

//¬Û¹ïªº¨ç¼Æ API_GetCharaPtrFromCharaIndex
inline int API_CHAR_getCharaIndex(int charaPtr){
	if(charaPtr)
	{
		return *(int*)(charaPtr + 4);
	}
	else
	{
		return -1;
	}
	
}

int _API_ITEM_CHECKINDEX(char* file, int line, int itemindex){
	return (*(int ( *)(char*, int, int))0x080EA7D8)(file, line, itemindex);
}

int API_ITEM_getInt(int itemindex, int flg){
	return (*(int ( *)(int, int))0x080EA908)(itemindex, flg);
}

int API_ITEM_setInt(int itemindex, int flg, int value){
	return (*(int ( *)(int, int, int))0x080EAA74)(itemindex, flg, value);
}

char* API_ITEM_getChar(int itemindex, int flg){
	return (*(char* ( *)(int, int))0x080E3510)(itemindex, flg);
}

int API_ITEM_setChar(int itemindex, int flg, char* str){
	return (*(int ( *)(int, int, char*))0x080EAB24)(itemindex, flg, str);
}

int API_ITEM_getWorkInt(int itemindex, int flg){
	return (*(int ( *)(int, int))0x080EAC6C)(itemindex, flg);
}

int API_ITEM_setWorkInt(int itemindex, int flg, int value){
	return (*(int ( *)(int, int, int))0x080EACB0)(itemindex, flg, value);
}

int API_DB_getMysqlIndex(){
	return (*(int ( *)())0x08059078)();
}

int API_DB_releaseMySqlIndex(int a1){
	return (*(int ( *)(int))0x080590D4)(a1);
}

int API_mysql_query(int mysql, char* str){
	return (*(int ( *)(int, char*))0x0804A03C)(mysql, str);
}

char* API_mysql_error(int mysql){
	return (*(char* ( *)(int))0x08049E9C)(mysql);
}

int API_mysql_store_result(int mysql){
	return (*(int ( *)(int))0x08049A4C)(mysql);
}

int API_mysql_num_rows(int mysql_res){
	return (*(int ( *)(int))0x08049D4C)(mysql_res);
}

int API_mysql_num_fields(int mysql_res){
	return (*(int ( *)(int))0x08049EAC)(mysql_res);
}

char** API_mysql_fetch_row(int mysql_res){
	return (*(const char** ( *)(int))0x08049A8C)(mysql_res);
}

int API_mysql_free_result(int mysql_res){
	return (*(int ( *)(int))0x08049F2C)(mysql_res);
}

int API_mysql_init(int mysql){
	return (*(int ( *)(int))0x08049AFC)(mysql);
}

int API_mysql_real_connect(int mysql, char* ip, char* user, char* pass, char* db, int port, char* unix_socket, long client_flag){
	return (*(int ( *)(int, char*, char*, char*, char*, int, char*, long))0x0804A08C)(mysql, ip, user, pass, db, port, unix_socket, client_flag);
}

int API_mysql_close(int mysql){
	return (*(int ( *)(int))0x08049D2C)(mysql);
}

int API_CHAR_getWorkFlg(char* file, int line, int charaPtr, int flg){
	return (*(int ( *)(char*, int, int, int))0x0806902C)(file, line, charaPtr, flg);
}