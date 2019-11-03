#include "STC12C5A60S2.H" 
#include "intrins.h"
#define NEXT_SONG 0
#define THE_SAME 1
#define CHANGE_NEXT 2
#define CHANGE_PRE 3
#define JUMP_BACK 4
#define JUMP_FORE 5
typedef unsigned char uint8;
typedef unsigned int uint16;

extern uint16 code reloadTHTL[3][7];
extern uint16 code freq[3][7];
extern uint8 musicBuff[192];
extern uint8 musicLength;
extern uint8 whichSong;
extern uint8 tot;
extern uint16 code dataStart[20];
extern float code clapDiv[7];
extern float oneClapTime;
extern float soundpercent;

extern float modBeat;
extern unsigned char beatLineIndex;
extern unsigned char nowLine;
extern unsigned char lineShowIndex[16];

extern void showName();
extern void showBasicPic();
extern void showSongNumber();
extern void showBeginPic();
extern void clearName();
extern void showContinue();
extern void showStop();
extern void showBeatLine();
extern void clearBeatLine();

extern void delay50ms(uint16 t);
extern void delay1ms(uint16 t);

extern bit eepromWriteByte(uint16 addr,uint8 dat);
extern uint8 eepromReadByte(uint16 addr);
extern bit eepromWritePage(uint16 addr,uint8 *dat,uint8 len);
extern bit eepromReadPage(uint16 addr,uint8 *dat,uint8 len);

extern void oledInit();
extern void oledClear();

sbit flag=P3^0;
sbit BUZZ=P1^5;
//switch song state
bit abortTrig;
bit jumpTrig;
uint8 trigMode;
uint8 musicMode;
//broadcast state
bit stopTrig;
bit isStopSignShow;
bit soundEnable;
uint16 cnt;
//set timer
uint8 T0RH=0xff;
uint8 T0RL=0x00;
//key in
sbit stop_KeyIn=P1^2;
sbit next_KeyIn=P1^3;
sbit prev_KeyIn=P1^1;
sbit back_KeyIn=P1^0;
sbit fore_KeyIn=P1^4;
sbit fast_KeyIn=P3^1;
sbit slow_KeyIn=P3^0;
//last key state
bit stop_10msAgo=1;
bit prev_10msAgo=1;
bit next_10msAgo=1;
bit back_10msAgo=1;
bit fore_10msAgo=1;
bit fast_10msAgo=1;
bit slow_10msAgo=1;

void beeInit();
void buttonInit();
void getMusicData();
void changeSong();
void readTotalSong();
void playMusic();

void main(){
	EA=1;
	TMOD=0x11;
	oledInit();
	beeInit();
	buttonInit();
	oledClear();
	readTotalSong();
	
	showBeginPic();
	delay50ms(500);
	whichSong=0;
	musicMode=THE_SAME;
	
	while(1){
		oledClear();
		showBasicPic();
		getMusicData();
		showSongNumber();
		showName();
		
		playMusic();
		
		changeSong();
		delay50ms(200);
	}
}
void playMusic(){
	uint8 t;
	float beatCnt=0,soundCnt=0;
	uint8 buffIndex=16;
	bit endTrig=0;
	
	uint8 note,beat;
	uint8 noteNum,noteLevel;
	uint8 beatNum,beatDot;
	
	isStopSignShow=1;
	soundEnable=0;
	stopTrig=0;
	cnt=0;
	clearBeatLine();

	modBeat=musicBuff[15]/32.0;
	for(t=0;t<16;t++) lineShowIndex[t]=modBeat*(float)(t+1)+0.5;
	nowLine=0;
	
	while(1){
		if(abortTrig==1) break;
		if(endTrig==1) break;
		if(stopTrig==1){
			if(isStopSignShow==1){
				isStopSignShow=0;
				showContinue();
			}
			continue;
		}
		else{
			if(isStopSignShow==0){
				isStopSignShow=1;
				showStop();
			}
		}
		if(jumpTrig==1){
			if(trigMode==JUMP_BACK){
				if(buffIndex<26) buffIndex=16;
				else buffIndex-=10;
			}
			if(trigMode==JUMP_FORE) buffIndex=buffIndex+10;
			jumpTrig=0;
			trigMode=0;
			
			cnt=0;
			soundEnable=0;
			beatCnt=0;
			soundCnt=0;
			continue;
		}
		if(soundEnable==1&&cnt>soundCnt) soundEnable=0;
		if(cnt>=beatCnt){
			//another note and beat,reset cnt
			cnt=0;
			//get note and beat
			note=musicBuff[buffIndex];
			beat=musicBuff[buffIndex+1];
			buffIndex+=2;
			//reach the end
			if(note==0x00&&beat==0x00){
				endTrig=1;
				T0RH=0Xff; T0RL=0X00;
				continue;
			}
			//translate note and beat
			noteNum=note%10-1; noteLevel=note/10-1;
			beatNum=beat%10;   beatDot=beat/100;
			//set the beatCnt and soundCnt
			if(beatDot==0) beatCnt=(oneClapTime*clapDiv[beat])*freq[noteLevel][noteNum];
					  else beatCnt=(oneClapTime*clapDiv[beatNum]*1.5)*freq[noteLevel][noteNum];
			soundCnt=beatCnt*soundpercent;
			//reload the timer
			T0RH=reloadTHTL[noteLevel][noteNum]>>8;
			T0RL=reloadTHTL[noteLevel][noteNum];
			soundEnable=1;
			
			if((buffIndex-16)/2==lineShowIndex[nowLine]){
				nowLine++;
				showBeatLine();
			}
		}
	}
	soundEnable=0;
	nowLine=0;
}
void beeTimer0()interrupt 1{
	TH0=T0RH; TL0=T0RL;
	if(stopTrig==1) return;
	if(jumpTrig==1) return;
	cnt++;
	if(soundEnable==1) BUZZ=~BUZZ;
	else BUZZ=1;
}
void buttonTimer1()interrupt 3{
	//10ms
	TH1=0x88;
	TL1=0x00;
	
	stop_KeyIn=1;
	next_KeyIn=1;
	prev_KeyIn=1;
	back_KeyIn=1;
	fore_KeyIn=1;
	fast_KeyIn=1;
	slow_KeyIn=1;
	
	if(stop_10msAgo==1&&stop_KeyIn==0){
		if(stopTrig==0){
			stopTrig=1;
			//showContinue();
		}
		else{
			stopTrig=0;
			//showStop();
		}
	}
	if(next_10msAgo==1&&next_KeyIn==0){
		abortTrig=1;
		trigMode=CHANGE_NEXT;
	}
	if(prev_10msAgo==1&&prev_KeyIn==0){
		abortTrig=1;
		trigMode=CHANGE_PRE;
	}
	if(back_10msAgo==1&&back_KeyIn==0){
		jumpTrig=1;
		trigMode=JUMP_BACK;
	}
	if(fore_10msAgo==1&&fore_KeyIn==0){
		jumpTrig=1;
		trigMode=JUMP_FORE;
	}
	if(fast_10msAgo==1&&fast_KeyIn==0){
		oneClapTime+=0.2;
	}
	if(slow_10msAgo==1&&slow_KeyIn==0){
		oneClapTime-=0.2;
	}
	stop_10msAgo=stop_KeyIn;
	prev_10msAgo=prev_KeyIn;
	next_10msAgo=next_KeyIn;
	back_10msAgo=back_KeyIn;
	fore_10msAgo=fore_KeyIn;
	fast_10msAgo=fore_KeyIn;
	slow_10msAgo=fore_KeyIn;
}

void musicInfoClear(){
	abortTrig=0;
	trigMode=0;
} 
void readTotalSong(){
	tot=0xee;
	while(tot==0xee)
	tot=eepromReadByte(0x1111);
}
void changeSong(){
	if(abortTrig==0){
		if(musicMode==NEXT_SONG) whichSong=(whichSong+1)%tot;
		if(musicMode==THE_SAME) whichSong=whichSong;
	}
	else{
		if(trigMode==CHANGE_NEXT) whichSong=(whichSong+1)%tot;
		if(trigMode==CHANGE_PRE) whichSong=(whichSong+tot-1)%tot;
	}
	abortTrig=0;
	trigMode=0;
}
void getMusicData(){
	uint8 i,tmp;
	uint16 addr;
	for(i=0;i<192;i++) musicBuff[i]=0;

	while(1){
		tmp=0xee;
		addr=dataStart[whichSong];
		while(tmp==0xee) tmp=eepromReadByte(addr+15);
		if(tmp==0x00) whichSong=(whichSong+1)%tot;
		else break; 
	}

	for(i=0;i<192;i++){
		tmp=0xee;
		while(tmp==0xee) tmp=eepromReadByte(addr);
		musicBuff[i]=tmp;
		addr++;
	}
	musicLength=musicBuff[15];
}
void beeInit(){
	TH0=0xff;
	TL0=0x00;
	ET0=1;
	TR0=1;
	return;
}
void buttonInit(){
	TH1=0xB8;
	TL1=0x00;
	ET1=1;
	TR1=1;
	return;
}