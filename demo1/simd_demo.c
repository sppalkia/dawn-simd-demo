
#include <math.h>

#define ADD_ONE                 1
#define SUM_LARGE_FLOATS        1
#define SUM_LARGE_INTS          1
#define NESTED_IFS              1
#define SQRT_EACH               1
#define UPDATE                  1
#define UPDATE_RESTRICT         1

#if ADD_ONE
void add_one(float *v, unsigned length) {
    for (int i = 0; i < length; i++) {
        v[i]++;
    }
}
#endif

// Sums all the values in v which are greater than 100.
#if SUM_LARGE_FLOATS
float sum_large_floats(const float *v, unsigned length) {
    float result = 0;
    for (int i = 0; i < length; i++) {
        float val = v[i];
        if (val >= 100.0f) {
            result += val;
        }
    }
    return result;
}
#endif

// Sums all the values in v which are greater than 100.
#if SUM_LARGE_INTS
int sum_large_integers(const int *v, unsigned length) {
    int result = 0;
    for (int i = 0; i < length; i++) {
        int val = v[i];
        if (val >= 100) {
            result += val;
        }
    }
    return result;
}
#endif

#if NESTED_IFS
void nested_ifs(int *v, unsigned length) {
    for (int i = 0; i < length; i++) {
        if (v[i] > 10) {
            if (v[i] < 20) {
                v[i]++;
            }
        }
    }
}
#endif

/** Takes a vector v and writes the square root of each element
 * in result (or the element itself if element is negative).
 */
#if SQRT_EACH
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
#endif

// Compiler can't tell where v1 and v2 point!
// For example, v2[i+1] can == v1[i]
#if UPDATE
void update(float *v1, float *v2, unsigned length) {
    for (int i = 0; i < length; i++) {
        v1[i] = 2 * v2[i];
    }
}
#endif

// Restrict says that v1 and v2 won't point to the same underlying object.
#if UPDATE_RESTRICT
void update_restrict(
        float* restrict v1,
        float* restrict v2,
        unsigned length) {

    for (int i = 0; i < length; i++) {
        v1[i] = 2 * v2[i];
    }
}
#endif
