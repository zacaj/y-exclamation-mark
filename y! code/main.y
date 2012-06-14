 uses ConsoleIO

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
	out = 3 + loadModelFrom pathToModel + number
	
r(string)path pathToModel
	return "c:/model.s3d"