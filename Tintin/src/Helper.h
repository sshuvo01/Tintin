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
}

#endif // !HELPER_H
