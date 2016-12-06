
#include <stdio.h>
#include <sys/time.h>

// For Intel intrinsics.
#include <immintrin.h>

// Sums all the values in v which are greater than 10.
double sum_large_floats(const float *v, unsigned length, unsigned trials) {
    double result = 0.0f;
    for (unsigned t = 0; t < trials; t++) {
        for (unsigned i = 0; i < length; i++) {
            float val = v[i];
            if (val >= 10.0f) {
                result += val;
            }
        }
    }
    return result;
}

// Sums all the values in v which are greater than 10.
double sum_large_floats_vectorized(const float *v, unsigned length, unsigned trials) {

    double result = 0.0f;

    for (unsigned t = 0; t < trials; t++) {

        __m128 cutoff = _mm_set1_ps(10.0f);
        __m128 sum = _mm_setzero_ps();

        float final[4] __attribute__((aligned(16)));

        unsigned i;

        for (i = 0; i+4 <= length; i+=4) {
            __m128 data = _mm_loadu_ps(v + i);
            __m128 mask = _mm_cmpge_ps(data, cutoff);
            __m128 masked = _mm_and_ps(mask, data);

            // Update the sum.
            sum = _mm_add_ps(sum, masked);
        }

        // Handle the fringe case.
        for (; i < length; i++) {
            float val = v[i];
            if (val >= 10.0f) {
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
    const unsigned LEN = 1000000;
    float *v  = malloc(sizeof(float) * LEN);

    // Generate some bogus data.
    for (int i = 0; i < LEN; i++) {
        v[i] = (float)((i+1) % 20);
    }

    // For timing.
    struct timeval start, end, diff;
    double result;

    gettimeofday(&start, 0);
    result = sum_large_floats(v, LEN, 100);
    gettimeofday(&end, 0);
    timersub(&end, &start, &diff);
    printf("Scalar: %ld.%06ld seconds (result=%f)\n",
            (long)diff.tv_sec, (long)diff.tv_usec,
            result);

    gettimeofday(&start, 0);
    result = sum_large_floats_vectorized(v, LEN, 100);
    gettimeofday(&end, 0);
    timersub(&end, &start, &diff);
    printf("Vectorized: %ld.%06ld seconds (result=%f)\n",
            (long)diff.tv_sec, (long)diff.tv_usec,
            result);
}
