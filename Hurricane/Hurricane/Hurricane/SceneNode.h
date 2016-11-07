//*******************************//
//
// Name:			SceneNode.h
// Description:		
//
// Author:			Edwin Chen
// Created:			Nov 07, 2016
// Last updated:	Nov 07, 2016
//
//*******************************//

#ifndef SCENE_NODE_H
#define SCENE_NODE_H

#include "Macro.h"
#include "HMath.h"

class SceneNode {
public:
	SceneNode();
	~SceneNode();

public:
	VEC3			location;
	VEC3			scale;
	QUATERNION		orientation;
	VEC3			rotateAboutPt;
	QUATERNION		rotateAboutOrientation;

	SceneNode*		firstChild;
	SceneNode*		lastChild;
	SceneNode*		prevSibling;
	SceneNode*		nextSibling;
	SceneNode*		parent;

};

#endif