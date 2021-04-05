#include <iostream>
#include <string>

void delete_student();
void add_course_to_student();
void print_student();
void print_student_avg();
void print_all_students();
void print_avg_for_all_students();
void erase_all_students();
void exit_program();
void new_student_addition();


int print_menu() {

	std::string add = "Add student";
	std::string delete_the_student = "Delete student";
	std::string add_course = "Add course to student";
	std::string print_single = "Print student";
	std::string print_all = "Print all students";
	std::string print_avg = "Print average for student";
	std::string print_avg_for_all = "Print average of all students";
	std::string reset = "Reset";
	std::string exit = "Exit";
	int choice; //used to form choice

	//print main options screen
	std::cout << "1) " << add << std::endl;
	std::cout << "2) " << delete_the_student << std::endl;
	std::cout << "3) " << add_course << std::endl;
	std::cout << "4) " << print_single << std::endl;
	std::cout << "5) " << print_avg << std::endl;
	std::cout << "6) " << print_all << std::endl;
	std::cout << "7) " << print_avg_for_all << std::endl;
	std::cout << "8) " << reset << std::endl;
	std::cout << "0) " << exit << std::endl;
	std::cout << "choose: " << std::endl;

	std::cin >> choice;

	switch (choice) { //act based on case
	case 1:
		new_student_addition(); //function to add new student
		return 0;
	case 2:
		delete_student(); //function to delete student
		return 0;
	case 3:
		add_course_to_student(); //function to add new course
		return 0;
	case 4:
		print_student(); //function to print student info
		return 0;
	case 5:
		print_student_avg(); //function to print student avg
		return 0;
	case 6:
		print_all_students(); //function to print all student's and courses
		return 0;
	case 7:
		print_avg_for_all_students(); //function to avg of all students
		return 0;
	case 8:
		erase_all_students(); //erase all students
		return 0;
	case 0:
		exit_program(); //exit function
		return -1;
	default:
		print_menu();
	}
	return 0;
}