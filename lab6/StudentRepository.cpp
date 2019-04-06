#include <iostream>
using ::std::cout;
using ::std::endl;

#include <fstream>
using ::std::fstream;

#include <boost/tokenizer.hpp>
using ::boost::char_separator;
using ::boost::tokenizer;

#include "StudentRepository.h"
#include "Student.h"
#include "StudyYear.h"

Student StudentRepository::operator[] (string index) const 
{
    for (auto student : students)
    {
        if (index==student.id) { return student; }
    }
    string exception="not_found";
    throw exception;
}

void StudentRepository::Append(Student& newStudent) 
{
    students.push_back(newStudent);
}

void StudentRepository::Print() 
{
    cout << "Content of repository:" << endl;
    for (auto student : students)
    {
        cout << student << endl;
    }
}

void StudentRepository::LoadDataBaseFromFile(string fileName)
{
    fstream inputFile;
    string line;

    inputFile.open(fileName, std::ios::in);
    if (inputFile.good() == false) 
    {
        string exception = "open_file_unsuccessful";
        throw exception;
    }

    while( !inputFile.eof())
    {
        getline(inputFile, line);

        char_separator<char> sep("{},\" ");
        tokenizer<char_separator<char>> tokens(line, sep);

        typedef tokenizer<char_separator<char>> tokenizer;
        tokenizer::iterator it =tokens.begin();

        string id = *(it++);
        string firstName = *(it++);
        string lastName = *(it++);
        string field = *(it++);
        int yearValue =(std::stoi(*it));

        Student newStudent(id, firstName, lastName, field, yearValue);
        Append(newStudent);
    }
    inputFile.close();
}