
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

//protected:
	void initdata();

//private:
	class Thepath
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

		friend std::ostream &operator<< (std::ostream &os, Thepath &path)
		{
			os << "CBallancePath::Thepath: \n" <<
				  "\t mode" << hex << (unsigned int)path.mode <<
				  "\t length" << dec <<path.length <<
				  "\t posx1" << path.posx1 <<
				  "\t posy1" << path.posy1 <<
				  "\t posx2" << path.posx2 <<
				  "\t posy2" << path.posy2 <<
				  "\t imagesize" << path.imagesize;
			return os;
		}
	};
	QVector<Thepath> m_vctThepath;
	YLTree4<Thepath> m_tre4Thepath;

	QSizeF m_szBall;
	QSizeF m_szStart;
	QSizeF m_szStop;
	QSizeF m_szWood3;
	QSizeF m_szCross;

};



#endif // BALLANCEPATH_H
