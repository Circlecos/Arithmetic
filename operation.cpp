#include "operation.h"
#include "TreePoint.h"
#include <iostream>
Operation::Operation():root(NULL),ans()
{
	Fraction *p;
	root=new TreePoint(1,1);
	while ((p=root->compute())==NULL) //if setans() return 1, this tree has error
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
	root->print(0);
}
Fraction Operation::getans()
{
	return ans;
}

