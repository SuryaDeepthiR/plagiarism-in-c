#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "longestcString.h"
int main(int argc, char * argv[])
{
	char *dirfile[10]; //to open the directory
	int i=0;
	DIR *d;
	struct dirent *dir;
	// char dirpath[1000];
	// scanf("%[^\n]",dirpath);
	d=opendir(argv[1]);
	chdir(argv[1]);
	while( (dir=readdir(d)) != NULL)
	{
		dirfile[i]= malloc(128);
		int l=strlen(dir->d_name);
		if(dir->d_name[l-1]=='t'&&dir->d_name[l-2]=='x'&&dir->d_name[l-3]=='t')
		{
			strcpy(dirfile[i],dir->d_name);
			i=i+1;
		}
	}
	int x=i;
	printf("\t");
	for(int i=0;i < x;i++)
	{
		printf("%s      ",dirfile[i]);
	}
	for(int i=0;i<4;i++)
	{	
		FILE *fileopen = fopen(dirfile[i], "r");
		char a;
		char char1[10000];
		int length1=0;
		a=fgetc(fileopen);
		while(a!=EOF)
		{
			if(a=='\n')
			{
				char1[length1]=' ';
				length1++;
			}
			else
			{
				char1[length1]=a;
				length1++;
			}
			a=fgetc(fileopen);
		}
		fclose(fileopen);
		printf("\n");
		printf("%s ",dirfile[i]);
		for(int j=0;j < 4;j++)
    	{
    	    FILE *fileopen= fopen(dirfile[j],"r");
    	    char b;
			char char2[10000];
			int length2=0;
			b=fgetc(fileopen);
			while(b!=EOF)
			{
				if(b=='\n')
				{
					char2[length2]=' ';
					length2++;
				}
				else
				{
					char2[length2]=b;
					length2++;
				}
				b=fgetc(fileopen);
			}
    	    fclose(fileopen);
    	    if((strcmp(dirfile[i],dirfile[j]))==0)
    	    {
    	    	printf("NONE         ");
    	    }
    	    else
    	    {
    	    	charset(char1,char2,length1,length2);	//to get words of a longest common substring
    	    }
    	    
    	}
	}
}//end of main