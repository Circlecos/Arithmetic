#include "fraction.h"
#include <iostream>
#include <cmath>

Fraction::Fraction():nume(0),deno(1)
{

}
Fraction::Fraction(int nu,int de):nume(nu),deno(de)
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


int Fraction::print()
{
	if (nume==0) {std::cout<<"0 ";return 0;}
	if (deno*nume<0) 
	{
		std::cout<<"-";
		deno=abs(deno);
		nume=abs(nume);
	}
	if (deno==1) std::cout<<nume;
	else std::cout<<nume<<"/"<<deno;
	std::cout<<" "; 
	return 0;
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
