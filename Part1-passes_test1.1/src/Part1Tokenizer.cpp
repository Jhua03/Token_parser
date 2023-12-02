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
//%      or put �none� if nobody helped (the two of) you.
//
// Helpers: _everybody helped us/me with the assignment (list names or put �none�)__
//
// Also, list any resources beyond the course textbook and the course pages on Piazza
// that you used in making your submission.
//
// Resources:  ___________
//
//%% Instructions:
//% * Put your name(s), student number(s), userid(s) in the above section.
//% * Enter the above information in Test.cpp if you are submitting that file too.
//% * Edit the "Helpers" line and "Resources" line.
//% * Your group name should be "P1_<userid1>_<userid2>" (eg. P1_stu1_stu2)
//% * Form groups as described at:  https://courses.cs.sfu.ca/docs/students
//% * Submit one or two files to courses.cs.sfu.ca
//
// Name        : Part1Tokenizer.cpp
// Description : Tokenizer that passes test1
// Original Version Copyright (c) 2023 Simon Fraser University
//============================================================================

#include "Part1Tokenizer.hpp"

using namespace std;

// Accepts a stream and returns a vector of tokens with any remaining preprocessing lines stripped out
// Input: a stream
// Output: a vector of tokens
vector<string> tokenizeCodeStrip(istream& code) {
	// *** Fill in implementation ...
	vector<string> myResultVect;
	               //  wrong{"A", "wrong", "vector"};
   string lineFromCode;
   const string internalWhiteSpace{" \t"};

   // https://cplusplus.com/reference/string/string/getline/
   getline(code, lineFromCode); // this ultimately needs to be in an outer loop

   string::size_type index1{0};

   while(index1 < lineFromCode.length()) {
      auto indexNotWS{lineFromCode.find_first_not_of(internalWhiteSpace, index1)};
      index1 = lineFromCode.find_first_of(internalWhiteSpace, indexNotWS);
      myResultVect.push_back(lineFromCode.substr(indexNotWS, index1 - indexNotWS));
   }

	return myResultVect;
}
