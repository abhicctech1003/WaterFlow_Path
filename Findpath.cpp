#include"stdafx.h"

#include <cmath>
#include"Findpath.h"
#include "STLWriter.h"



double path::slope(Point3D point1, Point3D point2)
{
	/*double numerator,denominator;

	numerator = P2.z() - P1.z();
	denominator = sqrt( ( P2.x()-P1.x()* P2.x() - P1.x() ) + P2.y() - P1.y() * P2.y() - P1.y()) ;

	double answer = numerator / denominator;
	return answer;*/

	double dx = point2.x() - point1.x();
	double dy = point2.y() - point1.y();
	double dz = point2.z() - point1.z();
	double distance = std::sqrt(dx * dx + dy * dy + dz * dz);
	return std::abs(dz / distance);
}

Point3D path::findHighestPoint(Triangulation& triangulation)
{
	vector<Point3D> points = triangulation.uniquePoints();
	double highestpoint = 0.0;
	Point3D answer;
	for (auto point : points)
	{
		double high = point.z();
		if (high > highestpoint)

		{
			highestpoint = high;
			answer = point;
		}
	}

	return answer;

}
Point3D path::findlowestPoint(Triangulation& triangulation)
{
	vector<Point3D> points = triangulation.uniquePoints();
	double lowestpoint = 0.0;
	Point3D answer;
	for (auto point : points)
	{
		double low = point.z();
		if (low < lowestpoint)

		{
			lowestpoint = low;
			answer = point;
		}
	}

	return answer;

}

Point3D path::nextpoint(Point3D& currpoint, Triangulation& terrain)
{
	vector<Triangle> triangles = terrain.triangles();
	vector<Point3D> uniquepoints = terrain.uniquePoints();

	Point3D currentpoint = currpoint;
	vector<Point3D> connectedvertics;
	for (auto triangle : triangles)
	{
		Point3D P1, P2, P3;
		P1 = uniquepoints[triangle.v1()];
		P2 = uniquepoints[triangle.v2()];
		P3 = uniquepoints[triangle.v3()];

		if (P1 == currpoint)
		{
			connectedvertics.push_back(P2);
			connectedvertics.push_back(P3);
		}
		else if (P2 == currentpoint)
		{

			connectedvertics.push_back(P1);
			connectedvertics.push_back(P3);

		}
		else if (P3 == currentpoint)
		{

			connectedvertics.push_back(P1);
			connectedvertics.push_back(P2);

		}

	}

	Point3D final;
	//checking for slope with the current point and answer vertices
	double steepestpoint = slope(currentpoint, connectedvertics[0]);

	for (auto it : connectedvertics)
	{
		double currentslope;
		currentslope = slope(currentpoint, it);
		if (currentslope >= steepestpoint)
		{
			final = it;
		}
	}
	return final;
}

vector<Point3D> path::generatepath(Point3D& highestpoint, Triangulation& terrain)
{
	vector<Point3D> result;
	Point3D currentpoint = highestpoint;
	Point3D end = findlowestPoint(terrain);

	while (true)
	{
		Point3D newpoint = nextpoint(currentpoint, terrain);
		if (newpoint.z() == end.z() || newpoint.z() <= end.z() ||  result.size()>250)
		{
			break;
		}
		result.push_back(newpoint);
		currentpoint = newpoint;
	}
	return result;
}


vector<Point3D> path::findpath(Triangulation& terrain)
{
	Point3D highestpoint = findHighestPoint(terrain);

	vector<Point3D> answer = generatepath(highestpoint, terrain);
	STLWriter writer;
	string filepath = "waterpath.txt";
	writer.writevectorToFile(filepath, answer);

	return answer;


}