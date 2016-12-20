//
// Created by christopher on 20.12.16.
//

#include "DctDirect.h"

#define M_PI 3.14159265358979323846

Eigen::MatrixXd DctDirect::Transform(Eigen::MatrixXd input) {
    // Based on: http://www.winfotex.de/die-diskrete-kosinus-transformation-dct/
    int n = (int) input.rows();
    double ca;
    double cb;
    double tmpXab = 0.0;
    double cmpnt;

    Eigen::MatrixXd output = input;

    for (int i = 0; i < n; i++) {                                        //erste Schleife für C(i)
        for (int j = 0; j < n; j++) {                                    //zweite Schleife für C(j)
            for (int x = 0; x < n; x++) {                                //dritte Schleife für x
                for (int y = 0; y < n; y++) {                            //vierte Schleife für y
                    cmpnt = input(x, y) *                                //X(x,y); Komponente der Transformation
                            cos((float) (((2.0 * x + 1.0) * i * M_PI) / (2.0 * n))) *    //erste Klammer
                            cos((float) (((2.0 * y + 1.0) * j * M_PI) / (2.0 * n)));    //zweite Klammer
                    tmpXab += cmpnt;                                    //Summierung von X
//                    cmpnt = 0.0;
                }
            }
            //Abfrage, ob n gleich oder ungleich 0; Entscheidung ob C(n) 1 oder (1/Wurzel(2)) ist
            //C(i)
            if (i == 0)
                ca = (1.0 / sqrt(2.0f));
            else
                ca = 1.0;
            //C(j)
            if (j == 0)
                cb = (1.0 / sqrt(2.0f));
            else
                cb = 1.0;

            output(i, j) = (float) ((2.0 / n) * ca * cb * tmpXab);        //Y(i,j)
            tmpXab = 0.0;
        }
    }

    return output;
}