

const double PI = cos(-1.0);
const double EPS = 1e-9; 

typedef long long TI;

int sign(double x) { return (x > EPS) - (x < -EPS); }
int sign(long long x) { return (x > 0) - (x < 0); }

struct Point{
    TI x, y;
    Point() : x(0), y(0) {}
    Point(TI x, TI y) : x(x), y(y) {}
    Point(const Point &a) : x(a.x), y(a.y) {}
    
    Point operator + (const Point &a) const { return Point(x + a.x, y + a.y); }
    Point operator - (const Point &a) const { return Point(x - a.x, y - a.y); }
    Point operator * (const TI &a) const { return Point(x * a, y * a); }
    Point operator / (const TI &a) const { return Point(x / a, y / a); }

    bool operator == (const Point &a) { return sign(x - a.x) == 0 && sign(y - a.y) == 0; }
    bool operator != (const Point &a) { return !(*this == a); }
    bool operator < (Point a) const { return sign(a.x - x) == 0 ? y < a.y : x < a.x; }
    bool operator > (Point a) const { return sign(a.x - x) == 0 ? y > a.y : x > a.x; }

    friend istream &operator >> (istream &is, Point &p) { return is >> p.x >> p.y; }
    friend ostream &operator << (ostream &os, const Point &p) { return os << p.x << " " << p.y; }

};

struct Line{
    TI a, b, c;
    Line(TI a, TI b, TI c) : a(a), b(b), c(c) {};
    sign(Point pt) return ::sign(a * pt.x + b * pt.y + c);
}

inline TI dot(Point a, Point b) { return a.x * b.x + a.y * b.y; }
inline TI cross(Point a, Point b) { return a.x * b.y - a.y * b.x; }
inline TI cross(Point a, Point b, Point c) { return cross(b - a, c - a); }
inline double dist(Point a, Point b) { return sqrt(dot(a - b, a - b)); }

bool isPointOnSegment(Point a, Point b, Point p){
    return cross(a, b, p) == 0 and p.x >= min(a.x, b.x) and p.x <= max(a.x, b.x) and p.y >= min(a.y, b.y) and p.y <= max(a.y, b.y);
}

// -1 --> outside, 0 --> boundary, 1 --> inside
int pointInPolygon(vector<Point> &pol, Point z){
    int n = pol.size(), winding = 0;
    for(int i = 0; i < n; i++){
        Point p1 = pol[i], p2 = pol[(i + 1) % n];
        if(isPointOnSegment(p1, p2, z)) return 0;
        int ori = sign(cross(p1, p2, z));
        if(p1.y <= z.y and p2.y > z.y and ori > 0) winding++;
        if(p1.y > z.y and p2.y <= z.y and ori < 0) winding--;
    }
    return winding != 0 ? 1 : -1;
}