#ifndef SPHERE_H
#define SPHERE_H
#include "Hitable.h"

namespace tintin
{
	class Sphere : public Hitable
	{
	public:
		Sphere() : m_Radius(0.0) {}
		Sphere(const lux::Vector& center, double radius, Material* mat) 
			: m_Center(center), m_Radius(radius), Hitable(mat) {}
		~Sphere() {}

		bool Hit(const tintin::Ray& r, double tMin, double tMax, HitRecord& rec) const override;
	private:
		lux::Vector m_Center;
		double m_Radius;
	};

}

#endif // !SPHERE_H

