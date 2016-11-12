#include "Debug.h"

void Debug::Init() {
	OFSTREAM out;

	// During this Init, we're going to either:
	// 1) Create "Log.txt" if it doesn't already exist, or
	// 2) Append to it if it exist
	out.open("Log.txt", IOS::app | IOS::out);

	out.close();
}

void Debug::Log(const EMessageType MsgType, const STRING& Class, const STRING& Method, const STRING& timestamp, const STRING& file, const int& line, const STRING& comments)
{
	std::ofstream out;
	out.open("DebugLog.txt", IOS::app); // this will either create a new debug file or append to it

	switch (MsgType) {
	case EMessageType::INFO:
		out << timestamp << file << line << ENDL << "INFO: " << Class << "::" << Method << "()" << ENDL << "Notes: " << comments << ENDL << ENDL;
		break;
	case EMessageType::WARNING:
		out << timestamp << file << line << ENDL << "WARNING: " << Class << "::" << Method << "()" << ENDL << "Notes: " << comments << ENDL << ENDL;
		break;
	case EMessageType::ERR:
		out << timestamp << file << line << ENDL << "ERROR: " << Class << "::" << Method << "()" << ENDL << "Notes: " << comments << ENDL << ENDL;
		break;
	case EMessageType::FATAL_ERR:
		out << timestamp << file << line << ENDL << "FATAL ERROR: " << Class << "::" << Method << "()" << ENDL << "Notes: " << comments << ENDL << ENDL;
		break;
	}

	out.close(); // close the debug file
}


void Debug::ConsoleLog(const STRING& notes) {
	COUT << notes << ENDL;
}

void Debug::ConsoleLog(const hFLOAT _f) {
	COUT << _f << ENDL;
}


void Debug::ConsoleError(const STRING& error) {
	CERR << "ERROR: " << error << ENDL;
}

void Debug::ConsoleError(const STRING & error, const STRING& file, const hINT line)
{
	CERR << "ERROR: " << error << ENDL << "FILE: " << file << ENDL << "LINE: " << line << ENDL;
	
}
