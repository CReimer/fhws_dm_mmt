//
// Created by christopher on 15.11.16.
//

#include <fstream>
#include <vector>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>
#include "Ppm.h"

using namespace std;

void Ppm::readFile(string filename) {
    ifstream ifs(filename);
    string line;

    getline(ifs, line);
    getline(ifs, line);

    while (line.substr(0, 1) == "#") {
        getline(ifs, line);
    }

    vector<string> words;
    boost::split(words, line, boost::is_any_of(" "), boost::token_compress_on);

    unsigned int maxX = (unsigned int) stoi(words.at(0));
    unsigned int maxY = (unsigned int) stoi(words.at(1));
    Ppm::x = maxX;
    Ppm::y = maxY;

    vector<vector<RGBPixel>> framebuffer(maxX, vector<RGBPixel>(maxY));

    getline(ifs, line);

    vector<string> colors;
    while (getline(ifs, line)) {
        string temp;
        for (int i = 0; i < line.length(); i++) {
            if (isdigit(line[i])) {
                temp.push_back(line[i]);
            } else {
                if (!temp.empty()) {
                    colors.push_back(temp);
                    temp.clear();
                }
            }
        }
    }

    for (int color = 0; color < colors.size(); color++) {
        int r = stoi(colors.at((unsigned) color));
        color++;
        int g = stoi(colors.at((unsigned) color));
        color++;
        int b = stoi(colors.at((unsigned) color));
        int y = color / (maxX * 3);
        int x = (color / 3) - y * maxX;
        framebuffer[x][y] = RGBPixel(r, g, b);
    }

    Ppm::image = framebuffer;
}

const vector<vector<RGBPixel>> &Ppm::getRgbImage() const {
    return image;
}


Ppm::Ppm() {}

vector<vector<YCbCrPixel>> Ppm::getYCbCrImage() {
    unsigned int maxX = (int) Ppm::image.size();
    unsigned int maxY = (int) Ppm::image[0].size();

    vector<vector<YCbCrPixel>> framebuffer(maxX, vector<YCbCrPixel>(maxY));
    for (int x = 0; x < maxX; x++) {
        for (int y = 0; y < maxY; y++) {
            int r = Ppm::image[x][y].getR();
            int g = Ppm::image[x][y].getG();
            int b = Ppm::image[x][y].getB();

            int Y = (int) (0.2989 * r + 0.5866 * g + 0.1145 * b);
            int Cb = (int) (-0.1687 * r - 0.3313 * g + 0.5000 * b) + 128;
            int Cr = (int) (0.5000 * r - 0.4184 * g - 0.0816 * b) + 128;

            framebuffer[x][y] = YCbCrPixel(Y, Cb, Cr);
        }
    }


    return framebuffer;
}

int Ppm::getX() const {
    return x;
}

int Ppm::getY() const {
    return y;
}
