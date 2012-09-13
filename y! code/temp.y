array=alloc 12
	arrayPtr=array
	@arrayPtr=2
	arrayPtr=arrayPtr+4
	@arrayPtr=1
	arrayPtr=arrayPtr+4
	@arrayPtr=4
	arrayPtr=array
	for i=0; i<3; i=i+1
		n=@arrayPtr
		print n toString
		arrayPtr=arrayPtr+4
	free array 



printHelloWorlds

getNumberFrom (int)number into o(int) out
	out=(3+loadModelFrom pathToModel "foo" "bar")*number
	
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
	getNumberFrom 1 into timesToPrint

	shouldPrintEnd=1

	for i=0 ; i<timesToPrint ; i=i+1 
		printHelloWorld
		switch i
		case 0
			print "Start\n"
			continue default
		case 2
			print "2\n"
		case 1
			if shouldPrintEnd<1
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