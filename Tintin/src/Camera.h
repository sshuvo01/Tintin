#ifndef CAMERA_H
#define CAMERA_H
#include "Ray.h"
#include "Helper.h"

namespace tintin
{
	class Camera
	{
	public:
		Camera();
		//Camera(const lux::Vector& origin, const lux::Vector& llc,
			//const lux::Vector& horizontal, const lux::Vector& vertical);
		Camera(const lux::Vector& origin, const lux::Vector& lookAt, const lux::Vector& vup,
			double vFOV, double aspectRatio, double aperture, double focusDistance);
		~Camera() {}

		const Ray GetRay(double s, double t) const;
	private:
		lux::Vector m_Origin, m_LLC, m_Horizontal, m_Vertical;
		lux::Vector m_U, m_V, m_W;
		double m_LensRadius;
	};
}

#endif // !CAMERA_H
