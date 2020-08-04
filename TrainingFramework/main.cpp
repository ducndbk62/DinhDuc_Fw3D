// TrainingFramework.cpp : Defines the entry point for the console application.


#include "stdafx.h"
#include "../Utilities/utilities.h" // if you use STL, please include this line AFTER all other include
#include "Vertex.h"
#include "TransformMatrix.h"
#include "ResourceManager.h"
#include "Globals.h"
#include <conio.h>
#include "Model.h"


Model model;
Object object;


void LoadNFGFile()
{
	model.loadObject(&object);
}

int Init(ESContext *esContext)
{
	return model.Init(esContext, &object);
}

void Draw ( ESContext *esContext )
{
	model.paintObject(esContext, &object);
}

void Update ( ESContext *esContext, float deltaTime )
{

}

void Key ( ESContext *esContext, unsigned char key, bool bIsPressed)
{
	switch (key)
	{
	case 'w':
		break;
	}
}

void CleanUp()
{
	glDeleteBuffers(1, &object.vboId);
}

int _tmain(int argc, _TCHAR* argv[])
{
	ESContext esContext;

    esInitContext ( &esContext );

	esCreateWindow ( &esContext, "Hello Triangle", Globals::screenWidth, Globals::screenHeight, ES_WINDOW_RGB | ES_WINDOW_DEPTH);

	if ( Init(&esContext) != 0 )
		return 0;

	esRegisterDrawFunc ( &esContext, Draw );
	esRegisterUpdateFunc ( &esContext, Update );
	esRegisterKeyFunc ( &esContext, Key);

	esMainLoop ( &esContext );

	//releasing OpenGL resources
	CleanUp();

	//identifying memory leaks
	MemoryDump();
	printf("Press any key...\n");
	_getch();

	return 0;
}

