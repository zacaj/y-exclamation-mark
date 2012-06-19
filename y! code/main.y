uses ConsoleIO

// forward declarations of system code / code that would be in ConsoleIO if 'uses' was actually implemented
return (int)r
return (string)r
r(int)sum (int)a + (int)b p = -20
r(int)product (int)a * (int)b p= -10
o(int)a = (int) b p = -100
r(bool)isLess (int)a < (int)b
print (string)str
goToLine (int)lineNumber
if (bool)is


r(int)success start (int) nArgument
	printHelloWorlds
	return 0

printHelloWorld 
	print "Hello world\n"

r(int)ret loadModelFrom (string)path
	print path
	return 2

printHelloWorlds
	getNumberFrom 4 into timesToPrint
	timesPrinted = 0
	printHelloWorld
	timesPrinted = timesPrinted + 1
	if timesPrinted < timesToPrint
		goToLine 17

getNumberFrom (int)number into o(int) out
	out = 3 + loadModelFrom pathToModel * number
	
r(string)path pathToModel
	return "c:/model.s3d"