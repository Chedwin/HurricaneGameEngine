//*******************************//
//
// Name:			Frustum.h
//
// Description:		The frustum is the conical section of space with its apex at the eye of the viewer and
//					its far end at the farthest distance the viewer can see.The actual view seen by a human
//					has an oval shape where the width is slightly greater than the height.The reason for this
//					is that our 2 eyes let us see more along the horizontal axis than the vertical axis.
//
//					This class approximates the conical shape of the scene viewed by a human by using
//					2 planes to represent the near and far limits of what can be seen.A further 4 planes
//					delimit the sides of the frustum.While using planes results in an approximation, it
//					is close enough and easire to calculate than using a true conical shape.
//
//					The frustum must be updated :
//						-every time the application window is resized
//						-whenever the camera position or orientation changes
//
// Author:			Edwin Chen
// Created:			Oct 24, 2016
// Last updated:	Nov 14, 2016
//
//*******************************//


#ifndef FRUSTUM_H
#define FRUSTUM_H

#include "Macro.h"
#include "HMath.h"
#include "Plane.h"


class Frustum {
protected:
	/** The names of the 6 planes */
	enum PlaneNames 
	{
		NEARP, FARP, TOPP, BOTTOMP, RIGHTP, LEFTP
	};

	/** The camera position at the apex of the frustum */
	VEC3										camPos;
	/** A normalized vector looking in the same direction as the camera */
	VEC3										viewDir;
	/** Distance from the camera to the near plane */
	hFLOAT											nearDist;
	/** Distance from the camera to the far plane */
	hFLOAT											farDist;
	/** The centre of the near plane */
	VEC3										nearCent;
	/** The centre of the far plane */
	VEC3										farCent;
	/** Width of the near plane */
	hFLOAT											nearWd;
	/** Height of the near plane */
	hFLOAT											nearHt;
	/** Width of the far plane */
	hFLOAT											farWd;
	/** Height of the far plane */
	hFLOAT											farHt;
	/** A normalized vector pointing up WRT the camera */
	VEC3										upDir;
	/** A normalized vector pointing right WRT the camera */
	VEC3										rightDir;
	/** The 6 planes delimiting the frustum */
	Plane											planes[6];
	/** The corner points of the near and far planes */
	VEC3										ntl, nbl, nbr, ntr, ftl, fbl, fbr, ftr;
	/** The ratio from the graphics system perspective calculations */
	hFLOAT											ratio;
	/** The angle of the field of view */
	hFLOAT											angle;
	/** Tangent of half the angle */
	hFLOAT											tang;
public:
	/** Used to determine if an object is inside the frustum */
	enum EnclosureType 
	{
		INSIDE, OUTSIDE, OVERLAP
	};

	Frustum() {}

	/**
	* This handles the situation where the window is resized.  It updates the
	* internal variables to reflect the new window size.
	* @param _angle The field of view angle
	* @param _ratio The ratio used in the perspective
	* @param nearD Distance from eye to near plane
	* @param farD Distance from eye to far plane
	*/
	void WindowResized(hFLOAT _angle, hFLOAT _ratio, hFLOAT nearD, hFLOAT farD);

	/**
	* This is called to recompute the frustum every time the position of the
	* camera changes.
	* @param camPosn The position of the camera
	* @param lookAt The point at which the camera is looking
	* @param up The up vector for the camera
	*/
	void CameraChanged(VEC3 &camPosn, VEC3 &lookAt, VEC3 &up);

	/**
	* Determine if a point is inside the frustum.
	* @param pt The point to check to see if inside the frustum
	* @return Whether the point is inside, outside or overlapping the frustum
	*/
	EnclosureType IsInside(VEC3 &pt);

	/**
	* Determine if a sphere is inside the frustum.
	* @param cent The centre of the sphere
	* @param radius The radius of the sphere
	* @return Whether the sphere is inside, outside or overlapping the frustum
	*/
	EnclosureType IsInside(VEC3 &cent, hFLOAT radius);

};

#endif