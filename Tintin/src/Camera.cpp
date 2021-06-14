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

	Camera::Camera(const lux::Vector & origin, const lux::Vector & llc, 
		const lux::Vector & horizontal, const lux::Vector & vertical)
		:m_Origin(origin),
		m_LLC(llc),
		m_Horizontal(horizontal),
		m_Vertical(vertical)
	{
	}

	const Ray Camera::GetRay(double u, double v) const
	{
		return Ray(m_Origin, m_LLC + u * m_Horizontal + v * m_Vertical - m_Origin);
	}

}