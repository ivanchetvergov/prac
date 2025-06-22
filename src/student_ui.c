#include <ncurses.h>
#include <string.h>
#include <student.h>
#include <database.h>
#include <student_backend.h>
#include <locale.h>

#define MAX_STUDENTS 50

DB header;
const char* DBpath = "/home/ivanchetvergov/prac/assets/students.db";
STUDENT students[MAX_STUDENTS]; // arr of stud
int student_count = 0;

void input_student() {
  STUDENT s; // new stud
    
  clear(); // clear screen
  mvprintw(1, 2, "input new student:");

  mvprintw(3, 4, "surname and initials: ");
  echo(); // show user input
  getnstr(s.name, MAX_NAME_LEN - 1); // get name

  mvprintw(5, 4, "number of group: ");
  getnstr(s.group, MAX_GROUP_LEN - 1); // get group

  mvprintw(7, 4, "enter 6 grades: ");

  for (int i = 0; i < MAX_MARKS; ++i) {
    mvprintw(8 + i, 6, " %d: ", i + 1);
	  scanw("%d", &s.marks[i]); // read marks
  }

  students[student_count++] = s; // add to arr 

  mvprintw(19, 2, "added! press any button...");
  noecho(); // hide user input 
  getch(); // read symb
}

void draw_student_table() {
  clear(); // clear screen
  mvprintw(1, 2, "MENU:");
  mvprintw(2, 2, "table of students:");
  mvprintw(3, 2, "  idx | surname          | group          | grades");

  for (int i = 0; i < student_count; ++i) {
    mvprintw(5 + i, 2, "  %-3d | %-16s | %-14s | ", i + 1,
    students[i].name, students[i].group); // draw stud
    
    for (int j = 0; j < MAX_MARKS; ++j) {
      printw("%d ", students[i].marks[j]); // draw his marks
    }
  }

  mvprintw(7 + student_count, 2, "press any key to return...");
  refresh(); // 
  getch();
}

void run_ui() {
  //setlocale(LC_ALL, "");
  initscr(); // make window
  cbreak(); // off buff. can input wout enter
  noecho(); // hide input
  keypad(stdscr, TRUE); // special keys

  int choice;
  while (true) {
    clear(); 
    mvprintw(1, 2, "menu:");
    mvprintw(3, 4, "1. add student");
    mvprintw(4, 4, "2. show students");
    mvprintw(5, 4, "3. load from db");
    mvprintw(6, 4, "4. sort by avg grade");
    mvprintw(7, 4, "5. gen n new users");
    mvprintw(8, 4, "6. exit");

    mvprintw(9, 2, "choice: ");
    echo();
    scanw("%d", &choice);
    noecho();

    if (choice == 1) input_student();
    else if (choice == 2) draw_student_table();
    else if (choice == 3) {
      STUDENT *loaded_students = NULL;
      int loaded_count = 0;

      int res = load_DB(DBpath, &header, &loaded_students, &loaded_count);

      if (res == 0) {
        memcpy(students, loaded_students, sizeof(STUDENT) * loaded_count);
        student_count = loaded_count;
        mvprintw(10, 2, "loaded %d students!", student_count);
      } else {
        mvprintw(10, 2, "error loading from db!");
      }
    }

    else if (choice == 4) {
      sort(); 
      mvprintw(10, 2, "sorted by average grade!");
    }  
    
    else if(choice == 5){
      mvprintw(10, 2, "enter n: ");
      int n;
      echo();
      scanw("%d", &n);
      if (n > MAX_STUDENTS - student_count) break;
      if (n >= 1){
        for (int i = 0; i < n; ++i){
          students[student_count++] = gen_new();
        }
        mvprintw(11, 2, "gen is done!");
      }
    }

    else if (choice == 6) break;

    refresh(); // update screen
    getch(); // input
  }

  clear();
  mvprintw(9, 2, "save data to db? [Y/n]");
  mvprintw(10, 2, "your choice: ");
    
  char c;
  echo();
  scanw(" %c", &c); 
  noecho();

  if (c == 'Y' || c == 'y') {
    int res = save_DB(DBpath, &header, students, student_count);
    if (res == 0) {
      mvprintw(11, 2, "saved successfully!");
    } else mvprintw(11, 2, "error while saving!");
  } else mvprintw(11, 2, "save cancelled.");

  refresh();
  getch();
  endwin(); // close window
}
