
#ifndef BALLANCEPATH_H
#define BALLANCEPATH_H

#include "ylqtwidgetheader.h"
#include "yltree4.h"



#define PATHDIR 			0x0f
#define PATHDIRNULL			0x00
#define PATHDIRN 			0x01
#define PATHDIRS 			0x02
#define PATHDIRW 			0x04
#define PATHDIRE 			0x08
#define PATHTYPE 			0xf0
#define PATHTYPESTART 		0x10
#define PATHTYPESTOP 		0x20
#define PATHTYPEWOOD3		0x30 		//12 pixel height per wood



class CBallancePath
{
public:
	CBallancePath();
	~CBallancePath();

	class PathUnit
	{
	public:
		unsigned char mode;				//高四位pathtype、低四位路径正方向
//		unsigned char gradient;			//坡度
		int unitamount;						//长度，以最小图片为一个单位
		float posx1;
		float posy1;
		float posx2;
		float posy2;
		QSizeF *unitsize;

#ifdef YL_WIN32_QT
		friend QDebug operator<<(QDebug qd, PathUnit &path)
		{
			qd << "    mode" << hex << (unsigned int)path.mode << dec <<
				  "    unitamount" << path.unitamount <<
				  "    posx1" << path.posx1 <<
				  "    posy1" << path.posy1 <<
				  "    posx2" << path.posx2 <<
				  "    posy2" << path.posy2 <<
				  "    unitsize" << path.unitsize->width() << path.unitsize->height();
			return qd;
		}
#else
		friend std::ostream &operator<<(std::ostream &os, PathUnit &path)
		{
			os << "    mode " << std::hex << (unsigned int)path.mode << std::dec <<
				  "    unitamount " << setw(3) << path.unitamount <<
				  "    posx1 " << setw(8) << path.posx1 <<
				  "    posy1 " << setw(8) << path.posy1 <<
				  "    posx2 " << setw(8) << path.posx2 <<
				  "    posy2 " << setw(8) << path.posy2 <<
				  "    unitsize " << path.unitsize->width() << "  " << path.unitsize->height();
			return os;
		}
#endif
	};

	template<typename Func> int foreachPathUnit(const QVector3D &ballpos, Func func)
	{
		int res = -1;
		m_tre4Path->traversalPreorder([&](PathUnit &pathunit, YLTree4<PathUnit>::NODE *punitnode)
		{
			const PathUnit &unit = pathunit;
			if (res != 0)
			{
				res = this->check(ballpos, punitnode);
			}
			func(unit);
		});
		return res;
	}

	static bool IsStart(const PathUnit &pu);
	static bool IsStop(const PathUnit &pu);
	static bool IsPath(const PathUnit &pu);

	int check(const QVector3D &point, YLTree4<PathUnit>::NODE *punitnode);

protected:
	void InitData();

	YLTree4<PathUnit> *m_tre4Path;

	QSizeF m_szBall;
	QSizeF m_szStart;
	QSizeF m_szStop;
	QSizeF m_szWood3;

private:

};



#endif // BALLANCEPATH_H
