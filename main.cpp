#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "operation.h"
#include "fraction.h"

int main(void)
{
	srand((unsigned) (time(NULL)));
	Operation *a;
	a=new Operation();
	a->print();
	(a->getans()).print(); 
	
	delete a;
	return 0;
}


