const double PI = acos(-1.0);
const double EPS = 1e-9; 

typedef double TI;

int sign(double x) { return (x > EPS) - (x < -EPS); }
int sign(long long x) { return (x > 0) - (x < 0); }

struct Point {
    TI x, y;
    Point() : x(0), y(0) {}
    Point(TI x, TI y) : x(x), y(y) {}
    Point(const Point &a) : x(a.x), y(a.y) {}
    
    Point operator + (const Point &a) const { return Point(x + a.x, y + a.y); }
    Point operator - (const Point &a) const { return Point(x - a.x, y - a.y); }
    Point operator * (const TI &a) const { return Point(x * a, y * a); }
    Point operator / (const TI &a) const { return Point(x / a, y / a); }

    bool operator == (const Point &a) const { return sign(x - a.x) == 0 && sign(y - a.y) == 0; }
    bool operator != (const Point &a) const { return !(*this == a); }
    bool operator < (Point a) const { return sign(a.x - x) == 0 ? y < a.y : x < a.x; }
    bool operator > (Point a) const { return sign(a.x - x) == 0 ? y > a.y : x > a.x; }

    friend istream &operator >> (istream &is, Point &p) { return is >> p.x >> p.y; }
    friend ostream &operator << (ostream &os, const Point &p) { return os << p.x << " " << p.y; }
};


inline TI dot(Point a, Point b) { return a.x * b.x + a.y * b.y; }
inline TI cross(Point a, Point b) { return a.x * b.y - a.y * b.x; }
inline TI cross(Point a, Point b, Point c) { return cross(b - a, c - a); }
inline double dist(Point a, Point b) { return sqrt(dot(a - b, a - b)); }
inline double dist2(Point a, Point b) { return dot(a - b, a - b); }

Point rotateccw90(Point a) { return Point(-a.y, a.x); }
Point rotatecw90(Point a) { return Point(a.y, -a.x); }
Point rotateccw(Point a, double t) { return Point(a.x * cos(t) - a.y * sin(t), a.x * sin(t) + a.y * cos(t)); }
Point rotatecw(Point a, double t) { return Point(a.x * cos(t) + a.y * sin(t), -a.x * sin(t) + a.y * cos(t)); }

bool is_point_in_segment(Point a, Point b, Point p) {
    return sign(cross(a, b, p)) == 0 && sign(dot(a - p, b - p)) <= 0;
}

// 0 -> no intersection, 1 -> unique intersection, 2 -> infinite intersection
int seg_seg_intersection(Point a, Point b, Point c, Point d) {
    TI oa = cross(c, d, a);
    TI ob = cross(c, d, b);
    TI oc = cross(a, b, c);
    TI od = cross(a, b, d);

    if (sign(oa) == 0 && sign(ob) == 0 && sign(oc) == 0 && sign(od) == 0) {
        if (b < a) swap(a, b);
        if (d < c) swap(c, d);
        Point L = max(a, c);
        Point R = min(b, d);

        if (R < L) return 0;
        if (L == R) return 1;
        return 2;
    }
    
    if (sign(oa) * sign(ob) <= 0 && sign(oc) * sign(od) <= 0) return 1;
    return 0;
}

// intersection point between ab and cd assuming unique intersection exists
bool line_line_intersection(Point a, Point b, Point c, Point d, Point &ans) {
    double a1 = a.y - b.y, b1 = b.x - a.x, c1 = cross(a, b);
    double a2 = c.y - d.y, b2 = d.x - c.x, c2 = cross(c, d);
    double det = a1 * b2 - a2 * b1;
    if (det == 0) return 0;
    ans = Point((b1 * c2 - b2 * c1) / det, (c1 * a2 - a1 * c2) / det);
    return 1;
}

double rat(Point a, Point b, Point p) {
    return !sign(a.x - b.x) ? (p.y - a.y) / (b.y - a.y) : (p.x - a.x) / (b.x - a.x);
}
