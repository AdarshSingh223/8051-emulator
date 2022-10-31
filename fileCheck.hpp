#pragma once

#include<sys/stat.h>
#include<fstream>
#include<string>
#include<process.h>

#ifdef _WIN32
   #include <io.h> 
#else
   #include <unistd.h>
#endif

/*
    The following macors are predefined in unistd.h
    but, it's not included here in this case as _WIN32 is
    defined. These macros have to be defined manually
*/
#define F_OK    0 
#define R_OK    4
#define W_OK    2

#define access _access_s

/*
//check wether compiled with C++ or C
#ifdef __STDC__
    #error USE C++ 14 OR ABOVE TO COMPILE
#endif
*/

//check if compiled with C++ 14
#if __cplusplus < 201402
    #error USE C++ 14 OR ABOVE TO COMPILE
#endif
 //the above section of code is not working

#ifndef _FILECHECK_HPP_
    #define _FILECHECK_HPP_

/*
    The GOAL of this  is to write a few tests in order to 
    check wether the file we are reading from, is avilable
    or not. This is a series of tests that can't be written
    in the main source code as it is universal and can be 
    used in future projects.
*/

//function prototypes of tests to be used
inline bool existsTest0 (const std::string& fileName);
inline bool existsTest1 (const std::string& fileName);
inline bool existsTest2 (const std::string& fileName);
inline bool existsTest3 (const std::string& fileName);

inline bool readTest (const std::string& fileName);
inline bool writeTest (const std::string& fileName);

//function to be called from the main program
bool fileIsPerfect(const std::string& fileName) {

    bool test0 = existsTest0 (fileName);
    bool test1 = existsTest1 (fileName);
    bool test2 = existsTest2 (fileName);
    bool test3 = existsTest3 (fileName);

    bool test4 = readTest (fileName);
    bool test5 = writeTest (fileName);

    return (test0 && test1 && test2 && test3 && test4 && test5);

} 

inline bool existsTest0 (const std::string& fileName) {
    std::basic_ifstream<char, std::char_traits<char>> f(fileName.c_str());
    return f.good();
}

inline bool existsTest1 (const std::string& fileName) {

    if (FILE *file = fopen(fileName.c_str(), "r")) {
        fclose(file);
        return true;
    } else {
        return false;
    }  

}

inline bool existsTest2 (const std::string& fileName) {

    return ( _access_s( fileName.c_str(), F_OK ) != -1 );

}

inline bool existsTest3 (const std::string& fileName) {

  struct stat buffer;   
  return (stat (fileName.c_str(), &buffer) == 0); 

}

inline bool readTest (const std::string& fileName) {

    return ( _access_s(fileName.c_str(), R_OK ) != -1 );

}

inline bool writeTest (const std::string& fileName) {

    return ( _access_s( fileName.c_str(), W_OK ) != -1 );

}

#endif
 