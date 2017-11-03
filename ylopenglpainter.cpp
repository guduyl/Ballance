
#include "ylopenglpainter.h"



#define MMM 1



YLOpenGLPainter::YLOpenGLPainter()
{
	qDebug() << "YLOpenGLPainter::YLOpenGLPainter";

}



YLOpenGLPainter::~YLOpenGLPainter()
{
	qDebug() << "YLOpenGLPainter::~YLOpenGLPainter";

}





void YLOpenGLPainter::ShowScreen1(const QQuaternion *quaternion, const GLuint *texture, QMatrix4x4 *eyematrix)
{
	qDebug() << "YLOpenGLPainter::ShowScreen1";

	//屏幕上方
	SetDrawAttr(QVector3D(-6*MMM, 4*MMM, -16*MMM), quaternion, &texture[1], eyematrix);
	DrawTriangle();
	SetDrawAttr(QVector3D(0, 4*MMM, -16*MMM), quaternion, &texture[2], eyematrix);
	DrawSquare();
	SetDrawAttr(QVector3D(6*MMM, 4*MMM, -16*MMM), quaternion, &texture[3], eyematrix);
	DrawHexagon();
	//屏幕下方
	SetDrawAttr(QVector3D(-6*MMM, -3*MMM, -16*MMM), quaternion, &texture[4], eyematrix);
	DrawpYramid();
	SetDrawAttr(QVector3D(0, -3*MMM, -16*MMM), quaternion, &texture[5], eyematrix);
	DrawMagicCube();
	SetDrawAttr(QVector3D(6*MMM, -3*MMM, -16*MMM), quaternion, &texture[6], eyematrix);
	DrawOrb(2*MMM, 30, 30);
}

void YLOpenGLPainter::ShowScreen2(const QQuaternion *quaternion, const GLuint *texture, QMatrix4x4 *eyematrix)
{
	qDebug() << "YLOpenGLPainter::ShowScreen2";

	//屏幕上方
	SetDrawAttr(QVector3D(-6*MMM, 4*MMM, -16*MMM), quaternion, &texture[1], eyematrix);
	DrawOrb(2*MMM, 10, 10);
	SetDrawAttr(QVector3D(0, 4*MMM, -16*MMM), quaternion, &texture[2], eyematrix);
	DrawOrb(2*MMM, 20, 20);
	SetDrawAttr(QVector3D(6*MMM, 4*MMM, -16*MMM), quaternion, &texture[3], eyematrix);
	DrawOrb(2*MMM, 30, 30);
	//屏幕下方
	SetDrawAttr(QVector3D(-6*MMM, -3*MMM, -16*MMM), quaternion, &texture[4], eyematrix);
	DrawOrb(2*MMM, 40, 40);
	SetDrawAttr(QVector3D(0, -3*MMM, -16*MMM), quaternion, &texture[5], eyematrix);
	DrawOrb(2*MMM, 50, 50);
	SetDrawAttr(QVector3D(6*MMM, -3*MMM, -16*MMM), quaternion, &texture[6], eyematrix);
	DrawOrb(2*MMM, 60, 60);
}

void YLOpenGLPainter::ShowScreen3(const QQuaternion *quaternion, const GLuint *texture, QMatrix4x4 *eyematrix)
{
	qDebug() << "YLOpenGLPainter::ShowScreen3";

	//屏幕中央
	SetDrawAttr(QVector3D(0, 0, -16*MMM), quaternion, &texture[0], eyematrix);
//	glRotatef(-90, 1, 0, 0);
	glLineWidth(3);
	glBegin(GL_LINES);
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(-32*MMM, 0, 0);
	glColor3f(1.0, 1.0, 1.0);
	glVertex3f(32*MMM, 0, 0);
	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(0, -32*MMM, 0);
	glColor3f(1.0, 1.0, 1.0);
	glVertex3f(0, 32*MMM, 0);
	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(0, 0, -32*MMM);
	glColor3f(1.0, 1.0, 1.0);
	glVertex3f(0, 0, 32*MMM);
	glEnd();
	glLineWidth(1);
	glBegin(GL_LINES);
	glColor3f(1.0, 1.0, 0.0);
	for (int i = -32; i <= 32; ++i)
	{
		if (i == 0)
			continue;
		glVertex3f(-32*MMM, i, 0);
		glVertex3f(32*MMM, i, 0);
		glVertex3f(i, -32*MMM, 0);
		glVertex3f(i, 32*MMM, 0);
	}
	glEnd();
	glColor3f(1.0, 1.0, 1.0);
}

void YLOpenGLPainter::ShowScreen4(const QQuaternion *quaternion, const GLuint *texture, QMatrix4x4 *eyematrix)
{
	qDebug() << "YLOpenGLPainter::ShowScreen4";

	//屏幕
}



void YLOpenGLPainter::SetDrawAttr(const QVector3D &vector, const QQuaternion *quaternion, const GLuint *texture, QMatrix4x4 *eyematrix)
{
	qDebug() << "YLOpenGLPainter::SetDrawAttr";

	glLoadIdentity();
	QMatrix4x4 matrix;
	matrix.setToIdentity();
	matrix.translate(vector);
	if (quaternion != NULL)
		matrix.rotate(*quaternion);
	if (eyematrix != NULL)
		matrix = *eyematrix * matrix;
	glLoadMatrixf(matrix.data());
	if (texture != NULL)
		glBindTexture(GL_TEXTURE_2D, *texture);
}



/**
 * @brief YLOpenGLPainter::DrawTriangle
 *		三角形
 */
void YLOpenGLPainter::DrawTriangle()
{
	qDebug() << "YLOpenGLPainter::DrawTriangle";

	glBegin(GL_TRIANGLES);
	glColor3f(1.0, 0.0, 0.0);
	glTexCoord2f(0.5, 1.0);
	glVertex3f(0, 2*MMM, 0);
	glColor3f(0.0, 1.0, 0.0);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(2*MMM, -2*MMM, 0);
	glColor3f(0.0, 0.0, 1.0);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-2*MMM, -2*MMM, 0);
	glEnd();
}



/**
 * @brief YLOpenGLPainter::DrawSquare
 *		正方形
 */
void YLOpenGLPainter::DrawSquare()
{
	qDebug() << "YLOpenGLPainter::DrawSquare";

	glColor3f(1.0, 1.0, 0.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(-2*MMM, 2*MMM, 0);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(2*MMM, 2*MMM, 0);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(2*MMM, -2*MMM, 0);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-2*MMM, -2*MMM, 0);
	glEnd();
}



/**
 * @brief YLOpenGLPainter::DrawHexagon
 *		正六边形
 */
void YLOpenGLPainter::DrawHexagon()
{
	qDebug() << "YLOpenGLPainter::DrawHexagon";

	glBegin(GL_POLYGON);
	glColor3f(1.0, 0.0, 0.0);
	glTexCoord2f(0.289, 1.0);
	glVertex3f(-MMM, 1.732*MMM, 0);
	glColor3f(1.0, 1.0, 0.0);
	glTexCoord2f(0.711, 1.0);
	glVertex3f(1*MMM, 1.732*MMM, 0);
	glColor3f(0.0, 1.0, 0.0);
	glTexCoord2f(1.0, 0.5);
	glVertex3f(2*MMM, 0, 0);
	glColor3f(0.0, 1.0, 1.0);
	glTexCoord2f(0.711, 0.0);
	glVertex3f(1*MMM, -1.732*MMM, 0);
	glColor3f(0.0, 0.0, 1.0);
	glTexCoord2f(0.289, 0.0);
	glVertex3f(-1*MMM, -1.732*MMM, 0);
	glColor3f(1.0, 0.0, 1.0);
	glTexCoord2f(0.0, 0.5);
	glVertex3f(-2*MMM, 0, 0);
	glEnd();
}



/**
 * @brief YLOpenGLPainter::DrawpYramid
 *		金字塔
 */
void YLOpenGLPainter::DrawpYramid()
{
	qDebug() << "YLOpenGLPainter::DrawpYramid";

	glBegin(GL_TRIANGLES);
	//前
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(0, 2*MMM, 0);
	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(2*MMM, -2*MMM, 2*MMM);
	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(-2*MMM, -2*MMM, 2*MMM);
	//右
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(0, 2*MMM, 0);
	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(2*MMM, -2*MMM, -2*MMM);
	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(2*MMM, -2*MMM, 2*MMM);
	//后
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(0, 2*MMM, 0);
	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(-2*MMM, -2*MMM, -2*MMM);
	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(2*MMM, -2*MMM, -2*MMM);
	//左
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(0, 2*MMM, 0);
	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(-2*MMM, -2*MMM, 2*MMM);
	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(-2*MMM, -2*MMM, -2*MMM);
	glEnd();
	//底
	glBegin(GL_QUADS);
	glColor3f(0.0, 1.0, 0.0);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-2*MMM, -2*MMM, -2*MMM);
	glColor3f(0.0, 0.0, 1.0);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(2*MMM, -2*MMM, -2*MMM);
	glColor3f(0.0, 1.0, 0.0);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(2*MMM, -2*MMM, 2*MMM);
	glColor3f(0.0, 0.0, 1.0);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(-2*MMM, -2*MMM, 2*MMM);
	glEnd();
}



/**
 * @brief YLOpenGLPainter::DrawMagicCube
 *		魔方
 */
void YLOpenGLPainter::DrawMagicCube()
{
	qDebug() << "YLOpenGLPainter::DrawMagicCube";

	glBegin(GL_QUADS);
	//上 红
	glColor3f(1.0, 0.0, 0.0);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(-2*MMM, 2*MMM, -2*MMM);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(2*MMM, 2*MMM, -2*MMM);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(2*MMM, 2*MMM, 2*MMM);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-2*MMM, 2*MMM, 2*MMM);
	//前 蓝
	glColor3f(0.0, 0.0, 1.0);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(-2*MMM, 2*MMM, 2*MMM);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(2*MMM, 2*MMM, 2*MMM);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(2*MMM, -2*MMM, 2*MMM);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-2*MMM, -2*MMM, 2*MMM);
	//右 白
	glColor3f(1.0, 1.0, 1.0);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(2*MMM, 2*MMM, 2*MMM);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(2*MMM, 2*MMM, -2*MMM);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(2*MMM, -2*MMM, -2*MMM);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(2*MMM, -2*MMM, 2*MMM);
	//后 绿
	glColor3f(0.0, 1.0, 0.0);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(2*MMM, 2*MMM, -2*MMM);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(-2*MMM, 2*MMM, -2*MMM);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(-2*MMM, -2*MMM, -2*MMM);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(2*MMM, -2*MMM, -2*MMM);
	//左 黄
	glColor3f(1.0, 1.0, 0.0);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(-2*MMM, 2*MMM, -2*MMM);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(-2*MMM, 2*MMM, 2*MMM);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(-2*MMM, -2*MMM, 2*MMM);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-2*MMM, -2*MMM, -2*MMM);
	//下 橘
	glColor3f(0.98, 0.5, 0.0);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(-2*MMM, -2*MMM, 2*MMM);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(2*MMM, -2*MMM, 2*MMM);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(2*MMM, -2*MMM, -2*MMM);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-2*MMM, -2*MMM, -2*MMM);
	glEnd();
	//线
	glLineWidth(8);
	glBegin(GL_LINES);
	glColor3f(0.0, 0.0, 0.0);
	//上 横
	glVertex3f(-2*MMM, 2*MMM, 1*MMM);
	glVertex3f(2*MMM, 2*MMM, 1*MMM);
	glVertex3f(-2*MMM, 2*MMM, 0*MMM);
	glVertex3f(2*MMM, 2*MMM, 0*MMM);
	glVertex3f(-2*MMM, 2*MMM, -1*MMM);
	glVertex3f(2*MMM, 2*MMM, -1*MMM);
	//上 竖
	glVertex3f(1*MMM, 2*MMM, -2*MMM);
	glVertex3f(1*MMM, 2*MMM, 2*MMM);
	glVertex3f(0*MMM, 2*MMM, -2*MMM);
	glVertex3f(0*MMM, 2*MMM, 2*MMM);
	glVertex3f(-1*MMM, 2*MMM, -2*MMM);
	glVertex3f(-1*MMM, 2*MMM, 2*MMM);
	//前 横
	glVertex3f(-2*MMM, 1*MMM, 2*MMM);
	glVertex3f(2*MMM, 1*MMM, 2*MMM);
	glVertex3f(-2*MMM, 0*MMM, 2*MMM);
	glVertex3f(2*MMM, 0*MMM, 2*MMM);
	glVertex3f(-2*MMM, -1*MMM, 2*MMM);
	glVertex3f(2*MMM, -1*MMM, 2*MMM);
	//前 竖
	glVertex3f(1*MMM, -2*MMM, 2*MMM);
	glVertex3f(1*MMM, 2*MMM, 2*MMM);
	glVertex3f(0*MMM, -2*MMM, 2*MMM);
	glVertex3f(0*MMM, 2*MMM, 2*MMM);
	glVertex3f(-1*MMM, -2*MMM, 2*MMM);
	glVertex3f(-1*MMM, 2*MMM, 2*MMM);
	//右 横
	glVertex3f(2*MMM, 1*MMM, -2*MMM);
	glVertex3f(2*MMM, 1*MMM, 2*MMM);
	glVertex3f(2*MMM, 0*MMM, -2*MMM);
	glVertex3f(2*MMM, 0*MMM, 2*MMM);
	glVertex3f(2*MMM, -1*MMM, -2*MMM);
	glVertex3f(2*MMM, -1*MMM, 2*MMM);
	//右 竖
	glVertex3f(2*MMM, -2*MMM, 1*MMM);
	glVertex3f(2*MMM, 2*MMM, 1*MMM);
	glVertex3f(2*MMM, -2*MMM, 0*MMM);
	glVertex3f(2*MMM, 2*MMM, 0*MMM);
	glVertex3f(2*MMM, -2*MMM, -1*MMM);
	glVertex3f(2*MMM, 2*MMM, -1*MMM);
	//后 横
	glVertex3f(-2*MMM, 1*MMM, -2*MMM);
	glVertex3f(2*MMM, 1*MMM, -2*MMM);
	glVertex3f(-2*MMM, 0*MMM, -2*MMM);
	glVertex3f(2*MMM, 0*MMM, -2*MMM);
	glVertex3f(-2*MMM, -1*MMM, -2*MMM);
	glVertex3f(2*MMM, -1*MMM, -2*MMM);
	//后 竖
	glVertex3f(1*MMM, -2*MMM, -2*MMM);
	glVertex3f(1*MMM, 2*MMM, -2*MMM);
	glVertex3f(0*MMM, -2*MMM, -2*MMM);
	glVertex3f(0*MMM, 2*MMM, -2*MMM);
	glVertex3f(-1*MMM, -2*MMM, -2*MMM);
	glVertex3f(-1*MMM, 2*MMM, -2*MMM);
	//左 横
	glVertex3f(-2*MMM, 1*MMM, -2*MMM);
	glVertex3f(-2*MMM, 1*MMM, 2*MMM);
	glVertex3f(-2*MMM, 0*MMM, -2*MMM);
	glVertex3f(-2*MMM, 0*MMM, 2*MMM);
	glVertex3f(-2*MMM, -1*MMM, -2*MMM);
	glVertex3f(-2*MMM, -1*MMM, 2*MMM);
	//左 竖
	glVertex3f(-2*MMM, -2*MMM, 1*MMM);
	glVertex3f(-2*MMM, 2*MMM, 1*MMM);
	glVertex3f(-2*MMM, -2*MMM, 0*MMM);
	glVertex3f(-2*MMM, 2*MMM, 0*MMM);
	glVertex3f(-2*MMM,-2*MMM,  -1*MMM);
	glVertex3f(-2*MMM, 2*MMM, -1*MMM);
	//下 横
	glVertex3f(-2*MMM, -2*MMM, 1*MMM);
	glVertex3f(2*MMM, -2*MMM, 1*MMM);
	glVertex3f(-2*MMM, -2*MMM, 0*MMM);
	glVertex3f(2*MMM, -2*MMM, 0*MMM);
	glVertex3f(-2*MMM, -2*MMM, -1*MMM);
	glVertex3f(2*MMM, -2*MMM, -1*MMM);
	//下 竖
	glVertex3f(1*MMM, -2*MMM, -2*MMM);
	glVertex3f(1*MMM, -2*MMM, 2*MMM);
	glVertex3f(0*MMM, -2*MMM, -2*MMM);
	glVertex3f(0*MMM, -2*MMM, 2*MMM);
	glVertex3f(-1*MMM, -2*MMM, -2*MMM);
	glVertex3f(-1*MMM, -2*MMM, 2*MMM);
	glEnd();
	glLineWidth(1);
}



/**
 * @brief YLOpenGLPainter::DrawOrb
 *		球体
 */
#define PI 2.1415926f
void YLOpenGLPainter::DrawOrb(double radius, int slices, int stacks)
{
	qDebug() << "YLOpenGLPainter::DrawOrb";

//	glColor4f(1, 1, 1, 1);
	GLUquadricObj *qobj = gluNewQuadric();
	gluQuadricTexture(qobj, GL_TRUE);
	gluSphere(qobj, radius, slices, stacks);
}



















































