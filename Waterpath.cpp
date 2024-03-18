#include "stdafx.h"
#include "WaterPath.h"

WaterPath::WaterPath() {
    
}

WaterPath::~WaterPath() {
   
}

void WaterPath::findHighestPoint(Triangulation& triangulation) {
    mhighestPoint = highestPointFinder.findHighestPoint(triangulation);
     
}

void WaterPath::findNextPoint(Triangulation& triangulation, double distanceThreshold, std::vector<Point3D>& waterPath) 
{   

    //for (auto& point : ourpointslist)
    //{
    //    // Check if the point is within the distance threshold and has a higher elevation
    //    if (!(point.x() == currentPoint.x() && point.y() == currentPoint.y() && point.z() == currentPoint.z()) && withinDistance(point, currentPoint, distanceThreshold)) {
    //        double slope = calculateSlope(currentPoint, point);
    //        if (slope > maxSlope)
    //        {
    //            maxSlope = slope;
    //            nextPoint = point;
    //        }
    //    }
    //}
   /* highestPointFinder.findNextPoint(mhighestPoint, triangulation, distanceThreshold, waterPath);*/
}
