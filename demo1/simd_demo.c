
#include <math.h>

// 1. Fast Math (add -ffast-math)
// 2. Uncomment the if statements
// 3. Talk about aliasing.
// 4. Fickleness
// ..

/** Takes a vector v and writes the square root of each element
 * in result (or the element itself if element is negative).
 */
void sqrt_each(float *result, const float *v, unsigned length) {
    for (int i = 0; i < length; i++) {
        float val = v[i];
        if (val >= 0.0f) {
                result[i] = sqrtf(val);
        } else {
            result[i] = val;
        }
    }
}

// Sums all the values in v which are greater than 100.
float sum_large_floats(const float *v, unsigned length) {
    float result = 0;
    for (int i = 0; i < length; i++) {
        float val = v[i];
        //if (val >= 100.0f) {
            result += val;
        //}
    }
    return result;
}

// Sums all the values in v which are greater than 100.
int sum_large_integers(const int *v, unsigned length) {
    int result = 0;
    for (int i = 0; i < length; i++) {
        int val = v[i];
        //if (val >= 100) {
            result += val;
        //}
    }
    return result;
}

// Compiler can't tell where v1 and v2 point!
// For example, v2[i+1] can == v1[i]
void update(float *v1, float *v2, unsigned length) {
    for (int i = 0; i < length; i++) {
        v1[i] = 2 * v2[i];
    }
}

// Restrict says that v1 and v2 won't point to the same underlying object.
void update_restrict(
        float* restrict v1,
        float* restrict v2,
        unsigned length) {

    for (int i = 0; i < length; i++) {
        v1[i] = 2 * v2[i];
    }
}

