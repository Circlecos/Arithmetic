/******************************************************************************
�ļ����� fraction.cpp
���ߣ�Circle  ���ڣ�2017/02/04
������"fraction"��
*******************************************************************************/

#include "fraction.h"
#include <iostream>
#include <cmath>
#include <sstream>

Fraction::Fraction():nume(0),deno(1)
{

}
Fraction::Fraction(int nu,int de=1):nume(nu),deno(de)
{
	simplify();
}
Fraction::~Fraction()
{

}

Fraction::Fraction(const Fraction &from)
{
	nume=from.nume;
	deno=from.deno;
}


std::string Fraction::print()
{
	int width=0,widnume=0,widdeno=0;
	std::string s="";
	
	if (nume==0) {s+="0";width+=1;return s;}
	if (deno*nume<0)
	{
		s+="-";
		width+=1;
		deno=abs(deno);
		nume=abs(nume);

	}
	widnume=(static_cast<int> (log10(nume)))+1;
	widdeno=(static_cast<int> (log10(deno)))+1;
	std::stringstream ss;
	std::string temp;
	if (deno == 1) 
	{
		ss << nume;
		ss >> temp;
		s += temp;
		width += widnume;
	}
	else
	{ 
		ss << nume; 
		ss >> temp; 
		s += temp; 
		s += "/"; 
		ss << deno;
		ss >> temp; 
		s += temp; 
		width += 1 + widnume + widdeno; }
	
	return s;
}

Fraction& Fraction::operator= (const Fraction &rhs)
{
	if(this!=&rhs)
	{
		this->deno=rhs.deno;
		this->nume=rhs.nume;
	}
	return *this;
}



//private of Fraction


int Fraction::simplify()
{
	int x,y,temp;
	if (nume==0) {deno=1;return 0;}
	x=abs(nume);y=abs(deno);
	if (x<y) {temp=x;x=y;y=temp;}
	while (x%y!=0)
	{
		temp=x%y;
		x=y;
		y=temp;
	}//find the GCD between nume and demo
	if (y!=1)
	{
		nume/=y;
		deno/=y;
	}
	return 0;
}


bool operator==(const Fraction &lhs,const Fraction &rhs)
{
	return ((lhs.nume==rhs.nume)&&(lhs.deno==rhs.deno));
}


const Fraction operator+ (const Fraction &lhs,const Fraction &rhs)
{
	int newdeno,newnume;
	newnume=(lhs.nume)*(rhs.deno)+(rhs.nume)*(lhs.deno);
	newdeno=(lhs.deno)*(rhs.deno);
	return Fraction(newnume,newdeno);
}
const Fraction operator- (const Fraction &lhs,const Fraction &rhs)
{
	int newdeno,newnume;
	newnume=(lhs.nume)*(rhs.deno)-(rhs.nume)*(lhs.deno);
	newdeno=(lhs.deno)*(rhs.deno);
	return Fraction(newnume,newdeno);
}
const Fraction operator* (const Fraction &lhs,const Fraction &rhs)
{
	int newdeno,newnume;
	newnume=(lhs.nume)*(rhs.nume);
	newdeno=(lhs.deno)*(rhs.deno);
	return Fraction(newnume,newdeno);
}
const Fraction operator/ (const Fraction &lhs,const Fraction &rhs)
{
	Fraction reci(rhs.deno,rhs.nume);//reciprocal
	return (lhs*reci);
}
