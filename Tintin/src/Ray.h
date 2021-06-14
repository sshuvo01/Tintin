#pragma once
#include "Vector.h"

namespace tintin
{
	using ConstVec = const lux::Vector;
	class Ray
	{
	public:
		Ray();
		Ray(ConstVec& A, ConstVec& B);
		~Ray();

		inline ConstVec GetOrigin() const { return m_A; }
		inline ConstVec GetDirection() const { return m_B; }
		ConstVec GetPointAt(double t) const;
	private:
		lux::Vector m_A, m_B;
	};
} 