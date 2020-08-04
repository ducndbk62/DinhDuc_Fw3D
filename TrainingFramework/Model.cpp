
#pragma warning(disable : 4996)
#include "Model.h"

void Model::loadObject(Object* object)
{
	int NrVertices, VerId;
	int IndId;
	FILE *fp;
	float x = 0, y = 0, z = 0;
	fp = fopen("E:/Gameloft/DinhDuc_Framework3D/Resources/Models/Woman1.nfg", "r");
	fscanf(fp, "NrVertices: %d\n", &NrVertices);
	for (int i = 0; i < NrVertices; i++)
	{
		fscanf(fp, "%d. pos:[%f, %f, %f]; ", &VerId, &x, &y, &z);
		object->vertex[i].pos.x = x; object->vertex[i].pos.y = y; object->vertex[i].pos.z = z;
		fscanf(fp, "norm:[%f, %f, %f]; ", &x, &y, &z);
		object->vertex[i].normal.x = x; object->vertex[i].normal.y = y; object->vertex[i].normal.z = z;
		fscanf(fp, "binorm:[%f, %f, %f]; ", &x, &y, &z);
		object->vertex[i].binormal.x = x; object->vertex[i].binormal.y = y; object->vertex[i].binormal.z = z;
		fscanf(fp, "tgt:[%f, %f, %f]; ", &x, &y, &z);
		object->vertex[i].tangent.x = x; object->vertex[i].tangent.y = y; object->vertex[i].tangent.z = z;
		fscanf(fp, "uv:[%f, %f];\n", &x, &y);
		object->vertex[i].uv.x = x; object->vertex[i].uv.y = y;
	}
	fscanf(fp, "NrIndices: %d\n", &object->indicesCount);
	for (int i = 0; i < object->indicesCount / 3; i++)
	{
		fscanf(fp, "%d. %d, %d, %d \n", &IndId, &object->indices[3 * i], &object->indices[3 * i + 1], &object->indices[3 * i + 2]);
	}
}

int Model::Init(ESContext *esContext, Object *object)
{
	Model::loadObject(object);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	glGenTextures(1, &object->textureId);
	glBindTexture(GL_TEXTURE_2D, object->textureId);

	int iWidth = 0;
	int iHeight = 0;
	int ibpp = 0;
	char *imageData = LoadTGA("E:/Gameloft/DinhDuc_Framework3D/Resources/Textures/Woman1.tga", &iWidth, &iHeight, &ibpp);

	if (ibpp == 24) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, iWidth, iHeight, 0,
			GL_RGB, GL_UNSIGNED_BYTE, imageData);
	}
	else {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, iWidth, iHeight, 0,
			GL_RGBA, GL_UNSIGNED_BYTE, imageData);
	}
	//buffer object

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glBindTexture(GL_TEXTURE_2D, 0);

	glGenBuffers(1, &object->vboId);
	glBindBuffer(GL_ARRAY_BUFFER, object->vboId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(object->vertex), object->vertex, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &object->iboId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, object->iboId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(object->indices), object->indices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glEnable(GL_DEPTH_TEST);

	//creation of shaders and program 
	return object->shaders.Init("../Resources/Shaders/TriangleShaderVS.vs", "../Resources/Shaders/TriangleShaderFS.fs");
}

void Model::changeObjAppear(Object object)
{

}

void Model::paintObject(ESContext *esContext, Object *object)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(object->shaders.program);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, object->textureId);

	glBindBuffer(GL_ARRAY_BUFFER, object->vboId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, object->iboId);

	if (object->shaders.positionAttribute != -1)
	{
		glEnableVertexAttribArray(object->shaders.positionAttribute);
		glVertexAttribPointer(object->shaders.positionAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	}

	if (object->shaders.normAttribute != -1)
	{
		glEnableVertexAttribArray(object->shaders.normAttribute);
		glVertexAttribPointer(object->shaders.normAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (char*)0 + sizeof(Vector3));
	}

	if (object->shaders.binormAttribute != -1)
	{
		glEnableVertexAttribArray(object->shaders.binormAttribute);
		glVertexAttribPointer(object->shaders.binormAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
			(char*)0 + sizeof(Vector3) + sizeof(Vector3));
	}

	if (object->shaders.tgtAttribute != -1)
	{
		glEnableVertexAttribArray(object->shaders.tgtAttribute);
		glVertexAttribPointer(object->shaders.tgtAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
			(char*)0 + sizeof(Vector3) + sizeof(Vector3) + sizeof(Vector3));
	}

	glEnableVertexAttribArray(object->shaders.uvAttribute);
	glVertexAttribPointer(object->shaders.uvAttribute, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
		(char*)0 + sizeof(Vector3) + sizeof(Vector3) + sizeof(Vector3) + sizeof(Vector3));

	//camera.setPMat(0.8f, Globals::screenWidth / Globals::screenHeight, 0.1f, 100.0f);
	//object->transMat.setTranslationMat(0.0f, -1.0f, 0.0f);
	//object->transMat.setScaleMat(1.5f, 1.5f, 1.5f);
	//camera.setRotationYMat(0.5f);

	glUniformMatrix4fv(object->shaders.transMatLoc, 1, GL_FALSE, (GLfloat*)&object->transMat.wMat);
	glUniform1i(object->shaders.iTextureLoc, 0);

	glDrawElements(GL_TRIANGLES, object->indicesCount, GL_UNSIGNED_INT, 0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);

	eglSwapBuffers(esContext->eglDisplay, esContext->eglSurface);
}