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