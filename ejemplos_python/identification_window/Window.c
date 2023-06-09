#include "Window.h"

uint16_t head = 0;
float queue[80];
const uint16_t features_count = 32;
float features[32];
/**
* Extract features
*/
bool transform(float *x, float *dest){
    // append source to queue
    memcpy(queue + head, x, sizeof(float) * 4);
    head += 4;

    if (head != 80) {
        return false;
    }

    // extract features for each axis
    uint16_t feature_idx = 0;

    for (uint16_t j = 0; j < 4; j++) {
        float m = queue[j];
        float M = m;
        float abs_m = abs(m);
        float abs_M = abs_m;
        float mean = m;
        float std = 0;
        float count_above_mean = 0;
        float count_below_mean = 0;
        // first-order features
        for (uint16_t i = j + 4; i < 80; i += 4) {
            float xi = queue[i];
            float abs_xi = abs(xi);
            mean += xi;

            if (xi < m) m = xi;

            if (xi > M) M = xi;

            if (abs_xi < abs_m) abs_m = abs_xi;

            if (abs_xi > abs_M) abs_M = abs_xi;
        }

        mean /= 20;
        // second-order features
        for (uint16_t i = j; i < 80; i += 4) {
            float xi = queue[i];
            float x0 = xi - mean;
            std += x0 * x0;

            if (x0 > 0) count_above_mean += 1;
            else count_below_mean += 1;
        }

        std = sqrt(std / 20);
        features[feature_idx++] = m;
        features[feature_idx++] = M;
        features[feature_idx++] = abs_m;
        features[feature_idx++] = abs_M;
        features[feature_idx++] = mean;
        features[feature_idx++] = std;
        features[feature_idx++] = count_above_mean;
        features[feature_idx++] = count_below_mean;
    }

    // copy to dest, if any
    if (dest != NULL) memcpy(dest, features, sizeof(float) * 32);
    // shift
    memcpy(queue, queue + 20, sizeof(float) * 60);
    head -= 20;

    return true;
};
/**
* Clear the current data of the window
*/
void clear() {
    head = 0;
};