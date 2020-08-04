#include "../Utilities/utilities.h" // if you use STL, please include this line AFTER all other include
#include "ResourceManager.h"
#include "Globals.h"
#include <stdio.h>
#include "Object.h"
//#include "Texture.h"

class Model
{
public:
	//Object object;
	
	void loadObject(Object* object);
	int Init(ESContext *esContext, Object *object);
	void changeObjAppear(Object object);
	void paintObject(ESContext *esContext, Object *object);
};