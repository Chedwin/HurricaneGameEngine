//*******************************//
//
// Name:			Colour.h
// Description:		Specific the colour within the game engine.
//
// Author:			Mathieu Violette
//					James Sholdice
//					Nathan Senter
//
// Created:			Apr 19, 2016
// Last updated:	Nov 11, 2016
//
//*******************************//


#ifndef COLOR_H
#define COLOR_H

#include <SDL.h>
#include "Macro.h"

class Colour {
public:
	Colour(hFLOAT _r = 1, hFLOAT _g = 1, hFLOAT _b = 1, hFLOAT _a = 1);
	~Colour();

	hFLOAT r, g, b, a;

	/* Factories */
	static Colour Black();			static Colour Red();		static Colour Yellow();		static Colour Orange();			static Colour Lime();
	static Colour White();			static Colour Green();		static Colour Cyan();		static Colour Pink();			static Colour SpringGreen();
	static Colour Transparent();	static Colour Blue();		static Colour Magenta();	static Colour ManganeseBlue();	static Colour Fuchsia();
	static Colour Gray();


	// Operator overloading
	Colour operator+(const Colour&) const;
	Colour operator+=(const Colour&);
	void operator=(const Colour&);
	Colour operator-(const Colour&) const;
	Colour operator-=(const Colour&);
	Colour operator*(const hFLOAT&) const;
	Colour operator*=(const hFLOAT&);
	Colour operator/(const hFLOAT&) const;
	Colour operator/=(const hFLOAT&);

	STRING ToString();

	friend const Colour operator*(const hFLOAT&, const Colour&);

	operator SDL_Color() const;

private:
	//Returns a value between 1 and 0
	hFLOAT Limit(const hFLOAT _value) const;
	void Normalize();
};

#endif
