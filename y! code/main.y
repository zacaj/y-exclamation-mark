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
	out = 3
	pathToModel
	
	out = 3 + loadModelFrom tempStrPathToModel + number
	out = 3
	loadModelFrom tempStrPathToModel

	out = 3 + tempInt2 + number
	out = 3
	3 + tempInt2
	tempInt2 + number

	out = tempInt5 + number
	out = tempInt5
	tempInt5+number
	out=tempInt5number


	out = 3 + loadModelFrom temp2 + number
	out = 3 + temp1 + number
	out = temp3 + number
	out = temp4



	
	out = 3 + loadModelFrom pathToModel ^ number
	out = 3 + loadModel str ^ number
	out = 3 + int2 ^ number
	out = 3
	3 + int2
	int2 ^ number

	=				-1000
	+				-100
	^				-50
	loadModelFrom	0
	pathToModel		0
	r(int) (int)a ^ (int)b
	
r(string)path pathToModel
	return "c:/model.s3d"