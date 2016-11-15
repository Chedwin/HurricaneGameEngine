//*******************************//
//
// Name:			Plane.h
// Description:		This represents a plane by storing the equation of the plane plus a point on the plane.
//					The equation of a plane has the form  aX + bY + cZ + d = 0.  The first 3 values, a, b, and c,
//					form a normalized vector which is normal to the plane.The value of d represents the
//					distance of the plane from the origin.
//
// Author:			
// Created:			Nov 14, 2016
// Last updated:	Nov 14, 2016
//
//*******************************//


#ifndef PLANE_H
#define PLANE_H

#include "Macro.h"
#include "HMath.h"


class Plane
{
private:
	/** This is a point on the plane */
	VEC3						point;
	/** These are the multipliers for the equation of the plane aX + bY + cZ +d = 0 */
	hFLOAT								a, b, c, d;
public:

	Plane() :
		a(0.0), b(1.0), c(0.0), d(0.0), point(VEC3(0.0, 0.0, 0.0)) {}


	Plane(hFLOAT _a, hFLOAT _b, hFLOAT _c, hFLOAT _d, VEC3 &pt);


	Plane(VEC3 &p1, VEC3 &p2, VEC3 &p3);

	VEC3 GetNormal() const;

	/**
	* Return the distance of the plane from the origin (d).  This assumed all
	* values have been normalized.
	* @return The distance from the origin
	*/
	hFLOAT GetDistance() const;

	/**
	* Assignment operator.
	* @param other The plane to assign to this plane
	* @return a reference to the plane to which the value was assigned
	*/
	Plane& operator=(const Plane &other);

	/**
	* Equality operator.
	* @param a First plane to compare
	* @param b second plane to compare
	* @return true if the planes are equal
	*/
	friend hBOOL operator==(const Plane &a, const Plane &b);

	/**
	* Inequality operator.
	* @param a First plane to compare
	* @param b second plane to compare
	* @return true if the planes are not equal
	*/
	friend hBOOL operator!=(const Plane &a, const Plane &b);

	/**
	* Compute the signed distance from the plane to a point.  The sign of the
	* distance tells you what side of the plane the point lies on.  If the
	* signed distance is negative, then the point lies on the side opposite
	* the normal.  We use the formula N dot pt + D = 0 to compute the distance
	* and just evaluate the left side of the equation.
	* @param pt The point to determine the distance of
	* @return the signed distance from the plane to the point
	*/
	hFLOAT SignedDistance(VEC3 &pt);

};

#endif

