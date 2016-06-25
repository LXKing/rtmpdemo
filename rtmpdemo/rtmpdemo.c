#include "rtmpdemo.h"
#include "librtmp/rtmp.h"

#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#endif

#define TYPE_NONE		0
#define TYPE_PUBLISH	1
#define TYPE_PLAY		2
void Help(){
	printf("./app -file:filename -url:url -publish\n");
	printf("publish a stream from file\n");
	printf("./app -file:filename -url:url -play\n");
	printf("save a stream from url\n");
	exit(0);
}
int InitSockets(){
#ifdef WIN32
  WORD version;
  WSADATA wsaData;
  version = MAKEWORD(1, 1);
  return (WSAStartup(version, &wsaData) == 0);
#else
  return TRUE;
#endif
}

void CleanupSockets(){
#ifdef WIN32
  WSACleanup();
#endif
}
int main(int argc,char**argv){
	int  nType=TYPE_NONE;
	int  i=0;
	char filename[256]={0};
	char url[256]={0};
	for(i=1;i<argc;i++){
		if(strcmp(argv[i],"-publish")==0){
		   nType=TYPE_PUBLISH;
		}else
		if(strcmp(argv[i],"-play")==0){
		   nType=TYPE_PLAY;
		}else
		if(strncmp(argv[i],"-file:",6)==0){
		   strcpy(filename,argv[i]+6);
		}else
		if(strncmp(argv[i],"-url:",5)==0){
		   strcpy(url,argv[i]+5);
		}else{
		   Help();
		}
	}
	if(nType==TYPE_NONE||filename[0]=='\0'||url[0]=='\0'){
	   Help();
	}
	InitSockets();
	printf("file:%s url:%s type:%s\n",filename,url,nType==TYPE_PUBLISH?"publish":"play");
	if(nType==TYPE_PUBLISH){
	   RtmpPublishStream(filename,url);
	}else{
	   RtmpPlayStream(filename,url,0);
	}
	CleanupSockets();
	return 0;
}