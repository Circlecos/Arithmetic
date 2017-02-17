#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <iomanip>
#include "operation.h"
#include "fraction.h"
#include<string>
#include<string.h>
#include<math.h>
using namespace std;
int main()
{
	srand(static_cast<unsigned> (time(NULL)));
	int prompt;
	cout<<"��ѡ����ʾ���ԣ�����1Ϊ���ģ�����2ΪӢ�ġ�"<<endl;
	cout<<"Please select the prompt language��click ��1��means you need Chinese prompt language,whlie ��2��means english."<<endl;
	cin>>prompt;
	int n;

	if(prompt==1)
	{
		cout<<"������Ŀ����:";
		cin >> n;
		cout<<"�������ʱ��e��ֹ���⣬��ǰ��Ŀ������ɼ�"<<endl;
	}
	else if(prompt==2)
	{
		cout<<"Enter the number of topics:"<<endl;
		cin >> n;
		cout<<"You can press e to stop answering at any time,while the question you are answering will no judged."<<endl;
	}
	else {cout << "Error: The input is wrong"<<endl; return 1;}
	int corrnum=0;
	int wrongnum=0;

	int num=0;
	int len;
	int x;
	int i;
	int j;
	char ans[100];
	int intans[100];
	int judge=0;
	int wrongquenum[100];
	Operation *a[1000];
	for(i=0;i<1000;i++)
	{
		a[i]=NULL;
	}
	for(x=0;x<n;x++)
	{
		a[x]=new Operation();
		cout<<x+1<<". ";
		(a[x])->print();
		cout<<" = ";
		cin>>ans;
		len=strlen(ans);
		judge = 0;
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
		judge=0;
		if (ans[0]=='-') judge=1;
		for(i=0;i<len;i++)
			{ 
				if ((judge==1)&&(i==0)) continue;
				num+=(static_cast<int>(pow(10,len-i-1)*(ans[i]-48)));
			}
		if (judge==1) intans[x]=0-num;
		else intans[x]=num;
		Fraction *p;
		p=new Fraction(intans[x],1); 
		if((a[x]->getans())==*p)
		{
			corrnum++;
		}
		else
		{
			wrongquenum[wrongnum]=x;
			wrongnum++;
		}
		delete p;
	}

	cout << "-----------------------------------"<<endl;

	if (prompt == 1)
	{
		cout << "�ܼ�:" << n << setw(12) << "��ȷ����:" << corrnum << setw(12) << "��������:" << wrongnum << endl;
	}
	else if (prompt == 2)
	{
		cout << "Total:" << n << setw(12)<< "True:" << corrnum <<setw(12)<< "False:" << wrongnum << endl;
	}

	cout << "-----------------------------------" << endl;

	if(wrongnum>0)
	{
		if(prompt==1)
		cout<<"�������飺"<<endl;
		else if(prompt==2)
		cout<<"Mistake��"<<endl;
		for(i=0;i<wrongnum;i++)
		{
			j=wrongquenum[i];
			cout << endl;
			if(prompt==1)
			{
				cout<<j+1<<". ";
				(a[j])->print();
				cout<<" = ";
				((a[j])->getans()).print();
				cout<<endl;
				cout<<"  ��Ĵ�:"<<intans[j]<<endl;
			}
			else if(prompt==2)
			{
				cout<<j+1<<". ";
				(a[j])->print();
				cout<<" = ";
				((a[j])->getans()).print();
				cout<<endl;
				cout<<"  Your answer is "<<intans[j]<<endl;
			}
		}
	}

	for (i = 0; i<1000; i++)
	{
		delete(a[i]);
	}
}
