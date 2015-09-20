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
inline _Bool isfinal(void);
inline int evaluate(int d);
inline _Bool addStone(int pos,int p);
inline _Bool removeStone(int pos,int p);
inline int max(int a,int b);
inline int min(int a,int b);

int main(int argc,char **argv){
	char str[20],preload;
	int move,i,j;
	_Bool interactive=0,quiet=0;
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
		printf("Enter minimax depth (reasonable=10): "); fflush(stdout);
		scanf("%d",&mmdepth);
		fgetc(stdin);
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
inline _Bool isfinal(void){
	return isfinalme()||isfinalother();
}

inline int evaluate(int d){ //board's heuristic value for "me"
	int i,score;
	score=0;
	for(i=0;i<69;i++){
		score+=((masks[i]&bme)==masks[i])*5*d;
		score-=((masks[i]&bother)==masks[i])*5*d;
	}
	
	return score;
}

int hasthreat(int pos){
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
}

inline _Bool addStone(int pos,int p){
	if(height[pos]==6)return 0;
	if(p==me)bme|=(U64(1)<<(pos+height[pos]*7));
	else bother|=(U64(1)<<(pos+height[pos]*7));
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
