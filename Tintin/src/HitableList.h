#ifndef HITABLELIST_H
#define HITABLELIST_H
#include "Hitable.h"
#include "Ray.h"

namespace tintin 
{
	class HitableList : public Hitable
	{
	public:
		HitableList() {}
		HitableList(Hitable** list, int size) : m_List(list), m_ListSize(size) {}
		~HitableList() {}

		bool Hit(const Ray& r, double tMin, double tMax, HitRecord& rec) const override;
	private:
		Hitable** m_List;
		int m_ListSize;
	};

}

#endif // !HITABLELIST_H

