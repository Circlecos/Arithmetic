#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <iomanip>
#include "operation.h"
#include "fraction.h"
#include<string>
#include<string.h>
#include "prompt.h"
using namespace std;
int main()
{
	int corrnum=0;
	int wrongnum=0
	int n;
	cin>>n;
	setpro(int prompt);
	selectpro();//ѡ�����Խ��� 
	string wrongquestion[100];
	string question[100];
	int num=0;
	int x;
	int i;
	int len;
	char ans[100];
	int intans[100];
	int wrongque[100];
	int wrongans[100];
	int rightans[100];
	int judge=0;
	for(x=0;x<n;x++)
	{
		string question[x]=print();
		rightans[x]=Operation::getans();
		cout<<print()
		cin>>ans;
		len=strlen(ans);
		for(i=0;i<len;i++)
		{
			if(ans[i]=='e')
			{
				judge=1;//judge=1 means it contains 'e'
			}
			if(judge==1)
			break;
		}
		if(judge==1)
		break; 
		num=0;
		for(i=0;i<len;i++)
			{
				num+=pow(10,len-i-1)*(ans[i]-48);
			}
		intans[x]=num;	
		if(intans[x]==rightans[x])
		{
			corrnum++;
		}
		else if(intans[x]!=rightans[x])
		{
			wrongque[wrongnum]=x+1;
			wrongquestion[wrongnum]=question[x];
			wrongans[wrongnum]=intans[x];
			wrongnum++;	
		}	
	 } 
	
		for(i=0;i<len;i++)
			{
				ans[i]='\0';
			}

	}		
	for(i=0;i<wrongnum;i++)
		{
			if(prompt==1)
			{
				cout<<"��"<<wrongque[i]+1<<"�����"<<endl;
				cout<<"��Ĵ�:"<<wrongquestion[i]<<wrongans[i]<<endl;
				cout<< "��ȷ��Ϊ"<<rightans[wrongque[i]-1]<<endl; 
			}
			else if(prompt==2) 
			{
				cout<<"The answer of question"<<wrongque[i]+1<<"is wrong"<<endl;
				cout<<"Your answer is:"<<wrongans[i]<<endl;
				cout<< "The right answer is:"<<rightans[wrongque[i]-1]<<endl; 
			}
		}
	 if(prompt==1)
	{
		cout<<"�ܼ�:"<<n+1<<endl;
		cout<<"��ȷ����:"<<corrnum<<endl;
		cout<<"��������:"<<wrongnum<<endl;
	}
	else if(prompt==2) 
	{
		cout<<"Total:"<<n+1<<endl;
		cout<<"True:"<<corrnum<<endl;
		cout<<"False:"<<wrongnum<<endl;
	}
}
