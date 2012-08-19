#include <stdio.h>

typedef struct 
{
	int labelId;
	unsigned char repeat;
} branch_t;

struct vec3;
struct vec4;
struct vec4
{
	int w;
};

struct vec3
{
	struct vec4 v;
	int x;
	int y;
	int z;
};

int int_plus_int ( int a, int b );
int int_asterisk_int ( int a, int b );
int int_equal_int ( int *a, int b );
void string_equal_string ( char* *a, char* b );
unsigned char int_less_int ( int a, int b );
void printstring ( char* str );
branch_t ifbool ( unsigned char is );
char* inttoString ( int i );
struct vec3 vec3_equal_vec3 ( struct vec3 *a, struct vec3 b );
struct vec3 f_C_vec3_D_int ( int i );
struct vec3 int_Q_int_Q_int ( int x, int y, int z );
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
struct vec3 f_C_vec3_D_ ( struct vec3 a );
struct vec4 f_C_vec4_D_ ( struct vec4 a );
void switchint ( int var );
void caseint ( int var );
void switchEnd (  );
void caseEnd (  );
void continue_ (  );
void continuedefault (  );
void continuecaseint ( int i );
void default_ (  );
branch_t whilebool ( unsigned char is );
struct vec4 vec3_Q_v ( struct vec3 this );
int vec3_Q_x ( struct vec3 this );
int vec3_Q_y ( struct vec3 this );
int vec3_Q_z ( struct vec3 this );
int vec4_Q_w ( struct vec4 this );


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

struct vec3 vec3_equal_vec3 ( struct vec3 *a, struct vec3 b )
{
	*a=b;
	return *a;
}

struct vec3 f_C_vec3_D_int ( int i )
{
	struct vec3 v;
	int_equal_int( &v.x, i );
	return v;
}

struct vec3 int_Q_int_Q_int ( int x, int y, int z )
{
	struct vec3 v;
	int_equal_int( &v.y, y );
	int_equal_int( &v.z, z );
	return v;
}

int startint ( int nArgument )
{
	int success;
	int t_int16_2 = 2;
	int t_int21_0 = 0;
	int t_int23_3 = 3;
	int t_int26_2 = 2;
	int t_int39_1 = 1;
	int t_int47_0 = 0;
	int t_int5_3 = 3;
	int t_int68_1 = 1;
	char* t_string15r_string_str_;
	char* t_string22 = ", ";
	char* t_string31r_string_str_;
	char* t_string33r_string_str_;
	char* t_string3r_string_str_;
	char* t_string40r_string_str_;
	char* t_string41r_string_str_;
	char* t_string44 = "\n";
	char* t_string4r_string_str_;
	char* t_string53 = "\n";
	char* t_string56 = ", ";
	char* t_string58 = ", ";
	char* t_string64 = ", ";
	char* t_string6r_string_str_;
	char* t_string76 = ", ";
	char* t_string77 = ", ";
	char* t_string84r_string_str_;
	char* t_string86 = "\n";
	char* t_string94 = ", ";
	char* t_string99r_string_str_;
	struct vec3 t_vec341r_vec3_v_;
	struct vec3 t_vec367r_vec3_v_;
	struct vec3 v;
	struct vec3 w;

	t_vec367r_vec3_v_ =  f_C_vec3_D_int( t_int47_0 );
	vec3_equal_vec3( &v, t_vec367r_vec3_v_ );
	t_string99r_string_str_ =  inttoString( v.v.w );
	printstring( t_string99r_string_str_ );
	printstring( t_string94 );
	t_string3r_string_str_ =  inttoString( v.x );
	printstring( t_string3r_string_str_ );
	printstring( t_string22 );
	t_string33r_string_str_ =  inttoString( v.y );
	printstring( t_string33r_string_str_ );
	printstring( t_string64 );
	t_string41r_string_str_ =  inttoString( v.z );
	printstring( t_string41r_string_str_ );
	printstring( t_string53 );
	int_equal_int( &v.x, t_int68_1 );
	int_equal_int( &v.y, t_int16_2 );
	int_equal_int( &v.z, t_int5_3 );
	t_string84r_string_str_ =  inttoString( v.x );
	printstring( t_string84r_string_str_ );
	printstring( t_string56 );
	t_string40r_string_str_ =  inttoString( v.y );
	printstring( t_string40r_string_str_ );
	printstring( t_string76 );
	t_string31r_string_str_ =  inttoString( v.z );
	printstring( t_string31r_string_str_ );
	printstring( t_string44 );
	t_vec341r_vec3_v_ =  int_Q_int_Q_int( t_int39_1, t_int26_2, t_int23_3 );
	vec3_equal_vec3( &w, t_vec341r_vec3_v_ );
	t_string15r_string_str_ =  inttoString( w.x );
	printstring( t_string15r_string_str_ );
	printstring( t_string58 );
	t_string4r_string_str_ =  inttoString( w.y );
	printstring( t_string4r_string_str_ );
	printstring( t_string77 );
	t_string6r_string_str_ =  inttoString( w.z );
	printstring( t_string6r_string_str_ );
	printstring( t_string86 );
	return t_int21_0;
}

void printHelloWorlds (  )
{
}

void getNumberFromintintoint ( int number, int *out )
{
	int t_int45_3 = 3;
	int t_int64r_int_ret_loadModelFrom_;
	int t_int82r_int_;
	int t_int86r_int_product_;
	int t_int9r_int_sum_;
	char* t_string24 = "foo";
	char* t_string58r_string_path_pathToModel_;
	char* t_string72 = "bar";

	t_string58r_string_path_pathToModel_ =  pathToModelstringstring( t_string24, t_string72 );
	t_int64r_int_ret_loadModelFrom_ =  loadModelFromstring( t_string58r_string_path_pathToModel_ );
	t_int9r_int_sum_ =  int_plus_int( t_int45_3, t_int64r_int_ret_loadModelFrom_ );
	t_int82r_int_ =  f_C_int_D_( t_int9r_int_sum_ );
	t_int86r_int_product_ =  int_asterisk_int( t_int82r_int_, number );
	int_equal_int( &*out, t_int86r_int_product_ );
}

char* pathToModelstringstring ( char* text, char* text2 )
{
	char* path;
	char* t_string55 = "c:/model.s3d\n";

	printstring( text );
	printstring( text2 );
	printstring( text2 );
	string_equal_string( &path, t_string55 );
	return path;
}

void printHelloWorld (  )
{
	char* t_string61 = "Hello world\n";

	printstring( t_string61 );
}

int loadModelFromstring ( char* path )
{
	int ret;
	int t_int64_1 = 1;

	int_equal_int( &ret, t_int64_1 );
	printstring( path );
	return ret;
}

void empty (  )
{
	int i;
	int shouldPrintEnd;
	unsigned char t_bool89r_bool_isLess_;
	int t_int3_1 = 1;
	int t_int43_0 = 0;
	int t_int61r_int_sum_;
	int t_int76_1 = 1;
	int t_int9_1 = 1;
	int timesToPrint;

	getNumberFromintintoint( t_int3_1, &timesToPrint );
	int_equal_int( &shouldPrintEnd, t_int76_1 );
	int_equal_int( &i, t_int43_0 );
	lt_branch89:;
	t_bool89r_bool_isLess_ =  int_less_int( i, timesToPrint );
	branch_t t_branch89 = whilebool( t_bool89r_bool_isLess_ );
	if( t_branch89.labelId==0 )
	{
		int t_int20_0 = 0;
		int t_int23_2 = 2;
		int t_int45_5 = 5;
		int t_int4_4 = 4;
		int t_int69_1 = 1;
		char* t_string13 = "";

		printHelloWorld( );
		switch( i )
		{
		case 0: case0t_sw22i:
		{
			char* t_string2 = "Start\n";

			printstring( t_string2 );
			goto defaultt_sw22i;
			break;
		}
		case 2: case2t_sw22i:
		{
			char* t_string31 = "2\n";

			printstring( t_string31 );
			break;
		}
		case 1: case1t_sw22i:
		{
			unsigned char t_bool59r_bool_isLess_;
			int t_int3_4 = 4;
			int t_int78_1 = 1;

			lt_branch38:;
			t_bool59r_bool_isLess_ =  int_less_int( shouldPrintEnd, t_int78_1 );
			branch_t t_branch38 = ifbool( t_bool59r_bool_isLess_ );
			if( t_branch38.labelId==0 )
			{
				char* t_string19 = "Hello\n";

				printstring( t_string19 );
			}
			else if( t_branch38.labelId==1 )
			{
				char* t_string71 = "Goodbye\n";

				printstring( t_string71 );
			}
			if( t_branch38.repeat!=0 ) goto lt_branch38;
			goto case4t_sw22i;
			break;
		}
		case 5: case5t_sw22i:
		{
			char* t_string81 = "5\n";

			goto case4t_sw22i;
			printstring( t_string81 );
			break;
		}
		case 4: case4t_sw22i:
		{
			char* t_string92 = "4\n";

			printstring( t_string92 );
			break;
		}
		default: defaultt_sw22i:
		{
			char* t_string85 = "?\n";

			printstring( t_string85 );
			}
		}
		printstring( t_string13 );
		t_int61r_int_sum_ =  int_plus_int( i, t_int9_1 );
		int_equal_int( &i, t_int61r_int_sum_ );
	}
	if( t_branch89.repeat!=0 ) goto lt_branch89;
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

struct vec3 f_C_vec3_D_ ( struct vec3 a )
{
	return a;
}

struct vec4 f_C_vec4_D_ ( struct vec4 a )
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
		int t_int98_1 = 1;

		return (branch_t){0 /* default */,1};
	}
	return (branch_t){2 /* none */,0};
}

struct vec4 vec3_Q_v ( struct vec3 this )
{
}

int vec3_Q_x ( struct vec3 this )
{
}

int vec3_Q_y ( struct vec3 this )
{
}

int vec3_Q_z ( struct vec3 this )
{
}

int vec4_Q_w ( struct vec4 this )
{
}

