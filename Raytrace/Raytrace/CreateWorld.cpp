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

	// Top
	Triangle T1(V1, V13, V3, N1, fin);
	Triangle T2(V3, V13, V5, N1, fin);
	Triangle T3(V1, V2, V5, N1, fin);
	Triangle T4(V2, V6, V5, N1, fin);
	Triangle T5(V2, V4, V14, N1, fin);
	Triangle T6(V4, V6, V14, N1, fin);

	// Bottom
	Triangle T7(V7, V15, V9, N2, fin);
	Triangle T8(V9, V15, V11, N2, fin);
	Triangle T9(V7, V8, V11, N2, fin);
	Triangle T10(V8, V12, V11, N2, fin);
	Triangle T11(V8, V10, V16, N2, fin);
	Triangle T12(V10, V12, V16, N2, fin);
	// Front _
	Triangle T13(V5, V6, V11, N3, fin);
	Triangle T14(V6, V12, V11, N3, fin);

	// Front left
	Triangle T15(V3, V5, V9, N4, fin);
	Triangle T16(V5, V11, V9, N4, fin);

	// Back left
	Triangle T17(V1, V3, V7, N5, fin);
	Triangle T18(V3, V9, V7, N5, fin);

	// Back
	Triangle T19(V1, V2, V7, N6, fin);
	Triangle T20(V2, V8, V7, N6, fin);

	// Back right
	Triangle T21(V2, V4, V8, N7, fin);
	Triangle T22(V4, V10, V8, N7, fin);

	// Front right
	Triangle T23(V4, V6, V8, N8, fin);
	Triangle T24(V6, V12, V10, N8, fin);
}


CreateWorld::~CreateWorld()
{
}
