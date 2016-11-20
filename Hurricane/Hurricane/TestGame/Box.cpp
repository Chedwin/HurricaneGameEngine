#include <Debug.h>
#include <TextureManager.h>


#include "Box.h"




Box::Box() : GameObject()
{
	//myCubeTexture = new Texture("textures/leafsman.png", "Leafs Man");
	//TEXTURE_MANAGER->UploadTexture(myCubeTexture->GetResourceName(), myCubeTexture);

	//glGenTextures(1, texture);
	//glBindTexture(GL_TEXTURE_2D, texture[0]);

	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, myCubeTexture->GetWidth(), myCubeTexture->GetHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, myCubeTexture->GetPixels());

	//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	//glGenerateMipmap(GL_TEXTURE_2D);

	//glGenBuffers(3, buffers);
	//glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	//glEnableVertexAttribArray(0);

	//glBindBuffer(GL_ARRAY_BUFFER, buffers[1]);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);
	//glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, 0, (void*)0);
	//glEnableVertexAttribArray(1);

	//glBindBuffer(GL_ARRAY_BUFFER, buffers[2]);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(g_uv_buffer_data), g_uv_buffer_data, GL_STATIC_DRAW);
	//glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
	//glEnableVertexAttribArray(2);



	//VECTOR(VEC3) vertices;
	//VECTOR(VEC2) uvs;
	//VECTOR(VEC3) normals;


	//glGenBuffers(2, buffers);
	//glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
	//glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(VEC3), &vertices[0], GL_STATIC_DRAW);
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	//glEnableVertexAttribArray(0);


	//glBindBuffer(GL_ARRAY_BUFFER, buffers[1]);
	//glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(VEC2), &uvs[0], GL_STATIC_DRAW);
	//glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
	//glEnableVertexAttribArray(1);


	//glActiveTexture(GL_TEXTURE0);
	//// Set our "myTextureSampler" sampler to user Texture Unit 0
	//glUniform1i(texture[0], 0);
}

Box::~Box() 
{
	//glDeleteTextures(1, texture);
	//glDeleteBuffers(2, buffers);
}


void Box::Render() 
{
	
	//glBindTexture(GL_TEXTURE_2D, texture[0]);
	//glDrawArrays(GL_TRIANGLES, 0, NumVertices);
}