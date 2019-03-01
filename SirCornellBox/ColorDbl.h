#pragma once

#include <iostream>

class ColorDbl{
public:
	ColorDbl();
	ColorDbl(double _r, double _g, double _b);
	ColorDbl(double _d);
	~ColorDbl();

	// Operators
	ColorDbl operator=(const double f);
	ColorDbl operator=(const float f);
	ColorDbl operator*(const float f);
	ColorDbl operator*(const ColorDbl c);
	ColorDbl operator*=(const ColorDbl c);
	ColorDbl operator+=(const float f);
	ColorDbl operator+(const ColorDbl c);
	ColorDbl operator+=(const ColorDbl c);
	ColorDbl operator/(const float f);
	ColorDbl operator/=(const float f);
	friend std::ostream& operator<<(std::ostream& os, const ColorDbl& c);

	void setColor(ColorDbl _color);
	void setColor(double _r, double _g, double _b);
	ColorDbl getColor();

	double r, g, b;
};

