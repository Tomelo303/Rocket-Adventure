#include "Vector2.h"

Vector2::Vector2(int x, int y)
	: x(x), y(y) {}

Vector2::~Vector2()
{}

Vector2& Vector2::operator=(const int& number)
{
	x = number;
	y = number;

	return *this;
}

Vector2& Vector2::add(const Vector2& vector)
{
	x += vector.x;
	y += vector.y;

	return *this;
}

Vector2& Vector2::subtract(const Vector2& vector)
{
	x -= vector.x;
	y -= vector.y;

	return *this;
}

Vector2& operator+(Vector2& v1, const Vector2& v2)
{
	return v1.add(v2);
}

Vector2& operator-(Vector2& v1, const Vector2& v2)
{
	return v1.subtract(v2);
}

Vector2& operator*(Vector2& vector, const int& number)
{
	vector.x *= number;
	vector.y *= number;

	return vector;
}

Vector2& operator+=(Vector2& v1, const Vector2& v2)
{
	return v1 + v2;
}

Vector2& operator+=(Vector2& vector, const int& number)
{
	vector.x += number;
	vector.y += number;

	return vector;
}

std::ostream& operator<<(std::ostream& out, const Vector2& vector)
{
	out << "(" << vector.x << ", " << vector.y << ")";

	return out;
}
