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