//*******************************//
//
// Name:			Debug.h
// Description:		I/O streams for debugging.
//					Opens a debug file for writing.
//
// Author:			Edwin Chen
// Created:			Jan 31, 2016
// Last updated:	Nov 11, 2016
//
//*******************************//

#ifndef _DEBUG_H
#define _DEBUG_H 

#include "Macro.h"


/// This enum is a simple 8-bit unsigned int
enum class EMessageType : unsigned short {
	INFO = 0,
	WARNING,
	ERR,
	FATAL_ERR
};

class Debug {
public:
	/// New in C++ 11: this deletes the automatic constructor from being formed if no other constructor is decleared 
	Debug() = delete;

	/// Let's kill any default constructors the complier makes for us
	Debug(const Debug&) = delete;
	Debug(Debug&&) = delete;
	Debug& operator=(const Debug&) = delete;
	Debug& operator=(Debug&&) = delete;

	static void Init();
	static void Log(const EMessageType MsgType, const STRING& Class, const STRING& Method, const STRING& timestamp, const STRING& file, const int& line, const STRING& comments);

	static void ConsoleLog(const STRING& notes);
	static void ConsoleLog(const hFLOAT _f);

	static void ConsoleError(const STRING& error);
	static void ConsoleError(const STRING& error, const STRING& file, const hINT line);
};



#endif