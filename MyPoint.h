#ifdef roottcl
#include <Rtypes.h>
#include <TObject.h>
#endif

#pragma once

#ifdef roottcl
struct MyPoint : TObject {
#else
struct MyPoint {
#endif
  int x, y, z;
  MyPoint(int x_, int y_, int z_) : x{x_}, y{y_}, z{z_} {}
#ifdef roottcl
  ClassDefOverride(MyPoint, 1);
#endif
};
