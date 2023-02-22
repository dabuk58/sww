#include <iostream>
#include "obsluga.h"
#include "wymiana.h"

using namespace std;

int main()
{
	unique_ptr<menu> Start(new menu);
	Start->wybor();
	return 0;
}