#ifndef RTMPDEMO_H
#define RTMPDEMO_H
#include<stdio.h>
#include<stdlib.h>
void RtmpPublishStream(const char*filename,const char*url);
void RtmpPlayStream(const char*filename,const char*url,int bLive);
#endif