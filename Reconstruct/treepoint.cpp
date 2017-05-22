/******************************************************************************
文件名： treepoint.cpp
作者：Circle  日期：2017/02/04
描述："treepoint"类
*******************************************************************************/

#include "treepoint.h"
#include <time.h>
#include <stdlib.h>
#include "fraction.h"
#include <iostream>

#define MAXNUM 10
#define MAXLEVEL 2

int TreePoint::newnum(int randmin, int randmax)
{
	int x;
	x = (static_cast<int> (rand()));
	if (x != 0) x = x % (randmax + 1 - randmin);
	return (x + randmin);
}

//private
char TreePoint::newsymbol(int maxnumber)
{
	int c;
	char x;
	switch (c=newnum(1,maxnumber))
	{
		case 1:x='+';break;
		case 2:x='-';break;
		case 3:x='*';break;
		case 4:x='/';break;
		default:x='0';break;
	}
	return x;
}




//set other variable based on symbol
int TreePoint::set()
{
	int flag,x;
	if (symbol=='0')
	{
		prep=nullptr;next=nullptr;priority=3;
		flag=newnum(0,1);
		if (flag==0)// int
		{
			num=new Fraction(newnum(0,MAXNUM),1);
		}
		else // proper fraction
		{
			x=newnum(1,MAXNUM-1);
			num=new Fraction(x,newnum(x+1,MAXNUM));
		}
	}
	else
	{
		switch (symbol)
		{
			case '+':priority=1;rightpriority=1;break;
			case '-':priority=1;rightpriority=3;break;
			case '*':priority=2;rightpriority=2;break;
			case '/':priority=2;rightpriority=3;break;
		}
	}
	return 0;
}



//public
TreePoint::TreePoint() :prep(nullptr),next(nullptr),symbol('0'),priority(4),rightpriority(4),num(nullptr)//default constructor
{

}


TreePoint::TreePoint(int model,int f):prep(nullptr),next(nullptr),symbol('0'),priority(4),rightpriority(3),num(nullptr)
//f==1 means root of the tree  f==2 means the second level of the tree and so on
//Model 1 means it can only be a operator, not a number.
//Model 3 means it can only be a number
{
	int c;
	if (model==1) { symbol=newsymbol(4);set();}
	else if (model==0) {symbol=newsymbol(50);set();} //4-50 means '0' . change 50 to change the chance of '0'
	else {symbol='0';set();}
	if (f==1)// make sure the equation has 3 number
	{
		prep=new TreePoint(1,2);
		next=new TreePoint(1,2);
	}
	else if ((f<MAXLEVEL)&&(symbol!='0'))// make sure the equation has MAXLEVEL number most.
	{
		prep=new TreePoint(0,f+1);
		next=new TreePoint(0,f+1);
	}
	else if ((f==MAXLEVEL)&&(symbol!='0'))
	{
		prep=new TreePoint(3,f+1);
		next=new TreePoint(3,f+1);
	}
}


TreePoint::~TreePoint()
{
	if (prep!=nullptr) delete(prep);
	if (next!=nullptr) delete(next);
	if (num!=nullptr) delete(num);
}


std::string TreePoint::print(int lastpri)// first time lastpri=0
{
	extern int wid;
	std::string s;
	if (lastpri>priority) {s+="( ";wid+=2;}
	if (prep!=nullptr)
		s+=prep->print(priority);//访问左孩子
	if (symbol!='0'&&symbol!='/')
	{
		s += " ";
		s += symbol;
		s += " "; wid += 3;
	}
	else if (symbol=='/')
		{s+=" \u00F7 ";wid+=4;}
	else { wid += (num->print()).size(); s += (num->print()); }
	if (next!=nullptr)
		s+=next->print(rightpriority);//访问右孩子
	if (lastpri>priority) {s+=" )";wid+=2;}
	return s;
}

Fraction* TreePoint::compute()// first time lastpri=0
{
	Fraction *p1=nullptr,*p2=nullptr,*p3=nullptr;
	if (prep!=nullptr)
		p1=prep->compute();
	if (symbol=='0')
		return (new Fraction(*num));
	if (p1==nullptr) { delete p1;delete p2;return nullptr;};
	if (next!=nullptr)
		p2=next->compute();
	if (p2==nullptr) { delete p1;delete p2;return nullptr;};
	if (symbol=='/')
		if (p2->ifzero()==1)//true
		{
			delete p1;
			delete p2;
			return nullptr;
		}
	p3=new Fraction(0,1);
	switch (symbol)
	{
		case '+':*p3=*p1+*p2;break;
		case '-':*p3=*p1-*p2;break;
		case '*':*p3=(*p1)*(*p2);break;
		case '/':*p3=(*p1)/(*p2);break;
	}
	delete p1;
	delete p2;
	return p3;
}


#undef MAXNUM
#undef MAXLEVEL
