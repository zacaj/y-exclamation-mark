#include <stdio.h>

typedef struct 
{
	int labelId;
	unsigned char repeat;
} branch_t;

int int_plus_int ( int a, int b );
int int_asterisk_int ( int a, int b );
void int_equal_int ( int *a, int b );
unsigned char int_less_int ( int a, int b );
void printstring ( char* str );
branch_t ifint_less_int ( int is, int times );
int startint ( int nArgument );
void printHelloWorld (  );
int loadModelFromstring ( char* path );
void printHelloWorlds (  );
void getNumberFromintintoint ( int number, int *out );
char* pathToModel (  );
unsigned char f_Q_bool_Q_ ( unsigned char a );
branch_t f_Q_branch_Q_ ( branch_t a );
int f_Q_int_Q_ ( int a );
char* f_Q_string_Q_ ( char* a );


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

branch_t ifint_less_int ( int is, int times )
{
	if(is==0)
	{
		return (branch_t){3 /* start */,0};
	}
	if(is<times)
	{
		return (branch_t){0 /* default */,0};
	}
	if(is>=times)
	{
		return (branch_t){2 /* else */,0};
	}
}

int startint ( int nArgument )
{
	int success;
	int t_int41_0 = 0;

	printHelloWorlds( );
	return t_int41_0;
	return success;
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

	int_equal_int( &ret, t_int34_2 );
	printstring( path );
	return ret;
	return ret;
}

void printHelloWorlds (  )
{
	int t_int0_4 = 4;
	int t_int24_1 = 1;
	int t_int69_ = -1;
	int t_int78r_int_sum_;
	int timesPrinted;
	int timesToPrint;

	getNumberFromintintoint( t_int0_4, &timesToPrint );
	int_equal_int( &timesPrinted, t_int69_ );
loop:
	printHelloWorld( );
	t_int78r_int_sum_ =  int_plus_int( timesPrinted, t_int24_1 );
	int_equal_int( &timesPrinted, t_int78r_int_sum_ );
	branch_t t_branch54 = ifint_less_int( timesPrinted, timesToPrint );
	if( t_branch54.labelId==0 )
	{
		int t_int64_17 = 17;

		{
			goto loop;
		}
	}
	else if( t_branch54.labelId==2 )
	{
		char* t_string5 = "End\n";

		printstring( t_string5 );
	}
	else if( t_branch54.labelId==3 )
	{
		int t_int81_17 = 17;
		char* t_string45 = "Start\n";

		printstring( t_string45 );
		{
			goto loop;
		}
	}
}

void getNumberFromintintoint ( int number, int *out )
{
	int t_int16r_int_product_;
	int t_int27_3 = 3;
	int t_int29r_int_sum_;
	int t_int41r_int_ret_loadModelFrom_;
	int t_int78r_int_;
	char* t_string23r_string_path_pathToModel;

	t_string23r_string_path_pathToModel =  pathToModel( );
	t_int41r_int_ret_loadModelFrom_ =  loadModelFromstring( t_string23r_string_path_pathToModel );
	t_int29r_int_sum_ =  int_plus_int( t_int27_3, t_int41r_int_ret_loadModelFrom_ );
	t_int78r_int_ =  f_Q_int_Q_( t_int29r_int_sum_ );
	t_int16r_int_product_ =  int_asterisk_int( t_int78r_int_, number );
	int_equal_int( &*out, t_int16r_int_product_ );
}

char* pathToModel (  )
{
	char* path;
	char* t_string84 = "c:/model.s3d\n";

	return t_string84;
	return path;
}

unsigned char f_Q_bool_Q_ ( unsigned char a )
{
	return a;
}

branch_t f_Q_branch_Q_ ( branch_t a )
{
	return a;
}

int f_Q_int_Q_ ( int a )
{
	return a;
}

char* f_Q_string_Q_ ( char* a )
{
	return a;
}

