#include "Camera.h"

namespace tintin
{
	
	Camera::Camera()
		:m_Origin(0.0, 0.0, 0.0), 
		m_LLC(-2.0, -1.0, -1.0), 
		m_Horizontal(4.0, 0.0, 0.0),
		m_Vertical(0.0, 2.0, 0.0)
	{
	}
	/*
	Camera::Camera(const lux::Vector & origin, const lux::Vector & llc, 
		const lux::Vector & horizontal, const lux::Vector & vertical)
		:m_Origin(origin),
		m_LLC(llc),
		m_Horizontal(horizontal),
		m_Vertical(vertical)
	{
	}
	*/

	Camera::Camera(const lux::Vector & origin, const lux::Vector & lookAt, const lux::Vector & vup, 
		double vFOV, double aspectRatio, double aperture, double focusDistance)
		: m_Origin(origin)
	{
		m_LensRadius = aperture / 2.0;
		const double PI = 3.1416;
		//lux::Vector m_U, m_V, m_Ww;
		double theta = vFOV * PI / 180.0;
		double halfHeight = std::tan(theta / 2.0);
		double halfWidth = aspectRatio * halfHeight;
		m_W = (m_Origin - lookAt).unitvector();
		m_U = (vup ^ m_W).unitvector();
		m_V = m_W ^ m_U;
		m_LLC = m_Origin - halfWidth * focusDistance * m_U - halfHeight * focusDistance * m_V - 
			focusDistance * m_W;
		m_Horizontal = 2.0 * halfWidth * focusDistance * m_U;
		m_Vertical = 2.0 * halfHeight * focusDistance * m_V;
	}

	const Ray Camera::GetRay(double s, double t) const
	{
		lux::Vector rd = m_LensRadius * RandomInUnitDisk();
		lux::Vector offset = m_U * rd.X() + m_V * rd.Y();
		return Ray(m_Origin + offset, m_LLC + s * m_Horizontal + t * m_Vertical - m_Origin - offset);
	}

}