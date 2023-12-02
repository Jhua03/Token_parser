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
// Copyright (c) 2023 School of Engineering Science, Simon Fraser University
//============================================================================

#include <array>
#include <vector>
#include <sstream>
#include <algorithm>
#include <memory>
#include "tokenClasses.hpp"

// \n is also whitespace, but should have been removed by getline()
#define WHITE "\r\t\v\f "

using namespace std;
using namespace ensc251;

bool processDigits(const string line, string::size_type &index)
{
	bool DigiFound{false};
	while (index < line.length()  &&  isdigit(line.at(index)))
		{
			++index;
			DigiFound = true;
		}
	return DigiFound;
}

// Construct token objects categorized into appropriate types
// Input: a stream with code from the subset of C++
// Output: a vector containing shared pointers to Token objects properly categorized
vector<shared_ptr<Token> > tokenClassifier(istream& code)
{
   vector<shared_ptr<Token> > tokenObjectSPs;
   string lineFromCode;

   const array delim3{">>="s, "<<="s};
   const array delim2{"+="s, "-="s, "/="s, "%="s, "<<"s, ">>"s, "++"s, "--"s};
   constexpr auto delim1andWhite{WHITE "/()*%:;=+-~?"};
   constexpr auto internalWhiteSpace{WHITE};

   //TODO: Write Code for classifying each token into an object of the proper class
   // store a shared pointer to the object in vector tokenObjectSPs

   // For example, if you want to classify the number '10' and the ';' in the input "errno = 10+2.5;":
   //		tokenObjectPs.push_back(make_shared<int_literal<int> >(10, 0 /* lineIndex*/, 8 /*posIndex*/));
   //		tokenObjectPs.push_back(make_shared<punctuator >(";", 0 /* lineIndex*/, 14 /*posIndex*/));
   // where the 2nd argument is the line index and the 3rd argument is the
   //    posIndex (the position index of the start of the token in that line).
   int lineNumber{0};

   while (getline (code, lineFromCode)) {
      if ('#' == lineFromCode.at(0))
         continue;

      string::size_type index1{0};
      auto length{lineFromCode.length()};

      while (index1 < length) {
         auto index2{lineFromCode.find_first_not_of(internalWhiteSpace, index1)};
         if (string::npos == index2)
            break;

         /// Dealing with int and double literals
         if (isdigit(lineFromCode.at(index2))  ||  '.' == lineFromCode.at(index2)) {
            index1 = index2;
            bool is_int_literal{true};

            // integer literals
            bool preDigitFound{processDigits(lineFromCode, index1)};

            // double float literals
            if (index1 < length  &&  '.' == lineFromCode.at(index1)) {
               ++index1;
               bool postDigitFound{processDigits(lineFromCode, index1)};

               if (!preDigitFound && !postDigitFound) { // detecting the single "." as an invalid token!
                  cout << "Tokenizer detected:  invalid token in input: " << lineFromCode.substr(index2, index1 - index2) << endl;
                  tokenObjectSPs.push_back(make_shared<incorrect>(lineFromCode.substr(index2, index1 - index2), lineNumber, index2));
                  continue;
               }
               is_int_literal = false;
            }

            // exponentials
            if (index1 < length  &&  ('e' == lineFromCode.at(index1)  ||  'E' == lineFromCode.at(index1)) )
            {
               if ('+' == lineFromCode.at(index1 + 1)  ||  '-' == lineFromCode.at(index1 + 1))
                  index1 += 2;
               else
                  ++index1;

               if(!processDigits(lineFromCode, index1)) // invalid double -> roll back ...
               {
                  if ('e' == lineFromCode.at(index1 - 1)  ||  'E' == lineFromCode.at(index1 - 1))
                     --index1;
                  else
                     index1 -= 2;
               }
               is_int_literal = false;
            }

            // suffix d and D
            if (index1 < length && ('d' == lineFromCode.at(index1)  ||  'D' == lineFromCode.at(index1)) ) {
               ++index1;
               is_int_literal = false;
            }

            auto subs{lineFromCode.substr(index2, index1 - index2)};
            if(is_int_literal){ // integer literal
               tokenObjectSPs.push_back(make_shared<ensc251::int_literal<int>>(atoi(subs.c_str()), lineNumber, index2));
            }
            else {	 // double literal
               // isn't there a better method?  strtof ??
               istringstream os(subs);
               double d;
               os >> noskipws >> d;
               tokenObjectSPs.push_back(make_shared<ensc251::numeric_literal<double>>(d, lineNumber, index2));
            }
            continue;
         }

         for (auto delim : delim3) { // "<<=" || ">>="
            if (lineFromCode.substr(index2, 3) == delim) {
               tokenObjectSPs.push_back(make_shared<int_assignment_operator>(delim, lineNumber, index2));
               index1 = index2 + 3;
               break;
            }
         }
         if (index1 > index2) continue;

         // the below follows similarly to the pattern from the lines above.
         for (auto delim : delim2) {
            if (lineFromCode.substr(index2, 2) == delim) {
               if("+=" == delim || "-=" == delim || "/=" == delim) {
                  tokenObjectSPs.push_back(make_shared<gen_assignment_operator>(delim, lineNumber, index2));
               } else if ("%=" == delim) {
                  tokenObjectSPs.push_back(make_shared<int_assignment_operator>(delim, lineNumber, index2));
               } else if("<<" == delim || ">>" == delim){
                  tokenObjectSPs.push_back(make_shared<shift_operator>(delim, lineNumber, index2));
               } else if("++" == delim || "--" == delim){
                  tokenObjectSPs.push_back(make_shared<postfix_operator>(delim, lineNumber, index2));
               }
               index1 = index2 + 2;
               break;
            }
         }
         if (index1 > index2) continue;

         if ('"' == lineFromCode.at(index2)) {
            index1 = index2 + 1;
            while (index1 < length) {
               if ('\\' == lineFromCode.at(index1)) {
                  ++index1; // skip over escape character
               }
               else
                  if ('"' == lineFromCode.at(index1)) {
                     tokenObjectSPs.push_back(make_shared<ensc251::string_literal>(lineFromCode.substr(index2, index1 + 1 - index2), lineNumber, index2));
                     break;
                  }
               ++index1;
            }
            if (index1 >= length) { // String is not terminated!
               cout << "Tokenizer detected:  string is not terminated!" << endl;
               tokenObjectSPs.push_back(make_shared<incorrect>(lineFromCode.substr(index2, index1 - index2), lineNumber, index2));
               break;
            }
            ++index1; // non-empty string was pushed on the result vector
            continue;
         }

         if ('\'' == lineFromCode.at(index2)) {
            index1 = index2 + 1;
            if (index1 < length  &&  '\\' == lineFromCode.at(index1)) {
               ++index1; // skip over escape character
            }
            ++index1; // skip over character
            if (index1 >= length  ||  '\'' != lineFromCode.at(index1)) // Character literal is not terminated!
            {
               cout << "Tokenizer detected:  character constant is not terminated!" << endl;
               tokenObjectSPs.push_back(make_shared<incorrect>(lineFromCode.substr(index2, index1 - index2), lineNumber, index2));
            }
            else {
               ++index1;
               char tempChar{lineFromCode.substr(index2, index1 - index2)[1]};
               tokenObjectSPs.push_back(make_shared<int_literal<char>>(tempChar, lineNumber, index2));
            }
            continue;
         }

         if('_' == lineFromCode.at(index2)  ||  isalpha(lineFromCode.at(index2))) {
            index1 = index2 + 1;
            while (index1 < length  &&  ('_' == lineFromCode.at(index1)  ||  isalnum(lineFromCode.at(index1))) )
               ++index1;
            string tempToken{lineFromCode.substr(index2, index1 - index2)};
            if( "int" == tempToken || "double" == tempToken || "char" == tempToken ){
               tokenObjectSPs.push_back(make_shared<type_spec>(tempToken, lineNumber, index2));
            } 
            else { // classify the ids
               if("errno" == tempToken)
                  tokenObjectSPs.push_back(make_shared<int_id>(tempToken, lineNumber, index2));
               else { // this may need work in the future.  WCS
                  string preType{tokenObjectSPs.back()->getStringValue()};
                  for (size_t t{0}; t<tokenObjectSPs.size(); ++t)
                  {
                     if (tokenObjectSPs[t]->getStringValue() == tempToken)
                     {
                        preType = tokenObjectSPs[t-1]->getStringValue();
                        break;
                     }
                  }
                  if ("double" == preType)
                     tokenObjectSPs.push_back(make_shared<numeric_id>(tempToken, lineNumber, index2));
                  else if ("int" == preType || "char" == preType)
                     tokenObjectSPs.push_back(make_shared<int_id>(tempToken, lineNumber, index2));
                  else if ("*" == preType)
                     tokenObjectSPs.push_back(make_shared<pointer_id>(tempToken, lineNumber, index2));
                  else {
                     cout << "Tokenizer detected:  identifier has not been declared!" << endl;
						   // WCS needs to improve the next line.
							tokenObjectSPs.push_back(make_shared<int_id>(tempToken, lineNumber, index1));
                  }
               }
            }
            continue;
         }

         index1 = lineFromCode.find_first_of(delim1andWhite, index2);
         if (index1 == index2) {
            ++index1; // we found a 1-character token
            string tempToken{lineFromCode.substr(index2, 1)};
            char tempChar{lineFromCode[index2]};
            switch (tempChar) {
               case '=': tokenObjectSPs.push_back(make_shared<gen_assignment_operator>(tempToken, lineNumber, index2)); 
               	break;
               case '?': tokenObjectSPs.push_back(make_shared<conditional_operator>(tempToken, lineNumber, index2)); 
               	break;

               case '+':
               case '-': tokenObjectSPs.push_back(make_shared<additive_operator>(tempToken, lineNumber, index2)); 
               	break;

               case '/': tokenObjectSPs.push_back(make_shared<div_operator>(tempToken, lineNumber, index2)); 
               	break;
               case '%': tokenObjectSPs.push_back(make_shared<mod_operator>(tempToken, lineNumber, index2)); 
               	break;

               case '~': tokenObjectSPs.push_back(make_shared<comp_operator>(tempToken, lineNumber, index2)); 
               	break;

               case ';':
               case ':':
               case '*':
               case '(':
               case ')': tokenObjectSPs.push_back(make_shared<punctuator>(tempToken, lineNumber, index2)); 
               	break;
            }

            continue;
         }
         cout << "Tokenizer detected:  invalid token in input: " <<
               lineFromCode.substr(index2, index1 - index2) << endl;
         tokenObjectSPs.push_back(make_shared<incorrect>(lineFromCode.substr(index2, index1 - index2), lineNumber, index2));
      }

      ++lineNumber;
   }
   return tokenObjectSPs;
}

