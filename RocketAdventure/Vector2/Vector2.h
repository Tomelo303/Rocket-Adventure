#ifndef VECTOR2_H
#define VECTOR2_H

#include <iostream>

class Vector2 
{
  public:
	Vector2(int x, int y);
	~Vector2();

	// Conversions
	Vector2& operator=(const int& number);

	// Operations
	Vector2& add(const Vector2& vector);
	Vector2& subtract(const Vector2& vector);

	friend Vector2& operator+(Vector2& v1, const Vector2& v2);
	friend Vector2& operator-(Vector2& v1, const Vector2& v2);
	friend Vector2& operator*(Vector2& vector, const int& number);

	friend Vector2& operator+=(Vector2& v1, const Vector2& v2);
	friend Vector2& operator+=(Vector2& vector, const int& number);

	// Output
	friend std::ostream& operator<<(std::ostream& out, const Vector2& vector);

	int x;
	int y;
};

#endif