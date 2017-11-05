
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
		int length;						//长度，以最小图片为一个单位
		float posx1;
		float posy1;
		float posx2;
		float posy2;
		QSizeF *imagesize;

		friend std::ostream &operator<<(std::ostream &os, PathUnit &path)
		{
			os << "CBallancePath::PathUnit: \n" <<
				  "\t mode" << std::hex << (unsigned int)path.mode << std::dec <<
				  "\t length" << path.length <<
				  "\t posx1" << path.posx1 <<
				  "\t posy1" << path.posy1 <<
				  "\t posx2" << path.posx2 <<
				  "\t posy2" << path.posy2 <<
				  "\t imagesize" << path.imagesize;
			return os;
		}
#ifdef YL_WIN32_QT
		friend QDebug operator<<(QDebug qd, PathUnit &path)
		{
			qd << "    mode" << hex << (unsigned int)path.mode <<
				  "    length" << dec <<path.length <<
				  "    posx1" << path.posx1 <<
				  "    posy1" << path.posy1 <<
				  "    posx2" << path.posx2 <<
				  "    posy2" << path.posy2 <<
				  "    imagesize" << path.imagesize->width() << path.imagesize->height();
			return qd;
		}
#endif
	};

	template<typename Func> void foreachPathUnit(Func func)
	{
		m_tre4Path->traversalPreorder([&](PathUnit &initdatapathunit, YLTree4<PathUnit>::NODE *pinitdatanode)
		{
			const PathUnit &pathunit = initdatapathunit;
			func(pathunit);
		});
	}

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
