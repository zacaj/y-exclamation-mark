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
	timesToPrint = get number from 4
	timesPrinted = 0
	print hello world
	timesPrinted = timesPrinted + 1
	if timesPrinted < timesToPrint
		go to line 17

r(int)ret get number from (int)number
	ret = 3 + load model from "c:/model.s3d" + number