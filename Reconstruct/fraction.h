#ifndef FRACTION_H_
#define FRACTION_H_

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
	int print();
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
