#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

long long denominator(long long hashmod1[],long long hashmod2[],int l1,int l2) //to sum up all the hashmod values
{
	long long y=0;
	for(int i=0;i<l1;i++)
	{
		y+=hashmod1[i];
	}
	for(int i=0;i<l2;i++)
	{
		y+=hashmod2[i];
	}
	return y;
}
void fp(long long hashmod1[],long long hashmod2[],int l1,int l2)//calculate percentage 
{
	float x=0;
	for(int i=0;i<l1;i++)
	{
		for(int j=0;j<l2;j++)
		{
			if(hashmod1[i]==hashmod2[j])
			{
				x=x+hashmod1[i];
			}
		}
	}
	float y=denominator(hashmod1,hashmod2,l1,l2);
	float percent= ((x*200)/y);
	printf("   %.2f      ",percent);
}
void hmodk(long long h1[],long long h2[],int l1,int l2,long long maxh1,long long maxh2) // to find the mod value of every hash value
{
	long long hashmod1[1000];
	long long x=0;
	for(int i=0;i<l1;i++)
	{
		x=(h1[i]%maxh1);
		hashmod1[i]=x;
	}
	long long hashmod2[1000];
	x=0;
	for(int j=0;j<l2;j++)
	{
		x=(h2[j]%maxh2);
		hashmod2[j]=x;
	} 
	fp(hashmod1,hashmod2,l1,l2);
}
long long prime(long long x)// to check whether the maximum value is prime or not
{
	int count=0;
	for(long long i=2;i<x;i++)
	{
		if(x%i==0)
		{
			count++;
		}
	}
	if(count==0)
	{
		return x;
	}
	else
	{
		count=5;
		while(count!=0)
		{
			count=0;
			x++;
			for(long long i=2;i<x;i++)
			{
				if(x%i==0)
				{
					count++;
				}
			}
			if(count==0)
			{
				return x;
			}
		}
	}
}
void maximum(long long h1[],long long h2[],int l1,int l2) //to find the maximum hash value
{
	long long maxh1=h1[0];
	for(int i=0;i<l1;i++)
	{
		if(h1[i]>maxh1)
		{
			maxh1=h1[i];
		}
	}
	long long maxh2=h2[0];
	for(int i=0;i<l2;i++)
	{
		if(h2[i]>maxh2)
		{
			maxh2=h2[i];
		}
	}
	maxh1=prime(maxh1);
	maxh2=prime(maxh2);
	hmodk(h1,h2,l1,l2,maxh1,maxh2);
}
void hashvalues(char wordset1[],char wordset2[],int x,int y) //to calculate hash values of each word
{
	long long h1[1000];
	int l1=0;
	long long value=0;
	for(int i=0;i<x-4;i++)
	{
		int z=4;
		for(int j=i;j<i+5;j++)
		{
			value+=(wordset1[j]*pow(10,z));
			z--;
		}
		h1[i]=value;
		l1++;
	}
	long long h2[1000];
	int l2=0;
	value=0;
	for(int i=0;i<y-4;i++)
	{
		int z=4;
		for(int j=i;j<i+5;j++)
		{
			value+=(wordset2[j]*pow(10,z));
			z--;
		}
		h2[i]=value;
		l2++;
	}
	maximum(h1,h2,l1,l2);

}
void removes(char word1[],char word2[],int l1,int l2) //to remove delimiters
{
	char wordset1[10000];
	char wordset2[10000];
	int x=0;
	int y=0;
	for(int i=0;i<l1;i++)
	{
		if(isalnum(word1[i]))
		{
			wordset1[x]=word1[i];
			x++;
		}
	}
	for(int i=0;i<l2;i++)
	{
		if(isalnum(word2[i]))
		{
			wordset2[y]=word2[i];
			y++;
		}
	}
	hashvalues(wordset1,wordset2,x,y);
}//end of removes function
