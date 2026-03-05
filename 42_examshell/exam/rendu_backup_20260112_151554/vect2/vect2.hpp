#pragma once

#include <iostream>
using namespace std;

class vect2 {
	private:
		int x, y;
	public:
		vect2() : x(0), y(0) {};
		vect2(int i, int j) : x(i), y(j) {};
		vect2(const vect2 &v) : x(v.x), y(v.y) {};
		vect2 &operator=(const vect2 &v) {if(*this != v){ x = v.x; y =v.y; } return *this; };

		bool operator==(const vect2 &v) const {return (x == v.x && y == v.y);};
		bool operator!=(const vect2 &v) const {return !(x == v.x && y == v.y);};

		friend ostream &operator<<(ostream &os, const vect2 &v) {return os << "{" << v.x << ", " << v.y << "}";}

		int operator[](int i) const {return (i == 0 ? x : y );};
		int &operator[](int i) {return (i == 0 ? x : y );};

		vect2 operator++(int) {vect2 tmp = *this; x++; y++; return tmp;};
		vect2 &operator++() {x++; y++; return *this; };
		vect2 &operator+=(const vect2 &v) {x+=v.x; y+=v.y; return *this;}
		vect2 operator+(const vect2 &v) const {return vect2(x + v.x, y + v.y);}
		
		vect2 operator--(int) {vect2 tmp = *this; x--; y--; return tmp;};
		vect2 &operator--() {x--; y--; return *this; };
		vect2 &operator-=(const vect2 &v) {x-=v.x; y-=v.y; return *this;}
		vect2 operator-(const vect2 &v) const {return vect2(x - v.x, y - v.y);}

		vect2 operator-() const {return vect2(-x, -y);}

		vect2 operator*(int s) const{return vect2(x * s, y*s);}
		friend vect2 operator*(int s, const vect2 &v) {return vect2(v.x * s, v.y*s);}
		vect2 operator*=(int s) {x*=s; y*=s; return *this; }

	};