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
//bresenham �����㷨
/*
*	ʹ���������ۼ���ȷ��ʲôʱ����������ֵ
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
//�е㻭Բ�㷨
/*
*	f(x,y) = x^2 + y^2 - r^2 d
*	di = f(xi + 1, yi - 1/2) = 	(xi + 1)^2 + (yi - 1/2)^2 - r^2
*	if di < 0 M����Բ�� M������ĵ������Բ	
*  di+1 = f(xi + 2, yi - 1/2) = (xi + 2)^2 + (yi - 1/2)^2 - r^2 = di + 2xi + 3
*  if di > 0 M����Բ�� M������ĵ������Բ
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
		//1/8 Բ
		DrawPixel(x + xCenter,y + yCenter,0,Color());
		//8/8 Բ
		DrawPixel(xCenter - x,y + yCenter,0,Color());
		//2/8 Բ
		DrawPixel(y + yCenter,x + xCenter,0,Color());
		//7/8 Բ
		DrawPixel(yCenter - y,x + xCenter,0,Color());
		//4/8 Բ
		DrawPixel(x + xCenter,yCenter - y,0,Color());
		//5/8 Բ
		DrawPixel(xCenter - x,yCenter - y,0,Color());
		//6/8 Բ
		DrawPixel(yCenter - y,xCenter - x,0,Color());
		//3/8 Բ
		DrawPixel(yCenter + y,xCenter - x,0,Color());
	}
	glEnd();
}
//�����
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
//Ч�����ã��е�����û������ϣ�������Ҫ������㷨�������ɫ
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
DIRECTION direction_8[] = { {-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1} };	//��Ϊ�ĸ��������ɳ�Ϊ����ͨ�㷨


//��������㷨����Ϊ����ͨ������ͨ������ֻͨ���������ң�����ͨ�����������ң����ϣ����ϣ����£�����
//ע����������㷨 ���ֱ߽磬���������滻��ɫ���ҵ�ָ����ɫ�滻���µ���ɫ���ݹ�����,�޶������귶Χ�����귶Χ̫������ջ���
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

//�߽磬��������㷨,����ջ������޶����귶Χ,��֪��Ϊʲô ����ͨ�ͻ�ջ���
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
#pragma region ɨ����������䷨
/// <summary>
///(1) ��ʼ��һ���յ�ջ���ڴ�����ӵ㣬�����ӵ�(x, y)��ջ��
///(2) �ж�ջ�Ƿ�Ϊ�գ����ջΪ��������㷨������ȡ��ջ��Ԫ����Ϊ��ǰɨ���ߵ����ӵ�(x, y)��y�ǵ�ǰ��ɨ���ߣ�
///(3) �����ӵ�(x, y)�������ص�ǰɨ��������������������䣬ֱ���߽硣�ֱ������ε����Ҷ˵�����ΪxLeft��xRight��
///(4) �ֱ����뵱ǰɨ�������ڵ�y - 1��y + 1����ɨ����������[xLeft, xRight]�е����أ���xLeft��ʼ��xRight���������������ڷǱ߽���δ�������ص㣬���ҳ���Щ���ڵ����ص������ұߵ�һ������������Ϊ���ӵ�ѹ��ջ�У�Ȼ�󷵻صڣ�2������ 
/// </summary>
//ɨ����������䷨
void MyRender::ScanLineFillAlgorithm(MyRint x, MyRint y, Color newColor, Color boundColor)
{	
	stack<Vector2> sVStack;
	sVStack.push(Vector2(x,y));		//����һ�����ӵ�ѹ��ջ

	while (!sVStack.empty())
	{
		Vector2 vPoint = sVStack.top();	//��ջһ�����ӵ�

		sVStack.pop();
		//�������ֱ���߽�
		MyRint num = FillLineRight(vPoint.x, vPoint.y , newColor, boundColor);
		cout<<"Rightnum"<<num<<endl;
		//�õ��Ҳ�߽����ӵ�
		MyRint xRight = vPoint.x + num - 1;
		//�������ֱ���߽�
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
/// ɨ��������㷨������߱���  
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
//��ʼ��ɨ�����±߱�
void InitScanLineNewEdgeTable(std::vector< std::list<EDGE> >& slNet,const Polygon& py, int ymin, int ymax)
{
	EDGE e;
	for(int i = 0; i < py.length; i++)
	{
		const Vector2& ps = py.vertices[i];
		const Vector2& pe = py.vertices[(i + 1) % py.length];
		const Vector2& pss = py.vertices[(i - 1 + py.length) % py.length];
		const Vector2& pee = py.vertices[(i + 2) % py.length];

		if(pe.y != ps.y) //������ˮƽ��
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



