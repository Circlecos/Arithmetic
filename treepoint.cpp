#include "treepoint.h"
#include <time.h>
#include <stdlib.h>
#include "fraction.h"
#include <iostream>

#define MAXNUM 10
#define MAXLEVEL 3


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

int TreePoint::newnum(int randmin,int randmax)
{
	int x;
	x=(static_cast<int> (rand()));
	if (x!=0) x=x%(randmax+1-randmin);
	return (x+randmin);
}

int TreePoint::set()
{
	int flag,x; 
	if (symbol=='0') 
	{
		prep=NULL;next=NULL;priority=3;
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
}//set other variable based on symbol



//public
TreePoint::TreePoint() :prep(NULL),next(NULL),symbol('0'),priority(4),rightpriority(4),num(NULL)
{
	
}
//default constructor

TreePoint::TreePoint(int model,int f):prep(NULL),next(NULL),symbol('0'),priority(4),rightpriority(3),num(NULL)
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
		if ((c=newnum(0,1))==0)
		{		
			prep=new TreePoint(1,2);  
			next=new TreePoint(0,2);		
		}
		else 
		{
			prep=new TreePoint(0,2);
			next=new TreePoint(1,2);		
		}
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
	if (prep!=NULL) delete(prep);
	if (next!=NULL) delete(next);
	if (num!=NULL) delete(num);
}


int TreePoint::print(int lastpri)// first time lastpri=0
{
	if (lastpri>priority) std::cout<<"( ";
	if (prep!=NULL)
		prep->print(priority);
	if (symbol!='0'&&symbol!='/')
		std::cout<<symbol<<" ";
	else if (symbol=='/')
		std::cout<<"¡Â ";
	else num->print();
	if (next!=NULL)
		next->print(rightpriority);
	if (lastpri>priority) std::cout<<") ";
	return 0;
}

Fraction* TreePoint::compute()// first time lastpri=0
{
	Fraction *p1=NULL,*p2=NULL,*p3=NULL;
	if (prep!=NULL)
		p1=prep->compute();
	if (symbol=='0')
		return (new Fraction(*num));
	if (p1==NULL) { delete p1;delete p2;return NULL;};
	if (next!=NULL)
		p2=next->compute();
	if (p2==NULL) { delete p1;delete p2;return NULL;};
	if (symbol=='/')
		if (p2->ifzero()==1)//true
		{
			delete p1;
			delete p2;
			return NULL;
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
