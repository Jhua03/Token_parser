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
//% * Enter the above information in Directory.hpp too.
//% * Edit the "Helpers" line and "Resources" line.
//% * Your group name should be "P3_<userid1>_<userid2>" (eg. P3_stu1_stu2)
//% * Form groups as described at:  https://coursys.sfu.ca/docs/students
//% * Submit one or two files to coursys.sfu.ca
//
// Name        : TreeNode.hpp
// Description : Course Project Part 3 (Directory Tree)
// Copyright   : Original Portions Copyright (c) 2023 School of Engineering Science
//============================================================================

#pragma once

#include <vector>
#include <memory>
#include <algorithm>
//#define USE_OSS

#ifndef USE_OSS
#include <iostream>
#define OUT std::cout
#else
#include <sstream>
extern std::ostringstream oss;
#define OUT oss
#endif

namespace ensc251 {

	class TreeNode {
	private:
	   inline static int count; // should automatically initialize to 0

	protected:
      typedef std::shared_ptr<TreeNode> TreeNodeSP;
      typedef std::vector<TreeNodeSP> TreeNodeSPVect;
		typedef void (TreeNode::*action_func)(void);
		typedef void (TreeNode::*traverse_func)(void);
      TreeNodeSPVect childSPVector;

	public:
		virtual ~TreeNode() {
			// do not modify this insertion on OUT
			OUT << "Destroying TreeNode with " << childSPVector.size() << " children."<< std::endl;
		}
		TreeNode() {};

		virtual TreeNodeSP clone() const { return std::make_shared<TreeNode>(*this); };

		TreeNode(const TreeNode& nodeToCopy) {
		if(nodeToCopy.childSPVector.size()){
		for (size_t i = 0; i < nodeToCopy.get_children().size(); ++i)
				this->add_childP(nodeToCopy.childSPVector[i]->clone());
		}

		}
		friend void swap(TreeNode& first, TreeNode& second) // the swap function (should never fail!)
		{
			  // enable ADL (not necessary in our case, but good practice)
			using std::swap;

			swap(first.childSPVector, second.childSPVector);
		}

		TreeNode & operator = (TreeNode other) // note: argument passed by value, copy made!
		{

		if(other.childSPVector.size()>0){
			swap(*this,other);
		}
		return *this;
		}// (current) other will go out of scope and be destroyed

		void add_childP(TreeNodeSP child){
			this->childSPVector.push_back(child);
		}
		void add_children(const TreeNodeSPVect& childPV){ childSPVector.insert(childSPVector.end(), childPV.begin(), childPV.end()); }

		const TreeNodeSPVect& get_children() const { return childSPVector; }

		void traverse_children_post_order(traverse_func tf, action_func af)
		{
			for(auto childP : childSPVector)
				(childP.get()->*tf)();
			(this->*af)();
		}

		void traverse_children_in_order(traverse_func tf, action_func af)
		{
			if(childSPVector.size() != 2) {
				OUT << "Error -- can only do inorder traversal on a node with 2 children" << std::endl;
			}
			(this->childSPVector[0].get()->*tf)();
			(this->*af)();
			(this->childSPVector[1].get()->*tf)();
		}

		void traverse_children_pre_order(traverse_func tf, action_func af)
		{
			(this->*af)();
			for(auto childP : childSPVector) {
				(childP.get()->*tf)();
			}
		}

		void count_action()
		{
			count++;
		}

		void count_traverse()
		{
			traverse_children_post_order(&ensc251::TreeNode::count_traverse, &ensc251::TreeNode::count_action);
		}
		void reset_count() { count = 0; }
		unsigned get_count() const { return count; }
	};
}
