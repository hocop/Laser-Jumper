#include "vec2.hpp"


std::ostream& operator<<(std::ostream& os, const Vec2& vec)
{
    os << "Vec2(" << vec.x << ", " << vec.y << ")";
    return os;
}

void Vec2::print() const
{
    std::cout << *this << std::endl;
}

sf::Vector2f Vec2::as_sf() const
{
    return sf::Vector2f(x, y);
}

double Vec2::norm() const
{
    return sqrt(norm2());
}
double Vec2::norm2() const
{
    return *this * *this;
}

Vec2 Vec2::unit() const
{
    double l = norm();

    if (l == 0)
        return Vec2(0, 0);

    return Vec2(x / l, y / l);
}

Vec2 Vec2::rotate(double angle) const
{
    Vec2 row1(cos(angle), -sin(angle));
    Vec2 row2 = row1.rot90();
    return Vec2(*this * row1, *this * row2);
}

Vec2 Vec2::rot90() const
{
    return Vec2(-y, x);
}

Vec2 Vec2::operator+ (Vec2 const& obj) const
{
    return Vec2(x + obj.x, y + obj.y);
}
Vec2& Vec2::operator+= (Vec2 const& obj)
{
    x += obj.x;
    y += obj.y;
    return *this;
}

Vec2 Vec2::operator- (Vec2 const& obj) const
{
    return Vec2(x - obj.x, y - obj.y);
}
Vec2& Vec2::operator-= (Vec2 const& obj)
{
    x -= obj.x;
    y -= obj.y;
    return *this;
}
Vec2 Vec2::operator- () const
{
    return Vec2(-x, -y);
}

double Vec2::operator* (Vec2 const& obj) const
{
    return x * obj.x + y * obj.y;
}

Vec2 Vec2::operator* (const double& scalar) const
{
    return Vec2(x * scalar, y * scalar);
}
Vec2 operator* (const double& scalar, const Vec2& obj)
{
    return Vec2(obj.x * scalar, obj.y * scalar);
}
Vec2& Vec2::operator*= (const double& scalar)
{
    x *= scalar;
    y *= scalar;
    return *this;
}

Vec2 Vec2::operator/ (const double& scalar) const
{
    return Vec2(x / scalar, y / scalar);
}
Vec2& Vec2::operator/= (const double& scalar)
{
    x /= scalar;
    y /= scalar;
    return *this;
}