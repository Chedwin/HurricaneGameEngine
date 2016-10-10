//*******************************//
//
// Name:			IOManager.h
// Description:		A basic description of the header goes here.
//
// Author:			Edwin Chen
// Created:			Oct 09, 2016
// Last updated:	Oct 09, 2016
//
//*******************************//

#pragma once

#ifndef IO_MANAGER_H
#define IO_MANAGER_H

#include "Macro.h"

class IOManager
{
public:
	static hBOOL ReadFileToBuffer(const STRING filePath, VECTOR(hCHAR)& buffer);
};

#endif

