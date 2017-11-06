
#include "ballancepath.h"





CBallancePath::CBallancePath() :
	m_szBall(2, 2),
	m_szStart(5, 5),
	m_szStop(5, 5),
	m_szWood3(3, 1)
{
	qDebug() << "CBallancePath::CBallancePath";

	m_tre4Path = new YLTree4<PathUnit>(PathUnit{PATHTYPESTART | PATHDIRNULL,   0, 0, 0, 0, 0, &m_szStart});
	YLTree4<PathUnit>::NODE *root = m_tre4Path->getNodeRoot();

//	m_tre4Path->pushN(root, PathUnit{PATHTYPEWOOD3 |    PATHDIRN,  10, 0, 0, 0, 0, &m_szWood3})
//			->pushS(root, PathUnit{PATHTYPEWOOD3 |    PATHDIRS,  10, 0, 0, 0, 0, &m_szWood3})
//			->pushW(root, PathUnit{PATHTYPEWOOD3 |    PATHDIRW,  10, 0, 0, 0, 0, &m_szWood3})
//			->pushE(root, PathUnit{PATHTYPEWOOD3 |    PATHDIRE,  10, 0, 0, 0, 0, &m_szWood3});
//	YLTree4<PathUnit>::NODE *rootn = m_tre4Path->getNodeN(root);
//	YLTree4<PathUnit>::NODE *roots = m_tre4Path->getNodeS(root);
//	YLTree4<PathUnit>::NODE *rootw = m_tre4Path->getNodeW(root);
//	YLTree4<PathUnit>::NODE *roote = m_tre4Path->getNodeE(root);
//	m_tre4Path
////			->pushN(rootn, PathUnit{PATHTYPESTOP  | PATHDIRNULL,  5, 0, 0, 0, 0, &m_szStop});
//			->pushW(rootn, PathUnit{PATHTYPEWOOD3 |    PATHDIRW,  5, 0, 0, 0, 0, &m_szWood3})
//			->pushE(rootn, PathUnit{PATHTYPEWOOD3 |    PATHDIRE,  5, 0, 0, 0, 0, &m_szWood3});
//	m_tre4Path
////			->pushS(roots, PathUnit{PATHTYPESTOP  | PATHDIRNULL,  5, 0, 0, 0, 0, &m_szStop});
//			->pushW(roots, PathUnit{PATHTYPEWOOD3 |    PATHDIRW,  5, 0, 0, 0, 0, &m_szWood3})
//			->pushE(roots, PathUnit{PATHTYPEWOOD3 |    PATHDIRE,  5, 0, 0, 0, 0, &m_szWood3});
//	m_tre4Path
////			->pushW(rootw, PathUnit{PATHTYPESTOP  | PATHDIRNULL,  5, 0, 0, 0, 0, &m_szStop});
//			->pushN(rootw, PathUnit{PATHTYPEWOOD3 |    PATHDIRN,  5, 0, 0, 0, 0, &m_szWood3})
//			->pushS(rootw, PathUnit{PATHTYPEWOOD3 |    PATHDIRS,  5, 0, 0, 0, 0, &m_szWood3});
//	m_tre4Path
////			->pushE(roote, PathUnit{PATHTYPESTOP  | PATHDIRNULL,  5, 0, 0, 0, 0, &m_szStop});
//			->pushN(roote, PathUnit{PATHTYPEWOOD3 |    PATHDIRN,  5, 0, 0, 0, 0, &m_szWood3})
//			->pushS(roote, PathUnit{PATHTYPEWOOD3 |    PATHDIRS,  5, 0, 0, 0, 0, &m_szWood3});

	root = m_tre4Path->pushNl(root, PathUnit{PATHTYPEWOOD3 |    PATHDIRN,  10, 0, 0, 0, 0, &m_szWood3});
	root = m_tre4Path->pushWl(root, PathUnit{PATHTYPEWOOD3 |    PATHDIRW,  10, 0, 0, 0, 0, &m_szWood3});
	root = m_tre4Path->pushSl(root, PathUnit{PATHTYPEWOOD3 |    PATHDIRS,  20, 0, 0, 0, 0, &m_szWood3});
	root = m_tre4Path->pushEl(root, PathUnit{PATHTYPEWOOD3 |    PATHDIRE,  20, 0, 0, 0, 0, &m_szWood3});
	root = m_tre4Path->pushNl(root, PathUnit{PATHTYPEWOOD3 |    PATHDIRN,  10, 0, 0, 0, 0, &m_szWood3});
	root = m_tre4Path->pushNl(root, PathUnit{PATHTYPESTOP  | PATHDIRNULL,   0, 0, 0, 0, 0,  &m_szStop});

	this->InitData();

	qDebug() << "m_tre4Path";
	m_tre4Path->traversalPreorder([&](PathUnit &path, YLTree4<PathUnit>::NODE *n)
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
//	t->traversalPreorder([](int &x, YLTree4<int>::NODE *n)
//	{
//		qDebug() << x;
//		x = x + 2;
//	});
//	t->getDataRoot() = 111;
//	qDebug() << "先序遍历";
//	t->traversalPreorder([](int &x, YLTree4<int>::NODE *n)
//	{
//		qDebug() << x;
//	});
//	qDebug() << "中序遍历";
//	t->traversalInorder([](int &x, YLTree4<int>::NODE *n)
//	{
//		qDebug() << x;
//	});
//	qDebug() << "后序遍历";
//	t->traversalPostorder([](int &x, YLTree4<int>::NODE *n)
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

	m_tre4Path->clear();
	delete m_tre4Path;
}



void CBallancePath::InitData()
{
	qDebug() << "CBallancePath::initdata";

	m_tre4Path->traversalPreorder([&](PathUnit &initpathunit, YLTree4<PathUnit>::NODE *pnode)
	{
		PathUnit preinitpathunit = m_tre4Path->getNodeParent(pnode)->nodeData;
		switch (initpathunit.mode & PATHTYPE)
		{
		case PATHTYPESTART :
		{
			initpathunit.posx1 = -initpathunit.imagesize->width() / 2;
			initpathunit.posy1 = initpathunit.imagesize->height() / 2;
			initpathunit.posx2 = initpathunit.imagesize->width() / 2;
			initpathunit.posy2 = -initpathunit.imagesize->height() / 2;
			break;
		}
		case PATHTYPEWOOD3 :
		{
			int temptype = preinitpathunit.mode & PATHTYPE;
			int tempdir = preinitpathunit.mode & PATHDIR;
			switch (initpathunit.mode & PATHDIR)
			{
			case PATHDIRN :
			{
				if (temptype == PATHTYPESTART)
				{
					initpathunit.posx1 = -initpathunit.imagesize->width() / 2;
					initpathunit.posy1 = preinitpathunit.posy1 + initpathunit.imagesize->height() * initpathunit.length;
					initpathunit.posx2 = initpathunit.imagesize->width() / 2;
					initpathunit.posy2 = preinitpathunit.posy1;
				}
				else if (tempdir == PATHDIRN)
				{
				}
				else if (tempdir == PATHDIRS)
				{
				}
				else if (tempdir == PATHDIRW)
				{
					initpathunit.posx1 = preinitpathunit.posx1;
					initpathunit.posy1 = preinitpathunit.posy1 + initpathunit.imagesize->height() * initpathunit.length;
					initpathunit.posx2 = preinitpathunit.posx1 + initpathunit.imagesize->width();
					initpathunit.posy2 = preinitpathunit.posy1;
				}
				else if (tempdir == PATHDIRE)
				{
					initpathunit.posx1 = preinitpathunit.posx2 - initpathunit.imagesize->width();
					initpathunit.posy1 = preinitpathunit.posy1 + initpathunit.imagesize->height() * initpathunit.length;
					initpathunit.posx2 = preinitpathunit.posx2;
					initpathunit.posy2 = preinitpathunit.posy1;
				}
				break;
			}
			case PATHDIRS :
			{
				if (temptype == PATHTYPESTART)
				{
					initpathunit.posx1 = -initpathunit.imagesize->width() / 2;
					initpathunit.posy1 = preinitpathunit.posy2;
					initpathunit.posx2 = initpathunit.imagesize->width() / 2;
					initpathunit.posy2 = preinitpathunit.posy2 - initpathunit.imagesize->height() * initpathunit.length;
				}
				else if (tempdir == PATHDIRN)
				{
				}
				else if (tempdir == PATHDIRS)
				{
				}
				else if (tempdir == PATHDIRW)
				{
					initpathunit.posx1 = preinitpathunit.posx1;
					initpathunit.posy1 = preinitpathunit.posy2;
					initpathunit.posx2 = preinitpathunit.posx1 + initpathunit.imagesize->width();
					initpathunit.posy2 = preinitpathunit.posy2 - initpathunit.imagesize->height() * initpathunit.length;
				}
				else if (tempdir == PATHDIRE)
				{
					initpathunit.posx1 = preinitpathunit.posx2 - initpathunit.imagesize->width();
					initpathunit.posy1 = preinitpathunit.posy2;
					initpathunit.posx2 = preinitpathunit.posx2;
					initpathunit.posy2 = preinitpathunit.posy2 - initpathunit.imagesize->height() * initpathunit.length;
				}
				break;
			}
			case PATHDIRW :
			{
				if (temptype == PATHTYPESTART)
				{
					initpathunit.posx1 = preinitpathunit.posx1 - initpathunit.imagesize->height() * initpathunit.length;
					initpathunit.posy1 = initpathunit.imagesize->width() / 2;
					initpathunit.posx2 = preinitpathunit.posx1;
					initpathunit.posy2 = -initpathunit.imagesize->width() / 2;
				}
				else if (tempdir == PATHDIRN)
				{
					initpathunit.posx1 = preinitpathunit.posx1 - initpathunit.imagesize->height() * initpathunit.length;
					initpathunit.posy1 = preinitpathunit.posy1;
					initpathunit.posx2 = preinitpathunit.posx1;
					initpathunit.posy2 = preinitpathunit.posy1 - initpathunit.imagesize->width();
				}
				else if (tempdir == PATHDIRS)
				{
					initpathunit.posx1 = preinitpathunit.posx1 - initpathunit.imagesize->height() * initpathunit.length;
					initpathunit.posy1 = preinitpathunit.posy2 + initpathunit.imagesize->width();
					initpathunit.posx2 = preinitpathunit.posx1;
					initpathunit.posy2 = preinitpathunit.posy2;
				}
				else if (tempdir == PATHDIRW)
				{
				}
				else if (tempdir == PATHDIRE)
				{
				}
				break;
			}
			case PATHDIRE :
			{
				if (temptype == PATHTYPESTART)
				{
					initpathunit.posx1 = preinitpathunit.posx2;
					initpathunit.posy1 = initpathunit.imagesize->width() / 2;
					initpathunit.posx2 = preinitpathunit.posx2 + initpathunit.imagesize->height() * initpathunit.length;
					initpathunit.posy2 = -initpathunit.imagesize->width() / 2;
				}
				else if (tempdir == PATHDIRN)
				{
					initpathunit.posx1 = preinitpathunit.posx2;
					initpathunit.posy1 = preinitpathunit.posy1;
					initpathunit.posx2 = preinitpathunit.posx2 + initpathunit.imagesize->height() * initpathunit.length;
					initpathunit.posy2 = preinitpathunit.posy1 - initpathunit.imagesize->width();
				}
				else if (tempdir == PATHDIRS)
				{
					initpathunit.posx1 = preinitpathunit.posx2;
					initpathunit.posy1 = preinitpathunit.posy2 + initpathunit.imagesize->width();
					initpathunit.posx2 = preinitpathunit.posx2 + initpathunit.imagesize->height() * initpathunit.length;
					initpathunit.posy2 = preinitpathunit.posy2;
				}
				else if (tempdir == PATHDIRW)
				{
				}
				else if (tempdir == PATHDIRE)
				{
				}
				break;
			}
			}
			break;
		}
		case PATHTYPESTOP :
		{
			switch (preinitpathunit.mode & PATHDIR)
			{
			case PATHDIRN :
			{
				initpathunit.posx1 = preinitpathunit.posx1 - ((initpathunit.imagesize->width() - preinitpathunit.imagesize->width()) / 2);
				initpathunit.posy1 = preinitpathunit.posy1 + initpathunit.imagesize->height();
				break;
			}
			case PATHDIRS :
			{
				initpathunit.posx1 = preinitpathunit.posx1 - ((initpathunit.imagesize->width() - preinitpathunit.imagesize->width()) / 2);
				initpathunit.posy1 = preinitpathunit.posy2;
				break;
			}
			case PATHDIRW :
			{
				initpathunit.posx1 = preinitpathunit.posx1 - initpathunit.imagesize->width();
				initpathunit.posy1 = preinitpathunit.posy1 + ((initpathunit.imagesize->height() - preinitpathunit.imagesize->width()) / 2);
				break;
			}
			case PATHDIRE :
			{
				initpathunit.posx1 = preinitpathunit.posx2;
				initpathunit.posy1 = preinitpathunit.posy1 + ((initpathunit.imagesize->height() - preinitpathunit.imagesize->width()) / 2);
				break;
			}
			}
			initpathunit.posx2 = initpathunit.posx1 + initpathunit.imagesize->width();
			initpathunit.posy2 = initpathunit.posy1 - initpathunit.imagesize->height();
			break;
		}
		}
	});
}





int CBallancePath::check(const QVector3D &point, YLTree4<PathUnit>::NODE *punitnode)
{
//	qDebug() << "CBallancePath::check";


	PathUnit unit = punitnode->nodeData;
	if (point.x() < unit.posx1 || point.x() > unit.posx2 ||
			point.y() < unit.posy2 || point.y() > unit.posy1)
	{
		return -1;																//输
	}
	else if ((unit.mode & PATHTYPE) == PATHTYPESTOP &&
			 (point.x() > unit.posx1 + unit.imagesize->width() / 3 &&
			  point.x() < unit.posx2 + unit.imagesize->width() / 3 * 2 &&
			  point.y() > unit.posy2 + unit.imagesize->height() / 3 &&
			  point.y() < unit.posy1 + unit.imagesize->height() / 3 * 2))
	{
		return 1;																//赢
	}
	return 0;																	//游戏继续
}




























