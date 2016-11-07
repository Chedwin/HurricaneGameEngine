//*******************************//
//
// Name:			Color.h
// Description:		A basic description of the header goes here.
//
// Author:			Author Name
// Created:			Jan 01, 2016
// Last updated:	Jan 01, 2016
//
//*******************************//


#ifndef COLOR_H
#define COLOR_H

#include "Macro.h"

class Color 
{
private:
	float r, g, b, a;
public:
	/**
	* Constant for color red.
	*/
	static const Color RED;
	/**
	* Constant for color green.
	*/
	static const Color GREEN;
	/**
	* Constant for color blue.
	*/
	static const Color BLUE;
	/**
	* Constant for color yellow.
	*/
	static const Color YELLOW;
	/**
	* Constant for color white.
	*/
	static const Color WHITE;
	/**
	* Constant for color black.
	*/
	static const Color BLACK;
	/**
	* Constant for color pink.
	*/
	static const Color PINK;
	/**
	* Constant for color violet.
	*/
	static const Color VIOLET;
	/**
	* Constant for color purple.
	*/
	static const Color PURPLE;
	/**
	* Constant for color dark slate gray.
	*/
	static const Color DARKSLATEGRAY;
	/**
	* Constant for color spring green.
	*/
	static const Color SPRINGGREEN;
	/**
	* Constant for color sea green.
	*/
	static const Color SEAGREEN;
	/**
	* Constant for color emerald green.
	*/
	static const Color EMERALDGREEN;
	/**
	* Constant for color aquamarine.
	*/
	static const Color AQUAMARINE;
	/**
	* Constant for color emerald teal.
	*/
	static const Color TEAL;
	/**
	* Constant for color gold.
	*/
	static const Color GOLD;
	/**
	* Constant for color brick.
	*/
	static const Color BRICK;
	/**
	* Constant for color tan.
	*/
	static const Color TAN;
	/**
	* Constant for color chocolate.
	*/
	static const Color CHOCOLATE;
	/**
	* Constant for color orange.
	*/
	static const Color ORANGE;
	/**
	* Constant for color SIENNA.
	*/
	static const Color SIENNA;
	/**
	* Constant for color brown.
	*/
	static const Color BROWN;
	/**
	* Constant for color gray.
	*/
	static const Color GRAY;


	/**
	* Default constructor for opaque black.
	*/
	Color() :
		r(0.0f), g(0.0f), b(0.0f), a(1.0f)
	{}

	/**
	* Copy constructor.
	*/
	Color(const Color &clr) :
		r(clr.r), g(clr.g), b(clr.b), a(clr.a)
	{}

	/**
	* Constructor for colors specified as values from 0.0-1.0.
	* @param red red value from 0 - 1
	* @param green green value from 0 - 1
	* @param blue blue value from 0 - 1
	* @param alpha alpha value from 0 - 1
	*/
	Color(float red, float green, float blue, float alpha = 1.0f) :
		r(red), g(green), b(blue), a(alpha)
	{}

	/**
	* Constructor for colors specified as values from 0 - 255.
	* @param red red value from 0 - 255
	* @param green green value from 0 - 255
	* @param blue blue value from 0 - 255
	* @param alpha alpha value from 0 - 255
	*/
	Color(int red, int green, int blue, int alpha = 255)
	{
		r = red / 255.0f;
		g = green / 255.0f;
		b = blue / 255.0f;
		a = alpha / 255.0f;
	}

	/**
	* Construct a color from a string representation of the color.
	* The Color can in on one of the following forms:
	* <UL>
	* <LI>one of the names of the color constants </LI>
	* <LI> #rrggbb[aa] using hex values </LI>
	* <LI> %rrrgggbbb[aaa] using decimal values </LI>
	* </UL>
	* In the event the color cannot be decoded, black will be returned.
	*/
	Color(const std::string& clrString);

	/**
	* Convert one of the named colors to an actual color.
	* @param clrName one of the supported color names
	* @return the requested color black if the name is not known
	*/
	static Color nameToColor(const std::string& clrName);

	/**
	* Convert a hex representation of a color to an actual color.
	* @param clrName 6 hex digits representing RGB or 8 hex digits representing RGBA
	* @return the requested color
	*/
	static Color hexToColor(const std::string& clrName);

	/**
	* Convert a int representation of a color to an actual color.
	* @param clrName 9 int digits representing RGB or 12 int digits representing RGBA
	* @return the requested color
	*/
	static Color intToColor(const std::string& clrName);


	/**
	* Assignment operator.
	* @param clr the color to assign to this color.
	* @return a reference to the color assigned to
	*/
	Color& operator=(const Color &clr)
	{
		r = clr.r;
		g = clr.g;
		b = clr.b;
		a = clr.a;
		return *this;
	}

	friend bool operator==(const Color &c1, const Color &c2);

	/**
	* Return the red component of the color.
	* @return the red component from 0.0-1.0
	*/
	float getRed() const
	{
		return r;
	}

	/**
	* Return the green component of the color.
	* @return the green component from 0.0-1.0
	*/
	float getGreen() const
	{
		return g;
	}

	/**
	* Return the blue component of the color.
	* @return the blue component from 0.0-1.0
	*/
	float getBlue() const
	{
		return b;
	}

	/**
	* Return the alpha component of the color.
	* @return the alpha component from 0.0-1.0
	*/
	float getAlpha() const
	{
		return a;
	}

	/**
	* Sets the red component of the color.
	* @param red the value of red from 0.0-1.0
	*/
	void setRed(float red)
	{
		r = red;
	}

	/**
	* Sets the green component of the color.
	* @param green the value of green from 0.0-1.0
	*/
	void setGreen(float green)
	{
		g = green;
	}

	/**
	* Sets the blue component of the color.
	* @param blue the value of blue from 0.0-1.0
	*/
	void setBlue(float blue)
	{
		b = blue;
	}

	/**
	* Sets the alpha component of the color.
	* @param alpha the value of alpha from 0.0-1.0
	*/
	void setAlpha(float alpha)
	{
		a = alpha;
	}

	/**
	* Insertion operator for color.
	* @paran os the stream in which to insert
	* @param clr the color to insert
	*/
	friend std::ostream& operator<<(std::ostream &os, const Color &clr);

	/**
	* Convert color to a readable string
	* @return a readable string
	*/
	std::string toString();
};

#endif
