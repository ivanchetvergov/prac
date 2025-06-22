#pragma once

#include <student.h>
#include <database.h>

#define MAX_STUDENTS 50

extern DB header;
extern STUDENT students[MAX_STUDENTS];
extern int student_count;

STUDENT gen_new();
void sort();


