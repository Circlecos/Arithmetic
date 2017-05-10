/******************************************************************************
文件名： fraction.h
作者：Circle  日期：2017/02/04
描述："fraction"类
*******************************************************************************/


#ifndef FRACTION_H_
#define FRACTION_H_

#include <string>

class Fraction{
private:
	int nume;// numerator
	int deno;// denominator

	int simplify();// simplify the fraction

public:
	Fraction();
	Fraction(int nu,int de);
	Fraction(const Fraction &from);
	~Fraction();

	std::string print();
	Fraction& operator= (const Fraction &rhs);

	friend bool operator==(const Fraction &lhs,const Fraction &rhs);
	friend const Fraction operator+ (const Fraction &lhs,const Fraction &rhs);
	friend const Fraction operator- (const Fraction &lhs,const Fraction &rhs);
	friend const Fraction operator* (const Fraction &lhs,const Fraction &rhs);
	friend const Fraction operator/ (const Fraction &lhs,const Fraction &rhs);

	inline int ifzero()
	{
		if (nume==0) return 1;//true
		return 0;
	}
	inline int ifint()
	{
		if (deno==1) return 1;//true
		return 0;
	}
};

#endif
