#ifndef OPERATION_H_
#define OPERATION_H_

#include "fraction.h"
#include "treepoint.h"

class Operation{
private:
	TreePoint *root;
	Fraction ans;

public:
	Operation();
	~Operation();
	Operation(const Operation &from);
	int print();
	Fraction getans();
};

#endif
