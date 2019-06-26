//============================================================================
// Name        : Assignment2.cpp
// Author      : Ryan Mansoor
// Version     :
// Copyright   : 
// Description : Hello World in C++, Ansi-style
//============================================================================

/// include here all the headers you need (but see guidelines)
#include <iostream>
#include <vector>
#include <cmath>



struct bdnode{
	std::string val;
	bdnode* left;
	bdnode* right;

};


typedef bdnode* bdt;


bdt buildcompactbdt(const std::vector<std::string>& fvalues);
std::string evalcompactbdt(bdt t, const std::string& input);

//additional functions
bdt reduceTree(bdt t);
bool check(bdt t1, bdt t2);
void verifybdt(int length, std::string inputCase, bdt t);
void deleteTree(bdt t);
int countnodes(bdt t);







int main(){
	std::vector<std::string> input;
	std::cout<<"Enter number of true values"<<std::endl;
	int n;
	std::cin>>n;
	for (int i=0;i<n;i++){

	std::cout<<"Enter value "<<i+1<<std::endl;
	std::string temp;
	std::cin>>temp;
	input.push_back(temp);

	}

	//input.push_back("101101");
	//input.push_back("100101");
	//input.push_back("110001");
	//input.push_back("111101");
	//input.push_back("111111");
	bdt t = buildcompactbdt(input);
	std::cout<<t->val<<std::endl;


	std::cout<< evalcompactbdt(t, "11111")<<std:: endl;

	int length = 0;
	if(!input.empty()){
	length = input[0].length();
	}
	std::string inputCase;
	verifybdt(length,inputCase, t);
	int count = countnodes(t);
	std::cout<< "count = "<<count<<std::endl;

	for (int i=0;i<input.size();i++){

	std::cout<<input[i]<<std::endl;


	}
	/// write the code for the main here in order to test your functions

	return 0;
}

bdt buildcompactbdt(const std::vector<std::string>& fvalues){
	/// write the implementation for the function here
	bdt t = new bdnode();
	t->val="x1";
	bdt current = t;


	const int size = fvalues.size();
	std::cout<<"size "<<size<<std::endl;
	//below are the extreme cases for which the tree reduces to one node with a 0 or 1

		if (fvalues.empty()){
			std::cout<<"size "<<size<<std::endl;
			t->val = "0";
			return t;
		}

		const int height = fvalues[0].length();
		//if the size of the a
		if(size == pow(2,height)){
				t->val = "1";
				return t;
			}
	for (int i = 0; i<size;i++){
		for (int j = 0; j<height;j++){
			if (fvalues[i].substr(j,1)=="0"){
				if(current->right == NULL){
					bdt temp = new bdnode();
					temp->val="0";
					current->right=temp;
				}
				if(j<height-1){
					if (current->left ==NULL){
						bdt temp2 = new bdnode();
						current->left = temp2;
					}
					current ->left->val = "x"+ std::to_string(j+2);
					current = current->left;

				}else{
					if (current->left==NULL){
						bdt temp2 = new bdnode();
						temp2->val="1";
						current->left=temp2;
						current = t;
					}else{
						current->left->val="1";
						current = t;
					}
				}


			}else if (fvalues[i].substr(j,1)=="1"){
				if(current->left == NULL){
					bdt temp = new bdnode();
					temp->val="0";
					current->left=temp;
				}
				if(j<height-1){
					if (current->right ==NULL){
						bdt temp2 = new bdnode();
						current->right = temp2;
					}
					current ->right->val = "x"+ std::to_string(j+2);
					current = current->right;

				}else{
					if (current->right==NULL){
						bdt temp2 = new bdnode();
						temp2->val="1";
						current->right=temp2;
						current = t;
					}else{
						current->right->val="1";
						current = t;
					}
				}
			}
		}
	}

	t = reduceTree(t);
	return t;
}

std::string evalcompactbdt(bdt t, const std::string& input){
	/// write the implementation for the function here
	bdt temp = t;
	for (int i = 0; i<input.length();i++){
		if ("x"+ std::to_string(i+1)==temp->val){
			if(input.substr(i,1)=="0"){
				temp = temp->left;
			}else if (input.substr(i,1)=="1"){
				temp = temp->right;
			}
		}

	}
	return temp->val;
}


/// add here the implementation for any other functions you wish to define and use
void verifybdt(int length, std::string inputCase, bdt t)
{
	if (t == NULL)
	{
	}
	else if (length == 0)
	{
		std::cout << inputCase + "| " + evalcompactbdt(t, inputCase) << std::endl;
	}
	else
	{
		verifybdt(length-1, inputCase + "0", t);
		verifybdt(length-1, inputCase + "1", t);
	}
}

bdt reduceTree(bdt t)
{

	if(t->val=="0"||t->val=="1") return t;

	else
	{
		t->left = reduceTree(t->left);
		bdt leftChild = t->left;
		t->right = reduceTree(t->right);
		bdt rightChild = t->right;
		if (check(leftChild,rightChild)){
			t->val = leftChild->val;
			t->left= leftChild->left;
			t->right = leftChild->right;
			delete leftChild;
			deleteTree(rightChild);
		}
	}

	return t;
}

bool check(bdt t1, bdt t2)
{
	if (t1 == NULL && t2 == NULL) return true;
	if (t1 == NULL || t2 == NULL) return false;
	return (t1->val == t2->val   &&
			check(t1->left, t2->left) &&
			check(t1->right, t2->right) );
}

void deleteTree(bdt t)
{
	if (t == NULL) return;
	deleteTree(t->left);
	deleteTree(t->right);
	delete t;
}
int countnodes(bdt t)
{
    if (t == NULL)
    {
        return 0;
    }
    else
    {
        return 1 + countnodes(t->left) + countnodes(t->right);
    }
}
