#include <stdio.h>

void  ( int r );
void  ( char* r );
int  ( int a, int b );
int  ( int a, int b );
void  ( int a, int b );
unsigned char  ( int a, int b );
void  ( char* str );
void  ( int lineNumber );
void  ( unsigned char is );
int  ( int nArgument );
void  (  );
int  ( char* path );
void  (  );
void  ( int number, int out );
char*  (  );


int main(int argc,char **argv)
{
	return startint(argc);
}

void returnint ( int r )
{
	return __ZXQ_return_value;
}

void returnstring ( char* r )
{
	return __ZXQ_return_value;
}

int int_plus_int ( int a, int b )
{
	int sum;
	return sum;
}

int int_asterisk_int ( int a, int b )
{
	int product;
	return product;
}

void int_equal_int ( int a, int b )
{
}

unsigned char int_less_int ( int a, int b )
{
	unsigned char isLess;
	return isLess;
}

void printstring ( char* str )
{
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
	returnint( t_int41_0 );
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

	printstring( path );
	returnint( t_int34_2 );
	return ret;
}

void printHelloWorlds (  )
{
	unsigned char t_bool58inline_r_bool_isLess_;
	unsigned char t_bool62inline_r_bool_isLess_;
	int t_int0_4 = 4;
	int t_int24_1 = 1;
	int t_int69_0 = 0;
	int t_int78inline_r_int_sum_;
	int timesPrinted;
	int timesToPrint;

	getNumberFromintintoint( t_int0_4, timesToPrint );
	int_equal_int( timesPrinted, t_int69_0 );
	printHelloWorld( );
	t_int78inline_r_int_sum_ =  int_plus_int( timesPrinted, t_int24_1 );
	int_equal_int( timesPrinted, t_int78inline_r_int_sum_ );
	t_bool62inline_r_bool_isLess_ =  int_less_int( timesPrinted, timesToPrint );
	ifbool( t_bool62inline_r_bool_isLess_ );
	{
		int t_int64_17 = 17;

		goToLineint( t_int64_17 );
	}
}

void getNumberFromintintoint ( int number, int out )
{
	int t_int27r_int_ret_loadModelFrom_;
	int t_int5_3 = 3;
	int t_int61inline_r_int_product_;
	int t_int91inline_r_int_sum_;
	char* t_string45r_string_path_pathToModel;
	char* t_string81r_string_path_pathToModel;

	t_string81r_string_path_pathToModel =  pathToModel( );
	t_int27r_int_ret_loadModelFrom_ =  loadModelFromstring( t_string81r_string_path_pathToModel );
	t_int61inline_r_int_product_ =  int_asterisk_int( t_int27r_int_ret_loadModelFrom_, number );
	t_int91inline_r_int_sum_ =  int_plus_int( t_int5_3, t_int61inline_r_int_product_ );
	int_equal_int( out, t_int91inline_r_int_sum_ );
}

char* pathToModel (  )
{
	char* path;
	char* t_string95 = "c:/model.s3d";

	returnstring( t_string95 );
	return path;
}

