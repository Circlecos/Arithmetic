#ifndef TREEPOINT_H_
#define TREEPOINT_H_

#include "fraction.h"

class TreePoint{
private:
	TreePoint *prep;
	TreePoint *next;
	char symbol;
	int priority;
	int rightpriority;
	Fraction *num;
	char newsymbol(int upper);
	int set();
	int newnum(int min,int max);// random min-10
public:
	TreePoint();
	~TreePoint();
	TreePoint(int model,int f);//init construct: f==1 means root of the tree  f==2 means the second level of the tree
	//Model 1 means it can only be a operator, not a number.
	int print(int lastpri);//last priority   Traversal tree,print the equation and calculate the answer
	Fraction* compute();
};

#endif
