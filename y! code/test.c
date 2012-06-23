#include <stdio.h>

typedef struct
{
	unsigned int labelId;
	unsigned char repeat;
} branch_t;

branch_t test()
{
		return (branch_t){4,2};
}

int main()
{
	branch_t branch=test();
	printf("%i,%i\n",branch.labelId,branch.repeat);
	loop:
	{
		loop:
		goto loop;
	}
}