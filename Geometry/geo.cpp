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

struct Line {
    TI a, b, c;
    Line(TI a, TI b, TI c) : a(a), b(b), c(c) {}
    int sign(Point pt) const { return ::sign(a * pt.x + b * pt.y + c); }
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

// intersection point between ab and cd assuming unique intersection exists
bool line_line_intersection(Point a, Point b, Point c, Point d, Point &ans) {
    double a1 = a.y - b.y, b1 = b.x - a.x, c1 = cross(a, b);
    double a2 = c.y - d.y, b2 = d.x - c.x, c2 = cross(c, d);
    double det = a1 * b2 - a2 * b1;
    if (det == 0) return 0;
    ans = Point((b1 * c2 - b2 * c1) / det, (c1 * a2 - a1 * c2) / det);
    return 1;
}

bool is_point_in_segment(Point a, Point b, Point p) {
    return cross(a, b, p) == 0 &&
           p.x >= min(a.x, b.x) && p.x <= max(a.x, b.x) &&
           p.y >= min(a.y, b.y) && p.y <= max(a.y, b.y);
}

// -1 --> outside, 0 --> boundary, 1 --> inside
int is_point_in_polygon(vector<Point> &pol, Point z) {
    int n = pol.size(), winding = 0;
    for(int i = 0; i < n; i++) {
        Point p1 = pol[i], p2 = pol[(i + 1) % n];
        if(is_point_in_segment(p1, p2, z)) return 0;
        int ori = sign(cross(p1, p2, z));
        if(p1.y <= z.y && p2.y > z.y && ori > 0) winding++;
        if(p1.y > z.y && p2.y <= z.y && ori < 0) winding--;
    }
    return winding != 0 ? 1 : -1;
}

double rat(Point a, Point b, Point p) {
    return !sign(a.x - b.x) ? (p.y - a.y) / (b.y - a.y) : (p.x - a.x) / (b.x - a.x);
}

double polygon_union(vector<vector<Point>> &p) {
    int n = p.size();
    double ans = 0;
    for(int i = 0; i < n; ++i) {
        for(int v = 0; v < (int)p[i].size(); ++v) {
            Point a = p[i][v], b = p[i][(v + 1) % p[i].size()];
            vector<pair<double, int>> segs;
            segs.emplace_back(0, 0), segs.emplace_back(1, 0);
            for(int j = 0; j < n; ++j) {
                if(i != j) {
                    for(size_t u = 0; u < p[j].size(); ++u) {
                        Point c = p[j][u], d = p[j][(u + 1) % p[j].size()];
                        int sc = sign(cross(b - a, c - a)), sd = sign(cross(b - a, d - a));
                        if(!sc && !sd) {
                            if(sign(dot(b - a, d - c)) > 0 && i > j) {
                                segs.emplace_back(rat(a, b, c), 1);
                                segs.emplace_back(rat(a, b, d), -1);
                            }
                        } else {
                            double sa = cross(d - c, a - c), sb = cross(d - c, b - c);
                            if(sc >= 0 && sd < 0) segs.emplace_back(sa / (sa - sb), 1);
                            else if(sc < 0 && sd >= 0) segs.emplace_back(sa / (sa - sb), -1);
                        }
                    }
                }
            }
            sort(segs.begin(), segs.end());
            double pre = min(max(segs[0].first, 0.0), 1.0), now, sum = 0;
            int cnt = segs[0].second;
            for(int j = 1; j < (int)segs.size(); ++j) {
                now = min(max(segs[j].first, 0.0), 1.0);
                if(!cnt) sum += now - pre;
                cnt += segs[j].second;
                pre = now;
            }
            ans += cross(a, b) * sum;
        }
    }
    return ans * 0.5;
}

struct Circle {
    Point center;
    TI radius;

    Circle() {}
    Circle(Point center, TI radius) : center(center), radius(radius) {}
    Circle(TI x, TI y, TI radius) : center(Point(x, y)), radius(radius) {}

    bool operator == (Circle v) {
        return center == v.center and sign(radius - v.radius) == 0;
    }
    double area() {
        return PI * radius * radius;
    }
    double circumference() {
        return 2.0 * PI * radius;
    }
};

// -1 --> outside, 0 --> boundary, 1 --> inside
int is_point_in_circle(Circle cr, Point p){
    return sign(cr.radius * cr.radius - dist2(cr.center, p));
}

//compute intersection of line through points a and b with
//circle centered at c with radius r > 0
vector<Point> circle_line_intersection(Circle c, Point a, Point b) {
    vector<Point> ret;
    b = b - a; a = a - c.center;
    TI A = dot(b, b), B = dot(a, b);
    TI C = dot(a, a) - c.radius * c.radius, D = B * B - A * C;
    if (sign(D) < 0) return ret;
    D = max(D, 0.0);
    ret.push_back(c.center + a + b * (-B + sqrt(D)) / A);
    if (sign(D) > 0) ret.push_back(c.center + a + b * (-B - sqrt(D)) / A);
    return ret;
}

vector<Point> circle_circle_intersection(Circle c1, Circle c2) {
    if (c1 == c2) return {Point(1e18, 1e18)};
    vector<Point> ret;
    double d = dist(c1.center, c2.center);
    TI r1 = c1.radius, r2 = c2.radius;
    if (d > r1 + r2 || d + min(r1, r2) < max(r1, r2)) return ret;
    double x = (d * d - r2 * r2 + r1 * r1) / (2 * d);
    double y = sqrt(r1 * r1 - x * x);
    Point v = (c2.center - c1.center) / d;
    ret.push_back(c1.center + v * x + rotateccw90(v) * y);
    if (y > 0) ret.push_back(c1.center + v * x - rotateccw90(v) * y);
    return ret;
}