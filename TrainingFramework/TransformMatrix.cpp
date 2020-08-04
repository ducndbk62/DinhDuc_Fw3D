#include "stdafx.h"
#include "TransformMatrix.h"

void TransformMatrix::setScaleMat(GLfloat scaleX, GLfloat scaleY, GLfloat scaleZ)
{
	scaleMat = scaleMat.SetScale(scaleX, scaleY, scaleZ);
	scaleMat_1 = scaleMat_1.SetScale(1.0f / scaleX, 1.0f / scaleY, 1.0f / scaleZ);
	calWVPMat();
}

void TransformMatrix::setRotationXMat(GLfloat angle)
{
	rotationXMat = rotationXMat.SetRotationX(angle);
	rotationXMat_1 = rotationXMat_1.SetRotationX(-angle);
	calWVPMat();
}

void TransformMatrix::setRotationYMat(GLfloat angle)
{
	rotationYMat = rotationYMat.SetRotationY(angle);
	rotationYMat_1 = rotationYMat_1.SetRotationY(-angle);
	calWVPMat();
}

void TransformMatrix::setRotationZMat(GLfloat angle)
{
	rotationZMat = rotationZMat.SetRotationZ(angle);
	rotationZMat_1 = rotationZMat_1.SetRotationZ(-angle);
	calWVPMat();
}

void TransformMatrix::setTranslationMat(GLfloat x, GLfloat y, GLfloat z)
{
	translationMat = translationMat.SetTranslation(x, y, z);
	translationMat_1 = translationMat_1.SetTranslation(-x, -y, -z);
	calWVPMat();
}

void TransformMatrix::calWMat()
{
	wMat = scaleMat * rotationZMat * rotationXMat * rotationYMat * translationMat;
}

void TransformMatrix::calVMat()
{
	vMat = translationMat_1 * rotationYMat_1 * rotationXMat_1 * rotationZMat_1 * scaleMat_1;
}

void TransformMatrix::setPMat(GLfloat fovY, GLfloat aspect, GLfloat nearPlane, GLfloat farPlane)
{
	pMat = pMat.SetPerspective(fovY, aspect, nearPlane, farPlane);
}

void TransformMatrix::calWVPMat()
{
	calWMat();
	calVMat();
	wvpMat = wMat * vMat;
}
/*
void Camera::cameraForward()
{

}
void Camera::cameraBackward();
void Camera::cameraRight();
void Camera::cameraLeft();*/