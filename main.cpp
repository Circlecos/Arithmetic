#include <iostream>
#include <iomanip>
#include<string>
#include <stdlib.h>
#include <time.h>
#include<math.h>
#include<Windows.h>
#include "operation.h"
#include "fraction.h"

#define MAX_NUM_OF_PROBLEM 1000

using namespace System;
using namespace System::Resources;
using namespace System::Collections;
using namespace System::Globalization;
using namespace System::Reflection;
using namespace std;

int main()
{
	//�������������
	srand(static_cast<unsigned> (time(NULL)));

	//��ȡ��Դ�ļ�
	Assembly^ CurrentAssem = Assembly::GetExecutingAssembly();
	ResourceManager RcLang("LangList", CurrentAssem);
	CultureInfo^ DefaultLoca = gcnew CultureInfo("", false);
	ResourceSet^ RcLangInfo = RcLang.GetResourceSet(DefaultLoca, true, true);


	//����IO����UnicodeEncoding
	Console::OutputEncoding = gcnew System::Text::UnicodeEncoding;
	Console::InputEncoding = Console::OutputEncoding;
	
	//�������ʹ�õ�����
	int NumLang = 0;
	IDictionaryEnumerator^ idlanginfo = RcLangInfo->GetEnumerator();
	while (idlanginfo->MoveNext())
	{
		NumLang++;
		Console::WriteLine("{0}:{1,-7}", NumLang, (idlanginfo->Key)->ToString()->Normalize());
	}

	//�����û�ѡ������ԺͶ�Ӧ��resource
	Console::Write("Please enter the prompt language by its name:");
	String^ str;
	int isLang = 0;
	while (str = Console::ReadLine())
	{
		idlanginfo->Reset();
		while (idlanginfo->MoveNext())
		{
			if ((idlanginfo->Key->ToString()->Equals(str)))//�ж��û�����������Ƿ�������
				isLang=1;
		}
		if (isLang == 1) break;
		else if (isLang == 0)
		{
			Console::WriteLine("The input is error!");
			Console::Write("Please enter the prompt language by its name:");
		}
	}

	//�����û���Ӧ��resource
	ResourceManager rc("Resource", CurrentAssem);
	CultureInfo^ loca = gcnew CultureInfo(RcLang.GetString(str), false);

	//���뽫���ɵ���������
	int NumProblem;
	Console::Write("{0}", rc.GetString("InputNumberOfProblems", loca));
	std::cin>>NumProblem;

	//�������������˵��
	Console::WriteLine("{0}\n", rc.GetString("InputNote", loca)); 
	
	// ���ɲ������Ŀ
	int CorrNum = 0, WrongNum = 0;
	int i,j;//ѭ������
	char ans[MAX_NUM_OF_PROBLEM];//�û��𰸣��ַ�����
	int len;//�û��𰸳���
	int intans[MAX_NUM_OF_PROBLEM];//�û��𰸣���ֵ��
	int judge = 0;//�ж��û������Ƿ���e
	int num = 0;//ת���û���
	int WrongQueNum[MAX_NUM_OF_PROBLEM];//�ش�������Ŀ�ı��
	Operation *Problem[MAX_NUM_OF_PROBLEM];//ָ����Ŀ��ָ��
	for (i = 0; i < MAX_NUM_OF_PROBLEM; i++)
		Problem[i] = NULL;
	//��� �����.��Ŀ=���������û���
	for (j = 0; j<NumProblem; j++)
	{
		Problem[j] = new Operation();

		String^ ProblemCodeStr = ((j+1).ToString());
		ProblemCodeStr = System::String::Concat(ProblemCodeStr, ".");
		Console::Write("{0,-5}", ProblemCodeStr);
		(Problem[j])->print();
		Console::Write(" = ");
		cin >> ans;
		len = strlen(ans);
		judge = 0;
		for (i = 0; i<len; i++)
		{
			if (ans[i] == 'e')
			{
				judge = 1;//judge=1 means it contains 'e'
			}
			if (judge == 1)
				break;
		}
		if (judge == 1)
			break;
		
		num = 0;
		judge = 0;
		if (ans[0] == '-') judge = 1;
		for (i = 0; i<len; i++)
		{
			if ((judge == 1) && (i == 0)) continue;
			num += (static_cast<int>(pow(10, len - i - 1)*(ans[i] - 48)));
		}
		if (judge == 1) intans[j] = 0 - num;
		else intans[j] = num;
		Fraction *p;//ָ�� ���� ��ָ��
		p = new Fraction(intans[j], 1);
		if ((Problem[j]->getans()) == *p)
		{
			CorrNum++;
		}
		else
		{
			WrongQueNum[WrongNum] = j;
			WrongNum++;
		}
		delete p;
	}

	cout << "-----------------------------------" << endl;

	//�������
	Console::WriteLine("{0}{1,-12}{2}{3,-12}{4}{5,-12}", rc.GetString("Total", loca), CorrNum+WrongNum,
		rc.GetString("CorrectNum", loca),CorrNum,rc.GetString("WrongNum", loca), WrongNum);
	int WrongCode;//������Ŀ���
	if (WrongNum > 0)
	{
		Console::WriteLine("{0}", rc.GetString("DetailMistake", loca));
		for (i = 0; i < WrongNum; i++)
		{
			Console::WriteLine();
			WrongCode = WrongQueNum[i];
			String^ WrongCodeStr=((WrongCode+1).ToString());
			WrongCodeStr=System::String::Concat(WrongCodeStr, ".");
			Console::Write("{0,-5}", WrongCodeStr);
			(Problem[WrongCode])->print();
			Console::Write(" = ");
			((Problem[WrongCode])->getans()).print();
			Console::WriteLine();
			Console::Write("     {0}", rc.GetString("YourAnswer", loca));
			Console::Write("{0}\n",intans[WrongCode]);
		}
	}
	Console::WriteLine();

	//��������ǰ����	
	for (i = 0; i<MAX_NUM_OF_PROBLEM; i++)
	{
		delete(Problem[i]);
	}
	return 0;
}
