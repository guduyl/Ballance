
#include "ballance.h"





Ballance::Ballance(QWidget *parent) :
	QWidget(parent),
	m_nWidth(800),
	m_nHeight(600),

	m_pwStart(new QWidget(this)),
	m_pgridStart(new QGridLayout),
	m_pbnNewgame(new QPushButton("新  游  戏", this)),
	m_pbnCustom(new QPushButton("自  定  义", this)),
	m_pbnScore(new QPushButton("计  分  板", this)),
	m_pbnAbout(new QPushButton("关  于", this)),
	m_pbnQuit(new QPushButton("退  出", this)),

	m_pbnBack2Start(new QPushButton("返  回", this)),

	m_pwLevel(new QWidget(this)),
	m_pgridLevel(new QGridLayout),
	m_pbnLevels(NULL),

	m_pbglwGame(NULL),

	m_nCurrentStatus(Ballance::PAGE_START)
{
	qDebug() << "Ballance::Ballance";

	this->mySetLayout();
}



Ballance::~Ballance()
{
	qDebug() << "Ballance::~Ballance";

	delete m_pbnNewgame;
	delete m_pbnCustom;
	delete m_pbnScore;
	delete m_pbnAbout;
	delete m_pbnQuit;
	delete m_pgridStart;
	delete m_pwStart;

	delete m_pbnBack2Start;

	delete[] m_pbnLevels;
	delete m_pgridLevel;
	delete m_pwLevel;
}





void Ballance::mySetLayout()
{
	qDebug() << "Ballance::mySetLayout";

	//Main
	this->resize(m_nWidth, m_nHeight);
	this->setFixedSize(m_nWidth, m_nHeight);
	QDesktopWidget *desktop = QApplication::desktop();
//	this->move((desktop->width() - m_nWidth) / 2 + 700, (desktop->height() - m_nHeight - 100) / 2);
//	this->move((desktop->width() - m_nWidth) / 2 + 500, (desktop->height() - m_nHeight - 100) / 2);
	this->move((desktop->width() - m_nWidth) / 2, (desktop->height() - m_nHeight - 100) / 2);
	this->setWindowIcon(QIcon(":/icon/earth1.ico"));

	this->showFullScreen();
	m_nWidth = this->width();
	m_nHeight = this->height();

	m_imgBg.load(":/bgimg/earth.jpg");

	//StartPage
	m_pwStart->setFixedSize(m_nWidth, m_nHeight);
	m_pgridStart->setColumnStretch(0, 3);
	m_pgridStart->setColumnStretch(1, 2);
	m_pgridStart->setColumnStretch(2, 3);
	m_pgridStart->setRowStretch(0, 1);
	m_pbnNewgame->setMinimumHeight(50);
	this->connect(m_pbnNewgame, SIGNAL(clicked()), this, SLOT(on_bnNewgame()));
	m_pgridStart->setRowStretch(1, 1);
	m_pgridStart->addWidget(m_pbnNewgame, 1, 1, 1, 1);
	m_pbnCustom->setMinimumHeight(50);
	this->connect(m_pbnCustom, SIGNAL(clicked()), this, SLOT(on_bnCustom()));
	m_pgridStart->setRowStretch(2, 1);
	m_pgridStart->addWidget(m_pbnCustom, 2, 1, 1, 1);
	m_pbnScore->setMinimumHeight(50);
	this->connect(m_pbnScore, SIGNAL(clicked()), this, SLOT(on_bnScore()));
	m_pgridStart->setRowStretch(3, 1);
	m_pgridStart->addWidget(m_pbnScore, 3, 1, 1, 1);
	m_pbnAbout->setMinimumHeight(50);
	this->connect(m_pbnAbout, SIGNAL(clicked()), this, SLOT(on_bnAbout()));
	m_pgridStart->setRowStretch(4, 1);
	m_pgridStart->addWidget(m_pbnAbout, 4, 1, 1, 1);
	m_pbnQuit->setMinimumHeight(50);
	this->connect(m_pbnQuit, SIGNAL(clicked()), this, SLOT(on_bnQuit()));
	m_pgridStart->setRowStretch(5, 1);
	m_pgridStart->addWidget(m_pbnQuit, 5, 1, 1, 1);
	m_pgridStart->setRowStretch(6, 1);
	m_pwStart->setLayout(m_pgridStart);
	m_pwStart->hide();

	//the button Back2Start
	m_pbnBack2Start->setMinimumHeight(50);
	this->connect(m_pbnBack2Start, SIGNAL(clicked()), this, SLOT(on_bnShowStartPage()));

	//LevelPage
	m_pwLevel->setFixedSize(m_nWidth, m_nHeight);
	m_pgridLevel->setColumnStretch(0, 3);
	m_pgridLevel->setColumnStretch(1, 2);
	m_pgridLevel->setColumnStretch(2, 3);
	int levelsamount = 10;
	m_pbnLevels = new QPushButton[levelsamount];
	int i = 0;
	m_pgridLevel->setRowStretch(i, 1);
	for (; i < levelsamount; ++i)
	{
		m_pbnLevels[i].setText("第 " + QString::number(i + 1) + " 关");
		m_pbnLevels[i].setMinimumHeight(50);
		this->connect(m_pbnLevels + i, SIGNAL(clicked()), this, SLOT(on_bnLevels()));
		m_pgridLevel->setRowStretch(i + 1, 1);
		m_pgridLevel->addWidget(m_pbnLevels + i, i + 1, 1, 1, 1);
	}
	++i;
	m_pgridLevel->addWidget(m_pbnBack2Start, i, 1, 1, 1);
	m_pgridLevel->setRowStretch(i, 1);
	++i;
	m_pgridLevel->setRowStretch(i, 1);
	m_pwLevel->setLayout(m_pgridLevel);
	m_pwLevel->hide();

	//BallancepathOpenglWidget
	if (m_pbglwGame != NULL)
	{
		m_pbglwGame->move(0, 0);
		m_pbglwGame->setFixedSize(m_nWidth, m_nHeight);
		m_pbglwGame->hide();
	}

//	this->on_bnShowStartPage();
//	this->on_bnNewgame();
//	this->on_bnCustom();
//	this->on_bnScore();
//	this->on_bnAbout();
	this->on_bnLevels();
}



int Ballance::getStatus() const
{
	return this->m_nCurrentStatus;
}

bool Ballance::setStatus(int status)
{
	if (status > GAMESTATUS && status < GAMESTATUS_END)
	{
		this->m_nCurrentStatus = status;
		return true;
	}
	return false;
}





void Ballance::paintEvent(QPaintEvent *e)
{
//	qDebug() << "Ballance::paintEvent";

	Q_UNUSED(e);
	QPainter p(this);
	p.drawImage(QRect(0, 0, m_nWidth, m_nHeight), m_imgBg);
}



void Ballance::keyPressEvent(QKeyEvent *event)
{
//	qDebug() << "Ballance::keyPressEvent";

	switch (event->key())
	{
	case Qt::Key_F11:						//F11为全屏和普通屏的切换键
	{
//		qDebug() << "Ballance::keyPressEvent" << "Key_F11";
		if (this->isFullScreen())
		{
			this->showNormal();
		}
		else
		{
			this->showFullScreen();
		}
		m_nWidth = this->width();
		m_nHeight = this->height();
		switch (m_nCurrentStatus)
		{
		case Ballance::PAGE_START:
		{
			m_pwStart->setFixedSize(m_nWidth, m_nHeight);
			break;
		}
		case Ballance::PAGE_LEVEL:
		{
			m_pwLevel->setFixedSize(m_nWidth, m_nHeight);
			break;
		}
		case Ballance::PAGE_CUSTOM:
		{
			break;
		}
		case Ballance::PAGE_SCORE:
		{
			break;
		}
		case Ballance::PAGE_ABOUT:
		{
			break;
		}
		default:
		{
			m_pbglwGame->setFixedSize(m_nWidth, m_nHeight);
			break;
		}
		}
		break;
	}
	case Qt::Key_Up:
	{
//		qDebug() << "Ballance::keyPressEvent" << "Key_Up";
		break;
	}
	case Qt::Key_Down:
	{
//		qDebug() << "Ballance::keyPressEvent" << "Key_Down";
		break;
	}
	case Qt::Key_Left:
	{
//		qDebug() << "Ballance::keyPressEvent" << "Key_Left";
		break;
	}
	case Qt::Key_Right:
	{
//		qDebug() << "Ballance::keyPressEvent" << "Key_Right";
		break;
	}
	case Qt::Key_Escape:					//ESC为退出键
	{
//		qDebug() << "Ballance::keyPressEvent" << "Key_Escape";
		if (m_nCurrentStatus == Ballance::PAGE_START)
		{
//			this->on_bnQuit();
		}
		else if (m_nCurrentStatus > Ballance::PAGES && m_nCurrentStatus < Ballance::PAGES_END)
		{
			this->on_bnShowStartPage();
		}
		else if (m_nCurrentStatus > Ballance::GAMESTATUS && m_nCurrentStatus < Ballance::GAMESTATUS_END)
		{
			m_pbglwGame->hide();
			delete m_pbglwGame;
			m_pbglwGame = NULL;
			this->on_bnNewgame();
		}
		break;
	}
	default: break;
	}
}





void Ballance::on_bnNewgame()
{
	qDebug() << "Ballance::on_bnNewgame";

	m_nCurrentStatus = Ballance::PAGE_LEVEL;
	m_pwStart->hide();
	m_pwLevel->move(0, 0);
	m_pwLevel->setFixedSize(m_nWidth, m_nHeight);
	m_pwLevel->show();
	m_pwLevel->setFocus();
}



void Ballance::on_bnCustom()
{
	qDebug() << "Ballance::on_bnCustom";

//	m_nCurrentStatus = Ballance::PAGE_CUSTOM;
}



void Ballance::on_bnScore()
{
	qDebug() << "Ballance::on_bnScore";

//	m_nCurrentStatus = Ballance::PAGE_SCORE;
}



void Ballance::on_bnAbout()
{
	qDebug() << "Ballance::on_bnAbout";

//	m_nCurrentStatus = Ballance::PAGE_ABOUT;
}



void Ballance::on_bnQuit()
{
	qDebug() << "Ballance::on_bnQuit";

	this->close();
}



void Ballance::on_bnShowStartPage()
{
	qDebug() << "Ballance::on_bnShowStartPage";

	m_nCurrentStatus = Ballance::PAGE_START;
	m_pwLevel->hide();
	m_pwStart->move(0, 0);
	m_pwStart->setFixedSize(m_nWidth, m_nHeight);
	m_pwStart->show();
	m_pwStart->setFocus();
}



void Ballance::on_bnLevels()
{
	qDebug() << "Ballance::on_bnLevels";

	m_nCurrentStatus = Ballance::GAMESTATUS_START;
	m_pwLevel->hide();
	m_pbglwGame = new BallancepathOpenglWidget(this);
	m_pbglwGame->setAttribute(Qt::WA_DeleteOnClose);							//设置窗口关闭时自动删除
	this->connect(m_pbglwGame, SIGNAL(destroyed()), this, SLOT(on_bnNewgame()));
	m_pbglwGame->move(0, 0);
	m_pbglwGame->setFixedSize(m_nWidth, m_nHeight);
	m_pbglwGame->show();
	m_pbglwGame->setFocus();
}



























