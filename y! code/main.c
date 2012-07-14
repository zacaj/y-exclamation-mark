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
	unsigned char t_bool18r_bool_isLess_;
	unsigned char t_bool58r_bool_isLess_;
	int t_int0_0 = 0;
	int t_int16_ = -1;
	int t_int34_1 = 1;
	int t_int67_1 = 1;
	int t_int69_1 = 1;
	int t_int78r_int_sum_;
	char* t_string68 = "Real end\n";
	int timesPrinted;
	int timesToPrint;

	getNumberFromintintoint( t_int67_1, &timesToPrint );
	int_equal_int( &shouldPrintEnd, t_int34_1 );
	lt_branch44:;
	int_equal_int( &i, t_int0_0 );
	t_bool58r_bool_isLess_ =  int_less_int( i, timesToPrint );
	branch_t t_branch44 = whilebool( t_bool58r_bool_isLess_ );
	if( t_branch44.labelId==0 )
	{
		int t_int4_5 = 5;
		int t_int53_4 = 4;
		int t_int5_0 = 0;
		int t_int61_1 = 1;
		int t_int81_2 = 2;
		char* t_string21 = "";

		printHelloWorld( );
		switch( i )
		{
		case 0: case0t_sw16i:
		{
			char* t_string45 = "Start\n";

			printstring( t_string45 );
			goto defaultt_sw16i;
			break;
		}
		case 2: case2t_sw16i:
		{
			char* t_string27 = "2\n";

			printstring( t_string27 );
			break;
		}
		case 1: case1t_sw16i:
		{
			unsigned char t_bool95r_bool_isLess_;
			int t_int91_1 = 1;
			int t_int91_4 = 4;

			lt_branch81:;
			t_bool95r_bool_isLess_ =  int_less_int( shouldPrintEnd, t_int91_1 );
			branch_t t_branch81 = ifbool( t_bool95r_bool_isLess_ );
			if( t_branch81.labelId==0 )
			{
				char* t_string27 = "Hello\n";

				printstring( t_string27 );
			}
			else if( t_branch81.labelId==1 )
			{
				char* t_string36 = "Goodbye\n";

				printstring( t_string36 );
			}
			if( t_branch81.repeat!=0 ) goto lt_branch81;
			printstring( t_string36 );
			goto case4t_sw16i;
			break;
		}
		case 5: case5t_sw16i:
		{
			char* t_string2 = "5\n";

			goto case4t_sw16i;
			printstring( t_string2 );
			break;
		}
		case 4: case4t_sw16i:
		{
			char* t_string92 = "4\n";

			printstring( t_string92 );
			break;
		}
		default: defaultt_sw16i:
		{
			char* t_string82 = "?\n";

			printstring( t_string82 );
			}
		}
		printstring( t_string21 );
		t_int78r_int_sum_ =  int_plus_int( i, t_int69_1 );
		int_equal_int( &i, t_int78r_int_sum_ );
	}
	if( t_branch44.repeat!=0 ) goto lt_branch44;
	return;
	int_equal_int( &timesPrinted, t_int16_ );
	lt_branch98:;
	t_bool18r_bool_isLess_ =  int_less_int( timesPrinted, timesToPrint );
	branch_t t_branch98 = whilebool( t_bool18r_bool_isLess_ );
	if( t_branch98.labelId==0 )
	{
		int t_int12_2 = 2;
		int t_int38_0 = 0;
		int t_int41_4 = 4;
		int t_int47_1 = 1;
		int t_int71r_int_sum_;
		int t_int73_5 = 5;
		int t_int99_1 = 1;

		printHelloWorld( );
		t_int71r_int_sum_ =  int_plus_int( timesPrinted, t_int47_1 );
		int_equal_int( &timesPrinted, t_int71r_int_sum_ );
		switch( timesPrinted )
		{
		case 0: case0t_sw22timesPrinted:
		{
			char* t_string69 = "Start\n";

			printstring( t_string69 );
			goto defaultt_sw22timesPrinted;
			break;
		}
		case 2: case2t_sw22timesPrinted:
		{
			char* t_string67 = "2\n";

			printstring( t_string67 );
			break;
		}
		case 1: case1t_sw22timesPrinted:
		{
			unsigned char t_bool94r_bool_isLess_;
			int t_int33_4 = 4;
			int t_int35_1 = 1;

			lt_branch51:;
			t_bool94r_bool_isLess_ =  int_less_int( shouldPrintEnd, t_int35_1 );
			branch_t t_branch51 = ifbool( t_bool94r_bool_isLess_ );
			if( t_branch51.labelId==0 )
			{
				char* t_string11 = "Hello\n";

				printstring( t_string11 );
			}
			else if( t_branch51.labelId==1 )
			{
				char* t_string22 = "Goodbye\n";

				printstring( t_string22 );
			}
			if( t_branch51.repeat!=0 ) goto lt_branch51;
			printstring( t_string22 );
			goto case4t_sw22timesPrinted;
			break;
		}
		case 5: case5t_sw22timesPrinted:
		{
			char* t_string64 = "5\n";

			goto case4t_sw22timesPrinted;
			printstring( t_string64 );
			break;
		}
		case 4: case4t_sw22timesPrinted:
		{
			char* t_string11 = "4\n";

			printstring( t_string11 );
			break;
		}
		default: defaultt_sw22timesPrinted:
		{
			char* t_string53 = "?\n";

			printstring( t_string53 );
			}
