#include "MyRender.h"
//  [3/30/2015 wangpengfei]
#include "Tool.h"

using namespace std;
MyRender::MyRender()
{

}

MyRender::~MyRender()
{

}

void MyRender::DrawArray(MyRenum mode, MyRfloat * buffer, MyRint length)
{

}
//bresenham 画线算法
/*
*	使用误差分量累加来确定什么时候增加坐标值
*/
void MyRender::DrawLine(MyRint startX, MyRint startY, MyRint endX, MyRint endY)
{
	MyRint deltaX = endX - startX;
	MyRint deltaY = endY - startY;

	MyRfloat deltaX2 = deltaX << 1;
	MyRfloat deltaY2 = deltaY << 1;
	MyRfloat error = deltaX2;	

	if(deltaX > deltaY && deltaX != deltaY && deltaX != -deltaY){
		glBegin(GL_POINTS);
		for (MyRint x = startX ,y = startY; x < endX ; x++)
		{
			DrawPixel(x,y,0,Color());
			error -= deltaY2;
			if(error < 0){
				y++;
				error += deltaX2;
			}
		}
		glEnd();
	}
	else if(deltaX == deltaY || deltaX == -deltaY)
	{
		if(deltaX == -deltaY){
			if(deltaX > 0){
				glBegin(GL_POINTS);
				for (MyRint x = startX ,y = startY; x < endX ; x++)
				{
					DrawPixel(x,y,0,Color());
					if(startY - endY < 0){
						y++;
					}else{
						y--;
					}
				}
				glEnd();
			}

			if(deltaX < 0){
				glBegin(GL_POINTS);
				for (MyRint x = startX ,y = startY; x < endX ; x--)
				{
					DrawPixel(x,y,0,Color());
					if(startY - endY < 0){
						y++;
					}else{
						y--;
					}
				}
				glEnd();
			}
		}

		if(deltaX == deltaY){
			if(deltaX > 0){
				glBegin(GL_POINTS);
				for (MyRint x = startX ,y = startY; x < endX ; x++)
				{
					DrawPixel(x,y,0,Color());
					if(startY - endY < 0){
						y++;
					}else{
						y--;
					}
				}
				glEnd();
			}

			if(deltaX < 0){
				glBegin(GL_POINTS);
				for (MyRint x = startX ,y = startY; x < endX ; x--)
				{
					DrawPixel(x,y,0,Color());
					if(startY - endY < 0){
						y++;
					}else{
						y--;
					}
				}
				glEnd();
			}
		}
	}
	else
	{
		error = deltaY2;
		glBegin(GL_POINTS);
		for (MyRint x = startX ,y = startY; y < endY ; y++)
		{
			DrawPixel(x,y,0,Color());
			error -= deltaX2;
			if(error < 0){
				x++;
				error += deltaY2;
			}
		}
		glEnd();
	}

}
//中点画圆算法
/*
*	f(x,y) = x^2 + y^2 - r^2 d
*	di = f(xi + 1, yi - 1/2) = 	(xi + 1)^2 + (yi - 1/2)^2 - r^2
*	if di < 0 M点在圆内 M点上面的点更靠近圆	
*  di+1 = f(xi + 2, yi - 1/2) = (xi + 2)^2 + (yi - 1/2)^2 - r^2 = di + 2xi + 3
*  if di > 0 M点在圆外 M点下面的点更靠近圆
*	di+1 = f(xi + 2, yi - 3/2) = (xi + 2)^2 + (yi - 3/2)^2 - r^2 = di + 2*(xi - yi) + 5
*/

void MyRender::DrawCircle(MyRint radius,MyRint xCenter, MyRint yCenter)
{
	float x = 0;
	float y = radius;
	float d;
	d = 1.25 - radius;
	glBegin(GL_POINTS);
	DrawPixel(x + xCenter ,y + yCenter,0,Color());
	DrawPixel(radius + xCenter + x ,yCenter,0,Color());
	DrawPixel(x + xCenter ,yCenter - y,0,Color());
	DrawPixel(x + xCenter - radius , yCenter,0,Color());
	while( x <= y){ 
		if( d < 0 ){
			d += 2*x + 3;
		}
		else { 
			d += 2*( x - y ) + 5; 
			y--;
		}
		x++;
		//1/8 圆
		DrawPixel(x + xCenter,y + yCenter,0,Color());
		//8/8 圆
		DrawPixel(xCenter - x,y + yCenter,0,Color());
		//2/8 圆
		DrawPixel(y + yCenter,x + xCenter,0,Color());
		//7/8 圆
		DrawPixel(yCenter - y,x + xCenter,0,Color());
		//4/8 圆
		DrawPixel(x + xCenter,yCenter - y,0,Color());
		//5/8 圆
		DrawPixel(xCenter - x,yCenter - y,0,Color());
		//6/8 圆
		DrawPixel(yCenter - y,xCenter - x,0,Color());
		//3/8 圆
		DrawPixel(yCenter + y,xCenter - x,0,Color());
	}
	glEnd();
}
//多边形
void MyRender::DrawPolygon(MyRint vArray[], MyRint length)
{
	// 	if(NULL == vArray)
	// 		return;
	// 
	// 	for (int i = 0; i < length; i++)
	// 	{
	// 
	// 	}
	DrawLine(1,1, 1,100);
	DrawLine(1,1,100,1);
	DrawLine(1,100,100,1);

}
//效果不好，有的像素没有填充上，还是需要用填充算法来填充颜色
void MyRender::DrawCircleAndFill(MyRint radius,MyRint x, MyRint y)
{
	for (int i = 1; i < radius; i++)
	{
		DrawCircle(i, x, y);
	}
}


typedef struct tagDIRECTION
{
	int x_offset;
	int y_offset;
}DIRECTION;
DIRECTION direction_8[] = { {-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1} };	//改为四个数，即可成为四联通算法


//种子填充算法，分为八连通和四联通，四联通只有上下左右，八连通包括上下左右，左上，右上，左下，右下
//注入种子填充算法 不分边界，可以用来替换颜色，找到指定颜色替换成新的颜色，递归搜索,限定了坐标范围，坐标范围太大会造成栈溢出
void MyRender::FloodFillAlgorithm(MyRint x, MyRint y, Color oldColor, Color newColor)
{
	if(x < 495 || y < 495)
	{
		return;
	}

	if(x > 505 || y > 505)
	{
		return;
	}

	MyRint *color = (MyRint *)malloc(1);
	GetPixelColor(x, y, color);
	MyRfloat r = (*color & 0xff) / 255;
	MyRfloat g = (*color>>8 & 0xff ) / 255;
	MyRfloat b = (*color>>24 & 0xff ) / 255;
	MyRfloat a = (*color>>24 & 0xff ) / 255;

	if(r == oldColor.r && g == oldColor.g && b == oldColor.b)
	{
		SetPixelColor(x, y, newColor);
		for(int i = 0; i < 8; i++)
		{
			FloodFillAlgorithm(x + direction_8[i].x_offset,
				y + direction_8[i].y_offset, oldColor, newColor);
		}
	}
}

//边界，种子填充算法,避免栈溢出，限定坐标范围,不知道为什么 五联通就会栈溢出
void MyRender::BoundaryFillAlgorithm(MyRint x, MyRint y, Color &newColor, Color &boundColor)
{
	if(x < 480 || y < 480)
	{
		return;
	}

	if(x > 490 || y > 490)
	{
		return;
	}
	// 	MyRint *color = (MyRint *)malloc(1 * sizeof(MyRint));
	// 	GetPixelColor(x, y, color);
	// 	MyRfloat r = (*color & 0xff) / 255;
	// 	MyRfloat g = (*color>>8 & 0xff ) / 255;
	// 	MyRfloat b = (*color>>24 & 0xff ) / 255;
	// 	MyRfloat a = (*color>>24 & 0xff ) / 255;
	Color color;
	GetPixelRGBColor(x, y, color);
	if(color != boundColor && color != newColor)//(r != boundColor.r || g != boundColor.g || b != boundColor.b )&&(r != newColor.r || g != newColor.g || b != newColor.b))
	{
		SetPixelColor(x, y, newColor);
		for(int i = 0; i < 4; i++)
		{
			BoundaryFillAlgorithm(x + direction_8[i].x_offset,
				y + direction_8[i].y_offset, newColor, boundColor);
		}
	}
	//free(color);
}
#pragma region 扫描线种子填充法
/// <summary>
///(1) 初始化一个空的栈用于存放种子点，将种子点(x, y)入栈；
///(2) 判断栈是否为空，如果栈为空则结束算法，否则取出栈顶元素作为当前扫描线的种子点(x, y)，y是当前的扫描线；
///(3) 从种子点(x, y)出发，沿当前扫描线向左、右两个方向填充，直到边界。分别标记区段的左、右端点坐标为xLeft和xRight；
///(4) 分别检查与当前扫描线相邻的y - 1和y + 1两条扫描线在区间[xLeft, xRight]中的像素，从xLeft开始向xRight方向搜索，若存在非边界且未填充的像素点，则找出这些相邻的像素点中最右边的一个，并将其作为种子点压入栈中，然后返回第（2）步； 
/// </summary>
//扫描线种子填充法
void MyRender::ScanLineFillAlgorithm(MyRint x, MyRint y, Color newColor, Color boundColor)
{	
	stack<Vector2> sVStack;
	sVStack.push(Vector2(x,y));		//将第一个种子点压入栈

	while (!sVStack.empty())
	{
		Vector2 vPoint = sVStack.top();	//出栈一个种子点

		sVStack.pop();
		//向左填充直到边界
		MyRint num = FillLineRight(vPoint.x, vPoint.y , newColor, boundColor);
		cout<<"Rightnum"<<num<<endl;
		//得到右侧边界种子点
		MyRint xRight = vPoint.x + num - 1;
		//向右填充直到边界
		num = FillLineLeft(vPoint.x, vPoint.y, newColor, boundColor);
		MyRint xLeft = vPoint.x - num;
		cout<<"xRight"<<xRight<<endl;
		cout<<"x"<<x<<endl;
		cout<<"Leftnum"<<num<<endl;
		cout<<"vPointX"<<vPoint.x<<endl;
		cout<<"vPointY"<<vPoint.y<<endl;

		//SearchLineNewSeed(sVStack, xLeft, xRight, vPoint.y + 1, newColor, boundColor);
		SearchLineNewSeed(sVStack, xLeft, xRight, vPoint.y - 1, newColor, boundColor);
	}
}

MyRint MyRender::FillLineLeft(MyRint x, MyRint y, Color newColor, Color boundColor)
{
	MyRint i = 0;
	while (x - i> 0)
	{
		Color color;
		GetPixelRGBColor(x - i, y, color);
		if(color == boundColor || color == newColor)
			break;
		SetPixelColor(x - i, y, newColor);
		i++;
	}
	return i;
}

MyRint MyRender::FillLineRight(MyRint x, MyRint y, Color newColor, Color boundColor)
{
	MyRint i = 0;
	while (x + i< 1024)
	{
		Color color;
		GetPixelRGBColor(x + i, y, color);
		if(color == boundColor || color == newColor)
			break;
		SetPixelColor(x + i, y, newColor);
		i++;
	}
	return i;
}

void MyRender::SearchLineNewSeed(stack<Vector2> &stk,MyRint xLeft, MyRint xRight, MyRint y, Color newColor, Color boundColor)
{
	if(xRight > 1024)
		return;

	MyRint x = xLeft;

	MyRboolean bFindNewSeed = false;
	Color color;
	
	MyRint leftPoints = GetLeftLineCrossPointNum(xRight, y, boundColor);

	if(leftPoints > 1)
	{
		xRight = FindLeftNotBoundNearestPointX(xRight, y, boundColor);
	}

	while (x <= xRight)
	{
		bFindNewSeed = false;
		GetPixelRGBColor(x, y, color);

		while (color != newColor && color != boundColor && x < xRight)
		{
			bFindNewSeed = true;
			x++;
		}
		MyRint xSpan = SkippInValidPointInLine(x, y, xRight, newColor, boundColor);
		if(xSpan >= (xRight - xLeft)){
			bFindNewSeed = false;
		}
		if(bFindNewSeed)
		{
			if(color != newColor && color != boundColor && x == xRight)
			{
				stk.push(Vector2(x ,y));
			}
			else {
				stk.push(Vector2(x - 1,y));		
			}
		}	
		x += xSpan == 0 ? 1 : xSpan;
	}

	if(x >= xRight)
	{
		cout<<"x = "<< x<<endl;
		cout<<"xRight = "<< xRight<<endl;
	}

}

MyRint MyRender::SkippInValidPointInLine(MyRint x, MyRint y,MyRint xRight, Color newColor, Color boundColor )
{
	if(x > xRight)
		return 0;

	Color color;
	MyRint spanX = 0;
	while (x < xRight)
	{
		GetPixelRGBColor(x, y, color);
		if(color == newColor || color == boundColor)
		{
			spanX++;
		}
		x++;
	}
	return spanX;
}

MyRint MyRender::GetLeftLineCrossPointNum(MyRint x, MyRint y, Color boundColor)
{
	Color color;
	MyRint num = 0;
	while (x >= MIN_POS_X)
	{
		GetPixelRGBColor(x,y,color);
		if(color == boundColor)
			num++;
		x--;
	}
	return num;
}

MyRint MyRender::GetRightLineCrossPointNum(MyRint x, MyRint y, Color boundColor)
{
	Color color;
	MyRint num = 0;
	while (x <= MAX_POS_X)
	{
		GetPixelRGBColor(x,y,color);
		if(color == boundColor)
			num++;
		x++;
	}
	return num;
}

MyRint MyRender::FindLeftNotBoundNearestPointX(MyRint x, MyRint y, Color boundColor)
{
	MyRboolean bFindBound = false;
	Color color;
	while (!bFindBound)
	{
		GetPixelRGBColor(x,y,color);
		if(color == boundColor)
		{
			bFindBound = true;
			break;
		}
		x--;
	}

	while (bFindBound)
	{
		x--;
		GetPixelRGBColor(x,y,color);
		if(color != boundColor)
		{
			break;
		}
	}
	return x;
}

#pragma endregion
/// <summary>
/// 扫描线填充算法（有序边表法）  
/// </summary>
void MyRender::ScanLineOrderdMarginsTableFillAlgorithm(const Polygon &py, Color newColor)
{
	MyRint yMax = 0;
	MyRint yMin = 0;
	GetPolygonMinMax(py, yMin, yMax);
	std::vector< std::list<EDGE> > slNet(yMax - yMin + 1);
	//InitScanLineNewEdgeTable(slNet, py, yMin, yMax);

}

void MyRender::GetPolygonMinMax(const Polygon & py, MyRint &yMin, MyRint &yMax)
{
	MyRint tmpMinY = py.vertices[0].y,tmpMaxY = py.vertices[0].y;

	for (int i = 1 ; i < py.length; i++ )
	{
		if(py.vertices[i].y < tmpMinY)
			tmpMinY = py.vertices[i].y;
		if(py.vertices[i].y > tmpMaxY)
			tmpMaxY = py.vertices[i].y;
	}
}
//初始化扫描线新边表
void InitScanLineNewEdgeTable(std::vector< std::list<EDGE> >& slNet,const Polygon& py, int ymin, int ymax)
{
	EDGE e;
	for(int i = 0; i < py.length; i++)
	{
		const Vector2& ps = py.vertices[i];
		const Vector2& pe = py.vertices[(i + 1) % py.length];
		const Vector2& pss = py.vertices[(i - 1 + py.length) % py.length];
		const Vector2& pee = py.vertices[(i + 2) % py.length];

		if(pe.y != ps.y) //不处理水平线
		{
			e.dx = double(pe.x - ps.x) / double(pe.y - ps.y);
			if(pe.y > ps.y)
			{
				e.xi = ps.x;
				if(pee.y >= pe.y)
					e.ymax = pe.y - 1;
				else
					e.ymax = pe.y;

				slNet[ps.y - ymin].push_front(e);
			}
			else
			{
				e.xi = pe.x;
				if(pss.y >= ps.y)
					e.ymax = ps.y - 1;
				else
					e.ymax = ps.y;
				slNet[pe.y - ymin].push_front(e);
			}
		}
	}
}

void MyRender::SwapValue(MyRint *x1, MyRint *x2)
{
	int x = *x1;
	*x1 = *x2;
	*x2 = x;
}

void MyRender::DrawPixel(MyRint x, MyRint y, MyRint z, Color color)
{
	glColor3f(1, 0, 0);
	glVertex3f(x, y, z);
}

void MyRender::GetPixelRGBColor(MyRint x, MyRint y, Color &color)
{
	MyRint *pixel = (MyRint *)malloc(1 * sizeof(MyRint));
	GetPixelColor(x, y, pixel);
	color.r = (*pixel & 0xff) / 255;
	color.g = (*pixel>>8 & 0xff ) / 255;
	color.b = (*pixel>>16 & 0xff ) / 255;
	color.a = (*pixel>>24 & 0xff ) / 255;
	free(pixel);
}

void MyRender::GetPixelColor(MyRint x, MyRint y, void *pixel)
{
	glReadPixels(x, y, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, pixel);
}

void MyRender::SetPixelColor(MyRint x, MyRint y, Color color)
{
	glBegin(GL_POINTS);
	glColor3f(color.r, color.g, color.b);
	glVertex3f(x, y, 0);
	glEnd();
}



