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
	//重置随机数种子
	srand(static_cast<unsigned> (time(NULL)));

	//读取资源文件
	Assembly^ CurrentAssem = Assembly::GetExecutingAssembly();
	ResourceManager RcLang("LangList", CurrentAssem);
	CultureInfo^ DefaultLoca = gcnew CultureInfo("", false);
	ResourceSet^ RcLangInfo = RcLang.GetResourceSet(DefaultLoca, true, true);

	
	//输出可以使用的语言
	int NumLang = 0;
	IDictionaryEnumerator^ idlanginfo = RcLangInfo->GetEnumerator();
	while (idlanginfo->MoveNext())
	{
		NumLang++;
		Console::OutputEncoding=gcnew System::Text::UnicodeEncoding;
		Console::InputEncoding = Console::OutputEncoding;
		Console::WriteLine("{0}:{1,-7}", NumLang, (idlanginfo->Key)->ToString()->Normalize());
	}

	std::cout << "Please enter the prompt language by its name:";
	
	//读入用户选择的语言和对应的resource
	String^ str = Console::ReadLine();
	ResourceManager rc("Resource", CurrentAssem);
	CultureInfo^ loca = gcnew CultureInfo(RcLang.GetString(str), false);

	//读入将生成的问题数量
	int NumProblem;
	Console::Write("{0}\n", rc.GetString("InputNumberOfProblems", loca));
	cin >> NumProblem;

	//关于作答的其他说明
	Console::WriteLine("{0}\n", rc.GetString("InputNote", loca)); 
	
	// 生成并输出题目
	int CorrNum = 0, WrongNum = 0;
	int i,j;//循环变量
	char ans[MAX_NUM_OF_PROBLEM];//用户答案（字符串）
	int len;//用户答案长度
	int intans[MAX_NUM_OF_PROBLEM];//用户答案（数值）
	int judge = 0;//判断用户答案中是否含有e
	int num = 0;//转换用户答案
	int WrongQueNum[MAX_NUM_OF_PROBLEM];//回答错误的题目的编号
	Operation *Problem[MAX_NUM_OF_PROBLEM];//指向题目的指针
	for (i = 0; i < MAX_NUM_OF_PROBLEM; i++)
		Problem[i] = NULL;
	//输出 “序号.题目=”并输入用户答案
	for (j = 0; j<NumProblem; j++)
	{
		Problem[j] = new Operation();
		cout << j + 1 << ". ";
		(Problem[j])->print();
		cout << " = ";
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
		Fraction *p;//指向 分数 的指针
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

	//输出报告
	Console::WriteLine("{0}{1,-12}{2}{3,-12}{4}{5,-12}", rc.GetString("Total", loca), CorrNum+WrongNum,
		rc.GetString("CorrectNum", loca),CorrNum,rc.GetString("WrongNum", loca), WrongNum);
	int WrongCode;//错误题目编号
	if (WrongNum > 0)
	{
		Console::WriteLine("{0}", rc.GetString("DetailMistake", loca));
		for (i = 0; i < WrongNum; i++)
		{
			cout << endl;
			WrongCode = WrongQueNum[i];
			cout << WrongCode + 1 << ".";
			(Problem[WrongCode])->print();
			cout << " = ";
			((Problem[WrongCode])->getans()).print();
			cout << endl;
			Console::Write("{0,4}", rc.GetString("YourAnswer", loca));
			cout << intans[WrongCode] << endl;
		}
	}
	cout << endl;

	//结束程序前处理	
	for (i = 0; i<MAX_NUM_OF_PROBLEM; i++)
	{
		delete(Problem[i]);
	}
	return 0;
}
