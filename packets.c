#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <unistd.h>
#include <dlfcn.h>
#include "cg_api.h"
#include "packets.h"
#include "lssproto_util.h"

//���A��������
#define SER_VERSION "0070720"

//�ʥ]�Y�ƶq
int recvNum, sendNum;
//�ʥ]�Y���e
PACKETSHEAD* packetsHeadRecv;
PACKETSHEAD* packetsHeadSend;

//�ʥ]�u��
#define MAXLSRPCARGS ( 13 + 1 ) 
#define LSGENWORKINGBUFFER  65536*4
int lssproto_Init(	int (*writefunc)(int,char*,int) ,	int worksiz )
{
	int i;
	if( (void*)writefunc == NULL){lssproto.write_func = lssproto_default_write_wrap;} else {lssproto.write_func = writefunc;}
	lssproto_AllocateCommonWork(worksiz);
	lssproto_stringwrapper = (char**)calloc( 1,sizeof(char*) * MAXLSRPCARGS);
	if(lssproto_stringwrapper ==NULL)return -1;
	memset( lssproto_stringwrapper , 0, sizeof(char*)*MAXLSRPCARGS);
	for(i=0;i<MAXLSRPCARGS;i++){
		lssproto_stringwrapper[i] = (char*)calloc( 1, worksiz );
		if( lssproto_stringwrapper[i] == NULL){
			for(i=0;i<MAXLSRPCARGS;i++){free( lssproto_stringwrapper[i]);return -1;}
		}
	}
	lssproto.ret_work = (char*)calloc( 1,sizeof( worksiz ));
	if( lssproto.ret_work == NULL ){ return -1; }
	return 0;
}

void printStringByte(char* src){
	int i;
	for(i=0; i<strlen(src); i++)
	{
		printf("%02X ", src[i]);
	}
	printf("\n");
}

void stringSpaceHandle(char* src){
	int i;
	for(i=0; i<strlen(src); i++)
	{
		if(src[i] == 0x17)
			src[i] = 0x20;
	}
}

void my_nrproto_decodeString(const char *src, char *out){
	//�����ʥ]�Y
	int i;
	//��l�ƫʥ]�u��
	int msgid;
	char funcname[255];
	//�}�l�M��
	lssproto_strcpysafe( lssproto.work , src, lssproto.workbufsize );
	lssproto_splitString( lssproto.work);
	lssproto_GetMessageInfo( &msgid , funcname , sizeof(funcname),lssproto.token_list);
	for(i=0; i<sendNum; i++)
	{
		//���n�������ʥ]�Y
		if(!strcmp(funcname, packetsHeadSend[i].encode))
		{
			sprintf(out, "%s%s", packetsHeadSend[i].decode, &src[strlen(packetsHeadSend[i].encode)]);
			//�i���B�z�ʥ]���e
			if(!strcmp(packetsHeadSend[i].decode, "ClientLogin"))
			{
				sprintf(out, "%s %s %s %s %s", packetsHeadSend[i].decode, lssproto.token_list[3], lssproto.token_list[2], lssproto.token_list[3], SER_VERSION);
			}
			//�L�X�B�z�᤺�e
			printf("\nDecode: %s\n", out);
			printStringByte(out);
			return;
		}
	}
	//�䤣��������r��
	printf("\nmy_nrproto_decodeString: Can't find replace string!\n");
	printf("%s", src);
	//getchar();
}

void my_nrproto_encodeString(const char *src , char *out , int maxoutlen ){
	//�����ʥ]�Y
	int i;
	//��l�ƫʥ]�u��
	int msgid;
	char funcname[255];
	//�}�l�M��
	lssproto_strcpysafe( lssproto.work , src, lssproto.workbufsize );
	lssproto_splitString( lssproto.work);
	lssproto_GetMessageInfo( &msgid , funcname , sizeof(funcname),lssproto.token_list);
	for(i=0; i<recvNum; i++)
	{
		//���n�������ʥ]�Y
		if(!strcmp(funcname, packetsHeadRecv[i].decode))
		{
			snprintf(out, maxoutlen, "%s%s", packetsHeadRecv[i].encode, &src[strlen(packetsHeadRecv[i].decode)]);
/*
			//�i���B�z�ʥ]���e
			if(!strcmp(packetsHeadRecv[i].decode, "B"))
			{
				//new
				//C|0|
				//0|����Ŧ�Ȥۡ��|19B36|0|29|1E9|1F4|9E|4E9|2000005|0|0|
				
				//old
				//C|0|
				//0|Shen|187B5|1|AA|AA|41|41|2000005|0|1BE16|
				
				if(lssproto.token_list[1][0]=='C' && lssproto.token_list[1][1]=='|')
				{
					char buffer[1024*1024];
					char tmp[1024];
					getStringFromIndexWithDelim( lssproto.token_list[1], "|", 2, tmp, sizeof(tmp) );
					sprintf(buffer, "C|%s|", tmp);
					//�}�l�D�n�B�z
					int index = 3;
					while(getStringFromIndexWithDelim( lssproto.token_list[1], "|", index, tmp, sizeof(tmp) ) != 0)
					{
						if(strlen(tmp)==0) break;
						strcat(buffer, tmp);
						strcat(buffer, "|");
						
						//�[�W�B�~��0, �Ȯɤ�����@��
						if((index-3)%11 == 2)
						{
							strcat(buffer, "0|");
						}
						index++;
					}
					
					snprintf(out, maxoutlen, "%s %s", packetsHeadRecv[i].encode, buffer);
					
				}
				
			}
*/
			//�L�X�B�z�᤺�e
			printf("Encode: %s\n", out);
			printStringByte(out);
			return;
		}
	}
	//�䤣��������r��
	printf("\nmy_nrproto_encodeString: Can't find replace string!\n");
	printf("%s", src);
	//getchar();
}

int my_packets_read(char* filename, PACKETSHEAD* packetshead_ptr){
	FILE* fp;
	//�}��
	fp = fopen(filename, "rb");
	//�o���ɮפj�p, �ë�buffer
	fseek(fp,0,SEEK_END);
	int fp_size = ftell(fp);
	char* buf = (char *)malloc(sizeof(char)*fp_size);
	//Ū���e�i buf
	fseek(fp,0,SEEK_SET);
	fread(buf, 1, fp_size, fp);
	//����
	fclose(fp);

	//�}�l�ѪR
	int comment = 0;
	int state = 0; //0�N���bŪdecode, 1�N���bŪencode
	int j = 0;
	int ret_num = 0;
	
	int i;
	for(i=0; i<fp_size; i++){
		//#���ᬰ����
		if(buf[i]=='#')
		{
			//��������
			if(j!=0)
			{
				state = 0;
				packetshead_ptr[ret_num].encode[j] = 0; //�r�굲��
				packetshead_ptr[ret_num].use = 1;
				j = 0;
				ret_num++;
			}
			comment = 1;
			continue;
		}
		//�P�_�O�_�� comment�᪺�@�椺���r��
		if(comment) 
		{
			if(buf[i]==0x0D || buf[i]==0x0A)
			{
				comment = 0;
				state = 0; j = 0;
				continue;
			}
			continue; //�٨S�J��촫��
		}
		
		//�P�_�O�_������Ÿ� �� �ť� �� tab
		if(buf[i]==0x0D || buf[i]==0x0A || buf[i]==' ' || buf[i]=='\t')
		{
			if(state==0 && j!=0) //Ū��decode����
			{
				state = 1;
				packetshead_ptr[ret_num].decode[j] = 0; //�r�굲��
				j = 0;
			}else if(state==1 && j!=0) //Ū�� encode ����
			{
				state = 0;
				packetshead_ptr[ret_num].encode[j] = 0; //�r�굲��
				packetshead_ptr[ret_num].use = 1;
				j = 0;
				ret_num++;
			}
			continue;
		}
		
		//Ū���e�iPACKETSHEAD
		if(state==0)
		{
			packetshead_ptr[ret_num].decode[j] = buf[i];
			j++;
		}else{
			packetshead_ptr[ret_num].encode[j] = buf[i];
			j++;
		}
	}
	
	//�R�� buffer ���e
	free(buf);

	//�^�ǫʥ]�Y�`��
	return ret_num;
}

void my_packets(){

	//��l�ƫʥ]�u��
	lssproto_Init(NULL ,LSGENWORKINGBUFFER);

	//recv �ʥ]�Y
	packetsHeadRecv = (PACKETSHEAD*)malloc(sizeof(PACKETSHEAD)*MAX_PACKETSHEAD_NUM);
	memset(packetsHeadRecv, 0, sizeof(PACKETSHEAD)*MAX_PACKETSHEAD_NUM);
	//send �ʥ]�Y
	packetsHeadSend = (PACKETSHEAD*)malloc(sizeof(PACKETSHEAD)*MAX_PACKETSHEAD_NUM);
	memset(packetsHeadSend, 0, sizeof(PACKETSHEAD)*MAX_PACKETSHEAD_NUM);

	//Ū��
	recvNum = my_packets_read("recv.txt", packetsHeadRecv);
	sendNum = my_packets_read("send.txt", packetsHeadSend);

/*
	//�L�X���G
	int i;
	printf("recvNum = %d, sendNum = %d\n", recvNum, sendNum);
	getchar();
	printf("recv:\n");
	for(i=0; i<recvNum; i++)
	{
		printf("decode: %s, encode: %s\n", packetsHeadRecv[i].decode, packetsHeadRecv[i].encode);
	}
	getchar();
	printf("send:\n");
	for(i=0; i<sendNum; i++)
	{
		printf("decode: %s, encode: %s\n", packetsHeadSend[i].decode, packetsHeadSend[i].encode);
	}
	getchar();
*/

	//�ʥ]�ѱK, nrproto_decodeString
	my_mprotect(0x08158694);
	*(int*)0x08158694 = (int)my_nrproto_decodeString -4 -0x08158694;
	
	//�ʥ]�[�K, nrproto_encodeString
	my_mprotect(0x08158821);
	*(int*)0x08158821 = (int)my_nrproto_encodeString -4 -0x08158821;

	//makePetInfo, �ץ��Y��, �M�d, �a�d�ʥ]�榡
	my_mprotect(0x0806C033);
	*(int*)0x0806C033 = (int)"|0|0|%d%s";
	
	//BATTLE_MakeCharaString, �ץ��԰��ʥ]�榡
	my_mprotect(0x080B1E1F);
	*(int*)0x080B1E1F = (int)"%X|%s|%X|0|%X|%X|%X|%X|%X|%X|%X|%X|";

}
