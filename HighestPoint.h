#pragma once
#include "Triangulation.h"

class HighestPoint {
public:
    
    HighestPoint();

    ~HighestPoint();

    Point3D findHighestPoint(Triangulation& triangulation);

    double calculateSlope( Point3D& point1, Point3D& point2);

    void findNextPoint( Point3D& currentPoint,  Triangulation& triangulation, double distanceThreshold, std::vector<Point3D>& waterPath);

    bool withinDistance( Point3D& p1,  Point3D& p2, double distanceThreshold);
};
