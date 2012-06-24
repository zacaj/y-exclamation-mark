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
int startint ( int nArgument );
void printHelloWorlds (  );
void getNumberFromintintoint ( int number, int *out );
char* pathToModelstringstring ( char* text, char* text2 );
void printHelloWorld (  );
int loadModelFromstring ( char* path );
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

int startint ( int nArgument )
{
	int success;
	int t_int41_0 = 0;

	printHelloWorlds( );
	return t_int41_0;
}

void printHelloWorlds (  )
{
	int shouldPrintEnd;
	unsigned char t_bool45r_bool_isLess_;
	unsigned char t_bool62r_bool_isLess_;
	unsigned char t_bool95r_bool_isLess_;
	int t_int0_1 = 1;
	int t_int24r_int_sum_;
	int t_int27_4 = 4;
	int t_int34_ = -1;
	int t_int61_6 = 6;
	int t_int64_1 = 1;
	int t_int67_1 = 1;
	int t_int69_1 = 1;
	char* t_string27 = "3\n";
	char* t_string36 = "Real end\n";
	int timesPrinted;
	int timesToPrint;

	getNumberFromintintoint( t_int67_1, &timesToPrint );
	int_equal_int( &timesPrinted, t_int34_ );
	int_equal_int( &shouldPrintEnd, t_int0_1 );
loop:
	printHelloWorld( );
	t_int24r_int_sum_ =  int_plus_int( timesPrinted, t_int69_1 );
	int_equal_int( &timesPrinted, t_int24r_int_sum_ );
	t_bool62r_bool_isLess_ =  int_less_int( timesPrinted, timesToPrint );
	branch_t t_branch81 = ifbool( t_bool62r_bool_isLess_ );
	if( t_branch81.labelId==0 )
	{
		goto loop;
	}
	else if( t_branch81.labelId==1 )
	{
		int shouldPrintEnd;
		unsigned char t_bool45r_bool_isLess_;
		unsigned char t_bool62r_bool_isLess_;
		unsigned char t_bool95r_bool_isLess_;
		int t_int0_1 = 1;
		int t_int24r_int_sum_;
		int t_int27_4 = 4;
		int t_int34_ = -1;
		int t_int61_6 = 6;
		int t_int64_1 = 1;
		int t_int67_1 = 1;
		int t_int69_1 = 1;
		char* t_string27 = "3\n";
		char* t_string36 = "Real end\n";
		int timesPrinted;
		int timesToPrint;

		t_bool45r_bool_isLess_ =  int_less_int( shouldPrintEnd, t_int64_1 );
		branch_t t_branch89 = ifbool( t_bool45r_bool_isLess_ );
		if( t_branch89.labelId==0 )
		{
			char* t_string81 = "End\n";

			printstring( t_string81 );
		}
		else if( t_branch89.labelId==1 )
		{
			int shouldPrintEnd;
			unsigned char t_bool45r_bool_isLess_;
			unsigned char t_bool62r_bool_isLess_;
			unsigned char t_bool95r_bool_isLess_;
			int t_int0_1 = 1;
			int t_int24r_int_sum_;
			int t_int27_4 = 4;
			int t_int34_ = -1;
			int t_int61_6 = 6;
			int t_int64_1 = 1;
			int t_int67_1 = 1;
			int t_int69_1 = 1;
			char* t_string27 = "3\n";
			char* t_string36 = "Real end\n";
			int timesPrinted;
			int timesToPrint;

			t_bool95r_bool_isLess_ =  int_less_int( t_int27_4, t_int61_6 );
			branch_t t_branch98 = ifbool( t_bool95r_bool_isLess_ );
			if( t_branch98.labelId==0 )
			{
				char* t_string42 = "Other\n";

				printstring( t_string42 );
			}
			else if( t_branch98.labelId==1 )
			{
				int shouldPrintEnd;
				unsigned char t_bool45r_bool_isLess_;
				unsigned char t_bool62r_bool_isLess_;
				unsigned char t_bool95r_bool_isLess_;
				int t_int0_1 = 1;
				int t_int24r_int_sum_;
				int t_int27_4 = 4;
				int t_int34_ = -1;
				int t_int61_6 = 6;
				int t_int64_1 = 1;
				int t_int67_1 = 1;
				int t_int69_1 = 1;
				char* t_string27 = "3\n";
				char* t_string36 = "Real end\n";
				int timesPrinted;
				int timesToPrint;

				printstring( t_string27 );
			}
		}
	}
	printstring( t_string36 );
}

void getNumberFromintintoint ( int number, int *out )
{
	int t_int15r_int_product_;
	int t_int29r_int_ret_loadModelFrom_;
	int t_int33r_int_;
	int t_int41r_int_sum_;
	int t_int91_3 = 3;
	char* t_string2 = "bar";
	char* t_string4 = "foo";
	char* t_string82r_string_path_pathToModel_;

	t_string82r_string_path_pathToModel_ =  pathToModelstringstring( t_string4, t_string2 );
	t_int29r_int_ret_loadModelFrom_ =  loadModelFromstring( t_string82r_string_path_pathToModel_ );
	t_int41r_int_sum_ =  int_plus_int( t_int91_3, t_int29r_int_ret_loadModelFrom_ );
	t_int33r_int_ =  f_C_int_D_( t_int41r_int_sum_ );
	t_int15r_int_product_ =  int_asterisk_int( t_int33r_int_, number );
	int_equal_int( &*out, t_int15r_int_product_ );
}

char* pathToModelstringstring ( char* text, char* text2 )
{
	char* path;
	char* t_string80 = "c:/model.s3d\n";

	printstring( text );
	printstring( text2 );
	printstring( text2 );
	string_equal_string( &path, t_string80 );
	return path;
}

void printHelloWorld (  )
{
	char* t_string96 = "Hello world\n";

	printstring( t_string96 );
}

int loadModelFromstring ( char* path )
{
	int ret;
	int t_int98_1 = 1;

	int_equal_int( &ret, t_int98_1 );
	printstring( path );
	return ret;
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

