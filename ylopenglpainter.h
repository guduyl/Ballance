
#ifndef YLOPENGLPAINTER_H
#define YLOPENGLPAINTER_H

#include "ylqtwidgetheader.h"



class YLOpenGLPainter
{
public:
	YLOpenGLPainter();
	~YLOpenGLPainter();

	static void ShowScreen1(const QQuaternion *quaternion, const GLuint *texture, QMatrix4x4 *eyematrix);
	static void ShowScreen2(const QQuaternion *quaternion, const GLuint *texture, QMatrix4x4 *eyematrix);
	static void ShowScreen3(const QQuaternion *quaternion, const GLuint *texture, QMatrix4x4 *eyematrix);
	static void ShowScreen4(const QQuaternion *quaternion, const GLuint *texture, QMatrix4x4 *eyematrix);
	static void SetDrawAttr(const QVector3D &vector, const QQuaternion *quaternion, const GLuint *texture, QMatrix4x4 *eyematrix);
	static void DrawTriangle();
	static void DrawSquare();
	static void DrawHexagon();
	static void DrawpYramid();
	static void DrawMagicCube();
	static void DrawOrb(double radius, int slices, int stacks);
};

#endif // YLOPENGLPAINTER_H
