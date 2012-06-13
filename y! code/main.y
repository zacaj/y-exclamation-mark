 uses ConsoleIO

 r(int)success start [with] (int) nArgument [arguments]
	print hello worlds
	return 0

print hello world 
	print "Hello world\n"

r(int)ret load model from (string)path
	print path
	return 2

print hello worlds
	get number from 4 into timesToPrint
	timesPrinted = 0
	print hello world
	timesPrinted = timesPrinted + 1
	if timesPrinted < timesToPrint
		go to line 17

get number from (int)number o(int) out
	out = 3 + load model from path to model + number
	
r(string)path path to model
	return "c:/model.s3d"