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
#include <string>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <msclr\marshal.h>
#include <msclr\marshal_cppstd.h>
#include "operation.h"
#include "fraction.h"
#include "interact.h"

#define TO_STRING(X) marshal_as<std::string>(X)
#define TO_SYSTEM_STRING(X) marshal_as<System::String^>(X)

using namespace System;
using namespace System::Resources;
using namespace System::Collections;
using namespace System::Globalization;
using namespace System::Reflection;
using namespace msclr::interop;
using namespace std;


int scan(Interact& act);//该函数用于与用户交互，获取输入数据
int generateExpression(Interact& act);//用于生成运算式
int writeFile(char* filename, Interact& act);//将最终结果写入文件
int print(Interact& act);//将统计结果输出给用户



Interact control;

int main(int argc, char *argv[])
{
	
	

	//重置随机数种子
	srand(static_cast<unsigned> (time(NULL)));

	control.ReadFile(argv[1]);
	scan(control);
	cout<<control.ShowTips()<<endl;

	generateExpression(control);
	cout << "-----------------------------------" << endl;
	writeFile(argv[2], control);
	print(control);
	
	system("pause");

	return 0;
}


int scan(Interact& act)
{
	string s;
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
			{
				isLang = 1;
				s = marshal_as<std::string>(idlanginfo->Value->ToString());
			}
		}
		if (isLang == 1) break;
		else if (isLang == 0)
		{
			cout<<"The input is error!";
			cout<<"Please enter the prompt language by its name:";
		}
	}
	
	
	int nProblem;
	
	act.BaseSetting(s);
	
	return 0;
}
int generateExpression(Interact& act)
{
	char ans[MAX_NUM_OF_PROBLEM];//用户答案（字符串）
	
	int len;//用户答案长度
	int judge = 0;//判断用户答案中是否含有e
	int num = 0;//转换用户答案
	int i, j;//循环变量
	
	for (j = 0; j < act.GetNumProblem(); j++)
	{
		Operation &pro = act.generateExpression(j);
		String^ ProblemCodeStr = ((j + 1).ToString());
		ProblemCodeStr = System::String::Concat(ProblemCodeStr, ".");
		cout<< setiosflags(ios::left) << setw(5)<<TO_STRING(ProblemCodeStr);
		cout<<pro.print();
		cout << " = " ;

		//输入用户答案
		int flag=0;
		cin >> ans;
		len = strlen(ans);
		control.GetUserAns(ans,len,flag,j);
		if (flag == 1)
		{
			break;
		}
		
		control.Judge(j);
		
	}
	return 0;
}
int writeFile(char* filename,Interact& act)
{
	fstream f1;
	f1.open(filename, ios::out);
	//输出报告
	Assembly^ CurrentAssem = Assembly::GetExecutingAssembly();
	ResourceManager RcLang("LangList", CurrentAssem);
	ResourceManager rc("Resource", CurrentAssem);
	CultureInfo^ loca = gcnew CultureInfo(TO_SYSTEM_STRING(control.GetLoca()), false);
	f1 << TO_STRING(rc.GetString("Total", loca))
		<< setiosflags(ios::left) << setw(12) << act.GetCorr() + act.GetWrong()
		<< TO_STRING(rc.GetString("CorrectNum", loca))
		<< setiosflags(ios::left) << setw(12) << act.GetCorr()
		<< TO_STRING(rc.GetString("WrongNum", loca)) << setiosflags(ios::left) << setw(12) << act.GetWrong() << endl;
	int WrongCode;//错误题目编号
	int i;//循环变量
	if (act.GetWrong() > 0)
	{
		f1 << TO_STRING(rc.GetString("DetailMistake", loca)) << endl;
		for (i = 0; i < act.GetWrong(); i++)
		{
			f1 << endl;
			WrongCode = act.GetWrongCode(i);
			String^ WrongCodeStr = ((WrongCode + 1).ToString());
			WrongCodeStr = System::String::Concat(WrongCodeStr, ".");
			f1 << setiosflags(ios::left) << setw(5) << TO_STRING(WrongCodeStr);
			Operation *ques= act.getExpression(WrongCode);
			f1 << (ques->print());
			f1 << " = ";
			f1 << (ques->getans()).print();
			f1 << endl;
			f1 << "     " << TO_STRING(rc.GetString("YourAnswer", loca));
			f1 << act.GetUserAns(WrongCode) << endl;
		}
	}
	f1 << endl;
	f1.close();

	return 0;
}
int print(Interact& act) {

	//输出报告
	Assembly^ CurrentAssem = Assembly::GetExecutingAssembly();
	ResourceManager RcLang("LangList", CurrentAssem);
	ResourceManager rc("Resource", CurrentAssem);
	CultureInfo^ loca = gcnew CultureInfo(TO_SYSTEM_STRING(control.GetLoca()), false);
	cout<<TO_STRING(rc.GetString("Total",loca))
		<<setiosflags(ios::left) << setw(12)<< act.GetCorr() + act.GetWrong()
		<<TO_STRING(rc.GetString("CorrectNum",loca))
		<< setiosflags(ios::left) << setw(12)<< act.GetCorr()
		<<TO_STRING(rc.GetString("WrongNum",loca)) << setiosflags(ios::left) << setw(12) << act.GetWrong() <<endl;
	int WrongCode;//错误题目编号
	int i;//循环变量
	if (act.GetWrong() > 0)
	{
		cout << TO_STRING(rc.GetString("DetailMistake", loca)) << endl;
		for (i = 0; i < act.GetWrong(); i++)
		{
			cout<<endl;
			WrongCode = act.GetWrongCode(i);
			String^ WrongCodeStr = ((WrongCode + 1).ToString());
			WrongCodeStr = System::String::Concat(WrongCodeStr, ".");
			cout<< setiosflags(ios::left) << setw(5)<<TO_STRING(WrongCodeStr);
			Operation *ques = act.getExpression(WrongCode);
			cout << (ques->print());
			cout << " = ";
			cout<<(ques->getans()).print();
			cout << endl;
			cout << "     " << TO_STRING(rc.GetString("YourAnswer", loca));
			cout << act.GetUserAns(WrongCode) << endl;
		}
	}
	cout << endl;
	return 0;

}//将统计结果输出给用户