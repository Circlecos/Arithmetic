/******************************************************************************
文件名： operation.h
作者：Circle  日期：2017/02/04
描述："operation"类
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
