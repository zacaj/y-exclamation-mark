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
char* inttoString ( int i );
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
	return *a;
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

char* inttoString ( int i )
{
	char* str;
	str=malloc(10);
	sprintf(str,"%i",i);
	return str;
}

int startint ( int nArgument )
{
	int success;
	int i;
	int t_int0_0 = 0;
	int t_int41_4 = 4;
	char* t_string67r_string_str_;

	int_equal_int( &i, t_int41_4 );
	t_string67r_string_str_ =  inttoString( i );
	printstring( t_string67r_string_str_ );
	return t_int0_0;
}

void printHelloWorlds (  )
{
}

void getNumberFromintintoint ( int number, int *out )
{
	int t_int24r_int_ret_loadModelFrom_;
	int t_int30r_int_;
	int t_int66r_int_sum_;
	int t_int69_3 = 3;
	int t_int7r_int_product_;
	char* t_string24 = "foo";
	char* t_string41r_string_path_pathToModel_;
	char* t_string78 = "bar";

	t_string41r_string_path_pathToModel_ =  pathToModelstringstring( t_string24, t_string78 );
	t_int24r_int_ret_loadModelFrom_ =  loadModelFromstring( t_string41r_string_path_pathToModel_ );
	t_int66r_int_sum_ =  int_plus_int( t_int69_3, t_int24r_int_ret_loadModelFrom_ );
	t_int30r_int_ =  f_C_int_D_( t_int66r_int_sum_ );
	t_int7r_int_product_ =  int_asterisk_int( t_int30r_int_, number );
	int_equal_int( &*out, t_int7r_int_product_ );
}

char* pathToModelstringstring ( char* text, char* text2 )
{
	char* path;
	char* t_string44 = "c:/model.s3d\n";

	printstring( text );
	printstring( text2 );
	printstring( text2 );
	string_equal_string( &path, t_string44 );
	return path;
}

void printHelloWorld (  )
{
	char* t_string9 = "Hello world\n";

	printstring( t_string9 );
}

int loadModelFromstring ( char* path )
{
	int ret;
	int t_int89_1 = 1;

	int_equal_int( &ret, t_int89_1 );
	printstring( path );
	return ret;
}

void empty (  )
{
	int i;
	int shouldPrintEnd;
	unsigned char t_bool87r_bool_isLess_;
	int t_int23r_int_sum_;
	int t_int2_1 = 1;
	int t_int85_0 = 0;
	int t_int93_1 = 1;
	int t_int95_1 = 1;
	int timesToPrint;

	getNumberFromintintoint( t_int2_1, &timesToPrint );
	int_equal_int( &shouldPrintEnd, t_int95_1 );
	int_equal_int( &i, t_int85_0 );
	lt_branch90:;
	t_bool87r_bool_isLess_ =  int_less_int( i, timesToPrint );
	branch_t t_branch90 = whilebool( t_bool87r_bool_isLess_ );
	if( t_branch90.labelId==0 )
	{
		int t_int22_4 = 4;
		int t_int48_0 = 0;
		int t_int57_5 = 5;
		int t_int58_2 = 2;
		int t_int80_1 = 1;
		char* t_string38 = "";

		printHelloWorld( );
		switch( i )
		{
		case 0: case0t_sw57i:
		{
			char* t_string0 = "Start\n";

			printstring( t_string0 );
			goto defaultt_sw57i;
			break;
		}
		case 2: case2t_sw57i:
		{
			char* t_string18 = "2\n";

			printstring( t_string18 );
			break;
		}
		case 1: case1t_sw57i:
		{
			unsigned char t_bool98r_bool_isLess_;
			int t_int96_1 = 1;
			int t_int9_4 = 4;

			lt_branch58:;
			t_bool98r_bool_isLess_ =  int_less_int( shouldPrintEnd, t_int96_1 );
			branch_t t_branch58 = ifbool( t_bool98r_bool_isLess_ );
			if( t_branch58.labelId==0 )
			{
				char* t_string89 = "Hello\n";

				printstring( t_string89 );
			}
			else if( t_branch58.labelId==1 )
			{
				char* t_string98 = "Goodbye\n";

				printstring( t_string98 );
			}
			if( t_branch58.repeat!=0 ) goto lt_branch58;
			goto case4t_sw57i;
			break;
		}
		case 5: case5t_sw57i:
		{
			char* t_string72 = "5\n";

			goto case4t_sw57i;
			printstring( t_string72 );
			break;
		}
		case 4: case4t_sw57i:
		{
			char* t_string38 = "4\n";

			printstring( t_string38 );
			break;
		}
		default: defaultt_sw57i:
		{
			char* t_string92 = "?\n";

			printstring( t_string92 );
			}
		}
		printstring( t_string38 );
		t_int23r_int_sum_ =  int_plus_int( i, t_int93_1 );
		int_equal_int( &i, t_int23r_int_sum_ );
	}
	if( t_branch90.repeat!=0 ) goto lt_branch90;
	return;
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
		int t_int79_1 = 1;

		return (branch_t){0 /* default */,1};
	}
	return (branch_t){2 /* none */,0};
}

