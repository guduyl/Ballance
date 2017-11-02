
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

//	qDebug() << m_vctThepath[0];
//	std::ostream os;
//	os << m_tre4Thepath;
//	qDebug() << os;
}



CBallancePath::~CBallancePath()
{
	qDebug() << "CBallancePath::~CBallancePath";

	m_vctThepath.clear();
	m_tre4Thepath.clear();
}



void CBallancePath::initdata()
{
	qDebug() << "CBallancePath::initdata";

	for (int i = 0; ; i++)
	{
		switch (m_vctThepath[i].mode & PATHTYPE)
		{
		case PATHTYPESTART :
		{
			m_vctThepath[i].posx1 = -m_vctThepath[i].imagesize->width() / 2;
			m_vctThepath[i].posy1 = -m_vctThepath[i].imagesize->height() / 2;
			m_vctThepath[i].posx2 = m_vctThepath[i].imagesize->width() / 2;
			m_vctThepath[i].posy2 = m_vctThepath[i].imagesize->height() / 2;
			break;
		}
		case PATHTYPEWOOD3 :
		{
			int temptype = m_vctThepath[i - 1].mode & PATHTYPE;
			int tempdir = m_vctThepath[i - 1].mode & PATHDIR;
			switch (m_vctThepath[i].mode & PATHDIR)
			{
			case PATHDIRN :
			{
				if (temptype == PATHTYPESTART)
				{
					m_vctThepath[i].posx1 = -m_szCross.width() / 2;
					m_vctThepath[i].posy1 = m_vctThepath[i - 1].posy1 + m_vctThepath[i - 1].imagesize->height();
				}
				else if (tempdir == PATHDIRW)
				{
					m_vctThepath[i].posx1 = m_vctThepath[i - 1].posx1 + m_vctThepath[i - 1].imagesize->height() * m_vctThepath[i - 1].length;
					m_vctThepath[i].posy1 = m_vctThepath[i - 1].posy1 + m_szCross.height();
				}
				else if (tempdir == PATHDIRE)
				{
					m_vctThepath[i].posx1 = m_vctThepath[i - 1].posx1 - m_szCross.width();
					m_vctThepath[i].posy1 = m_vctThepath[i - 1].posy1 + m_szCross.height();
				}
				m_vctThepath[i].posx2 = m_vctThepath[i].posx1 + m_vctThepath[i].imagesize->width();
				m_vctThepath[i].posy2 = m_vctThepath[i].posy1 + m_vctThepath[i].imagesize->height() * m_vctThepath[i].length;
				break;
			}
			case PATHDIRS :
			{
				m_vctThepath[i].posy1 = m_vctThepath[i - 1].posy1 - m_vctThepath[i].imagesize->height() * m_vctThepath[i].length;
				m_vctThepath[i].posy2 = m_vctThepath[i - 1].posy1;
				if (temptype == PATHTYPESTART)
				{
					m_vctThepath[i].posx1 = -m_szCross.width() / 2;
				}
				else if (tempdir == PATHDIRW)
				{
					m_vctThepath[i].posx1 = m_vctThepath[i - 1].posx1 + m_vctThepath[i - 1].imagesize->height() * m_vctThepath[i - 1].length;
				}
				else if (tempdir == PATHDIRE)
				{
					m_vctThepath[i].posx1 = m_vctThepath[i - 1].posx1 - m_szCross.width();
				}
				m_vctThepath[i].posx2 = m_vctThepath[i].posx1 + m_vctThepath[i].imagesize->width();
				break;
			}
			case PATHDIRW :
			{
				if (temptype == PATHTYPESTART)
				{
					m_vctThepath[i].posx1 = m_vctThepath[i - 1].posx1 + m_vctThepath[i - 1].imagesize->width();
					m_vctThepath[i].posy1 = -m_szCross.height() / 2;
				}
				else if (tempdir == PATHDIRN)
				{
					m_vctThepath[i].posx1 = m_vctThepath[i - 1].posx1 + m_szCross.width();
					m_vctThepath[i].posy1 = m_vctThepath[i - 1].posy1 + m_vctThepath[i - 1].imagesize->height() * m_vctThepath[i - 1].length;
				}
				else if (tempdir == PATHDIRS)
				{
					m_vctThepath[i].posx1 = m_vctThepath[i - 1].posx1 + m_szCross.width();
					m_vctThepath[i].posy1 = m_vctThepath[i - 1].posy1 - m_szCross.height();
				}
				m_vctThepath[i].posx2 = m_vctThepath[i].posx1 + m_vctThepath[i].imagesize->height() * m_vctThepath[i].length;
				m_vctThepath[i].posy2 = m_vctThepath[i].posy1 + m_vctThepath[i].imagesize->width();
				break;
			}
			case PATHDIRE :
			{
				m_vctThepath[i].posx1 = m_vctThepath[i - 1].posx1 - m_vctThepath[i].imagesize->height() * m_vctThepath[i].length;
				m_vctThepath[i].posx2 = m_vctThepath[i - 1].posx1;
				if (temptype == PATHTYPESTART)
				{
					m_vctThepath[i].posy1 = -m_szCross.height() / 2;
				}
				else if (tempdir == PATHDIRN)
				{
					m_vctThepath[i].posy1 = m_vctThepath[i - 1].posy1 + m_vctThepath[i - 1].imagesize->height() * m_vctThepath[i - 1].length;
				}
				else if (tempdir == PATHDIRS)
				{
					m_vctThepath[i].posy1 = m_vctThepath[i - 1].posy1 - m_szCross.height();
				}
				m_vctThepath[i].posy2 = m_vctThepath[i].posy1 + m_vctThepath[i].imagesize->width();
				break;
			}
			}
			break;
		}
		case PATHTYPESTOP :
		{
			switch (m_vctThepath[i - 1].mode & PATHDIR)
			{
			case PATHDIRS :
			{
				m_vctThepath[i].posx1 = m_vctThepath[i - 1].posx1 - ((m_vctThepath[i].imagesize->width() - m_szCross.width()) / 2);
				m_vctThepath[i].posy1 = m_vctThepath[i - 1].posy1 - m_vctThepath[i].imagesize->height();
				break;
			}
			case PATHDIRN :
			{
				m_vctThepath[i].posx1 = m_vctThepath[i - 1].posx1 - ((m_vctThepath[i].imagesize->width() - m_szCross.width()) / 2);
				m_vctThepath[i].posy1 = m_vctThepath[i - 1].posy1 + m_vctThepath[i - 1].imagesize->height() * m_vctThepath[i - 1].length;
				break;
			}
			case PATHDIRE :
			{
				m_vctThepath[i].posx1 = m_vctThepath[i - 1].posx1 - m_vctThepath[i].imagesize->width();
				m_vctThepath[i].posy1 = m_vctThepath[i - 1].posy1 - ((m_vctThepath[i].imagesize->height() - m_szCross.height()) / 2);
				break;
			}
			case PATHDIRW :
			{
				m_vctThepath[i].posx1 = m_vctThepath[i - 1].posx1 + m_vctThepath[i - 1].imagesize->height() * m_vctThepath[i - 1].length;
				m_vctThepath[i].posy1 = m_vctThepath[i - 1].posy1 - ((m_vctThepath[i].imagesize->height() - m_szCross.height()) / 2);
				break;
			}
			}
			m_vctThepath[i].posx2 = m_vctThepath[i].posx1 + m_vctThepath[i].imagesize->width();
			m_vctThepath[i].posy2 = m_vctThepath[i].posy1 + m_vctThepath[i].imagesize->height();
			break;
		}
		}
		if (m_vctThepath[i].mode == PATHTYPESTOP)
			break;
	}
}
