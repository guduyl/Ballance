
#include "ballance.h"
#include "ballancepathopenglwidget.h"
#include "ylopenglpainter.h"





BallancepathOpenglWidget::BallancepathOpenglWidget(QWidget *parent) :
	QGLWidget(parent),
	m_parent((Ballance *)parent),

	m_punTexture(new GLuint[10]),
	m_mtx4Eye(),
	m_qtnPath(),
	m_vct4Ball(0, 0, 0),
	m_qtnBall(),
	m_fBallSpeed(1)
{
	QVector3D delta;
	//调整看点
	delta = QVector3D(0, -1, 0).normalized();
	for (int i = 0; i < 12; i++)
		m_mtx4Eye.translate(delta);
	m_mtx4Eye.rotate(36, 1, 0, 0);
	//调整地图旋转度
	delta = QVector3D(1, 0, 0).normalized();
	m_qtnPath = QQuaternion::fromAxisAndAngle(delta, -90) * m_qtnPath;
	//调整球体旋转度使球表面显示合适的图案
//	delta = QVector3D(1, 0, 0).normalized();
//	m_qtnBall = QQuaternion::fromAxisAndAngle(delta, -90) * m_qtnBall;
//	delta = QVector3D(0, 1, 0).normalized();
//	m_qtnBall = QQuaternion::fromAxisAndAngle(delta, -90) * m_qtnBall;
	delta = QVector3D(0, 0, 1).normalized();
	m_qtnBall = QQuaternion::fromAxisAndAngle(delta, -90) * m_qtnBall;
//	m_qtnBall = m_qtnBall * m_qtnPath;
//	m_qtnBall = m_qtnPath * m_qtnBall;
	//调整球体位置
	m_vct4Ball += QVector3D(0, 0, 1);
}



BallancepathOpenglWidget::~BallancepathOpenglWidget()
{
	delete[] m_punTexture;
}





/**
 * @brief BallancepathOpenglWidget::initializeGL
 *		此处开始对OpenGL进行所以设置
 */
void BallancepathOpenglWidget::initializeGL()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_SMOOTH);													//启用阴影平滑
	glClearDepth(1.0);															//设置深度缓存
	glEnable(GL_DEPTH_TEST);													//启用深度测试
	glDepthFunc(GL_LEQUAL);														//所作深度测试的类型
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);							//告诉系统对透视进行修正
	this->LoadTexture();
	glEnable(GL_TEXTURE_2D);
}



/**
 * @brief BallancepathOpenglWidget::resizeGL
 *		重置OpenGL窗口的大小
 */
void BallancepathOpenglWidget::resizeGL(int w, int h)
{
	glViewport(0, 0, (GLint)w, (GLint)h);										//重置当前的视口
	glMatrixMode(GL_PROJECTION);												//选择投影矩阵
	glLoadIdentity();															//重置投影矩阵

	gluPerspective(45.0, (GLfloat)w/(GLfloat)h, 0.1, 100.0);					//设置视口的大小
	glMatrixMode(GL_MODELVIEW);													//选择模型观察矩阵
	glLoadIdentity();															//重置模型观察矩阵
}



/**
 * @brief BallancepathOpenglWidget::paintGL
 *		从这里开始进行所以的绘制
 */
#define MMM 1
void BallancepathOpenglWidget::paintGL()
{
//	qDebug() << "BallancepathOpenglWidget::paintGL: ";

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);							//清除屏幕和深度缓存
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	QMatrix4x4 matrix;
	matrix.setToIdentity();
	matrix.translate(QVector3D(0, 0, -16*MMM));
	matrix = m_mtx4Eye * matrix;												//设置看点

	//绘制地图
	matrix.rotate(m_qtnPath);													//设置地图旋转度
	glLoadMatrixf(matrix.data());
	glBindTexture(GL_TEXTURE_2D, m_punTexture[0]);
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
		glVertex3f(-32*MMM, i*MMM, 0);
		glVertex3f(32*MMM, i*MMM, 0);
		glVertex3f(i*MMM, -32*MMM, 0);
		glVertex3f(i*MMM, 32*MMM, 0);
	}
	glEnd();
	glColor3f(1.0, 1.0, 1.0);

	//绘制球体
	matrix.translate(m_vct4Ball);												//设置球体位置
//	m_qtnBall = QQuaternion::fromAxisAndAngle(QVector3D(1, 0, 0).normalized(), 90) * m_qtnBall;
	matrix.rotate(m_qtnBall);													//设置球体旋转度
	glLoadMatrixf(matrix.data());
	glBindTexture(GL_TEXTURE_2D, m_punTexture[6]);
	YLOpenGLPainter::DrawOrb(1*MMM, 30, 30);
}





bool BallancepathOpenglWidget::event(QEvent *event)
{
	//以下键盘消息本widget将忽略，由父widget处理
	if (event->type() == QEvent::KeyPress)
	{
		int keyid = static_cast<QKeyEvent *>(event)->key();
		if (keyid == Qt::Key_F11 || keyid == Qt::Key_Escape)
		{
			qDebug() << "BallancepathOpenglWidget::event: " << "ignored: " << "Key_F11 || Key_Escape";
			return false;
		}
	}

	return QWidget::event(event);
}



void BallancepathOpenglWidget::keyPressEvent(QKeyEvent *event)
{
	float fDeltaAngleX = 0;
	float fDeltaAngleY = 0;
	float fDeltaAngleZ = 0;
//	float fDeltaEyeX = 0;
//	float fDeltaEyeY = 0;
//	float fDeltaEyeZ = 0;

	switch (event->key())
	{
	case Qt::Key_Up:
	{
		qDebug() << "BallancepathOpenglWidget::keyPressEvent: " << "Key_Up-";

		--fDeltaAngleX;
		break;
	}
	case Qt::Key_Down:
	{
		qDebug() << "BallancepathOpenglWidget::keyPressEvent: " << "Key_Down+";

		++fDeltaAngleX;
		break;
	}
	case Qt::Key_Left:
	{
		qDebug() << "BallancepathOpenglWidget::keyPressEvent: " << "Key_Left-";

		--fDeltaAngleY;
//		++fDeltaAngleZ;
		break;
	}
	case Qt::Key_Right:
	{
		qDebug() << "BallancepathOpenglWidget::keyPressEvent: " << "Key_Right+";

		++fDeltaAngleY;
//		--fDeltaAngleZ;
		break;
	}
	case Qt::Key_PageUp:
	{
		qDebug() << "BallancepathOpenglWidget::keyPressEvent: " << "Key_PageUp+";

//		++fDeltaEyeZ;
		break;
	}
	case Qt::Key_PageDown:
	{
		qDebug() << "BallancepathOpenglWidget::keyPressEvent: " << "Key_PageDown-";

//		--fDeltaEyeZ;
		break;
	}
	case Qt::Key_Pause:
	case Qt::Key_P:
	{
		qDebug() << "BallancepathOpenglWidget::keyPressEvent: " << "Key_Pause || Key_P";
		break;
	}
	default: break;
	}

	if (fDeltaAngleX != 0 || fDeltaAngleY != 0 || fDeltaAngleZ != 0)
	{
		QVector3D delta;
//		delta = QVector3D(fDeltaAngleY / 100, fDeltaAngleY / 100, fDeltaAngleZ / 100);
		delta = QVector3D(-fDeltaAngleY / 100, 0, -fDeltaAngleX / 100);
		m_mtx4Eye.translate(delta);
		delta = QVector3D(fDeltaAngleY / 100, -fDeltaAngleX / 100, 0);
		m_vct4Ball += delta;
		delta = QVector3D(fDeltaAngleX, fDeltaAngleY, fDeltaAngleZ).normalized();
		m_qtnBall = QQuaternion::fromAxisAndAngle(delta, m_fBallSpeed) * m_qtnBall;

		this->updateGL();
	}
}





/**
 * @brief BallancepathOpenglWidget::LoadTexture
 *		载入纹理
 */
void BallancepathOpenglWidget::LoadTexture()
{
	QImage buf, tex;

	buf.load(":/bgimg/mmexport1502771182717.png");
	tex = QGLWidget::convertToGLFormat(buf);
	//创建一个纹理
	glGenTextures(1, &m_punTexture[1]);
	//使用来自位图数据生成的典型纹理,纹理名字texture[1]绑定到纹理目标上
	glBindTexture(GL_TEXTURE_2D, m_punTexture[1]);
	//真正的创建纹理
	glTexImage2D(GL_TEXTURE_2D, 0, 3, tex.width(), tex.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, tex.bits());
	//滤波方式
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	buf.load(":/bgimg/mmexport1507349001837.png");
	tex = QGLWidget::convertToGLFormat(buf);
	glGenTextures(1, &m_punTexture[2]);
	glBindTexture(GL_TEXTURE_2D, m_punTexture[2]);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, tex.width(), tex.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, tex.bits());
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	buf.load(":/bgimg/mmexport1507349023277.png");
	tex = QGLWidget::convertToGLFormat(buf);
	glGenTextures(1, &m_punTexture[3]);
	glBindTexture(GL_TEXTURE_2D, m_punTexture[3]);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, tex.width(), tex.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, tex.bits());
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	buf.load(":/bgimg/mmexport1507349027215.png");
	tex = QGLWidget::convertToGLFormat(buf);
	glGenTextures(1, &m_punTexture[4]);
	glBindTexture(GL_TEXTURE_2D, m_punTexture[4]);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, tex.width(), tex.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, tex.bits());
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	buf.load(":/bgimg/mmexport1507349033771.png");
	tex = QGLWidget::convertToGLFormat(buf);
	glGenTextures(1, &m_punTexture[5]);
	glBindTexture(GL_TEXTURE_2D, m_punTexture[5]);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, tex.width(), tex.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, tex.bits());
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	buf.load(":/bgimg/map.jpg");
	tex = QGLWidget::convertToGLFormat(buf);
	glGenTextures(1, &m_punTexture[6]);
	glBindTexture(GL_TEXTURE_2D, m_punTexture[6]);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, tex.width(), tex.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, tex.bits());
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

}


























































