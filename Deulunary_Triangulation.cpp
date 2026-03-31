#include <iostream>
#include <vector>

using namespace std;

struct Point { double x, y; };
struct Triangle { Point p1, p2, p3; };

bool isInsideCircumcircle(Point p1, Point p2, Point p3, Point p) {
    double ax = p1.x - p.x, ay = p1.y - p.y;
    double bx = p2.x - p.x, by = p2.y - p.y;
    double cx = p3.x - p.x, cy = p3.y - p.y;
    
    double det = (ax*ax + ay*ay) * (bx*cy - cx*by) - 
                 (bx*bx + by*by) * (ax*cy - cx*ay) + 
                 (cx*cx + cy*cy) * (ax*by - bx*ay);
    return det > 0;
}

bool pointsMatch(Point a, Point b) {
    return a.x == b.x && a.y == b.y;
}

bool edgesMatch(Point a1, Point a2, Point b1, Point b2) {
    return (pointsMatch(a1, b1) && pointsMatch(a2, b2)) || 
           (pointsMatch(a1, b2) && pointsMatch(a2, b1));
}

int main() {
    vector<Point> points = {{0,0}, {2,0}, {1,2}, {1,1}};
    vector<Triangle> mesh;

    Point s1 = {-100, -100}, s2 = {100, -100}, s3 = {0, 100};
    mesh.push_back({s1, s2, s3});

    for (const auto& p : points) {
        vector<pair<Point, Point>> edges;
        vector<Triangle> nextMesh;

        for (const auto& tri : mesh) {
            if (isInsideCircumcircle(tri.p1, tri.p2, tri.p3, p)) {
                edges.push_back({tri.p1, tri.p2});
                edges.push_back({tri.p2, tri.p3});
                edges.push_back({tri.p3, tri.p1});
            } else {
                nextMesh.push_back(tri);
            }
        }

        for (int i = 0; i < edges.size(); i++) {
            bool isShared = false;
            for (int j = 0; j < edges.size(); j++) {
                if (i != j && edgesMatch(edges[i].first, edges[i].second, edges[j].first, edges[j].second)) {
                    isShared = true;
                    break;
                }
            }
            if (!isShared) {
                nextMesh.push_back({edges[i].first, edges[i].second, p});
            }
        }
        mesh = nextMesh;
    }

    int count = 0;
    for (const auto& t : mesh) {
        bool touchesSuper = pointsMatch(t.p1, s1) || pointsMatch(t.p1, s2) || pointsMatch(t.p1, s3) ||
                            pointsMatch(t.p2, s1) || pointsMatch(t.p2, s2) || pointsMatch(t.p2, s3) ||
                            pointsMatch(t.p3, s1) || pointsMatch(t.p3, s2) || pointsMatch(t.p3, s3);

        if (!touchesSuper) {
            cout << "T" << count++ << ": (" << t.p1.x << "," << t.p1.y << ") "
                 << "(" << t.p2.x << "," << t.p2.y << ") "
                 << "(" << t.p3.x << "," << t.p3.y << ")\n";
        }
    }

    return 0;
}