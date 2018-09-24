#include "CreateWorld.h"



CreateWorld::CreateWorld()
{
	Vertex V1(0, 6, 5);
	Vertex V2(10, 6, 5);
	Vertex V3(-3, 0, 5);
	Vertex V4(13, 0, 5);
	Vertex V5(0, -6, 5);
	Vertex V6(10, -6, 5);
	Vertex V7(0, 6, -5);
	Vertex V8(10, 6, -5);
	Vertex V9(-3, 0, -5);
	Vertex V10(13, 0, -5);
	Vertex V11(0, -6, -5);
	Vertex V12(10, -6, -5);
	Vertex V13(0, 0, 5);
	Vertex V14(10, 0, 5);
	Vertex V15(0, 0, 5);
	Vertex V16(10, 0, -5);

	Direction N1(0, 0, -1); // Top
	Direction N2(0, 0, 1); // Bottom
	Direction N3(0, 1, 0); // Front
	Direction N4(2 / sqrt(5), 1 / sqrt(5), 0); // Front left
	Direction N5(2 / sqrt(5), -1 / sqrt(5), 0); // Back left
	Direction N6(0, -1, 0); // Back
	Direction N7(-2 / sqrt(5), -1 / sqrt(5), 0); // Back right
	Direction N8(-2 / sqrt(5), 1 / sqrt(5), 0); // Front right

	ColorDbl fin(255, 0, 204);
	ColorDbl white(255, 255, 255);
	ColorDbl b(0, 0, 200);
	ColorDbl r(200, 0, 0);
	ColorDbl g(0, 200, 0);
	ColorDbl c(0, 200, 200);
	ColorDbl y(200, 200, 0);

	// Top
	Triangle T1(V1, V13, V3, N1, white);
	Triangle T2(V3, V13, V5, N1, white);
	Triangle T3(V1, V2, V5, N1, white);
	Triangle T4(V2, V6, V5, N1, white);
	Triangle T5(V2, V4, V14, N1, white);
	Triangle T6(V4, V6, V14, N1, white);

	// Bottom
	Triangle T7(V7, V15, V9, N2, white);
	Triangle T8(V9, V15, V11, N2, white);
	Triangle T9(V7, V8, V11, N2, white);
	Triangle T10(V8, V12, V11, N2, white);
	Triangle T11(V8, V10, V16, N2, white);
	Triangle T12(V10, V12, V16, N2, white);

	// Front _
	Triangle T13(V5, V6, V11, N3, fin);
	Triangle T14(V6, V12, V11, N3, fin);

	// Front left
	Triangle T15(V3, V5, V9, N4, b);
	Triangle T16(V5, V11, V9, N4, b);

	// Back left
	Triangle T17(V1, V3, V7, N5, r);
	Triangle T18(V3, V9, V7, N5, r);

	// Back
	Triangle T19(V1, V2, V7, N6, g);
	Triangle T20(V2, V8, V7, N6, g);

	// Back right
	Triangle T21(V2, V4, V8, N7, c);
	Triangle T22(V4, V10, V8, N7, c);

	// Front right
	Triangle T23(V4, V6, V8, N8, y);
	Triangle T24(V6, V12, V10, N8, y);

	
}


CreateWorld::~CreateWorld()
{
}
