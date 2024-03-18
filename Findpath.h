#pragma once

#include "Triangulation.h"
#include "Point3D.h"


class path
{

public:
	double slope(Point3D P1, Point3D P2);

	vector<Point3D> findpath(Triangulation& terrain);

	//	Point3D gethighestpoint(Triangulation& terrain);

	Point3D nextpoint(Point3D& currentpoint, Triangulation& terrain);

	Point3D findHighestPoint(Triangulation& triangulation);

	Point3D findlowestPoint(Triangulation& triangulation);

	vector<Point3D> generatepath(Point3D& hghestpoint, Triangulation& terrain);
};