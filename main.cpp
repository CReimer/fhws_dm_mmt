#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <iterator>
#include <boost/algorithm/string/classification.hpp> // Include boost::for is_any_of
#include <boost/algorithm/string/split.hpp> // Include for boost::split

using namespace std;

struct RGBPixel {
    int R, G, B;

    RGBPixel(int r = 0, int g = 0, int b = 0) : R(r), G(g), B(b) {};
};

struct YCbCrPixel {
    int Y, Cb, Cr;

    YCbCrPixel(int y = 0, int cb = 0, int cr = 0) : Y(y), Cb(cb), Cr(cr) {};
};

struct Subsample {
    int Y1;
    int Y2;
    int Y3;
    int Y4;
    int Cb;
    int Cr;

    Subsample(int y1 = 0, int y2 = 0, int y3 = 0, int y4 = 0, int cb = 0, int cr = 0) : Y1(y1), Y2(y2), Y3(y3), Y4(y4),
                                                                                        Cb(cb), Cr(cr) {};

};

vector<vector<Subsample>> subsample420(vector<vector<YCbCrPixel>> input) {
    vector<vector<Subsample>> output(input.size() / 2, vector<Subsample>(input[0].size() / 2));


    for (int y = 0; y < input[0].size(); y++) {
        for (int x = 0; x < input.size(); x++) {
            int y1 = input[x][y].Y;
            int cb1 = input[x][y].Cb;
            int cr1 = input[x][y].Cr;
            x += 1; // 1 nach rechts

            int y2 = input[x][y].Y;
            int cb2 = input[x][y].Cb;
            int cr2 = input[x][y].Cr;
            x -= 1; // 1 nach links
            y += 1; // neue Zeile

            int y3 = input[x][y].Y;
            int cb3 = input[x][y].Cb;
            int cr3 = input[x][y].Cr;
            x += 1; // 1 nach rechts

            int y4 = input[x][y].Y;
            int cb4 = input[x][y].Cb;
            int cr4 = input[x][y].Cr;
            y -= 1; //

            int cb = (cb1 + cb2 + cb3 + cb4) / 4;
            int cr = (cr1 + cr2 + cr3 + cr4) / 4;

            int xo = (x - 1) / 2;
            int yo = y / 2;
            output[xo][yo] = Subsample(y1, y2, y3, y4, cb, cr);
        }
        y += 1; // Zwei Zeilen abgearbeitet. Springe zur nächsten
    }
    return output;
}

vector<vector<YCbCrPixel>> rgbToYcbcr(vector<vector<RGBPixel>> input) {
    unsigned int maxX = (int) input.size();
    unsigned int maxY = (int) input[0].size();

    vector<vector<YCbCrPixel>> framebuffer(maxX, vector<YCbCrPixel>(maxY));
    for (int x = 0; x < maxX; x++) {
        for (int y = 0; y < maxY; y++) {
            int r = input[x][y].R;
            int g = input[x][y].G;
            int b = input[x][y].B;

            int Y = (int) (0.2989 * r + 0.5866 * g + 0.1145 * b);
            int Cb = (int) (-0.1687 * r - 0.3313 * g + 0.5000 * b) + 128;
            int Cr = (int) (0.5000 * r - 0.4184 * g - 0.0816 * b) + 128;

            framebuffer[x][y] = YCbCrPixel(Y, Cb, Cr);
        }
    }
    return framebuffer;
}

vector<vector<RGBPixel>> readPpm(string test = "./test.ppm") {
    std::ifstream ifs(test);
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

    return framebuffer;
}

vector<bool> readBitstream(string file) {
    std::ifstream ifs(file);
    char b;
    vector<bool> bitstream;
    while(ifs.read(&b, 1)) {
        for (int i=0; i < 8; ++i)
            bitstream.push_back((b & (1<<i)) != 0);
    }
    return bitstream;
}

void writeBitstream(string file, vector<bool> bitstream) {
    std::ofstream ofs(file);


    int i = 0;
    while (i < bitstream.size()) {
        char c = 0;
        for (int j = 0; j < 8; j++) {
            if(bitstream[i + j]) {
                c |= 1 << j;
            }
        }
        i += 8;
        ofs.write(&c,1);
    }
}

int main() {
    std::cout << "Hello, World!" << std::endl;
//    vector<vector<RGBPixel>> picture = readPpm();
//    vector<vector<YCbCrPixel>> ypicture = rgbToYcbcr(picture);
//    subsample420(ypicture);
    vector<bool> test = readBitstream("./test.jpg");

    // Bit hinten anhängen: vector.push_back(bool)
    // Bit vorne anhängen: vector.insert(vector.begin(),bool)

    writeBitstream("output.jpg", test);

    return 0;
}
