#include "interact.h"
#include <fstream>
#include <iomanip>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <msclr\marshal.h>
#include <msclr\marshal_cppstd.h>



using namespace std;
using namespace System;
using namespace System::Resources;
using namespace System::Collections;
using namespace System::Globalization;
using namespace System::Reflection;
using namespace msclr::interop;


#define TO_STRING(X) marshal_as<std::string>(X)
#define TO_SYSTEM_STRING(X) marshal_as<System::String^>(X)


int Interact::ReadFile(char * filename)
{
	int nProblem;
	fstream f1;
	f1.open(filename, ios::in);
	f1 >> nProblem;
	if (nProblem < 0)
	{
		throw out_of_range("The number of Problem is less than 0.");
	}
	else {
		f1.close();
		NumProblem = nProblem;
	}
	return 0;
}
int Interact::BaseSetting(string &loca,int nPro)
{
	location = loca;
	NumProblem = nPro;
	return 0;
}

int Interact::BaseSetting(string &loca)
{
	location = loca;
	return 0;
}

string Interact::GetLoca()
{
	return location;
}

string Interact::ShowTips()
{
	
	//读入用户对应的resource
	Assembly^ CurrentAssem = Assembly::GetExecutingAssembly();
	ResourceManager RcLang("LangList", CurrentAssem);
	ResourceManager rc("Resource", CurrentAssem);
	
	CultureInfo^ loca = gcnew CultureInfo(TO_SYSTEM_STRING(location), false);

	//关于作答的其他说明

	return TO_STRING(rc.GetString("InputNote", loca));
}


int Interact::GetUserAns(char ans[],int len,int &flag,int code)
{
	int i,judge = 0;
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
	{
		flag = 1;
		return 0;
	}
	else
	{
		int num = 0;
		judge = 0;
		if (ans[0] == '-') judge = 1;
		for (i = 0; i < len; i++)
		{
			if ((judge == 1) && (i == 0)) continue;
			num += (static_cast<int>(pow(10, len - i - 1)*(ans[i] - 48)));
		}
		if (judge == 1) { intAns[code] = (0 - num); return 0; }
		else { intAns[code] = num; return 0; }
	}
}
int Interact::GetUserAns(int code)
{
	return intAns[code];
}

int Interact::GetNumProblem()
{
	return NumProblem;
}
int Interact::GetCorr()
{
	return CorrNum;
}
int Interact::GetWrong()
{
	return WrongNum;
}
int Interact::GetWrongCode(int code)
{
	return WrongQueNum[code];
}
Operation* Interact::getExpression(int code)
{
	return Problem[code];
}
int Interact::Judge(int code)
{
	Fraction *p;//指向 分数 的指针
	p = new Fraction(intAns[code], 1);
	if ((Problem[code]->getans()) == *p)
	{
		CorrNum++;
	}
	else
	{
		WrongQueNum[WrongNum] = code;
		WrongNum++;
	}
	delete p;

	return 0;
}



Operation& Interact::generateExpression(int code) 
{
	Problem[code] = new Operation();
	return *Problem[code];
}