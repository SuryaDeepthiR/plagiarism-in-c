#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <dirent.h>
#include <ctype.h>
#include "percent.h"

float denom(int freq1[],int freq2[],int c1,int c2) //to get denominator
{
  float temp1=0,temp2=0;
  for(int i=0;i<c1;i++)
  {
    temp1+=freq1[i]*freq1[i];
  }
  temp1=sqrt(temp1);
  for(int i=0;i<c2;i++)
  {
    temp2+=freq2[i]*freq2[i];
  }
  temp2=sqrt(temp2);
  float x=(temp1*temp2);
  return x;
}//end of denominator

int num(char *w1[],char *w2[],int freq1[],int freq2[],int c1,int c2) //to get numerator
{
  int temp=0;
  for(int i=0;i<c1;i++)
  {
    for(int j=0;j<c2;j++)
    {
      if((strcmp(w1[i],w2[j]))==0)
      {
        temp=temp+(freq1[i]*freq2[j]);
      }
    }
  }
  return temp;
}//end of numerator

void BagOfWords(char *w1[],char *w2[],int freq1[],int freq2[],int c1,int c2) //to calculate bag of words
{
  int n=num(w1,w2,freq1,freq2,c1,c2);
  float d=denom(freq1,freq2,c1,c2);
  float bow = n/d;
  float percentage= percent(bow);
  printf("  %.2f     ",percentage);
}// end of BagOfWords

void frequency(char split1[1000][1000],char split2[1000][1000],int p1,int p2) //to calculate frequency of each word
{
  char *w1[p1],*w2[p2];
  for(int i=0;i<=p1;i++)
  {
    w1[i]=malloc(128);
  }
  for(int i=0;i<=p2;i++)
  {
    w2[i]=malloc(128);
  }
  int c1=0;
  for(int i=0;i<=p1;i++)
  {
    int count=0;
    for(int j=0;j<=p1;j++)
    {
      if((strcmp(split1[i],w1[j]))==0)
      {
        count++;
      }
    }
    if(count==0)
    {
      strcpy(w1[i],split1[i]);
      c1++;
    }
  }
  int c2=0;
  for(int i=0;i<=p2;i++)
  {
    int count=0;
    for(int j=0;j<=p2;j++)
    {
      if((strcmp(split2[i],w2[j]))==0)
      {
        count++;
      }
    }
    if(count==0)
    {
      strcpy(w2[i],split2[i]);
      c2++;
    }
  }
  int freq1[c1],freq2[c2];
  for(int i=0;i<c1;i++)
  {
    int count=0;
    for(int j=0;j<=p1;j++)
    {
      if((strcmp(w1[i],split1[j]))==0)
      {
        count++;
      }
    }
    freq1[i]=count;
  }
  for(int i=0;i<c2;i++)
  {
    int count=0;
    for(int j=0;j<=p2;j++)
    {
      if((strcmp(w2[i],split2[j]))==0)
      {
        count++;
      }
    }
    freq2[i]=count;
  }
  BagOfWords(w1,w2,freq1,freq2,c1,c2);
}// end of frequency

void words(char d1[10000], char d2[10000],int l1, int l2) //to split into words and get into an array
{
    char split1[1000][1000];
    char split2[1000][1000];
    int p1=0,q1=0,p2=0,q2=0;
    for(int i=0;i<l1;i++)
    {
      if(isalnum(d1[i]))
      {
        split1[p1][q1]=d1[i];
        q1++;
      }
      else
      {
        split1[p1][q1]='\0';
        p1++;
        q1=0;
      }
    }
    for(int i=0;i<l2;i++)
    {
      if(isalnum(d2[i]))
      {
        split2[p2][q2]=d2[i];
        q2++;
      }
      else
      {
        split2[p2][q2]='\0';
        p2++;
        q2=0;
      }
    }
    frequency(split1,split2,p1,p2);
}// end of words

void removes(char a[],char b[],int size1,int size2)//to remove delimiters
{
    char d1[10000],d2[10000];
    int l1=0,l2=0;
    for(int i=0;i<size1;i++)
    {
        if((isalnum(a[i]))|| a[i]==' ' || a[i]=='_')
        {
            d1[l1]=a[i];
            l1++;
        }
    }
    for(int i=0;i<size2;i++)
    {
        if((isalnum(b[i]))|| b[i]==' ' || b[i]=='_')
        {
            d2[l2]=b[i];
            l2++;
        }
    }
    words(d1,d2,l1,l2);
}//end of delimiters

int main(int argc, char *argv[])
{
 char *dirfile[10];
  int i=0;
  DIR *d;
  struct dirent *dir;
 // char dirpath[1000];
//  scanf("%[^\n]",dirpath);
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
   return 0;
}//end of main
