#include <iostream>
#include <iomanip>
#include<string>
#include <stdlib.h>
#include <time.h>
#include<math.h>
#include<Windows.h>
#include <msclr\marshal.h>
#include <msclr\marshal_cppstd.h>
#include "operation.h"
#include "fraction.h"

#define MAX_NUM_OF_PROBLEM 1000
#define TO_STRING(X) marshal_as<std::string>(X)
#define TO_SYSTEM_STRING(X) marshal_as<System::String^>(X)

using namespace System;
using namespace System::Resources;
using namespace System::Collections;
using namespace System::Globalization;
using namespace System::Reflection;
using namespace msclr::interop;
using namespace std;


int scan();//该函数用于与用户交互，获取输入数据
int generateExpression();//用于生成运算式
int print();//将统计结果输出给用户

int NumProblem;
int CorrNum = 0, WrongNum = 0;
int i, j;//循环变量
char ans[MAX_NUM_OF_PROBLEM];//用户答案（字符串）
int len;//用户答案长度
int intans[MAX_NUM_OF_PROBLEM];//用户答案（数值）
int judge = 0;//判断用户答案中是否含有e
int num = 0;//转换用户答案
int WrongQueNum[MAX_NUM_OF_PROBLEM];//回答错误的题目的编号
Operation *Problem[MAX_NUM_OF_PROBLEM];//指向题目的指针
string str;

int main()
{
	//重置随机数种子
	srand(static_cast<unsigned> (time(NULL)));

	scan();

	

	generateExpression();
	cout << "-----------------------------------" << endl;
	print();

	//结束程序前处理	
	for (i = 0; i<MAX_NUM_OF_PROBLEM; i++)
	{
		delete(Problem[i]);
	}
	return 0;
}


int scan()
{
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
		cout << NumLang << ":" << setiosflags(ios::left) << setw(7) << TO_STRING((idlanginfo->Key)->ToString()) << endl;
	}

	//读入用户选择的语言和对应的resource
	cout<<"Please enter the prompt language by its name:";

	int isLang = 0;
	while (cin>>str)
	{
		idlanginfo->Reset();
		while (idlanginfo->MoveNext())
		{
			if (idlanginfo->Key->ToString()->Equals(TO_SYSTEM_STRING(str)))//判断用户输入的语言是否已设置
				isLang = 1;
		}
		if (isLang == 1) break;
		else if (isLang == 0)
		{
			cout<<"The input is error!";
			cout<<"Please enter the prompt language by its name:";
		}
	}
	//读入用户对应的resource
	ResourceManager rc("Resource", CurrentAssem);
	CultureInfo^ loca = gcnew CultureInfo(RcLang.GetString(TO_SYSTEM_STRING(str)), false);

	//读入将生成的问题数量
	cout << TO_STRING(rc.GetString("InputNumberOfProblems", loca));
	cin >> NumProblem;
	cout << endl;
	//关于作答的其他说明

	cout << TO_STRING(rc.GetString("InputNote", loca)) << endl;

	
	return 0;
}
int generateExpression()
{

	for (i = 0; i < MAX_NUM_OF_PROBLEM; i++)
		Problem[i] = NULL;
	for (j = 0; j < NumProblem; j++)
	{
		Problem[j] = new Operation();

		String^ ProblemCodeStr = ((j + 1).ToString());
		ProblemCodeStr = System::String::Concat(ProblemCodeStr, ".");
		cout<< setiosflags(ios::left) << setw(5)<<TO_STRING(ProblemCodeStr);
		(Problem[j])->print();
		cout << " = " ;

		//输入用户答案
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
	return 0;
}
int print() {
	//输出报告
	
	Assembly^ CurrentAssem = Assembly::GetExecutingAssembly();
	ResourceManager RcLang("LangList", CurrentAssem);
	ResourceManager rc("Resource", CurrentAssem);
	CultureInfo^ loca = gcnew CultureInfo(RcLang.GetString(TO_SYSTEM_STRING(str)), false);
	cout<<TO_STRING(rc.GetString("Total",loca))
		<<setiosflags(ios::left) << setw(12)<< CorrNum + WrongNum
		<<TO_STRING(rc.GetString("CorrectNum",loca))
		<< setiosflags(ios::left) << setw(12)<< CorrNum
		<<TO_STRING(rc.GetString("WrongNum",loca)) << setiosflags(ios::left) << setw(12) << WrongNum<<endl;
	int WrongCode;//错误题目编号
	if (WrongNum > 0)
	{
		cout << TO_STRING(rc.GetString("DetailMistake", loca)) << endl;
		for (i = 0; i < WrongNum; i++)
		{
			cout<<endl;
			WrongCode = WrongQueNum[i];
			String^ WrongCodeStr = ((WrongCode + 1).ToString());
			WrongCodeStr = System::String::Concat(WrongCodeStr, ".");
			cout<< setiosflags(ios::left) << setw(5)<<TO_STRING(WrongCodeStr);
			(Problem[WrongCode])->print();
			cout << " = ";
			((Problem[WrongCode])->getans()).print();
			cout << endl;
			cout << "     " << TO_STRING(rc.GetString("YourAnswer", loca));
			cout << intans[WrongCode] << endl;
		}
	}
	cout << endl;
	return 0;

}//将统计结果输出给用户