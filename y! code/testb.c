int main()
{
	int *i=malloc(sizeof(int)*16);
	*(i+14)=5;
	return 0;
}