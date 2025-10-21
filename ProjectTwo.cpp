//============================================================================
// Name        : ProjectTwo.cpp
// Author      : Ken Smith
// Version     : 1.0
// Copyright   : Copyright � 2023 SNHU COCE
// Description : Project Two: courses in a data structure
//============================================================================

#include <iostream>
#include <time.h>
#include <vector>
#include <fstream>
#include <string>
//#include "CSVparser.hpp"

using namespace std;

//============================================================================
// Global definitions visible to all methods and classes
//============================================================================


// define a structure to hold course information
struct Course {
    string courseId; // unique identifier
    string title;
    vector<string> prereqs;
    
};

// forward declarations
double strToDouble(string str, char ch);
void displayCourse(Course course);

// Internal structure for tree node
struct Node {
    Course course;
    Node *left;
    Node *right;

    // default constructor
    Node() {
        left = nullptr;
        right = nullptr;
    }

    // initialize with a course
    Node(Course aCourse) :
            Node() {
        course = aCourse;
    }
};

//============================================================================
// Binary Search Tree class definition
//============================================================================

/**
 * Define a class containing data members and methods to
 * implement a binary search tree
 */
class BinarySearchTree {

private:
    Node* root;

    void addNode(Node* node, Course course);
    void inOrder(Node* node);
    void postOrder(Node* node);
    void preOrder(Node* node);
    void recursiveDelete(Node* node);
    Node* removeNode(Node* node, string courseId);

public:
    BinarySearchTree();
    virtual ~BinarySearchTree();
    void InOrder();
    void PostOrder();
    void PreOrder();
    void Insert(Course course);
    void Remove(string courseId);
    Course Search(string courseId);
    bool IsEmpty();
};

/**
 * Default constructor
 */
BinarySearchTree::BinarySearchTree() {
    // FixMe (1): initialize housekeeping variables
    this->root = nullptr;
    //root is equal to nullptr
}

/**
 * Destructor
 */
BinarySearchTree::~BinarySearchTree() {
    // recurse from root deleting every node
    recursiveDelete(root);
}

/**
 * Traverse the tree in order
 */
void BinarySearchTree::InOrder() {
    // call inOrder fuction and pass root
    inOrder(root);
}

/**
 * Traverse the tree in post-order
 */
void BinarySearchTree::PostOrder() {
    // postOrder root
    postOrder(root);
}

/**
 * Traverse the tree in pre-order
 */
void BinarySearchTree::PreOrder() {
    // preOrder root
    preOrder(root);
}

/**
*  Helper Function for destructor
*/
void BinarySearchTree::recursiveDelete(Node* node) {
    if (node == nullptr) {
        return;
    }

    recursiveDelete(node->left);
    recursiveDelete(node->right);
    delete node;
    return;
}

/**
 * Insert a course
 */
void BinarySearchTree::Insert(Course course) {
    // if root equarl to null ptr
    if (root == nullptr) {
        // root is equal to new node course
        root = new Node(course);
    }
    // else
    else {
        // add Node root and course
        addNode(root, course);
    }
}

/**
 * Remove a course
 */
void BinarySearchTree::Remove(string courseId) {
    // remove node root courseID
    removeNode(root, courseId);
}

/**
 * Search for a course
 */
Course BinarySearchTree::Search(string courseId) {
    // set current node equal to root
    Node* currNode = root;

    // keep looping downwards until bottom reached or matching courseId found
    while (currNode != nullptr) {
        // if match found, return current course
        if (currNode->course.courseId == courseId) {
            return currNode->course;
        }
        // if course is smaller than current node then traverse left
        if (currNode->course.courseId > courseId) {
            currNode = currNode->left;
        }
        // else larger so traverse right
        else {
            currNode = currNode->right;
        }
    }
    Course course;
    return course;
}

/**
 * Add a course to some node (recursive)
 *
 * @param node Current node in tree
 * @param Course course to be added
 */
void BinarySearchTree::addNode(Node* node, Course course) {
    // FIXME (6b) Implement inserting a course into the tree
    // if node is larger then add to left
    if (node->course.courseId > course.courseId) {
        // if no left node
        if (node->left == nullptr) {
            // this node becomes left
            node->left = new Node(course);
            return;
        }
        // else recurse down the left node
        else {
            addNode(node->left, course);
        }
    }
    // else
    else {
        // if no right node
        if (node->right == nullptr) {
            // this node becomes right
            node->right = new Node(course);
            return;
        }
        //else
        else {
            // recurse down the right node
            addNode(node->right, course);
        }
    }
}

/**
* Recursive traversal in order
*/
void BinarySearchTree::inOrder(Node* node) {
    //if node is not equal to null ptr
    if (node != nullptr) {
        //InOrder node left
        inOrder(node->left);
        //output courseID, title, amount, fund
        displayCourse(node->course);
        //InOder right
        inOrder(node->right);
    }
}

/**
* recursive traversal in post order
*/
void BinarySearchTree::postOrder(Node* node) {
    //if node is not equal to null ptr
    if (node != nullptr) {
        //postOrder left
        postOrder(node->left);
        //postOrder right
        postOrder(node->right);
        //output courseID, title, amount, fund
        displayCourse(node->course);
    }
}

/**
* recursive traversal in prOrder
*/
void BinarySearchTree::preOrder(Node* node) {
    //if node is not equal to null ptr
    if (node != nullptr) {
        //output courseID, title, amount, fund
        displayCourse(node->course);
        //preOrder left
        preOrder(node->left);
        //preOrder right
        preOrder(node->right);
    }
}

/**
 * Remove a course from some node (recursive)
 */
Node* BinarySearchTree::removeNode(Node* node, string courseId) {
    // FIXME (7b) Implement removing a course from the tree
    // if node = nullptr return node
    if (node == nullptr) {
        return node;
    }

    //RECURSION CASES
    // this is not the node we are looking for, go deeper, with recursion.
    if (node->course.courseId != courseId) {
        //std::cout << "course " << node->course.courseId << " is not the course we are looking for." << endl;

        // (otherwise recurse down the left subtree)
        // check for match and if so, remove left node using recursive call
        if (node->course.courseId > courseId) {
            //std::cout << "going to check left\n";
            node->left = removeNode(node->left, courseId);
        }
        // (otherwise recurse down the right subtree)
        // check for match and if so, remove right node using recursive call
        else if (node->course.courseId < courseId) {
            //std::cout << "going to check right\n";
            node->right = removeNode(node->right, courseId);
        }
        return node;
    }
    //REMOVAL CASES
    // this is the node. determine what to do with the children.
    else if (node->course.courseId == courseId) {
        //std::cout << "course " << node->course.courseId << " IS the course we are looking for." << endl;
        // (otherwise no children so node is a leaf node)
        // if left node = nullptr && right node = nullptr delete node 
        if (node->left == nullptr && node->right == nullptr) {
            //std::cout << "No Children. delete this node and return null\n";
            delete node;
            return nullptr;
        }
        // (otherwise check one child to the left)
        // if left node != nullptr && right node = nullptr delete node 
        else if (node->left != nullptr && node->right == nullptr) {
            //std::cout << "One Child on the left. promote the child.\n";
            Node* child = node->left;
            delete node;
            return child;
        }
        // (otherwise check one child to the right)
        // if left node = nullptr && right node != nullptr delete node
        else if (node->left == nullptr && node->right != nullptr) {
            //std::cout << "One Child on the right. promote the child.\n";
            Node* child = node->right;
            delete node;
            return child;
        }
        // (otherwise more than one child so find the minimum)
        else {
            //std::cout << "Two Children...promote the minimum.\n";
            // create temp node to right
            Node* tempNode = node->right;
            // while left node is not nullptr keep moving temp left
            while (tempNode->left != nullptr) {
                tempNode = tempNode->left;
            }
            // make node course (right) equal to temp course (left)
            node->course = tempNode->course;
            // remove right node using recursive call
            removeNode(tempNode, tempNode->course.courseId);
            // return node
        }
    }
}

/**
* Return true if tree is empty
**/
bool BinarySearchTree::IsEmpty() {
    if (root == nullptr) {
        return true;
    }
    else {
        return false;
    }
}


//============================================================================
// Static methods used for testing
//============================================================================

/**
 * Display the course information to the console (std::out)
 *
 * @param course struct containing the course info
 */
void displayCourse(Course course) {
    std::cout << course.courseId << ": " << course.title;
    if (course.prereqs.size() > 0) {
        std::cout << "\nPrerequisites: ";
        for (int i = 0; i < course.prereqs.size(); i++) {
            std::cout << course.prereqs.at(i) << " ";
        }
    }
    std::cout << endl;
    return;
}

/**
* Read a CSV file
* a string for each line is validated
* the strings are added to a vector and returned
**/
vector<string> readFile(string filePath) {
    vector<string> courses;
    ifstream inFS;
    inFS.open(filePath);
    if (!inFS.is_open()) {
        std::cout << "file open failed\n";
        
        cin.ignore();
        cin.clear();
        inFS.clear();
        inFS.close();
        return courses;
    }
    while (!inFS.eof()) {
        string line;
        getline(inFS, line);
        if (!inFS.fail()) {
            courses.push_back(line);
        }
    }
    inFS.close();
    return courses;
}

/**
* parse Course details from provided string
**/
vector<string> parseCourse(string courseInfo) {
    vector<string> course;
    string remaining = courseInfo;
    if (remaining.back() != ', ') {
        remaining.push_back(',');
    }
    //std::cout << "Parsing: " << remaining << endl;
    int start = 0;
    int end = 0;
    while (remaining.size() > 1) {
        end = remaining.find(',');
        if (end == 1) {
            remaining = remaining.substr(end + 1);
            continue;
        }
        string item = remaining.substr(start, end);
        //std::cout << "Identified: " << item << endl;
        course.push_back(item);
        remaining = remaining.substr(end + 1);
        //std::cout << "left with: " << remaining << endl;
        end = 0;
    }
    return course;
}

/**
 * Load a CSV file containing courses into a container
 *
 * @param csvPath the path to the CSV file to load
 * @return a container holding all the courses read
 */
void loadCourses(BinarySearchTree* bst) {
    std::cout << "Enter file path: ";
    string filePath;
    cin.ignore();
    getline(cin, filePath);
    
    std::cout << "attempting to load csv file at " << filePath << endl;
    

    //first read the file
    vector<string> courseDescriptions = readFile(filePath);
    if (courseDescriptions.empty()) {
        cout << "No courses found" << endl;
        return;
    }

    //second build the course objects and add them to the structure, while validating the strings.
    for (int i = 0; i < courseDescriptions.size(); i++) {
        //for now outputting them will have to do.
        std::cout << courseDescriptions.at(i) << endl;
        //bur really I need to split the string on commas, get the different parts, and handle them.
        vector<string> courseParts = parseCourse(courseDescriptions.at(i));
        //now build a course from the course Parts
        Course newCourse;
        newCourse.courseId = courseParts.at(0);
        newCourse.title = courseParts.at(1);
        for (int j = 2; j < courseParts.size(); j++) {
            newCourse.prereqs.push_back(courseParts.at(j));
        }
        //now add it to the tree
        bst->Insert(newCourse);
    }

}

/**
 * Simple C function to convert a string to a double
 * after stripping out unwanted char
 *
 * credit: http://stackoverflow.com/a/24875936
 *
 * @param ch The character to strip out
 */
double strToDouble(string str, char ch) {
    str.erase(remove(str.begin(), str.end(), ch), str.end());
    return atof(str.c_str());
}

/**
 * The one and only main() method
 */
int main(int argc, char* argv[]) {

    // Define a binary search tree to hold all courses and other useful items.
    BinarySearchTree* bst;
    bst = new BinarySearchTree();
    Course course;
    string courseKey;


    int choice = 0;
    while (choice != 9) {
        std::cout << "Menu:" << endl;
        std::cout << "  1. Load Courses" << endl;
        if (!bst->IsEmpty()) {
            std::cout << "  2. Display All Courses" << endl;
            std::cout << "  3. Find Course" << endl;
        }
        std::cout << "  9. Exit" << endl;
        std::cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {

        case 1:
            // Method call to load the courses
            loadCourses(bst);

            //std::cout << bst->Size() << " courses read" << endl;
            break;

        case 2:
            bst->InOrder();
            break;

        case 3:
            cout << "Enter course ID: ";
            
            cin >> courseKey;

            course = bst->Search(courseKey);

            if (!course.courseId.empty()) {
                displayCourse(course);
            } else {
            	std::cout << "course Id " << courseKey << " not found." << endl;
            }

            break;
        default:
            std::cout << "Please enter the number corresponding to your selection" << endl;
            break;
        }
    }

    std::cout << "Good bye." << endl;

	return 0;
}
