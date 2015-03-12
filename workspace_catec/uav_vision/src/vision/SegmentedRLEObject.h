/////////////////////////////////////////////////////////////////////////////////////////
//	BOVIL: segmentation
//
//		Author: Pablo Ramón Soria
//		Date:	2014-02-19
//
/////////////////////////////////////////////////////////////////////////////////////////


#ifndef SEGMENTATION_H_
#define SEGMENTATION_H_

#include <vector>
#include "BasicTypes.h"

namespace BOViL{
	namespace algorithms{
		//-----------------------------------------------------------------------------
			struct LineRLE{		// RLE encoding object.
				LineRLE(unsigned int _i,
						unsigned int _js,
						unsigned int _je,
						int _color){
							i = _i;
							js = _js;
							je = _je;
							size = je - js;
							color = _color;
							hasParent = false;
							pi = pj = 0;
							iObj = -1;
				};

				unsigned int i;			// Row of the object.
				unsigned int js;		// Started column of the object.
				unsigned int je;		// Ended column of the object.
				unsigned int size;		// Size of the object (= je - js + 1) its computed one time in order to reduce the algorithm operations.

				int color;	// Color of the object.s

				bool hasParent;				// Flag if the RLE was parented.
				unsigned int pi;			// Index of the parent in the vector.
				unsigned int pj;			// Index of the parent in the vector.

				int iObj;

			};

		class SegmentedRLEObject {
		public:
			SegmentedRLEObject(LineRLE ini);

			void addLineObjRLE(LineRLE);
			void addRLEFamily(SegmentedRLEObject&);

			int getLines() const;
			LineRLE getRLEObj(int) const;
			Vec2ui upperLeft() const;
			Vec2ui downRight() const;
			unsigned int getColor() const;
			unsigned int getSize() const;
			unsigned int getBBSize() const;
			Vec2ui getCentroid() const;

			void sortObj();

		private:
			std::vector<LineRLE> obj;

			Vec2ui mUpperLeft, mDownRight; // Border pixels
			int color;
			unsigned int size;
		};

	}	// namespace algorithms
}	// namespace BOViL

#endif	//_BOVIL_ALGORITHM_SEGMENTATION_H_