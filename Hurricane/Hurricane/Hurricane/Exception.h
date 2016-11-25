//*******************************//
//
// Name:			Exception.h
// Description:		
//
// Author:			Edwin Chen
// Created:			Nov 24, 2016
// Last updated:	Nov 24, 2016
//
//*******************************//


#ifndef EXCEPTION_H
#define EXCEPTION_H

#include "Macro.h"
#include <exception>

class Exception : public _exception {
public:
	Exception() = delete;
	~Exception() = delete;
};

#endif