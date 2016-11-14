//*******************************//
//
// Name:			Random.h
// Description:		Generate random floating pointing numbers if required.
//
// Authors:			Mathieu Violette
//					James Sholdice
//					Nathan Senter
//
// Created:			Apr 19, 2016
// Last updated:	Nov 13, 2016
//
//*******************************//


#ifndef CLASS_NAME_H
#define CLASS_NAME_H

#include "Macro.h"

class Random {
private:
	static hINT seed;
	static long ran1idnum;
	static hINT qd2idnum;
public:
	Random();
	~Random();

	static hDOUBLE rand(hDOUBLE low, hDOUBLE high);
	static hINT rand(hINT low, hINT high);
	static hDOUBLE ran1();
	static hFLOAT box_muller(hFLOAT m, hFLOAT s);

	static inline hDOUBLE ranqd2() {
		unsigned long itemp;
		static unsigned long jflone = 0x3f800000;
		static unsigned long jflmsk = 0x007fffff;

		qd2idnum = 1664525L * qd2idnum + 1013904223L;
		itemp = jflone | (jflmsk & qd2idnum);
		return (hDOUBLE)(*(hFLOAT *)&itemp) - 1.0;
	}

};


#endif