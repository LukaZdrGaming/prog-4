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

struct Vertex3D {
    float x, y, z, w;
};

Vertex3D multiply(const float m[4][4], const Vertex3D& v) {
    return {
        m[0][0] * v.x + m[0][1] * v.y + m[0][2] * v.z + m[0][3] * v.w,
        m[1][0] * v.x + m[1][1] * v.y + m[1][2] * v.z + m[1][3] * v.w,
        m[2][0] * v.x + m[2][1] * v.y + m[2][2] * v.z + m[2][3] * v.w,
        m[3][0] * v.x + m[3][1] * v.y + m[3][2] * v.z + m[3][3] * v.w
    };
}

int main() {
    string filename = "C:/Users/Frosina Zdravkovic/Code/Programiranje domasna/Programiranje-domasna-IV-1/3d transformacii/monkey.obj";
    ifstream file(filename);

    if (!file.is_open()) {
        cerr << "Error: Could not open file " << filename << endl;
        return 1;
    }

    vector<Vertex3D> vertices;
    string line;
    float sumX = 0, sumY = 0, sumZ = 0;

    while (getline(file, line)) {
        if (line.substr(0, 2) == "v ") {
            stringstream ss(line.substr(2));
            float x, y, z;
            if (ss >> x >> y >> z) {
                vertices.push_back({x, y, z, 1});
                sumX += x;
                sumY += y;
                sumZ += z;
            }
        }
    }
    file.close();

    if (vertices.empty()) return 1;

    float centerX = sumX / vertices.size();
    float centerY = sumY / vertices.size();
    float centerZ = sumZ / vertices.size();

    float tx = 0, ty = 0, tz = 0;
    float radx = 45 * (M_PI / 180);
    float rady = 27 * (M_PI / 180);
    float radz = 10 * (M_PI / 180);
    float scaleFactorX = 1.5;
    float scaleFactorY = -1;
    float scaleFactorZ = 1;

    float T[4][4] = {
        {1, 0, 0, tx},
        {0, 1, 0, ty},
        {0, 0, 1, tz},
        {0, 0, 0, 1 }
    };

    float T_to_origin[4][4] = {
        {1, 0, 0, -centerX},
        {0, 1, 0, -centerY},
        {0, 0, 1, -centerZ},
        {0, 0, 0, 1}
    };


    float RX[4][4] = {
    {1, 0,        0,         0},
    {0, cos(radx), -sin(radx), 0},
    {0, sin(radx), cos(radx),  0},
    {0, 0,        0,         1}
    };

    float RY[4][4] = {
        {cos(rady),  0, sin(rady), 0},
        {0,         1, 0,        0},
        {-sin(rady), 0, cos(rady), 0},
        {0,         0, 0,        1}
    };

    float RZ[4][4] = {
    {cos(radz), -sin(radz), 0, 0},
    {sin(radz),  cos(radz), 0, 0},
    {0,         0,        1, 0},
    {0,         0,        0, 1}
    };

    float S[4][4] = {
        {scaleFactorX, 0, 0, 0},
        {0, scaleFactorY, 0, 0},
        {0, 0, scaleFactorZ, 0},
        {0, 0, 0, 1}
    };

    float T_back[4][4] = {
        {1, 0, 0, centerX},
        {0, 1, 0, centerY},
        {0, 0, 1, centerZ},
        {0, 0, 0, 1}
    };
    for(auto& v: vertices){
        v = multiply(T_to_origin, v);
        v = multiply(RX, v);
        v = multiply(RY, v);
        v = multiply(RZ, v);
        v = multiply(S, v);
        v = multiply(T_back,v);
    }

    string outputFilename = "transformed_model.obj";
    ofstream outFile(outputFilename);

    if (outFile.is_open()) {
        outFile << fixed << setprecision(6);

        for (const auto& v : vertices) {
            outFile << "v " << v.x / v.w << " " 
                            << v.y / v.w << " " 
                            << v.z / v.w << "\n";
        }

        outFile.close();
        cout << "Success! Transformed model saved to: " << outputFilename << endl;
    } else {
        cerr << "Error: Could not create output file." << endl;
    }
    

    return 0;
}