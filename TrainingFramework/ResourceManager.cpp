#pragma warning(disable : 4996)
#include "stdafx.h"
#include "ResourceManager.h"

int Shaders::Init(char * fileVertexShader, char * fileFragmentShader)
{
	vertexShader = esLoadShader(GL_VERTEX_SHADER, fileVertexShader);

	if ( vertexShader == 0 )
		return -1;

	fragmentShader = esLoadShader(GL_FRAGMENT_SHADER, fileFragmentShader);

	if ( fragmentShader == 0 )
	{
		glDeleteShader( vertexShader );
		return -2;
	}

	program = esLoadProgram(vertexShader, fragmentShader);

	//finding location of uniforms / attributes
	positionAttribute = glGetAttribLocation(program, "a_posL");
	normAttribute = glGetAttribLocation(program, "a_norm");
	binormAttribute = glGetAttribLocation(program, "a_binorm");
	tgtAttribute = glGetAttribLocation(program, "a_tgt");
	uvAttribute = glGetAttribLocation(program, "a_uv");
	iTextureLoc = glGetUniformLocation(program, "u_texture");
	transMatLoc = glGetUniformLocation(program, "u_trans");

	return 0;
}

Shaders::~Shaders()
{
	glDeleteProgram(program);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}