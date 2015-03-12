/////////////////////////////////////////////////////////////////////////////////////////
//	BOVIL: core
//
//		Author: Pablo Ramon Soria
//		Date:	2014-05-03
//
/////////////////////////////////////////////////////////////////////////////////////////

#ifndef COLORS_H_
#define COLORS_H_

namespace BOViL{
	// ----- Traits -----		666 TODO: hacer con constexpr cuando salga para el compilador de vs
	template <typename T> struct ColorTypeInfo{

	};

	template <> struct ColorTypeInfo<unsigned char>{
		static unsigned char getMAX(){ return 255; };
		static unsigned char getMIN(){ return 0; };
	};

	template <> struct ColorTypeInfo<float>{
		static float getMAX(){ return 1.0f; };
		static float getMIN(){ return 0.0f; };
	};

	// ----- Types and structures -----
	template<typename T_> struct color3 {
			color3(){
				a = b = c = T_(0);
			};

			color3(T_ _a, T_ _b, T_ _c){
				a = _a; b = _b; c = _c;
			};
			
			T_ a, b, c;
		};

	typedef color3<unsigned char> c3u;
	typedef color3<float> c3f;
	typedef color3<double> c3d;


	// ----- Functions -----
	template<typename T> color3<T> PixelRGB2HSV(const color3<T> &_color){
		color3<T> HSV;
		T MAX, MIN;

		_color.a > _color.b ? (_color.a > _color.c ? MAX = _color.a : MAX = _color.c) : (_color.b > _color.c ? MAX = _color.b : MAX = _color.c);
		_color.a < _color.b ? (_color.a < _color.c ? MIN = _color.a : MIN = _color.c) : (_color.b < _color.c ? MIN = _color.b : MIN = _color.c);
	
		if(MAX == MIN)
			HSV.a = 0;
		else if (_color.a == MAX && _color.b >= _color.c)
			HSV.a = (60*(_color.b - _color.c)/(MAX - MIN) + 0)/360 * ColorTypeInfo<T>::getMAX();
		else if (_color.a == MAX && _color.b < _color.c)
			HSV.a = (60*(_color.b - _color.c)/(MAX - MIN) + 360)/360 * ColorTypeInfo<T>::getMAX();
		else if (_color.b == MAX)
			HSV.a = (60*(_color.c - _color.a)/(MAX - MIN) + 120)/360 * ColorTypeInfo<T>::getMAX();
		else if (_color.c == MAX)
			HSV.a = (60*(_color.a - _color.b)/(MAX - MIN) + 240)/360 * ColorTypeInfo<T>::getMAX();


		MAX == 0 ? HSV.b = 0 : HSV.b = (1 - MIN/MAX) * ColorTypeInfo<T>::getMAX();
		
		HSV.c = MAX;
		
		return HSV;
	}
}	// namespace BOViL


#endif	//_BOVIL_COLORS_H_