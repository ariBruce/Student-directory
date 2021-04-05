#include <iostream>

void fill_student_info();
int print_menu();

int main() {

	int close_program = 0; //used in oreder to close program

	std::cout << "Reading Student info file......" << std::endl;
	std::cout << "Reading Course info file......" << std::endl;

	fill_student_info(); //read relavent txt files

	std::cout << "Data Loaded." << std::endl;

	while (close_program == 0) {
		close_program = print_menu();
	}

}