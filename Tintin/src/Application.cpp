#include <iostream>
#include <fstream>
#include <limits>
#include <random>
#include "Vector.h"
#include "Ray.h"
#include "Hitable.h"
#include "HitableList.h"
#include "Sphere.h"
#include "Camera.h"
#include "Reflections.h"

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_real_distribution<> dis(0.0, 0.99999);

static double drand49()
{
	return dis(gen);
}

static lux::Vector Color(const tintin::Ray& r) 
{
	lux::Vector unitDir = r.GetDirection().unitvector();
	double t = 0.5 * (unitDir.Y() + 1.0);
	return (1.0 - t) * lux::Vector(1.0, 1.0, 1.0) + t * lux::Vector(0.5, 0.7, 1.0);
}

static bool HitSphere(const lux::Vector& center, double radius, const tintin::Ray& r)
{
	lux::Vector AmC = r.GetOrigin() - center;
	lux::Vector B = r.GetDirection();
	double a = B * B;
	double b = 2.0 * B * AmC;
	double c = AmC * AmC - radius * radius;
	double discriminant = b * b - 4.0 * a * c;
	
	return discriminant > 0;
}

static lux::Vector Color2(const tintin::Ray& r)
{
	if (HitSphere(lux::Vector(0.0, 0.0, 1.0), 0.5, r))
	{
		return lux::Vector(1.0, 0.0, 0.0);
	}
	lux::Vector unitDir = r.GetDirection().unitvector();
	double t = 0.5 * (unitDir.Y() + 1.0);
	return (1.0 - t) * lux::Vector(1.0, 1.0, 1.0) + t * lux::Vector(0.5, 0.7, 1.0);
}

static double HitSphere2(const lux::Vector& center, double radius, const tintin::Ray& r)
{
	lux::Vector AmC = r.GetOrigin() - center;
	lux::Vector B = r.GetDirection();
	double a = B * B;
	double b = 2.0 * B * AmC;
	double c = AmC * AmC - radius * radius;
	double discriminant = b * b - 4.0 * a * c;

	if (discriminant < 0.0)
	{
		return -1.0;
	}
	else
	{
		return (-b - discriminant) / (2.0 * a);
	}
}

static lux::Vector Color3(const tintin::Ray& r)
{
	lux::Vector center(0.0, 0.0, -1.0);
	double t = HitSphere2(center, 0.5, r);
	if (t > 0.0)
	{
		lux::Vector hitPos = r.GetPointAt(t);
		lux::Vector N = hitPos - center;
		return 0.5 * lux::Vector(N.X() + 1.0, N.Y() + 1.0, N.Z() + 1.0);
	}
	lux::Vector unitDir = r.GetDirection().unitvector();
	t = 0.5 * (unitDir.Y() + 1.0);
	return (1.0 - t) * lux::Vector(1.0, 1.0, 1.0) + t * lux::Vector(0.5, 0.7, 1.0);
}


static lux::Vector Color4(const tintin::Ray& r, tintin::Hitable* world)
{
	tintin::HitRecord rec;
	if (world->Hit(r, 0.0, std::numeric_limits<double>::max(), rec))
	{
		return 0.5 * lux::Vector(rec.normal.X() + 1.0, rec.normal.Y() + 1.0, rec.normal.Z() + 1.0);
	}
	else
	{
		lux::Vector unitDir = r.GetDirection().unitvector();
		double t = 0.5 * (unitDir.Y() + 1.0);
		return (1.0 - t) * lux::Vector(1.0, 1.0, 1.0) + t * lux::Vector(0.5, 0.7, 1.0);
	}
}

static lux::Vector RandomInUnitSphere()
{
	lux::Vector p;
	do
	{
		p = 2.0 * lux::Vector(drand49(), drand49(), drand49()) - lux::Vector(1.0, 1.0, 1.0);
	} while (p.magnitude() >= 1.0);
	return p;
}

static lux::Vector Color5(const tintin::Ray& r, const tintin::Hitable* world)
{
	tintin::HitRecord rec;
	if (world->Hit(r, 0.001, std::numeric_limits<double>::max(), rec))
	{
		lux::Vector target = rec.position + rec.normal + RandomInUnitSphere();
		return 0.5 * Color5(tintin::Ray(rec.position, target - rec.position), world);
	}
	else
	{
		lux::Vector unitDir = r.GetDirection().unitvector();
		double t = 0.5 * (unitDir.Y() + 1.0);
		return (1.0 - t) * lux::Vector(1.0, 1.0, 1.0) + t * lux::Vector(0.5, 0.7, 1.0);
	}
}

static lux::Vector Color6(const tintin::Ray& r, const tintin::Hitable* world, int depth)
{
	tintin::HitRecord rec;
	if (world->Hit(r, 0.001, std::numeric_limits<double>::max(), rec))
	{
		lux::Vector attenuation;
		tintin::Ray scattered;
		if (depth < 50 && rec.material->Scatter(r, rec, attenuation, scattered))
		{
			return lux::Vector::CompWiseMult(attenuation, Color6(scattered, world, depth + 1));
		}
		else
		{
			return lux::Vector(0.0);
		}
	}
	else
	{
		lux::Vector unitDir = r.GetDirection().unitvector();
		double t = 0.5 * (unitDir.Y() + 1.0);
		return (1.0 - t) * lux::Vector(1.0, 1.0, 1.0) + t * lux::Vector(0.5, 0.7, 1.0);
	}
}

int main()
{
	//int nx = 200, ny = 100;

	std::ofstream file("res/test11.ppm");

	if (!file.is_open())
	{
		std::cout << "Failed to open the output file\n";
		exit(-1);
	}

	int nx = 200, ny = 100, ns = 100;
	file << "P3\n" << nx << " " << ny << "\n255\n";
	
	lux::Vector llc(-2.0, -1.0, -1.0);
	lux::Vector horizontal(4.0, 0.0, 0.0);
	lux::Vector vertical(0.0, 2.0, 0.0);
	lux::Vector origin(0.0, 0.0, 0.0);

	tintin::Hitable* list[4];
	list[0] = new tintin::Sphere(lux::Vector(0.0, 0.0, -1.0), 0.5, 
		new tintin::Lambertian(lux::Vector(0.8, 0.3, 0.3)));
	list[1] = new tintin::Sphere(lux::Vector(0.0, -100.5, -1.0), 100.0,
		new tintin::Lambertian(lux::Vector(0.8, 0.8, 0.0)));
	list[2] = new tintin::Sphere(lux::Vector(1.0, 0.0, -1.0), 0.5,
		new tintin::Metal(lux::Vector(0.8, 0.6, 0.2)));
	list[3] = new tintin::Sphere(lux::Vector(-1.0, 0.0, -1.0), 0.5,
		new tintin::Metal(lux::Vector(0.8, 0.8, 0.8)));

	//list[1] = new tintin::Sphere(lux::Vector(0.0, -100.5, -1.0), 100.0);
	tintin::Hitable* world = new tintin::HitableList(list, 4);
	
	tintin::Camera cam;

	for (int j = ny - 1; j >= 0; j--)
	{
		for (int i = 0; i < nx; i++)
		{
			lux::Vector col(0.0, 0.0, 0.0);
			for (int k = 0; k < ns; k++)
			{
				double u = double(i + drand49()) / double(nx);
				double v = double(j + drand49()) / double(ny);
				//tintin::Ray r(origin, llc + u * horizontal + v * vertical);
				tintin::Ray r = cam.GetRay(u, v);
				col += Color6(r, world, 0);
			}
			col /= ns;

			int ir = int(255.99 * std::sqrt(col.X()));
			int ig = int(255.99 * std::sqrt(col.Y()));
			int ib = int(255.99 * std::sqrt(col.Z()));

			file << ir << " " << ig << " " << ib << "\n";
		}
	}

	file.close();
	std::cout << "Done!\n";
	std::cin.get();
	return 0;
}

int main2()
{
	lux::Vector bla1;
	lux::Vector bla2;
	tintin::Ray a(bla1, bla2);
	

	std::cout << "what\n";
	std::cin.get();
	std::cin.get();
	std::cin.get();

	std::ofstream file("res/test.ppm");
	
	if (!file.is_open())
	{
		std::cout << "Failed to open the output file\n";
		exit(-1);
	}
	
	int nx = 200, ny = 100;
	file << "P3\n" << nx << " " << ny << "\n255\n";
	for (int j = ny - 1; j >= 0; j--)
	{
		for (int i = 0; i < nx; i++)
		{
			double r = double(i) / double(nx);
			double g = double(j) / double(ny);
			double b = 0.2;
			int ir = int(255.99 * r);
			int ig = int(255.99 * g);
			int ib = int(255.99 * b);
			file << ir << " " << ig << " " << ib << "\n";
		}
	}


	file.close();
	std::cout << "Done!\n";
	std::cin.get();
	return 0;
}