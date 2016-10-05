//*******************************//
//
// Name:			DebugLog.h
// Description:		I/O streams for Debug Logging.
//					Opens a DebugLog file for writing.
//
// Author:			Edwin Chen
// Created:			Jan 31, 2016
// Last updated:	Sep 13, 2016
//
//*******************************//

#ifndef _DebugLog_H
#define _DebugLog_H 

#include "Macro.h"

#define LOG DebugLog::GetDebugLog()

class DebugLog {
public:
	enum LOG_LEVEL : unsigned short{
		LOG_NONE = 0,
		LOG_ERROR, 
		LOG_WARN, 
		LOG_TRACE, 
		LOG_INFO
	};
private:
	DebugLog();

	void SetSeverity(LOG_LEVEL severity) {
		_currentSeverity = severity;
	}


public:
	~DebugLog();

	static DebugLog* GetDebugLog();

	void Close();

	void Trace(STRING msg);
	void Info(STRING msg);
	void Warn(STRING msg);
	void Error(STRING err);
	void Error(STRING msg, hINT line, STRING file);

	void SetLogFile(STRING& fileName);


	inline STRING GetLogFileName() const {
		return _logFileName;
	}

	inline LOG_LEVEL getSeverity() const
	{
		return _currentSeverity;
	}

	void ConsoleLog(STRING msg);
	void ConsoleError(STRING err);

	void Log(LOG_LEVEL severity, STRING& msg);
	void Log(LOG_LEVEL severity, STRING& msg, hINT line, STRING& file);

private:
	static UNIQUE_PTR(DebugLog) _DebugLog;
	friend DEFAULT_DELETE(DebugLog);

	LOG_LEVEL _currentSeverity;
	OFSTREAM* _outStream;
	STRING _logFileName;
};



#endif