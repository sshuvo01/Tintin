#ifndef CAMERA_H
#define CAMERA_H
#include "Ray.h"

namespace tintin
{
	class Camera
	{
	public:
		Camera();
		Camera(const lux::Vector& origin, const lux::Vector& llc,
			const lux::Vector& horizontal, const lux::Vector& vertical);
		~Camera() {}

		const Ray GetRay(double u, double v) const;
	private:
		lux::Vector m_Origin, m_LLC, m_Horizontal, m_Vertical;
	};
}

#endif // !CAMERA_H
