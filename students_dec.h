#pragma once
#ifndef STUDENTS_DEC
#define STUDENTS_DEC

const int max_name_Length = 10;
const int Id_length = 9;
const int course_length = 5;
const int grade_length = 3;
std::string error = "ERROR: NO STUDENT ";

struct student {
	char Name[max_name_Length + 1];
	char Id[Id_length + 1];
	int Num_Of_courses;
	struct course* list;
};

struct course {
	int C_number;
	int G_number;
};

struct student_manager {
	int num_of_students;
	student *dynamic_num;
}the_Only_one;

#endif // !STUDENTS_DEC
