//*******************************//
//
// Name:			HurricaneTestBed
// Description:		Welcome to Hurricane's main tester!
//					Use this main function to test simple engine functionalities or components created by Hurricane.
//
// Author:			Edwin Chen
// Created:			Nov 19, 2016
// Last updated:	Dec 10, 2016
//
//*******************************//

#include <Macro.h>
#include <Debug.h>
#include <HMath.h>

///// OTHER INCLUDES HERE ///
#include <MatrixStack.h>
/////////////////////////////


hINT main(hINT argc, hCHAR** argv) 
{
	MatrixStack ms;
	ms.RotateBy(QUATERNION());
	
	GETCHAR();
	return 0;
}