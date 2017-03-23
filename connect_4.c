#include <stdio.h>
#include <stdlib.h>
int* minimax(int* [], int, int, int, int, int);
int heuristic(int* []);
int game_over(int* []);
void game_print(int* []);
int main()
{
	int **box = (int **) malloc (6*(sizeof(int *))),i,j,n=42,col,move;
	int * value;
	value = (int *) malloc (3*sizeof(int));
	for(i=0;i<6;i++)
	{
		*(box+i)=(int *) malloc(7*(sizeof(int)));
	}
	for(i=0;i<6;i++)
	{
		for(j=0;j<7;j++)
		{
			*(*(box+i)+j)=0;
		}
	}
	char turn;
	printf("You are Mr.R(Red), Computer is Mr.Y(Yellow)\nSpecify if you want to go first or not? Y/N\n");
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
	while(n>0)
	{
		if(game_over(box)==1||game_over(box)==-1)
		{
			break;
		}		
		if(move==1)
		{
			value = minimax(box,n,1,0,-1000,1000);
			*(*(box+(value[1]))+(value[2]))=1;
			move=-1;
			printf("After Computer's move:\n");
		}
		else if(move==-1)
		{
			while(1)
			{
				printf("Specify Column\n");				
				scanf("%d",&col);
				if( col>6 )
				{
					printf("Out of Range\n");
					continue;
				}
				for(i=0;i<6;i++)
				{
					if((*(*(box+i)+col))==0)
					{
						(*(*(box+i)+col))=-1;
						break;
					}
					if(i==5)
					{
						printf("Whole column filled\n");
					}
				}
				if(i!=6)
				{
					break;
				}				
			}
			move=1;			
			printf("After your move :\n");
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
int* minimax(int* box[], int n, int flag, int count, int alpha, int beta)
{
	int *value,i,j,index1,index2;
	value = (int *) malloc (3*sizeof(int));	
	if(game_over(box)==1)
	{
		value[0]=100;
		value[1]=0;
		value[2]=0;
		return value;
	}
	else if(game_over(box)==-1)
	{
		value[0]=-100;
		value[1]=0;
		value[2]=0;
		return value;
	}
	else if(n==0)
	{
		value[0]=0;
		value[1]=0;
		value[2]=0;
		return value;
	}
	else if(count==7)
	{
		value[0]=heuristic(box);
		value[1]=0;
		value[2]=0;
		count = 0;
		return value;
	}			
	if(flag==1)	
	{
		int max=-1000;		
		for(i=0;i<6;i++)
		{
			for(j=0;j<7;j++)
			{
				if((i==0||((*(*(box+(i-1))+j))!=0))&&(*(*(box+i)+j))==0)
				{
					*(*(box+i)+j)=1;
					count++;
					value = minimax(box,n-1,0,count,alpha,beta);
					*(*(box+i)+j)=0;
					count--;
					if(value[0]>max)
					{
						max=value[0];						
						index1=i;
						index2=j;
					}
				}		
			}
		}	
		value[0]=max;
		value[1]=index1;
		value[2]=index2;
		return value;
	}
	else if(flag==0)
	{
		int min=1000;		
		for(i=0;i<6;i++)
		{
			for(j=0;j<7;j++)
			{
				if((i==0||((*(*(box+(i-1))+j))!=0))&&(*(*(box+i)+j))==0)
				{
					*(*(box+i)+j)=-1;
					count++;
					value = minimax(box,n-1,1,count,alpha,beta);
					*(*(box+i)+j)=0;
					count--;
					if(value[0]<min)
					{
						min=value[0];						
						index1=i;
						index2=j;
					}
				}		
			}
		}	
		value[0]=min;
		value[1]=index1;
		value[2]=index2;
		return value;
	}
}
int heuristic(int * box[])
{
	int i,j,count1=0,counta=0,countb=0,countc=0,heuristic_value;
	for(i=0;i<6;i++)
	{
		for(j=0;j<7;j++)
		{
			int k=i,l=j;
			if((*(*(box+i)+j))==0)
			{
				continue;
			}
			else if((*(*(box+i)+j))>0)
			{
				while((j<7)&&(*(*(box+i)+j)>0))
				{
					count1++;
					j++;
				}
				if((count1==2)&&(((j<7)&&((*(*(box+i)+j))==0))||((k!=0)&&((*(*(box+(k-1))+j))==0))))
				{
					counta++;
				}
				if((count1==3)&&(((j<7)&&((*(*(box+i)+j))==0))||((k!=0)&&((*(*(box+(k-1))+j))==0))))
				{
					countb++;
				}
				if((count1==1)&&(((j<7)&&((*(*(box+i)+j))==0))||((k!=0)&&((*(*(box+(k-1))+j))==0))))
				{
					countc++;
				}
				count1=0;
				j=l;
				while((i<6)&&(*(*(box+i)+j)>0))
				{
					count1++;
					i++;
				}
				if((count1==2)&&(((i<6)&&((*(*(box+i)+j))==0))||((k!=0)&&((*(*(box+(k-1))+j))==0))))
				{
					counta++;
				}
				if((count1==3)&&(((i<6)&&((*(*(box+i)+j))==0))||((k!=0)&&((*(*(box+(k-1))+j))==0))))
				{
					countb++;
				}
				if((count1==1)&&(((i<6)&&((*(*(box+i)+j))==0))||((k!=0)&&((*(*(box+(k-1))+j))==0))))
				{
					countc++;
				}
				count1=0;
				i=k;
				while((i<6)&&(j<7)&&(*(*(box+i)+j)>0))
				{
					count1++;
					i++;
					j++;
				}
				if((count1==2)&&(((i<6)&&(j<7)&&((*(*(box+i)+j))==0))||((k!=0)&&(l!=0)&&((*(*(box+(k-1))+(l-1)))==0))))
				{
					counta++;
				}
				if((count1==3)&&(((i<6)&&(j<7)&&((*(*(box+i)+j))==0))||((k!=0)&&(l!=0)&&((*(*(box+(k-1))+(l-1)))==0))))
				{
					countb++;
				}
				if((count1==1)&&(((i<6)&&(j<7)&&((*(*(box+i)+j))==0))||((k!=0)&&(l!=0)&&((*(*(box+(k-1))+(l-1)))==0))))
				{
					countc++;
				}
				count1=0;
				i=k;
				j=l;
				while((i<6)&&(j>=0)&&(*(*(box+i)+j)>0))
				{
					count1++;
					i++;
					j--;
				}
				if((count1==2)&&(((j>=0)&&(i<6)&&((*(*(box+i)+j))==0))||((k!=0)&&(l!=6)&&((*(*(box+(k-1))+(l+1)))==0))))
				{
					counta++;
				}
				if((count1==3)&&(((j>=0)&&(i<6)&&((*(*(box+i)+j))==0))||((k!=0)&&(l!=6)&&((*(*(box+(k-1))+(l+1)))==0))))
				{
					countb++;
				}
				if((count1==1)&&(((j>=0)&&(i<6)&&((*(*(box+i)+j))==0))||((k!=0)&&(l!=6)&&((*(*(box+(k-1))+(l+1)))==0))))
				{
					countc++;
				}
				count1=0;
				i=k;
				j=l;
			}
			else if((*(*(box+i)+j))<0)
			{	
				while((j<7)&&(*(*(box+i)+j)<0))
				{
					count1++;
					j++;
				}
				if((count1==2)&&(((j<7)&&((*(*(box+i)+j))==0))||((k!=0)&&((*(*(box+(k-1))+j))==0))))
				{
					counta--;
				}
				if((count1==3)&&(((j<7)&&((*(*(box+i)+j))==0))||((k!=0)&&((*(*(box+(k-1))+j))==0))))
				{
					countb--;
				}
				if((count1==1)&&(((j<7)&&((*(*(box+i)+j))==0))||((k!=0)&&((*(*(box+(k-1))+j))==0))))
				{
					countc--;
				}
				count1=0;
				j=l;
				while((i<6)&&(*(*(box+i)+j)<0))
				{
					count1++;
					i++;
				}
				if((count1==2)&&(((i<6)&&((*(*(box+i)+j))==0))||((k!=0)&&((*(*(box+(k-1))+j))==0))))
				{
					counta--;
				}
				if((count1==3)&&(((i<6)&&((*(*(box+i)+j))==0))||((k!=0)&&((*(*(box+(k-1))+j))==0))))
				{
					countb--;
				}
				if((count1==1)&&(((i<6)&&((*(*(box+i)+j))==0))||((k!=0)&&((*(*(box+(k-1))+j))==0))))
				{
					countc--;
				}
				count1=0;
				i=k;
				while((i<6)&&(j<7)&&(*(*(box+i)+j)<0))
				{
					count1++;
					i++;
					j++;
				}
				if((count1==2)&&(((i<6)&&(j<7)&&((*(*(box+i)+j))==0))||((k!=0)&&(l!=0)&&((*(*(box+(k-1))+(l-1)))==0))))
				{
					counta--;
				}
				if((count1==3)&&(((i<6)&&(j<7)&&((*(*(box+i)+j))==0))||((k!=0)&&(l!=0)&&((*(*(box+(k-1))+(l-1)))==0))))
				{
					countb--;
				}
				if((count1==1)&&(((i<6)&&(j<7)&&((*(*(box+i)+j))==0))||((k!=0)&&(l!=0)&&((*(*(box+(k-1))+(l-1)))==0))))
				{
					countc--;
				}
				count1=0;
				i=k;
				j=l;
				while((i<6)&&(j>=0)&&(*(*(box+i)+j)<0))
				{
					count1++;
					i++;
					j--;
				}
				if((count1==2)&&(((j>=0)&&(i<6)&&((*(*(box+i)+j))==0))||((k!=0)&&(l!=6)&&((*(*(box+(k-1))+(l+1)))==0))))
				{
					counta--;
				}
				if((count1==3)&&(((j>=0)&&(i<6)&&((*(*(box+i)+j))==0))||((k!=0)&&(l!=6)&&((*(*(box+(k-1))+(l+1)))==0))))
				{
					countb--;
				}
				if((count1==1)&&(((j>=0)&&(i<6)&&((*(*(box+i)+j))==0))||((k!=0)&&(l!=6)&&((*(*(box+(k-1))+(l+1)))==0))))
				{
					countc--;
				}
				count1=0;
				i=k;
				j=l;
			}
		}
	}
	heuristic_value=1*countc+5*counta+15*countb;
	return heuristic_value;
}
int game_over(int * box[])
{
	int i,j,count1=0;
	for(i=0;i<6;i++)
	{
		for(j=0;j<7;j++)
		{
			int k=i,l=j;
			if((*(*(box+i)+j))==0)
			{
				continue;
			}
			else if((*(*(box+i)+j))>0)
			{
				while((j<7)&&(*(*(box+i)+j)>0))
				{
					count1++;
					j++;
				}
				if(count1==4)
				{
					return 1;
				}
				count1=0;
				j=l;
				while((i<6)&&(*(*(box+i)+j)>0))
				{
					count1++;
					i++;
				}
				if(count1==4)
				{
					return 1;
				}
				count1=0;
				i=k;
				while((i<6)&&(j<7)&&(*(*(box+i)+j)>0))
				{
					count1++;
					i++;
					j++;
				}
				if(count1==4)
				{
					return 1;
				}
				count1=0;
				i=k;
				j=l;
				while((i<6)&&(j>=0)&&(*(*(box+i)+j)>0))
				{
					count1++;
					i++;
					j--;
				}
				if(count1==4)
				{
					return 1;
				}
				count1=0;
				i=k;
				j=l;
			}
			else if((*(*(box+i)+j))<0)
			{	
				while((j<7)&&(*(*(box+i)+j)<0))
				{
					count1++;
					j++;
				}
				if(count1==4)
				{
					return -1;
				}
				count1=0;
				j=l;
				while((i<6)&&(*(*(box+i)+j)<0))
				{
					count1++;
					i++;
				}
				if(count1==4)
				{
					return -1;
				}
				count1=0;
				i=k;
				while((i<6)&&(j<7)&&(*(*(box+i)+j)<0))
				{
					count1++;
					i++;
					j++;
				}
				if(count1==4)
				{
					return -1;
				}
				count1=0;
				i=k;
				j=l;
				while((i<6)&&(j>=0)&&(*(*(box+i)+j)<0))
				{
					count1++;
					i++;
					j--;
				}
				if(count1==4)
				{
					return -1;
				}
				count1=0;
				i=k;
				j=l;
			}
		}
	}
	return 0;
}
void game_print(int * box[])
{
	printf("---------------------\n");
	for(int i=5;i>=0;i--)
	{
		for(int j=0;j<7;j++)
		{
			if((*(*(box+i)+j))==0)
			{
				printf(" . ");
			}
			else if((*(*(box+i)+j))==1)
			{
				printf(" Y ");
			}
			else if((*(*(box+i)+j))==-1)
			{
				printf(" R ");
			}
		}
		printf("\n---------------------\n");
	}
}


