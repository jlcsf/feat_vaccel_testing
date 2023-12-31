/*
 * TensorFlow Model Test
 *
 * The code below tests TensorFlow model handling using vAccel.
 *
 */

#include "../catch2/catch.hpp"

#include <atomic>

using atomic_int = std::atomic<int>;
using atomic_uint = std::atomic<unsigned int>;

extern "C" {
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "session.h"
#include "tf_model.h"
#include <vaccel.h>

static unsigned char* read_file(const char* path, size_t* len)
{
    struct stat buffer;
    int status, fd;

    fd = open(path, O_RDONLY);
    if (fd < 0) {
        perror("Could not open file");
        return NULL;
    }

    status = fstat(fd, &buffer);
    if (status < 0) {
        perror("Could not stat file");
        return NULL;
    }

    unsigned char* buff = (unsigned char*)malloc(buffer.st_size);
    if (!buff) {
        close(fd);
        perror("malloc");
        return NULL;
    }

    size_t bytes = buffer.st_size;
    ssize_t ptr = 0;
    while (bytes) {
        ssize_t ret = read(fd, &buff[ptr], bytes);
        if (ret < 0) {
            perror("read");
            free(buff);
            close(fd);
            return NULL;
        }

        ptr += ret;
        bytes -= ret;
    }

    close(fd);

    *len = ptr;
    return buff;
}
}

TEST_CASE("tf_model")
{
    struct vaccel_tf_model model;
    struct vaccel_session sess;
    const char* model_path = "../../examples/models/tf/lstm2/saved_model.pb";

    int ret = vaccel_tf_model_new(&model, model_path);
    REQUIRE(ret == VACCEL_OK);

    ret = vaccel_sess_init(&sess, 0);
    REQUIRE(ret == VACCEL_OK);

    ret = vaccel_sess_register(&sess, model.resource);
    REQUIRE(ret == VACCEL_OK);

    struct vaccel_tf_model model2;
    size_t len = 0;
    unsigned char* buff = read_file(model_path, &len);
    REQUIRE(buff);

    ret = vaccel_tf_model_new_from_buffer(&model2, buff, len);
    REQUIRE(ret == VACCEL_OK);

    ret = vaccel_sess_register(&sess, model2.resource);
    REQUIRE(ret == VACCEL_OK);

    ret = vaccel_sess_unregister(&sess, model.resource);
    REQUIRE(ret == VACCEL_OK);

    ret = vaccel_sess_unregister(&sess, model2.resource);
    REQUIRE(ret == VACCEL_OK);

    ret = vaccel_tf_model_destroy(&model);
    REQUIRE(ret == VACCEL_OK);

    ret = vaccel_tf_model_destroy(&model2);
    REQUIRE(ret == VACCEL_OK);

    ret = vaccel_sess_free(&sess);
    REQUIRE(ret == VACCEL_OK);

    free(buff);
}
