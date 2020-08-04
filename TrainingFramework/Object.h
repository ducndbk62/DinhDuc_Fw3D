
#include "TransformMatrix.h"
#include "Vertex.h"
#include "../Utilities/utilities.h"

class Object
{
public:
	int indicesCount;
	Vertex vertex[1024];
	GLuint indices[3000];
	Shaders shaders;
	GLuint vboId;
	GLuint iboId;
	GLuint textureId;
	TransformMatrix transMat;

	// function
};