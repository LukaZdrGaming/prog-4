#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <cmath>
#include <iomanip>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

using namespace std;

struct Vertex2D {
    float x, y, w;
};

Vertex2D multiply(const float m[3][3], const Vertex2D& v) {
    return {
        m[0][0] * v.x + m[0][1] * v.y + m[0][2] * v.w,
        m[1][0] * v.x + m[1][1] * v.y + m[1][2] * v.w,
        m[2][0] * v.x + m[2][1] * v.y + m[2][2] * v.w
    };
}

int main() {
    string filename = "C:/Users/Frosina Zdravkovic/Code/Programiranje domasna/Programiranje-domasna-IV-1/2D_transformacija/square.obj";
    ifstream file(filename);

    if (!file.is_open()) {
        cerr << "Error: Could not open file " << filename << endl;
        return 1;
    }

    vector<Vertex2D> vertices;
    string line;
    float sumX = 0, sumY = 0;

    while (getline(file, line)) {
        if (line.substr(0, 2) == "v ") {
            stringstream ss(line.substr(2));
            float x, y;
            if (ss >> x >> y) {
                vertices.push_back({x, y, 1.0f});
                sumX += x;
                sumY += y;
            }
        }
    }
    file.close();

    if (vertices.empty()) return 1;

    float initialCenterX = sumX / vertices.size();
    float initialCenterY = sumY / vertices.size();

    float tx = 2.0f; 
    float ty = 0.0f;
    float degrees = 45.0f;
    float rad = degrees * (M_PI / 180.0f);
    float scaleFactor = 0.25f;

    float newCenterX = initialCenterX + tx;
    float newCenterY = initialCenterY + ty;

    float T[3][3] = {
        {1, 0, tx},
        {0, 1, ty},
        {0, 0, 1 }
    };

    float T_to_origin[3][3] = {
        {1, 0, -newCenterX},
        {0, 1, -newCenterY},
        {0, 0, 1}
    };

    float R[3][3] = {
        {cos(rad), -sin(rad), 0},
        {sin(rad),  cos(rad), 0},
        {0,         0,        1}
    };

    float S[3][3] = {
        {scaleFactor, 0, 0},
        {0, scaleFactor, 0},
        {0, 0, 1}
    };

    float T_back[3][3] = {
        {1, 0, newCenterX},
        {0, 1, newCenterY},
        {0, 0, 1}
    };

    cout << fixed << setprecision(3);

    cout << "Translation:" << endl;
    for (auto& v : vertices) {
        v = multiply(T, v);
        cout << "Pos: (" << v.x/v.w << ", " << v.y/v.w << ")" << endl;
    }

    cout << "\n Rotation:" << endl;
    for (auto& v : vertices) {
        v = multiply(T_to_origin, v);
        v = multiply(R, v);
        v = multiply(T_back, v);
        cout << "Pos: (" << v.x/v.w << ", " << v.y/v.w << ")" << endl;
    }

    cout << "\n Scale:" << endl;
    for (auto& v : vertices) {
        v = multiply(T_to_origin, v);
        v = multiply(S, v);
        v = multiply(T_back, v);
        cout << "Pos: (" << v.x/v.w << ", " << v.y/v.w << ")" << endl;
    }

    return 0;
}