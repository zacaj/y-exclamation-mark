void string_equal_string ( char* *a, char* b )
{
	*a=malloc(strlen(b));
	strcpy(*a,b);
}
char* pathToModel( char* text, char* text2 )
{
	char* path;
	char* t_string80 = "c:/model.s3d\n";

	string_equal_string( &path, t_string80 );
	return path;
}


int int_equal_int ( int *a, int b )
{
	*a=b;
	return *a;
}
int loadModelFrom ( char* path )
{
	int ret;
	int t_int49_1 = 1;

	int_equal_int( &ret, t_int49_1 );
	return ret;
}

int main()
{
	int number=1;
	int out=(3+loadModelFrom(pathToModel("foo","bar")))*number;
}