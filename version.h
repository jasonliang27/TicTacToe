#ifndef VERSION_H
#define VERSION_H

	//Date Version Types
	static const char DATE[] = "01";
	static const char MONTH[] = "02";
	static const char YEAR[] = "2017";
	static const char UBUNTU_VERSION_STYLE[] =  "17.02";
	
	//Software Status
	static const char STATUS[] =  "Beta";
	static const char STATUS_SHORT[] =  "b";
	
	//Standard Version Type
	static const long MAJOR  = 2;
	static const long MINOR  = 0;
	static const long BUILD  = 1;
	static const long REVISION  = 10;
	
	//Miscellaneous Version Types
	static const long BUILDS_COUNT  = 49;
	#define RC_FILEVERSION 2,0,1,10
	#define RC_FILEVERSION_STRING "2, 0, 1, 10\0"
	static const char FULLVERSION_STRING [] = "2.0.1.10";
	
	//These values are to keep track of your versioning state, don't modify them.
	static const long BUILD_HISTORY  = 12;
	

#endif //VERSION_H
