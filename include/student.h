#ifndef STUDENT_H
#define STUDENT_H

#define MAX_NAME_LEN 50
#define MAX_GROUP_LEN 24
#define MAX_MARKS 6

typedef struct {
    char name[MAX_NAME_LEN];   
    char group[MAX_GROUP_LEN];
    int marks[MAX_MARKS];
    int marks_count;
} STUDENT;

#endif
