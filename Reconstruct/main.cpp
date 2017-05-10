/******************************************************************************
文件名： main.cpp
作者：Circle  日期：2017/02/04
描述：主函数，与用户进行交互

作者：Circle  日期：2017/05/10
描述：命令行模式
*******************************************************************************/

#include <iostream>
#include <fstream>
#include <iomanip>
#include<string>
#include <stdlib.h>
#include <time.h>
#include <math.h>
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

int readFile(char *filename);
int scan(string &s);//该函数用于与用户交互，获取输入数据
int generateExpression(int nProblem,Operation** ArrayProblem,int *UserAns,int *corr,int *wrong,int *ArrayWrong);//用于生成运算式
int writeFile(char *outputfilename,Operation** ArrayProblem, int *UserAns, int *corr, int *wrong, int *ArrayWrong, string &s);//将最终结果写入文件
int print(Operation** ArrayProblem, int *UserAns, int *corr, int *wrong, int *ArrayWrong, string &s);//将统计结果输出给用户




int main(int argc, char *argv[])
{
	string str;//处理地区信息
	int CorrNum = 0, WrongNum = 0;
	int WrongQueNum[MAX_NUM_OF_PROBLEM];//回答错误的题目的编号
	int intAns[MAX_NUM_OF_PROBLEM];//用户答案（数值）
	int NumProblem = 0;
	Operation *Problem[MAX_NUM_OF_PROBLEM];//指向题目的指针

	//重置随机数种子
	srand(static_cast<unsigned> (time(NULL)));

	NumProblem = readFile(argv[1]);
	scan(str);

	generateExpression(NumProblem,Problem,intAns,&CorrNum,&WrongNum,WrongQueNum);
	cout << "-----------------------------------" << endl;
	writeFile(argv[2], Problem, intAns, &CorrNum, &WrongNum, WrongQueNum,str);
	print(Problem, intAns,&CorrNum, &WrongNum, WrongQueNum,str);
	
	system("pause");

	//结束程序前处理	
	int i;//循环变量
	for (i = 0; i<MAX_NUM_OF_PROBLEM; i++)
	{
		delete(Problem[i]);
	}
	return 0;
}

int readFile(char *filename)
{
	int nProblem;
	fstream f1;
	f1.open(filename,ios::in);
	f1 >> nProblem;
	//to-do#1: judge NumProblem
	f1.close();
	return nProblem;
	
}
int scan(string &s)
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
	while (cin>>s)
	{
		idlanginfo->Reset();
		while (idlanginfo->MoveNext())
		{
			if (idlanginfo->Key->ToString()->Equals(TO_SYSTEM_STRING(s)))//判断用户输入的语言是否已设置
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
	CultureInfo^ loca = gcnew CultureInfo(RcLang.GetString(TO_SYSTEM_STRING(s)), false);

	//关于作答的其他说明

	cout << TO_STRING(rc.GetString("InputNote", loca)) << endl;

	
	return 0;
}
int generateExpression(int nProblem, Operation** ArrayProblem, int *UserAns, int *corr, int *wrong, int *ArrayWrong)
{
	char ans[MAX_NUM_OF_PROBLEM];//用户答案（字符串）
	
	int len;//用户答案长度
	int judge = 0;//判断用户答案中是否含有e
	int num = 0;//转换用户答案
	int i, j;//循环变量
	for (i = 0; i < MAX_NUM_OF_PROBLEM; i++)
		ArrayProblem[i] = NULL;
	for (j = 0; j < nProblem; j++)
	{
		ArrayProblem[j] = new Operation();

		String^ ProblemCodeStr = ((j + 1).ToString());
		ProblemCodeStr = System::String::Concat(ProblemCodeStr, ".");
		cout<< setiosflags(ios::left) << setw(5)<<TO_STRING(ProblemCodeStr);
		cout<<(ArrayProblem[j])->print();
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
		if (judge == 1) UserAns[j] = 0 - num;
		else UserAns[j] = num;
		Fraction *p;//指向 分数 的指针
		p = new Fraction(UserAns[j], 1);
		if ((ArrayProblem[j]->getans()) == *p)
		{
			(*corr)++;
		}
		else
		{
			ArrayWrong[*wrong] = j;
			(*wrong)++;
		}
		delete p;
	}
	return 0;
}
int writeFile(char* filename, Operation** ArrayProblem, int *UserAns, int *corr, int *wrong, int *ArrayWrong, string &s)
{
	fstream f1;
	f1.open(filename, ios::out);
	//输出报告
	Assembly^ CurrentAssem = Assembly::GetExecutingAssembly();
	ResourceManager RcLang("LangList", CurrentAssem);
	ResourceManager rc("Resource", CurrentAssem);
	CultureInfo^ loca = gcnew CultureInfo(RcLang.GetString(TO_SYSTEM_STRING(s)), false);
	f1 << TO_STRING(rc.GetString("Total", loca))
		<< setiosflags(ios::left) << setw(12) << *corr + *wrong
		<< TO_STRING(rc.GetString("CorrectNum", loca))
		<< setiosflags(ios::left) << setw(12) << *corr
		<< TO_STRING(rc.GetString("WrongNum", loca)) << setiosflags(ios::left) << setw(12) << *wrong << endl;
	int WrongCode;//错误题目编号
	int i;//循环变量
	if (*wrong > 0)
	{
		f1 << TO_STRING(rc.GetString("DetailMistake", loca)) << endl;
		for (i = 0; i < *wrong; i++)
		{
			f1 << endl;
			WrongCode = ArrayWrong[i];
			String^ WrongCodeStr = ((WrongCode + 1).ToString());
			WrongCodeStr = System::String::Concat(WrongCodeStr, ".");
			f1 << setiosflags(ios::left) << setw(5) << TO_STRING(WrongCodeStr);

			f1 << (ArrayProblem[WrongCode])->print();
			f1 << " = ";
			f1 << ((ArrayProblem[WrongCode])->getans()).print();
			f1 << endl;
			f1 << "     " << TO_STRING(rc.GetString("YourAnswer", loca));
			f1 << UserAns[WrongCode] << endl;
		}
	}
	f1 << endl;
	f1.close();

	return 0;
}
int print(Operation** ArrayProblem,int *UserAns, int *corr, int *wrong, int *ArrayWrong, string &s) {

	//输出报告
	Assembly^ CurrentAssem = Assembly::GetExecutingAssembly();
	ResourceManager RcLang("LangList", CurrentAssem);
	ResourceManager rc("Resource", CurrentAssem);
	CultureInfo^ loca = gcnew CultureInfo(RcLang.GetString(TO_SYSTEM_STRING(s)), false);
	cout<<TO_STRING(rc.GetString("Total",loca))
		<<setiosflags(ios::left) << setw(12)<< *corr + *wrong
		<<TO_STRING(rc.GetString("CorrectNum",loca))
		<< setiosflags(ios::left) << setw(12)<< *corr
		<<TO_STRING(rc.GetString("WrongNum",loca)) << setiosflags(ios::left) << setw(12) << *wrong<<endl;
	int WrongCode;//错误题目编号
	int i;//循环变量
	if (*wrong > 0)
	{
		cout << TO_STRING(rc.GetString("DetailMistake", loca)) << endl;
		for (i = 0; i < *wrong; i++)
		{
			cout<<endl;
			WrongCode = ArrayWrong[i];
			String^ WrongCodeStr = ((WrongCode + 1).ToString());
			WrongCodeStr = System::String::Concat(WrongCodeStr, ".");
			cout<< setiosflags(ios::left) << setw(5)<<TO_STRING(WrongCodeStr);
			cout << (ArrayProblem[WrongCode])->print();
			cout << " = ";
			cout<<((ArrayProblem[WrongCode])->getans()).print();
			cout << endl;
			cout << "     " << TO_STRING(rc.GetString("YourAnswer", loca));
			cout << UserAns[WrongCode] << endl;
		}
	}
	cout << endl;
	return 0;

}//将统计结果输出给用户