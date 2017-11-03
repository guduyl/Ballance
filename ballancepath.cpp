
#include "ballancepath.h"



CBallancePath::CBallancePath() :
	m_szBall(2, 2),
	m_szStart(4, 4),
	m_szStop(4, 4),
	m_szWood3(3, 1),
	m_szCross(3, 3)
{
	qDebug() << "CBallancePath::CBallancePath";

	m_vctThepath.push_back(Thepath{PATHTYPESTART | PATHDIRNULL,   0, 0, 0, 0, 0, &m_szStart});
	m_vctThepath.push_back(Thepath{PATHTYPEWOOD3 |    PATHDIRN,  10, 0, 0, 0, 0, &m_szWood3});
	m_vctThepath.push_back(Thepath{PATHTYPEWOOD3 |    PATHDIRW,  10, 0, 0, 0, 0, &m_szWood3});
	m_vctThepath.push_back(Thepath{PATHTYPEWOOD3 |    PATHDIRS,  20, 0, 0, 0, 0, &m_szWood3});
	m_vctThepath.push_back(Thepath{PATHTYPEWOOD3 |    PATHDIRE,  20, 0, 0, 0, 0, &m_szWood3});
	m_vctThepath.push_back(Thepath{PATHTYPEWOOD3 |    PATHDIRN,  10, 0, 0, 0, 0, &m_szWood3});
	m_vctThepath.push_back(Thepath{PATHTYPESTOP  | PATHDIRNULL,   0, 0, 0, 0, 0,  &m_szStop});

	this->initdata();

//	qDebug() << "m_vctThepath";
//	foreach(Thepath p, m_vctThepath)
//		qDebug() << p;

	m_tre4Thepath = new YLTree4<Thepath>(Thepath{PATHTYPESTART | PATHDIRNULL,   0, 0, 0, 0, 0, &m_szStart});
	YLTree4<Thepath>::NODE *p = m_tre4Thepath->getNodeRoot();
	p = m_tre4Thepath->pushNl(p, Thepath{PATHTYPEWOOD3 |    PATHDIRN,  10, 0, 0, 0, 0, &m_szWood3});
	p = m_tre4Thepath->pushWl(p, Thepath{PATHTYPEWOOD3 |    PATHDIRW,  10, 0, 0, 0, 0, &m_szWood3});
	p = m_tre4Thepath->pushSl(p, Thepath{PATHTYPEWOOD3 |    PATHDIRS,  20, 0, 0, 0, 0, &m_szWood3});
	p = m_tre4Thepath->pushEl(p, Thepath{PATHTYPEWOOD3 |    PATHDIRE,  20, 0, 0, 0, 0, &m_szWood3});
	p = m_tre4Thepath->pushNl(p, Thepath{PATHTYPEWOOD3 |    PATHDIRN,  10, 0, 0, 0, 0, &m_szWood3});
	p = m_tre4Thepath->pushNl(p, Thepath{PATHTYPESTOP  | PATHDIRNULL,   0, 0, 0, 0, 0,  &m_szStop});

	qDebug() << "m_tre4Thepath&";
	int i = 0;
	m_tre4Thepath->traversalPreorder([&](Thepath &path, YLTree4<Thepath>::NODE *n)
	{
		qDebug() << ++i << path;
	});

	qDebug() << "m_tre4Thepath";
	m_tre4Thepath->traversalPreorder([&](Thepath &path, YLTree4<Thepath>::NODE *n)
	{
		qDebug() << path;
	});

//	YLTree4<int> *t = new YLTree4<int>(0);
//	qDebug() << t->getSize();
//	qDebug() << t->getDepth();
//	YLTree4<int>::NODE *n = t->getNodeRoot();
//	t->pushN(n, 1)->pushS(n, 2)->pushW(n, 3)->pushE(n, 4);
//	n = t->getNodeN(t->getNodeRoot());
//	t->pushN(n, 11)->pushS(n, 12);
//	n = t->getNodeS(t->getNodeRoot());
//	t->pushW(n, 23)->pushE(n, 24);
//	n = t->getNodeW(t->getNodeRoot());
//	t->pushN(n, 31)->pushW(n, 33);
//	n = t->getNodeE(t->getNodeRoot());
//	t->pushS(n, 42)->pushE(n, 44);
//	qDebug() << "先序遍历";
//	t->traversalPreorder([](int &x)
//	{
//		qDebug() << x;
//		x = x + 2;
//	});
//	t->getDataRoot() = 111;
//	qDebug() << "先序遍历";
//	t->traversalPreorder([](int &x)
//	{
//		qDebug() << x;
//	});
//	qDebug() << "中序遍历";
//	t->traversalInorder([](int &x)
//	{
//		qDebug() << x;
//	});
//	qDebug() << "后序遍历";
//	t->traversalPostorder([](int &x)
//	{
//		qDebug() << x;
//	});
//	qDebug() << t->getSize();
//	qDebug() << t->getDepth();
//	t->clear();
}



CBallancePath::~CBallancePath()
{
	qDebug() << "CBallancePath::~CBallancePath";

	m_vctThepath.clear();
	m_tre4Thepath->clear();
	delete m_tre4Thepath;
}



void CBallancePath::initdata()
{
	qDebug() << "CBallancePath::initdata";

//	m_tre4Thepath->traversalPreorder([&](Thepath &initdatapathunit, YLTree4<Thepath>::NODE *pinitdatanode)
//	{
//		Thepath preinitdatapathunit = m_tre4Thepath->getNodeParent(pinitdatanode)->nodeData;
//		this->zzz(initdatapathunit, preinitdatapathunit);
//	});

//	m_tre4Thepath->traversalPreorder([](Thepath &initdatapathunit, YLTree4<Thepath>::NODE *pinitdatanode)
//	{
//		Thepath preinitdatapathunit = m_tre4Thepath->getNodeParent(pinitdatanode)->nodeData;
//		this->zzz(initdatapathunit, preinitdatapathunit);
//	});
}

void CBallancePath::xxx(Thepath &initdatapathunit, YLTree4<Thepath>::NODE *pinitdatanode)
{
	Thepath preinitdatapathunit = m_tre4Thepath->getNodeParent(pinitdatanode)->nodeData;
	this->zzz(initdatapathunit, preinitdatapathunit);
}

void CBallancePath::zzz(Thepath &initdatapathunit, Thepath &preinitdatapathunit)
{
	switch (initdatapathunit.mode & PATHTYPE)
	{
	case PATHTYPESTART :
	{
		initdatapathunit.posx1 = -initdatapathunit.imagesize->width() / 2;
		initdatapathunit.posy1 = -initdatapathunit.imagesize->height() / 2;
		initdatapathunit.posx2 = initdatapathunit.imagesize->width() / 2;
		initdatapathunit.posy2 = initdatapathunit.imagesize->height() / 2;
		break;
	}
	case PATHTYPEWOOD3 :
	{
		int temptype = preinitdatapathunit.mode & PATHTYPE;
		int tempdir = preinitdatapathunit.mode & PATHDIR;
		switch (initdatapathunit.mode & PATHDIR)
		{
		case PATHDIRN :
		{
			if (temptype == PATHTYPESTART)
			{
				initdatapathunit.posx1 = -m_szCross.width() / 2;
				initdatapathunit.posy1 = preinitdatapathunit.posy1 + preinitdatapathunit.imagesize->height();
			}
			else if (tempdir == PATHDIRW)
			{
				initdatapathunit.posx1 = preinitdatapathunit.posx1 + preinitdatapathunit.imagesize->height() * preinitdatapathunit.length;
				initdatapathunit.posy1 = preinitdatapathunit.posy1 + m_szCross.height();
			}
			else if (tempdir == PATHDIRE)
			{
				initdatapathunit.posx1 = preinitdatapathunit.posx1 - m_szCross.width();
				initdatapathunit.posy1 = preinitdatapathunit.posy1 + m_szCross.height();
			}
			initdatapathunit.posx2 = initdatapathunit.posx1 + initdatapathunit.imagesize->width();
			initdatapathunit.posy2 = initdatapathunit.posy1 + initdatapathunit.imagesize->height() * initdatapathunit.length;
			break;
		}
		case PATHDIRS :
		{
			initdatapathunit.posy1 = preinitdatapathunit.posy1 - initdatapathunit.imagesize->height() * initdatapathunit.length;
			initdatapathunit.posy2 = preinitdatapathunit.posy1;
			if (temptype == PATHTYPESTART)
			{
				initdatapathunit.posx1 = -m_szCross.width() / 2;
			}
			else if (tempdir == PATHDIRW)
			{
				initdatapathunit.posx1 = preinitdatapathunit.posx1 + preinitdatapathunit.imagesize->height() * preinitdatapathunit.length;
			}
			else if (tempdir == PATHDIRE)
			{
				initdatapathunit.posx1 = preinitdatapathunit.posx1 - m_szCross.width();
			}
			initdatapathunit.posx2 = initdatapathunit.posx1 + initdatapathunit.imagesize->width();
			break;
		}
		case PATHDIRW :
		{
			if (temptype == PATHTYPESTART)
			{
				initdatapathunit.posx1 = preinitdatapathunit.posx1 + preinitdatapathunit.imagesize->width();
				initdatapathunit.posy1 = -m_szCross.height() / 2;
			}
			else if (tempdir == PATHDIRN)
			{
				initdatapathunit.posx1 = preinitdatapathunit.posx1 + m_szCross.width();
				initdatapathunit.posy1 = preinitdatapathunit.posy1 + preinitdatapathunit.imagesize->height() * preinitdatapathunit.length;
			}
			else if (tempdir == PATHDIRS)
			{
				initdatapathunit.posx1 = preinitdatapathunit.posx1 + m_szCross.width();
				initdatapathunit.posy1 = preinitdatapathunit.posy1 - m_szCross.height();
			}
			initdatapathunit.posx2 = initdatapathunit.posx1 + initdatapathunit.imagesize->height() * initdatapathunit.length;
			initdatapathunit.posy2 = initdatapathunit.posy1 + initdatapathunit.imagesize->width();
			break;
		}
		case PATHDIRE :
		{
			initdatapathunit.posx1 = preinitdatapathunit.posx1 - initdatapathunit.imagesize->height() * initdatapathunit.length;
			initdatapathunit.posx2 = preinitdatapathunit.posx1;
			if (temptype == PATHTYPESTART)
			{
				initdatapathunit.posy1 = -m_szCross.height() / 2;
			}
			else if (tempdir == PATHDIRN)
			{
				initdatapathunit.posy1 = preinitdatapathunit.posy1 + preinitdatapathunit.imagesize->height() * preinitdatapathunit.length;
			}
			else if (tempdir == PATHDIRS)
			{
				initdatapathunit.posy1 = preinitdatapathunit.posy1 - m_szCross.height();
			}
			initdatapathunit.posy2 = initdatapathunit.posy1 + initdatapathunit.imagesize->width();
			break;
		}
		}
		break;
	}
	case PATHTYPESTOP :
	{
		switch (preinitdatapathunit.mode & PATHDIR)
		{
		case PATHDIRS :
		{
			initdatapathunit.posx1 = preinitdatapathunit.posx1 - ((initdatapathunit.imagesize->width() - m_szCross.width()) / 2);
			initdatapathunit.posy1 = preinitdatapathunit.posy1 - initdatapathunit.imagesize->height();
			break;
		}
		case PATHDIRN :
		{
			initdatapathunit.posx1 = preinitdatapathunit.posx1 - ((initdatapathunit.imagesize->width() - m_szCross.width()) / 2);
			initdatapathunit.posy1 = preinitdatapathunit.posy1 + preinitdatapathunit.imagesize->height() * preinitdatapathunit.length;
			break;
		}
		case PATHDIRE :
		{
			initdatapathunit.posx1 = preinitdatapathunit.posx1 - initdatapathunit.imagesize->width();
			initdatapathunit.posy1 = preinitdatapathunit.posy1 - ((initdatapathunit.imagesize->height() - m_szCross.height()) / 2);
			break;
		}
		case PATHDIRW :
		{
			initdatapathunit.posx1 = preinitdatapathunit.posx1 + preinitdatapathunit.imagesize->height() * preinitdatapathunit.length;
			initdatapathunit.posy1 = preinitdatapathunit.posy1 - ((initdatapathunit.imagesize->height() - m_szCross.height()) / 2);
			break;
		}
		}
		initdatapathunit.posx2 = initdatapathunit.posx1 + initdatapathunit.imagesize->width();
		initdatapathunit.posy2 = initdatapathunit.posy1 + initdatapathunit.imagesize->height();
		break;
	}
	}
}
























