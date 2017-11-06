
#include "ballance.h"
#include "ballancepath.h"
#include "ballancepathopenglwidget.h"
#include "ylopenglpainter.h"





BallancepathOpenglWidget::BallancepathOpenglWidget(QWidget *parent) :
	QGLWidget(parent),
	m_parent((Ballance *)parent),
	m_Path(new CBallancePath),
	m_punTexture(new GLuint[10])
{
	qDebug() << "BallancepathOpenglWidget::BallancepathOpenglWidget";

	m_pnlBall = new YLNaturalLaw(1, 10, 0.1);
	m_pnlBall->setForce(10);
	m_pnlBall->setMaxVelocity(10);

	this->ResetGame();

}



BallancepathOpenglWidget::~BallancepathOpenglWidget()
{
	qDebug() << "BallancepathOpenglWidget::~BallancepathOpenglWidget";

	this->m_parent->setStatus(Ballance::GAMESTATUS_OVER);

	delete m_Path;
	delete[] m_punTexture;
	delete m_pnlBall;
}





/**
 * @brief BallancepathOpenglWidget::initializeGL
 *		此处开始对OpenGL进行所以设置
 */
void BallancepathOpenglWidget::initializeGL()
{
	qDebug() << "BallancepathOpenglWidget::initializeGL";

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_SMOOTH);													//启用阴影平滑
	glClearDepth(1.0);															//设置深度缓存
	glEnable(GL_DEPTH_TEST);													//启用深度测试
	glDepthFunc(GL_LEQUAL);														//所作深度测试的类型
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);							//告诉系统对透视进行修正

	glEnable(GL_TEXTURE_2D);
	this->LoadTexture();
}



/**
 * @brief BallancepathOpenglWidget::resizeGL
 *		重置OpenGL窗口的大小
 */
void BallancepathOpenglWidget::resizeGL(int w, int h)
{
//	qDebug() << "BallancepathOpenglWidget::resizeGL";

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
#define COORDINATELENGTH 100
void BallancepathOpenglWidget::paintGL()
{
//	qDebug() << "BallancepathOpenglWidget::paintGL";

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);							//清除屏幕和深度缓存
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

//	YLOpenGLPainter::ShowScreen1(NULL, m_punTexture + 6, NULL);
//	return ;

	QMatrix4x4 matrix;
	matrix.setToIdentity();
	matrix.translate(QVector3D(0, 0, -24));
	matrix = m_mtx4Eye * matrix;												//设置看点

	//绘制坐标系
	matrix.rotate(m_qtnPath);													//设置地图旋转度
	glLoadMatrixf(matrix.data());
//	this->PaintCoordinate();

	//绘制地图
	this->PaintPath();

	//绘制球体
	matrix.translate(m_vct3Ball);												//设置球体位置
	matrix.rotate(m_qtnBall);													//设置球体旋转度
	glLoadMatrixf(matrix.data());
	this->PaintBall();

	//开启定时器
	if (this->m_parent->getStatus() == Ballance::GAMESTATUS_START)
	{
		m_nTmrMoveEverything = this->startTimer(30);
	}
}





/**
 * @brief BallancepathOpenglWidget::event
 *		预处理事件
 * @param event
 * @return
 */
bool BallancepathOpenglWidget::event(QEvent *event)
{
//	qDebug() << "BallancepathOpenglWidget::event";

	if (event->type() == QEvent::KeyPress)
	{
		int keyid = static_cast<QKeyEvent *>(event)->key();
		//以下键盘消息本widget将忽略，由父widget处理
		if (keyid == Qt::Key_F11 || keyid == Qt::Key_Escape)
		{
//			qDebug() << "BallancepathOpenglWidget::event" << "ignored" << "Key_F11 || Key_Escape";
			return false;
		}
		else if (this->m_parent->getStatus() != Ballance::GAMESTATUS_START)
		{
			return true;
		}
	}

	return QWidget::event(event);
}



/**
 * @brief BallancepathOpenglWidget::timerEvent
 *		定时器事件
 * @param event
 */
void BallancepathOpenglWidget::timerEvent(QTimerEvent *event)
{
//	qDebug() << "BallancepathOpenglWidget::timerEvent";

	if (event->timerId() == m_nTmrMoveEverything)
	{
		this->MoveEverything();
	}
}



/**
 * @brief BallancepathOpenglWidget::keyPressEvent
 *		键盘按下事件
 * @param event
 */
void BallancepathOpenglWidget::keyPressEvent(QKeyEvent *event)
{
//	qDebug() << "BallancepathOpenglWidget::keyPressEvent";

	if (this->IsAutoRepeatKeyEvent(event))
		return ;

	switch (event->key())
	{
	case Qt::Key_W:
	case Qt::Key_Up:
	{
//		qDebug() << "BallancepathOpenglWidget::keyPressEvent" << "Key_Up-ax";

		m_bPressBnW = true;
		break;
	}
	case Qt::Key_S:
	case Qt::Key_Down:
	{
//		qDebug() << "BallancepathOpenglWidget::keyPressEvent" << "Key_Down+ax";

		m_bPressBnS = true;
		break;
	}
	case Qt::Key_A:
	case Qt::Key_Left:
	{
//		qDebug() << "BallancepathOpenglWidget::keyPressEvent" << "Key_Left-ay";

		m_bPressBnA = true;
		break;
	}
	case Qt::Key_D:
	case Qt::Key_Right:
	{
//		qDebug() << "BallancepathOpenglWidget::keyPressEvent" << "Key_Right+ay";

		m_bPressBnD = true;
		break;
	}
	case Qt::Key_PageUp:
	{
//		qDebug() << "BallancepathOpenglWidget::keyPressEvent" << "Key_PageUp";

		break;
	}
	case Qt::Key_PageDown:
	{
//		qDebug() << "BallancepathOpenglWidget::keyPressEvent" << "Key_PageDown";

		break;
	}
	case Qt::Key_Pause:
	case Qt::Key_P:
	{
//		qDebug() << "BallancepathOpenglWidget::keyPressEvent" << "Key_Pause || Key_P";
		break;
	}
	default: break;
	}
}



/**
 * @brief BallancepathOpenglWidget::keyReleaseEvent
 *		键盘释放事件
 * @param event
 */
void BallancepathOpenglWidget::keyReleaseEvent(QKeyEvent *event)
{
//	qDebug() << "BallancepathOpenglWidget::keyReleaseEvent";

	if (this->IsAutoRepeatKeyEvent(event))
		return ;

	switch (event->key())
	{
	case Qt::Key_W:
	case Qt::Key_Up:
	{
//		qDebug() << "BallancepathOpenglWidget::keyReleaseEvent" << "Key_Up-ax";

		m_bPressBnW = false;
		break;
	}
	case Qt::Key_S:
	case Qt::Key_Down:
	{
//		qDebug() << "BallancepathOpenglWidget::keyReleaseEvent" << "Key_Down+ax";

		m_bPressBnS = false;
		break;
	}
	case Qt::Key_A:
	case Qt::Key_Left:
	{
//		qDebug() << "BallancepathOpenglWidget::keyReleaseEvent" << "Key_Left-ay";

		m_bPressBnA = false;
		break;
	}
	case Qt::Key_D:
	case Qt::Key_Right:
	{
//		qDebug() << "BallancepathOpenglWidget::keyReleaseEvent" << "Key_Right+ay";

		m_bPressBnD = false;
		break;
	}
	default: break;
	}
}





/**
 * @brief BallancepathOpenglWidget::IsAutoRepeatKeyEvent
 *		以下键盘消息应该直接忽略
 * @param QKeyEvent
 * @return 是否应该忽略该键盘消息
 */
bool BallancepathOpenglWidget::IsAutoRepeatKeyEvent(QKeyEvent *event)
{
//	qDebug() << "BallancepathOpenglWidget::IsAutoRepeatKeyEvent";

	int keyid = event->key();
	if ((event)->isAutoRepeat() &&
		(keyid == Qt::Key_W || keyid == Qt::Key_Up ||
		 keyid == Qt::Key_S || keyid == Qt::Key_Down ||
		 keyid == Qt::Key_A || keyid == Qt::Key_Left ||
		 keyid == Qt::Key_D || keyid == Qt::Key_Right))
	{
//		qDebug() << "BallancepathOpenglWidget::IsAutoRepeatKeyEvent" << "ignored";
		return true;
	}
	else
	{
		return false;
	}
}



/**
 * @brief BallancepathOpenglWidget::LoadTexture
 *		载入纹理
 */
void BallancepathOpenglWidget::LoadTexture()
{
	qDebug() << "BallancepathOpenglWidget::LoadTexture";

	QImage buf, tex;

	buf.load(":/bgimg/map.jpg");
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
}



/**
 * @brief BallancepathOpenglWidget::PaintCoordinate
 *		绘制坐标系
 */
void BallancepathOpenglWidget::PaintCoordinate()
{
//	qDebug() << "BallancepathOpenglWidget::PaintCoordinate";

	glBindTexture(GL_TEXTURE_2D, m_punTexture[0]);
	glLineWidth(3);
	glBegin(GL_LINES);
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(-COORDINATELENGTH, 0, 0);
	glColor3f(0.0, 1.0, 1.0);
	glVertex3f(COORDINATELENGTH, 0, 0);
	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(0, -COORDINATELENGTH, 0);
	glColor3f(1.0, 0.0, 1.0);
	glVertex3f(0, COORDINATELENGTH, 0);
	glEnd();
	glLineWidth(1);
	glBegin(GL_LINES);
	for (int i = -COORDINATELENGTH; i <= COORDINATELENGTH; ++i)
	{
		if (i == 0)
			continue;
		glColor3f(0.0, 0.0, 1.0);
		glVertex3f(-COORDINATELENGTH, i, 0);
		glColor3f(1.0, 1.0, 0.0);
		glVertex3f(COORDINATELENGTH, i, 0);
		glColor3f(0.0, 0.0, 1.0);
		glVertex3f(i, -COORDINATELENGTH, 0);
		glColor3f(1.0, 1.0, 0.0);
		glVertex3f(i, COORDINATELENGTH, 0);
	}
	glEnd();
	glColor3f(1.0, 1.0, 1.0);
	glPointSize(5);
	glBegin(GL_POINTS);
	for (int i = -COORDINATELENGTH; i <= COORDINATELENGTH; i += 10)
	{
		for (int j = -COORDINATELENGTH; j <= COORDINATELENGTH; j += 10)
		{
			glVertex3f(i, j, 0);
		}
	}
	glEnd();
	glPointSize(1);
}



/**
 * @brief BallancepathOpenglWidget::PaintPath
 *		绘制地图
 */
void BallancepathOpenglWidget::PaintPath()
{
//	qDebug() << "BallancepathOpenglWidget::PaintPath";

	glBindTexture(GL_TEXTURE_2D, m_punTexture[0]);
	glLineWidth(8);
	int gameres = m_Path->foreachPathUnit(m_vct3Ball, [&](const CBallancePath::PathUnit &pu)
	{
		glRectf(pu.posx1, pu.posy1, pu.posx2, pu.posy2);
	});
	glLineWidth(1);
	this->CheckGameStatus(gameres);
}



/**
 * @brief BallancepathOpenglWidget::PaintBall
 *		绘制球体
 */
void BallancepathOpenglWidget::PaintBall()
{
//	qDebug() << "BallancepathOpenglWidget::PaintBall";

	glBindTexture(GL_TEXTURE_2D, m_punTexture[1]);
	GLUquadricObj *qobj = gluNewQuadric();
	gluQuadricTexture(qobj, GL_TRUE);
	gluSphere(qobj, 1, 30, 30);
}



/**
 * @brief BallancepathOpenglWidget::MoveEverything
 *		场景移动
 */
void BallancepathOpenglWidget::MoveEverything()
{
//	qDebug() << "BallancepathOpenglWidget::MoveEverything";

	this->killTimer(m_nTmrMoveEverything);

	float fDeltaAngleX = (float)m_bPressBnD - (float)m_bPressBnA;
	float fDeltaAngleY = (float)m_bPressBnW - (float)m_bPressBnS;
	float fDeltaAngleZ = 0;

	QVector3D delta;

	delta = QVector3D(fDeltaAngleX, fDeltaAngleY, fDeltaAngleZ).normalized();
	QVector3D speed = m_pnlBall->newVelocity(delta, 0.03) / 30;

	delta = QVector3D(-speed.x(), speed.z(), speed.y());
	m_mtx4Eye.translate(delta);
	m_vct3Ball += speed;
	delta = QVector3D(-speed.y(), speed.x(), speed.z()).normalized();
	float angle = 180 * sqrt(speed.x() * speed.x() + speed.y() * speed.y() + speed.z() * speed.z()) / YLPI;
	m_qtnBall = QQuaternion::fromAxisAndAngle(delta, angle) * m_qtnBall;

	this->updateGL();
}



void BallancepathOpenglWidget::ResetGame()
{
	this->m_parent->setStatus(Ballance::GAMESTATUS_START);

	QVector3D delta;
	//调整看点
	m_mtx4Eye.setToIdentity();
	delta = QVector3D(0, -1, 0).normalized();
	for (int i = 0; i < 18; i++)
		m_mtx4Eye.translate(delta);
	m_mtx4Eye.rotate(45, 1, 0, 0);
	//调整地图旋转度
	m_qtnPath = QQuaternion::fromAxisAndAngle(QVector3D(0, 0, 0), 0);
	delta = QVector3D(1, 0, 0).normalized();
	m_qtnPath = QQuaternion::fromAxisAndAngle(delta, -90) * m_qtnPath;
	//调整球体旋转度使球表面显示合适的图案
	m_qtnBall = QQuaternion::fromAxisAndAngle(QVector3D(0, 0, 0), 0);
	delta = QVector3D(0, 0, 1).normalized();
	m_qtnBall = QQuaternion::fromAxisAndAngle(delta, -90) * m_qtnBall;
	//调整球体位置
	m_vct3Ball = QVector3D(0, 0, 1);

	m_pnlBall->setVelocity0(QVector3D(0, 0, 0));

	m_nTmrMoveEverything = 0;
	m_bPressBnW = false;
	m_bPressBnS = false;
	m_bPressBnA = false;
	m_bPressBnD = false;
}



void BallancepathOpenglWidget::CheckGameStatus(int s)
{
	switch (s)
	{
	case -1:
	{
		if (this->m_parent->getStatus() == Ballance::GAMESTATUS_START)
		{
			this->m_parent->setStatus(Ballance::GAMESTATUS_OVER);
			QMessageBox::StandardButton res;
			res = QMessageBox::information(this, "Ballance", "defeat", QMessageBox::Retry | QMessageBox::Cancel);
			if (res == QMessageBox::Retry)
			{
				this->ResetGame();
			}
			else if (res == QMessageBox::Cancel)
			{
				this->close();
			}
		}
		break;
	}
	case 0:
	{
		break;
	}
	case 1:
	{
		if (this->m_parent->getStatus() == Ballance::GAMESTATUS_START)
		{
			this->m_parent->setStatus(Ballance::GAMESTATUS_WIN);
			QMessageBox::StandardButton res;
			res = QMessageBox::information(this, "Ballance", "win", QMessageBox::Ok | QMessageBox::Retry);
			if (res == QMessageBox::Ok)
			{
				this->close();
			}
			else if (res == QMessageBox::Retry)
			{
				this->ResetGame();
			}
		}
		break;
	}
	}
}


























































