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
	v = (struct vec3) {(struct vec4) {2}, 0, 8, 5};
	int_equal_int( &v.z, i );
	return v;
}

struct vec3 int_Q_int_Q_int ( int x, int y, int z )
{
	struct vec3 v;
	int_equal_int( &v.x, x );
	int_equal_int( &v.y, y );
	int_equal_int( &v.z, z );
	return v;
}

int startint ( int nArgument )
{
	int success;
	int t_int29_1 = 1;
	int t_int38_3 = 3;
	int t_int3_0 = 0;
	int t_int56_2 = 2;
	int t_int73_2 = 2;
	int t_int77_1 = 1;
	int t_int88_0 = 0;
	int t_int97_3 = 3;
	char* t_string21 = "\n";
	char* t_string24r_string_str_;
	char* t_string35r_string_str_;
	char* t_string37r_string_str_;
	char* t_string40 = ", ";
	char* t_string42 = ", ";
	char* t_string42r_string_str_;
	char* t_string45 = ", ";
	char* t_string46r_string_str_;
	char* t_string48 = ", ";
	char* t_string53r_string_str_;
	char* t_string70 = "\n";
	char* t_string73 = ", ";
	char* t_string77r_string_str_;
	char* t_string86r_string_str_;
	char* t_string87 = ", ";
	char* t_string88r_string_str_;
	char* t_string9 = ", ";
	char* t_string90 = "\n";
	char* t_string9r_string_str_;
	struct vec3 t_vec378r_vec3_v_;
	struct vec3 t_vec391r_vec3_v_;
	struct vec3 v;
	struct vec3 w;

	t_vec378r_vec3_v_ =  f_C_vec3_D_int( t_int3_0 );
	vec3_equal_vec3( &v, t_vec378r_vec3_v_ );
	v.v.w = 0;
	t_string35r_string_str_ =  inttoString( v.v.w );
	printstring( t_string35r_string_str_ );
	printstring( t_string42 );
	t_string88r_string_str_ =  inttoString( v.x );
	printstring( t_string88r_string_str_ );
	printstring( t_string40 );
	t_string42r_string_str_ =  inttoString( v.y );
	printstring( t_string42r_string_str_ );
	printstring( t_string48 );
	t_string46r_string_str_ =  inttoString( v.z );
	printstring( t_string46r_string_str_ );
	printstring( t_string90 );
	int_equal_int( &v.x, t_int29_1 );
	int_equal_int( &v.y, t_int56_2 );
	int_equal_int( &v.z, t_int38_3 );
	t_string77r_string_str_ =  inttoString( v.x );
	printstring( t_string77r_string_str_ );
	printstring( t_string73 );
	t_string86r_string_str_ =  inttoString( v.y );
	printstring( t_string86r_string_str_ );
	printstring( t_string45 );
	t_string24r_string_str_ =  inttoString( v.z );
	printstring( t_string24r_string_str_ );
	printstring( t_string70 );
	t_vec391r_vec3_v_ =  int_Q_int_Q_int( t_int77_1, t_int73_2, t_int97_3 );
	vec3_equal_vec3( &w, t_vec391r_vec3_v_ );
	t_string37r_string_str_ =  inttoString( w.x );
	printstring( t_string37r_string_str_ );
	printstring( t_string87 );
	t_string53r_string_str_ =  inttoString( w.y );
	printstring( t_string53r_string_str_ );
	printstring( t_string9 );
	t_string9r_string_str_ =  inttoString( w.z );
	printstring( t_string9r_string_str_ );
	printstring( t_string21 );
	return t_int88_0;
}

void printHelloWorlds (  )
{
}

void getNumberFromintintoint ( int number, int *out )
{
	int t_int22_3 = 3;
	int t_int33r_int_ret_loadModelFrom_;
	int t_int42r_int_;
	int t_int44r_int_product_;
	int t_int69r_int_sum_;
	char* t_string46 = "foo";
	char* t_string6 = "bar";
	char* t_string75r_string_path_pathToModel_;

	t_string75r_string_path_pathToModel_ =  pathToModelstringstring( t_string46, t_string6 );
	t_int33r_int_ret_loadModelFrom_ =  loadModelFromstring( t_string75r_string_path_pathToModel_ );
	t_int69r_int_sum_ =  int_plus_int( t_int22_3, t_int33r_int_ret_loadModelFrom_ );
	t_int42r_int_ =  f_C_int_D_( t_int69r_int_sum_ );
	t_int44r_int_product_ =  int_asterisk_int( t_int42r_int_, number );
	int_equal_int( &*out, t_int44r_int_product_ );
}

char* pathToModelstringstring ( char* text, char* text2 )
{
	char* path;
	char* t_string58 = "c:/model.s3d\n";

	printstring( text );
	printstring( text2 );
	printstring( text2 );
	string_equal_string( &path, t_string58 );
	return path;
}

void printHelloWorld (  )
{
	char* t_string41 = "Hello world\n";

	printstring( t_string41 );
}

int loadModelFromstring ( char* path )
{
	int ret;
	int t_int90_1 = 1;

	int_equal_int( &ret, t_int90_1 );
	printstring( path );
	return ret;
}

void empty (  )
{
	int i;
	int shouldPrintEnd;
	unsigned char t_bool72r_bool_isLess_;
	int t_int12_1 = 1;
	int t_int13_1 = 1;
	int t_int55_0 = 0;
	int t_int60_1 = 1;
	int t_int93r_int_sum_;
	int timesToPrint;

	getNumberFromintintoint( t_int13_1, &timesToPrint );
	int_equal_int( &shouldPrintEnd, t_int12_1 );
	int_equal_int( &i, t_int55_0 );
	lt_branch29:;
	t_bool72r_bool_isLess_ =  int_less_int( i, timesToPrint );
	branch_t t_branch29 = whilebool( t_bool72r_bool_isLess_ );
	if( t_branch29.labelId==0 )
	{
		int t_int19_0 = 0;
		int t_int5_1 = 1;
		int t_int60_5 = 5;
		int t_int71_4 = 4;
		int t_int7_2 = 2;
		char* t_string14 = "";

		printHelloWorld( );
		switch( i )
		{
		case 0: case0t_sw89i:
		{
			char* t_string72 = "Start\n";

			printstring( t_string72 );
			goto defaultt_sw89i;
			break;
		}
		case 2: case2t_sw89i:
		{
			char* t_string94 = "2\n";

			printstring( t_string94 );
			break;
		}
		case 1: case1t_sw89i:
		{
			unsigned char t_bool83r_bool_isLess_;
			int t_int38_4 = 4;
			int t_int40_1 = 1;

			lt_branch66:;
			t_bool83r_bool_isLess_ =  int_less_int( shouldPrintEnd, t_int40_1 );
			branch_t t_branch66 = ifbool( t_bool83r_bool_isLess_ );
			if( t_branch66.labelId==0 )
			{
				char* t_string9 = "Hello\n";

				printstring( t_string9 );
			}
			else if( t_branch66.labelId==1 )
			{
				char* t_string7 = "Goodbye\n";

				printstring( t_string7 );
			}
			if( t_branch66.repeat!=0 ) goto lt_branch66;
			goto case4t_sw89i;
			break;
		}
		case 5: case5t_sw89i:
		{
			char* t_string71 = "5\n";

			goto case4t_sw89i;
			printstring( t_string71 );
			break;
		}
		case 4: case4t_sw89i:
		{
			char* t_string54 = "4\n";

			printstring( t_string54 );
			break;
		}
		default: defaultt_sw89i:
		{
			char* t_string47 = "?\n";

			printstring( t_string47 );
			}
		}
		printstring( t_string14 );
		t_int93r_int_sum_ =  int_plus_int( i, t_int60_1 );
		int_equal_int( &i, t_int93r_int_sum_ );
	}
	if( t_branch29.repeat!=0 ) goto lt_branch29;
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
		int t_int23_1 = 1;

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

