//*******************************//
//
// Name:			MatrixStack.h
// Description:		
//
// Author:			Edwin Chen
// Created:			Nov 13, 2016
// Last updated:	Nov 13, 2016
//
//*******************************//

#ifndef MATRIX_STACK_H
#define MATRIX_STACK_H

#include "Macro.h"
#include "HMath.h"

class MatrixStack {
public:
	MatrixStack();
	~MatrixStack() {}

	void Orthographic(hFLOAT xMin, hFLOAT xMax, hFLOAT yMin, hFLOAT yMax, hFLOAT zMin, hFLOAT zMax);
	void Perspective(hFLOAT fovy, hFLOAT aspect, hFLOAT nearZ, hFLOAT farZ);

	const MATRIX4 GetProjetionMatrix() const;
	const MATRIX4 GetModelMatrix() const;

	void PushModelView();
	void PopModelView();

	void PushProjection();
	void PopProjectionStack();

	void RotateBy(const QUATERNION& q);
	void RotateBy(hFLOAT angle, hFLOAT vx, hFLOAT vy, hFLOAT vz);
	void ScaleBy(hFLOAT xFactor, hFLOAT yFactor, hFLOAT zFactor);
	void TranslateBy(hFLOAT xAmt, hFLOAT yAmt, hFLOAT zAmt);

private:
	STACK(MATRIX4) _modelStack;
	STACK(MATRIX4) _projectionStack;
public:

};

#endif