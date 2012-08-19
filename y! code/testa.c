

void string_equal_string ( char* *a, char* b )
{
	*a=malloc(strlen(b));
	strcpy(*a,b);
}
char* pathToModelstringstring ( char* text, char* text2 )
{
	char* path;
	char* t_string80 = "c:/model.s3d\n";

	string_equal_string( &path, t_string80 );
	return path;
}

int loadModelFromstring ( char* path )
{
	int ret;
	int t_int49_1 = 1;

	int_equal_int( &ret, t_int49_1 );
	return ret;
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

int f_C_int_D_ ( int a )
{
	return a;
}

int main()
{
	int number=1;
	int t_int14r_int_product_;
	int t_int23_3 = 3;
	int t_int36r_int_ret_loadModelFrom_;
	int t_int36r_int_sum_;
	int t_int41r_int_;
	char* t_string14 = "bar";
	char* t_string65r_string_path_pathToModel_;
	char* t_string87 = "foo";
	int *out;

	t_string65r_string_path_pathToModel_ =  pathToModelstringstring( t_string87, t_string14 );
	t_int36r_int_ret_loadModelFrom_ =  loadModelFromstring( t_string65r_string_path_pathToModel_ );
	t_int36r_int_sum_ =  int_plus_int( t_int23_3, t_int36r_int_ret_loadModelFrom_ );
	t_int41r_int_ =  f_C_int_D_( t_int36r_int_sum_ );
	t_int14r_int_product_ =  int_asterisk_int( t_int41r_int_, number );
	int_equal_int( &*out, t_int14r_int_product_ );
}