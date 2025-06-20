#ifndef DATABASE_H
#define DATABASE_H

#include <stdint.h>
#include "student.h"

typedef struct {
    char signature[4]; // first 4 letters of surname
    uint32_t transaction_id; // num of trans 
    uint32_t num_records; // num structures
    uint32_t checksum;
} DB;

int save_DB(const char* path, DB* db, STUDENT* students, int count);

int load_DB(const char* path, DB* db, STUDENT** students, int* count);

#endif
