#include "HitableList.h"

namespace tintin
{
	bool HitableList::Hit(const Ray & r, double tMin, double tMax, HitRecord & rec) const
	{
		HitRecord tempRec;
		bool hitAnything = false;
		double tClosest = tMax;
		for (int i = 0; i < m_ListSize; i++)
		{
			if (m_List[i]->Hit(r, tMin, tClosest, tempRec))
			{
				hitAnything = true;
				tClosest = tempRec.t;
				rec = tempRec;
			}
		}

		return hitAnything;
	}
}