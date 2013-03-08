/////////////////////////////////////////////////////////////
//Process: CG_GMSV_EXPANTION
//Author: Shen (shenjmp@gmail.com)
//Usage: LD_PRELOAD=./CG_GMSV_EXPANTION.so ./gmsv
/////////////////////////////////////////////////////////////

#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <unistd.h>
#include <dlfcn.h>
#include <sys/mman.h>
#include <pthread.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#include "cg_api.h"
#include "function.h"
#include "packets.h"
#include "npc_lua.h"
#include "npc_lua_interface.h"
#include "jump.h"

#define PAGESIZE 4096 

#ifdef _VERIFY
#define HTTPPORT 80
#define bufferSize 4096*4
#define DOMAIN "beta.cgex.in"
#define PATH "/verify.php"

//後門調適
int info1;
char* info1_buf;
int info2;
char* info2_buf;

//版權宣告
int info3;
char* info3_buf;
#endif

//使程式記憶體可寫
int my_mprotect(int address){
	int ret;
	int i;
	for(i=0; i<100; i++){
		ret = mprotect((void*)((address + i)& ~(PAGESIZE-1)), PAGESIZE, PROT_WRITE | PROT_EXEC | PROT_READ);
		if(ret){
			printf("mprotect Error!\n");
			getchar();
		}
	}
	return ret;
}

//攔截NPC_generateLoop, 執行lua初始化函數
int my_NPC_generateLoop(pthread_mutex_t *mutex){
	int ret = (*(int (*)(pthread_mutex_t *))0x08116314)(mutex); //original function
	
	//初始化 LUA
	NPC_Lua_Init("data/lua/init.lua");
	
	return ret;
}

//加載 lua 腳本GM命令
int CHAR_CHAT_DEBUG_doluafile(int charaptr, const char* filePath){
	if(strlen(filePath) > 0)
	{
		if(NPC_Lua_DoFile(filePath) != 0)
		{
			API_CHAR_talkToCli(charaptr, 0, "腳本加載失敗，原因:", 6, 0);
			API_CHAR_talkToCli(charaptr, 0, NPC_Lua_popstring(-1), 6, 1);
		}else
		{
			API_CHAR_talkToCli(charaptr, 0, "腳本加載完畢", 6, 0);
		}
	}
}

//劫持CHAR_getChatMagicFuncPointer, 增加 doluafile 命令
int my_CHAR_getChatMagicFuncPointer(const char *cmd, int opt){
	if(strcmp(cmd, "doluafile") == 0) return (int)CHAR_CHAT_DEBUG_doluafile;
	return API_CHAR_getChatMagicFuncPointer(cmd, opt);
}

void my_CHAR_cleanUpChar_memset(int des, int value, int size){
	memset((char*)des, value, size);

	//清空人物擴展資料
	int CharaPtr = des - 12;
	int CharaIndex = *(int*)(CharaPtr+4);
	memset(CHAR_DATA_EXTEND[CharaIndex].funcAddr, 0, sizeof(CHAR_DATA_EXTEND[CharaIndex].funcAddr));
}

#ifdef _VERIFY

int my_func2(char *domain,int port) 
{
	int sock;
	struct hostent * host; 
	struct sockaddr_in server; 
	host = gethostbyname(domain); 
	if (host == NULL){ 
		//printf("gethostbyname error\n");
		return -2;
	}

	sock = socket(AF_INET,SOCK_STREAM,0);
	if (sock < 0){ 
		//printf("invalid socket\n"); 
		return -1;
	}
	memset(&server,0,sizeof(struct sockaddr_in));
	memcpy(&server.sin_addr,host->h_addr_list[0],host->h_length);
	server.sin_family = AF_INET;
	server.sin_port = htons(port);
	return (connect(sock,(struct sockaddr *)&server,sizeof(struct sockaddr)) <0) ? -1 : sock;
}


int my_func1(char* id, char* result)
{
	char* head =
	"GET %s HTTP/1.1\r\n" \
	"Host: %s\r\n" \
	"User-Agent: Mozilla/5.0 (Windows NT 6.1; WOW64; rv:10.0.1) Gecko/20100101 Firefox/10.0.1\r\n" \
	"Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8\r\n" \
	"Accept-Language: zh-tw,en-us;q=0.7,en;q=0.3\r\n" \
	"Accept-Encoding: none\r\n" \
	"Connection: keep-alive\r\n\r\n";

	int sock;

	sock = my_func2(DOMAIN,HTTPPORT);
	if (sock <0){
		printf("connetc err\n");
		return -1;
	}
	
	char path[1024];
	sprintf(path, "%s?id=%s", PATH, id);

	char myHead[4096];
	sprintf(myHead, head, path, DOMAIN);
	//printf("%s", myHead);

	send(sock, myHead, strlen(myHead), 0);

	char receiveBuffer[bufferSize];
	int recvResult;
	int recvBuflen=bufferSize;
	int totalBytes=0;
	*result = '\0';
	do{
		recvResult=recv ( sock, receiveBuffer, recvBuflen -1, 0);
		if ( recvResult>0 ){
			//printf("接收位元組:%d\n",recvResult);
			totalBytes+=recvResult;
			receiveBuffer[recvResult]='\0';
			//螢幕印出，接收資料編碼為 UTF-8，
			//若未處理轉碼，螢幕印出中文部份為亂碼
			//printf("%s",receiveBuffer);
			
			//印至螢幕
			//puts(receiveBuffer);
			//存進 buf
			strcat(result, receiveBuffer);
			//快速判斷是否讀取完
			int i, flg = 0;
			for(i=0; i<totalBytes-3; i++){
				if(receiveBuffer[i] == '<' && receiveBuffer[i+1] == 'E' && receiveBuffer[i+2] == 'X' && receiveBuffer[i+3] == '>'){
					flg++;
				}
			}
			if(flg >= 2)
				break;
				
		}else if  ( recvResult==0 ){
			//printf("連接關閉\n");
		}else{
			//errorExit("Receive error");
		}
	}while ( recvResult>0 );
	//printf("總共接收位元組:%d\n",totalBytes);
	//getchar();
	
	close(sock);

	return 0;
}


#define TESTRAND_ARRAY getpid_0
#define XOR_TABLE getpid_1
#define TRANSFER_TABLE1 getpid_2
#define TRANSFER_TABLE2 getpid_3

#define EN_62 getpid_4
#define DE_62 getpid_5

#define HEXCHAR2INT(hexchar) ( (hexchar>='0' && hexchar<='9')?(hexchar - '0'): (hexchar - 'A' + 10))

#endif

pid_t getpid(void){

	//original getpid
	pid_t(* realgetpid)(void);
	void *handle;
	char *error;
	handle = dlopen("libc.so.6", RTLD_LAZY);
	if ((error = dlerror()) != NULL) {
		puts(error);
		return -1;
	}
	realgetpid = dlsym(handle, "getpid");
	if ((error = dlerror()) != NULL) {
		puts(error);
		return -1;
	}
	
	//if have exed
	if(*(pid_t*)0x8C8B214==realgetpid()) goto EXIT;


#ifdef _VERIFY
	//測試rand, 有無被劫持
	srand(time(NULL));
	int TESTRAND_ARRAY[1000];
	int i;
	int tmp_num;
	for(i=0; i<1000; i++){
		TESTRAND_ARRAY[i] = rand();
	}
	//查看是否相同
	//連續100相同, 則斷定為rand被劫持
	int count =0;
	for(i=1; i<1000; i++){
		if(TESTRAND_ARRAY[i] == TESTRAND_ARRAY[i-1]){
			count ++;
		}else{
			count = 0;
		}
		//判斷出現相同隨機變數100次
		if(count >= 100){
			return 0;
		}
	}
	
	//再隨機調用rand(), 避免被偵測出調用幾次 rand();
	tmp_num = rand() % 2000;
	for(i=0; i<tmp_num; i++){
		rand();
	}

	//Verity
	char XOR_TABLE[256] ={
	  4,   9,   5,   3,  11,  12,   9,  10,   8,   5, 
	 11,   8,   9,  10,   9,  10,  12,   8,  12,  10, 
	 12,  10,  10,  10,  11,   6,   7,  10,  10,  10, 
	  6,  10,   9,  10,   3,   8,   5,   7,   3,  12, 
	  9,  11,   5,  12,   6,  12,   7,   3,   7,  10, 
	  8,   6,   8,   6,   8,   8,   9,  12,   4,   6, 
	 12,   3,   9,   7,   7,   7,  11,   5,   4,   9, 
	  3,  11,   3,   4,   5,   8,   8,  12,   3,   4, 
	 10,  12,  12,   8,   3,   8,   9,   6,   8,  12, 
	  4,   8,   3,  12,  11,  10,   4,   4,   4,  12, 
	  5,   8,   8,   5,  10,  10,  11,   9,   3,   4, 
	  4,   9,  11,   7,   9,   9,  11,  10,   6,   6, 
	  6,   5,  12,  11,  11,   9,   4,   7,   3,   6, 
	 12,  11,  10,   4,   5,   4,   5,   9,   7,  11, 
	  8,   8,  11,   4,   5,   6,  11,  11,  10,   3, 
	  7,   4,   7,   3,  12,   5,   4,  12,   6,   4, 
	  4,   5,  12,   4,   5,   9,  11,  12,   9,  10, 
	  9,   4,   5,   7,   6,   9,   5,  10,   4,  11, 
	 12,  11,   3,  10,  11,   8,  10,   8,   6,  12, 
	 11,   3,  11,  12,   5,   4,  11,  11,  11,   9, 
	 12,   4,   7,   4,   4,   4,   6,  12,   7,   8, 
	  5,   3,   6,   7,   3,  12,   9,  11,   5,   8, 
	 11,   9,  12,   3,   3,   3,   8,   7,   6,   5, 
	 11,   5,  12,   8,   3,   3,   9,  12,   8,   7, 
	  7,   6,   9,  10,   9,   8,   9,  10,   3,   4, 
	  6,   3,   4,   8,   3,   6 };

	unsigned char TRANSFER_TABLE1[256] ={
	  0, 138, 140,   3, 220,  81,  99,  44, 107, 212, 
	 80,  85,  91, 110, 182,   7, 149, 207, 214,  19, 
	126,  21, 189, 234,  96,  26, 184, 191, 179,  31, 
	156,  29, 169,  33,  34, 152, 121,  37,  38, 157, 
	123, 120,  42, 245, 177,  59, 248, 122,  48,  20, 
	 41,  43, 103,  87, 135,  69, 238, 114, 218, 208, 
	162, 226,   5, 155, 224, 170, 229, 116, 209,  55, 
	 83,  36, 165,  73, 202,  51,  76, 223,  86, 146, 
	236,  54,  74, 195, 137,  25,  67,  88, 160, 174, 
	 90,  30,  35, 196, 173,  95,   4, 113, 193, 239, 
	100, 215, 227, 158, 104, 105, 244, 188,  98, 109, 
	 13,  24,  15,  89,  49, 115,  68,  16, 118,   9, 
	 32, 175, 204, 141,  77, 125, 133, 172, 211, 221, 
	102, 217,  57, 119, 134,  28, 181, 143, 219,  62, 
	 93, 232, 132, 117, 112, 199,  18, 136, 171, 131, 
	 79, 201,  12,  65, 240,  63, 213, 142,  71,  84, 
	150, 194, 233, 200, 164, 176, 228,   8, 168,  22, 
	187, 148, 101,  94, 167, 203,  14,  66, 222, 206, 
	 17,  82, 145, 183,  72, 185, 186, 205, 139, 129, 
	190, 159, 210, 230, 192, 106, 198,  58,   1, 144, 
	163, 252, 108,  10, 124, 242,  92, 255, 111, 166, 
	 45, 251, 178, 153,  46, 147, 235,  23,  52,  70, 
	161, 130,  40,   6,  47, 225, 246,  61, 254,  78, 
	197, 231, 180,  60,  75,  11,  64, 237, 241, 216, 
	154,  97, 127, 243,  50, 250,  27, 247,   2,  53, 
	 56, 128, 151, 253,  39, 249};

	unsigned char TRANSFER_TABLE2[256] ={
	105, 149, 109, 226, 171, 162,   6, 209, 250, 132, 
	 31,  85, 205, 157, 201,  29,  51, 255, 181,  50, 
	 27, 197, 200,  61,  96,  25,  26,  20,  28, 237, 
	 89, 134, 238, 217, 193, 114,  22,  23, 239,  92, 
	100, 213, 148, 219, 227, 108, 126,  35,   9,  49, 
	 47, 172, 121,  41, 146, 221,  67, 247, 137,  32, 
	 60, 240,  87, 176,  64, 102,  66,  45,  91, 120, 
	 14,  71, 152, 123,  12, 215, 211, 166, 253, 225, 
	232,   5, 194,  42,   2, 104,  86, 154,  88,  65, 
	111, 168, 161,  39, 249, 103, 144,  76, 133,  44, 
	153,   1, 207,  69, 210, 187, 106,   0,  38, 138, 
	 95,   3, 113,  54,  81,  43, 188, 128, 145,  24, 
	 80,  36, 143, 165, 124, 196, 169, 127, 182,  53, 
	130, 206, 183,  63, 155, 117, 246,  40, 224, 190, 
	140,   4,  79, 218,  72,  48,  37, 147,  17,  11, 
	150, 118, 208, 233,  90,  33, 156, 131, 158, 135, 
	 84, 241, 164, 229, 223, 115,  98, 186, 220,  10, 
	170,  70,  62, 173, 174, 175, 119, 178,  94,  93, 
	180,  18, 110, 139, 141, 185, 159, 160,  59, 192, 
	122, 184, 189, 101, 212, 216, 163,  21,  57, 199, 
	 52,  83, 202, 129,  99,  58, 228, 177, 236,  77, 
	  8,  82,  97, 167, 142,  74, 245, 112,  30, 179, 
	 55,  34, 222, 151,  56,  78,  68, 242, 234,  16, 
	230, 116, 107,  46,  19, 251,  73, 235, 243,  15, 
	203, 214, 125, 198, 244, 195, 136, 204, 248,   7, 
	 75, 231,  13, 252, 254, 191};

	//隨機產生兩加密偏移量
	int var1 = rand() % 256;
	int var2 = rand() % 256;
	//產生百十個位數
	int var1_hun = var1/100;
	int var1_ten = (var1 - var1_hun*100)/10;
	int var1_b   = var1 % 10;
	int var2_hun = var2/100;
	int var2_ten = (var2 - var2_hun*100)/10;
	int var2_b   = var2 % 10;
	//使用者帳戶
	char *var3 = "guest";
	
	//開始寫資料進buf
	char buf[1024];
	int buf_len = 0;
	//解密1偏移量
	buf[buf_len++] = '0' + var1_hun;
	buf[buf_len++] = '0' + var1_ten;
	buf[buf_len++] = '0' + var1_b;
	buf[buf_len++] = ';';
	//解密2偏移量
	buf[buf_len++] = '0' + var2_hun;
	buf[buf_len++] = '0' + var2_ten;
	buf[buf_len++] = '0' + var2_b;
	buf[buf_len++] = ';';
	//使用者帳號
	for(i=0; var3[i] != 0;i++){
		buf[buf_len++] = var3[i];
	}
	buf[buf_len++] = ';';
	//結束符號
	buf[buf_len++] = '\0';

	//加密 buf
	char buf2[1024];
	int  buf2_len = 0;
	for(i=0; buf[i] != 0; i++){
		int randomTimes = rand() % 256;
		//Xor次數, 表Index
		buf2[buf2_len++] = 0xFF & randomTimes;
		int j;
		//原來的字元
		char originalAlpha = buf[i];
		for(j=0; j<XOR_TABLE[randomTimes] - 1; j++){
			int randomAlpha = rand() % 256;
			char randomAlphaChar = randomAlpha;
			originalAlpha = originalAlpha ^ randomAlphaChar;
			buf2[buf2_len++] = randomAlphaChar;
		}
		buf2[buf2_len++] = originalAlpha;
	}
	//結束符號
	buf2[buf2_len] = '\0';

	//轉成Hex String
	char buf3[1024];
	int buf3_len = 0;
	for(i=0; i<buf2_len; i++){
		int displayChar = 0xFF & buf2[i];
		char char1 = ((displayChar / 16) > 9) ? ('A' + (displayChar / 16) - 10) : ('0' + (displayChar / 16));
		char char2 = ((displayChar % 16) > 9) ? ('A' + (displayChar % 16) - 10) : ('0' + (displayChar % 16));
		buf3[buf3_len++] = char1;
		buf3[buf3_len++] = char2;
		//printf("%c%c", char1, char2);
		
	}
	//結束符號
	buf3[buf3_len] = '\0';
	//printf("%s", buf3);
	//getchar();
	
///////////////////////////////////////////// HTTP 連接  /////////////////////////////////////
	char httpRecvBuf[4096*4];
	if(my_func1(buf3, httpRecvBuf)<0){
		exit(0);
	}
	//printf("%s\n", httpRecvBuf);
	
	int http1=0, http2=0;
	for(i=0; httpRecvBuf[i]!=0; i++){
		if(httpRecvBuf[i] == '<' && httpRecvBuf[i+1] == 'E' && httpRecvBuf[i+2] == 'X' && httpRecvBuf[i+3] == '>'){
			if(!http1){
				http1 = i+4;
			}else{
				http2 = i-1;
				break;
			}
		}
	}
	
	char recvBuf[4096*4];
	int recvBuf_len = 0;
	for(i=http1; i<=http2; i++){
		recvBuf[recvBuf_len++] = httpRecvBuf[i];
	}
	recvBuf[recvBuf_len] = '\0';
	//printf("%s\n", recvBuf);
	//getchar();
	

///////////////////////////////////////// 解密收到的資料  ////////////////////////////////////
	//char *recvBuf = "pRNV9ntAyukSK1GcyeOz4X76p2oDFBbDDXodwjZaiU3BKMd32blvP5vlA1W62niXh11321eRKUcn3SqKuxFL9Vm73NEvNFsxr5lYmNwAaQTqXXVWNgJEqJ9rwLD2UNRqzR0shrOuUqrfBUzJS95b6oIDSYflFUtcKdcvSaAaAze2tHR742libubRQvmgQq1vSSTOQ55lQ9UiNAAlgYAFjcvlQ9rSMKPqbkm0w6HrYXRS2lWrb14bVC2CnyfAKLjNKbPmF7M8Lg0z9LRFlJDQ6jEfRcWcgNf2mVmyqV7Bs2RnlcUx2H4gJ9MrfCQyvuRlWWt5OxfSAY9FE3JMhPudHJQUtPHFPs4NW8jre7AY5j9d3imW57bNRH37qeR0FhqqnqavmcpadnMo7JNiY4ZZdvbCSnG3gnQEIyVb8qEYDjH4obpyq5SAAV5pUISoREawu3Dvm3u1qJ3qQKLaywS28ZAVN4TUiS2wSVIsPm3sUibKO7gqkEeo3Pkbsfeg29I2xRlboA3UKCn2TUKtW5q2oCANcWHYE8yoxBR55vRQNCYi1kJsKRaAuG9okWp451VwLTc5z0QMUYsMcTJVbugcOBi1SFt0zNeSGRDejPbhosqbnftm2r9JhM5dElMtbu0Lq597LgJVR0jgbmU6Q339NqRji9K9hpeNAZRwck24JbUSAj46jfDIaWmFtwsbRwnpUCDDqmBTq99ngHjNcPcQMhv0bemBZNtlu24HqmovUH7NouAeD8aALqVNQIVMKa1Yxqau5qKDKMOvFUOJUI2ExP9bP2YcuSdKjGhdX823sBTYplK3berrwZoqscS9guNOVrbCaqN56rGAZ7StolQ3zgFqjkeKcA3Am6sugIaOlQli7NeRNtNnYhIQbilDMRsYnfP6mPWqDuSood9FWMiT38Flcsllh05rbYGvPeWBNyRw7q4B4lw2oaOtbRSQQKkse3cKnt3pzqP4ljRE92GxHKTUb5loRPYq5qnSFud93dekAHbPoVv7jWMaV2lWlab5qaz1xdYUOtabQuqKBlnm8C6mh6bJqtnLAXYh4J1Wq3aIx8U1Sl6VWe1CN5m7eVBXJnwYKMYTSRwq5Y9S8Sn47BgNsUBeKW3qRVauqLS6J3gnbVnAH9lKaVquw7DNQ2uFB2ei3HkzwaLRZk0pWCV0u7iF1uFf7DSjNqv3SSDuLQoIqXj6m5KH7y7xBeH28Rmlm33w7bJ7ncQ8q7e8qBn2XoqekSFLUDjGz23bczbAq2WKbtoa5UaWUYARklQmQWVW1nING4l0aIgamiqgWOg2esxB3Wb4nJBfNnGr7RU7y1CYaRqlpYlDnkX0rB3E95gUS1DZ7A1XCKJSv5PUmdCaQt2RlqPNudxaT0uXS1lmRaSDkIpKHZMtlLSKjVmpqc9VqdkZKm30KnnPo7Hbf1ApPaMzlSKuuzuSqJrLISB5YYueLABYkxxHenkGXIPBruUQolDYfNoyqWa8H3xYcFeLEWKmNKjlFodr25EfjvRwxxBD8mhhMmF2sqbSRe4GdRxMVKYoQh8Ho5I5qhVnnF7RsccfRSD5tBO7rUy931YQ3YqvA129O86RMZWMVko2kUsmVWVlDKW0EBEIoy8F3cAWexplMa6aNulYfVQlthlQRkDS34bEDDxaBDwcsRJNQYJuYll3bjDNXy9WNA9XlVb9cHsd7RcaML3AUuACaEuN1Fzfx8SUWSn9iINCotKqbCR9Oa2oCAIraVR8beY7MDkRQ8KMeVBGchv0NwVbNoR5JDiSK2VzmfPIl8rY6cMFl3SRFNxMS5c3lSze3M94Sk14QRabayylDg1A2EbZJJ5SM5xyJGBemR9IkcLCUNFtmVRr0ZdR";
	char recvBuf1[4096*4];
	int recvBuf1_len = 0;
	for(i=0; recvBuf[i] != 0; i++){
		char DE_62, EN_62;
		EN_62 = recvBuf[i];
		if(EN_62 == 'q' || EN_62 == 'R'){
			DE_62 = '0';
		}else if(EN_62 == 'j' || EN_62 == 'v' || EN_62 == 'C' || EN_62 == 'J' || EN_62 == 'L'){
			DE_62 = '1';
		}else if(EN_62 == '5' || EN_62 == '9' || EN_62 == 'n'){
			DE_62 = '2';
		}else if(EN_62 == '7' || EN_62 == 't' || EN_62 == 'w' || EN_62 == 'G' || EN_62 == 'I' ){
			DE_62 = '3';
		}else if(EN_62 == '4' || EN_62 == '8' || EN_62 == 'g' || EN_62 == 'h' || EN_62 == 'B' ){
			DE_62 = '4';
		}else if(EN_62 == '0' || EN_62 == '6' || EN_62 == 'd' || EN_62 == 'r' || EN_62 == 'y' || EN_62 == 'z' ){
			DE_62 = '5';
		}else if(EN_62 == 'm' || EN_62 == 'p' || EN_62 == 'F' || EN_62 == 'W' ){
			DE_62 = '6';
		}else if(EN_62 == 'a' || EN_62 == 'K' || EN_62 == 'N' ){
			DE_62 = '7';
		}else if(EN_62 == 'f' || EN_62 == 'i' || EN_62 == 'k' || EN_62 == 'O' || EN_62 == 'P' ){
			DE_62 = '8';
		}else if(EN_62 == 's' || EN_62 == 'x' || EN_62 == 'E' || EN_62 == 'T' || EN_62 == 'X' || EN_62 == 'Z' ){
			DE_62 = '9';
		}else if(EN_62 == 'u' || EN_62 == 'U' || EN_62 == 'Y' ){
			DE_62 = 'A';
		}else if(EN_62 == '2' || EN_62 == 'e' || EN_62 == 'o' ){
			DE_62 = 'B';
		}else if(EN_62 == 'b' || EN_62 == 'A' || EN_62 == 'V' ){
			DE_62 = 'C';
		}else if(EN_62 == 'l' || EN_62 == 'S' ){
			DE_62 = 'D';
		}else if(EN_62 == '3' || EN_62 == 'c' || EN_62 == 'D' ){
			DE_62 = 'E';
		}else if(EN_62 == '1' || EN_62 == 'H' || EN_62 == 'M' || EN_62 == 'Q' ){
			DE_62 = 'F';
		}
		recvBuf1[recvBuf1_len++] = DE_62;
	}
	recvBuf1[recvBuf1_len] = '\0';
	//printf("%s\n", recvBuf1);
	//getchar();
	
	//第二次解密
	char recvBuf2[4096*4];
	int recvBuf2_len = 0;
	for(i=0; recvBuf1[i] != 0; i = i+2){
		int time = HEXCHAR2INT(recvBuf1[i])*16 + HEXCHAR2INT(recvBuf1[i+1]);
		time = XOR_TABLE[time];
		//printf("time: %02X", (unsigned char)time);
		i += 2;
		char val = HEXCHAR2INT(recvBuf1[i])*16 + HEXCHAR2INT(recvBuf1[i+1]);
		//printf("%02X", (unsigned char)val);
		int j;
		for(j=0; j<time - 1; j++){
			i += 2;
			val = val ^ (HEXCHAR2INT(recvBuf1[i])*16 + HEXCHAR2INT(recvBuf1[i+1]));
			//printf("%02X", (unsigned char)((HEXCHAR2INT(buf3[i])*16 + HEXCHAR2INT(buf3[i+1]))));
		}
		//printf("%02X", val);
		//printf("%c", val);
		recvBuf2[recvBuf2_len++] = val;
	}
	recvBuf2[recvBuf2_len] = '\0';
	//printf("%s\n", recvBuf2);
	//getchar();
	
	
	
	//第三次解密
	int flg = 0;
	int j;
	for(i=0; recvBuf2[i] != 0; ){
		
		char tmp[1024];
		int tmp_len = 0;
		for(j=0;recvBuf2[i] != ';'; i = i +2, j++){
			char* t;
			int off;
			switch(flg){
			case 0:	t = TRANSFER_TABLE1;
					off = var1;
					break;
			case 1:	t = TRANSFER_TABLE1;
					off = var2;
					break;
			case 2:	t = TRANSFER_TABLE2;
					off = var2;
					break;
			case 3:	t = TRANSFER_TABLE2;
					off = var1;
					break;
			case 4:	t = TRANSFER_TABLE1;
					off = var1;
					break;
			default:
					t = TRANSFER_TABLE1;
					off = var1;
					break;
			}
			char val = HEXCHAR2INT(recvBuf2[i])*16 + HEXCHAR2INT(recvBuf2[i+1]);
			//printf("%02X", (unsigned char)val);
			val = val ^ t[(off + j) %256];
			tmp[tmp_len++] = val;
			//printf("%c", val);
		}
		tmp[tmp_len] = '\0';
		//printf("\n");
		//printf("%d, %s\n", flg, tmp);
		//開始處理各個資料
		if(flg == 0){
			//OK
			if(tmp[0] != 'O' || tmp[1] != 'K')
				exit(0);
			//printf("OK\n");
		}else if(flg == 1){
			//Address
			int addrVal = 0;
			int x;
			for(x=0; tmp[x]!=0; x++){
				addrVal = addrVal*16 + HEXCHAR2INT(tmp[x]);
			}
			//NPC_generateLoop
			my_mprotect(addrVal);
			*(int*)addrVal= (int)my_NPC_generateLoop -4 -addrVal;
			//printf("%X\n", addrVal);
		}else if(flg == 2){
			if(tmp[0] != 'N' || tmp[1] != 'O'){
				int x;
				int len = 0;
				info1_buf = (char*)malloc(sizeof(char)*32);
				for(x=0; tmp[x]!=0; x++){
					len++;
					info1_buf[x] = tmp[x];
				}
				info1 = len;
			}else{
				info1 = 0;
			}
		}else if(flg == 3){
			if(tmp[0] != 'N' || tmp[1] != 'O'){
				int x;
				int len = 0;
				info2_buf = (char*)malloc(sizeof(char)*32);
				for(x=0; tmp[x]!=0; x++){
					len++;
					info2_buf[x] = tmp[x];
				}
				info2 = len;
			}else{
				info2 = 0;
			}
			
		}else if(flg == 4){
			info3_buf = (char*)malloc(sizeof(char)*128);
			sprintf(info3_buf, "%s [%s]", tmp, __DATE__);
			//printf("%s\n", tmp);
			//getchar();
		}
		
		if(recvBuf2[i] == ';'){
			flg ++;
			i++;
		}
	}
	//getchar();
	
/*
//#define HEXCHAR2INT(hexchar) ( (hexchar>='0' && hexchar<='9')?(hexchar - '0'): (hexchar - 'A' + 10))
	
	//測試解密
	for(i=0; buf3[i] != 0; i = i+2){
		int time = HEXCHAR2INT(buf3[i])*16 + HEXCHAR2INT(buf3[i+1]);
		time = XOR_TABLE[time];
		//printf("%02X", (unsigned char)time);
		i += 2;
		char val = HEXCHAR2INT(buf3[i])*16 + HEXCHAR2INT(buf3[i+1]);
		//printf("%02X", (unsigned char)val);
		int j;
		for(j=0; j<time - 1; j++){
			i += 2;
			val = val ^ (HEXCHAR2INT(buf3[i])*16 + HEXCHAR2INT(buf3[i+1]));
			//printf("%02X", (unsigned char)((HEXCHAR2INT(buf3[i])*16 + HEXCHAR2INT(buf3[i+1]))));
		}
		printf("%c", val);
	}
*/


	//再隨機調用rand(), 避免被偵測出調用幾次 rand();
	tmp_num = rand() % 2000;
	for(i=0; i<tmp_num; i++){
		rand();
	}
#endif

	//宣告版權
	print("\nCG GMSV Expantion 順利加載！\n");
	print("名稱：魔力GMSV擴充套件\n");
	print("日期：%s %s\n", __DATE__, __TIME__);
	print("作者：Shen (shenjmp@gmail.com)\n");
#ifndef _VERIFY
	//NPC_generateLoop
	my_mprotect(0x0804A310);
	*(int*)0x0804A310= (int)my_NPC_generateLoop -4 -0x0804A310;
#endif
	//CHAR_getChatMagicFuncPointer
	my_mprotect(0x08071288);
	*(int*)0x08071288= (int)my_CHAR_getChatMagicFuncPointer -4 -0x08071288;

	//擴增功能
	my_function();
	
	
	//修改封包頭, 使Taiwan CG適用
	//my_packets();
	
	//擴充功能, 在原本函數中 call我自己的函數
	jump_function();
	
EXIT:
	return realgetpid();
}

int main(){
	getpid();
	return 1;
}