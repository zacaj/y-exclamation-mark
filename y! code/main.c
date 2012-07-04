#include <stdio.h>

typedef struct 
{
	int labelId;
	unsigned char repeat;
} branch_t;

int int_plus_int ( int a, int b );
int int_asterisk_int ( int a, int b );
void int_equal_int ( int *a, int b );
void string_equal_string ( char* *a, char* b );
unsigned char int_less_int ( int a, int b );
void printstring ( char* str );
branch_t ifbool ( unsigned char is );
branch_t whilebool ( unsigned char is );
char* f_C_int_D_int ( int i );
int startint ( int nArgument );
void printHelloWorlds (  );
void getNumberFromintintoint ( int number, int *out );
char* pathToModelstringstring ( char* text, char* text2 );
void printHelloWorld (  );
int loadModelFromstring ( char* path );
void empty (  );
int f_C_Label_D_ ( int a );
unsigned char f_C_bool_D_ ( unsigned char a );
branch_t f_C_branch_D_ ( branch_t a );
int f_C_int_D_ ( int a );
char* f_C_string_D_ ( char* a );
void switchint ( int var );
void caseint ( int var );
void switchEnd (  );
void caseEnd (  );
void continue_ (  );
void continuedefault (  );
void continuecaseint ( int i );
void default_ (  );


int main(int argc,char **argv)
{
	return startint(argc);
}

int int_plus_int ( int a, int b )
{
	int sum;
	sum=a+b;
	return sum;
}

int int_asterisk_int ( int a, int b )
{
	int product;
	product=a*b;
	return product;
}

void int_equal_int ( int *a, int b )
{
	*a=b;
}

void string_equal_string ( char* *a, char* b )
{
	*a=malloc(strlen(b));
	strcpy(*a,b);
}

unsigned char int_less_int ( int a, int b )
{
	unsigned char isLess;
	isLess=a<b;
	return isLess;
}

void printstring ( char* str )
{
	printf(str);
}

branch_t ifbool ( unsigned char is )
{
	if(is)
	{
		return (branch_t){0 /* default */,0};
	}
	else
	{
		return (branch_t){1 /* else */,0};
	}
}

branch_t whilebool ( unsigned char is )
{
	if(is)
	{
		int t_int41_1 = 1;

		return (branch_t){0 /* default */,1};
	}
	return (branch_t){2 /* none */,0};
}

char* f_C_int_D_int ( int i )
{
	char *ret=malloc(10);
	sprintf(ret,"%i",i);
	return ret;
}

int startint ( int nArgument )
{
	int success;
	int t_int67_0 = 0;

	printHelloWorlds( );
	return t_int67_0;
}

void printHelloWorlds (  )
{
	int i;
	int shouldPrintEnd;
	unsigned char t_bool78r_bool_isLess_;
	int t_int0_1 = 1;
	int t_int34_1 = 1;
	int t_int69_ = -1;
	int t_int95_0 = 0;
	char* t_string18 = "Real end\n";
	int timesPrinted;
	int timesToPrint;

	getNumberFromintintoint( t_int34_1, &timesToPrint );
	int_equal_int( &shouldPrintEnd, t_int0_1 );
	int_equal_int( &timesPrinted, t_int69_ );
	lt_branch86:;
	t_bool78r_bool_isLess_ =  int_less_int( timesPrinted, timesToPrint );
	branch_t t_branch86 = whilebool( t_bool78r_bool_isLess_ );
	if( t_branch86.labelId==0 )
	{
		int t_int53_5 = 5;
		int t_int58_1 = 1;
		int t_int61_2 = 2;
		int t_int62r_int_sum_;
		int t_int81_0 = 0;
		int t_int82_4 = 4;
		int t_int95_1 = 1;
		char* t_string45r_string_;

		printHelloWorld( );
		t_int62r_int_sum_ =  int_plus_int( timesPrinted, t_int58_1 );
		int_equal_int( &timesPrinted, t_int62r_int_sum_ );
		t_string45r_string_ =  f_C_int_D_int( timesPrinted );
		printstring( t_string45r_string_ );
		switch( timesPrinted )
		{
		case 0: case0t_sw75timesPrinted:
		{
			char* t_string27 = "Start\n";

			printstring( t_string27 );
			goto defaultt_sw75timesPrinted;
			break;
		}
		case 2: case2t_sw75timesPrinted:
		{
			char* t_string91 = "2\n";

			printstring( t_string91 );
			break;
		}
		case 1: case1t_sw75timesPrinted:
		{
			unsigned char t_bool36r_bool_isLess_;
			int t_int2_4 = 4;
			int t_int42_1 = 1;

			lt_branch33:;
			t_bool36r_bool_isLess_ =  int_less_int( shouldPrintEnd, t_int42_1 );
			branch_t t_branch33 = ifbool( t_bool36r_bool_isLess_ );
			if( t_branch33.labelId==0 )
			{
				char* t_string91 = "Hello\n";

				printstring( t_string91 );
			}
			else if( t_branch33.labelId==1 )
			{
				char* t_string4 = "Goodbye\n";

				printstring( t_string4 );
			}
			if( t_branch33.repeat!=0 ) goto lt_branch33;
			goto case4t_sw75timesPrinted;
			break;
		}
		case 5: case5t_sw75timesPrinted:
		{
			char* t_string92 = "5\n";

			goto case4t_sw75timesPrinted;
			printstring( t_string92 );
			break;
		}
		case 4: case4t_sw75timesPrinted:
		{
			char* t_string21 = "4\n";

			printstring( t_string21 );
			break;
		}
		default: defaultt_sw75timesPrinted:
		{
			char* t_string16 = "?\n";

			printstring( t_string16 );
			}
		}
	}
	if( t_branch86.repeat!=0 ) goto lt_branch86;
	printstring( t_string18 );
	return ;
	int_equal_int( &i, t_int95_0 );
	{
		int t_int11_5 = 5;
		int t_int33_4 = 4;
		int t_int47_0 = 0;
		int t_int69_1 = 1;
		int t_int71_2 = 2;

		printHelloWorld( );
		switch( i )
		{
		case 0: case0t_sw69i:
		{
			char* t_string26 = "Start\n";

			printstring( t_string26 );
			goto defaultt_sw69i;
			break;
		}
		case 2: case2t_sw69i:
		{
			char* t_string38 = "2\n";

			printstring( t_string38 );
			break;
		}
		case 1: case1t_sw69i:
		{
			unsigned char t_bool99r_bool_isLess_;
			int t_int12_1 = 1;
			int t_int3_4 = 4;

			lt_branch42:;
			t_bool99r_bool_isLess_ =  int_less_int( shouldPrintEnd, t_int12_1 );
			branch_t t_branch42 = ifbool( t_bool99r_bool_isLess_ );
			if( t_branch42.labelId==0 )
			{
				char* t_string35 = "Hello\n";

				printstring( t_string35 );
			}
			else if( t_branch42.labelId==1 )
			{
				char* t_string94 = "Goodbye\n";

				printstring( t_string94 );
			}
			if( t_branch42.repeat!=0 ) goto lt_branch42;
			goto case4t_sw69i;
			break;
		}
		case 5: case5t_sw69i:
		{
			char* t_string22 = "5\n";

			goto case4t_sw69i;
			printstring( t_string22 );
			break;
		}
		case 4: case4t_sw69i:
		{
			char* t_string73 = "4\n";

			printstring( t_string73 );
			break;
		}
		default: defaultt_sw69i:
		{
			char* t_string64 = "?\n";

			printstring( t_string64 );
			}
		}
	}
	return ;
}

void getNumberFromintintoint ( int number, int *out )
{
	int t_int41_3 = 3;
	int t_int55r_int_;
	int t_int55r_int_ret_loadModelFrom_;
	int t_int67r_int_sum_;
	int t_int74r_int_product_;
	char* t_string11 = "foo";
	char* t_string36r_string_path_pathToModel_;
	char* t_string53 = "bar";

	t_string36r_string_path_pathToModel_ =  pathToModelstringstring( t_string11, t_string53 );
	t_int55r_int_ret_loadModelFrom_ =  loadModelFromstring( t_string36r_string_path_pathToModel_ );
	t_int67r_int_sum_ =  int_plus_int( t_int41_3, t_int55r_int_ret_loadModelFrom_ );
	t_int55r_int_ =  f_C_int_D_( t_int67r_int_sum_ );
	t_int74r_int_product_ =  int_asterisk_int( t_int55r_int_, number );
	int_equal_int( &*out, t_int74r_int_product_ );
}

char* pathToModelstringstring ( char* text, char* text2 )
{
	char* path;
	char* t_string28 = "c:/model.s3d\n";

	printstring( text );
	printstring( text2 );
	printstring( text2 );
	string_equal_string( &path, t_string28 );
	return path;
}

void printHelloWorld (  )
{
	char* t_string46 = "Hello world\n";

	printstring( t_string46 );
}

int loadModelFromstring ( char* path )
{
	int ret;
	int t_int62_1 = 1;

	int_equal_int( &ret, t_int62_1 );
	printstring( path );
	return ret;
}

void empty (  )
{
}

int f_C_Label_D_ ( int a )
{
	return a;
}

unsigned char f_C_bool_D_ ( unsigned char a )
{
	return a;
}

branch_t f_C_branch_D_ ( branch_t a )
{
	return a;
}

int f_C_int_D_ ( int a )
{
	return a;
}

char* f_C_string_D_ ( char* a )
{
	return a;
}

void switchint ( int var )
{
}

void caseint ( int var )
{
}

void switchEnd (  )
{
}

void caseEnd (  )
{
}

void continue_ (  )
{
}

void continuedefault (  )
{
}

void continuecaseint ( int i )
{
}

void default_ (  )
{
}

