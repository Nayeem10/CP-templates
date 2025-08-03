#include <bits/stdc++.h>

using namespace std;


int main(){
	int n, m, s;
	cin >> n >> m >> s;
	vector<int> g[n + 1];
	vector<int> dis(n + 1, 1e9), vis(n + 1);
	queue<pair<int, int>> q;
	for(int i = 0; i < m; i++){
		int u, v; cin >> u >> v;#ifndef LINE
#define LINE

#include "../obj.hpp"

class Line{
public:
    float a, b, c;
    Line(float a, float b, float c) : a(a), b(b), c(c) {}

    void shiftHorizontal(float amount){
        c -= a * amount;
    }

    void shiftVertical(float amount){
        c -= b * amount;
    }

    tuple<float, float, float> getEqn(){
        return {a, b, c};
    }
    
};

class HorizontalLine : public Line{
public:
    node &refPoint;
    HorizontalLine(node &refPoint) : refPoint(refPoint) {}

    tuple<float, float, float> getEqn(){
        auto [x, y] = refPoint.loc();
        return {0, 1, -y};
    }
};


class VerticalLine : public Line{
public:
    node &refPoint;
    VerticalLine(node &refPoint) : refPoint(refPoint) {}


    tuple<float, float, float> getEqn(){
        auto [x, y] = refPoint.loc();
        return {1, 0, -x};
    }
    
};

class PerpendicularLine : public Line{
    public:
        Line &refLine;
        node &refPoint;
        VerticalLine(Line &refLine, node &refPoint) : refLine(refLine), refPoint(refPoint) {}
    
    
        tuple<float, float, float> getEqn(){
            auto [x, y] = refPoint.loc();
            return {1, 0, -x};
        }
        
    };
    

Line getPerpendicularLine(Line &l, node &p){
    auto [x, y] = p.loc();
    auto [a, b, c] = l.getEqn();
    float x, y;
    return Line(b, -a, a * y - b * x);
}

class LineSegment : public Line{
public:
    node &startPoint, &endPoint;

    tuple<float, float, float> getEqn(){
        auto [x1, y1] = startPoint.loc();
        auto [x2, y2] = endPoint.loc();
        a = y1 - y2;
        b = x2 - x1;
        c = x1 * y2 - x2 * y1;
        return {a, b, c};
    }

};


#endif // !LINE

		g[u].push_back(v);
		g[v].push_back(u);
	}
	for(int i = 1; i <= n; i++){
		cout << i << ": ";
		for(auto j: g[i]) cout << j << ' ';
		cout << '\n';
	}
	dis[s] = 0;
	q.push({s, 0});
	vector<pair<int, int>> ed;
	cout << "BFS order\n";
	while(q.size()){
		auto [u, d] = q.front();
		q.pop();
		if(vis[u]) continue;
		dis[u] = d; vis[u] = 1;
		for(auto v: g[u]){
			if(!vis[v]){
				q.push({v, d + 1});
				ed.push_back({u, v});
			}
		}
		cout << u << ' ';
	}
	cout << '\n';
	cout << "Distance\n";
	for(int i = 1; i <= n; i++){
		cout << i << "(" << dis[i] << ") ";
	}
	cout << '\n';
	cout << "BFS TREE\n";
	for(auto [u, v]: ed){
		cout << u << " " << v << '\n';
	}
}