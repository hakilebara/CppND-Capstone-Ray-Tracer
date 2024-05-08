#ifndef SPHERE_H
#define SPHERE_H

struct Sphere 
{
  Sphere();
  int id;

  bool operator==(const Sphere& lhs) const
  {
    return this->id == lhs.id;
  }
};

#endif
