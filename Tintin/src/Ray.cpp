#include "Ray.h"
#include <iostream>

namespace tintin
{
	Ray::Ray() {}

	Ray::Ray(ConstVec& A, ConstVec& B)
		: m_A(A), m_B(B)
	{
		//std::cout << "lalalalal\n";
	}

	Ray::~Ray() {}

	ConstVec Ray::GetPointAt(double t) const
	{
		return m_A + t * m_B;
	}
}
