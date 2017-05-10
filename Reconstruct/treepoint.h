/******************************************************************************
文件名： treepoint.h
作者：Circle  日期：2017/02/04
描述："treepoint"类
*******************************************************************************/

#ifndef TREEPOINT_H_
#define TREEPOINT_H_

#include "fraction.h"
#include <string>

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
	std::string print(int lastpri);//last priority   Traversal tree,print the equation and calculate the answer
	Fraction* compute();
};

#endif
