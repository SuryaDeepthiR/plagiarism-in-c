#ifndef LCS_H_INCLUDED
#define LCS_H_INCLUDED
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
void lcs(char charset1[],char charset2[],int x,int y) //to get the longest common substring
{
	int count=0,c=0;
	int trash;
	for(int i=0;i<strlen(charset1);i++)
	{
		int j=0;
		while(j<strlen(charset2))
		{
			trash=i;
			c=0;
			if(charset1[trash]==charset2[j])
			{
				while((charset1[trash]==charset2[j])&&j<strlen(charset2)&&trash<strlen(charset1))
				{
					c++;
					j++;
					trash++;
				}
				if(c>count)
				{

					count=c;
				}
			}
			else
			{
				j++;
			}
		}
	}
	float percent=(float)(count*200)/(x+y);
	printf("%.2f        ",percent);

}// end of lcs

void charset(char *char1,char *char2,int length1,int length2) //to get the words of longest common substring
{
	char charset1[length1];
	char charset2[length2];
	int x=0,y=0;

	for(int i=0;i<length1;i++)
	{
		if((isalnum(char1[i]))|| (char1[i]=='_') || (char1[i]==' '))
		{
			if(isupper(char1[i]))
			{
				tolower(char1[i]);
				charset1[x]=char1[i];
				x++;
			}
			else
			{
				charset1[x]=char1[i];
				x++;
			}
		}
	}
	for(int i=0;i<length2;i++)
	{
		if((isalnum(char2[i]))|| (char2[i]=='_') || (char2[i]==' '))
		{
			if(isupper(char2[i]))
			{
				tolower(char2[i]);
				charset2[y]=char2[i];
				y++;
			}
			else
			{
				charset2[y]=char2[i];
				y++;
			}
		}
	}
	lcs(charset1,charset2,x,y);
}//end of charset

#endif
