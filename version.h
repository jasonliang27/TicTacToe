#ifndef VERSION_H
#define VERSION_H

	//Date Version Types
	static const char DATE[] = "09";
	static const char MONTH[] = "03";
	static const char YEAR[] = "2017";
	static const char UBUNTU_VERSION_STYLE[] =  "17.03";
	
	//Software Status
	static const char STATUS[] =  "Release";
	static const char STATUS_SHORT[] =  "r";
	
	//Standard Version Type
	static const long MAJOR  = 4;
	static const long MINOR  = 0;
	static const long BUILD  = 1;
	static const long REVISION  = 194;
	
	//Miscellaneous Version Types
	static const long BUILDS_COUNT  = 205;
	#define RC_FILEVERSION 4,0,1,194
	#define RC_FILEVERSION_STRING "4, 0, 1, 194\0"
	static const char FULLVERSION_STRING [] = "4.0.1.194";
	
	//These values are to keep track of your versioning state, don't modify them.
	static const long BUILD_HISTORY  = 47;
	

#endif //VERSION_H
