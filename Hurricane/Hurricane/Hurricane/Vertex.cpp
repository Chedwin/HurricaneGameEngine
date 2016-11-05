#include "Vertex.h"

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