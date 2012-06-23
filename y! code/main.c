#include <stdio.h>

typedef struct 
{
	int labelId;
	unsigned char repeat;
} branch_t;

int int_plus_int ( int a, int b );
int int_asterisk_int ( int a, int b );
void string_equal_string ( char* *a, char* b );
unsigned char int_less_int ( int a, int b );
void printstring ( char* str );
branch_t ifbool ( unsigned char is );
int startint ( int nArgument );
void printHelloWorld (  );
int loadModelFromstring ( char* path );
void printHelloWorlds (  );
void getNumberFromintintoint ( int number, int *out );
int f_C_Label_D_ ( int a );
unsigned char f_C_bool_D_ ( unsigned char a );
branch_t f_C_branch_D_ ( branch_t a );
int f_C_int_D_ ( int a );
char* f_C_string_D_ ( char* a );


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

void string_equal_string ( char* *a, char* b )
{
	a=malloc(strlen(b));
	strcpy(a,b);
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

void printHelloWorld (  )
{
	char* t_string67 = "Hello world\n";

	printstring( t_string67 );
}

int loadModelFromstring ( char* path )
{
	int ret;
	int t_int34_2 = 2;

	{//inline call to int_equal_int
		int a = ret;
		int b = t_int34_2;
		*a=b;
		t_Label43:
	}
	printstring( path );
	return ret;
}

void printHelloWorlds (  )
{
	unsigned char t_bool64r_bool_isLess_;
	int t_int0_4 = 4;
	int t_int24_1 = 1;
	int t_int69_ = -1;
	int t_int78r_int_sum_;
	int timesPrinted;
	int timesToPrint;

	getNumberFromintintoint( t_int0_4, &timesToPrint );
	{//inline call to int_equal_int
		int a = timesPrinted;
		int b = t_int69_;
		*a=b;
		t_Label23:
	}
loop:
	printHelloWorld( );
	t_int78r_int_sum_ =  int_plus_int( timesPrinted, t_int24_1 );
	{//inline call to int_equal_int
		int a = timesPrinted;
		int b = t_int78r_int_sum_;
		*a=b;
		t_Label87:
	}
	t_bool64r_bool_isLess_ =  int_less_int( timesPrinted, timesToPrint );
	branch_t t_branch14 = ifbool( t_bool64r_bool_isLess_ );
	if( t_branch14.labelId==0 )
	{
		goto loop;
	}
	else if( t_branch14.labelId==1 )
	{
		char* t_string5 = "End\n";

		printstring( t_string5 );
	}
}

void getNumberFromintintoint ( int number, int *out )
{
	int t_int26r_int_product_;
	int t_int39r_int_;
	int t_int44r_int_sum_;
	int t_int45_3 = 3;
	int t_int8r_int_ret_loadModelFrom_;
	char* t_string27 = "bar";
	char* t_string31inline_r_string_path_pathToModel_;
	char* t_string81 = "foo";

	{//inline call to pathToModelstringstring
		char* t_string48;
		char* text = t_string81;
		char* text2 = t_string27;
		char* t_string93 = "c:/model.s3d\n";

		printstring( text );
		printstring( text2 );
		printstring( text2 );
		string_equal_string( &path, t_string93 );
		t_string48 = path;
}
		t_Label3:
		t_string31inline_r_string_path_pathToModel_ = t_string48;
	}
	t_int8r_int_ret_loadModelFrom_ =  loadModelFromstring( t_string31inline_r_string_path_pathToModel_ );
	t_int44r_int_sum_ =  int_plus_int( t_int45_3, t_int8r_int_ret_loadModelFrom_ );
	t_int39r_int_ =  f_C_int_D_( t_int44r_int_sum_ );
	t_int26r_int_product_ =  int_asterisk_int( t_int39r_int_, number );
	{//inline call to int_equal_int
		int a = out;
		int b = t_int26r_int_product_;
		*a=b;
		t_Label0:
	}
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

