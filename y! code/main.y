uses ConsoleIO

// forward declarations of system code / code that would be in ConsoleIO if 'uses' was actually implemented
r(int)sum (int)a + (int)b p = -20
c	sum=a+b;
r(int)product (int)a * (int)b p= -10
c	product=a*b;
o(int)a = (int) b p = -100
c	*a=b;
r(bool)isLess (int)a < (int)b
c	isLess=a<b;
print (string)str
c	printf(str);
inline goToLine (int)lineNumber
c:	goto loop;
r(branch) if (int)is



r(int)success start (int) nArgument
	printHelloWorlds
	return 0

printHelloWorld 
	print "Hello world\n"

r(int)ret loadModelFrom (string)path
	ret = 2
	print path
	return

printHelloWorlds
	getNumberFrom 4 into timesToPrint
	timesPrinted = 0
	printHelloWorld
	timesPrinted = timesPrinted + 1
	if timesPrinted // < timesToPrint
		goToLine 17
	else:
		print "End\n"
	start:
		print "Start\n"


getNumberFrom (int)number into o(int) out
	out = 3 + loadModelFrom pathToModel * number
	
r(string)path pathToModel
	return "c:/model.s3d\n"