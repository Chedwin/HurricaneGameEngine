//*******************************//
//
// Name:			Rigidbody.h
// Description:		A basic description of the header goes here.
//
// Author:			Edwin Chen
// Created:			Oct 24, 2016
// Last updated:	Oct 24, 2016
//
//*******************************//

#pragma once

#include "Macro.h"
#include "Component.h"

#ifndef RIGIDBODY_H
#define RIGIDBODY_H

class Rigidbody : public Component 
{
public:
	Rigidbody();
	~Rigidbody();
};

#endif