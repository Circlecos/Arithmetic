/******************************************************************************
文件名： operation.cpp
作者：Circle  日期：2017/02/04
描述："operation"类
*******************************************************************************/

#include "operation.h"
#include "TreePoint.h"
#include <iostream>
#include <string>

int wid=0;

Operation::Operation():root(NULL),ans()
{
	Fraction *p;
	root=new TreePoint(1,1);
	while (((p=root->compute())==NULL)||(p->ifint()==0)) //if compute() return NULL or ifint() return 0, this tree has error
	{
		delete root;
		root=new TreePoint(1,1);
	}
	ans=Fraction(*p);

}
//default constructor


Operation::~Operation()
{
	delete root;
}

Operation::Operation(const Operation &from)
{
	root=new TreePoint(*(from.root));
}
std::string Operation::print()
{
	std::string s;
	wid=0;
	s=root->print(0);
	return s;
}
Fraction Operation::getans()
{
	return ans;
}

