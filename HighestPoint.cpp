#include "stdafx.h"
#include "HighestPoint.h"
#include "Triangulation.h"
#include <algorithm> 

HighestPoint::HighestPoint() {
    // Constructor implementation (if needed)
}

HighestPoint::~HighestPoint() {
    // Destructor implementation (if needed)
}

Point3D HighestPoint::findHighestPoint(Triangulation& triangulation)  
{   
    vector<Point3D> points = triangulation.uniquePoints();
    double highestpoint = 0.0;
    Point3D answer;
    for (auto point : points) 
    {
        double high = point.z();
       
        if (high>highestpoint ) 

        {
            highestpoint = high;
            answer = point;
        }
        
    }

    return answer;
    // Heloo
    
}

double HighestPoint::calculateSlope( Point3D& point1,  Point3D& point2) {
    double dx = point2.x() - point1.x();
    double dy = point2.y() - point1.y();
    double dz = point2.z() - point1.z();
    double distance = std::sqrt(dx * dx + dy * dy + dz * dz);
    return std::abs(dz / distance); 
}

bool HighestPoint::withinDistance( Point3D& p1,  Point3D& p2, double distanceThreshold) {
    double dx = p1.x() - p2.x();
    double dy = p1.y() - p2.y();
    double dz = p1.z() - p2.z();
    double distance = std::sqrt(dx * dx + dy * dy + dz * dz);
    return distance <= distanceThreshold;
}
bool isequal(Point3D P1, Point3D P2)
{
    return(P1.x() == P2.x() && P1.y() == P2.y() && P1.z() == P2.z());
}

vector<Point3D> getsurroundingpoints(Point3D currentpoint,Triangulation &triangulation)
{
    vector<Point3D> answer;
    vector<Point3D> points = triangulation.uniquePoints();
    Point3D refrencepoint = currentpoint; 
    int count = 0;
    
    for (auto it : triangulation.triangles())
    {
        if (count == 6)
            break;
       
            if (isequal(refrencepoint,points[it.v1()]))
            {   
                count++;
                answer.push_back(points[it.v2()]);
                answer.push_back(points[it.v3()]);

            }
     
            if (isequal(refrencepoint, points[it.v2()]))
            {
                count++;
                answer.push_back(points[it.v1()]);
                answer.push_back(points[it.v3()]);

            }
            if (isequal(refrencepoint, points[it.v3()]))
            {
                count++;
                answer.push_back(points[it.v1()]);
                answer.push_back(points[it.v2()]);

            }


    }
    return answer;
}
void HighestPoint::findNextPoint(Point3D& currentPoint, Triangulation& triangulation, double distanceThreshold, std::vector<Point3D>& waterPath) 
{
    Point3D nextPoint = currentPoint;
    double maxSlope = 0.0;
    vector<Point3D> ourpointslist =  getsurroundingpoints(currentPoint,triangulation);
    
        for (auto& point :ourpointslist)
        {
            // Check if the point is within the distance threshold and has a higher elevation
            if (!(point.x() == currentPoint.x() && point.y() == currentPoint.y() && point.z() == currentPoint.z()) && withinDistance(point, currentPoint, distanceThreshold)) {
                double slope = calculateSlope(currentPoint, point);
                if (slope > maxSlope) 
                {
                    maxSlope = slope;
                    nextPoint = point;
                }
            }
        }
    

    waterPath.push_back(currentPoint);

    if (currentPoint.z() > nextPoint.z()) {
        findNextPoint(nextPoint, triangulation, 1.0, waterPath);

   }
}


