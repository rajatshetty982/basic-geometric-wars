#include "Vec2.h"
#include <iostream>
#include <math.h>

Vec2::Vec2(){ }

Vec2::Vec2(float x_in, float y_in)
	:x(x_in), y(y_in){}


bool Vec2::operator == (const Vec2& rhs) const
{
	return (rhs.x == x  && rhs.y == y);
}

bool Vec2::operator != (const Vec2& rhs) const
{
	
	return (rhs.x != x  && rhs.y != y);
}

Vec2 Vec2::operator + (const Vec2& rhs) const
{
	return Vec2(rhs.x+x, rhs.y+y);
}

Vec2 Vec2::operator - (const Vec2& rhs) const
{
	return Vec2(rhs.x-x, rhs.y-y);
}

Vec2 Vec2::operator / (const float val) const
{
	return Vec2(x/val, y/val);
}


Vec2 Vec2::operator * (const float val) const
{
	return Vec2(x*val, y*val);
}

void Vec2::operator += (const Vec2 &rhs)
{
	x += rhs.x;
	y += rhs.y;
}

void Vec2::operator -= (const Vec2 &rhs)
{
	x -= rhs.x;
	y -= rhs.y;
}


void Vec2::operator *= (const float val)
{
	x *= val;
	y *= val;
}

void Vec2::operator /= (const float val)
{
	x /= val;
	y /= val;
}

float Vec2::dist(const Vec2 &rhs) const
{
	float adj = rhs.x - x;
	float opp = rhs.y - y;
	float val = sqrt(opp*opp + adj*adj);
	return val;
}

// TODO!
void Vec2::normalise()
{

}
// float Vec2::length(Vec2& rhs)
// {

// }