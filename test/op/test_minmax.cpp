/*
 * Unit Testing for VAccel Min-Max Operation
 *
 * The code below performs unit testing for the VAccel Min-Max operation.
 * It includes two test cases: one for the standard Min-Max operation and
 * another for the generic version using vaccel_genop. Both test cases read
 * input data from a CSV file, perform the Min-Max operation, and print the
 * results along with the execution time.
 *
 */


#include "../catch2/catch.hpp"

#include <atomic>

using atomic_int = std::atomic<int>;
using atomic_uint = std::atomic<unsigned int>;

extern "C" {

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <vaccel.h>

#include "minmax.h"
#include "session.h"
}

TEST_CASE("due to vaccel_arg change - TODO: redo these tests")
{
    REQUIRE(1==1);
}

// #define timespec_usec(t) ((double)(t).tv_nsec / 10e3 + (double)(t).tv_sec * 10e6)
// #define time_diff_usec(t0, t1) (timespec_usec((t1)) - timespec_usec((t0)))

// TEST_CASE("min_max", "[minmax]")
// {

//     const char* path = "../../examples/input/input_262144.csv";
//     double min, max;
//     int ret;

//     int ndata = 262144;
//     REQUIRE(ndata > 0);

//     double* indata = (double*)malloc(ndata * sizeof(double));
//     REQUIRE(indata != nullptr);

//     FILE* fp = fopen(path, "r");
//     REQUIRE(fp != nullptr);

//     for (int i = 0; i < ndata; ++i) {
//         REQUIRE(fscanf(fp, "%lf\n", &indata[i]) == 1);
//     }

//     double* outdata = (double*)malloc(ndata * sizeof(double));
//     REQUIRE(outdata != nullptr);

//     int low_threshold = 0;
//     int high_threshold = 4000;

//     struct vaccel_session session;
//     REQUIRE(vaccel_sess_init(&session, 0) == VACCEL_OK);

//     struct timespec t0, t1;
//     clock_gettime(CLOCK_MONOTONIC_RAW, &t0);

//     ret = vaccel_minmax(&session, indata, ndata, low_threshold, high_threshold,
//         outdata, &min, &max);

//     clock_gettime(CLOCK_MONOTONIC_RAW, &t1);
//     REQUIRE(ret == VACCEL_OK);

//     fprintf(stdout, "min: %lf max: %lf Execution time: %lf msec\n", min, max,
//         (double)(t1.tv_sec - t0.tv_sec) * 1000.0 + (double)(t1.tv_nsec - t0.tv_nsec) / 1.0e6);

//     vaccel_sess_free(&session);
//     free(outdata);
//     free(indata);
// }

// TEST_CASE("min_max_generic", "[minmax]")
// {

//     const char* path = "../../examples/input/input_262144.csv";
//     double min, max;
//     int ret;

//     int ndata = 262144;
//     REQUIRE(ndata > 0);

//     double* indata = (double*)malloc(ndata * sizeof(double));
//     REQUIRE(indata != nullptr);

//     FILE* fp = fopen(path, "r");
//     REQUIRE(fp != nullptr);

//     for (int i = 0; i < ndata; ++i) {
//         REQUIRE(fscanf(fp, "%lf\n", &indata[i]) == 1);
//     }

//     double* outdata = (double*)malloc(ndata * sizeof(double));
//     REQUIRE(outdata != nullptr);

//     int low_threshold = 0;
//     int high_threshold = 4000;

//     struct vaccel_session session;
//     REQUIRE(vaccel_sess_init(&session, 0) == VACCEL_OK);

//     struct timespec t0, t1;

//     enum vaccel_op_type op_type = VACCEL_MINMAX;
//     struct vaccel_arg read[5] = {
//         { .size = sizeof(enum vaccel_op_type), .buf = &op_type },
//         { .size = static_cast<uint32_t>(ndata * sizeof(double)), .buf = indata },
//         { .size = sizeof(int), .buf = &ndata },
//         { .size = sizeof(int), .buf = &low_threshold },
//         { .size = sizeof(int), .buf = &high_threshold },
//     };
//     struct vaccel_arg write[3] = {
//         { .size = static_cast<uint32_t>(ndata * sizeof(double)), .buf = outdata },
//         { .size = sizeof(double), .buf = &min },
//         { .size = sizeof(double), .buf = &max },
//     };
//     clock_gettime(CLOCK_MONOTONIC_RAW, &t0);

//     ret = vaccel_genop(&session, &read[0], 5, &write[0], 3);

//     clock_gettime(CLOCK_MONOTONIC_RAW, &t1);
//     REQUIRE(ret == VACCEL_OK);

//     fprintf(stdout, "min: %lf max: %lf Execution time: %lf msec\n", min, max,
//         (double)(t1.tv_sec - t0.tv_sec) * 1000.0 + (double)(t1.tv_nsec - t0.tv_nsec) / 1.0e6);

//     vaccel_sess_free(&session);
//     free(outdata);
//     free(indata);
// }
