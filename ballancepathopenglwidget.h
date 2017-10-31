
#ifndef BALLANCEPATHOPENGLWIDGET_H
#define BALLANCEPATHOPENGLWIDGET_H

#include "ylqtwidgetheader.h"

class Ballance;



class BallancepathOpenglWidget : public QGLWidget
{
public:
	BallancepathOpenglWidget(QWidget *parent = 0);
	~BallancepathOpenglWidget();

public slots:

protected:
	//对3个opengl纯虚函数的重定义
	void initializeGL();
	void paintGL();
	void resizeGL(int w, int h);

	bool event(QEvent *event);
	void keyPressEvent(QKeyEvent *event);				//处理键盘按下事件
//	void keyReleaseEvent(QKeyEvent *event);				//处理键盘释放事件

	void LoadTexture();

private:
	Ballance *m_parent;

	GLuint *m_punTexture;

	QQuaternion m_qtnBallRotation;						//四元数保存旋转属性
	float m_fBallSpeed;

};

#endif // BALLANCEPATHOPENGLWIDGET_H
