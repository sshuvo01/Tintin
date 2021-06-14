#include "Reflections.h"

namespace tintin          
{
	/*Lambertian*/
	bool Lambertian::Scatter(const Ray & rayIn, const HitRecord & rec, 
		lux::Vector & attenuation, Ray & rayScattered) const
	{
		lux::Vector target = rec.position + rec.normal + RandomInUnitSphere();
		rayScattered = Ray(rec.position, target - rec.position);
		attenuation = m_Albedo;
		return true;
	}

	const lux::Vector Lambertian::RandomInUnitSphere() const
	{
		lux::Vector p;
		do
		{
			p = 2.0 * lux::Vector(drand49(), drand49(), drand49()) - lux::Vector(1.0, 1.0, 1.0);
		} while (p.magnitude() >= 1.0);
		return p;
	}
	/*Metal*/
	bool Metal::Scatter(const Ray & rayIn, const HitRecord & rec, lux::Vector & attenuation, Ray & rayScattered) const
	{
		lux::Vector reflected = Reflect(rayIn.GetDirection().unitvector(), rec.normal);
		rayScattered = Ray(rec.position, reflected);
		attenuation = m_Albedo;
		return (rayScattered.GetDirection() * rec.normal) > 0.0;
	}
}