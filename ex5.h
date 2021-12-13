/******
* Lior Agron
* 208250225
* 01
* ex5
*******/
#ifndef MAIN_C_EX5_H
#define MAIN_C_EX5_H
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

#define _CRT_SECURE_NO_WARNINGS
#define NUM_OF_COURSES 5
#define MAX_COURSE_NAME_LEN 30
#define MIN_COURSE_NAME_LEN 1
#define COURSE_ID_LEN 5
#define MAX_INPUT_LEN 200
#define MAX_STUD_NAME_LEN 20
#define MIN_STUD_NAME_LEN 1


typedef struct {
    char* name;
    char* grade;
}StudentData;

typedef struct Student {
    StudentData* data;
    struct Student* next;
}Student;

typedef struct {
    Student* head, * tail;
}StudentList;

typedef struct {
    char* id;
    char* name;
    StudentList* list;
    int made;
}Course;


void printMenu();
void useMenu();
void changeClassesList(Course courses[]);
void nextOperation(Course courses[]);
void addNewCourse(char* token, Course course[], int i);
int checkForCourses(Course courses[], char* input);
StudentData* addNewStudentData(char* name, char* grade);
void addNewStudent(StudentList* list, StudentData* data);
void addStudentList(Course* course);
void freeStudentData(StudentData* data);
void freeStudents(Student* student);
void freeStudentList(StudentList* list);
void exitProg(Course courses[]);
int testInput(char input[200]);
void parseAndAdd(Course courses[]);
//void submitStudent();
void addGrade(char* gradeToken, char course[200], char name[200], Course courses[]);
int findAndChange(Student* student, char name[200], char* grade);
int isStudentInputLegal(char* gradeToken, char name[200]);
void removeStudentInput(Course courses[]);
void removeStudent(char course[200], char name[200], Course courses[]);
int freeAStudent(char* name, StudentList* list, Student* student);
int doesCourseExist(Course courses[], char* tmpTok);
int countCourses(Course courses[]);
int isHeInHere(Student* student, char* name);
void printSorted(Course courses[]);
void sortList(StudentList* list);
void calAndPrintAlls(Course courses[]);
void print5Menu();
void applyCalc(Course courses[], void (*funcPointer)(Course));
void calcAvarage(Course course);
void findMax(Course course);
void findMin(Course course);
void findCount(Course course);
void findSum(Course course);
Course updateCourseName(Course course, char* name);

#endif //MAIN_C_EX5_H