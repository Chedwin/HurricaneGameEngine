#pragma once
#include <Macro.h>
#include <HMath.h>

class OBJLoader {
public:
	OBJLoader() {}
	~OBJLoader() {}

	hBOOL LoadOBJModel(const STRING& path, VECTOR(VEC3) & out_vertices, VECTOR(VEC2) & out_uvs, VECTOR(VEC3) & out_normals);
};