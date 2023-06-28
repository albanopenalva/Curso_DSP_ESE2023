#include "Classifier.h"

/**
* Predict class for features vector
*/
int predict(float *x) {
    uint8_t votes[4] = { 0 };
    // tree #1
    if (x[20] <= 51.375) {
        if (x[10] <= 23.0) {
            votes[1] += 1;
        }

        else {
            if (x[12] <= 30.049999237060547) {
                votes[2] += 1;
            }

            else {
                votes[3] += 1;
            }
        }
    }

    else {
        votes[0] += 1;
    }

    // tree #2
    if (x[19] <= 64.0) {
        if (x[1] <= 92.5) {
            if (x[11] <= 33.0) {
                votes[2] += 1;
            }

            else {
                votes[3] += 1;
            }
        }

        else {
            votes[1] += 1;
        }
    }

    else {
        votes[0] += 1;
    }

    // tree #3
    if (x[4] <= 94.70000076293945) {
        if (x[8] <= 23.0) {
            votes[1] += 1;
        }

        else {
            if (x[4] <= 87.95000076293945) {
                votes[3] += 1;
            }

            else {
                votes[2] += 1;
            }
        }
    }

    else {
        votes[0] += 1;
    }

    // tree #4
    if (x[12] <= 20.199999809265137) {
        votes[0] += 1;
    }

    else {
        if (x[26] <= 101.2413558959961) {
            votes[1] += 1;
        }

        else {
            if (x[2] <= 86.0) {
                votes[3] += 1;
            }

            else {
                votes[2] += 1;
            }
        }
    }

    // tree #5
    if (x[8] <= 17.0) {
        votes[0] += 1;
    }

    else {
        if (x[12] <= 25.27500057220459) {
            votes[1] += 1;
        }

        else {
            if (x[11] <= 33.0) {
                votes[2] += 1;
            }

            else {
                votes[3] += 1;
            }
        }
    }

    // tree #6
    if (x[19] <= 64.0) {
        if (x[28] <= 102.7834587097168) {
            votes[1] += 1;
        }

        else {
            if (x[2] <= 86.0) {
                votes[3] += 1;
            }

            else {
                votes[2] += 1;
            }
        }
    }

    else {
        votes[0] += 1;
    }

    // tree #7
    if (x[19] <= 64.0) {
        if (x[1] <= 92.5) {
            if (x[13] <= 1.716581404209137) {
                votes[2] += 1;
            }

            else {
                votes[3] += 1;
            }
        }

        else {
            votes[1] += 1;
        }
    }

    else {
        votes[0] += 1;
    }

    // tree #8
    if (x[24] <= 98.43399810791016) {
        votes[0] += 1;
    }

    else {
        if (x[28] <= 102.7834587097168) {
            votes[1] += 1;
        }

        else {
            if (x[4] <= 87.95000076293945) {
                votes[3] += 1;
            }

            else {
                votes[2] += 1;
            }
        }
    }

    // tree #9
    if (x[3] <= 96.0) {
        if (x[24] <= 101.2413558959961) {
            votes[1] += 1;
        }

        else {
            if (x[1] <= 90.5) {
                votes[3] += 1;
            }

            else {
                votes[2] += 1;
            }
        }
    }

    else {
        votes[0] += 1;
    }

    // tree #10
    if (x[8] <= 17.0) {
        votes[0] += 1;
    }

    else {
        if (x[28] <= 102.7834587097168) {
            votes[1] += 1;
        }

        else {
            if (x[9] <= 33.0) {
                votes[2] += 1;
            }

            else {
                votes[3] += 1;
            }
        }
    }

    // return argmax of votes
    uint8_t classIdx = 0;
    float maxVotes = votes[0];

    for (uint8_t i = 1; i < 4; i++) {
        if (votes[i] > maxVotes) {
            classIdx = i;
            maxVotes = votes[i];
        }
    }

    return classIdx;
};
/**
* Predict readable class name
*/
const char* predictLabel(float *x) {
    return idxToLabel(predict(x));
};
/**
* Convert class idx to readable name
*/
const char* idxToLabel(uint8_t classIdx) {
    switch (classIdx) {
        case 0:
        return "Stable";
        case 1:
        return "Mild";
        case 2:
        return "Moderate";
        case 3:
        return "Critical";
        default:
        return "Houston we have a problem";
    }
};