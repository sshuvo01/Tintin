#ifndef HITABLE_H
#define HITABLE_H
#include "Ray.h"

namespace tintin
{
	class Material;

	struct HitRecord
	{
		double t;
		lux::Vector position, normal;
		Material* material;
	};

	class Hitable
	{
	public:
		Hitable() : m_Material(nullptr) {}
		Hitable(Material* mat) : m_Material(mat) {}
		virtual bool Hit(const Ray& r, double tMin, double tMax, HitRecord& rec) const = 0;
	protected:
		Material* m_Material;
	};

}

#endif // !HITABLE_H
