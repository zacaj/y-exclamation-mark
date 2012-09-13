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

r(string)str (int)i toString
c	str=malloc(10);
c	sprintf(str,"%i",i);

struct vec4
	(int) w= 2

struct vec3
	(int) x
	(int)y=8
	(int) z =5
	(vec4) v
	
r(vec3) o(vec3)a = (vec3)b p=-100
c	*a=b;
	return a	

r(vec3)v ( vec3 ) (int)i
	v=default
	//v.x=i
	//v.y=i
	v.z=i
	return v

r(vec3)v (int)x , (int)y , (int)z
	v.x=x
	v.y=y
	v.z=z
	return v

r(int)success start (int) nArgument
	v=(vec3)0
	print v.v.w toString
	print ", "
	print v.x toString
	print ", "
	print v.y toString
	print ", "
	print v.z toString
	print "\n"

	v2=alloc vec3
	v2.x=4
	v2.v.w=2
	v2.y=3
	print v2.v.w toString
	print ", "
	print v2.x toString
	print ", "
	print v2.y toString
	print ", "
	print v2.z toString
	print "\n"
	return 0
