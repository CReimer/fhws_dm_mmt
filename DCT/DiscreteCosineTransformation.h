//
// Created by christopher on 18.12.16.
//

#ifndef DM_MMT_DISCRETECOSINETRANSFORMATION_H
#define DM_MMT_DISCRETECOSINETRANSFORMATION_H


using namespace std;

class DiscreteCosineTransformation {
private:

public:
    static vector<vector<float>> dct(vector<vector<float>> input);

    static vector<vector<float>> idct(vector<vector<float>> input);
};


#endif //DM_MMT_DISCRETECOSINETRANSFORMATION_H
