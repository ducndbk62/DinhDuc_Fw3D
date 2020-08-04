#pragma once
#include "../Utilities/utilities.h"

class Shaders 
{
public:
	GLuint program, vertexShader, fragmentShader;
	char fileVS[260];
	char fileFS[260];
	GLint positionAttribute;
	GLint iTextureLoc;
	GLint uvAttribute;
	GLint normAttribute;
	GLint binormAttribute;
	GLint tgtAttribute;
	GLint transMatLoc;

	int Init(char * fileVertexShader, char * fileFragmentShader);
	~Shaders();
};