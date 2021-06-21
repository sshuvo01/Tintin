#ifndef HELPER_H
#define HELPER_H
#include <random>
#include "Vector.h"

namespace tintin
{
	static std::random_device rd01;
	static std::mt19937 gen01(rd01());
	static std::uniform_real_distribution<> dis01(0.0, 0.99999);

	inline double drand49()
	{
		return dis01(gen01);
	}

	inline const lux::Vector Reflect(const lux::Vector& incoming, const lux::Vector& normal)
	{
		return incoming - 2.0 * (incoming * normal) * normal;
	}

	inline bool Refract(const lux::Vector& incoming, const lux::Vector& normal,
		double niOverNt, lux::Vector& refracted)
	{
		lux::Vector in = incoming.unitvector();
		double dt = in * normal;
		double discriminant = 1.0 - niOverNt * (1.0 - dt * dt);
		if (discriminant > 0.0)
		{
			refracted = niOverNt * (in - normal * dt) - normal * std::sqrt(discriminant);
			return true;
		}
		else
		{
			return false;
		}
	}

	inline const lux::Vector RandomInUnitSphere()
	{
		lux::Vector p;
		do
		{
			p = 2.0 * lux::Vector(drand49(), drand49(), drand49()) - lux::Vector(1.0, 1.0, 1.0);
		} while (p.magnitude() >= 1.0);
		return p;

	}

	inline const lux::Vector RandomInUnitDisk()
	{
		lux::Vector p;
		do
		{
			p = 2.0 * lux::Vector(drand49(), drand49(), 0.0) - lux::Vector(1.0, 1.0, 0.0);
		} while ((p * p) >= 1.0);
		return p;
	}

	inline double Schlick(double cosine, double refractiveIndex)
	{
		double r0 = (1.0 - refractiveIndex) / (1.0 + refractiveIndex);
		r0 = r0 * r0;
		return r0 + (1.0 - r0) * std::pow((1.0 - cosine), 5.0);
	}

}

#endif // !HELPER_H
