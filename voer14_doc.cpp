//
// voer14.cpp
//
// Gemaakt door Jens Heuseveldt
// voor de NIO3 codecup 2013
//
#include <iostream>
#include <string>
using namespace std;
int antwoord, tot1, tot2, tot3, tot4, tot5, tot6, tot7, field[7][6];
//
// Mijn programma gebruikt een 2-dimensionale array (field[][]) om op te slaan waar de stenen staan
// 0 betekent dat het vakje nog vrij is
// 1 betekent dat mijn steen er staat
// 2 betekent dat het vakje door de tegenstander bezet is
//
int checkwin(int player)
{
	//controleer of er een speler heeft gewonnen met de huidige situatie
	//controleer horizontaal
	if(field[0][0]==player&&field[1][0]==player&&field[2][0]==player&&field[3][0]==player){return true;}
	if(field[1][0]==player&&field[2][0]==player&&field[3][0]==player&&field[4][0]==player){return true;}
	if(field[2][0]==player&&field[3][0]==player&&field[4][0]==player&&field[5][0]==player){return true;}
	if(field[3][0]==player&&field[4][0]==player&&field[5][0]==player&&field[6][0]==player){return true;}
	if(field[0][1]==player&&field[1][1]==player&&field[2][1]==player&&field[3][1]==player){return true;}
	if(field[1][1]==player&&field[2][1]==player&&field[3][1]==player&&field[4][1]==player){return true;}
	if(field[2][1]==player&&field[3][1]==player&&field[4][1]==player&&field[5][1]==player){return true;}
	if(field[3][1]==player&&field[4][1]==player&&field[5][1]==player&&field[6][1]==player){return true;}
	if(field[0][2]==player&&field[1][2]==player&&field[2][2]==player&&field[3][2]==player){return true;}
	if(field[1][2]==player&&field[2][2]==player&&field[3][2]==player&&field[4][2]==player){return true;}
	if(field[2][2]==player&&field[3][2]==player&&field[4][2]==player&&field[5][2]==player){return true;}
	if(field[3][2]==player&&field[4][2]==player&&field[5][2]==player&&field[6][2]==player){return true;}
	if(field[0][3]==player&&field[1][3]==player&&field[2][3]==player&&field[3][3]==player){return true;}
	if(field[1][3]==player&&field[2][3]==player&&field[3][3]==player&&field[4][3]==player){return true;}
	if(field[2][3]==player&&field[3][3]==player&&field[4][3]==player&&field[5][3]==player){return true;}
	if(field[3][3]==player&&field[4][3]==player&&field[5][3]==player&&field[6][3]==player){return true;}
	if(field[0][4]==player&&field[1][4]==player&&field[2][4]==player&&field[3][4]==player){return true;}
	if(field[1][4]==player&&field[2][4]==player&&field[3][4]==player&&field[4][4]==player){return true;}
	if(field[2][4]==player&&field[3][4]==player&&field[4][4]==player&&field[5][4]==player){return true;}
	if(field[3][4]==player&&field[4][4]==player&&field[5][4]==player&&field[6][4]==player){return true;}
	if(field[0][5]==player&&field[1][5]==player&&field[2][5]==player&&field[3][5]==player){return true;}
	if(field[1][5]==player&&field[2][5]==player&&field[3][5]==player&&field[4][5]==player){return true;}
	if(field[2][5]==player&&field[3][5]==player&&field[4][5]==player&&field[5][5]==player){return true;}
	if(field[3][5]==player&&field[4][5]==player&&field[5][5]==player&&field[6][5]==player){return true;}
	//controleer verticaal
	if(field[0][0]==player&&field[0][1]==player&&field[0][2]==player&&field[0][3]==player){return true;}
	if(field[0][1]==player&&field[0][2]==player&&field[0][3]==player&&field[0][4]==player){return true;}
	if(field[0][2]==player&&field[0][3]==player&&field[0][4]==player&&field[0][5]==player){return true;}
	if(field[1][0]==player&&field[1][1]==player&&field[1][2]==player&&field[1][3]==player){return true;}
	if(field[1][1]==player&&field[1][2]==player&&field[1][3]==player&&field[1][4]==player){return true;}
	if(field[1][2]==player&&field[1][3]==player&&field[1][4]==player&&field[1][5]==player){return true;}
	if(field[2][0]==player&&field[2][1]==player&&field[2][2]==player&&field[2][3]==player){return true;}
	if(field[2][1]==player&&field[2][2]==player&&field[2][3]==player&&field[2][4]==player){return true;}
	if(field[2][2]==player&&field[2][3]==player&&field[2][4]==player&&field[2][5]==player){return true;}
	if(field[3][0]==player&&field[3][1]==player&&field[3][2]==player&&field[3][3]==player){return true;}
	if(field[3][1]==player&&field[3][2]==player&&field[3][3]==player&&field[3][4]==player){return true;}
	if(field[3][2]==player&&field[3][3]==player&&field[3][4]==player&&field[3][5]==player){return true;}
	if(field[4][0]==player&&field[4][1]==player&&field[4][2]==player&&field[4][3]==player){return true;}
	if(field[4][1]==player&&field[4][2]==player&&field[4][3]==player&&field[4][4]==player){return true;}
	if(field[4][2]==player&&field[4][3]==player&&field[4][4]==player&&field[4][5]==player){return true;}
	if(field[5][0]==player&&field[5][1]==player&&field[5][2]==player&&field[5][3]==player){return true;}
	if(field[5][1]==player&&field[5][2]==player&&field[5][3]==player&&field[5][4]==player){return true;}
	if(field[5][2]==player&&field[5][3]==player&&field[5][4]==player&&field[5][5]==player){return true;}
	if(field[6][0]==player&&field[6][1]==player&&field[6][2]==player&&field[6][3]==player){return true;}
	if(field[6][1]==player&&field[6][2]==player&&field[6][3]==player&&field[6][4]==player){return true;}
	if(field[6][2]==player&&field[6][3]==player&&field[6][4]==player&&field[6][5]==player){return true;}
	//controleer diagonaal
	if(field[0][0]==player&&field[1][1]==player&&field[2][2]==player&&field[3][3]==player){return true;}
	if(field[3][0]==player&&field[2][1]==player&&field[1][2]==player&&field[0][3]==player){return true;}
	if(field[0][1]==player&&field[1][2]==player&&field[2][3]==player&&field[3][4]==player){return true;}
	if(field[3][1]==player&&field[2][2]==player&&field[1][3]==player&&field[0][4]==player){return true;}
	if(field[0][2]==player&&field[1][3]==player&&field[2][4]==player&&field[3][5]==player){return true;}
	if(field[3][2]==player&&field[2][3]==player&&field[1][4]==player&&field[0][5]==player){return true;}
	if(field[1][0]==player&&field[2][1]==player&&field[3][2]==player&&field[4][3]==player){return true;}
	if(field[4][0]==player&&field[3][1]==player&&field[2][2]==player&&field[1][3]==player){return true;}
	if(field[1][1]==player&&field[2][2]==player&&field[3][3]==player&&field[4][4]==player){return true;}
	if(field[4][1]==player&&field[3][2]==player&&field[2][3]==player&&field[1][4]==player){return true;}
	if(field[1][2]==player&&field[2][3]==player&&field[3][4]==player&&field[4][5]==player){return true;}
	if(field[4][2]==player&&field[3][3]==player&&field[2][4]==player&&field[1][5]==player){return true;}
	if(field[2][0]==player&&field[3][1]==player&&field[4][2]==player&&field[5][3]==player){return true;}
	if(field[5][0]==player&&field[4][1]==player&&field[3][2]==player&&field[2][3]==player){return true;}
	if(field[2][1]==player&&field[3][2]==player&&field[4][3]==player&&field[5][4]==player){return true;}
	if(field[5][1]==player&&field[4][2]==player&&field[3][3]==player&&field[2][4]==player){return true;}
	if(field[2][2]==player&&field[3][3]==player&&field[4][4]==player&&field[5][5]==player){return true;}
	if(field[5][2]==player&&field[4][3]==player&&field[3][4]==player&&field[2][5]==player){return true;}
	if(field[3][0]==player&&field[4][1]==player&&field[5][2]==player&&field[6][3]==player){return true;}
	if(field[6][0]==player&&field[5][1]==player&&field[4][2]==player&&field[3][3]==player){return true;}
	if(field[3][1]==player&&field[4][2]==player&&field[5][3]==player&&field[6][4]==player){return true;}
	if(field[6][1]==player&&field[5][2]==player&&field[4][3]==player&&field[3][4]==player){return true;}
	if(field[3][2]==player&&field[4][3]==player&&field[5][4]==player&&field[6][5]==player){return true;}
	if(field[6][2]==player&&field[5][3]==player&&field[4][4]==player&&field[3][5]==player){return true;}
	return false;
}
void dropstone(int row, int player)
{
	//zet een steen neer bovenop de laatste steen in die kolom
	if(row==1)
	{
		field[row-1][5-tot1]=player;
		tot1++;
	}
	if(row==2)
	{
		field[row-1][5-tot2]=player;
		tot2++;
	}
	if(row==3)
	{
		field[row-1][5-tot3]=player;
		tot3++;
	}
	if(row==4)
	{
		field[row-1][5-tot4]=player;
		tot4++;
	}
	if(row==5)
	{
		field[row-1][5-tot5]=player;
		tot5++;
	}
	if(row==6)
	{
		field[row-1][5-tot6]=player;
		tot6++;
	}
	if(row==7)
	{
		field[row-1][5-tot7]=player;
		tot7++;
	}
}
void removestone(int row)
{
	//haal de bovenste steen in een kolom weg
	if(row==1)
	{
		if(tot1>=1)
		{
			field[row-1][6-tot1]=0;
			tot1--;
		}
	}
	if(row==2)
	{
		if(tot2>=1)
		{
			field[row-1][6-tot2]=0;
			tot2--;
		}
	}
	if(row==3)
	{
		if(tot3>=1)
		{
			field[row-1][6-tot3]=0;
			tot3--;
		}
	}
	if(row==4)
	{
		if(tot4>=1)
		{
			field[row-1][6-tot4]=0;
			tot4--;
		}
	}
	if(row==5)
	{
		if(tot5>=1)
		{
			field[row-1][6-tot5]=0;
			tot5--;
		}
	}
	if(row==6)
	{
		if(tot6>=1)
		{
			field[row-1][6-tot6]=0;
			tot6--;
		}
	}
	if(row==7)
	{
		if(tot7>=1)
		{
			field[row-1][6-tot7]=0;
			tot7--;
		}
	}
}
int main(void)
{
	//nog even een lading variabelen initialiseren
	tot1=0; tot2=0; tot3=0; tot4=0; tot5=0; tot6=0; tot7=0;
	int i=0, j=0, stop=false, order=0, wins1=0, wins2=0, wins3=0, wins4=0, wins5=0, wins6=0, wins7=0, loss1=0, loss2=0, loss3=0, loss4=0, loss5=0, loss6=0, loss7=0;
	bool exclude1=0, exclude2=0, exclude3=0, exclude4=0, exclude5=0, exclude6=0, exclude7=0, dontdo1=0, dontdo2=0, dontdo3=0, dontdo4=0, dontdo5=0, dontdo6=0, dontdo7=0, good1=0, good2=0, good3=0, good4=0, good5=0, good6=0, good7=0;
	for (i=0;i<=6;i++)
	{
		for (j=0;j<=5;j++)
		{
			field[i][j]=0;
		}
	}
	string leesgetal;
	while (1)
	{
		cin >> leesgetal;
		//stop als Quit werd ingevoerd
		if (leesgetal=="Quit")break;
		//zet een steen neer op de juiste plek
		if (leesgetal=="1") {dropstone(1,2); order=1;}
		if (leesgetal=="2") {dropstone(2,2); order=5;}
		if (leesgetal=="3") {dropstone(3,2); order=6;}
		if (leesgetal=="4") {dropstone(4,2); order=3;}
		if (leesgetal=="5") {dropstone(5,2); order=4;}
		if (leesgetal=="6") {dropstone(6,2); order=0;}
		if (leesgetal=="7") {dropstone(7,2); order=2;}
		exclude1=0; exclude2=0; exclude3=0; exclude4=0; exclude5=0; exclude6=0; exclude7=0;
		dontdo1=0; dontdo2=0; dontdo3=0; dontdo4=0; dontdo5=0; dontdo6=0; dontdo7=0;
		good1=0; good2=0; good3=0; good4=0; good5=0; good6=0; good7=0;
		antwoord=8;
		if (leesgetal=="Start"){antwoord = 4; dropstone(4,1);}
		else
		{
			//zodra stop waar is, wordt er niet meer gekeken naar betere zetten
			stop=false;
			//controleer of we kunnen winnen
			//eerst controleren of we er nog ruimte vrij is in de kolom
			if(tot1<=5&&stop==false)
			{
				//zet een steen neer
				dropstone(1,1);
				//controleer of we gewonnen hebben
				if (checkwin(1))
				{
					antwoord=1;
					stop=true;
				}
				else
				{
					//en anders moet de steen weer verwijderd worden
					removestone(1);
				}
			}
			if(tot2<=5&&stop==false)
			{
				dropstone(2,1);
				if (checkwin(1))
				{
					antwoord=2;
					stop=true;
				}
				else
				{
					removestone(2);
				}
			}
			if(tot3<=5&&stop==false)
			{
				dropstone(3,1);
				if (checkwin(1))
				{
					antwoord=3;
					stop=true;
				}
				else
				{
					removestone(3);
				}
			}
			if(tot4<=5&&stop==false)
			{
				dropstone(4,1);
				if (checkwin(1))
				{
					antwoord=4;
					stop=true;
				}
				else
				{
					removestone(4);
				}
			}
			if(tot5<=5&&stop==false)
			{
				dropstone(5,1);
				if (checkwin(1))
				{
					antwoord=5;
					stop=true;
				}
				else
				{
					removestone(5);
				}
			}
			if(tot6<=5&&stop==false)
			{
				dropstone(6,1);
				if (checkwin(1))
				{
					antwoord=6;
					stop=true;
				}
				else
				{
					removestone(6);
				}
			}
			if(tot7<=5&&stop==false)
			{
				dropstone(7,1);
				if (checkwin(1))
				{
					antwoord=7;
					stop=true;
				}
				else
				{
					removestone(7);
				}
			}
			//controleer of de tegenstander kan winnen
			//eerst weer controleren of er nog ruimte is
			if(tot1<=5&&stop==false)
			{
				//zet een steen van de tegenstander neer
				dropstone(1,2);
				//controleer of hij gewonnen heeft
				if (checkwin(2))
				{
					antwoord=1;
					stop=true;
					//haal zijn steen weg
					removestone(1);
					//en zet mijn steen er voor in de plaats
					dropstone(1,1);
				}
				else
				{
					//zijn steen weghalen als het geen winnende zet is
					removestone(1);
				}
			}
			if(tot2<=5&&stop==false)
			{
				dropstone(2,2);
				if (checkwin(2))
				{
					antwoord=2;
					stop=true;
					removestone(2);
					dropstone(2,1);
				}
				else
				{
					removestone(2);
				}
			}
			if(tot3<=5&&stop==false)
			{
				dropstone(3,2);
				if (checkwin(2))
				{
					antwoord=3;
					stop=true;
					removestone(3);
					dropstone(3,1);
				}
				else
				{
					removestone(3);
				}
			}
			if(tot4<=5&&stop==false)
			{
				dropstone(4,2);
				if (checkwin(2))
				{
					antwoord=4;
					stop=true;
					removestone(4);
					dropstone(4,1);
				}
				else
				{
					removestone(4);
				}
			}
			if(tot5<=5&&stop==false)
			{
				dropstone(5,2);
				if (checkwin(2))
				{
					antwoord=5;
					stop=true;
					removestone(5);
					dropstone(5,1);
				}
				else
				{
					removestone(5);
				}
			}
			if(tot6<=5&&stop==false)
			{
				dropstone(6,2);
				if (checkwin(2))
				{
					antwoord=6;
					stop=true;
					removestone(6);
					dropstone(6,1);
				}
				else
				{
					removestone(6);
				}
			}
			if(tot7<=5&&stop==false)
			{
				dropstone(7,2);
				if (checkwin(2))
				{
					antwoord=7;
					stop=true;
					removestone(7);
					dropstone(7,1);
				}
				else
				{
					removestone(7);
				}
			}
			if (stop==false)
			{
				//controleer of de tegenstander kan winnen als we een steen verkeerd neerzetten
				//eerst controleren of er nog genoeg ruimte in de kolom is voor 2 stenen
				if(stop==false&&tot1<=4)
				{
					//leg eerst een eigen steen neer en daarna die vande tegenstander er bovenop
					dropstone(1,1);
					dropstone(1,2);
					//controleer op winst voor de tegenstander
					if(checkwin(2))
					{
						exclude1=true;
					}
					//haal de stenen weer weg
					removestone(1);
					removestone(1);
				}
				if(stop==false&&tot2<=4)
				{
					dropstone(2,1);
					dropstone(2,2);
					if(checkwin(2))
					{
						exclude2=true;
					}
					removestone(2);
					removestone(2);
				}
				if(stop==false&&tot3<=4)
				{
					dropstone(3,1);
					dropstone(3,2);
					if(checkwin(2))
					{
						exclude3=true;
					}
					removestone(3);
					removestone(3);
				}
				if(stop==false&&tot4<=4)
				{
					dropstone(4,1);
					dropstone(4,2);
					if(checkwin(2))
					{
						exclude4=true;
					}
					removestone(4);
					removestone(4);
				}
				if(stop==false&&tot5<=4)
				{
					dropstone(5,1);
					dropstone(5,2);
					if(checkwin(2))
					{
						exclude5=true;
					}
					removestone(5);
					removestone(5);
				}
				if(stop==false&&tot6<=4)
				{
					dropstone(6,1);
					dropstone(6,2);
					if(checkwin(2))
					{
						exclude6=true;
					}
					removestone(6);
					removestone(6);
				}
				if(stop==false&&tot7<=4)
				{
					dropstone(7,1);
					dropstone(7,2);
					if(checkwin(2))
					{
						exclude7=true;
					}
					removestone(7);
					removestone(7);
				}
				//nu andersom, controleer of wij kunnen winnen als hij een verkeerde zet doet
				if(stop==false&&tot1<=4)
				{
					dropstone(1,2);
					dropstone(1,1);
					if(checkwin(1))
					{
						//natuurlijk wel een andere variabele gebruiken
						dontdo1=true;
					}
					removestone(1);
					removestone(1);
				}
				if(stop==false&&tot2<=4)
				{
					dropstone(2,2);
					dropstone(2,1);
					if(checkwin(1))
					{
						dontdo2=true;
					}
					removestone(2);
					removestone(2);
				}
				if(stop==false&&tot3<=4)
				{
					dropstone(3,2);
					dropstone(3,1);
					if(checkwin(1))
					{
						dontdo3=true;
					}
					removestone(3);
					removestone(3);
				}
				if(stop==false&&tot4<=4)
				{
					dropstone(4,2);
					dropstone(4,1);
					if(checkwin(1))
					{
						dontdo4=true;
					}
					removestone(4);
					removestone(4);
				}
				if(stop==false&&tot5<=4)
				{
					dropstone(5,2);
					dropstone(5,1);
					if(checkwin(1))
					{
						dontdo5=true;
					}
					removestone(5);
					removestone(5);
				}
				if(stop==false&&tot6<=4)
				{
					dropstone(6,2);
					dropstone(6,1);
					if(checkwin(1))
					{
						dontdo6=true;
					}
					removestone(6);
					removestone(6);
				}
				if(stop==false&&tot7<=4)
				{
					dropstone(7,2);
					dropstone(7,1);
					if(checkwin(1))
					{
						dontdo7=true;
					}
					removestone(7);
					removestone(7);
				}
				//als we onszelf nu blokkeren, de variabelen exclude1 tot en met exclude7 weer resetten
				//dus als alle zeven kolommen geldt: vol(tot# is 6) of exclude# is waar, worden exclude1 tot en met 7 weer op niet waar gezet
				if ((exclude1==true||tot1>=6)&&(exclude2==true||tot2>=6)&&(exclude3==true||tot3>=6)&&(exclude4==true||tot4>=6)&&(exclude5==true||tot5>=6)&&(exclude6==true||tot6>=6)&&(exclude7==true||tot7>=6))
				{
					exclude1=false;
					exclude2=false;
					exclude3=false;
					exclude4=false;
					exclude5=false;
					exclude6=false;
					exclude7=false;
				}
				//controleer voor elke zet of er winnende posities vrijkomen
				//de check wordt alleen uitgevoerd als exclude# niet waar is
				//voor elke winnende positie gaat wins# één omhoog
				wins1=0;
				if(stop==false&&tot1<=5&&exclude1==false)
				{
					dropstone(1,1);
					if(tot1<=5)
					{
						dropstone(1,1);
						if (checkwin(1))
						{
							wins1++;
						}
						removestone(1);
					}
					if(tot2<=5)
					{
						dropstone(2,1);
						if (checkwin(1))
						{
							wins1++;
						}
						removestone(2);
					}
					if(tot3<=5)
					{
						dropstone(3,1);
						if (checkwin(1))
						{
							wins1++;
						}
						removestone(3);
					}
					if(tot4<=5)
					{
						dropstone(4,1);
						if (checkwin(1))
						{
							wins1++;
						}
						removestone(4);
					}
					//als er 2 of meer winnende posities vrijkomen zetten we daar een steen neer (en winnen we de volgende beurt)
					if(wins1>=2)
					{
						antwoord=1;
						stop=true;
					}
					else
					{
						removestone(1);
					}
				}
				wins2=0;
				if(stop==false&&tot2<=5&&exclude2==false)
				{
					dropstone(2,1);
					if(tot1<=5)
					{
						dropstone(1,1);
						if (checkwin(1))
						{
							wins2++;
						}
						removestone(1);
					}
					if(tot2<=5)
					{
						dropstone(2,1);
						if (checkwin(1))
						{
							wins2++;
						}
						removestone(2);
					}
					if(tot3<=5)
					{
						dropstone(3,1);
						if (checkwin(1))
						{
							wins2++;
						}
						removestone(3);
					}
					if(tot4<=5)
					{
						dropstone(4,1);
						if (checkwin(1))
						{
							wins2++;
						}
						removestone(4);
					}
					if(tot5<=5)
					{
						dropstone(5,1);
						if (checkwin(1))
						{
							wins2++;
						}
						removestone(5);
					}
					if(wins2>=2)
					{
						antwoord=2;
						stop=true;
					}
					else
					{
						removestone(2);
					}
				}
				wins3=0;
				if(stop==false&&tot3<=5&&exclude3==false)
				{
					dropstone(3,1);
					if(tot1<=5)
					{
						dropstone(1,1);
						if (checkwin(1))
						{
							wins3++;
						}
						removestone(1);
					}
					if(tot2<=5)
					{
						dropstone(2,1);
						if (checkwin(1))
						{
							wins3++;
						}
						removestone(2);
					}
					if(tot3<=5)
					{
						dropstone(3,1);
						if (checkwin(1))
						{
							wins3++;
						}
						removestone(3);
					}
					if(tot4<=5)
					{
						dropstone(4,1);
						if (checkwin(1))
						{
							wins3++;
						}
						removestone(4);
					}
					if(tot5<=5)
					{
						dropstone(5,1);
						if (checkwin(1))
						{
							wins3++;
						}
						removestone(5);
					}
					if(tot6<=5)
					{
						dropstone(6,1);
						if (checkwin(1))
						{
							wins3++;
						}
						removestone(6);
					}
					if(wins3>=2)
					{
						antwoord=3;
						stop=true;
					}
					else
					{
						removestone(3);
					}
				}
				wins4=0;
				if(stop==false&&tot4<=5&&exclude4==false)
				{
					dropstone(4,1);
					if(tot1<=5)
					{
						dropstone(1,1);
						if (checkwin(1))
						{
							wins4++;
						}
						removestone(1);
					}
					if(tot2<=5)
					{
						dropstone(2,1);
						if (checkwin(1))
						{
							wins4++;
						}
						removestone(2);
					}
					if(tot3<=5)
					{
						dropstone(3,1);
						if (checkwin(1))
						{
							wins4++;
						}
						removestone(3);
					}
					if(tot4<=5)
					{
						dropstone(4,1);
						if (checkwin(1))
						{
							wins4++;
						}
						removestone(4);
					}
					if(tot5<=5)
					{
						dropstone(5,1);
						if (checkwin(1))
						{
							wins4++;
						}
						removestone(5);
					}
					if(tot6<=5)
					{
						dropstone(6,1);
						if (checkwin(1))
						{
							wins4++;
						}
						removestone(6);
					}
					if(tot7<=5)
					{
						dropstone(7,1);
						if (checkwin(1))
						{
							wins4++;
						}
						removestone(7);
					}
					if(wins4>=2)
					{
						antwoord=4;
						stop=true;
					}
					else
					{
						removestone(4);
					}
				}
				wins5=0;
				if(stop==false&&tot5<=5&&exclude5==false)
				{
					dropstone(5,1);
					if(tot2<=5)
					{
						dropstone(2,1);
						if (checkwin(1))
						{
							wins5++;
						}
						removestone(2);
					}
					if(tot3<=5)
					{
						dropstone(3,1);
						if (checkwin(1))
						{
							wins5++;
						}
						removestone(3);
					}
					if(tot4<=5)
					{
						dropstone(4,1);
						if (checkwin(1))
						{
							wins5++;
						}
						removestone(4);
					}
					if(tot5<=5)
					{
						dropstone(5,1);
						if (checkwin(1))
						{
							wins5++;
						}
						removestone(5);
					}
					if(tot6<=5)
					{
						dropstone(6,1);
						if (checkwin(1))
						{
							wins5++;
						}
						removestone(6);
					}
					if(tot7<=5)
					{
						dropstone(7,1);
						if (checkwin(1))
						{
							wins5++;
						}
						removestone(7);
					}
					if(wins5>=2)
					{
						antwoord=5;
						stop=true;
					}
					else
					{
						removestone(5);
					}
				}
				wins6=0;
				if(stop==false&&tot6<=5&&exclude6==false)
				{
					dropstone(6,1);
					if(tot3<=5)
					{
						dropstone(3,1);
						if (checkwin(1))
						{
							wins6++;
						}
						removestone(3);
					}
					if(tot4<=5)
					{
						dropstone(4,1);
						if (checkwin(1))
						{
							wins6++;
						}
						removestone(4);
					}
					if(tot5<=5)
					{
						dropstone(5,1);
						if (checkwin(1))
						{
							wins6++;
						}
						removestone(5);
					}
					if(tot6<=5)
					{
						dropstone(6,1);
						if (checkwin(1))
						{
							wins6++;
						}
						removestone(6);
					}
					if(tot7<=5)
					{
						dropstone(7,1);
						if (checkwin(1))
						{
							wins6++;
						}
						removestone(7);
					}
					if(wins6>=2)
					{
						antwoord=6;
						stop=true;
					}
					else
					{
						removestone(6);
					}
				}
				wins7=0;
				if(stop==false&&tot7<=5&&exclude7==false)
				{
					dropstone(7,1);
					if(tot4<=5)
					{
						dropstone(4,1);
						if (checkwin(1))
						{
							wins7++;
						}
						removestone(4);
					}
					if(tot5<=5)
					{
						dropstone(5,1);
						if (checkwin(1))
						{
							wins7++;
						}
						removestone(5);
					}
					if(tot6<=5)
					{
						dropstone(6,1);
						if (checkwin(1))
						{
							wins7++;
						}
						removestone(6);
					}
					if(tot7<=5)
					{
						dropstone(7,1);
						if (checkwin(1))
						{
							wins7++;
						}
						removestone(7);
					}
					if(wins7>=2)
					{
						antwoord=7;
						stop=true;
					}
					else
					{
						removestone(7);
					}
				}
				//controleer of we winnen als we er een eigen steen, een van de tegenstander en nog een eigen steen in gooien
				if(stop==false&&tot1<=3)
				{
					//eerst 3 stenen erin gooien
					dropstone(1,1);
					dropstone(1,2);
					dropstone(1,1);
					if(checkwin(1))
					{
						good1=true;
					}
					//en ze weer verwijderen
					removestone(1);
					removestone(1);
					removestone(1);
				}
				if(stop==false&&tot2<=3)
				{
					dropstone(2,1);
					dropstone(2,2);
					dropstone(2,1);
					if(checkwin(1))
					{
						good2=true;
					}
					removestone(2);
					removestone(2);
					removestone(2);
				}
				if(stop==false&&tot3<=3)
				{
					dropstone(3,1);
					dropstone(3,2);
					dropstone(3,1);
					if(checkwin(1))
					{
						good3=true;
					}
					removestone(3);
					removestone(3);
					removestone(3);
				}
				if(stop==false&&tot4<=3)
				{
					dropstone(4,1);
					dropstone(4,2);
					dropstone(4,1);
					if(checkwin(1))
					{
						good4=true;
					}
					removestone(4);
					removestone(4);
					removestone(4);
				}
				if(stop==false&&tot5<=3)
				{
					dropstone(5,1);
					dropstone(5,2);
					dropstone(5,1);
					if(checkwin(1))
					{
						good5=true;
					}
					removestone(5);
					removestone(5);
					removestone(5);
				}
				if(stop==false&&tot6<=3)
				{
					dropstone(6,1);
					dropstone(6,2);
					dropstone(6,1);
					if(checkwin(1))
					{
						good6=true;
					}
					removestone(6);
					removestone(6);
					removestone(6);
				}
				if(stop==false&&tot7<=3)
				{
					dropstone(7,1);
					dropstone(7,2);
					dropstone(7,1);
					if(checkwin(1))
					{
						good7=true;
					}
					removestone(7);
					removestone(7);
					removestone(7);
				}
				//als dontdo# en good# beide waar zijn kunnen we dus winnen als we in die kolom een steen zetten
				if(good1==true&&dontdo1==true&&exclude1==false&&stop==false){antwoord=1; stop=true; dropstone(1,1);}
				if(good2==true&&dontdo2==true&&exclude2==false&&stop==false){antwoord=2; stop=true; dropstone(2,1);}
				if(good3==true&&dontdo3==true&&exclude3==false&&stop==false){antwoord=3; stop=true; dropstone(3,1);}
				if(good4==true&&dontdo4==true&&exclude4==false&&stop==false){antwoord=4; stop=true; dropstone(4,1);}
				if(good5==true&&dontdo5==true&&exclude5==false&&stop==false){antwoord=5; stop=true; dropstone(5,1);}
				if(good6==true&&dontdo6==true&&exclude6==false&&stop==false){antwoord=6; stop=true; dropstone(6,1);}
				if(good7==true&&dontdo7==true&&exclude7==false&&stop==false){antwoord=7; stop=true; dropstone(7,1);}
				//dit (onder) controleert of de tegenstander een zet kan doen waardoor hij 2 winnende posities creeert
				//dit is dus hetzelfde als hierboven (regel 615) maar dan voor de tegenstander
				loss1=0;
				if(stop==false&&tot1<=5&&exclude1==false)
				{
					dropstone(1,2);
					if(tot1<=5)
					{
						dropstone(1,2);
						if (checkwin(2))
						{
							loss1++;
						}
						removestone(1);
					}
					if(tot2<=5)
					{
						dropstone(2,2);
						if (checkwin(2))
						{
							loss1++;
						}
						removestone(2);
					}
					if(tot3<=5)
					{
						dropstone(3,2);
						if (checkwin(2))
						{
							loss1++;
						}
						removestone(3);
					}
					if(tot4<=5)
					{
						dropstone(4,2);
						if (checkwin(2))
						{
							loss1++;
						}
						removestone(4);
					}
					removestone(1);
					if(loss1>=2)
					{
						antwoord=1;
						stop=true;
						dropstone(1,1);
					}
				}
				loss2=0;
				if(stop==false&&tot2<=5&&exclude2==false)
				{
					dropstone(2,2);
					if(tot1<=5)
					{
						dropstone(1,2);
						if (checkwin(2))
						{
							loss2++;
						}
						removestone(1);
					}
					if(tot2<=5)
					{
						dropstone(2,2);
						if (checkwin(2))
						{
							loss2++;
						}
						removestone(2);
					}
					if(tot3<=5)
					{
						dropstone(3,2);
						if (checkwin(2))
						{
							loss2++;
						}
						removestone(3);
					}
					if(tot4<=5)
					{
						dropstone(4,2);
						if (checkwin(2))
						{
							loss2++;
						}
						removestone(4);
					}
					if(tot5<=5)
					{
						dropstone(5,2);
						if (checkwin(2))
						{
							loss2++;
						}
						removestone(5);
					}
					removestone(2);
					if(loss2>=2)
					{
						antwoord=2;
						stop=true;
						dropstone(2,1);
					}
				}
				loss3=0;
				if(stop==false&&tot3<=5&&exclude3==false)
				{
					dropstone(3,2);
					if(tot1<=5)
					{
						dropstone(1,2);
						if (checkwin(2))
						{
							loss3++;
						}
						removestone(1);
					}
					if(tot2<=5)
					{
						dropstone(2,2);
						if (checkwin(2))
						{
							loss3++;
						}
						removestone(2);
					}
					if(tot3<=5)
					{
						dropstone(3,2);
						if (checkwin(2))
						{
							loss3++;
						}
						removestone(3);
					}
					if(tot4<=5)
					{
						dropstone(4,2);
						if (checkwin(2))
						{
							loss3++;
						}
						removestone(4);
					}
					if(tot5<=5)
					{
						dropstone(5,2);
						if (checkwin(2))
						{
							loss3++;
						}
						removestone(5);
					}
					if(tot6<=5)
					{
						dropstone(6,2);
						if (checkwin(2))
						{
							loss3++;
						}
						removestone(6);
					}
					removestone(3);
					if(loss3>=2)
					{
						antwoord=3;
						stop=true;
						dropstone(3,1);
					}
				}
				loss4=0;
				if(stop==false&&tot4<=5&&exclude4==false)
				{
					dropstone(4,2);
					if(tot1<=5)
					{
						dropstone(1,2);
						if (checkwin(2))
						{
							loss4++;
						}
						removestone(1);
					}
					if(tot2<=5)
					{
						dropstone(2,2);
						if (checkwin(2))
						{
							loss4++;
						}
						removestone(2);
					}
					if(tot3<=5)
					{
						dropstone(3,2);
						if (checkwin(2))
						{
							loss4++;
						}
						removestone(3);
					}
					if(tot4<=5)
					{
						dropstone(4,2);
						if (checkwin(2))
						{
							loss4++;
						}
						removestone(4);
					}
					if(tot5<=5)
					{
						dropstone(5,2);
						if (checkwin(2))
						{
							loss4++;
						}
						removestone(5);
					}
					if(tot6<=5)
					{
						dropstone(6,2);
						if (checkwin(2))
						{
							loss4++;
						}
						removestone(6);
					}
					if(tot7<=5)
					{
						dropstone(7,2);
						if (checkwin(2))
						{
							loss4++;
						}
						removestone(7);
					}
					removestone(4);
					if(loss4>=2)
					{
						antwoord=4;
						stop=true;
						dropstone(4,1);
					}
				}
				loss5=0;
				if(stop==false&&tot5<=5&&exclude5==false)
				{
					dropstone(5,2);
					if(tot2<=5)
					{
						dropstone(2,2);
						if (checkwin(2))
						{
							loss5++;
						}
						removestone(2);
					}
					if(tot3<=5)
					{
						dropstone(3,2);
						if (checkwin(2))
						{
							loss5++;
						}
						removestone(3);
					}
					if(tot4<=5)
					{
						dropstone(4,2);
						if (checkwin(2))
						{
							loss5++;
						}
						removestone(4);
					}
					if(tot5<=5)
					{
						dropstone(5,2);
						if (checkwin(2))
						{
							loss5++;
						}
						removestone(5);
					}
					if(tot6<=5)
					{
						dropstone(6,2);
						if (checkwin(2))
						{
							loss5++;
						}
						removestone(6);
					}
					if(tot7<=5)
					{
						dropstone(7,2);
						if (checkwin(2))
						{
							loss5++;
						}
						removestone(7);
					}
					removestone(5);
					if(loss5>=2)
					{
						antwoord=5;
						stop=true;
						dropstone(5,1);
					}
				}
				loss6=0;
				if(stop==false&&tot6<=5&&exclude6==false)
				{
					dropstone(6,2);
					if(tot3<=5)
					{
						dropstone(3,2);
						if (checkwin(2))
						{
							loss6++;
						}
						removestone(3);
					}
					if(tot4<=5)
					{
						dropstone(4,2);
						if (checkwin(2))
						{
							loss6++;
						}
						removestone(4);
					}
					if(tot5<=5)
					{
						dropstone(5,2);
						if (checkwin(2))
						{
							loss6++;
						}
						removestone(5);
					}
					if(tot6<=5)
					{
						dropstone(6,2);
						if (checkwin(2))
						{
							loss6++;
						}
						removestone(6);
					}
					if(tot7<=5)
					{
						dropstone(7,2);
						if (checkwin(2))
						{
							loss6++;
						}
						removestone(7);
					}
					removestone(6);
					if(loss6>=2)
					{
						antwoord=6;
						stop=true;
						dropstone(6,1);
					}
				}
				loss7=0;
				if(stop==false&&tot7<=5&&exclude7==false)
				{
					dropstone(7,2);
					if(tot4<=5)
					{
						dropstone(4,2);
						if (checkwin(2))
						{
							loss7++;
						}
						removestone(4);
					}
					if(tot5<=5)
					{
						dropstone(5,2);
						if (checkwin(2))
						{
							loss7++;
						}
						removestone(5);
					}
					if(tot6<=5)
					{
						dropstone(6,2);
						if (checkwin(2))
						{
							loss7++;
						}
						removestone(6);
					}
					if(tot7<=5)
					{
						dropstone(7,2);
						if (checkwin(2))
						{
							loss7++;
						}
						removestone(7);
					}
					removestone(7);
					if(loss7>=2)
					{
						antwoord=7;
						stop=true;
						dropstone(7,1);
					}
				}
				//zelfde check als eerder gedaan voor exclude#, maar nu voor dontdo#
				//als alle kolommen geblokkeerd zijn (exclude# of dontdo# is waar of de kolom zit vol) worden dontdo1 tot en met dontdo7 onwaar gemaakt
				if ((exclude1==true||dontdo1==true||tot1>=6)&&(exclude2==true||dontdo2==true||tot2>=6)&&(exclude3==true||dontdo3==true||tot3>=6)&&(exclude4==true||dontdo4==true||tot4>=6)&&(exclude5==true||dontdo5==true||tot5>=6)&&(exclude6==true||dontdo6==true||tot6>=6)&&(exclude7==true||dontdo7==true||tot7>=6))
				{
					dontdo1=false;
					dontdo2=false;
					dontdo3=false;
					dontdo4=false;
					dontdo5=false;
					dontdo6=false;
					dontdo7=false;
				}
				//nog een paar checks waarbij good# op waar gezet kan worden
				if(stop==false&&tot1<=4&&dontdo1==false)
				{
					//zet een vijandige steen en een eigen steen neer
					dropstone(1,2);
					dropstone(1,1);
					//als dat een winnende situatie oplevert wordt good# voor die kolom op waar gezet
					if(tot2<=5){dropstone(2,1); if(checkwin(1)){good2=true;} removestone(2);}
					if(tot3<=5){dropstone(3,1); if(checkwin(1)){good3=true;} removestone(3);}
					if(tot4<=5){dropstone(4,1); if(checkwin(1)){good4=true;} removestone(4);}
					removestone(1);
					removestone(1);
				}
				if(stop==false&&tot2<=4&&dontdo2==false)
				{
					dropstone(2,2);
					dropstone(2,1);
					if(tot1<=5){dropstone(1,1); if(checkwin(1)){good1=true;} removestone(1);}
					if(tot3<=5){dropstone(3,1); if(checkwin(1)){good3=true;} removestone(3);}
					if(tot4<=5){dropstone(4,1); if(checkwin(1)){good4=true;} removestone(4);}
					if(tot5<=5){dropstone(5,1); if(checkwin(1)){good5=true;} removestone(5);}
					removestone(2);
					removestone(2);
				}
				if(stop==false&&tot3<=4&&dontdo3==false)
				{
					dropstone(3,2);
					dropstone(3,1);
					if(tot1<=5){dropstone(1,1); if(checkwin(1)){good1=true;} removestone(1);}
					if(tot2<=5){dropstone(2,1); if(checkwin(1)){good2=true;} removestone(2);}
					if(tot4<=5){dropstone(4,1); if(checkwin(1)){good4=true;} removestone(4);}
					if(tot5<=5){dropstone(5,1); if(checkwin(1)){good5=true;} removestone(5);}
					if(tot6<=5){dropstone(6,1); if(checkwin(1)){good6=true;} removestone(6);}
					removestone(3);
					removestone(3);
				}
				if(stop==false&&tot4<=4&&dontdo4==false)
				{
					dropstone(4,2);
					dropstone(4,1);
					if(tot1<=5){dropstone(1,1); if(checkwin(1)){good1=true;} removestone(1);}
					if(tot2<=5){dropstone(2,1); if(checkwin(1)){good2=true;} removestone(2);}
					if(tot3<=5){dropstone(3,1); if(checkwin(1)){good3=true;} removestone(3);}
					if(tot5<=5){dropstone(5,1); if(checkwin(1)){good5=true;} removestone(5);}
					if(tot6<=5){dropstone(6,1); if(checkwin(1)){good6=true;} removestone(6);}
					if(tot7<=5){dropstone(7,1); if(checkwin(1)){good7=true;} removestone(7);}
					removestone(4);
					removestone(4);
				}
				if(stop==false&&tot5<=4&&dontdo5==false)
				{
					dropstone(5,2);
					dropstone(5,1);
					if(tot2<=5){dropstone(2,1); if(checkwin(1)){good2=true;} removestone(2);}
					if(tot3<=5){dropstone(3,1); if(checkwin(1)){good3=true;} removestone(3);}
					if(tot4<=5){dropstone(4,1); if(checkwin(1)){good4=true;} removestone(4);}
					if(tot6<=5){dropstone(6,1); if(checkwin(1)){good6=true;} removestone(6);}
					if(tot7<=5){dropstone(7,1); if(checkwin(1)){good7=true;} removestone(7);}
					removestone(5);
					removestone(5);
				}
				if(stop==false&&tot6<=4&&dontdo6==false)
				{
					dropstone(6,2);
					dropstone(6,1);
					if(tot3<=5){dropstone(3,1); if(checkwin(1)){good3=true;} removestone(3);}
					if(tot4<=5){dropstone(4,1); if(checkwin(1)){good4=true;} removestone(4);}
					if(tot5<=5){dropstone(5,1); if(checkwin(1)){good5=true;} removestone(5);}
					if(tot7<=5){dropstone(7,1); if(checkwin(1)){good7=true;} removestone(7);}
					removestone(6);
					removestone(6);
				}
				if(stop==false&&tot7<=4&&dontdo7==false)
				{
					dropstone(7,2);
					dropstone(7,1);
					if(tot4<=5){dropstone(4,1); if(checkwin(1)){good4=true;} removestone(4);}
					if(tot5<=5){dropstone(5,1); if(checkwin(1)){good5=true;} removestone(5);}
					if(tot6<=5){dropstone(6,1); if(checkwin(1)){good6=true;} removestone(6);}
					removestone(7);
					removestone(7);
				}
				//als ergens good# waar is of wins# groter dan 1 wordt daar een steen gezet
				if((good4==true||wins4>=1)&&exclude4==false&&dontdo4==false&&stop==false){antwoord=4; stop=true; dropstone(4,1);}
				if((good3==true||wins3>=1)&&exclude3==false&&dontdo3==false&&stop==false){antwoord=3; stop=true; dropstone(3,1);}
				if((good5==true||wins5>=1)&&exclude5==false&&dontdo5==false&&stop==false){antwoord=5; stop=true; dropstone(5,1);}
				if((good2==true||wins2>=1)&&exclude2==false&&dontdo2==false&&stop==false){antwoord=2; stop=true; dropstone(2,1);}
				if((good6==true||wins6>=1)&&exclude6==false&&dontdo6==false&&stop==false){antwoord=6; stop=true; dropstone(6,1);}
				if((good1==true||wins1>=1)&&exclude1==false&&dontdo1==false&&stop==false){antwoord=1; stop=true; dropstone(1,1);}
				if((good7==true||wins7>=1)&&exclude7==false&&dontdo7==false&&stop==false){antwoord=7; stop=true; dropstone(7,1);}
				//als loss# ergens groter is dan 1 wordt daar een steen gezet
				if(loss4>=1&&exclude4==false&&stop==false&&dontdo4==false){antwoord=4; stop=true; dropstone(4,1);}
				if(loss3>=1&&exclude3==false&&stop==false&&dontdo3==false){antwoord=3; stop=true; dropstone(3,1);}
				if(loss5>=1&&exclude5==false&&stop==false&&dontdo5==false){antwoord=5; stop=true; dropstone(5,1);}
				if(loss2>=1&&exclude2==false&&stop==false&&dontdo2==false){antwoord=2; stop=true; dropstone(2,1);}
				if(loss6>=1&&exclude6==false&&stop==false&&dontdo6==false){antwoord=6; stop=true; dropstone(6,1);}
				if(loss1>=1&&exclude1==false&&stop==false&&dontdo1==false){antwoord=1; stop=true; dropstone(1,1);}
				if(loss7>=1&&exclude7==false&&stop==false&&dontdo7==false){antwoord=7; stop=true; dropstone(7,1);}
				//doe een willekeurige zet
				//ik wist nog geen andere manier voor willekeurige getallen dus heb ik dit maar zo gedaan
				//tel een aantal getallen bij elkaar op en haal er zo vaak mogelijk 7 van af
				//dit resulteert in een getal van 0-6
				//dat bepaalt in welke volgorde de kolommen bekeken worden om te kijken of er een zet mogelijk is (altijd een of meer kolommen)
				order=(order+tot2+tot4+tot6+3)%7;
				if (order==3)
				{
					if (stop==false&&dontdo3==false&&exclude3==false&&tot3<=5){antwoord=3; stop=true; dropstone(3,1);}
					if (stop==false&&dontdo1==false&&exclude1==false&&tot1<=5){antwoord=1; stop=true; dropstone(1,1);}
					if (stop==false&&dontdo2==false&&exclude2==false&&tot2<=5){antwoord=2; stop=true; dropstone(2,1);}
					if (stop==false&&dontdo5==false&&exclude5==false&&tot5<=5){antwoord=5; stop=true; dropstone(5,1);}
					if (stop==false&&dontdo4==false&&exclude4==false&&tot4<=5){antwoord=4; stop=true; dropstone(4,1);}
					if (stop==false&&dontdo6==false&&exclude6==false&&tot6<=5){antwoord=6; stop=true; dropstone(6,1);}
					if (stop==false&&dontdo7==false&&exclude7==false&&tot7<=5){antwoord=7; stop=true; dropstone(7,1);}
				}
				if (order==5)
				{
					if (stop==false&&dontdo2==false&&exclude2==false&&tot2<=5){antwoord=2; stop=true; dropstone(2,1);}
					if (stop==false&&dontdo3==false&&exclude3==false&&tot3<=5){antwoord=3; stop=true; dropstone(3,1);}
					if (stop==false&&dontdo4==false&&exclude4==false&&tot4<=5){antwoord=4; stop=true; dropstone(4,1);}
					if (stop==false&&dontdo5==false&&exclude5==false&&tot5<=5){antwoord=5; stop=true; dropstone(5,1);}
					if (stop==false&&dontdo6==false&&exclude6==false&&tot6<=5){antwoord=6; stop=true; dropstone(6,1);}
					if (stop==false&&dontdo7==false&&exclude7==false&&tot7<=5){antwoord=7; stop=true; dropstone(7,1);}
					if (stop==false&&dontdo1==false&&exclude1==false&&tot1<=5){antwoord=1; stop=true; dropstone(1,1);}
				}
				if (order==0)
				{
					if (stop==false&&dontdo3==false&&exclude3==false&&tot3<=5){antwoord=3; stop=true; dropstone(3,1);}
					if (stop==false&&dontdo4==false&&exclude4==false&&tot4<=5){antwoord=4; stop=true; dropstone(4,1);}
					if (stop==false&&dontdo5==false&&exclude5==false&&tot5<=5){antwoord=5; stop=true; dropstone(5,1);}
					if (stop==false&&dontdo6==false&&exclude6==false&&tot6<=5){antwoord=6; stop=true; dropstone(6,1);}
					if (stop==false&&dontdo7==false&&exclude7==false&&tot7<=5){antwoord=7; stop=true; dropstone(7,1);}
					if (stop==false&&dontdo1==false&&exclude1==false&&tot1<=5){antwoord=1; stop=true; dropstone(1,1);}
					if (stop==false&&dontdo2==false&&exclude2==false&&tot2<=5){antwoord=2; stop=true; dropstone(2,1);}
				}
				if (order==2)
				{
					if (stop==false&&dontdo4==false&&exclude4==false&&tot4<=5){antwoord=4; stop=true; dropstone(4,1);}
					if (stop==false&&dontdo5==false&&exclude5==false&&tot5<=5){antwoord=5; stop=true; dropstone(5,1);}
					if (stop==false&&dontdo6==false&&exclude6==false&&tot6<=5){antwoord=6; stop=true; dropstone(6,1);}
					if (stop==false&&dontdo7==false&&exclude7==false&&tot7<=5){antwoord=7; stop=true; dropstone(7,1);}
					if (stop==false&&dontdo1==false&&exclude1==false&&tot1<=5){antwoord=1; stop=true; dropstone(1,1);}
					if (stop==false&&dontdo2==false&&exclude2==false&&tot2<=5){antwoord=2; stop=true; dropstone(2,1);}
					if (stop==false&&dontdo3==false&&exclude3==false&&tot3<=5){antwoord=3; stop=true; dropstone(3,1);}
				}
				if (order==4)
				{
					if (stop==false&&dontdo5==false&&exclude5==false&&tot5<=5){antwoord=5; stop=true; dropstone(5,1);}
					if (stop==false&&dontdo6==false&&exclude6==false&&tot6<=5){antwoord=6; stop=true; dropstone(6,1);}
					if (stop==false&&dontdo3==false&&exclude3==false&&tot3<=5){antwoord=3; stop=true; dropstone(3,1);}
					if (stop==false&&dontdo4==false&&exclude4==false&&tot4<=5){antwoord=4; stop=true; dropstone(4,1);}
					if (stop==false&&dontdo7==false&&exclude7==false&&tot7<=5){antwoord=7; stop=true; dropstone(7,1);}
					if (stop==false&&dontdo1==false&&exclude1==false&&tot1<=5){antwoord=1; stop=true; dropstone(1,1);}
					if (stop==false&&dontdo2==false&&exclude2==false&&tot2<=5){antwoord=2; stop=true; dropstone(2,1);}
				}
				if (order==6)
				{
					if (stop==false&&dontdo6==false&&exclude6==false&&tot6<=5){antwoord=6; stop=true; dropstone(6,1);}
					if (stop==false&&dontdo1==false&&exclude1==false&&tot1<=5){antwoord=1; stop=true; dropstone(1,1);}
					if (stop==false&&dontdo7==false&&exclude7==false&&tot7<=5){antwoord=7; stop=true; dropstone(7,1);}
					if (stop==false&&dontdo2==false&&exclude2==false&&tot2<=5){antwoord=2; stop=true; dropstone(2,1);}
					if (stop==false&&dontdo3==false&&exclude3==false&&tot3<=5){antwoord=3; stop=true; dropstone(3,1);}
					if (stop==false&&dontdo4==false&&exclude4==false&&tot4<=5){antwoord=4; stop=true; dropstone(4,1);}
					if (stop==false&&dontdo5==false&&exclude5==false&&tot5<=5){antwoord=5; stop=true; dropstone(5,1);}
				}
				if (order==1)
				{
					if (stop==false&&dontdo5==false&&exclude5==false&&tot5<=5){antwoord=5; stop=true; dropstone(5,1);}
					if (stop==false&&dontdo4==false&&exclude4==false&&tot4<=5){antwoord=4; stop=true; dropstone(4,1);}
					if (stop==false&&dontdo3==false&&exclude3==false&&tot3<=5){antwoord=3; stop=true; dropstone(3,1);}
					if (stop==false&&dontdo7==false&&exclude7==false&&tot7<=5){antwoord=7; stop=true; dropstone(7,1);}
					if (stop==false&&dontdo1==false&&exclude1==false&&tot1<=5){antwoord=1; stop=true; dropstone(1,1);}
					if (stop==false&&dontdo2==false&&exclude2==false&&tot2<=5){antwoord=2; stop=true; dropstone(2,1);}
					if (stop==false&&dontdo6==false&&exclude6==false&&tot6<=5){antwoord=6; stop=true; dropstone(6,1);}
				}
			}
		}
		//error check, als het antwoord nog steeds 8 is wordt er wat neer stderr geschreven en is er een kleine kans dat er alsnog een geldige zet wordt doorgestuurd
		if (antwoord==8)
		{
			cerr << "antwoord= " << antwoord << " maxrows 1-7: " << tot1 << tot2 << tot3 << tot4 << tot5 << tot6 << tot7 << " input: " << leesgetal << " order: " << order << endl;
			if(tot4<=5) {antwoord=4; dropstone(4,1);}
			else {antwoord=2; dropstone(2,1);}
		}
		//stuur het antwoord door naar de jurysoftware en flush
		cout << antwoord << endl;
	}
	return 0;
}