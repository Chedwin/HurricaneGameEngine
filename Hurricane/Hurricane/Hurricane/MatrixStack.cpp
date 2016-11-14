#include "MatrixStack.h"
#include "Debug.h"

MatrixStack::MatrixStack()
{
	MATRIX4 identity(1.0f), identity2(1.0f);
	_projectionStack.push(identity);
	_modelStack.push(identity2);
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void MatrixStack::Orthographic(hFLOAT xMin, hFLOAT xMax, hFLOAT yMin, hFLOAT yMax, hFLOAT zMin, hFLOAT zMax)
{
	_projectionStack.top() = glm::ortho(xMin, xMax, yMin, yMax, zMin, zMax);
}

void MatrixStack::Perspective(hFLOAT fovy, hFLOAT aspect, hFLOAT nearZ, hFLOAT farZ)
{
	_projectionStack.top() = glm::perspective(fovy, aspect, nearZ, farZ);
}

const MATRIX4 MatrixStack::GetProjetionMatrix() const
{
	if (_projectionStack.empty())
	{
		Debug::ConsoleError("Model matrix stack is EMPTY", __FILE__, __LINE__);
	}
	return _projectionStack.top();
}

const MATRIX4 MatrixStack::GetModelMatrix() const
{
	if (_modelStack.empty())
	{
		Debug::ConsoleError("Model matrix stack is EMPTY", __FILE__, __LINE__);
	}
	return _modelStack.top();
}

void MatrixStack::PushModelView()
{
	_modelStack.push(_modelStack.top());
}

void MatrixStack::PopModelView()
{
	if (_modelStack.empty())
	{
		Debug::ConsoleError("Model matrix stack is EMPTY", __FILE__, __LINE__);
	}
	_modelStack.pop();
}

void MatrixStack::PushProjection()
{
	_projectionStack.push(_projectionStack.top());
}

void MatrixStack::PopProjectionStack()
{
	if (_projectionStack.empty())
	{
		Debug::ConsoleError("Projection matrix stack is EMPTY", __FILE__, __LINE__);
	}
	_projectionStack.pop();
}

void MatrixStack::RotateBy(const QUATERNION& q)
{
	float angle = glm::angle(q);
	VEC3 vect = glm::axis(q);

	_modelStack.top() = _modelStack.top() * glm::rotate(MATRIX4(1.0f), angle, vect);
}

void MatrixStack::RotateBy(hFLOAT angle, hFLOAT vx, hFLOAT vy, hFLOAT vz)
{
	_modelStack.top() = _modelStack.top() * glm::rotate(MATRIX4(1.0f), angle, VEC3(vx, vy, vz));

}


void MatrixStack::ScaleBy(hFLOAT xFactor, hFLOAT yFactor, hFLOAT zFactor)
{
	_modelStack.top() = _modelStack.top() * glm::scale(MATRIX4(1.0f), VEC3(xFactor, yFactor, zFactor));

}


void MatrixStack::TranslateBy(hFLOAT xAmt, hFLOAT yAmt, hFLOAT zAmt)
{
	_modelStack.top() = _modelStack.top() * glm::translate(MATRIX4(1.0f), VEC3(xAmt, yAmt, zAmt));

}