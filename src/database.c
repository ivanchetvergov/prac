#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <zlib.h>

#include "../include/database.h"
#include "../include/student.h"

static uint32_t compute_crc32(STUDENT *students, int count) {
    return crc32(0L, (const Bytef *)students, sizeof(STUDENT) * count);
}

int save_DB(const char *path, DB *db, STUDENT *students, int count) {
    FILE *file = fopen(path, "wb");
    if (!file) {
        perror("error opening file");
        return -1;
    }

    db->num_records = count;
    db->checksum = compute_crc32(students, count);
    db->transaction_id += 1;

    if (fwrite(db, sizeof(DB), 1, file) != 1) {
        perror("error writing database header");
        fclose(file);
        return -2;
    }

    if (fwrite(students, sizeof(STUDENT), count, file) != count) {
        perror("error writing student data");
        fclose(file);
        return -3;
    }

    fclose(file);
    return 0;
}

int load_DB(const char *path, DB *db, STUDENT **students, int *count) {
    FILE *file = fopen(path, "rb");
    if (!file) {
        perror("error opening file");
        return -1;
    }

    if (fread(db, sizeof(DB), 1, file) != 1) {
        perror("error reading database header");
        fclose(file);
        return -2;
    }

    *count = db->num_records;
    *students = malloc(sizeof(STUDENT) * (*count));
    if (!*students) {
        perror("error allocating memory");
        fclose(file);
        return -3;
    }

    if (fread(*students, sizeof(STUDENT), *count, file) != *count) {
        perror("error reading student data");
        fclose(file);
        free(*students);
        return -4;
    }

    uint32_t actual_crc = compute_crc32(*students, *count);
    if (actual_crc != db->checksum) {
        perror("error: checksum mismatch");
        fclose(file);
        free(*students);
        return -5;
    }

    db->transaction_id += 1;
    fclose(file);
    return 0;
}

