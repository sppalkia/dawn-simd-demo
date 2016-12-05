
#include <stdio.h>
#include <sys/time.h>

// For Intel intrinsics.
#include <immintrin.h>

// Sums all the values in v which are greater than 100.
double sum_large_floats(const float *v, unsigned length, unsigned trials) {
    double result = 0.0f;
    for (int t = 0; t < trials; t++) {
        for (int i = 0; i < length; i++) {
            float val = v[i];
            if (val >= 100.0f) {
                result += val;
            }
        }
    }
    return result;
}

// Sums all the values in v which are greater than 100.
double sum_large_floats_vectorized(const float *v, unsigned length, unsigned trials) {

    double result = 0.0f;

    for (int t = 0; t < trials; t++) {

        __m128 cutoff = _mm_set1_ps(100);
        __m128 sum = _mm_setzero_ps();

        float final[4] __attribute__((aligned(16)));

        int i;

        for (i = 0; i+4 <= length; i+=4) {
            //printf("%f %f %f %f\n", v[i], v[i+1], v[i+2], v[i+3]);
            __m128 data = _mm_load_ps(v + i);
            __m128 mask = _mm_cmpge_ps(data, cutoff);
            __m128 masked = _mm_and_ps(mask, data);

            // Update the sum.
            sum = _mm_add_ps(masked, sum);
        }

        // Handle the fringe case.
        for (; i < length; i++) {
            float val = v[i];
            if (val >= 100.0f) {
                result += val;
            }
        }

        // Sum up the sum vector.
        // TODO there are faster ways of doing this! See hadd, etc.
        _mm_store_ps(final, sum);
        result += (final[0] + final[1] + final[2] + final[3]);
    }
    return result;
}

int main(int argc, char **argv) {
    const unsigned LEN = 10000000;
    float *v  = malloc(sizeof(float) * LEN);

    for (int i = 0; i < LEN; i++) {
        v[i] = i+1;
    }

    struct timeval start, end, diff;
    double result;

    gettimeofday(&start, 0);
    result = sum_large_floats(v, LEN, 1);
    gettimeofday(&end, 0);
    timersub(&end, &start, &diff);
    printf("Scalar: %ld.%06ld seconds (result=%f)\n",
            (long)diff.tv_sec, (long)diff.tv_usec,
            (long)result);

    gettimeofday(&start, 0);
    result = sum_large_floats_vectorized(v, LEN, 1);
    gettimeofday(&end, 0);
    timersub(&end, &start, &diff);
    printf("Vectorized: %ld.%06ld seconds (result=%f)\n",
            (long)diff.tv_sec, (long)diff.tv_usec,
            (long)result);
}
