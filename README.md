# Student and Course Management System
This C++ program is designed to manage student and course information. It allows users to read data from text files, store it in data structures, sort students by their IDs, and add new students with associated courses and grades.

## Features
Sorting Students: The program provides a function to sort students based on their ID numbers using the bubble sort algorithm. It handles cases where students have the same ID by recursively comparing additional values in the student records.

Reading Student Information: The read_Line function reads a line of text from a file (presumably containing student data) and extracts student ID and name information. It populates a dynamic array of student structures with this data.

Reading Course Information: The take_line_of_course_info function reads a line of text from another file (presumably containing course data) and associates courses and grades with students based on their IDs. It allocates memory for dynamic arrays of course structures to store course information for each student.

Managing Course Lists: The program maintains a list of courses and grades for each student. It allocates memory dynamically for these lists based on the number of courses each student has.

Adding a New Student: The add_new_student_to_array function allows you to add a new student to the system. It prompts for the student's ID, name, and the number of courses they have. It creates a temporary array to hold the updated student information and then transfers data from the old array to the new one with the new student added.

Initialization: The program initializes the number of students and reads student and course information from files. It also reads the number of courses per student, assigns courses and grades to the appropriate students, and creates the necessary dynamic data structures.
