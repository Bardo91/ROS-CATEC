/////////////////////////////////////////////////////////////////////////////////////////
//	BOVIL: core
//
//		OpenBOVIL
//			Author: Pablo Ramon Soria
//			Date:	2014-02-19
/////////////////////////////////////////////////////////////////////////////////////////
//

#ifndef BASIC_TYPES_H_
#define BASIC_TYPES_H_

namespace BOViL{
	//-----------------------------------------------------------------------------
	template<typename Type_>
	struct Vec2{
		// Constructors.
		Vec2():	x(0), y(0)	{};
		Vec2(Type_ _x, Type_ _y):	x(_x),  y(_y)	{};

		// Properties.
		Type_ x, y;		// Coordinates of the point in the image.
	};


	typedef Vec2<double>		Vec2d;
	typedef Vec2<int>			Vec2i;
	typedef Vec2<unsigned>		Vec2ui;
	typedef Vec2<unsigned char> Vec2uc;

	//-----------------------------------------------------------------------------
	template<typename Type_>
	struct Vec3{
		// Constructors.
		Vec3():	x(0), y(0), z(0)	{};

		Vec3(Type_ _x, Type_ _y, Type_ _z):	x(_x),  y(_y),	z(_z)	{};

		// Properties.
		Type_ x, y, z;		// Coordinates of the point in the image.
	};


	typedef Vec3<double>		Vec3d;
	typedef Vec3<int>			Vec3i;
	typedef Vec3<unsigned>		Vec3ui;
	typedef Vec3<unsigned char> Vec3uc;

	//-----------------------------------------------------------------------------
	class ImageObject{		// Summarized object.
	public:
		ImageObject(Vec2ui _upperLeft, Vec2ui _downRight, int _size, int _color){
			centroid = Vec2ui((_upperLeft.x + _downRight.x)/2, (_upperLeft.y + _downRight.y)/2);
			width = _downRight.x - _upperLeft.x;
			height = _downRight.y - _upperLeft.y;
			size = _size;
			color = _color;
		};
			
		Vec2ui getCentroid() const {return centroid;};
		int getWidth() const {return width;};
		int getHeight() const {return height;};
		int getColor() const {return color;};
		int getSize() const {return size;};
	private:
		Vec2ui centroid;
		int width, height;
		int color;
		int size;
	};

}	// namespace BOViL


#endif	//_BOVIL_CORE_TYPES_BASICTYPES_H_