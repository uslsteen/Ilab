#include "STRING.h"

using namespace ADM;

int main()
{
	String a("Hello, Im a bad guy!\n");
	String b(a);

	String c = "HHHHHH\n";

	a.print();
	c.print();

	a = "Papa roach - its the best rock group!!!\n";
	c += "We are the hero our time!"; 

	a.print();
	c.print();

	return 0;
}