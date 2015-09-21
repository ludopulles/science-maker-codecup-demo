#include <iostream>
#include <cstdint>
#include <sys/time.h>

#define U64(x) ((uint64_t)(x))

#define NSIMULATIONS (1000)

using namespace std;

uint64_t masks[69]={ //winmasks
	0x7800000000,0xf000000000,0x1e000000000,0x3c000000000,0xf0000000,0x1e0000000,
	0x3c0000000,0x780000000,0x1e00000,0x3c00000,0x7800000,0xf000000,
	0x3c000,0x78000,0xf0000,0x1e0000,0x780,0xf00,
	0x1e00,0x3c00,0xf,0x1e,0x3c,0x78,
	0x810204000,0x1020408000,0x2040810000,0x4081020000,0x8102040000,0x10204080000,
	0x20408100000,0x10204080,0x20408100,0x40810200,0x81020400,0x102040800,
	0x204081000,0x408102000,0x204081,0x408102,0x810204,0x1020408,
	0x2040810,0x4081020,0x8102040,0x4040404000,0x8080808000,0x10101010000,
	0x20202020000,0x80808080,0x101010100,0x202020200,0x404040400,0x1010101,
	0x2020202,0x4040404,0x8080808,0x820820000,0x1041040000,0x2082080000,
	0x4104100000,0x10410400,0x20820800,0x41041000,0x82082000,0x208208,
	0x410410,0x820820,0x1041040
};

uint64_t bme,bother;
int colheight[7];

//0: nothing, -1: tie, 1: I win, 2: opponent wins
int checkwin(void){
	if((bme|bother)==0x1ffffffffff)return -1; //full board
	if(((masks[0]&bme)==masks[0])||((masks[1]&bme)==masks[1])||((masks[2]&bme)==masks[2])||((masks[3]&bme)==masks[3])||((masks[4]&bme)==masks[4])||((masks[5]&bme)==masks[5])||((masks[6]&bme)==masks[6])||((masks[7]&bme)==masks[7])||((masks[8]&bme)==masks[8])||((masks[9]&bme)==masks[9])||((masks[10]&bme)==masks[10])||((masks[11]&bme)==masks[11])||((masks[12]&bme)==masks[12])||((masks[13]&bme)==masks[13])||((masks[14]&bme)==masks[14])||((masks[15]&bme)==masks[15])||((masks[16]&bme)==masks[16])||((masks[17]&bme)==masks[17])||((masks[18]&bme)==masks[18])||((masks[19]&bme)==masks[19])||((masks[20]&bme)==masks[20])||((masks[21]&bme)==masks[21])||((masks[22]&bme)==masks[22])||((masks[23]&bme)==masks[23])||((masks[24]&bme)==masks[24])||((masks[25]&bme)==masks[25])||((masks[26]&bme)==masks[26])||((masks[27]&bme)==masks[27])||((masks[28]&bme)==masks[28])||((masks[29]&bme)==masks[29])||((masks[30]&bme)==masks[30])||((masks[31]&bme)==masks[31])||((masks[32]&bme)==masks[32])||((masks[33]&bme)==masks[33])||((masks[34]&bme)==masks[34])||((masks[35]&bme)==masks[35])||((masks[36]&bme)==masks[36])||((masks[37]&bme)==masks[37])||((masks[38]&bme)==masks[38])||((masks[39]&bme)==masks[39])||((masks[40]&bme)==masks[40])||((masks[41]&bme)==masks[41])||((masks[42]&bme)==masks[42])||((masks[43]&bme)==masks[43])||((masks[44]&bme)==masks[44])||((masks[45]&bme)==masks[45])||((masks[46]&bme)==masks[46])||((masks[47]&bme)==masks[47])||((masks[48]&bme)==masks[48])||((masks[49]&bme)==masks[49])||((masks[50]&bme)==masks[50])||((masks[51]&bme)==masks[51])||((masks[52]&bme)==masks[52])||((masks[53]&bme)==masks[53])||((masks[54]&bme)==masks[54])||((masks[55]&bme)==masks[55])||((masks[56]&bme)==masks[56])||((masks[57]&bme)==masks[57])||((masks[58]&bme)==masks[58])||((masks[59]&bme)==masks[59])||((masks[60]&bme)==masks[60])||((masks[61]&bme)==masks[61])||((masks[62]&bme)==masks[62])||((masks[63]&bme)==masks[63])||((masks[64]&bme)==masks[64])||((masks[65]&bme)==masks[65])||((masks[66]&bme)==masks[66])||((masks[67]&bme)==masks[67])||((masks[68]&bme)==masks[68]))return 1;
	if(((masks[0]&bother)==masks[0])||((masks[1]&bother)==masks[1])||((masks[2]&bother)==masks[2])||((masks[3]&bother)==masks[3])||((masks[4]&bother)==masks[4])||((masks[5]&bother)==masks[5])||((masks[6]&bother)==masks[6])||((masks[7]&bother)==masks[7])||((masks[8]&bother)==masks[8])||((masks[9]&bother)==masks[9])||((masks[10]&bother)==masks[10])||((masks[11]&bother)==masks[11])||((masks[12]&bother)==masks[12])||((masks[13]&bother)==masks[13])||((masks[14]&bother)==masks[14])||((masks[15]&bother)==masks[15])||((masks[16]&bother)==masks[16])||((masks[17]&bother)==masks[17])||((masks[18]&bother)==masks[18])||((masks[19]&bother)==masks[19])||((masks[20]&bother)==masks[20])||((masks[21]&bother)==masks[21])||((masks[22]&bother)==masks[22])||((masks[23]&bother)==masks[23])||((masks[24]&bother)==masks[24])||((masks[25]&bother)==masks[25])||((masks[26]&bother)==masks[26])||((masks[27]&bother)==masks[27])||((masks[28]&bother)==masks[28])||((masks[29]&bother)==masks[29])||((masks[30]&bother)==masks[30])||((masks[31]&bother)==masks[31])||((masks[32]&bother)==masks[32])||((masks[33]&bother)==masks[33])||((masks[34]&bother)==masks[34])||((masks[35]&bother)==masks[35])||((masks[36]&bother)==masks[36])||((masks[37]&bother)==masks[37])||((masks[38]&bother)==masks[38])||((masks[39]&bother)==masks[39])||((masks[40]&bother)==masks[40])||((masks[41]&bother)==masks[41])||((masks[42]&bother)==masks[42])||((masks[43]&bother)==masks[43])||((masks[44]&bother)==masks[44])||((masks[45]&bother)==masks[45])||((masks[46]&bother)==masks[46])||((masks[47]&bother)==masks[47])||((masks[48]&bother)==masks[48])||((masks[49]&bother)==masks[49])||((masks[50]&bother)==masks[50])||((masks[51]&bother)==masks[51])||((masks[52]&bother)==masks[52])||((masks[53]&bother)==masks[53])||((masks[54]&bother)==masks[54])||((masks[55]&bother)==masks[55])||((masks[56]&bother)==masks[56])||((masks[57]&bother)==masks[57])||((masks[58]&bother)==masks[58])||((masks[59]&bother)==masks[59])||((masks[60]&bother)==masks[60])||((masks[61]&bother)==masks[61])||((masks[62]&bother)==masks[62])||((masks[63]&bother)==masks[63])||((masks[64]&bother)==masks[64])||((masks[65]&bother)==masks[65])||((masks[66]&bother)==masks[66])||((masks[67]&bother)==masks[67])||((masks[68]&bother)==masks[68]))return 2;
	return 0;
}

inline void addstoneme(int col){
	bme|=U64(1)<<(col+7*colheight[col]);
	colheight[col]++;
}
inline void addstoneother(int col){
	bother|=U64(1)<<(col+7*colheight[col]);
	colheight[col]++;
}
inline void removestoneme(int col){
	colheight[col]--;
	bme&=~(U64(1)<<(col+7*colheight[col]));
}
inline void removestoneother(int col){
	colheight[col]--;
	bother&=~(U64(1)<<(col+7*colheight[col]));
}

inline bool validate(int col){
	return colheight[col]<6;
}

void printboard(void){
	int i,j;
	uint64_t m;
	for(i=0,m=U64(1)<<35;i<6;i++,m>>=14){
		for(j=0;j<7;j++,m<<=1){
			cerr<<((bme&m)!=0?'X':(bother&m)?'O':'.');
		}
		cerr<<endl;
	}
}

int calcmove(void){
	int col;
	uint64_t bmebak,botherbak;
	int colheightbak[7];
	int score,maxscore=INT_MIN,maxscoreat=0;
	int win;
	int i,j;
	int poss[7],nposs;
	cerr<<'[';
	for(col=0;col<7;col++){
		if(!validate(col)){
			cerr<<(col==0?"*":",*");
			continue;
		}
		score=0;
		addstoneme(col);
		if((win=checkwin())){
			removestoneme(col);
			switch(win){
				case 1:score=NSIMULATIONS;break;
				case 2:score=-NSIMULATIONS;break;
				default:break;
			}
			cerr<<(col==0?"[":",[")<<score<<']';
			if(score>maxscore){
				maxscore=score;
				maxscoreat=col;
			}
			continue;
		}
		bmebak=bme;
		botherbak=bother;
		memcpy(colheightbak,colheight,7*sizeof(int));
		for(i=NSIMULATIONS;i!=0;i--){
			while(true){
				nposs=0;
				for(j=0;j<7;j++){
					if(!validate(j))continue;
					addstoneother(j);
					win=checkwin();
					removestoneother(j);
					if(win==2)break;
					if(win==1||win==0)poss[nposs++]=j;
				}
				if(win==2)break; //this person's won
				else if(nposs)addstoneother(poss[rand()%nposs]);
				else break; //no more reasonable moves

				nposs=0;
				for(j=0;j<7;j++){
					if(!validate(j))continue;
					addstoneme(j);
					win=checkwin();
					removestoneme(j);
					if(win==1)break;
					if(win==2||win==0)poss[nposs++]=j;
				}
				if(win==1)break; //this person's won
				else if(nposs)addstoneme(poss[rand()%nposs]);
				else break; //no more reasonable moves
			}
			switch(win){
				case 1:score++;break;
				case 2:score--;break;
				default:break;
			}
			bme=bmebak;
			bother=botherbak;
			memcpy(colheight,colheightbak,7*sizeof(int));
		}
		removestoneme(col);
		cerr<<(col==0?"":",")<<score;
		if(score>maxscore){
			maxscore=score;
			maxscoreat=col;
		}
	}
	cerr<<']'<<endl;
	return maxscoreat;
}

int main(void){
	cerr<<"R caaaaaaaaaaarlo"<<endl;

	struct timeval tv;
	gettimeofday(&tv,NULL);
	srand(tv.tv_sec*1000000+tv.tv_usec);

	char c=cin.peek();
	if(c=='s'||c=='S'){
		cin.ignore(1024,'\n');
		addstoneme(3);
		cout<<'4'<<endl;
	}
	int col;
	while(true){
		printboard();
		c=cin.peek();
		if(c=='q'||c=='Q')break;
		cin>>col; cin.ignore(1024,'\n');
		col--;
		addstoneother(col);
		col=calcmove();
		if(!validate(col)){
			int i;
			for(i=0;i<7;i++)if(validate(col))break;
			if(i==7)col=3; //bla
		}
		addstoneme(col);
		cout<<col+1<<endl;
	}
}
