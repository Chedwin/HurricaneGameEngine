#include "Frustum.h"
#include "Debug.h"

#define ANG2RAD 3.14159265358979323846f / 180.0f

void Frustum::WindowResized(hFLOAT _angle, hFLOAT _ratio, hFLOAT nearD, hFLOAT farD)
{
	angle = _angle;
	ratio = _ratio;
	nearDist = nearD;
	farDist = farD;

	/////////////////////////////////////////////////////////
	// Compute width & height of near & far planes
	/////////////////////////////////////////////////////////
	tang = (hFLOAT)tan(ANG2RAD * angle * 0.5f);
	nearHt = nearDist * tang;
	nearWd = nearHt * ratio;
	farHt = farDist * tang;
	farWd = farHt * ratio;
}

void Frustum::CameraChanged(VEC3 &camPosn, VEC3 &lookAt, VEC3 &up)
{
	////////////////////////////////////////////////
	// Compute the view direction of the camera
	////////////////////////////////////////////////
	viewDir = glm::normalize(camPosn - lookAt);

	////////////////////////////////////////////////
	// The right vect is the up vector cross the view vector
	////////////////////////////////////////////////
	rightDir = glm::normalize(glm::cross(up, viewDir));

	/////////////////////////////////////////////////////////
	// Re-compute up vect as cross product of viewDie & rightDir
	/////////////////////////////////////////////////////////
	upDir = glm::cross(viewDir, rightDir);

	////////////////////////////////////////////////
	// Compute centres of near and far planes
	////////////////////////////////////////////////
	nearCent = camPosn - (viewDir * nearDist);
	farCent = camPosn - (viewDir * farDist);

	//////////////////////////////////////////////////
	// Compute 4 corners of near plane
	//////////////////////////////////////////////////
	ntl = nearCent + upDir * nearHt - rightDir * nearWd;
	ntr = nearCent + upDir * nearHt + rightDir * nearWd;
	nbl = nearCent - upDir * nearHt - rightDir * nearWd;
	nbr = nearCent - upDir * nearHt + rightDir * nearWd;

	//////////////////////////////////////////////////
	// Compute 4 corners of far plane
	//////////////////////////////////////////////////
	ftl = farCent + upDir * farHt - rightDir * farWd;
	ftr = farCent + upDir * farHt + rightDir * farWd;
	fbl = farCent - upDir * farHt - rightDir * farWd;
	fbr = farCent - upDir * farHt + rightDir * farWd;

	//////////////////////////////////////////////////
	// Compute the 6 planes
	//////////////////////////////////////////////////
	planes[TOPP] = Plane(ntr, ntl, ftl);
	planes[BOTTOMP] = Plane(nbl, nbr, fbr);
	planes[LEFTP] = Plane(ntl, nbl, fbl);
	planes[RIGHTP] = Plane(nbr, ntr, fbr);
	planes[NEARP] = Plane(ntl, ntr, nbr);
	planes[FARP] = Plane(ftr, ftl, fbl);
}

Frustum::EnclosureType Frustum::IsInside(VEC3 &pt)
{
	for (hINT i = 0; i < 6; i++)
	{
		if (planes[i].SignedDistance(pt) < 0)
		{	
			return OUTSIDE;
		}
	}
	return INSIDE;
}

Frustum::EnclosureType Frustum::IsInside(VEC3 &cent, hFLOAT radius)
{
	hFLOAT distance;
	EnclosureType result = INSIDE;

	for (hINT i = 0; i < 6; i++)
	{
		distance = planes[i].SignedDistance(cent);

		if (distance < -radius)
		{
			return OUTSIDE;
		}
		else if (distance < radius) 
		{
			result = OVERLAP;
		}
	}
	return result;
}