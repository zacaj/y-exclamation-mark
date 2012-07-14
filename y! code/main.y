uses ConsoleIO

// forward declarations of system code / code that would be in ConsoleIO if 'uses' was actually implemented
r(int)sum (int)a + (int)b p = -20
c	sum=a+b;

r(int)product (int)a * (int)b p= -10
c	product=a*b;

r(int) o(int)a = (int)b p = -100
c	*a=b;
	return a

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

	shouldPrintEnd = 1

	for i = 0 ; i < timesToPrint ; i = i + 1 
		printHelloWorld
		switch i
		case 0
			print "Start\n"
			continue default
		case 2
			print "2\n"
		case 1
			if shouldPrintEnd < 1
				print "Hello\n"
			else: print "Goodbye\n"
			continue case 4
		case 5
			continue
			print "5\n"
		case 4
			print "4\n"
		default
			print "?\n"
		print ""

	return
	timesPrinted = -1
	while timesPrinted < timesToPrint
		printHelloWorld
		timesPrinted = timesPrinted + 1
		//print (int) timesPrinted
		switch timesPrinted
		case 0
			print "Start\n"
			continue default
		case 2
			print "2\n"
		case 1
			if shouldPrintEnd < 1
				print "Hello\n"
			else: print "Goodbye\n"
			continue case 4
		case 5
			continue
			print "5\n"
		case 4
			print "4\n"
		default
			print "?\n"
	print "Real end\n"
	return

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

empty