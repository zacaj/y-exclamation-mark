#include<iostream>
#include<ctype.h>
using namespace std;
int main()
{
int arr[] = {1, 4, 5, 6, 9, 14, 21, 23, 28, 31, 35, 42, 46, 50, 53, 57, 62, 63, 65, 74, 79, 89, 95};
int value;
for(int i = 0; i < 23; i++)
cout << arr[i] << " ";
cout << endl;
	char c;
while(1)
{
	cout << "Enter seach value(-1 to exit): ";
	cin >> value >> c;
	printf("%c\n",c);
	if(value == -1)
	{
	cout << "Exiting..\n";
	break;
	}
	int beg = 0;
	int end = 23;
	for(beg = 0; beg < 23; beg++)
	{
		int middle = (beg+end)/2;
		if(value == arr[middle])
		{
		cout << "Its at location " << middle << endl;
		break;
		}
		else if(value > arr[middle])
		end = middle + 1;
		else if(value < arr[middle])
		end = middle - 1;
		else
		cout << "Element Not found\n";
	}
}
}