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

bool isPointOnSegment(Point a, Point b, Point p) {
    return cross(a, b, p) == 0 &&
           p.x >= min(a.x, b.x) && p.x <= max(a.x, b.x) &&
           p.y >= min(a.y, b.y) && p.y <= max(a.y, b.y);
}

// -1 --> outside, 0 --> boundary, 1 --> inside
int pointInPolygon(vector<Point> &pol, Point z) {
    int n = pol.size(), winding = 0;
    for(int i = 0; i < n; i++) {
        Point p1 = pol[i], p2 = pol[(i + 1) % n];
        if(isPointOnSegment(p1, p2, z)) return 0;
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