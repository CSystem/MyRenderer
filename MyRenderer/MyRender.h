#ifndef _MY_RENDER_H
#define _MY_RENDER_H

#include "MyRenderEnum.h"
#include <stack> 
#include <list>
#include <vector>
#include <iostream>
#include <gl/glew.h>
#include <gl/glut.h>
class MyRender
{
public:
	MyRender();
	~MyRender();
	void DrawArray(MyRenum mode, MyRfloat * buffer, MyRint length);
	void LoadShader(MyRchar *vsName, MyRchar *vfName);
	void DrawLine(MyRint startX, MyRint startY, MyRint endX, MyRint endY);
	void DrawCircle(MyRint radius,MyRint x, MyRint y);
	void DrawPolygon(MyRint vArray[], MyRint length);
	void DrawCircleAndFill(MyRint radius,MyRint x, MyRint y);
	void FloodFillAlgorithm(MyRint x, MyRint y, Color oldColor, Color newColor);
	void BoundaryFillAlgorithm(MyRint x, MyRint y, Color &newColor, Color &boundColor);
	void ScanLineFillAlgorithm(MyRint x, MyRint y, Color newColor, Color boundColor);
	void ScanLineOrderdMarginsTableFillAlgorithm(const Polygon &py, Color newColor);
	void DrawPixel(MyRint x, MyRint y, MyRint z, Color color);
	void GetPixelRGBColor(MyRint x, MyRint y, Color &color);
private:
	void GetPolygonMinMax(const Polygon & py, MyRint &yMin, MyRint &yMax);
	MyRint GetLeftLineCrossPointNum(MyRint x, MyRint y, Color boundColor);
	MyRint GetRightLineCrossPointNum(MyRint x, MyRint y, Color boundColor);
	MyRint FindLeftNotBoundNearestPointX(MyRint x, MyRint y, Color boundColor);
	MyRint FillLineLeft(MyRint x, MyRint y, Color newColor, Color boundColor);
	MyRint FillLineRight(MyRint x, MyRint y, Color newColor, Color boundColor);
	void SearchLineNewSeed(std::stack<Vector2> &stk,MyRint xLeft, MyRint xRight, MyRint y, Color newColor, Color boundColor);
	MyRint SkippInValidPointInLine(MyRint x, MyRint y,MyRint xRight, Color newColor, Color boundColor );
	void SwapValue(MyRint *x1, MyRint *x2);
	void GetPixelColor(MyRint x, MyRint y, void *pixel);
	void SetPixelColor(MyRint x, MyRint y, Color color);
	void UseVertexShader();
	void GeneratePrimitives();
	void Rasterization();
	void UseFragmentShader();
	void TestingAndMix();
	void AddToFrameBuffer();
};
#endif // !_MY_RENDER_H