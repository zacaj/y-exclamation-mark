define fastcc void @returnint ( i32 r)
{
	ret void;
}

define fastcc void @returnstring ( i8* r)
{
	ret void;
}

define fastcc i32 @int.plus.int ( i32 a, i32 b)
{
	ret i32 sum;
}

define fastcc i32 @int.asterisk.int ( i32 a, i32 b)
{
	ret i32 product;
}

define fastcc void @int.equal.int ( i32 a, i32 b)
{
	ret void;
}

define fastcc i1 @int.less.int ( i32 a, i32 b)
{
	ret i1 isLess;
}

define fastcc void @printstring ( i8* str)
{
	ret void;
}

define fastcc void @goToLineint ( i32 lineNumber)
{
	ret void;
}

define fastcc void @ifbool ( i1 is)
{
	ret void;
}

define fastcc i32 @startint ( i32 nArgument)
{
	call void @printHelloWorlds();
	call void @returnint(i32 %tint410);
	ret i32 success;
}

define fastcc void @printHelloWorld ( )
{
	call void @printstring(i8* %tstring67);
	ret void;
}

define fastcc i32 @loadModelFromstring ( i8* path)
{
	call void @printstring(i8* %path);
	{
		call void @printstring(i8* %path);
		{
			call void @printstring(i8* %path);
		}
	}
	call void @returnint(i32 %tint342);
	ret i32 ret;
}

define fastcc void @printHelloWorlds ( )
{
	call void @getNumberFromintintoint(i32 %tint04i32 %timesToPrint);
	call void @int.equal.int(i32 %timesPrintedi32 %tint690);
	call void @printHelloWorld();
	%tint78rintsum = call i32 @int.plus.int(i32 %timesPrintedi32 %tint241);
	call void @int.equal.int(i32 %timesPrintedi32 %tint78rintsum);
	%tbool62rboolisLess = call i1 @int.less.int(i32 %timesPrintedi32 %timesToPrint);
	call void @ifbool(i1 %tbool62rboolisLess);
	{
		call void @goToLineint(i32 %tint6417);
	ret void;
}

define fastcc void @getNumberFromintintoint ( i32 number, i32 out)
{
	%tstring81rstringpathpathToModel = call i8* @pathToModel();
	%tint27rintretloadModelFrom = call i32 @loadModelFromstring(i8* %tstring81rstringpathpathToModel);
	%tint61rintproduct = call i32 @int.asterisk.int(i32 %tint27rintretloadModelFromi32 %number);
	%tint91rintsum = call i32 @int.plus.int(i32 %tint53i32 %tint61rintproduct);
	call void @int.equal.int(i32 %outi32 %tint91rintsum);
	ret void;
}

define fastcc i8* @pathToModel ( )
{
	call void @returnstring(i8* %tstring95);
	ret i8* path;
}

