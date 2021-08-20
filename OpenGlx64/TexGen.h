#ifndef TEXGEN_H
#define TEXGEN_H

#include <cmath>
#include <vector>
#include <random>
#include <utility>
#include <iomanip>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <windows.h>

class TexGen
{
private:
    //static int texlen;
    static std::mt19937_64 gen64;
    static std::vector<int> color_values;
    static std::vector<int> ground_prefix_sums;
    void hsv2rgb(int h, int s, int v, int& r, int& g, int& b);

public:
    int texlen;
    TexGen();
    static std::vector<int> ground();
    static std::vector<int> hedge();
    void actual_visualization_function(std::vector<int> vec, bool hedge);
    void del();
};

#endif //TEXGEN_H