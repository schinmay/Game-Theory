#include <stdio.h>
#include <stdlib.h>
int* minimax(int [], int, int);
int game_over(int []);
void game_print(int []);
int main()
{
	int i,j,index,n=9,box[9]={0,0,0,0,0,0,0,0,0},move,*value;
	value = (int *) malloc(2*sizeof(int));
	char turn;
	printf("You are X, Computer is O\nSpecify if you want to go first or not? Y/N\n");
	while(1)	
	{
		scanf("%c",&turn);
		if(turn=='\n')
		{
			continue;
		}		
		else if(turn!='y'&&turn!='Y'&&turn!='n'&&turn!='N')
		{
			printf("Reply with a Y/y or N/n\n");
		}
		else
		{
			if(turn=='y'||turn=='Y')
			{
				move=-1;
			}
			else if(turn=='n'||turn=='N')
			{	
				move=1;
			}
			break;
		}
	}
	printf("Index of Locations:\n 1 | 2 | 3\n------------\n 4 | 5 | 6\n------------\n 7 | 8 | 9\n");
	while(n>0)
	{
		if(game_over(box)==1||game_over(box)==-1)
		{
			break;
		}		
		if(move==1)
		{
			for(int i=0;i<9;i++)
			{
				if(box[i]==0)
				{
					box[i]=1;
					if(game_over(box)==1)
					{
						printf("After Computer's move:\n");						
						game_print(box);
						n=0;
						break;
					}
					else
					{
						box[i]=0;	
					}			
				}
			}
			if(n!=0)
			{		
				value = minimax(box,n,1);
				box[value[1]]=1;
				move=-1;
				printf("After Computer's move:\n");
			}
		}
		else if(move==-1)
		{
			while(1)
			{
				printf("Specify your location\n");				
				scanf("%d",&index);		
				if(box[index-1]!=0)
				{
					printf("Already filled\n");
				}
				else
				{
					break;
				}				
			}
			box[index-1]=-1;
			move=1;			
			printf("After your move :\n");
		}
		if(n==0)
		{
			break;
		}
		game_print(box);	
		n--;
	}
	if(game_over(box)==1)
	{
		printf("You lose\n");
	}
	else if(game_over(box)==-1)
	{
		printf("You Win\n");
	}
	else if(n==0)
	{
		printf("Draw\n");
	}
	return 0;
}
int* minimax(int box[], int n, int flag)
{
	int *value,i,index;
	value = (int *) malloc(2*sizeof(int));	
	if(game_over(box)==1)
	{
		value[0]=1;
		value[1]=0;
		return value;
	}
	else if(game_over(box)==-1)
	{
		value[0]=-1;
		value[1]=0;
		return value;
	}
	else if(n==0)
	{
		value[0]=0;
		value[1]=0;
		return value;
	}			
	if(flag==1)	
	{
		int max=-1000;		
		for(i=0;i<9;i++)
		{
			if(box[i]==0)
			{
				box[i]=1;
				value = minimax(box,n-1,0);
				box[i]=0;
				if(value[0]>max)
				{
					max=value[0];						
					index=i;
				}
			}		
		}
		value[0]=max;
		value[1]=index;
		return value;
	}
	else if(flag==0)
	{
		int min=1000;		
		for(i=0;i<9;i++)
		{
			if(box[i]==0)
			{
				box[i]=-1;
				value = minimax(box,n-1,1);
				box[i]=0;
				if(value[0]<min)
				{
					min=value[0];
					index=i;
				}
			}		
		}
		value[0]=min;
		value[1]=index;
		return value;
	}
}
int game_over(int box[])
{
	if((box[0]==box[1]&&box[1]==box[2]&&box[2]==1)||
	   (box[3]==box[4]&&box[4]==box[5]&&box[5]==1)||
	   (box[6]==box[7]&&box[7]==box[8]&&box[8]==1)||
	   (box[0]==box[3]&&box[3]==box[6]&&box[6]==1)||
	   (box[1]==box[4]&&box[4]==box[7]&&box[7]==1)||
	   (box[2]==box[5]&&box[5]==box[8]&&box[8]==1)||
	   (box[0]==box[4]&&box[4]==box[8]&&box[8]==1)||
	   (box[2]==box[4]&&box[4]==box[6]&&box[6]==1))
	{
		return 1;
	}
	else if((box[0]==box[1]&&box[1]==box[2]&&box[2]==-1)||
	   	(box[3]==box[4]&&box[4]==box[5]&&box[5]==-1)||
	   	(box[6]==box[7]&&box[7]==box[8]&&box[8]==-1)||
	   	(box[0]==box[3]&&box[3]==box[6]&&box[6]==-1)||
	   	(box[1]==box[4]&&box[4]==box[7]&&box[7]==-1)||
	   	(box[2]==box[5]&&box[5]==box[8]&&box[8]==-1)||
	   	(box[0]==box[4]&&box[4]==box[8]&&box[8]==-1)||
	   	(box[2]==box[4]&&box[4]==box[6]&&box[6]==-1))
	{
		return -1;
	}
	else
	{
		return 0;
	}
}
void game_print (int box[])
{
	char cbox[9];
	for(int i=0;i<9;i++)
	{
		if(box[i]==0)
		{
			cbox[i]=' ';
		}
		else if(box[i]==1)
		{
			cbox[i]='O';
		}
		else if(box[i]==-1)
		{
			cbox[i]='X';
		}
	}
	printf(" %c | %c | %c\n------------\n %c | %c | %c\n------------\n %c | %c | %c\n",cbox[0],cbox[1],cbox[2],cbox[3],cbox[4],cbox[5],cbox[6],cbox[7],cbox[8]);
}
