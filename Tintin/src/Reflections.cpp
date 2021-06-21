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
	Metal::Metal(const lux::Vector & albedo, double fuzz)
		:m_Albedo(albedo)
	{
		if (fuzz < 1.0)
		{
			m_Fuzz = fuzz;
		}
		else
		{
			m_Fuzz = 1.0;
		}
	}

	bool Metal::Scatter(const Ray & rayIn, const HitRecord & rec, lux::Vector & attenuation, Ray & rayScattered) const
	{
		lux::Vector reflected = Reflect(rayIn.GetDirection().unitvector(), rec.normal);
		//rayScattered = Ray(rec.position, reflected);
		rayScattered = Ray(rec.position, reflected + m_Fuzz * RandomInUnitSphere());
		attenuation = m_Albedo;
		return (rayScattered.GetDirection() * rec.normal) > 0.0;
	}
	/*Dielectric*/
	Dielectric::Dielectric(double refractiveIndex)
		:m_RefractiveIndex(refractiveIndex)
	{
	}

	bool Dielectric::Scatter(const Ray & rayIn, const HitRecord & rec, lux::Vector & attenuation, Ray & rayScattered) const
	{
		lux::Vector outwardNormal;
		lux::Vector reflected = Reflect(rayIn.GetDirection(), rec.normal);
		double niOverNt;
		attenuation = lux::Vector(1.0, 1.0, 1.0);
		lux::Vector refracted;
		double reflectProb;
		double cosine;
		if ((rayIn.GetDirection() * rec.normal) > 0.0) 
		{
			outwardNormal = -rec.normal;
			niOverNt = m_RefractiveIndex;
			cosine = m_RefractiveIndex * (rayIn.GetDirection() * rec.normal) / 
				rayIn.GetDirection().magnitude();
		}
		else
		{
			outwardNormal = rec.normal;
			niOverNt = 1.0 / m_RefractiveIndex;
			cosine = -(rayIn.GetDirection() * rec.normal) / rayIn.GetDirection().magnitude();
		}
		if (Refract(rayIn.GetDirection(), outwardNormal, niOverNt, refracted))
		{
			reflectProb = Schlick(cosine, m_RefractiveIndex);
		}
		else
		{
			rayScattered = Ray(rec.position, reflected);
			reflectProb = 1.0;
		}
		if (drand49() < reflectProb)
		{
			rayScattered = Ray(rec.position, reflected);
		}
		else
		{
			rayScattered = Ray(rec.position, refracted);
		}

		return true;
	}
}