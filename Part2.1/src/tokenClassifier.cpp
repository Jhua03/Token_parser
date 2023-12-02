//============================================================================
//
//% Student Name 1: student1
//% Student 1 #: 123456781
//% Student 1 userid (email): stu1 (stu1@sfu.ca)
//
//% Student Name 2: student2
//% Student 2 #: 123456782
//% Student 2 userid (email): stu2 (stu2@sfu.ca)
//
//% Below, edit to list any people who helped you with the code in this file,
//%      or put 'None' if nobody helped (the two of) you.
//
// Helpers: _everybody helped us/me with the assignment (list names or put 'None')__
//
// Also, list any resources beyond the course textbook and the course pages on Piazza
// that you used in making your submission.
//
// Resources:  ___________
//
//%% Instructions:
//% * Put your name(s), student number(s), userid(s) in the above section.
//% * Enter the above information in tokenClasses.cpp  too.
//% * Edit the "Helpers" line and "Resources" line.
//% * Your group name should be "P2_<userid1>_<userid2>" (eg. P2_stu1_stu2)
//% * Form groups as described at:  https://courses.cs.sfu.ca/docs/students
//% * Submit files to courses.cs.sfu.ca
//
// Name        : tokenClassifier.cpp
// Description : Course Project Part 2 (Token Classifier)
// Original portions Copyright (c) 2023 School of Engineering Science, Simon Fraser University
//============================================================================

#include <vector>
#include <sstream>
#include <algorithm>
#include <memory>
#include "tokenClasses.hpp"

using namespace std;
using namespace ensc251;

// You can put one or more functions here if you want

// Construct token objects categorized into appropriate types
// Input: a stream with code from the subset of C++
// Output: a vector containing shared pointers to Token objects properly categorized
vector<shared_ptr<Token> > tokenClassifier(istream& code)
{
		vector<shared_ptr<Token> > tokenObjectSPs;

        //TODO: Write Code for classifying each token into an object of the proper class
        // store a shared pointer to the object in vector tokenObjectSPs

		// For example, if you want to classify the number '10' in the input "errno = 10+2.5;":
		tokenObjectSPs.push_back(make_shared<int_literal<int> >(int_literal<int>(10, 1 /* lineIndex*/, 8 /*posIndex*/)));
        // where the 2nd argument is the line index and the 3rd argument is the
        //    posIndex (the position of the start of the token in that line).

        return tokenObjectSPs;
}

