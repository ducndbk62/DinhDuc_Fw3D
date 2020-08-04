#include "Object.h"
#include <stdio.h>

class Texture
{
public:
	void loadTexture(Object object, const char * NFGFile)
	{
		int NrVertices, VerId;
		int NrIndices, IndId;
		FILE *fp;
		float x = 0, y = 0, z = 0;
		fp = fopen(NFGFile, "r");
		fscanf(fp, "NrVertices: %d\n", &NrVertices);
		for (int i = 0; i < NrVertices; i++)
		{
			fscanf(fp, "%d. pos:[%f, %f, %f]; ", &VerId, &x, &y, &z);
			object.vertex[i].pos.x = x; object.vertex[i].pos.y = y; object.vertex[i].pos.z = z;
			fscanf(fp, "norm:[%f, %f, %f]; ", &x, &y, &z);
			object.vertex[i].normal.x = x; object.vertex[i].normal.y = y; object.vertex[i].normal.z = z;
			fscanf(fp, "binorm:[%f, %f, %f]; ", &x, &y, &z);
			object.vertex[i].binormal.x = x; object.vertex[i].binormal.y = y; object.vertex[i].binormal.z = z;
			fscanf(fp, "tgt:[%f, %f, %f]; ", &x, &y, &z);
			object.vertex[i].tangent.x = x; object.vertex[i].tangent.y = y; object.vertex[i].tangent.z = z;
			fscanf(fp, "uv:[%f, %f];\n", &x, &y);
			object.vertex[i].uv.x = x; object.vertex[i].uv.y = y;
		}
		fscanf(fp, "NrIndices: %d\n", &NrIndices);
		for (int i = 0; i < NrIndices / 3; i++)
		{
			fscanf(fp, "%d. %d, %d, %d \n", &IndId, &object.indices[3 * i], &object.indices[3 * i + 1], &object.indices[3 * i + 2]);
		}
	}
};
