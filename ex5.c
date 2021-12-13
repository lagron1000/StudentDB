/******
* Lior Agron
* 208250225
* 01
* ex5
*******/
#define _CRT_SECURE_NO_WARNINGS

#include "ex5.h"

/*
* Function Name: useMenu
* Input: initialized array of courses
* Output: none in paticular
* Function Operation: its a menu
*/
void useMenu(Course courses[]) {
    char option;
    scanf(" %c", &option);
        switch (option) {
        case '0': {
            //?????????????????????????????????????????????????????????
            exitProg(courses);
            exit(1);
        };
        case '1': {
            changeClassesList(courses);
            break;
        }
        case '2': {
            parseAndAdd(courses);
            break;
        }
        case '3': {
            removeStudentInput(courses);
            break;
        }
        case '4': {
            printSorted(courses);
            break;
        }
        case '5': {
            calAndPrintAlls(courses);
            //nextOperation(courses);
            break;
        }
        case '6': {
            printMenu();
            useMenu(courses);
            break;
        }
        default: {
            printf("Error: unrecognized operation.\n");
            break;
        }
        }
    
    nextOperation(courses);
}

/*
* Function Name:printMenu
* Input:no input
* Function Operation: prints out the main menu
*/
void printMenu() {
    printf("Please select an operation:\n\
\t0. Exit.\n\
\t1. Insert or update a class.\n\
\t2. Insert or update a student.\n\
\t3. Remove a student from classes.\n\
\t4. Print a class.\n\
\t5. Print all classes with their computed scores.\n\
\t6. Print the menu.\n");
}

/*
* Function Name:print5Menu
* Function Operation: prints out he secondary manu
*/
void print5Menu() {
    printf("Please select the aggregation method:\n\
\ta. Average Grade.\n\
\tb. Maximal Grade.\n\
\tc. Minimal Grade.\n\
\td. Sum.\n\
\te. Count.\n\
\t0. Return to the main menu.\n");
}

/*
* Function Name: countCourses
* Input: array of courses
* Output: num of courses currently submited by user
* Function Operation: loops through the arra of initialized courses and checks which were submited by the user using the .made boolean
*/
int countCourses(Course courses[]) {
    int count = 0;
    for (int i = 0; i < NUM_OF_COURSES; i++) {
        if (courses[i].made) count++;
    }
    return count;
}

/*
* Function Name:nextOperation
* Function Operation: calls the menu
*/
void nextOperation(Course courses[]) {
    printf("Select the next operation (insert 6 for the entire menu):\n");
    useMenu(courses);
}

/*
* Function Name:exitProg
* Input: array of courses
* Function Operation: iterates over all courses. goes through each courses list and frees all its contents before freeing the courses data itself
*/
void exitProg(Course courses[]) {
    int len = countCourses(courses);
    for (int i = 0; i < len; i++) {
            freeStudentList(courses[i].list);
            free(courses[i].name);
            free(courses[i].id);
    }
}

/*
* Function Name:applyCalc
* Input: array of courses and a pointer to a function
* Function Operation: preformes the requested action upon all of the submited courses
*/
void applyCalc(Course courses[], void (*funcPointer)(Course)) {
    for (int i = 0; i < countCourses(courses); i++) {
        (*funcPointer)(courses[i]);
    }
}

/*
* Function Name:calAndPrintAlls
* Input:array off courses
* Function Operation: chooses which function to point to when sending to the above func "applyCalc"
*/
void calAndPrintAlls(Course courses[]) {
    void (*funcPointer)(Course);
    // self explanatory
    if (!countCourses(courses)) {
        printf("Error: there are no classes.\n");
        return;
    }
    print5Menu();
    char option[MAX_INPUT_LEN] = "";
    scanf(" %c", option);
    // attaches fitting funtion to each choice
    if (!strcmp(option, "a")) {
        funcPointer = &calcAvarage;
        applyCalc(courses, funcPointer);
    }
    else if (!strcmp(option, "b")) {
        funcPointer = &findMax;
        applyCalc(courses, funcPointer);
    }
    else if (!strcmp(option, "c")) {
        funcPointer = &findMin;
        applyCalc(courses, funcPointer);
    }
    else if (!strcmp(option, "d")) {
        funcPointer = &findSum;
        applyCalc(courses, funcPointer);
    }
    else if (!strcmp(option, "e")) {
        funcPointer = &findCount;
        applyCalc(courses, funcPointer);
    }
    else if (!strcmp(option, "0")) {
        nextOperation(courses);
    }
}

/*
* Function Name:calcAvarage
* Input: a single course
* Output: prints the avarage
* Function Operation: counts numm of students while iterating over their grades. dividing the sum of their grades by the counter
*/
void calcAvarage(Course course) {
    int count = 0;
    int sum = 0;
    Student* current = course.list->head;
    while(current) {
        count++;
        sum += atoi(current->data->grade);
        current = current->next;
    }
    if (count) {
        printf("%s %s, %d\n", course.id, course.name, sum / count);
    }
    else printf("Class \"%s %s\" has no students.\n", course.id, course.name);
}

/*
* Function Name:findMax
* Input: a course
* Output: prints maximal grade
* Function Operation: compares each grade to the previous maximal one starting with zero
*/
void findMax(Course course) {
    int max = 0;
    int count = 0;
    Student* current = course.list->head;
    while (current) {
        count++;
        if (atoi(current->data->grade) > max) max = atoi(current->data->grade);
        current = current->next;
    }
    if (count) {
        printf("%s %s, %d\n", course.id, course.name, max);
    }
    else printf("Class \"%s %s\" has no students.\n", course.id, course.name);
}

/*
* Function Name:findMin
* Input: course
* Output: prints min grade
* Function Operation: compares each grade to the previous minimal one starting with the first one
*/
void findMin(Course course) {
    int count = 0;
    Student* current = course.list->head;
    int min = atoi(current->data->grade);
    while (current) {
        count++;
        if (atoi(current->data->grade) < min) min = atoi(current->data->grade);
        current = current->next;
    }
    if (count) {
        printf("%s %s, %d\n", course.id, course.name, min);
    }
    else printf("Class \"%s %s\" has no students.\n", course.id, course.name);
}

/*
* Function Name:findCount
* Input:course
* Output:prints num of students in course
* Function Operation: goes through students from the head of the list till NULL and counts num of iterations
*/
void findCount(Course course) {
    int count = 0;
    Student* current = course.list->head;
    while (current) {
        count++;
        current = current->next;
    }
    if (count) {
        printf("%s %s, %d\n", course.id, course.name, count);
    }
    else printf("Class \"%s %s\" has no students.\n", course.id, course.name);
}

/*
* Function Name:findSum
* Input:course
* Output:prints sum of grades
* Function Operation: sums grades as iterates over all students
*/
void findSum(Course course) {
    int count = 0;
    int sum = 0;
    Student* current = course.list->head;
    while (current) {
        count++;
        sum += atoi(current->data->grade);
        current = current->next;
    }
    if (count) {
        printf("%s %s, %d\n", course.id, course.name, sum);
    }
    else printf("Class \"%s %s\" has no students.\n", course.id, course.name);
}

/*
* Function Name:sortList
* Input:student list
* Function Operation: using the bouble sort algorithm to sort students in alphabetical order (case sensitive)
*/
void sortList(StudentList* list) {
    int switched = 1;
    while (switched) {
        switched = 0;
        Student* current = list->head;
        while (current->next) {
            if (strcmp(current->data->name, current->next->data->name) > 0) {
                switched = 1;
                StudentData* tmp = current->data;
                current->data = current->next->data;
                current->next->data = tmp;
            }
            current = current->next;
        }
    }
}

/*
* Function Name:printSorted
* Input: course array
* Function Operation: once the list is in order, this prints out all its innards
*/
void printSorted(Course courses[]) {
    char input[MAX_INPUT_LEN] ="";
    scanf(" %[^\n]", input);
    for (int i = 0; i < countCourses(courses); i++) {
        if (!strcmp(courses[i].id, input)) {
            Student* studentToPrint = courses[i].list->head;
            if (studentToPrint) {
                sortList(courses[i].list);
                printf("Class \"%s %s\" students:\n", courses[i].id, courses[i].name);
                while (studentToPrint) {
                    printf("%s, %s\n", studentToPrint->data->name, studentToPrint->data->grade);
                    studentToPrint = studentToPrint->next;
                }
            }
            else {
                printf("Class \"%s %s\" has no students.\n", courses[i].id, courses[i].name);
            }
            return;
        }
    }
    printf("Error: invalid class number.\n");
}

/*
* Function Name:removeStudent
* Input: course id, name and courses array
* Function Operation: calling the right functions to make sure input is legal then calls operating functiobs to free student
*/
void removeStudent(char course[MAX_INPUT_LEN], char name[MAX_INPUT_LEN], Course courses[]) {
    for (int i = 0; i < NUM_OF_COURSES; i++) {
        if (courses[i].id) {
            if (!strcmp(courses[i].id, course)) {
                if (isStudentInputLegal("1", name)) {
                    //if (!findAndChange(courses[i].list->head, name, "del")) {}
                    if (freeAStudent(name, courses[i].list, courses[i].list->head)) {
                        printf("Student \"%s\" removed from class \"%s %s\".\n", name, courses[i].id, courses[i].name);
                        return;
                    }
                    else printf("Error: student is not a member of class \"%s %s\".\n", courses[i].id, courses[i].name);
                }
                else { 
                    printf("Error: invalid name, class number or grade.\n");
                    return;
                }
            }
        }
    }
}

/*
* Function Name:removeStudentInput
* Input:courses. recieves course num and srudent name from user
* Function Operation: handles states of legallity
*/
void removeStudentInput(Course courses[]){
    int numOfCourses = countCourses(courses);
    char input[MAX_INPUT_LEN];
    char name[MAX_INPUT_LEN];
    char course[MAX_INPUT_LEN];
    //char test[MAX_INPUT_LEN];
    scanf(" %[^\n]", input);
    //strcpy(test, input);
    int shouldBeRemoved = doesCourseExist(courses, input);
    if (shouldBeRemoved == 1) {
    char* token = strtok(input, ":");
    strcpy(name, token);
    token = strtok(NULL, ", ");
    if (!token){
        printf("Error: invalid name or class number.\n");
        return;
    }
        do {
            if (token) strcpy(course, token);
            removeStudent(course, name, courses);
            token = strtok(NULL, ", ");
        } while (token);
    }
    else if (!shouldBeRemoved) {
        printf("Error: student cannot be removed from all classes.\n");
        return;
    }
    else {
        printf("Error: invalid name or class number.\n");
        return;
    }
}

/*
* Function Name:doesCourseExist
* Input:
* Output:
* Function Operation: iterates through inputed courses nums and checks if student is in the course
*/
int doesCourseExist(Course courses[], char input[MAX_INPUT_LEN]) {
    char tmp[MAX_INPUT_LEN];
    char name[MAX_INPUT_LEN];
    strcpy(tmp, input);
    char* tmpTok = strtok(tmp, ":");
    strcpy(name, tmpTok);
    tmpTok = strtok(NULL, ", ");
    int count = 0;
    int sameCount = 0;
    while (tmpTok) {
        for (int i = 0; i < countCourses(courses); i++) {
            if (isHeInHere(courses[i].list->head, name)) count++;
            if (!strcmp(courses[i].id, tmpTok)) {
                if(isHeInHere(courses[i].list->head, name))
                sameCount++;
            }
        }
        tmpTok = strtok(NULL, ", ");
    }
    if (count == sameCount) return 0;
    if (sameCount < count && sameCount > 0) return 1;
    return 2;
}

/*
* Function Name:isHeInHere
* Input:
* Output:
* Function Operation: iterates over all students in course list and compares to inputted name
*/
int isHeInHere(Student* student, char* name) {
    if (student) {
        if (strcmp(student->data->name, name)) {
            return  isHeInHere(student->next, name);
        }
        else return 1;
    }
    return 0;
}

/*
* Function Name:addNewCourse
* Input:
* Output:
* Function Operation: allocates memory space for all proporties of course then copys value from inpit
*/
void addNewCourse(char* token, Course course[], int i) {
    Course* newCourse = (Course*)malloc(sizeof(Course));
    if (!newCourse) exit(0);
    newCourse->id = (char*)malloc((strlen(token) * sizeof(char) + 1));
    if (!newCourse->id) exit(0);
    strcpy(newCourse->id, token);
    token = strtok(NULL, "\0");
    newCourse->name = (char*)malloc((strlen(token) * sizeof(char) + 1 ));
    if (!newCourse->name) exit(0);
    strcpy(newCourse->name, token);
    addStudentList(newCourse);
    newCourse->made = 1;
    course[i] = *newCourse;
    free(newCourse);
    return;
}

/*
* Function Name:checkForCourses
* Input:
* Output:
* Function Operation: makes sure all inputed courses exist
*/
int checkForCourses(Course courses[], char* input) {
    char tmp[MAX_INPUT_LEN];
    //char name[MAX_INPUT_LEN];
    strcpy(tmp, input);
    char* tmpTok = strtok(tmp, ":");
    //strcpy(name, tmpTok);
    tmpTok = strtok(NULL, ", ");
    int coursesInputed = 0;
    int coursesConfirmed = 0;
    while (tmpTok) {
        coursesInputed++;
        int numOfCourses = countCourses(courses);
        for (int i = 0; i < numOfCourses; i++) {
            if (!strcmp(courses[i].id, tmpTok)) {
                coursesConfirmed++;
            }
        }
        tmpTok = strtok(NULL, ", ");
        tmpTok = strtok(NULL, "; ,");

    }
    if (coursesConfirmed == coursesInputed) return 1;
    return 0;
}

/*
* Function Name:parseAndAdd
* Input:
* Output:
* Function Operation: parsing the inputted text then adding its contents to the fitting list in the array
*/
void parseAndAdd(Course courses[]) {
    //Yair Koskas: 12345, 100; 89210, 90
    char input[MAX_INPUT_LEN];
    char name[MAX_INPUT_LEN];
    char course[MAX_INPUT_LEN];
    scanf(" %[^\n]", input);
    if (checkForCourses(courses, input)) {
        char* token = strtok(input, ":");
        strcpy(name, token);
        token = strtok(NULL, ", ");
        do {
            if (token)
                strcpy(course, token);
            // look for courses 
            token = strtok(NULL, " ;");
            addGrade(token, course, name, courses);
            token = strtok(NULL, ", ");
        } while (token);
    }
    else printf("Error: invalid name, class number or grade.\n");
}

/*
* Function Name:addGrade
* Input:
* Output:
* Function Operation: looks for student in appropriate list. changes his grade if found, adds him as a new student if not
*/
void addGrade(char* gradeToken, char course[MAX_INPUT_LEN], char name[MAX_INPUT_LEN], Course courses[]) {
    for (int i = 0; i < NUM_OF_COURSES; i++) {
        if (courses[i].id) {
            if (!strcmp(courses[i].id, course)) {
                if (isStudentInputLegal(gradeToken, name)) {
                    if (!findAndChange(courses[i].list->head, name, gradeToken)) {
                        addNewStudent(courses[i].list, addNewStudentData(name, gradeToken));
                        printf("Student \"%s\" added to class \"%s %s\" with grade %s.\n", name, courses[i].id, courses[i].name, gradeToken);
                        return;
                    }
                    else {
                        printf("Student \"%s\" updated on class \"%s %s\" with grade %s.\n", name, courses[i].id, courses[i].name, gradeToken);
                        return;
                    }
                }
            }
        }
    }
    printf("Error: invalid name, class number or grade.\n");
    return;
}

/*
* Function Name:isStudentInputLegal
* Input:
* Output:
* Function Operation: reviews legallity of input based on task standarts
*/
int isStudentInputLegal(char* gradeToken, char name[MAX_INPUT_LEN]) {
    int nameLength = strlen(name);
    // try \0 instead of null when everything else is chill
    while (*gradeToken != '\0') {
        if (!isdigit(*gradeToken)) return 0;
        gradeToken++;
    }
    int gradeVal = atoi(gradeToken);
    if (gradeVal > 100 || gradeVal < 0) return 0;
    if (nameLength > MAX_STUD_NAME_LEN || nameLength < MIN_STUD_NAME_LEN) return 0;
    for (int i = 0; i < nameLength; i++) {
        if (!(isalpha(name[i]) || isspace(name[i]))) return 0;
    }
    return 1;
}

// look for sttdenit in a courses list. if one is not found, then one shall be added to course.
/*
* Function Name:
* Input:
* Output:
* Function Operation: checks weather or not student is in list
*/
int findAndChange(Student* student, char name[MAX_INPUT_LEN], char* grade) {
    int found = 0;
    if (student) {
        //while (student->next) {
            if (strcmp(student->data->name, name)) {
                return findAndChange(student->next, name, grade);
            }
            else {
                //if (!strcmp(grade, "del")) {
                //    //freeAStudent(student);
                //}
                strcpy(student->data->grade, grade);
                return found = 1;
            }
        //}
    }
    return found;
}

/*
* Function Name:addNewStudentData
* Input:
* Output:
* Function Operation:allocates memory space for student details and copys the values into the newly allocated spaces
*/
StudentData* addNewStudentData(char* name, char* grade) {
    StudentData* newStudent = (StudentData*)malloc(sizeof(StudentData));
    if (!newStudent) return NULL;
    newStudent->name = (char*)malloc((strlen(name) * sizeof(char) + 1));
    if (!newStudent->name) return NULL;
    strcpy(newStudent->name, name);
    newStudent->grade =(char*) malloc(strlen(grade) * sizeof(char) + 1);
    if (!newStudent->grade) return NULL;
    strcpy(newStudent->grade, grade);
    return newStudent;
}

/*
* Function Name:addNewStudent
* Input:
* Output:
* Function Operation:iterates over the list. adds student at the tail then changes list tail to point at it.
*/
void addNewStudent(StudentList* list, StudentData* data) {
    Student* student = (Student*)malloc(sizeof(Student));
    //what should i return?
    if (!student) return;
    student->next = NULL;
    student->data = data;
    if (!list->head) {
        list->head = student;
        list->tail = student;
    }
    else {
        list->tail->next = student;
        list->tail = student;
    }
}

/*
* Function Name:addStudentList
* Input:
* Output:
* Function Operation:initializes new student list for a course
*/
void addStudentList(Course* course) {
    course->list = (StudentList*)malloc(sizeof(StudentList));
    if (!course->list) return;
    course->list->head = NULL;
    course->list->tail = course->list->head;
    return;
}

/*
* Function Name:freeStudentData
* Input:
* Output:
* Function Operation: frees all contents of a students data and the whole data boundle afterwards 
*/
void freeStudentData(StudentData* data){
    if (data) {
        free(data->name);
        free(data->grade);
        free(data);
    }
}

/*
* Function Name:freeStudents
* Input:
* Output:
* Function Operation:frees all students data boundles before freeing all student items
*/
void freeStudents(Student* student) {
    if (student) {
        freeStudentData(student->data);
        freeStudents(student->next);
        free(student);
    }
}

/*
* Function Name:freeStudentList
* Input:
* Output:
* Function Operation:goes to free all students and their data from a list before freeing the list itself
*/
void freeStudentList(StudentList* list) {
    freeStudents(list->head);
    free(list);
}

/*
* Function Name:freeAStudent
* Input:
* Output:
* Function Operation: checking if the next student is the one meant for deletion, if so, saves the student after him in a tmp so that when he is
* deleted, the thet came before him could still point at the student that comes after him
*/
int freeAStudent(char* name, StudentList* list, Student* student) {
    if (!strcmp(list->head->data->name, name)) {
        Student* tmp = list->head->next;
        freeStudentData(list->head->data);
        free(list->head);
        list->head = tmp;
        return 1;
    }
    // if its my next than change my next to its next
    if (!strcmp(student->next->data->name, name)) {
        Student *tmp = student->next->next;
        freeStudentData(student->next->data);
        free(student->next);
        student->next = tmp;
        return 1;
    }
    else {
        if (student->next) {
            return freeAStudent(name, list, student->next);
        }
        else return 0;
    }
}

/*
* Function Name:testInput
* Input:
* Output:
* Function Operation: checks legallity of input for adding/updating a course
*/
int testInput(char input[MAX_INPUT_LEN]){
    char tmp[MAX_INPUT_LEN];
    strcpy(tmp, input);
    int isBad = 0;
    char* tmpTok = strtok(tmp, " ");
    if (strlen(tmpTok) != COURSE_ID_LEN) isBad = 1;
    tmpTok = strtok(NULL, "\0");
    if (!tmpTok) return 1;
    int nameLen = strlen(tmpTok);
    if (nameLen > MAX_COURSE_NAME_LEN || nameLen < MIN_STUD_NAME_LEN || !tmpTok) isBad = 1;
    while (*tmpTok != '\0') {
        if (!isalnum(*tmpTok) && !isspace(*tmpTok)) isBad = 1;
        tmpTok++;
    }
    return isBad;
}

/*
* Function Name:updateCourseName
* Input:
* Output:
* Function Operation: freeing the previous names memory space and allocating new space fitting the new name
*/
Course updateCourseName(Course course, char* name) {
    //printf("DEBUG name pre free: %s.\n", course.name);

    free(course.name);
    //printf("DEBUG name post free pre re: %s.\n", course.name);

    course.name = (char*)malloc((strlen(name) * sizeof(char) + 1));
    if (!course.name) return course;
    strcpy(course.name, name);
    //printf("DEBUG name post re: %s.\n", course.name);

    return course;
}

/*
* Function Name:changeClassesList
* Input:
* Output:
* Function Operation:if input is legal, will add\update the courses array
*/
void changeClassesList(Course courses[]) {
    int wasChanged = 0;
    char input[MAX_INPUT_LEN];
    scanf(" %[^\n]", input);
    if(testInput(input)){
        printf("Error: invalid class number or name.\n");
        return;
    }
    //addressing course id
    char* token = strtok(input, " ");
    for (int i = 0; i < countCourses(courses); i++) {
        if (!strcmp(courses[i].id, token)) {
            //printf("DEBUG token: %s.\n", token);

            char* newName = strtok(NULL, "\0");
            //printf("DEBUG newNAme: %s.\n", newName);

            courses[i] = updateCourseName(courses[i], newName);
            wasChanged = 1;
            printf("Class \"%s %s\" updated.\n", courses[i].id, courses[i].name);
            break;
        }
    }
    if (!wasChanged) {
        for (int i = 0; i <= NUM_OF_COURSES; i++) {
            if (!courses[i].id) {
                addNewCourse(token, courses, i);
                wasChanged = 1;
                printf("Class \"%s %s\" added.\n", courses[i].id, courses[i].name);
                break;
            }
        }
    }
    if (!wasChanged) {
        printf("Unfortunately, there is no room for more classes.\n");
    }
    //addressing course name
    token = strtok(NULL, "\0");
}