#ifndef HELPER_H
#define HELPER_H
#include <vector>
#include <random>
namespace Rng{
  extern std::random_device rd;
  extern std::mt19937 mt;
  int randInt(int ll, int ul);
}

//-----------------------------------------------------------------------------
// Geometry
//-----------------------------------------------------------------------------
class P
{
public:
    P() :
        x(0),
        y(0) {}

    P(const int x, const int y) :
        x(x),
        y(y) {}

    P(const P& p) :
        x(p.x),
        y(p.y) {}

    P(const int v) :
        x(v),
        y(v) {}

    P& operator=(const P& p)
    {
        x = p.x;
        y = p.y;
        return *this;
    }

    P& operator/=(const int v)
    {
        x /= v;
        y /= v;
        return *this;
    }

    P& operator+=(const P& p)
    {
        x += p.x;
        y += p.y;
        return *this;
    }

    P& operator-=(const P& p)
    {
        x -= p.x;
        y -= p.y;
        return *this;
    }

    P& operator++()
    {
        ++x;
        ++y;
        return *this;
    }

    P& operator--()
    {
        --x;
        --y;
        return *this;
    }

    P operator+(const P& p) const
    {
        return P(x + p.x, y + p.y);
    }

    P operator+(const int  v) const
    {
        return P(x + v, y + v);
    }

    P operator-(const P& p) const
    {
        return P(x - p.x, y - p.y);
    }

    P operator-(const int v) const
    {
        return P(x - v, y - v);
    }

    P operator/(const int  v) const
    {
        return P(x / v, y / v);
    }

    P operator/(const P& p) const
    {
        return P(x / p.x, y / p.y);
    }

    P operator*(const int v) const
    {
        return P(x * v, y * v);
    }

    P operator*(const P& p) const
    {
        return P(x * p.x, y * p.y);
    }

    bool operator==(const P& p) const
    {
        return x == p.x && y == p.y;
    }

    bool operator!=(const P& p) const
    {
        return x != p.x || y != p.y;
    }

    bool operator!=(const int v) const
    {
        return x != v || y != v;
    }

    bool operator>(const P& p) const
    {
        return x > p.x && y > p.y;
    }

    bool operator>(const int v) const
    {
        return x > v && y > v;
    }

    bool operator<(const P& p) const
    {
        return x < p.x && y < p.y;
    }

    bool operator<(const int v) const
    {
        return x < v && y < v;
    }

    bool operator>=(const P& p) const
    {
        return x >= p.x && y >= p.y;
    }

    bool operator>=(const int v) const
    {
        return x >= v && y >= v;
    }

    bool operator<=(const P& p) const
    {
        return x <= p.x && y <= p.y;
    }

    bool operator<=(const int  v) const
    {
        return x <= v && y <= v;
    }

    P signs() const
    {
        return P(x == 0 ? 0 : x > 0 ? 1 : -1,
                 y == 0 ? 0 : y > 0 ? 1 : -1);
    }

    void set(const int x_, const int y_)
    {
        x = x_;
        y = y_;
    }

    void set(const P& p)
    {
        x = p.x;
        y = p.y;
    }

    void swap(P& p)
    {
        P tmp(p);
        p = *this; set(tmp);
    }

    int x, y;
};

class R
{
public:
    R() :
        p0(P()),
        p1(P()) {}

    R(const P& p0, const P& p1) :
        p0(p0),
        p1(p1) {}

    R(const int x0, const int y0, const int x1, const int y1) :
        p0(P(x0, y0)),
        p1(P(x1, y1)) {}

    R(const R& r) :
        p0(r.p0),
        p1(r.p1) {}

    int w() const
    {
        return p1.x - p0.x + 1;
    }

    int h() const
    {
        return p1.y - p0.y + 1;
    }

    P dims() const
    {
        return P(w(), h());
    }

    int min_dim() const
    {
        return std::min(w(), h());
    }

    int max_dim() const
    {
        return std::max(w(), h());
    }

    P center() const
    {
        return ((p1 + p0) / 2);
    }
    
    P randPoint() const
    {
      return (P(Rng::randInt(p0.x,p1.x), Rng::randInt(p0.y,p1.y)));
    }

    bool is_p_inside(const P& p) const
    {
        return p >= p0 &&
               p <= p1;
    }

    R& operator+=(const P& p)
    {
        p0 += p;
        p1 += p;
        return *this;
    }

    R& operator-=(const P& p)
    {
        p0 -= p;
        p1 -= p;
        return *this;
    }

    // Useful for e.g. converting map cell dimensions to pixel dimensions
    R operator*(const P& p)
    {
        return R(p0 * p, p1 * p);
    }

    P p0;
    P p1;
};

#endif
