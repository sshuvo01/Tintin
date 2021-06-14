#include "Sphere.h"

namespace tintin
{
	bool Sphere::Hit(const tintin::Ray & r, double tMin, double tMax, HitRecord & rec) const
	{
		lux::Vector AmC = r.GetOrigin() - m_Center;
		lux::Vector B = r.GetDirection();
		double a = B * B;
		double b = B * AmC;
		double c = AmC * AmC - m_Radius * m_Radius;
		double discriminant = b * b - a * c;
		
		if (discriminant > 0.0)
		{
			double temp = (-b - std::sqrt(b * b - a * c)) / a;
			if (temp < tMax && temp > tMin)
			{
				rec.t = temp;
				rec.position = r.GetPointAt(rec.t);
				rec.normal = (rec.position - m_Center) / m_Radius;
				rec.material = m_Material;
				return true;
			}
			temp = (-b + std::sqrt(b * b - a * c)) / a;
			if (temp < tMax && temp > tMin)
			{
				rec.t = temp;
				rec.position = r.GetPointAt(rec.t);
				rec.normal = (rec.position - m_Center) / m_Radius;
				rec.material = m_Material;
				return true;
			}
		}
		
		return false;
	}
}

