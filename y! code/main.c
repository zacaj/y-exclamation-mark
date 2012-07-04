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

int startint ( int nArgument )
{
	int success;
	int t_int67_0 = 0;

	printHelloWorlds( );
	return t_int67_0;
}

void printHelloWorlds (  )
{
	int shouldPrintEnd;
	unsigned char t_bool78r_bool_isLess_;
	int t_int0_ = -1;
	int t_int34_1 = 1;
	int t_int69_1 = 1;
	char* t_string21 = "Real end\n";
	int timesPrinted;
	int timesToPrint;

	getNumberFromintintoint( t_int34_1, &timesToPrint );
	int_equal_int( &timesPrinted, t_int0_ );
	int_equal_int( &shouldPrintEnd, t_int69_1 );
	lt_branch22:;
	t_bool78r_bool_isLess_ =  int_less_int( timesPrinted, timesToPrint );
	branch_t t_branch22 = whilebool( t_bool78r_bool_isLess_ );
	if( t_branch22.labelId==0 )
	{
		int t_int4_5 = 5;
		int t_int53_4 = 4;
		int t_int58_1 = 1;
		int t_int5_0 = 0;
		int t_int61_1 = 1;
		int t_int62r_int_sum_;
		int t_int81_2 = 2;

		printHelloWorld( );
		t_int62r_int_sum_ =  int_plus_int( timesPrinted, t_int58_1 );
		int_equal_int( &timesPrinted, t_int62r_int_sum_ );
		switch( timesPrinted )
		{
		case 0: case0t_sw38timesPrinted:
		{
			char* t_string45 = "Start\n";

			printstring( t_string45 );
			goto defaultt_sw38timesPrinted;
			break;
		}
		case 2: case2t_sw38timesPrinted:
		{
			char* t_string27 = "2\n";

			printstring( t_string27 );
			break;
		}
		case 1: case1t_sw38timesPrinted:
		{
			unsigned char t_bool42r_bool_isLess_;
			int t_int91_1 = 1;
			int t_int91_4 = 4;

			lt_branch92:;
			t_bool42r_bool_isLess_ =  int_less_int( shouldPrintEnd, t_int91_1 );
			branch_t t_branch92 = ifbool( t_bool42r_bool_isLess_ );
			if( t_branch92.labelId==0 )
			{
				char* t_string27 = "Hello\n";

				printstring( t_string27 );
			}
			else if( t_branch92.labelId==1 )
			{
				char* t_string36 = "Goodbye\n";

				printstring( t_string36 );
			}
			if( t_branch92.repeat!=0 ) goto lt_branch92;
			goto case4t_sw38timesPrinted;
			break;
		}
		case 5: case5t_sw38timesPrinted:
		{
			char* t_string2 = "5\n";

			goto case4t_sw38timesPrinted;
			printstring( t_string2 );
			break;
		}
		case 4: case4t_sw38timesPrinted:
		{
			char* t_string92 = "4\n";

			printstring( t_string92 );
			break;
		}
		default: defaultt_sw38timesPrinted:
		{
			char* t_string82 = "?\n";

			printstring( t_string82 );
			}
		}
	}
	if( t_branch22.repeat!=0 ) goto lt_branch22;
	printstring( t_string21 );
}

void getNumberFromintintoint ( int number, int *out )
{
	int t_int16_3 = 3;
	int t_int30r_int_ret_loadModelFrom_;
	int t_int6r_int_;
	int t_int73r_int_product_;
	int t_int77r_int_sum_;
	char* t_string18 = "foo";
	char* t_string4r_string_path_pathToModel_;
	char* t_string95 = "bar";

	t_string4r_string_path_pathToModel_ =  pathToModelstringstring( t_string18, t_string95 );
	t_int30r_int_ret_loadModelFrom_ =  loadModelFromstring( t_string4r_string_path_pathToModel_ );
	t_int77r_int_sum_ =  int_plus_int( t_int16_3, t_int30r_int_ret_loadModelFrom_ );
	t_int6r_int_ =  f_C_int_D_( t_int77r_int_sum_ );
	t_int73r_int_product_ =  int_asterisk_int( t_int6r_int_, number );
	int_equal_int( &*out, t_int73r_int_product_ );
}

char* pathToModelstringstring ( char* text, char* text2 )
{
	char* path;
	char* t_string9 = "c:/model.s3d\n";

	printstring( text );
	printstring( text2 );
	printstring( text2 );
	string_equal_string( &path, t_string9 );
	return path;
}

void printHelloWorld (  )
{
	char* t_string57 = "Hello world\n";

	printstring( t_string57 );
}

int loadModelFromstring ( char* path )
{
	int ret;
	int t_int72_1 = 1;

	int_equal_int( &ret, t_int72_1 );
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

