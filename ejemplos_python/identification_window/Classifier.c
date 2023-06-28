#include "Classifier.h"

/**
* Predict class for features vector
*/
int predict(float *x) {
    uint8_t votes[4] = { 0 };
    // tree #1
    if (x[29] <= 0.7194645404815674) {
        votes[1] += 1;
    }

    else {
        if (x[9] <= 24.0) {
            votes[0] += 1;
        }

        else {
            if (x[0] <= 86.0) {
                votes[3] += 1;
            }

            else {
                votes[2] += 1;
            }
        }
    }

    // tree #2
    if (x[3] <= 92.5) {
        if (x[5] <= 1.2408960461616516) {
            votes[2] += 1;
        }

        else {
            votes[3] += 1;
        }
    }

    else {
        if (x[11] <= 21.0) {
            votes[0] += 1;
        }

        else {
            votes[1] += 1;
        }
    }

    // tree #3
    if (x[13] <= 0.9347169995307922) {
        votes[1] += 1;
    }

    else {
        if (x[24] <= 99.38311004638672) {
            votes[0] += 1;
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

    // tree #4
    if (x[10] <= 23.0) {
        if (x[3] <= 96.0) {
            votes[1] += 1;
        }

        else {
            votes[0] += 1;
        }
    }

    else {
        if (x[12] <= 30.07499885559082) {
            votes[2] += 1;
        }

        else {
            votes[3] += 1;
        }
    }

    // tree #5
    if (x[29] <= 0.7194645404815674) {
        votes[1] += 1;
    }

    else {
        if (x[5] <= 0.6241657733917236) {
            votes[2] += 1;
        }

        else {
            if (x[4] <= 91.29999923706055) {
                votes[3] += 1;
            }

            else {
                votes[0] += 1;
            }
        }
    }

    // tree #6
    if (x[11] <= 26.0) {
        if (x[21] <= 5.327179670333862) {
            votes[1] += 1;
        }

        else {
            votes[0] += 1;
        }
    }

    else {
        if (x[18] <= 37.0) {
            votes[3] += 1;
        }

        else {
            votes[2] += 1;
        }
    }

    // tree #7
    if (x[26] <= 101.2413558959961) {
        if (x[25] <= 100.68804168701172) {
            votes[0] += 1;
        }

        else {
            votes[1] += 1;
        }
    }

    else {
        if (x[18] <= 37.0) {
            votes[3] += 1;
        }

        else {
            votes[2] += 1;
        }
    }

    // tree #8
    if (x[13] <= 0.9347169995307922) {
        votes[1] += 1;
    }

    else {
        if (x[13] <= 1.7617025971412659) {
            if (x[21] <= 7.377678990364075) {
                votes[2] += 1;
            }

            else {
                votes[0] += 1;
            }
        }

        else {
            if (x[1] <= 94.0) {
                votes[3] += 1;
            }

            else {
                votes[0] += 1;
            }
        }
    }

    // tree #9
    if (x[0] <= 91.5) {
        if (x[20] <= 40.474998474121094) {
            votes[3] += 1;
        }

        else {
            votes[2] += 1;
        }
    }

    else {
        if (x[27] <= 100.68804168701172) {
            votes[0] += 1;
        }

        else {
            votes[1] += 1;
        }
    }

    // tree #10
    if (x[13] <= 0.9347169995307922) {
        votes[1] += 1;
    }

    else {
        if (x[13] <= 1.7617025971412659) {
            if (x[5] <= 0.8173403143882751) {
                votes[2] += 1;
            }

            else {
                votes[0] += 1;
            }
        }

        else {
            if (x[1] <= 94.0) {
                votes[3] += 1;
            }

            else {
                votes[0] += 1;
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