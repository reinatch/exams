#pragma once

#include <string>
#include <iostream>

class vect2 {
    private:
        int _x, _y;
    public:
        vect2() : _x(0), _y(0) {};
        vect2(int x, int y) : _x(x), _y(y) {};
        vect2(const vect2 &v) : _x(v._x), _y(v._y) {};
        vect2 &operator=(const vect2 &v) {_x = v._x; _y = v._y; return *this;}; 
        
        int& operator[](int i) {return (i == 0 ? _x : _y);};
        int operator[](int i) const {return (i == 0 ? _x : _y);};

        vect2 operator+(const vect2 &v) const{ return (vect2(_x + v._x, _y + v._y));};
        friend vect2 operator+(int i, const vect2 &v) { return (vect2(v._x + i, v._y + i));};
        friend vect2 operator+(const vect2 &v, int i) { return (vect2(v._x + i, v._y + i));};
        vect2 operator*(int i) {_x = _x * i; _y = _y * i; return *this;};
        friend vect2 operator*(const vect2 &v, int i) { return (vect2(v._x * i, v._y * i));};
        friend vect2 operator*(int i, const vect2 &v) { return (vect2(v._x * i, v._y * i));};
        vect2 operator-(const vect2 &v) const{ return (vect2(_x - v._x, _y - v._y));};
        vect2 operator-() const{ return (vect2(-_x, -_y));};

        
        
        
        friend std::ostream &operator<<(std::ostream &os, const vect2 v) {
            os << "{" << v._x << "," << v._y << "}";
            
            return os;
        }
        
        
};