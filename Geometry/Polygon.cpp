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