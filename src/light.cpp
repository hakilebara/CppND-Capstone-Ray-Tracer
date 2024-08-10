#include "light.h"

Color lighting(const Material& material, const PointLight& light, const Point& point, const Vector& eyev, const Vector& normalv)
{
  Color diffuse, specular;
  // combine the surface color with the light's color/intensity
  Color effective_color = material.color * light.intensity;

  // find the direction to the light source
  Vector lightv = normalize(light.position - point);

  // compute the ambient contribution
  Color ambient = effective_color * material.ambient;

  // light_dot_normal represents the cosine of the angle between the
  // light vector and the normal vector. A negative number means the
  // light is on the other side of the surface
  double light_dot_normal = dot(lightv, normalv);
  if (light_dot_normal < 0)
  {
    diffuse = Color{0,0,0};
    specular = Color{0,0,0};
  }
  else
  {
    // compute the diffuse contribution
    diffuse = effective_color * material.diffuse * light_dot_normal;

    // reflect_dot_eye represents the cosine of the angle between the
    // reflection vector and the eye vector. A negative number means the
    // light reflects away from the eye.
    Vector reflectv = reflect(-lightv, normalv);
    double reflect_dot_eye = dot(reflectv, eyev);
    if (reflect_dot_eye <= 0)
    {
      specular = Color{0,0,0};
    }
    else
    {
      // compute the specular contribution
      double factor = std::pow(reflect_dot_eye, material.shininess);
      specular = light.intensity * material.specular * factor;
    }
  }

  // Add the three contributions together to get the final shading
  return ambient + diffuse + specular;
}
