
#ifndef BALLANCEPATHOPENGLWIDGET_H
#define BALLANCEPATHOPENGLWIDGET_H

#include "ylqtwidgetheader.h"

class Ballance;
class CBallancePath;



class BallancepathOpenglWidget : public QGLWidget
{
public:
	BallancepathOpenglWidget(QWidget *parent = 0);
	~BallancepathOpenglWidget();

protected:
	//对3个opengl纯虚函数的重定义
	void initializeGL();
	void paintGL();
	void resizeGL(int w, int h);

	virtual void timerEvent(QTimerEvent *event);
	bool event(QEvent *event);
	void keyPressEvent(QKeyEvent *event);										//处理键盘按下事件
	void keyReleaseEvent(QKeyEvent *event);										//处理键盘释放事件

	bool IsAutoRepeatKeyEvent(QKeyEvent *event);								//这些按键是否是自动重按的按键
	void LoadTexture();
	void PaintCoordinate();
	void PaintPath();
	void PaintBall();
	void MoveEverything();

private:
	Ballance *m_parent;
	CBallancePath *m_ThePath;

	GLuint *m_punTexture;														//贴图
	QMatrix4x4 m_mtx4Eye;														//矩阵保存看点属性
	QQuaternion m_qtnPath;														//四元数保存地图旋转度属性
	QVector3D m_vct4Ball;														//坐标值保存球体坐标属性
	QQuaternion m_qtnBall;														//四元数保存球体旋转度属性
	float m_fBallSpeed;															//球体运动速度

	int m_nTmrMoveEverything;
	bool m_bPressBnW;
	bool m_bPressBnS;
	bool m_bPressBnA;
	bool m_bPressBnD;

};

#endif // BALLANCEPATHOPENGLWIDGET_H
