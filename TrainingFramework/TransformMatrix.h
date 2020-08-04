#include "../Utilities/utilities.h" // if you use STL, please include this line AFTER all other include
#ifndef TransformMatrix_HEADER
#define TransformMatrix_HEADER

class TransformMatrix
{
public:
	GLfloat moveSpeed;
	GLfloat sensitivity;
public:
	// matrix in world camera
	Matrix scaleMat = scaleMat.SetIdentity();
	Matrix rotationXMat = rotationXMat.SetIdentity();
	Matrix rotationYMat = rotationYMat.SetIdentity();
	Matrix rotationZMat = rotationZMat.SetIdentity();
	Matrix translationMat = translationMat.SetIdentity();
	Matrix wMat = wMat.SetIdentity();

	// matrix in view camera
	Matrix scaleMat_1 = scaleMat.SetIdentity();
	Matrix rotationXMat_1 = rotationXMat.SetIdentity();
	Matrix rotationYMat_1 = rotationYMat.SetIdentity();
	Matrix rotationZMat_1 = rotationZMat.SetIdentity();
	Matrix translationMat_1 = translationMat.SetIdentity();
	Matrix vMat = vMat.SetIdentity();

	Matrix pMat = pMat.SetIdentity(); // Perspective camera
	Matrix wvpMat = wvpMat.SetIdentity(); // WVP
	
	// function
	void setScaleMat(GLfloat scaleX, GLfloat scaleY, GLfloat scaleZ);
	void setRotationXMat(GLfloat angle);
	void setRotationYMat(GLfloat angle);
	void setRotationZMat(GLfloat angle);
	void setTranslationMat(GLfloat x, GLfloat y, GLfloat z);
	void calWMat();
	void calVMat();
	void setPMat(GLfloat fovY, GLfloat aspect, GLfloat nearPlane, GLfloat farPlane);
	void calWVPMat();
};
#endif