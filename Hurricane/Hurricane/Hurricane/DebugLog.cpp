#include "DebugLog.h"

// LOG MANAGER
UNIQUE_PTR(DebugLog) DebugLog::_DebugLog(nullptr);

DebugLog* DebugLog::GetDebugLog() {
	if (_DebugLog.get() == nullptr) {
		/// I originally set the unique_ptr to be null in the constructor - reset() sets the new address
		_DebugLog.reset(new DebugLog());
	}
	return _DebugLog.get();
}

DebugLog::DebugLog() : 
	_outStream(nullptr), 
	_currentSeverity(LOG_LEVEL::LOG_INFO), 
	_logFileName("DebugLog_File.log") 
{
	// empty
}


DebugLog::~DebugLog() {
	Close();
}

///////////////////////////////////////////////////////

void DebugLog::SetLogFile(STRING &fileName) {
	Close();
	_outStream = new OFSTREAM(fileName.c_str());
	_currentSeverity = LOG_ERROR;
}

void DebugLog::ConsoleLog(STRING msg) {
	COUT << msg << ENDL;
}

void DebugLog::ConsoleError(STRING err) {
	CERR << err << ENDL;
}

void DebugLog::Close()
{
	if (_outStream != NULL)
	{
		_outStream->close();
		delete _outStream;
		_outStream = NULL;
	}
}

void DebugLog::Log(LOG_LEVEL severity, STRING& msg)
{
	if (severity <= _currentSeverity && _currentSeverity > LOG_NONE)
	{
		if (_outStream == NULL)
		{
			SetLogFile(_logFileName);
		}
		(*_outStream) << msg << "\n";
		_outStream->flush();
	}
}

void DebugLog::Log(LOG_LEVEL severity, STRING & msg, hINT line, STRING & file)
{
	if (severity <= _currentSeverity && _currentSeverity > LOG_NONE)
	{
		if (_outStream == NULL)
		{
			SetLogFile(_logFileName);
		}
		(*_outStream) << "DATE: " << __TIMESTAMP__ << "\n" << "FILE: " << file << "\n" << "LINE: " << line << "\n" << "MESSAGE: " << msg << "\n";
		_outStream->flush();
	}
}

void DebugLog::Trace(STRING msg) {
	Log(LOG_TRACE, msg);
}
void DebugLog::Info(STRING msg) {
	Log(LOG_INFO, msg);
}
void DebugLog::Warn(STRING msg) {
	Log(LOG_WARN, msg);
}


void DebugLog::Error(STRING err) {
	Log(LOG_ERROR, err);
}
void DebugLog::Error(STRING msg, hINT line, STRING file) {
	Log(LOG_ERROR, msg, line, file);
}