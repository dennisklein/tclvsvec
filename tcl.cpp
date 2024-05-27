#include "MyPoint.h"

#include <TClonesArray.h>
#include <TCollection.h>
#include <iostream>

int main() {
  constexpr auto numPoints = 100000;
  TClonesArray points("MyPoint", numPoints);
  for (int i = 0; i < numPoints; ++i) {
    new (points[i]) MyPoint(i, i, i);
  }

  for (auto point : TRangeDynCast<MyPoint>(points)) {
    std::cout << point->x << ", " << point->y << ", " << point->z << "\n";
  }
}
