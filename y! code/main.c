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
	return v;
}

struct vec3 int_Q_int_Q_int ( int x, int y, int z )
{
	struct vec3 v;
	int t_int5r_int_;
	int t_int82r_int_;

	t_int5r_int_ =  vec3_Q_y( v );
	int_equal_int( &t_int5r_int_, y );
	t_int82r_int_ =  vec3_Q_z( v );
	int_equal_int( &t_int82r_int_, z );
	return v;
}

int startint ( int nArgument )
{
	int success;
	int t_int13r_int_;
	int t_int18r_int_;
	int t_int19_0 = 0;
	int t_int21_1 = 1;
	int t_int23r_int_;
	int t_int33r_int_;
	int t_int3r_int_;
	int t_int41r_int_;
	int t_int48_2 = 2;
	int t_int50r_int_;
	int t_int55r_int_;
	int t_int66r_int_;
	int t_int6_1 = 1;
	int t_int6r_int_;
	int t_int71_0 = 0;
	int t_int73r_int_;
	int t_int90_2 = 2;
	int t_int91_3 = 3;
	int t_int93r_int_;
	int t_int99_3 = 3;
	int t_int9r_int_;
	char* t_string10r_string_str_;
	char* t_string11r_string_str_;
	char* t_string14r_string_str_;
	char* t_string15r_string_str_;
	char* t_string17 = ", ";
	char* t_string26 = ", ";
	char* t_string28 = ", ";
	char* t_string2r_string_str_;
	char* t_string30r_string_str_;
	char* t_string37r_string_str_;
	char* t_string38r_string_str_;
	char* t_string40 = ", ";
	char* t_string41 = ", ";
	char* t_string48r_string_str_;
	char* t_string49 = "\n";
	char* t_string62 = ", ";
	char* t_string76r_string_str_;
	char* t_string77 = "\n";
	char* t_string95 = ", ";
	char* t_string96 = "\n";
	struct vec3 t_vec335r_vec3_v_;
	struct vec3 t_vec399r_vec3_v_;
	struct vec4 t_vec494r_vec4_;
	struct vec3 v;
	struct vec3 w;

	t_vec335r_vec3_v_ =  f_C_vec3_D_int( t_int71_0 );
	vec3_equal_vec3( &v, t_vec335r_vec3_v_ );
	t_vec494r_vec4_ =  vec3_Q_v( v );
	t_int3r_int_ =  vec4_Q_w( t_vec494r_vec4_ );
	t_string11r_string_str_ =  inttoString( t_int3r_int_ );
	printstring( t_string11r_string_str_ );
	printstring( t_string40 );
	t_int66r_int_ =  vec3_Q_x( v );
	t_string76r_string_str_ =  inttoString( t_int66r_int_ );
	printstring( t_string76r_string_str_ );
	printstring( t_string26 );
	t_int23r_int_ =  vec3_Q_y( v );
	t_string37r_string_str_ =  inttoString( t_int23r_int_ );
	printstring( t_string37r_string_str_ );
	printstring( t_string41 );
	t_int33r_int_ =  vec3_Q_z( v );
	t_string15r_string_str_ =  inttoString( t_int33r_int_ );
	printstring( t_string15r_string_str_ );
	printstring( t_string77 );
	t_int73r_int_ =  vec3_Q_x( v );
	int_equal_int( &t_int73r_int_, t_int6_1 );
	t_int50r_int_ =  vec3_Q_y( v );
	int_equal_int( &t_int50r_int_, t_int90_2 );
	t_int9r_int_ =  vec3_Q_z( v );
	int_equal_int( &t_int9r_int_, t_int91_3 );
	t_int6r_int_ =  vec3_Q_x( v );
	t_string30r_string_str_ =  inttoString( t_int6r_int_ );
	printstring( t_string30r_string_str_ );
	printstring( t_string62 );
	t_int55r_int_ =  vec3_Q_y( v );
	t_string10r_string_str_ =  inttoString( t_int55r_int_ );
	printstring( t_string10r_string_str_ );
	printstring( t_string95 );
	t_int41r_int_ =  vec3_Q_z( v );
	t_string2r_string_str_ =  inttoString( t_int41r_int_ );
	printstring( t_string2r_string_str_ );
	printstring( t_string96 );
	t_vec399r_vec3_v_ =  int_Q_int_Q_int( t_int21_1, t_int48_2, t_int99_3 );
	vec3_equal_vec3( &w, t_vec399r_vec3_v_ );
	t_int18r_int_ =  vec3_Q_x( w );
	t_string38r_string_str_ =  inttoString( t_int18r_int_ );
	printstring( t_string38r_string_str_ );
	printstring( t_string28 );
	t_int93r_int_ =  vec3_Q_y( w );
	t_string48r_string_str_ =  inttoString( t_int93r_int_ );
	printstring( t_string48r_string_str_ );
	printstring( t_string17 );
	t_int13r_int_ =  vec3_Q_z( w );
	t_string14r_string_str_ =  inttoString( t_int13r_int_ );
	printstring( t_string14r_string_str_ );
	printstring( t_string49 );
	return t_int19_0;
}

void printHelloWorlds (  )
{
}

void getNumberFromintintoint ( int number, int *out )
{
	int t_int29r_int_ret_loadModelFrom_;
	int t_int32r_int_product_;
	int t_int56_3 = 3;
	int t_int59r_int_;
	int t_int65r_int_sum_;
	char* t_string29r_string_path_pathToModel_;
	char* t_string3 = "bar";
	char* t_string98 = "foo";

	t_string29r_string_path_pathToModel_ =  pathToModelstringstring( t_string98, t_string3 );
	t_int29r_int_ret_loadModelFrom_ =  loadModelFromstring( t_string29r_string_path_pathToModel_ );
	t_int65r_int_sum_ =  int_plus_int( t_int56_3, t_int29r_int_ret_loadModelFrom_ );
	t_int59r_int_ =  f_C_int_D_( t_int65r_int_sum_ );
	t_int32r_int_product_ =  int_asterisk_int( t_int59r_int_, number );
	int_equal_int( &*out, t_int32r_int_product_ );
}

char* pathToModelstringstring ( char* text, char* text2 )
{
	char* path;
	char* t_string68 = "c:/model.s3d\n";

	printstring( text );
	printstring( text2 );
	printstring( text2 );
	string_equal_string( &path, t_string68 );
	return path;
}

void printHelloWorld (  )
{
	char* t_string25 = "Hello world\n";

	printstring( t_string25 );
}

int loadModelFromstring ( char* path )
{
	int ret;
	int t_int76_1 = 1;

	int_equal_int( &ret, t_int76_1 );
	printstring( path );
	return ret;
}

void empty (  )
{
	int i;
	int shouldPrintEnd;
	unsigned char t_bool80r_bool_isLess_;
	int t_int29_1 = 1;
	int t_int50_1 = 1;
	int t_int86r_int_sum_;
	int t_int98_0 = 0;
	int t_int9_1 = 1;
	int timesToPrint;

	getNumberFromintintoint( t_int29_1, &timesToPrint );
	int_equal_int( &shouldPrintEnd, t_int50_1 );
	int_equal_int( &i, t_int98_0 );
	lt_branch9:;
	t_bool80r_bool_isLess_ =  int_less_int( i, timesToPrint );
	branch_t t_branch9 = whilebool( t_bool80r_bool_isLess_ );
	if( t_branch9.labelId==0 )
	{
		int t_int21_2 = 2;
		int t_int26_1 = 1;
		int t_int64_5 = 5;
		int t_int79_0 = 0;
		int t_int86_4 = 4;
		char* t_string21 = "";

		printHelloWorld( );
		switch( i )
		{
		case 0: case0t_sw15i:
		{
			char* t_string64 = "Start\n";

			printstring( t_string64 );
			goto defaultt_sw15i;
			break;
		}
		case 2: case2t_sw15i:
		{
			char* t_string5 = "2\n";

			printstring( t_string5 );
			break;
		}
		case 1: case1t_sw15i:
		{
			unsigned char t_bool16r_bool_isLess_;
			int t_int16_1 = 1;
			int t_int81_4 = 4;

			lt_branch2:;
			t_bool16r_bool_isLess_ =  int_less_int( shouldPrintEnd, t_int16_1 );
			branch_t t_branch2 = ifbool( t_bool16r_bool_isLess_ );
			if( t_branch2.labelId==0 )
			{
				char* t_string66 = "Hello\n";

				printstring( t_string66 );
			}
			else if( t_branch2.labelId==1 )
			{
				char* t_string87 = "Goodbye\n";

				printstring( t_string87 );
			}
			if( t_branch2.repeat!=0 ) goto lt_branch2;
			goto case4t_sw15i;
			break;
		}
		case 5: case5t_sw15i:
		{
			char* t_string40 = "5\n";

			goto case4t_sw15i;
			printstring( t_string40 );
			break;
		}
		case 4: case4t_sw15i:
		{
			char* t_string21 = "4\n";

			printstring( t_string21 );
			break;
		}
		default: defaultt_sw15i:
		{
			char* t_string62 = "?\n";

			printstring( t_string62 );
			}
		}
		printstring( t_string21 );
		t_int86r_int_sum_ =  int_plus_int( i, t_int9_1 );
		int_equal_int( &i, t_int86r_int_sum_ );
	}
	if( t_branch9.repeat!=0 ) goto lt_branch9;
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
		int t_int64_1 = 1;

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

