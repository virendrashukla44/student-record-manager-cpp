# Student Record Manager (C++)

## Project Overview
Console-based application to manage student records using arrays/vectors and sorting/searching algorithms.

## Features
- Add new student record
- Display all records
- Search by roll number
- Update record
- Delete record
- Sort students by marks (descending)
- Save/load records to/from `students.txt`

## How to compile & run

g++ student_record_manager.cpp -o student_record_manager
./student_record_manager

## File format
Records are stored in `students.txt` with format:
roll|name|marks

## Notes
- The program automatically saves to `students.txt` when you choose "Save & Exit".
