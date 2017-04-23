#include "operation.h"
#include "TreePoint.h"
#include <iostream>

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
int Operation::print()
{
	wid=0;
	root->print(0);
	return wid;
}
Fraction Operation::getans()
{
	return ans;
}

