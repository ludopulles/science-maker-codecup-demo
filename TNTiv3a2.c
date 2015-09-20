#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

#define LARGE 1e8
#define HEIGHTS HEIGHT1(0) HEIGHT1(3) HEIGHT3
#define HEIGHT1(n) HEIGHT2(n) HEIGHT2(n+1) HEIGHT2(n+2)
#define HEIGHT2(n) height[n],
#define HEIGHT3 height[6]
#define U64(n) ((uint64_t)n)
#define not !
int me,height[7]={0},mmdepth=8;
uint64_t bme=0,bother=0; //Yeah, why the hell bother.
uint64_t masks[69]={
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

void printallmasks(void);
void printboard(void);
void getuserboard(void);
int choosemove(void);
int minimaxab(int depth,int alpha,int beta,int p);
inline _Bool isfinalme(void);
inline _Bool isfinalother(void);
inline _Bool isfinalbd(uint64_t bd);
inline _Bool isfinal(void);
int evaluate(int d);
inline _Bool hasthreat(int pos,uint64_t bd);
inline _Bool addStone(int pos,int p);
inline _Bool removeStone(int pos,int p);
inline int max(int a,int b);
inline int min(int a,int b);

int main(int argc,char **argv){
	char str[20],preload;
	int move,i,j;
	_Bool interactive=0,quiet=0,mmdepthset=0;
	_Bool skipparam=0;
	for(i=1;i<argc;i++){
		if(skipparam){
			skipparam=0;
			continue;
		}
		if(argv[i][0]!='-'){
			fprintf(stderr,"Unrecognised argument '%s'\n",argv[i]);
			return 1;
		}
		for(j=1;argv[i][j];j++){
			switch(argv[i][j]){
				case 'i':interactive=1;break;
				case 'd':
					if(i==argc-1){
						fprintf(stderr,"-d at end of parameter list!\n");
						return 1;
					}
					mmdepth=strtol(argv[i+1],NULL,10);
					mmdepthset=1;
					skipparam=1;
					break;
				case 'q':
					quiet=1;
					break;
				default:
					fprintf(stderr,"Unrecognised flag '-%c'\n",argv[i][j]);
					return 1;
			}
		}
	}
	if(quiet)freopen("/dev/null","w",stderr);
	fprintf(stderr,"S TomSmeding\n");
	if(interactive){
		if(!mmdepthset){
			printf("Enter minimax depth (reasonable=10): "); fflush(stdout);
			scanf("%d",&mmdepth);
			fgetc(stdin);
		}
		printf("Pre-load board (Y/N): "); fflush(stdout);
		scanf("%c",&preload);
		if(preload=='y'||preload=='Y'){
			printf("Enter board, X'es for MY stones, O's for YOUR stones:\n");
			getuserboard();
			printf("Got board:\n");
			printboard();
			for(i=0;i<7;i++)putchar(height[i]+'0');
			putchar('\n');putchar('\n');
		}
		printf("Enter first move. (preload=%c)\n",preload);
	}
	fscanf(stdin,"%s",str);
	if(str[0]=='s'||str[0]=='S'){
		me=0;
		if(bme==U64(0)&&bother==U64(0))move=3;
		else move=choosemove();
		addStone(move,me);
		printf("%d\n",move+1);
		fflush(stdout);
		if(interactive)printboard();
		fscanf(stdin,"%s",str);
	} else {
		me=1;
		addStone(str[0]-'1',not me);
		if(interactive){
			printf("You did move %d.\n",str[0]-'0');
			printboard();
		}
		if(bme==U64(0)&&bother==U64(0))move=3;
		else move=choosemove();
		addStone(move,me);
		printf("%d\n",move+1);
		fflush(stdout);
		if(interactive)printboard();
		fscanf(stdin,"%s",str);
	}
	while(str[0]!='q'&&str[0]!='Q'&&!feof(stdin)){
		addStone(str[0]-'1',not me);
		if(interactive){
			printf("You did move %d.\n",str[0]-'0');
			printboard();
			if(isfinalme()){
				printf("I WON!\n");
				break;
			}
			if(isfinalother()){
				printf("YOU WON!\n");
				break;
			}
		}
		move=choosemove();
		addStone(move,me);
		printf("%d\n",move+1);
		fflush(stdout);
		if(interactive){
			printf("I did move %d.\n",move+1);
			printboard();
			if(isfinalme()){
				printf("I WON!\n");
				break;
			}
			if(isfinalother()){
				printf("YOU WON!\n");
				break;
			}
		}
		fscanf(stdin,"%s",str);
	}
	//fprintf(stderr,"KABOOM TNT C4 EXPLOSION  done.\n");
	return 0;
}

void printallmasks(void){
	int i,c;
	char read;
	_Bool skipchar;
	skipchar=0;
	c=1;
	for(i=0;i<(int)(sizeof(masks)/sizeof(masks[0]));i++){
		if(skipchar){skipchar=0;i--;c=1;getchar();continue;}
		bme=masks[i];
		fprintf(stderr,"masks[%d]= (%d)\n",i,c);
		printboard();
		read=getchar();
		c++;
		if(read=='r')skipchar=1;
		system("clear");
	}
	return;
}

void printboard(void){
	int i,j;
	uint64_t m;
	for(i=0,m=U64(1)<<35;i<6;i++,m>>=14){
		for(j=0;j<7;j++,m<<=1){
			fputc((bme&m)!=0?'X':(bother&m)?'O':'.',stderr);
		}
		fputc('\n',stderr);
	}
	return;
}

void getuserboard(void){
	int i,j;
	uint64_t m;
	char instr[20];
	bme^=bme; bother^=bother;
	for(i=0;i<6;i++){
		m=U64(1)<<(35-7*i);
		scanf("%s",instr);
		for(j=0;j<7&&j<(int)strlen(instr);j++,m<<=1){
			if(instr[j]=='X'){if(me==0)bme|=m; else bother|=m; height[j]++;}
			if(instr[j]=='O'){if(me==0)bother|=m; else bme|=m; height[j]++;}
		}
	}
}

int choosemove(void){
	int i,move,highest,score,sameval;
	uint64_t tempbme;
	highest=-LARGE;
	fprintf(stderr,"[");
	sameval=-LARGE;
	move=0;
	for(i=0;i<7;i++){
		tempbme=bme;
		if(!addStone(i,me))continue;
		score=minimaxab(mmdepth,-LARGE,LARGE,not me);
		fprintf(stderr,"%d%s",score,(i!=6?",":""));
		if(score>=highest){highest=score;move=i;}
		if(sameval==-LARGE)sameval=score;
		else if(sameval!=score)sameval=-LARGE+1;
		bme=tempbme;height[i]--;
	}
	fprintf(stderr,"]\n");
	if(sameval!=-LARGE+1){
		if(height[3]<6)move=3;
		else if(height[4]<6)move=4;
		else if(height[2]<6)move=2;
		else if(height[5]<6)move=5;
		else if(height[1]<6)move=1;
		else if(height[6]<6)move=6;
		else move=0;
	}
	return move;
}

int minimaxab(int depth,int alpha,int beta,int p){
	int i;
	uint64_t tempbme,tempbother;
	if(depth==0||isfinal())return evaluate(depth);
	if(p==me){
		for(i=0;i<7;i++){
			tempbme=bme;tempbother=bother;
			if(!addStone(i,p))continue;
			alpha=max(alpha,minimaxab(depth-1,alpha,beta,not p));
			bme=tempbme;bother=tempbother;height[i]--;
			if(beta<=alpha)break;
		}
		return alpha;
	}else{
		for(i=0;i<7;i++){
			tempbme=bme;tempbother=bother;
			if(!addStone(i,p))continue;
			beta=min(beta,minimaxab(depth-1,alpha,beta,not p));
			bme=tempbme;bother=tempbother;height[i]--;
			if(beta<=alpha)break;
		}
		return beta;
	}
}

inline _Bool isfinalme(void){
	int i;
	if(bme==0x1ffffffffff)return 1; //checks full board
	for(i=0;i<69;i++)
		if((masks[i]&bme)==masks[i])
			return 1;
	return 0;
}
inline _Bool isfinalother(void){
	int i;
	if(bother==0x1ffffffffff)return 1; //checks full board
	for(i=0;i<69;i++)
		if((masks[i]&bother)==masks[i])
			return 1;
	return 0;
}
inline _Bool isfinalbd(uint64_t bd){
	int i;
	if(bd==0x1ffffffffff)return 1; //checks full board
	for(i=0;i<69;i++)
		if((masks[i]&bd)==masks[i])
			return 1;
	return 0;
}
inline _Bool isfinal(void){
	return isfinalme()||isfinalother();
}

int evaluate(int d){ //board's heuristic value for "me"
	int score4,scoreT; //T=Threat
	score4=((masks[ 0]&bme)==masks[ 0])-((masks[ 0]&bother)==masks[ 0])
	      +((masks[ 1]&bme)==masks[ 1])-((masks[ 1]&bother)==masks[ 1])
	      +((masks[ 2]&bme)==masks[ 2])-((masks[ 2]&bother)==masks[ 2])
	      +((masks[ 3]&bme)==masks[ 3])-((masks[ 3]&bother)==masks[ 3])
	      +((masks[ 4]&bme)==masks[ 4])-((masks[ 4]&bother)==masks[ 4])
	      +((masks[ 5]&bme)==masks[ 5])-((masks[ 5]&bother)==masks[ 5])
	      +((masks[ 6]&bme)==masks[ 6])-((masks[ 6]&bother)==masks[ 6])
	      +((masks[ 7]&bme)==masks[ 7])-((masks[ 7]&bother)==masks[ 7])
	      +((masks[ 8]&bme)==masks[ 8])-((masks[ 8]&bother)==masks[ 8])
	      +((masks[ 9]&bme)==masks[ 9])-((masks[ 9]&bother)==masks[ 9])
	      +((masks[10]&bme)==masks[10])-((masks[10]&bother)==masks[10])
	      +((masks[11]&bme)==masks[11])-((masks[11]&bother)==masks[11])
	      +((masks[12]&bme)==masks[12])-((masks[12]&bother)==masks[12])
	      +((masks[13]&bme)==masks[13])-((masks[13]&bother)==masks[13])
	      +((masks[14]&bme)==masks[14])-((masks[14]&bother)==masks[14])
	      +((masks[15]&bme)==masks[15])-((masks[15]&bother)==masks[15])
	      +((masks[16]&bme)==masks[16])-((masks[16]&bother)==masks[16])
	      +((masks[17]&bme)==masks[17])-((masks[17]&bother)==masks[17])
	      +((masks[18]&bme)==masks[18])-((masks[18]&bother)==masks[18])
	      +((masks[19]&bme)==masks[19])-((masks[19]&bother)==masks[19])
	      +((masks[20]&bme)==masks[20])-((masks[20]&bother)==masks[20])
	      +((masks[21]&bme)==masks[21])-((masks[21]&bother)==masks[21])
	      +((masks[22]&bme)==masks[22])-((masks[22]&bother)==masks[22])
	      +((masks[23]&bme)==masks[23])-((masks[23]&bother)==masks[23])
	      +((masks[24]&bme)==masks[24])-((masks[24]&bother)==masks[24])
	      +((masks[25]&bme)==masks[25])-((masks[25]&bother)==masks[25])
	      +((masks[26]&bme)==masks[26])-((masks[26]&bother)==masks[26])
	      +((masks[27]&bme)==masks[27])-((masks[27]&bother)==masks[27])
	      +((masks[28]&bme)==masks[28])-((masks[28]&bother)==masks[28])
	      +((masks[29]&bme)==masks[29])-((masks[29]&bother)==masks[29])
	      +((masks[30]&bme)==masks[30])-((masks[30]&bother)==masks[30])
	      +((masks[31]&bme)==masks[31])-((masks[31]&bother)==masks[31])
	      +((masks[32]&bme)==masks[32])-((masks[32]&bother)==masks[32])
	      +((masks[33]&bme)==masks[33])-((masks[33]&bother)==masks[33])
	      +((masks[34]&bme)==masks[34])-((masks[34]&bother)==masks[34])
	      +((masks[35]&bme)==masks[35])-((masks[35]&bother)==masks[35])
	      +((masks[36]&bme)==masks[36])-((masks[36]&bother)==masks[36])
	      +((masks[37]&bme)==masks[37])-((masks[37]&bother)==masks[37])
	      +((masks[38]&bme)==masks[38])-((masks[38]&bother)==masks[38])
	      +((masks[39]&bme)==masks[39])-((masks[39]&bother)==masks[39])
	      +((masks[40]&bme)==masks[40])-((masks[40]&bother)==masks[40])
	      +((masks[41]&bme)==masks[41])-((masks[41]&bother)==masks[41])
	      +((masks[42]&bme)==masks[42])-((masks[42]&bother)==masks[42])
	      +((masks[43]&bme)==masks[43])-((masks[43]&bother)==masks[43])
	      +((masks[44]&bme)==masks[44])-((masks[44]&bother)==masks[44])
	      +((masks[45]&bme)==masks[45])-((masks[45]&bother)==masks[45])
	      +((masks[46]&bme)==masks[46])-((masks[46]&bother)==masks[46])
	      +((masks[47]&bme)==masks[47])-((masks[47]&bother)==masks[47])
	      +((masks[48]&bme)==masks[48])-((masks[48]&bother)==masks[48])
	      +((masks[49]&bme)==masks[49])-((masks[49]&bother)==masks[49])
	      +((masks[50]&bme)==masks[50])-((masks[50]&bother)==masks[50])
	      +((masks[51]&bme)==masks[51])-((masks[51]&bother)==masks[51])
	      +((masks[52]&bme)==masks[52])-((masks[52]&bother)==masks[52])
	      +((masks[53]&bme)==masks[53])-((masks[53]&bother)==masks[53])
	      +((masks[54]&bme)==masks[54])-((masks[54]&bother)==masks[54])
	      +((masks[55]&bme)==masks[55])-((masks[55]&bother)==masks[55])
	      +((masks[56]&bme)==masks[56])-((masks[56]&bother)==masks[56])
	      +((masks[57]&bme)==masks[57])-((masks[57]&bother)==masks[57])
	      +((masks[58]&bme)==masks[58])-((masks[58]&bother)==masks[58])
	      +((masks[59]&bme)==masks[59])-((masks[59]&bother)==masks[59])
	      +((masks[60]&bme)==masks[60])-((masks[60]&bother)==masks[60])
	      +((masks[61]&bme)==masks[61])-((masks[61]&bother)==masks[61])
	      +((masks[62]&bme)==masks[62])-((masks[62]&bother)==masks[62])
	      +((masks[63]&bme)==masks[63])-((masks[63]&bother)==masks[63])
	      +((masks[64]&bme)==masks[64])-((masks[64]&bother)==masks[64])
	      +((masks[65]&bme)==masks[65])-((masks[65]&bother)==masks[65])
	      +((masks[66]&bme)==masks[66])-((masks[66]&bother)==masks[66])
	      +((masks[67]&bme)==masks[67])-((masks[67]&bother)==masks[67])
	      +((masks[68]&bme)==masks[68])-((masks[68]&bother)==masks[68]);

	if(me==0){
		scoreT=hasthreat( 0,bme) +hasthreat(14,bme) +hasthreat(28,bme)
		      +hasthreat( 1,bme) +hasthreat(15,bme) +hasthreat(29,bme)
		      +hasthreat( 2,bme) +hasthreat(16,bme) +hasthreat(30,bme)
		      +hasthreat( 3,bme) +hasthreat(17,bme) +hasthreat(31,bme)
		      +hasthreat( 4,bme) +hasthreat(18,bme) +hasthreat(32,bme)
		      +hasthreat( 5,bme) +hasthreat(19,bme) +hasthreat(33,bme)
		      +hasthreat( 6,bme) +hasthreat(20,bme) +hasthreat(34,bme)

		      -hasthreat( 7,bother) -hasthreat(21,bother) -hasthreat(35,bother)
		      -hasthreat( 8,bother) -hasthreat(22,bother) -hasthreat(36,bother)
		      -hasthreat( 9,bother) -hasthreat(23,bother) -hasthreat(37,bother)
		      -hasthreat(10,bother) -hasthreat(24,bother) -hasthreat(38,bother)
		      -hasthreat(11,bother) -hasthreat(25,bother) -hasthreat(39,bother)
		      -hasthreat(12,bother) -hasthreat(26,bother) -hasthreat(40,bother)
		      -hasthreat(13,bother) -hasthreat(27,bother) -hasthreat(41,bother);
	} else {
		scoreT=hasthreat( 7,bme) +hasthreat(21,bme) +hasthreat(35,bme)
		      +hasthreat( 8,bme) +hasthreat(22,bme) +hasthreat(36,bme)
		      +hasthreat( 9,bme) +hasthreat(23,bme) +hasthreat(37,bme)
		      +hasthreat(10,bme) +hasthreat(24,bme) +hasthreat(38,bme)
		      +hasthreat(11,bme) +hasthreat(25,bme) +hasthreat(39,bme)
		      +hasthreat(12,bme) +hasthreat(26,bme) +hasthreat(40,bme)
		      +hasthreat(13,bme) +hasthreat(27,bme) +hasthreat(41,bme)

		      -hasthreat( 0,bother) -hasthreat(14,bother) -hasthreat(28,bother)
		      -hasthreat( 1,bother) -hasthreat(15,bother) -hasthreat(29,bother)
		      -hasthreat( 2,bother) -hasthreat(16,bother) -hasthreat(30,bother)
		      -hasthreat( 3,bother) -hasthreat(17,bother) -hasthreat(31,bother)
		      -hasthreat( 4,bother) -hasthreat(18,bother) -hasthreat(32,bother)
		      -hasthreat( 5,bother) -hasthreat(19,bother) -hasthreat(33,bother)
		      -hasthreat( 6,bother) -hasthreat(20,bother) -hasthreat(34,bother);
	}

	return score4*5*d+scoreT*2*d;
}

/*int hasthreat(int pos){
	int i,j,numstonesme,numstonesother,mode,x,y;
	x=pos%7; y=pos/7;
	mode=0;
#define innerloopx {if(bme&(U64(1)<<(y*7+j))){if(mode==-1)break;numstonesme++;mode=1;} \
                   else if(bother&(U64(1)<<(y*7+j))){if(mode==1)break;numstonesother++;mode=-1;} \
                   else break;}
	numstonesme=numstonesother=0;
	for(j=x;j>=max(x-3,0);j--)innerloopx
	for(j=x;j<=min(x+3,6);j++)innerloopx
	if(numstonesme>=3)return 1;
	if(numstonesother>=3)return -1;

#define innerloopd {if(bme&(U64(1)<<(i*7+j))){if(mode==-1)break;numstonesme++;mode=1;} \
                   else if(bother&(U64(1)<<(i*7+j))){if(mode==1)break;numstonesother++;mode=-1;} \
                   else break;}
	numstonesme=numstonesother=0;
	for(j=x,i=y;j>=(x-3<0?0:x-3)&&i>=(y-3<0?0:y-3);j--,i--)innerloopd
	for(j=x,i=y;j<=(x+3>6?6:x+3)&&i<=(y+3>5?5:y+3);j++,i++)innerloopd
	if(numstonesme>=3)return 1;
	if(numstonesother>=3)return -1;

	numstonesme=numstonesother=0;
	for(j=x,i=y;j>=(x-3<0?0:x-3)&&i<=(y+3>5?5:y+3);j--,i++)innerloopd
	for(j=x,i=y;j<=(x+3>6?6:x+3)&&i>=(y-3<0?0:y-3);j++,i--)innerloopd
	if(numstonesme>=3)return 1;
	if(numstonesother>=3)return -1;

	return 0;
}*/

inline _Bool hasthreat(int pos,uint64_t bd){
	const uint64_t m=U64(1)<<pos;
	if((bme|bother)&m)return 0;
	return isfinalbd(bd|m);
}

inline _Bool addStone(int pos,int p){
	if(height[pos]==6)return 0;
	if(p==me)bme|=U64(1)<<(pos+height[pos]*7);
	else bother|=U64(1)<<(pos+height[pos]*7);
	height[pos]++;
	return 1;
}

inline _Bool removeStone(int pos,int p){
	if(height[pos]==0)return 0;
	if(p==me)bme&=~(U64(1)<<(pos+7*height[pos]));
	else bother&=~(U64(1)<<(pos+7*height[pos]));
	height[pos]--;
	return 1;
}

inline int max(int a,int b){return b>a?b:a;}

inline int min(int a,int b){return b<a?b:a;}
