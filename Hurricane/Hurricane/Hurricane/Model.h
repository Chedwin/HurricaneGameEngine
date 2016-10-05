//*******************************//
//
// Name:			Model.h
// Description:		A basic description of the header goes here.
//
// Author:			Edwin Chen
// Created:			Oct 03, 2016
// Last updated:	Oct 03, 2016
//
//*******************************//

#pragma once


#ifndef MODEL_H
#define MODEL_H

#include "Macro.h"

class Model 
{
	virtual void Render() = 0;
};

class SimpleModel : public Model 
{
	void Render() {}
};

#endif