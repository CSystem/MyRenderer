
#ifndef _MY_RENDER_ENUM_H
#define _MY_RENDER_ENUM_H

typedef unsigned int MyRenum;
typedef unsigned char MyRboolean;
typedef unsigned int MyRbitfield;
typedef signed char MyRLbyte;
typedef short MyRshort;
typedef int MyRint;
typedef int MyRsizei;
typedef unsigned char MyRubyte;
typedef unsigned short MyRushort;
typedef unsigned int MyRuint;
typedef float MyRfloat;
typedef float MyRclampf;
typedef double MyRdouble;
typedef double MyRclampd;
typedef void MyRvoid;
typedef char MyRchar;

class Color
{
public:
	MyRfloat r, g, b, a;
	~Color(){}

	Color()
		: r(1),g(1),b(1),a(1)
	{	
	}

	Color(MyRfloat _r, MyRfloat _g, MyRfloat _b, MyRfloat _a)
		: r(_r),g(_g),b(_b),a(_a)
	{ 
	}

	Color(MyRfloat _r, MyRfloat _g, MyRfloat _b)
		: r(_r),g(_g),b(_b),a(1)
	{	
	}

	Color(const Color &color)
		:r(color.r), g(color.g), b(color.b), a(color.a) 
	{ 
	} 

	Color GetInstance()
	{
		return Color(r,g,b,a);
	}

	void operator=(const Color &color)
	{ 
		r = color.r;
		g = color.g;
		b = color.b;
		a = color.a;
	}

	Color operator+(const Color &color)
	{
		return Color(r + color.r, g + color.g, b + color.b, a);
	}

	Color operator-(const Color &color)
	{
		return Color(r - color.r, g - color.g, b - color.b, a);
	}

	bool operator!=(const Color &color)
	{
		return r != color.r || g != color.g || b != color.b;
	}

	bool operator==(const Color &color)
	{
		return r == color.r && g == color.g && b == color.b;
	}
};

typedef struct _sVector2
{
	_sVector2(){ };
	_sVector2(MyRint p1, MyRint p2) : x(p1), y(p2){ };
	_sVector2(const MyRint arr[]): x(arr[0]), y(arr[1]){ };
	MyRint x;
	MyRint y;
}Vector2;

typedef struct _sPolygon
{
	MyRint length;
	Vector2 vertices[4];
}Polygon;


typedef struct tagEDGE
{
	MyRdouble xi;
	MyRdouble dx;
	MyRint ymax;
}EDGE;

#define MAX_POS_X 2048
#define MAX_POS_Y 2048
#define MIN_POS_X -512
#define MIN_POS_Y -512

#define MYR_POINTS 0x0001
#define MYR_LINE 0x0002
#define MYR_TRIANGLE 0x0003
#define MYR_POINTS_LOOP 0x0004

#define MYR_VERTEX_SHADER 0x1001
#define  MYR_FRAGMENT_SHADER 0x1002


#endif // !_MY_RENDER_ENUM_H