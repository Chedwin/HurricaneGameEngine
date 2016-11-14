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
#include "Transform.h"
#include "GameObject.h"

class SceneNode {
public:
	SceneNode();
	~SceneNode();

	void SetLocation(const VEC3& loc);



	void SetRotateAbout(const VEC3& pt, const QUATERNION& rotation);
	void GetRotateAbout(VEC3& pt, QUATERNION& rotation);



	void AppendChild(SceneNode *node);
	void RemoveChild(SceneNode *node);

	void AddModel(GameObject* model);
	void RemoveModel(GameObject* model);

public:
	Transform		transform;

	VEC3			rotateAboutPt;
	QUATERNION		rotateAboutOrientation;

	SceneNode*		firstChild;
	SceneNode*		lastChild;
	SceneNode*		prevSibling;
	SceneNode*		nextSibling;
	SceneNode*		parent;

	VECTOR(GameObject*) gameObjectList;

	typedef VECTOR(GameObject*)::iterator sceneIterator;
};

#endif