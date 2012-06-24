uses ConsoleIO

// forward declarations of system code / code that would be in ConsoleIO if 'uses' was actually implemented
r(int)sum (int)a + (int)b p = -20
c	sum=a+b;

r(int)product (int)a * (int)b p= -10
c	product=a*b;

o(int)a = (int) b p = -100
c	*a=b;

o(string)a = (string)b p = -100
c	*a=malloc(strlen(b));
c	strcpy(*a,b);

r(bool)isLess (int)a < (int)b
c	isLess=a<b;

print (string)str
c	printf(str);

r(branch) if (bool)is
c	if(is) 
		return default
c	else
		return else



r(int)success start (int) nArgument
	printHelloWorlds
	return 0

printHelloWorlds
	getNumberFrom 1 into timesToPrint

	timesPrinted = -1
	shouldPrintEnd = 1
loop:
	printHelloWorld
	timesPrinted = timesPrinted + 1

	if timesPrinted < timesToPrint
		goto loop
	else: if shouldPrintEnd < 1
		print "End\n"
	else: if 4 < 6
		print "Other\n"
	else: print "3\n"
	print "Real end\n"


getNumberFrom (int)number into o(int) out
	out = ( 3 + loadModelFrom pathToModel "foo" "bar" ) * number
	
r(string)path pathToModel (string)text (string)text2
	print text
	print text2
	print text2
	path = "c:/model.s3d\n"

printHelloWorld 
	print "Hello world\n"

r(int)ret loadModelFrom (string)path
	ret = 1
	print path
	return