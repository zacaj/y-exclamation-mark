#include <stdio.h>

int int_plus_int ( int a, int b );
int int_asterisk_int ( int a, int b );
void int_equal_int ( int *a, int b );
unsigned char int_less_int ( int a, int b );
void printstring ( char* str );
void goToLineint ( int lineNumber );
void ifbool ( unsigned char is );
int startint ( int nArgument );
void printHelloWorld (  );
int loadModelFromstring ( char* path );
void printHelloWorlds (  );
void getNumberFromintintoint ( int number, int *out );
char* pathToModel (  );


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

void goToLineint ( int lineNumber )
{
}

void ifbool ( unsigned char is )
{
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
	unsigned char t_bool58r_bool_isLess_;
	unsigned char t_bool62r_bool_isLess_;
	int t_int0_4 = 4;
	int t_int24_1 = 1;
	int t_int69_0 = 0;
	int t_int78r_int_sum_;
	int timesPrinted;
	int timesToPrint;

	getNumberFromintintoint( t_int0_4, &timesToPrint );
	int_equal_int( &timesPrinted, t_int69_0 );
	printHelloWorld( );
	t_int78r_int_sum_ =  int_plus_int( timesPrinted, t_int24_1 );
	int_equal_int( &timesPrinted, t_int78r_int_sum_ );
	t_bool62r_bool_isLess_ =  int_less_int( timesPrinted, timesToPrint );
	ifbool( t_bool62r_bool_isLess_ );
	{
		int t_int64_17 = 17;

		goToLineint( t_int64_17 );
	}
}

void getNumberFromintintoint ( int number, int *out )
{
	int t_int27r_int_ret_loadModelFrom_;
	int t_int5_3 = 3;
	int t_int61r_int_product_;
	int t_int91r_int_sum_;
	char* t_string45r_string_path_pathToModel;
	char* t_string81r_string_path_pathToModel;

	t_string81r_string_path_pathToModel =  pathToModel( );
	t_int27r_int_ret_loadModelFrom_ =  loadModelFromstring( t_string81r_string_path_pathToModel );
	t_int61r_int_product_ =  int_asterisk_int( t_int27r_int_ret_loadModelFrom_, number );
	t_int91r_int_sum_ =  int_plus_int( t_int5_3, t_int61r_int_product_ );
	int_equal_int( &*out, t_int91r_int_sum_ );
}

char* pathToModel (  )
{
	char* path;
	char* t_string95 = "c:/model.s3d\n";

	return t_string95;
	return path;
}

