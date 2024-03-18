#pragma once
#include "Triangulation.h"
#include "HighestPoint.h"
#include <vector>

class WaterPath {
public:
    WaterPath();
    ~WaterPath();

    void findHighestPoint(Triangulation& triangulation);
    void findNextPoint(Triangulation& triangulation, double distanceThreshold, std::vector<Point3D>& waterPath);
private:
    HighestPoint highestPointFinder;
    Point3D mhighestPoint;
};
