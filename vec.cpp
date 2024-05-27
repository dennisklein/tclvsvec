#include "MyPoint.h"

#include <iostream>
#include <vector>

int main() {
  constexpr auto numPoints = 100000;
  std::vector<MyPoint> points;
  points.reserve(numPoints);
  for (int i = 0; i < numPoints; ++i) {
    points.emplace_back(i, i, i);
  }

  for (auto& point : points) {
    std::cout << point.x << ", " << point.y << ", " << point.z << "\n";
  }
}
