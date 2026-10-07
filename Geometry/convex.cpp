vector<Point> ConvexHull(vector<Point> &PT) {
    sort(PT.begin(), PT.end());
    int m = 0, n = PT.size();
    vector<Point> hull(n + n + 2);
    for(int i = 0; i < n; i++) {
        while(m > 1 && cross(hull[m - 2], hull[m - 1], PT[i]) < 0) m--;
        hull[m++] = PT[i];
    }
    for(int i = n - 2, k = m; i >= 0; i--) {
        while(m > k && cross(hull[m - 2], hull[m - 1], PT[i]) < 0) m--;
        hull[m++] = PT[i];
    }
    if(n > 1) m--;
    hull.resize(m);
    return hull;
}

// -1 --> outside, 0 --> boundary, 1 --> inside
// Assumes polygon vertex are in CCW order
int isPointInConvexPolygon(const vector<Point>& poly, Point p) {
    int n = poly.size();
    assert(n >= 3);

    int sign1 = sign(cross(poly[0], poly[1], p));
    int sign2 = sign(cross(poly[0], poly[n - 1], p));

    if (sign1 < 0 || sign2 > 0) return -1;

    if (sign1 == 0) return is_point_in_segment(poly[0], poly[1], p) - 1;
    if (sign2 == 0) return is_point_in_segment(poly[0], poly[n - 1], p) - 1;

    int lo = 1, hi = n - 1;
    while (hi - lo > 1) {
        int mid = (lo + hi) / 2;
        if (sign(cross(poly[0], poly[mid], p)) >= 0) lo = mid;
        else hi = mid;
    }
    return sign(cross(poly[lo], poly[hi], p));
}