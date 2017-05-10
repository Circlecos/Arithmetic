/******************************************************************************
�ļ����� operation.h
���ߣ�Circle  ���ڣ�2017/02/04
������"operation"��
*******************************************************************************/


#ifndef OPERATION_H_
#define OPERATION_H_

#include "fraction.h"
#include "treepoint.h"
#include <string>

class Operation{
private:
	TreePoint *root;
	Fraction ans;

public:
	Operation();
	~Operation();
	Operation(const Operation &from);
	std::string print();
	Fraction getans();
};

#endif
