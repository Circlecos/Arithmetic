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
	

	friend const Fraction operator+ (const Fraction &lhs,const Fraction &rhs);
	friend const Fraction operator- (const Fraction &lhs,const Fraction &rhs);
	friend const Fraction operator* (const Fraction &lhs,const Fraction &rhs);
	friend const Fraction operator/ (const Fraction &lhs,const Fraction &rhs);

	inline int ifzero()
	{
		if (nume==0) return 1;
		return 0;
	}
};

#endif
