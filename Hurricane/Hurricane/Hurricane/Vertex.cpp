#include "Vertex.h"
#include "Debug.h"

hINT VertexComponentDescriptor::GetSize() 
{
	hINT result = 0;

	switch (type)
	{
	case VERTEX_COMP_TYPE_IGNORE_3F:
	case VERTEX_COMP_TYPE_VERTEX_3F:
	case VERTEX_COMP_TYPE_NORMAL_3F:
	case VERTEX_COMP_TYPE_COLOR_3F:
		result = 3 * sizeof(hFLOAT);
		break;
	case VERTEX_COMP_TYPE_IGNORE_4F:
	case VERTEX_COMP_TYPE_COLOR_4F:
		result = 4 * sizeof(hFLOAT);
		break;
	case VERTEX_COMP_TYPE_IGNORE_2F:
	case VERTEX_COMP_TYPE_TEX1_2F:
	case VERTEX_COMP_TYPE_TEX2_2F:
	case VERTEX_COMP_TYPE_TEX3_2F:
	case VERTEX_COMP_TYPE_TEX4_2F:
	case VERTEX_COMP_TYPE_TEX5_2F:
	case VERTEX_COMP_TYPE_TEX6_2F:
	case VERTEX_COMP_TYPE_TEX7_2F:
	case VERTEX_COMP_TYPE_TEX8_2F:
		result = 2 * sizeof(hFLOAT);
		break;
	}

	return result;
}


hINT VertexComponentDescriptor::GetNumFloats() 
{
	hINT result = 0;

	switch (type)
	{
	case VERTEX_COMP_TYPE_IGNORE_3F:
	case VERTEX_COMP_TYPE_VERTEX_3F:
	case VERTEX_COMP_TYPE_NORMAL_3F:
	case VERTEX_COMP_TYPE_COLOR_3F:
		result = 3;
		break;
	case VERTEX_COMP_TYPE_IGNORE_4F:
	case VERTEX_COMP_TYPE_COLOR_4F:
		result = 4;
		break;
	case VERTEX_COMP_TYPE_IGNORE_2F:
	case VERTEX_COMP_TYPE_TEX1_2F:
	case VERTEX_COMP_TYPE_TEX2_2F:
	case VERTEX_COMP_TYPE_TEX3_2F:
	case VERTEX_COMP_TYPE_TEX4_2F:
	case VERTEX_COMP_TYPE_TEX5_2F:
	case VERTEX_COMP_TYPE_TEX6_2F:
	case VERTEX_COMP_TYPE_TEX7_2F:
	case VERTEX_COMP_TYPE_TEX8_2F:
		result = 2;
		break;
	}

	return result;
}

STRING VertexComponentDescriptor::ComponentTypeToString(VertexComponentType typ)
{
	STRING result;

	switch (typ)
	{
	case VERTEX_COMP_TYPE_IGNORE_3F:
		result = "IGNORE_3F";
		break;
	case VERTEX_COMP_TYPE_VERTEX_3F:
		result = "VERTEX_3F";
		break;
	case VERTEX_COMP_TYPE_NORMAL_3F:
		result = "NORMAL_3F";
		break;
	case VERTEX_COMP_TYPE_COLOR_3F:
		result = "COLOR_3F";
		break;
	case VERTEX_COMP_TYPE_IGNORE_4F:
		result = "IGNORE_4F";
		break;
	case VERTEX_COMP_TYPE_COLOR_4F:
		result = "COLOR_4F";
		break;
	case VERTEX_COMP_TYPE_IGNORE_2F:
		result = "IGNORE_2F";
		break;
	case VERTEX_COMP_TYPE_TEX1_2F:
		result = "TEXTURE1_2F";
		break;
	case VERTEX_COMP_TYPE_TEX2_2F:
		result = "TEXTURE2_2F";
		break;
	case VERTEX_COMP_TYPE_TEX3_2F:
		result = "TEXTURE3_2F";
		break;
	case VERTEX_COMP_TYPE_TEX4_2F:
		result = "TEXTURE4_2F";
		break;
	case VERTEX_COMP_TYPE_TEX5_2F:
		result = "TEXTURE5_2F";
		break;
	case VERTEX_COMP_TYPE_TEX6_2F:
		result = "TEXTURE6_2F";
		break;
	case VERTEX_COMP_TYPE_TEX7_2F:
		result = "TEXTURE7_2F";
		break;
	case VERTEX_COMP_TYPE_TEX8_2F:
		result = "TEXTURE8_2F";
		break;
	default:
		result = "UNKNOWN";
		break;
	}

	return result;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

VertexDescriptor::VertexDescriptor() {
	stride = 0;
	for (int i = 0; i < 12; i++) {
		componentIndex[i] = -1;
	}
}

VertexComponentDescriptor VertexDescriptor::GetComponent(hINT index) const
{
	VertexComponentDescriptor result;

	if (index < 0 || index >= ((int)componentList.size())) {
		Debug::ConsoleError("Component range out of bounds", __FILE__, __LINE__);
	}

	result = componentList[index];
	return result;
}