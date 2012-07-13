#include <stdio.h>

typedef struct 
{
	int labelId;
	unsigned char repeat;
} branch_t;

int int_plus_int ( int a, int b );
int int_asterisk_int ( int a, int b );
int int_equal_int ( int *a, int b );
void string_equal_string ( char* *a, char* b );
unsigned char int_less_int ( int a, int b );
void printstring ( char* str );
branch_t ifbool ( unsigned char is );
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
branch_t whilebool ( unsigned char is );


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

int int_equal_int ( int *a, int b )
{
	*a=b;
	return a;
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

int startint ( int nArgument )
{
	int success;
	int t_int41_0 = 0;

	printHelloWorlds( );
	return t_int41_0;
}

void printHelloWorlds (  )
{
	int i;
	int shouldPrintEnd;
	unsigned char t_bool16r_bool_isLess_;
	unsigned char t_bool58r_bool_isLess_;
	int t_int0_0 = 0;
	int t_int21_ = -1;
	int t_int34_1 = 1;
	int t_int67_1 = 1;
	int t_int69_1 = 1;
	int t_int78r_int_sum_;
	char* t_string53 = "Real end\n";
	int timesPrinted;
	int timesToPrint;

	getNumberFromintintoint( t_int67_1, &timesToPrint );
	int_equal_int( &shouldPrintEnd, t_int34_1 );
	lt_branch69:;
	int_equal_int( &i, t_int0_0 );
	t_bool58r_bool_isLess_ =  int_less_int( i, timesToPrint );
	branch_t t_branch69 = whilebool( t_bool58r_bool_isLess_ );
	if( t_branch69.labelId==0 )
	{
		int t_int4_5 = 5;
		int t_int53_4 = 4;
		int t_int5_0 = 0;
		int t_int61_1 = 1;
		int t_int81_2 = 2;

		printHelloWorld( );
		switch( i )
		{
		case 0: case0t_sw42i:
		{
			char* t_string45 = "Start\n";

			printstring( t_string45 );
			goto defaultt_sw42i;
			break;
		}
		case 2: case2t_sw42i:
		{
			char* t_string27 = "2\n";

			printstring( t_string27 );
			break;
		}
		case 1: case1t_sw42i:
		{
			unsigned char t_bool95r_bool_isLess_;
			int t_int91_1 = 1;
			int t_int91_4 = 4;

			lt_branch44:;
			t_bool95r_bool_isLess_ =  int_less_int( shouldPrintEnd, t_int91_1 );
			branch_t t_branch44 = ifbool( t_bool95r_bool_isLess_ );
			if( t_branch44.labelId==0 )
			{
				char* t_string27 = "Hello\n";

				printstring( t_string27 );
			}
			else if( t_branch44.labelId==1 )
			{
				char* t_string36 = "Goodbye\n";

				printstring( t_string36 );
			}
			if( t_branch44.repeat!=0 ) goto lt_branch44;
			goto case4t_sw42i;
			break;
		}
		case 5: case5t_sw42i:
		{
			char* t_string2 = "5\n";

			goto case4t_sw42i;
			printstring( t_string2 );
			break;
		}
		case 4: case4t_sw42i:
		{
			char* t_string92 = "4\n";

			printstring( t_string92 );
			break;
		}
		default: defaultt_sw42i:
		{
			char* t_string82 = "?\n";

			printstring( t_string82 );
			}
		}
	}
	if( t_branch69.repeat!=0 ) goto lt_branch69;
	return ;
	int_equal_int( &timesPrinted, t_int21_ );
	lt_branch16:;
	t_bool16r_bool_isLess_ =  int_less_int( timesPrinted, timesToPrint );
	branch_t t_branch16 = whilebool( t_bool16r_bool_isLess_ );
	if( t_branch16.labelId==0 )
	{
		int t_int26r_int_sum_;
		int t_int33_5 = 5;
		int t_int64_4 = 4;
		int t_int67_1 = 1;
		int t_int69_2 = 2;
		int t_int71_0 = 0;
		int t_int95_1 = 1;

		printHelloWorld( );
		t_int26r_int_sum_ =  int_plus_int( timesPrinted, t_int95_1 );
		int_equal_int( &timesPrinted, t_int26r_int_sum_ );
		switch( timesPrinted )
		{
		case 0: case0t_sw81timesPrinted:
		{
			char* t_string38 = "Start\n";

			printstring( t_string38 );
			goto defaultt_sw81timesPrinted;
			break;
		}
		case 2: case2t_sw81timesPrinted:
		{
			char* t_string12 = "2\n";

			printstring( t_string12 );
			break;
		}
		case 1: case1t_sw81timesPrinted:
		{
			unsigned char t_bool35r_bool_isLess_;
			int t_int22_4 = 4;
			int t_int99_1 = 1;

			lt_branch98:;
			t_bool35r_bool_isLess_ =  int_less_int( shouldPrintEnd, t_int99_1 );
			branch_t t_branch98 = ifbool( t_bool35r_bool_isLess_ );
			if( t_branch98.labelId==0 )
			{
				char* t_string3 = "Hello\n";

				printstring( t_string3 );
			}
			else if( t_branch98.labelId==1 )
			{
				char* t_string11 = "Goodbye\n";

				printstring( t_string11 );
			}
			if( t_branch98.repeat!=0 ) goto lt_branch98;
			goto case4t_sw81timesPrinted;
			break;
		}
		case 5: case5t_sw81timesPrinted:
		{
			char* t_string73 = "5\n";

			goto case4t_sw81timesPrinted;
			printstring( t_string73 );
			break;
		}
		case 4: case4t_sw81timesPrinted:
		{
			char* t_string41 = "4\n";

			printstring( t_string41 );
			break;
		}
		default: defaultt_sw81timesPrinted:
		{
			char* t_string11 = "?\n";

			printstring( t_string11 );
			}
		}
	}
	if( t_branch16.repeat!=0 ) goto lt_branch16;
	printstring( t_string53 );
	return ;
}

void getNumberFromintintoint ( int number, int *out )
{
	int t_int34r_int_product_;
	int t_int68_3 = 3;
	int t_int68r_int_ret_loadModelFrom_;
	int t_int81r_int_;
	int t_int84r_int_sum_;
	char* t_string44 = "bar";
	char* t_string47 = "foo";
	char* t_string99r_string_path_pathToModel_;

	t_string99r_string_path_pathToModel_ =  pathToModelstringstring( t_string47, t_string44 );
	t_int68r_int_ret_loadModelFrom_ =  loadModelFromstring( t_string99r_string_path_pathToModel_ );
	t_int84r_int_sum_ =  int_plus_int( t_int68_3, t_int68r_int_ret_loadModelFrom_ );
	t_int81r_int_ =  f_C_int_D_( t_int84r_int_sum_ );
	t_int34r_int_product_ =  int_asterisk_int( t_int81r_int_, number );
	int_equal_int( &*out, t_int34r_int_product_ );
}

char* pathToModelstringstring ( char* text, char* text2 )
{
	char* path;
	char* t_string62 = "c:/model.s3d\n";

	printstring( text );
	printstring( text2 );
	printstring( text2 );
	string_equal_string( &path, t_string62 );
	return path;
}

void printHelloWorld (  )
{
	char* t_string86 = "Hello world\n";

	printstring( t_string86 );
}

int loadModelFromstring ( char* path )
{
	int ret;
	int t_int75_1 = 1;

	int_equal_int( &ret, t_int75_1 );
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

branch_t whilebool ( unsigned char is )
{
	if(is)
	{
		int t_int33_1 = 1;

		return (branch_t){0 /* default */,1};
	}
	return (branch_t){2 /* none */,0};
}

