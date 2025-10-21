# DataStructuresPractice
A scenario to read in a data file of items. Validate, sort, hold, and output using different data structures. This version uses a binary tree.

The Scenario:
A school wants a program to hold course information consisting of: Course ID, Course Title, and a list of prerequisites.
This information exists in a CSV file and will need to be read, validated, and sorted.
using a command line interface, present a menu with the following options:
- load data (user provides file path)
- output all courses in alphanumeric order by Course ID
- output details for a single course from a course ID provided by the user
- exit the program

Approach
First, consider the functionality of different data structures. Those evaluated included Hash, Vector, and Binary Tree.
  Evaluation included Big O analysis of pseudocode for adding a new item, retrieving all items in alphanumeric order, and searching for a specific item.
Second, select a data structure to use based on the requirements and analysis. Binary tree was selected.
Third, profile the format of the data in the input file in preparation for read/validate operations.
Fourth, write the code.
Fifth, test the code.

Challenges
Of the data structures considered, I am the least familiar with hash tables. Specifically felt challenged when considering how the contents of a hash table could be printed in order.

What I learned
Data structures and the algorithms behind them are incredible. They lurk in the background of every program. 
Using the right one is an opportunity for efficiency. Using the wrong one can expose sensitive information or lead to massive overhead in processing time and memory requirements.

Notes for future projects
This code is not especially adaptable. the binary tree implementation as written here does not handle balancing. It is also not a true example of an abstract data structure, using a specific struct for the data values instead of a template data type. This means the code is not reusable, even though I tried to write it in a clear, maintainable manner.
