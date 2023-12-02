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
// Name        : tokenClasses.hpp
// Description : Course Project Part 2 (Token Classifier)
// Original portions Copyright (c) 2023 School of Engineering Science, Simon Fraser University
//============================================================================

#pragma once

#include <string>
#include <string_view>
#include <iostream>
//#include <typeinfo>

namespace ensc251 {

using namespace std;

char *demangle(const char *typeName);

class Token { // The Base Token Class
private:
   string m_stringValue;
   int m_lineIndex;
   int m_posIndex;
public:
   Token() : m_stringValue(""), m_lineIndex(0), m_posIndex(0) {
      cout << "Warning:  Do not invoke this constructor" << std::endl; }; // make sure this does not get invoked.

   Token(const string_view aStringView, int lineIndex, int posIndex) /* Fill in... */ {  /* ... the implementation */ }

   int getLineIndex() const { return m_lineIndex; }
   int getPosIndex() const { return m_posIndex; }
   const string& getStringValue( ) const { return m_stringValue; }
   void print(ostream& outs) const {  outs << demangle(typeid(*this).name()) << " (line: " << m_lineIndex <<", pos: " << m_posIndex <<"): " << m_stringValue; }

   virtual ~Token() {} // You will learn about virtual soon, but for now, don't delete this line.
};

class punctuator:public Token {
	// e.g., ';', '*', '(', ')', ':'
public:
	/*Fill in the implementation for constructor */
};

class type_spec:public Token {
	// e.g., 'char' | 'int' | 'double'
public:
	/*Fill in the implementation for constructor  */
};

// do not instantiate this class.
class id:public Token {
	// identifiers -- example:  sum
public:
	/*Fill in the implementation for constructor */
};

class pointer_id:public id {
	// e.g., char* identifier
public:
	/*Fill in the implementation for constructor  */
};

class numeric_id:public id {
	// char, int, and float identifiers
public:
	/*Fill in the implementation for constructor  */
};

class int_id:public numeric_id {
	// char and int identifiers
public:
	/*Fill in the implementation for constructor  */
};

class gen_assignment_operator:public Token
{
	// '=' | '/=' | '+=' | '-='
public:
	/*Fill in the implementation for constructor  */
};

class int_assignment_operator:public Token
{
	// '%=' | '<<=' | '>>='
public:
	/*Fill in the implementation for constructor  */
};

class conditional_operator:public Token
{
	// ?
public:
	/*Fill in the implementation for constructor  */
};

class shift_operator:public Token
{
	// '<<' | '>>'
public:
	/*Fill in the implementation for constructor  */
};

class additive_operator:public Token
{
	// '+' | '-'
public:
	/*Fill in the implementation for constructor  */
};

class div_operator:public Token {
	// '/'
public:
	/*Fill in the implementation for constructor  */
};

class mod_operator:public Token {
	// '%'
public:
	/*Fill in the implementation for constructor  */
};

class comp_operator:public Token
{
	//  '~'
public:
	/*Fill in the implementation for constructor  */
};

class postfix_operator:public Token
{
	// '++' | '--'
public:
	/*Fill in the implementation for constructor  */
};

class string:public Token
{
	// e.g., "sample string"
public:
	/*Fill in the implementation for constructor  */
};

class incorrect:public Token
{
	// e.g., "sample string     --> This is incorrect ...
	//		(quotation mark " is missing at the end)
public:
	/* Fill in the implementation for constructor. Store the unrecognized characters. */
};

class literal:public Token
{
public:
   literal() { std::cout << "Warning:  Do not invoke this constructor" << std::endl; }; // make sure this does not get invoked.
   literal(const string_view aStringView, int lineIndex, int posIndex): Token(aStringView, lineIndex, posIndex) {};
};

template<typename T>
class numeric_literal:public literal
{
	// e.g. 48.5
private:
	T m_value;
public:
	numeric_literal(const T& literalValue, int lineIndex, int posIndex) /* Fill in... */ {  /* ... the implementation */ };
	//Fill in for additional constructors if desired
	const T& getValue() const { /*Fill in the implementation */ }
};

template<typename T>
class int_literal:public numeric_literal<T>
{
	// e.g. 48 or '0' -- covers just int and char
public:
   int_literal(const T& literalValue, int lineIndex, int posIndex): numeric_literal<T>(literalValue, lineIndex, posIndex) {}
	//Fill in for additional constructors if desired
};

} // namespace ensc251
