#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>    
#include <student_backend.h>

static void gen_group(char* buffer, size_t size){
  const char* institutes[] = {
      "ИКНК", "ФИЗИМЕХ", "ИСИ", "ГУ", "ИММИТ", "ИЭТ", "ИПМЭИТ", "ИСИТ"
  };

  int inst_count = sizeof(institutes) / sizeof(institutes[0]);

  srand(time(NULL));
  int id = rand() % inst_count;
  int group_num = 100 + rand() % 400;

  snprintf(buffer, size, "%s-%d", institutes[id], group_num);

}

const char* cmd = "python3 /home/ivanchetvergov/prac/scripts/random_name.py";
STUDENT gen_new() {
  STUDENT s;
  FILE *fp = popen(cmd, "r");

  if (!fp || !fgets(s.name, MAX_NAME_LEN, fp)) {
    pclose(fp);
    snprintf(s.name, MAX_NAME_LEN, "Иванов Иван");
  } else {
    s.name[strcspn(s.name, "\n")] = 0;
    pclose(fp);
  }

  gen_group(s.group, MAX_GROUP_LEN);

  for (int i = 0; i < MAX_MARKS; ++i)
    s.marks[i] = 3 + rand() % 3; 

  s.marks_count = MAX_MARKS;
  return s;
}

static double avg_grade(int index){
  int sumn = 0;

  for (int j = 0; j < MAX_MARKS; ++j){
    sumn += students[index].marks[j];
  }

  if (students[index].marks_count == 0) return 0.0;

  return (double)sumn / MAX_MARKS;
}

// regular bubble sort O(n^2)
void sort(){
  for (int i = 0; i < student_count; ++i){
    for (int j = 0; j < student_count; ++j){
      if (avg_grade(j) < avg_grade(j + 1)){
        STUDENT temp = students[j];
        students[j] = students[j + 1];
        students[j + 1] = temp;
      }
    }
  }
}

