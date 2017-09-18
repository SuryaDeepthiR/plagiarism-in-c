#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <dirent.h>
#include <ctype.h>
#include "temp.h"
void main(int argc, char *argv[])
{
 char *dirfile[10];
  int i=0;
  DIR *d;
  struct dirent *dir;
  char dirpath[1000];
  // scanf("%[^\n]",dirpath);
  // d=opendir(dirpath);
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

    for(i = 0;i < 4;i++)
    {
      char arr1[10000];
      char a;
      int size1=0;
      FILE *myfile = fopen(dirfile[i], "r");
      a=fgetc(myfile);
      printf("\n%s",dirfile[i]);
      while(a!=EOF)
      {
        if(a=='\n')
        {
          arr1[size1]=' ';
          size1++;
        }
        else
        {
          arr1[size1]=a;
          size1++;
        }
        a=fgetc(myfile);
      }
      strlwr(arr1);
      fclose(myfile);
      for (int j = 0;j < 4;j++)
      {

        char arr2[10000];
        char b;
        int size2=0;
        FILE *myfile = fopen(dirfile[j], "r");
        b=fgetc(myfile);
        while(b!=EOF)
        {
          if(b=='\n')
          {
            arr2[size2]=' ';
            size2++;
          }
          else
          {
            arr2[size2]=b;
            size2++;
          }
          b=fgetc(myfile);
        }
        strlwr(arr2);
        fclose(myfile);
        if((strcmp(dirfile[i],dirfile[j]))==0)
        {
            printf("  NONE      ");
        }
        else
        {
          removes(arr1,arr2,size1,size2);
        }
      }
   }
}//end of main
