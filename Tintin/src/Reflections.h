#ifndef REFLECTIONS_H
#define REFLECTIONS_H
#include "Helper.h"
#include "Ray.h"
#include "Hitable.h"

namespace tintin
{
	class Material
	{
	public:
		Material() {}
		~Material() {}

		virtual bool Scatter(const Ray& rayIn, const HitRecord& rec, 
			lux::Vector& attenuation, Ray& rayScattered) const = 0;
	};
	/*-------------------Lambertian-------------------*/
	class Lambertian : public Material
	{
	public:
		Lambertian(const lux::Vector& albedo) : m_Albedo(albedo) {}
		~Lambertian() {}
		bool Scatter(const Ray& rayIn, const HitRecord& rec,
			lux::Vector& attenuation, Ray& rayScattered) const override;
	private:
		lux::Vector m_Albedo;
		/*private functions*/
		const lux::Vector RandomInUnitSphere() const;
	};
	/*-------------------Metal-------------------*/
	class Metal : public Material
	{
	public:
		Metal(const lux::Vector& albedo, double fuzz);
		~Metal() {}

		bool Scatter(const Ray& rayIn, const HitRecord& rec,
			lux::Vector& attenuation, Ray& rayScattered) const override;
	private:
		lux::Vector m_Albedo;
		double m_Fuzz;
	};
	/*-------------------Dielectric-------------------*/
	class Dielectric : public Material
	{
	public:
		Dielectric(double refractiveIndex);
		~Dielectric() {}

		bool Scatter(const Ray& rayIn, const HitRecord& rec,
			lux::Vector& attenuation, Ray& rayScattered) const override;
	private:
		double m_RefractiveIndex;
	};

}

#endif // !REFLECTIONS_H
