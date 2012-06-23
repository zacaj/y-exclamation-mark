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
branch_t ifbool ( unsigned char is );
branch_t loopinttestint ( int is, int times );
int startint ( int nArgument );
void printHelloWorld (  );
int loadModelFromstring ( char* path );
void printHelloWorlds (  );
void getNumberFromintintoint ( int number, int *out );
char* pathToModel (  );
 f_Q_Label_Q_ (  a );
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

branch_t loopinttestint ( int is, int times )
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
		return (branch_t){1 /* else */,0};
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
	unsigned char t_bool62r_bool_isLess_;
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
	t_bool62r_bool_isLess_ =  int_less_int( timesPrinted, timesToPrint );
	branch_t t_branch29 = ifbool( t_bool62r_bool_isLess_ );
	if( t_branch29.labelId==0 )
	{
		goto loop;
	}
	else if( t_branch29.labelId==1 )
	{
		char* t_string64 = "End\n";

		printstring( t_string64 );
	}
	else if( t_branch29.labelId==3 )
	{
		char* t_string5 = "Start\n";

		printstring( t_string5 );
		goto loop;
	}
}

void getNumberFromintintoint ( int number, int *out )
{
	int t_int31r_int_sum_;
	int t_int44r_int_product_;
	int t_int45_3 = 3;
	int t_int76r_int_ret_loadModelFrom_;
	int t_int8r_int_;
	char* t_string66r_string_path_pathToModel;

	t_string66r_string_path_pathToModel =  pathToModel( );
	t_int76r_int_ret_loadModelFrom_ =  loadModelFromstring( t_string66r_string_path_pathToModel );
	t_int31r_int_sum_ =  int_plus_int( t_int45_3, t_int76r_int_ret_loadModelFrom_ );
	t_int8r_int_ =  f_Q_int_Q_( t_int31r_int_sum_ );
	t_int44r_int_product_ =  int_asterisk_int( t_int8r_int_, number );
	int_equal_int( &*out, t_int44r_int_product_ );
}

char* pathToModel (  )
{
	char* path;
	char* t_string70 = "c:/model.s3d\n";

	return t_string70;
	return path;
}

 f_Q_Label_Q_ (  a )
{
	return a;
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

