
#ifndef BALLANCEPATH_H
#define BALLANCEPATH_H

#include <QVector>

#define PATHDIR 			0x0f
#define PATHDIRNULL			0x00
#define PATHDIRN 			0x01
#define PATHDIRS 			0x02
#define PATHDIRW 			0x04
#define PATHDIRE 			0x08
#define PATHTYPE 			0xf0
#define PATHTYPESTART 		0x00
#define PATHTYPESTOP 		0x80
#define PATHTYPEWOOD3		0x10 		//12 pixel height per wood



class CBallancePath
{
public:
	CBallancePath();
	~CBallancePath();

protected:
	void initdata();

private:
	class Thepath
	{
	public:
//		Thepath()

		unsigned char mode;		//高四位pathtype、低四位路径正方向
//		unsigned char gradient;	//坡度
		unsigned short length;		//长度，以最小图片为一个单位
		short posx1;
		short posy1;
		short posx2;
		short posy2;
	};
	QVector<Thepath> m_vctThepath;

};



#endif // BALLANCEPATH_H
