
#ifndef BALLANCE_H
#define BALLANCE_H

#include "ylqtwidgetheader.h"
#include "ballancepathopenglwidget.h"



namespace Ui {
class Ballance;
}

class Ballance : public QWidget
{
	Q_OBJECT

public:
	explicit Ballance(QWidget *parent = 0);
	~Ballance();

public slots:
	void on_bnNewgame();
	void on_bnCustom();
	void on_bnScore();
	void on_bnAbout();
	void on_bnQuit();
	void on_bnBack2Start();
	void on_bnLevels();

protected:
	void paintEvent(QPaintEvent *e);					//
	void keyPressEvent(QKeyEvent *event);				//处理键盘按下事件

	void mySetLayout();									//

private:
	Ui::Ballance *ui;

//public:
	int m_nWidth;
	int m_nHeight;

	QImage m_imgBg;

	QWidget *m_pwStart;
	QGridLayout *m_pgridStart;
	QPushButton *m_pbnNewgame;
	QPushButton *m_pbnCustom;
	QPushButton *m_pbnScore;
	QPushButton *m_pbnAbout;
	QPushButton *m_pbnQuit;

	QPushButton *m_pbnBack2Start;

	QWidget *m_pwLevel;
	QGridLayout *m_pgridLevel;
	QPushButton *m_pbnLevels;

	BallancepathOpenglWidget *m_pbglwGame;

	static enum enums
	{
		PAGE_START,

		PAGES 				 = 10,
		PAGE_LEVEL,
		PAGE_CUSTOM,
		PAGE_SCORE,
		PAGE_ABOUT,
		PAGES_END,

		GAMESTATUS 			 = 20,
		GAMESTATUS_START,
		GAMESTATUS_PAUSE,
		GAMESTATUS_WIN,
		GAMESTATUS_OVER,
		GAMESTATUS_END,
	} m_enums;
	int m_nCurrentStatus;

};

#endif // BALLANCE_H
