#pragma once
#include <iostream>
#include <cmath>
#include <vector>
#include <SFML/Graphics.hpp>


class Vec2
{
public:
	double x = 0;
	double y = 0;

	// Constructor to initialize Vec2 object to a 2D Zero Vector
	Vec2() = default;

	// Constructor to initialize Vec2 object to a 2D non-zero vector.
	Vec2(const double& xin, const double& yin) : x(xin), y(yin) {};

	// Copy constructor
	Vec2(const Vec2& vec) : x(vec.x), y(vec.y) {};
	Vec2(const sf::Vector2f& vec) : x(vec.x), y(vec.y) {};
	Vec2(const sf::Vector2i& vec) : x(vec.x), y(vec.y) {};
	Vec2(const sf::Vector2u& vec) : x(vec.x), y(vec.y) {};

	Vec2& operator= (Vec2 const& vec) {this->x = vec.x; this->y = vec.y; return *this;};
	Vec2& operator= (sf::Vector2f const& vec) {this->x = vec.x; this->y = vec.y; return *this;};
	Vec2& operator= (sf::Vector2i const& vec) {this->x = vec.x; this->y = vec.y; return *this;};
	Vec2& operator= (sf::Vector2u const& vec) {this->x = vec.x; this->y = vec.y; return *this;};

	// Prints Vector in (x,y) format (Cartesian Coordinates)
	void print();
	friend std::ostream& operator<<(std::ostream& as, const Vec2& obj);

	// Returns SFML sf::Vector2f representation
	sf::Vector2f as_sf();

	// Norm of the vector
	double norm();
	// Squared norm of the vector
	double norm2();

	// Unit of this vector
	Vec2 unit();

    // Rotate by radians
	Vec2 rotate (double angle);

	// Returns this vector rotated by 90 degrees
	Vec2 rot90();

	// Overloading "+" operator
	Vec2 operator+ (Vec2 const& obj);
	Vec2& operator+= (Vec2 const& obj);

	// Overloading "-" operator
	Vec2 operator- (Vec2 const& obj);
	Vec2& operator-= (Vec2 const& obj);
	Vec2 operator- ();

	// Overloading "*" operator for dot product
	double operator* (Vec2 const& obj);

    // Overloading "*" operator for multiplication by a scalar
	Vec2 operator* (const double& scalar);
	friend Vec2 operator* (const double& scalar, const Vec2& obj);
	Vec2& operator*= (const double& scalar);

    // Overloading "*" operator for dividing by a scalar
	Vec2 operator/ (const double& scalar);
	Vec2& operator/= (const double& scalar);
};