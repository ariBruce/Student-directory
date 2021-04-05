#include <iostream>
#include <stdio.h>
#include <string>
#include <string.h>
#include "students_dec.h"

void swap_when_equal(student temp, int problem_id, int increase_checker) {
	if (the_Only_one.dynamic_num[problem_id].Id[increase_checker] > the_Only_one.dynamic_num[problem_id + 1].Id[increase_checker]) { //swap numbers if need be
		temp = the_Only_one.dynamic_num[problem_id]; //swap next num 
		the_Only_one.dynamic_num[problem_id] = the_Only_one.dynamic_num[problem_id + 1];
		the_Only_one.dynamic_num[problem_id + 1] = temp;
	}
	else if (the_Only_one.dynamic_num[problem_id].Id[increase_checker] == the_Only_one.dynamic_num[problem_id + 1].Id[increase_checker]) {
		increase_checker++; //check next num if need be
		swap_when_equal(temp, problem_id, increase_checker); //recursion for function check
	}
}

void put_students_in_order() { //put the list into the right order with bubble sortin of structs

	student temp;
	int increase_checker = 1;

	for (int i = 0; i < the_Only_one.num_of_students - 1; i++) //go over whole list enough times
	{
		for (int j = 0; j < (the_Only_one.num_of_students - 1 - i); j++) { //go over whole list
			if (the_Only_one.dynamic_num[j].Id[0] > the_Only_one.dynamic_num[j + 1].Id[0]) // if id num is in wrong order swap
			{
				temp = the_Only_one.dynamic_num[j];
				the_Only_one.dynamic_num[j] = the_Only_one.dynamic_num[j + 1];
				the_Only_one.dynamic_num[j + 1] = temp;
			}
			if (the_Only_one.dynamic_num[j].Id[0] == the_Only_one.dynamic_num[j + 1].Id[0]) { //if need more comparason
				temp = the_Only_one.dynamic_num[j];
				swap_when_equal(temp, j, increase_checker);
			}
		}
	}

}

bool read_Line(FILE *IDinfo, char idn[Id_length + 2], char name[max_name_Length + 2], int counter) {

	for (int i = 0; i < 10; i++) {
		fread(&idn[i], sizeof(char), 1, IDinfo); //read line of txt file and insert id
		if (idn[i] == ' ' || idn[i] == (char)0) { //move to name
			idn[i] = '\0';
			for (int j = 0; j < 10; j++) { //read line of txt file and insert name
				fread(&name[j], sizeof(char), 1, IDinfo); //read line of txt file and insert name
				if (name[j] == '\n' || name[i] == (char)0) {
					name[j] = '\0';
					break;
				}
			}
			break;
		}
	}
	if (idn[0] == (char)0) { // if empty you reached the end of the page
		return false;
	}

	for (int i = 0; i < max_name_Length + 1; i++) { //insert all names into dynamic array
		if (name[i] == (char)0) {
			the_Only_one.dynamic_num[counter].Name[i] = '\0';//clear the rest of the space and finish insursion
			i = max_name_Length + 1;
			the_Only_one.dynamic_num[counter].Num_Of_courses = 0;
			continue;
		}
		the_Only_one.dynamic_num[counter].Name[i] = name[i];
	}
	for (int i = 0; i < Id_length + 1; i++) { //insert all ids into dynamic array
		if (idn[i] == (char)0) {
			the_Only_one.dynamic_num[counter].Id[i] = '\0'; //clear the rest of the space and finish insursion
			i = Id_length;
			the_Only_one.dynamic_num[counter].Num_Of_courses = 0;
			continue;
		}
		the_Only_one.dynamic_num[counter].Id[i] = idn[i];
	}

	//empty name and id number
	name[0] = '\0';
	idn[0] = '\0';
	return true;
}

int read_num_of_lines(FILE *IDinfo, int counter) {
	char line[max_name_Length + Id_length + 3];
	for (int i = 0; i < max_name_Length + Id_length + 2; i++) { //repeat for maximun length of line
		fread(&line[i], sizeof(char), 1, IDinfo); //read line of txt file and indecate when done
		if (line[i] == '\n') {
			counter++;
			break;
		}
		else if (line[0] > (char)57 || line[0] < (char)49) { //if the first char is not a number you have passed the last line
			return -1;
		}
	}
	return counter; //return number of lines

}

void take_line_of_course_info(FILE *Courseinfo) {

	char course_Num[course_length + 1], grade[grade_length + 1], id[Id_length + 1];
	int grade_one_num = 0, course_one_num = 0, current_student, list_number;

	for (int a = 0; a < Id_length + 1; a++) { //find id and student to assing course to
		fread(&id[a], sizeof(char), 1, Courseinfo);
		if (id[a] == ' ') {
			id[a] = '\0';
			for (int i = 0; i < the_Only_one.num_of_students; i++) { //assign course number and grade to correct student
				std::string string_id = id;
				std::string string_compare = the_Only_one.dynamic_num[i].Id;
				if (string_id == string_compare) { //compare strings to see if id's are the same
					current_student = i;
					for (int g = 0; g < the_Only_one.dynamic_num[i].Num_Of_courses; g++) { //check if grade number was givin to see if list was used
						if (the_Only_one.dynamic_num[i].list[g].G_number > 100 || the_Only_one.dynamic_num[i].list[g].G_number < 0) {
							list_number = g;
							i = the_Only_one.num_of_students;
							break;
						}
					}
				}
			}
		}
	}
	for (int q = 0; q < course_length + 1; q++) { //read course and assign to student
		fread(&course_Num[q], sizeof(char), 1, Courseinfo); //read course num
		if (course_Num[q] == ' ') {
			for (int f = 0; f < course_length; f++) { //convert course to single int
				course_one_num = 10 * course_one_num + (int)(course_Num[f] - '0');
			}
			the_Only_one.dynamic_num[current_student].list[list_number].C_number = course_one_num; //place into dynamic array
			for (int j = 0; j < grade_length + 1; j++) { //including backslash n
				fread(&grade[j], sizeof(char), 1, Courseinfo); //read line of txt file
				if (grade[j] == '\n') {
					for (int f = 0; f < j; f++) { //convert grade to single int
						grade_one_num = 10 * grade_one_num + (int)(grade[f] - '0');
					}
					the_Only_one.dynamic_num[current_student].list[list_number].G_number = grade_one_num; //place grade in student grade
					j = grade_length + 1;
					continue;
				}
			}
		}
	}
}

void read_num_of_lines_per_student(FILE *Courseinfo, int counter) {
	char line[Id_length + 2];
	int also_count = 0;
	for (int i = 0; i < 2 + Id_length; i++) { //repeat for maximun length of line
		fread(&line[i], sizeof(char), 1, Courseinfo); //read line of txt file 
		if (line[i] == '\n') {
			i = -1; //restart the id
			also_count++; //count until last line
		}
		if (line[i] == ' ' && line[5] != '\0') { //and indecate when done readin id
			line[i] = '\0';
			for (int j = 0; j < the_Only_one.num_of_students + 1; j++) {
				std::string id = the_Only_one.dynamic_num[j].Id;
				std::string id_line = line;
				if (id_line == id) { //if id name has a course increase amount of courses
					the_Only_one.dynamic_num[j].Num_Of_courses++;
					break;
				}
			}
			i = -1; // restart the line string
		}
		if (also_count == counter) { //if no more id's leave function
			break;
		}

	}
}

int read_num_of_lines_course_info(FILE *Courseinfo, int counter) {
	char line[Id_length + course_length + grade_length + 3];
	for (int i = 0; i < Id_length + course_length + grade_length + 3; i++) { //repeat for maximun length of line
		fread(&line[i], sizeof(char), 1, Courseinfo); //read line of txt file and indecate when done
		if (line[i] == '\n') {
			counter++;
			break;
		}
		else if (line[0] > (char)57 || line[0] < (char)49) { //if the first char is not a number you have passed the last line
			return -1;
		}
	}
	return counter; //return number of lines

}

void read_List_course_info() {

	int counter = 0, line_helper = 0;
	FILE *Courseinfo;
	fopen_s(&Courseinfo, "Course_info.txt", "r");

	if (Courseinfo == NULL) { //verify the file opend
		std::cout << "File not found!";
	}
	else {
		while (counter != -1) {
			counter = read_num_of_lines_course_info(Courseinfo, counter); //count number of lines
			if (counter == -1) { //stop at the end of the page
				continue;
			}
			else {
				line_helper++; //increase number of students for every line
			}
		}
	}
		fclose(Courseinfo); //close file

		fopen_s(&Courseinfo, "Course_info.txt", "r");

		if (Courseinfo == NULL) { //verify the file opend
			std::cout << "File not found!";
		}
		else {
			read_num_of_lines_per_student(Courseinfo, line_helper); //add correct amount of courses per student
		}
		fclose(Courseinfo); //close file

		fopen_s(&Courseinfo, "Course_info.txt", "r");
		if (Courseinfo == NULL) { //verify the file opend
			std::cout << "File not found!";
		}
		else {
			for (int i = 0; i < the_Only_one.num_of_students; i++) { //start dynamic array of courses for all students
				the_Only_one.dynamic_num[i].list = new course[the_Only_one.dynamic_num[i].Num_Of_courses]; 
			}
				for (int k = 0; k < line_helper; k++) { //go over all lines of file
						take_line_of_course_info(Courseinfo); //add correct course info per student per line
				}
			
		}
			fclose(Courseinfo); //close file
		
}

void read_List_student_info() { //read list student_info.txt  

	bool flag;
	char idn[Id_length + 2], name[max_name_Length + 2]; //id & name length
	int line_helper = 0 ,counter = 0; //identefiers
	FILE *IDinfo;
	fopen_s(&IDinfo, "Student_info.txt", "r"); 
	//turn to student file & open file for read only
	
	
	if (IDinfo == NULL) { //verify the file opend
		std::cout << "File not found!";
	}
	else {
		while (line_helper != -1) { 
			line_helper = read_num_of_lines(IDinfo, line_helper); //count number of lines
			if (line_helper == -1) { //stop at the end of the page
				continue;
			}
			else {
				the_Only_one.num_of_students++; //increase number of students for every line
			}
		}
		fclose(IDinfo); //close file
	}

		fopen_s(&IDinfo, "Student_info.txt", "r");
		if (IDinfo == NULL) { //verify the file opend
			std::cout << "File not found!";
		}else{
			the_Only_one.dynamic_num = new student[the_Only_one.num_of_students + 1]; //open the dynamic array to the right size
		do {
			flag = read_Line(IDinfo, idn, name, counter); //set each given name
			counter++;
		} while (flag == true); //end loop at the end of list
		
		fclose(IDinfo); //close file
	}
		put_students_in_order(); // place students in correct order
}

void fill_student_info() {
	the_Only_one.num_of_students = 0; //initialize num of students
	read_List_student_info(); //retrive info from student list
	read_List_course_info();  //retrive info fron course list
}

void add_new_student_to_array(std::string id, std::string name, int number_of_courses) {

	int name_length=0;
	std::string course_num = "Number: ";
	std::string grade = "Grade: ";

	//if list is empty
	if (the_Only_one.dynamic_num == NULL) {
		the_Only_one.dynamic_num = new student;
		for (int i = 0; i < Id_length + 1; i++) { //insert new id
			if (i == 9) {
				the_Only_one.dynamic_num[the_Only_one.num_of_students].Id[i] = '\0';
				break;
			}
			the_Only_one.dynamic_num[the_Only_one.num_of_students].Id[i] = id[i];
		}
		for (int i = 0; name[i]; i++) //find name length
		{
			name_length++;
		}
		for (int i = 0; i < name_length + 1; i++) { //insert new name
			if (i == name_length) {
				the_Only_one.dynamic_num[the_Only_one.num_of_students].Name[i] = '\0';
				break;
			}
			the_Only_one.dynamic_num[the_Only_one.num_of_students].Name[i] = name[i];
		}
		the_Only_one.dynamic_num[the_Only_one.num_of_students].Num_Of_courses = number_of_courses; //insert num of courses
		if (number_of_courses > 0) {
			the_Only_one.dynamic_num[the_Only_one.num_of_students].list = new course[number_of_courses]; //create new temp array of courses for new student
			for (int i = 0; i < number_of_courses; i++)
			{ //get all needed courses and grade numbers
				std::cout << course_num;
				std::cin >> the_Only_one.dynamic_num[the_Only_one.num_of_students].list[i].C_number;
				std::cout << grade;
				std::cin >> the_Only_one.dynamic_num[the_Only_one.num_of_students].list[i].G_number;
			}
		}
			the_Only_one.num_of_students++; //increase num of students to one
	}
	else {
		student *temp_student_array = new student[the_Only_one.num_of_students + 1]; //create temporary dynamic array

		for (int i = 0; i < the_Only_one.num_of_students; i++) { //enter all students into new array
			strcpy_s(temp_student_array[i].Id, the_Only_one.dynamic_num[i].Id);
			strcpy_s(temp_student_array[i].Name, the_Only_one.dynamic_num[i].Name);
			temp_student_array[i].Num_Of_courses = the_Only_one.dynamic_num[i].Num_Of_courses;
		}
		//start dynamic array of courses for all students in temp array
		for (int j = 0; j < the_Only_one.num_of_students; j++) {
			if (temp_student_array[j].Num_Of_courses == 0) {
				continue;
			}
			temp_student_array[j].list = new course[temp_student_array[j].Num_Of_courses];
		}
		for (int i = 0; i < the_Only_one.num_of_students; i++) { //copy dynamic array of courses for all students in temp array
			for (int j = 0; j < temp_student_array[i].Num_Of_courses; j++) {
				temp_student_array[i].list[j].C_number = the_Only_one.dynamic_num[i].list[j].C_number;
				temp_student_array[i].list[j].G_number = the_Only_one.dynamic_num[i].list[j].G_number;
			}
		}

		for (int i = 0; i < the_Only_one.num_of_students; i++) { //delete dynamic array of courses for all students
			delete[]the_Only_one.dynamic_num[i].list;
		}
		delete[] the_Only_one.dynamic_num; //delete all old dynamic arrays of students

		for (int i = 0; i < Id_length + 1; i++) { //insert new id
			if (i == 9) {
				temp_student_array[the_Only_one.num_of_students].Id[i] = '\0';
				break;
			}
			temp_student_array[the_Only_one.num_of_students].Id[i] = id[i];
		}
		name_length = 0;
		for (int i = 0; name[i]; i++) //find name length
		{
			name_length++;
		}
		for (int i = 0; i < name_length + 1; i++) { //insert new name
			if (i == name_length) {
				temp_student_array[the_Only_one.num_of_students].Name[i] = '\0';
				break;
			}
			temp_student_array[the_Only_one.num_of_students].Name[i] = name[i];
		}

		temp_student_array[the_Only_one.num_of_students].Num_Of_courses = number_of_courses; //insert num of courses
		//dont make course list if there are no courses
		if (temp_student_array[the_Only_one.num_of_students].Num_Of_courses != 0) {
			temp_student_array[the_Only_one.num_of_students].list = new course[number_of_courses]; //create new temp array of courses for new student
			for (int i = 0; i < number_of_courses; i++)
			{ //get all needed courses and grade numbers
				std::cout << course_num;
				std::cin >> temp_student_array[the_Only_one.num_of_students].list[i].C_number;
				std::cout << grade;
				std::cin >> temp_student_array[the_Only_one.num_of_students].list[i].G_number;
			}
		}
		the_Only_one.num_of_students++; //increase num of students by one
		the_Only_one.dynamic_num = new student[the_Only_one.num_of_students];
		for (int i = 0; i < the_Only_one.num_of_students; i++) { //enter all students into not temporary new array
			strcpy_s(the_Only_one.dynamic_num[i].Id, temp_student_array[i].Id);
			strcpy_s(the_Only_one.dynamic_num[i].Name, temp_student_array[i].Name);
			the_Only_one.dynamic_num[i].Num_Of_courses = temp_student_array[i].Num_Of_courses;
		}
		//make course list for all students
		for (int j = 0; j < the_Only_one.num_of_students; j++) {
			if (the_Only_one.dynamic_num[j].Num_Of_courses == 0) {
				continue;
			}
			the_Only_one.dynamic_num[j].list = new course[the_Only_one.dynamic_num[j].Num_Of_courses];
		}

		for (int i = 0; i < the_Only_one.num_of_students; i++) { //place back dynamic array of courses for all students in new array
			for (int j = 0; j < temp_student_array[i].Num_Of_courses; j++) {
				the_Only_one.dynamic_num[i].list[j].C_number = temp_student_array[i].list[j].C_number;
				the_Only_one.dynamic_num[i].list[j].G_number = temp_student_array[i].list[j].G_number;
			}
		}
		for (int i = 0; i < the_Only_one.num_of_students; i++) { //delete all temp dynamic arrays of lists
			//dont delete course list if there are no courses
			if (the_Only_one.dynamic_num[i].Num_Of_courses == 0) {
				continue;
			}
			delete[] temp_student_array[i].list;
		}
		delete[] temp_student_array; //delete all temp dynamic array of students
		put_students_in_order(); //put students in correct order
	}
}

void new_student_addition() {
	//defining strings and int's
		int N_num_of_courses;
		std::string N_name, N_id;
		std::string name = "Name: ";
		std::string id = "Id: ";
		std::string num_of_courses = "Number of courses: ";
	
	//print and recive needed additions for new student
	std::cout << name;
	std::cin >> N_name;
	std::cout << id;
	std::cin >> N_id;
	std::cout << num_of_courses;
	std::cin >> N_num_of_courses;
	
	add_new_student_to_array(N_id, N_name, N_num_of_courses);

}

int binary_Search(int first_spot, int last_spot, char string_we_need[], int stay_safe)
{
	if (stay_safe != 1) { //if id num is there
		int middle = first_spot + (last_spot - first_spot) / 2; //define middle
		int i = 0; //indicator
		if (last_spot == first_spot) { //raise safty to avoid infinite if there is no id
			stay_safe++;
		}
		while (i != 9) {
			if (the_Only_one.dynamic_num[middle].Id[i] > string_we_need[i]) { // If element is smaller than mid, then it will be on the left side
				return binary_Search(first_spot, middle - 1, string_we_need, stay_safe); //use recursion to continue looking
			}
			else if (the_Only_one.dynamic_num[middle].Id[i] < string_we_need[i]) { //Else it will be on the right side
				return binary_Search(middle + 1, last_spot, string_we_need, stay_safe); //use recursion to continue looking
			}
			else if (the_Only_one.dynamic_num[middle].Id[i] == string_we_need[i]) { //compare every num in string until we find bigger or smaller
				i++;
			}
		}
		if (i == 9)//we found corresponding number of id
		{
			return middle;
		}

	}
	// the id num does not exist
	return -1;
}

void delete_student() {

	//if there are no students
	if (the_Only_one.dynamic_num == NULL) {
		std::cout << error << std::endl;
	} else{
	char N_id[Id_length+1];
	int id_num_spot;
	std::string id = "Id: ";

	//request id number for deletion
	std::cout << id;
	std::cin >> N_id;

	id_num_spot = binary_Search( 0, the_Only_one.num_of_students, N_id,0); //find location in dynamic array with binary search of student to delete
	
	//error if no student found
	if (id_num_spot == -1) {
		std::cout << error << std::endl;
	}
	else {
		for (int i = 0; i < Id_length; i++) {
			the_Only_one.dynamic_num[id_num_spot].Id[i] = (char)57;
		}
		put_students_in_order();

		student *temp_student_array = new student[the_Only_one.num_of_students - 1]; //create temporary dynamic array

		for (int i = 0; i < the_Only_one.num_of_students - 1; i++) { //enter all students into new array besides the last one
			strcpy_s(temp_student_array[i].Id, the_Only_one.dynamic_num[i].Id);
			strcpy_s(temp_student_array[i].Name, the_Only_one.dynamic_num[i].Name);
			temp_student_array[i].Num_Of_courses = the_Only_one.dynamic_num[i].Num_Of_courses;
			for (int j = 0; j < the_Only_one.num_of_students - 1; j++) { //start dynamic array of courses for all students in temp array besides the last one
				temp_student_array[i].list = new course[temp_student_array[i].Num_Of_courses];
			}
			for (int j = 0; j < temp_student_array[i].Num_Of_courses; j++) { //copy dynamic array of courses for all students in temp array besides the last one
				temp_student_array[i].list[j].C_number = the_Only_one.dynamic_num[i].list[j].C_number;
				temp_student_array[i].list[j].G_number = the_Only_one.dynamic_num[i].list[j].G_number;
			}
		}
		for (int i = 0; i < the_Only_one.num_of_students - 1; i++) { //delete dynamic array of courses for all students
			delete[]the_Only_one.dynamic_num[i].list;
		}
		delete[] the_Only_one.dynamic_num; //delete all old dynamic arrays of students

		the_Only_one.num_of_students--; //decrease num of students by one
		the_Only_one.dynamic_num = new student[the_Only_one.num_of_students];
		for (int i = 0; i < the_Only_one.num_of_students; i++) { //enter all students into not temporary new array
			strcpy_s(the_Only_one.dynamic_num[i].Id, temp_student_array[i].Id);
			strcpy_s(the_Only_one.dynamic_num[i].Name, temp_student_array[i].Name);
			the_Only_one.dynamic_num[i].Num_Of_courses = temp_student_array[i].Num_Of_courses;

			for (int j = 0; j < the_Only_one.num_of_students; j++) { //recreate student list for each student
				the_Only_one.dynamic_num[i].list = new course[the_Only_one.dynamic_num[i].Num_Of_courses];
			}

			for (int j = 0; j < temp_student_array[i].Num_Of_courses; j++) { //place back dynamic array of courses for all students in good array
				the_Only_one.dynamic_num[i].list[j].C_number = temp_student_array[i].list[j].C_number;
				the_Only_one.dynamic_num[i].list[j].G_number = temp_student_array[i].list[j].G_number;
			}
		}
		for (int i = 0; i < the_Only_one.num_of_students; i++) { //delete all temp dynamic arrays of lists
			delete[] temp_student_array[i].list;
		}
		delete[] temp_student_array; //delete all temp dynamic array of students
	  }
	}
}

void add_course_to_student() {

	//if there are no students
	if (the_Only_one.dynamic_num == NULL) {
		std::cout << error << std::endl;
	}
	else {
		//initialize necasery variables
		bool already_there = false;
		char N_id[Id_length + 1];
		int N_grade, N_course, id_num_spot,check_if_existes;
		std::string id = "Id: ";
		std::string course_num = "Number: ";
		std::string grade = "Grade: ";


		//request id number 
		std::cout << id;
		std::cin >> N_id;

		//find location in dynamic array with binary search of student to add course to
		id_num_spot = binary_Search(0, the_Only_one.num_of_students, N_id, 0);
		//error if no student found
		if (id_num_spot == -1) {
			std::cout << error << std::endl;
		}
		else {
			//course info in order to add course to correct student
			std::cout << course_num;
			std::cin >> N_course;
			std::cout << grade;
			std::cin >> N_grade;

            //check if course is already there
			for (check_if_existes = 0; check_if_existes < the_Only_one.dynamic_num[id_num_spot].Num_Of_courses; check_if_existes++) {
				if (the_Only_one.dynamic_num[id_num_spot].list[check_if_existes].C_number == N_course) {
					already_there = true;
					break;
				}
			}
			//just change grade
			if (already_there == true) {
				the_Only_one.dynamic_num[id_num_spot].list[check_if_existes].G_number = N_grade;
			}
			else {
				//create temp list
				student temp_student;
				temp_student.list = new course[the_Only_one.dynamic_num[id_num_spot].Num_Of_courses + 1];

				//copy dynamic array of courses for all students in temp array besides the last one
				for (int i = 0; i < the_Only_one.dynamic_num[id_num_spot].Num_Of_courses; i++) {
					temp_student.list[i].C_number = the_Only_one.dynamic_num[id_num_spot].list[i].C_number;
					temp_student.list[i].G_number = the_Only_one.dynamic_num[id_num_spot].list[i].G_number;
				}

				//add new course number and grade and delete old list
				temp_student.list[the_Only_one.dynamic_num[id_num_spot].Num_Of_courses].C_number = N_course;
				temp_student.list[the_Only_one.dynamic_num[id_num_spot].Num_Of_courses].G_number = N_grade;
				delete[] the_Only_one.dynamic_num[id_num_spot].list;

				//increase num of courses for the student
				the_Only_one.dynamic_num[id_num_spot].Num_Of_courses++;

				//recreate course list for student
				the_Only_one.dynamic_num[id_num_spot].list = new course[the_Only_one.dynamic_num[id_num_spot].Num_Of_courses];

				//place back dynamic array of courses for the student in new array
				for (int i = 0; i < the_Only_one.dynamic_num[id_num_spot].Num_Of_courses; i++) {
					the_Only_one.dynamic_num[id_num_spot].list[i].C_number = temp_student.list[i].C_number;
					the_Only_one.dynamic_num[id_num_spot].list[i].G_number = temp_student.list[i].G_number;
				}
				//delete temp list array 
				delete[] temp_student.list;
			}
		}
	}
}

void print_student() {

	//if there are no students
	if (the_Only_one.dynamic_num == NULL) {
		std::cout << error << std::endl;
	}
	else {
		char N_id[Id_length + 1];
		int id_num_spot;
		std::string id = "Id: ";

		//request id number in order to print student
		std::cout << id;
		std::cin >> N_id;

		//find location in dynamic array with binary search in order to present student
		id_num_spot = binary_Search(0, the_Only_one.num_of_students, N_id, 0);

		//error if no student found
		if (id_num_spot == -1) {
			std::cout << error << std::endl;
		}
		else {
			//print student info
			std::cout << the_Only_one.dynamic_num[id_num_spot].Name << " " << the_Only_one.dynamic_num[id_num_spot].Id << std::endl;
			std::cout << the_Only_one.dynamic_num[id_num_spot].Num_Of_courses << std::endl;
			for (int i = 0; i < the_Only_one.dynamic_num[id_num_spot].Num_Of_courses; i++) {
				std::cout << the_Only_one.dynamic_num[id_num_spot].list[i].C_number << " " << the_Only_one.dynamic_num[id_num_spot].list[i].G_number << std::endl;
			}
		}
	}
}

void print_student_avg() {

	//if there are no students
	if (the_Only_one.dynamic_num == NULL) {
		std::cout << error << std::endl;
	}
	else {
		char N_id[Id_length + 1];
		int id_num_spot, grade_avg;
		int all_grade_addition = 0;
		std::string id = "Id: ";


		//request id number in order to print student avg
		std::cout << id;
		std::cin >> N_id;

		//find location in dynamic array with binary search in order to present student avg
		id_num_spot = binary_Search(0, the_Only_one.num_of_students, N_id, 0);

		//error if no student found
		if (id_num_spot == -1) {
			std::cout << error << std::endl;
		}
		else if (the_Only_one.dynamic_num[id_num_spot].Num_Of_courses == 0) {
			std::cout << "The student has no grades" << std::endl;
		}
		else {
			//sum of all grades
			for (int i = 0; i < the_Only_one.dynamic_num[id_num_spot].Num_Of_courses; i++) {
				all_grade_addition = the_Only_one.dynamic_num[id_num_spot].list[i].G_number + all_grade_addition;
			}
			//calculate grade avg
			grade_avg = all_grade_addition / the_Only_one.dynamic_num[id_num_spot].Num_Of_courses;

			//print grade avg
			std::cout << "Average grade: " << std::endl;
			std::cout << grade_avg;
		}
	}
}

void print_all_students() {

	//if there are no students
	if (the_Only_one.dynamic_num == NULL) {
		std::cout << error << std::endl;
	}
	else {
		//print all students
		for (int i = 0; i < the_Only_one.num_of_students; i++) {
			std::cout << the_Only_one.dynamic_num[i].Name << " " << the_Only_one.dynamic_num[i].Id << std::endl;
			std::cout << the_Only_one.dynamic_num[i].Num_Of_courses << std::endl;
			//print all lists of courses for all students
			for (int j = 0; j < the_Only_one.dynamic_num[i].Num_Of_courses; j++) {
				std::cout << the_Only_one.dynamic_num[i].list[j].C_number << " " << the_Only_one.dynamic_num[i].list[j].G_number << std::endl;
			}
		}
	}
}

void print_avg_for_all_students() {

	//if there are no students
	if (the_Only_one.dynamic_num == NULL) {
		std::cout << error << std::endl;
	}
	else {
		int sum_of_grade_for_one_student = 0, overall_of_avgreges = 0;
		int grade_avg_for_one_student, average_of_avreges;

		//sum of all avg's
		for (int j = 0; j < the_Only_one.num_of_students; j++) {
			//restart grade for every new student
			sum_of_grade_for_one_student = 0;
			//sum of amount of grades for one student
			for (int i = 0; i < the_Only_one.dynamic_num[j].Num_Of_courses; i++) {
				sum_of_grade_for_one_student = the_Only_one.dynamic_num[j].list[i].G_number + sum_of_grade_for_one_student;
			}
			//calculate grade avg
			grade_avg_for_one_student = sum_of_grade_for_one_student / the_Only_one.dynamic_num[j].Num_Of_courses;
			//add to sum of avg's
			overall_of_avgreges = grade_avg_for_one_student + overall_of_avgreges;
		}
		//calculate overall avg
		average_of_avreges = overall_of_avgreges / the_Only_one.num_of_students;
		//print overall avg
		std::cout << average_of_avreges;
	}
}

void erase_all_students() {

	//if there are no students
	if (the_Only_one.dynamic_num == NULL) {
		std::cout << error << std::endl;
	}
	else {
		for (int i = 0; i < the_Only_one.num_of_students; i++) { //delete all dynamic arrays of lists
			delete[] the_Only_one.dynamic_num[i].list;
		}
		delete[] the_Only_one.dynamic_num; //delete all dynamic arrays of students
		the_Only_one.dynamic_num = NULL;
		the_Only_one.num_of_students = 0;
	}
}

void exit_program() {

	for (int i = 0; i < the_Only_one.num_of_students; i++) { //delete all dynamic arrays of lists
		delete[] the_Only_one.dynamic_num[i].list;
	}
	delete[] the_Only_one.dynamic_num; //delete all dynamic arrays of students
}

	
	
