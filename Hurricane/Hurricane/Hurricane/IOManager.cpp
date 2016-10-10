#include "IOManager.h"
#include "DebugLog.h"

hBOOL IOManager::ReadFileToBuffer(const STRING filePath, VECTOR(hCHAR)& buffer)
{
	IFSTREAM file(filePath, IOS::binary);

	if (file.fail()) 
	{
		LOG->ConsoleError("File failed to open");
		return false;
	}

	// seek to the end of file
	file.seekg(0, IOS::end);

	// get the file size
	hINT fileSize = file.tellg();

	// iterate back to the beginning of the file
	file.seekg(0, IOS::beg);

	// reduce the file size by any header bytes that might be present
	fileSize -= file.tellg();

	buffer.resize(fileSize);

	// get the address of first element in the buffer (which is a c string)
	hCHAR* cBuffer = &(buffer[0]); 

	file.read(cBuffer, fileSize);
	file.close();

	return true;
}
