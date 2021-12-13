/******
* Lior Agron
* 208250225
* 01
* ex5
*******/
#include "ex5.h"

int main() {
	Course courses[NUM_OF_COURSES];

	for (int i = 0; i < NUM_OF_COURSES; i++) {
        Course newCourse = {.id = NULL, .name = NULL};
		courses[i] = newCourse;
	}
	printMenu();
	useMenu(courses);
}
