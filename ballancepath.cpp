
#include "ballancepath.h"



CBallancePath::CBallancePath()
{
	// m_vctThepath.push_back(Thepath(PATHTYPESTART | PATHDIRNULL, 0,   0, 0, 0, 0, 0,  &g_imgstart));
	// m_vctThepath.push_back(Thepath(PATHTYPEWOOD3 | PATHDIRN,    0,  30, 0, 0, 0, 0,  &g_imgwood3));
	// m_vctThepath.push_back(Thepath(PATHTYPEWOOD3 | PATHDIRW,    0,  30, 0, 0, 0, 0,  &g_imgwood3));
	// m_vctThepath.push_back(Thepath(PATHTYPEWOOD3 | PATHDIRS,    0,  60, 0, 0, 0, 0,  &g_imgwood3));
	// m_vctThepath.push_back(Thepath(PATHTYPEWOOD3 | PATHDIRE,    0,  60, 0, 0, 0, 0,  &g_imgwood3));
	// m_vctThepath.push_back(Thepath(PATHTYPEWOOD3 | PATHDIRN,    0,  30, 0, 0, 0, 0,  &g_imgwood3));
	// m_vctThepath.push_back(Thepath(PATHTYPESTOP  | PATHDIRNULL, 0,   0, 0, 0, 0, 0,   &g_imgstop));

//	Thepath p = Thepath{PATHTYPESTART | PATHDIRNULL,   0, 0, 0, 0, 0};

	m_vctThepath.push_back(Thepath{PATHTYPESTART | PATHDIRNULL,   0, 0, 0, 0, 0});
	m_vctThepath.push_back(Thepath{PATHTYPEWOOD3 |    PATHDIRN,  30, 0, 0, 0, 0});
	m_vctThepath.push_back(Thepath{PATHTYPEWOOD3 |    PATHDIRW,  30, 0, 0, 0, 0});
	m_vctThepath.push_back(Thepath{PATHTYPEWOOD3 |    PATHDIRS,  60, 0, 0, 0, 0});
	m_vctThepath.push_back(Thepath{PATHTYPEWOOD3 |    PATHDIRE,  60, 0, 0, 0, 0});
	m_vctThepath.push_back(Thepath{PATHTYPEWOOD3 |    PATHDIRN,  30, 0, 0, 0, 0});
	m_vctThepath.push_back(Thepath{PATHTYPESTOP  | PATHDIRNULL,   0, 0, 0, 0, 0});
}



CBallancePath::~CBallancePath()
{
	m_vctThepath.clear();
}



void CBallancePath::initdata()
{
}
