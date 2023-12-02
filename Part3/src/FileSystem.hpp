//============================================================================
//
//% Student Name 1: Paul Zielinski
//% Student 1 #: 301153495
//% Student 1 userid (email): pzielins (pzielins@sfu.ca)
//
//% Student Name 2: Minh Tri Hua
//% Student 2 #: 301540779
//% Student 2 userid (email): mth5 (mth5@sfu.ca)
//
//% Below, edit to list any people who helped you with the code in this file,
//%      or put ‘none’ if nobody helped (the two of) you.
//
// Helpers: _everybody helped us/me with the assignment (list names or put ‘none’)__
//
// Also, list any resources beyond the course textbook and the course pages on Piazza
// that you used in making your submission.
//
// Resources:  ___________
//
//%% Instructions:
//% * Put your name(s), student number(s), userid(s) in the above section.
//% * Enter the above information in any other files you are also submitting.
//% * Edit the "Helpers" line and "Resources" line.
//% * Your group name should be "P3_<userid1>_<userid2>" (eg. P3_stu1_stu2)
//% * Form groups as described at:  https://coursys.sfu.ca/docs/students
//% * Submit files to coursys.sfu.ca
//
// Name        : FileSystem.hpp
// Description : Course Project Part 3 (Directory Tree)
// Copyright   : Original Portions Copyright (c) 2023 School of Engineering Science
//============================================================================

#pragma once

#include <iomanip>
#include <string>
#include <string_view>
#include <memory>

#include "TreeNode.hpp"

class DirectoryEntry :  public ensc251::TreeNode
{
private:
	std::string m_name;

public:
	explicit DirectoryEntry(std::string_view name): m_name{name} {}

    friend void swap(DirectoryEntry& a, DirectoryEntry& b) noexcept
    {
        using std::swap;
        swap(static_cast<ensc251::TreeNode&>(a), static_cast<ensc251::TreeNode&>(b));
        swap(a.m_name, b.m_name);
    }

	void set_name(const std::string_view& name){ m_name = name;}
	const std::string & get_name() { return m_name; }

   virtual void print_action() = 0;
   virtual void print_traverse() = 0;
};

class File :  public DirectoryEntry
{
private:
	// std::string m_content;
public:
	explicit File(std::string_view name): DirectoryEntry(name) {}
	TreeNodeSP clone() const override {return std::make_shared<File>(*this);  /* ***** Complete this member function ***** */ };

	void print_action() override
	{
		// Do not modify insertion on OUT in this member function!
		OUT << std::setw(20) << this->get_name()+"\tF" << std::endl;
	}

   void print_traverse() override
   {
	   if (childSPVector.size() < 2) {
	            traverse_children_post_order(
	                  static_cast<traverse_func>(&File::print_traverse),
	                  static_cast<action_func>(&DirectoryEntry::print_action));
	      }
	   else if (childSPVector.size() == 2) {
	         traverse_children_in_order(
	               static_cast<traverse_func>(&File::print_traverse),
	               static_cast<action_func>(&DirectoryEntry::print_action));
	      }
	   else {
	         traverse_children_pre_order(
	               static_cast<traverse_func>(&File::print_traverse),
	               static_cast<action_func>(&DirectoryEntry::print_action));
	         }
	   /* ***** Complete this member function ***** */
   }
};

class Directory :  public DirectoryEntry
{
public:
   explicit Directory(std::string_view dir_name): DirectoryEntry{dir_name} {}
   TreeNodeSP clone() const override { return std::make_shared<Directory>(*this);  };

	void print_action() override
	{
		// Do not modify insertion on OUT in this member function!
		OUT << std::setw(20) << this->get_name()+"\t|" << " ";
		OUT << this->childSPVector.size() << std::endl;
	}

	void print_traverse() override
	{
		// ***** this needs work *****
		// ***** encode the rules in the .pdf instructions
		   if (childSPVector.size() < 2) {
		            traverse_children_post_order(
		                  static_cast<traverse_func>(&Directory::print_traverse),
		                  static_cast<action_func>(&DirectoryEntry::print_action));
		      }
		   else if (childSPVector.size() == 2) {
		         traverse_children_in_order(
		               static_cast<traverse_func>(&Directory::print_traverse),
		               static_cast<action_func>(&DirectoryEntry::print_action));
		      }
		   else{
		         traverse_children_pre_order(
		               static_cast<traverse_func>(&Directory::print_traverse),
		               static_cast<action_func>(&DirectoryEntry::print_action));
		         }

	}
};
