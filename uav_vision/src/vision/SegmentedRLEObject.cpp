/////////////////////////////////////////////////////////////////////////////////////////
//	BOVIL: segmentation
//
//		Author: Pablo Ramón Soria
//		Date:	2014-02-19
//
/////////////////////////////////////////////////////////////////////////////////////////


#include "SegmentedRLEObject.h"

#include <algorithm>    // std::sort
#include <vector>


namespace BOViL {
	namespace algorithms {
		SegmentedRLEObject::SegmentedRLEObject(LineRLE ini) {
			mUpperLeft.x = 9999;
			mDownRight.x = 0;
			mUpperLeft.y = 9999;
			mDownRight.y = 0;
			size = 0;
			color = ini.color;
			addLineObjRLE(ini);

		}

		void SegmentedRLEObject::addLineObjRLE(LineRLE aux) {
			obj.push_back(aux);

			if (mUpperLeft.y > aux.i)
				mUpperLeft.y = aux.i;
			if (mUpperLeft.x > aux.js)
				mUpperLeft.x = aux.js;
			if (mDownRight.y < aux.i)
				mDownRight.y = aux.i;
			if (mDownRight.x < aux.je)
				mDownRight.x = aux.je;
			size += aux.size + 1;
		}

		void SegmentedRLEObject::addRLEFamily(SegmentedRLEObject& family) {
			for (int k = 0; k < family.getLines(); k++) {
				LineRLE aux = family.getRLEObj(k);
				obj.push_back(aux);
				if (mUpperLeft.y > aux.i)
					mUpperLeft.y = aux.i;
				if (mUpperLeft.x > aux.js)
					mUpperLeft.x = aux.js;
				if (mDownRight.y < aux.i)
					mDownRight.y = aux.i;
				if (mDownRight.x < aux.je)
					mDownRight.x = aux.je;
				size += aux.size + 1;
			}
		}

		int SegmentedRLEObject::getLines() const {
			return obj.size();
		}

		LineRLE SegmentedRLEObject::getRLEObj(int k) const {
			return obj[k];
		}

		Vec2ui SegmentedRLEObject::upperLeft() const {
			return mUpperLeft;
		}

		Vec2ui SegmentedRLEObject::downRight() const {
			return mDownRight;
		}

		unsigned int SegmentedRLEObject::getColor() const {
			return color;
		}

		unsigned int SegmentedRLEObject::getSize() const {
			return size;
		}

		unsigned int SegmentedRLEObject::getBBSize() const {
			return (mDownRight.x - mUpperLeft.x) * (mDownRight.y - mUpperLeft.y);
		}

		Vec2ui SegmentedRLEObject::getCentroid() const {
			return Vec2ui((mUpperLeft.x + mDownRight.x)/2, (mUpperLeft.y + mDownRight.y)/2);
		}

		bool sortFunction(LineRLE a, LineRLE b) {
			return a.i < b.i || (a.i == b.i && a.je < b.js) ? true : false;
		}

		void SegmentedRLEObject::sortObj() {
			std::sort(obj.begin(), obj.end(), sortFunction);
		}
	} // namespace segmentation
} // namespace BOViL

