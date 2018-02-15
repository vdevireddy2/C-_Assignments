#include <iostream>

/*
** This class is invokes a method asm with ASM instructions in it's constructor
** which will find out whether the object/variable is allocated on stack or heap.
** This works only on x86 processors such as intel ..etc because these
** ASM instructions are specific to processor.
*/

class A
{
public:
	void checkMemory();
};

void A::checkMemory()
{
	int x;

	asm("movq %1, %%rax;"       //%1 contains 'this' object. i.e. class object
		"cmpq %%rsp, %%rax;"    // compare class object with stack pointer which has x
		"jbe Heap;"             // if both are equal then jump to Heap
		"movl $1,%0;"           /* if not then assign 1 to x (%0 contains x);
								*   Newly created object is form stack */
		"jmp Done;"             // goto Done
		"Heap:"                 // Heap:
		"movl $0,%0;"           // x = 0 ; Newly created object is from heap
		"Done:"                // Done
		: "=r" (x)             // output is x
		: "r" (this)           // input is 'this' object
	);

	std::cout << (x ? " Stack " : " Heap ") << std::endl;
}



int main()
{
	A a;
	a.checkMemory(a);
	A *b = new A;
	b->checkMemory(*b);
	A c;
	c.checkMemory(c);

	return 0;
}
