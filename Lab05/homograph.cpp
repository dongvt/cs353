#include <string>
#include <iostream>
#include <fstream>
#include <deque>
#include <stdio.h>  /* defines FILENAME_MAX */
#include <unistd.h>
#define GetCurrentDir getcwd
using namespace std;

//************************************************************************
// Test Functions
#define assert(expected, actual) customAssert(expected, actual, __LINE__)

void customAssert(bool expected, bool actual, int line);
void runTests();
void test_H_doubleDots();
void test_H_tilda();
void test_H_singleDot();
void test_H_everythingTogether();
void test_H_reallyWeirdOnes();
void displayTest(string path1, string path2, bool isHomograph);
//*************************************************************************

string C(string encoding);
void R();
bool H(string path1, string path2);

int main() {

  string userInput;

  cout << "Enter 1: Test cases." << endl;
  cout << "Enter 2: Manual test cases." << endl << " > ";
  cin >> userInput;

  if (userInput == "1")
  {

   string testfilename1;
   string testfilename2;

   cout << "Enter Path 1: ";
   cin >> testfilename1;
   cout << "Enter Path 2: ";
   cin >> testfilename2;

  cout << endl << endl;
    if(H(testfilename1,testfilename2))
  {
    cout << "\nThe paths are homographs\n";
  }
  else
  {
    cout << "\nThe paths are not homographs\n";
  }
  }
  else if (userInput == "2")
 {
  //chdir("cs453/week05");

  // cout << "Specify the first filename: ";
  // cin >> fileName1;
  // // cerr << fileName1 << endl;

  // cout << "Specify the second filename: ";
  // cin >> fileName2;

  runTests();
  // Checking if paths are homographs

 }
 else
 {
    cout << "Incorrect Input. Exiting program.\n";
 }
}

// function to split string into substrings on the
// basis of delimiter and return the substrings
// after split
// snagged from https://www.geeksforgeeks.org/how-to-split-a-string-in-cc-python-and-java/
deque<string> splitStrings(string str, char dl)
{
    string word = "";

    // to count the number of split strings
    int num = 0;

    // adding delimiter character at the end
    // of 'str'
    // str += dl;
    str = str + dl;

    // length of 'str'
    int l = str.size();

    // traversing 'str' from left to right
    deque<string> substr_list;
    
    for (int i = 0; i < l; i++) {

        // if str[i] is not equal to the delimiter
        // character then accumulate it to 'word'
        if (str[i] != dl)
            word = word + str[i];

        else {

           // if 'word' is not an empty string,
            // then add this 'word' to the array
            // 'substr_list[]'
            if ((int)word.size() != 0)
                substr_list.push_back(word);

            // reset 'word'
            word = "";
        }
    }

    // return the splitted strings
    return substr_list;
}

/*
  Summary: Returns home directory path represented as a deque
  Input: NA
  Output: deque<string> representing cwd
*/
deque<string> getHomePathDeque(){
  deque<string> path;
  char buff[FILENAME_MAX];
  GetCurrentDir( buff, FILENAME_MAX );
  std::string current_working_dir(buff);
  current_working_dir.erase(0,1);
  string delimiter = "/";
  string rootDir = current_working_dir.substr(0, current_working_dir.find(delimiter));

  path.push_back(rootDir);
  current_working_dir.erase(0, rootDir.length());
  current_working_dir.erase(0,1);
  string secondDir = current_working_dir.substr(0, current_working_dir.find(delimiter));
  path.push_back(secondDir);

  return path;
}

// Returns cwd path string
string getCwdStr(){
  char buff[FILENAME_MAX];
  GetCurrentDir( buff, FILENAME_MAX );
  string current_working_dir(buff);
  return current_working_dir;
}

/*
Summary: Returns cwd represented as a deque
Input: NA
Output: deque<string> representing cwd
*/
deque<string> getCwdDeque(){
  deque<string> cwd;

  string cwdStr = getCwdStr().erase(0,1);
  cwd = splitStrings(cwdStr, '/');

  // // Previous hardcoded values
  // cwd.push_back("home");
  // cwd.push_back("runner");
  // cwd.push_back("HomographProject");

  return cwd;
}

/*
Summary: Reads a path string and returns the first directory symbol
Input: string representing part of a path
Output: string representing directory symbol
*/
string getNextDir(string * path){
  string dir;
  if ((*path).at(0) == '/')
  {
    (*path).erase(0,1);
  }
  string delimiter = "/";
  dir = (*path).substr(0, (*path).find(delimiter));
  int numToErase = dir.length();
  (*path).erase(0, numToErase);
  return dir;
}

/*
  Summary: Return the absolute path of a file given the cwd and it's
  relative filepath
  Input: deque<string> representing cwd
  Output: deque<string> representing absolute path
*/
deque<string> getAbsPathDeque(deque<string> startingPath, string relPath){
  string dir;
  deque<string> absPath = startingPath;

  while (relPath.length() > 0){
    dir = getNextDir(&relPath);
    if (dir == ".")
      continue;
    if (dir == ".."){
      absPath.pop_back();
      continue;
    }
    absPath.push_back(dir);
  }

  return absPath;
}
/*
Summary: Return the absolute path of a file in string form
Input: deque<string> representing absolute path
Output: string representing absolute path
*/
string getAbsPathStr(deque<string> absPathDeque){
  string absPathStr;

  while(!absPathDeque.empty()){
    absPathStr += "/" + absPathDeque.front();
    absPathDeque.pop_front();
  }

  return absPathStr;
}

/*
Summary: Return the canonized path
Input: e, encoding, a relative file path
Output: c, canon, the absolute file path (canonical)
*/
string C(string encoding) {
  ///cerr << encoding;
  //cout << encoding;
  string canon;
  deque<string> startingPath;

  // encoding is an absolute path
  if (encoding.at(0) == '/'){
    canon = encoding;
    return canon;
  }
  // start at home folder
  if (encoding.at(0) == '~'){
    startingPath = getHomePathDeque();
    encoding.erase(0,2);
  }
  else {
    // get absolute path of cwd
    startingPath = getCwdDeque();
  }

  // get absolute path of encoding as deque
  deque<string> absPath = getAbsPathDeque(startingPath, encoding);

  // get absolute path of encoding as string
  string absPathStr = getAbsPathStr(absPath);

  canon = absPathStr;
  return canon;
}

/*
Summary:
This function compares the canonized filepaths to see if they are
homographs. If they are it returns true if not it returns false.
Input: 2 filepaths
Output: A boolean value
*/
bool H(string path1, string path2)
{
  if(C(path1) == C(path2))
  {
    return true;
  }
  else
  {
    return false;
  }
}

//*************************************************
//Tests
void customAssert(bool expected, bool actual, int line)
{
   if (expected != actual)
   {
      cout << "---------------------------\n";
      cout << "Failed test on line " << line << ".\n";
      cout << "Expected: " << expected << endl;
      cout << "Actual: " << actual << endl;
      cout << "---------------------------\n";
   }

}

void runTests()
{
   test_H_doubleDots();
   test_H_tilda();
   test_H_singleDot();
   test_H_everythingTogether();
   test_H_reallyWeirdOnes();
}

void test_H_doubleDots()
{

   // Test 1: Homograph
   string path1 = "cs453/week05/test.txt";
   string path2 = "cs453/week05/../../cs453/week05/test.txt";
   bool isHomograph = H(path1, path2);
   displayTest(path1, path2, isHomograph);
   assert(true, isHomograph);

   // Test 2: Homograph
   path1 = "cs453/../cs453";
   path2 = "cs453";
   isHomograph = H(path1, path2);
   displayTest(path1, path2, isHomograph);
   assert(true, isHomograph);

   // Test 3: Homograph
   path1 = "cs453/week05/test.txt";
   path2 = "cs453/../cs453/week05/../week05/test.txt";
   isHomograph = H(path1, path2);
   displayTest(path1, path2, isHomograph);
   assert(true, isHomograph);


   // Test 4: Not Homograph
   path1 = "../../cs453/week06/test.txt";
   path2 = "../../cs453/week05/test.txt";
   isHomograph = H(path1, path2);
   displayTest(path1, path2, isHomograph);
   assert(false, isHomograph);

   // Test 5: Not Homograph
   path1 = "../../cs453/week05/test.txt";
   path2 = "../../cs453/week05/../test.txt";
   isHomograph = H(path1, path2);
   displayTest(path1, path2, isHomograph);
   assert(false, isHomograph);

   // Test 6: Not Homograph
   path1 = "../test.txt";
   path2 = "test.txt";
   isHomograph = H(path1, path2);
   displayTest(path1, path2, isHomograph);
   assert(false, isHomograph);
}

void test_H_tilda()
{
  // Test 7: Homograph
   string path1 = "~/HomographProject/home/text.txt";
   string path2 = "HomographProject/home/text.txt";
   bool isHomograph = H(path1, path2);
   displayTest(path1, path2, isHomograph);
   assert(true, isHomograph);

   // Homograph
   path1 = "~/file.txt";
   path2 = "file.txt";
   isHomograph = H(path1, path2);
   displayTest(path1, path2, isHomograph);
   assert(true, isHomograph);

   // Not Homograph
   path1 = "~/home/cs270/text.txt";
   path2 = "~/home/cs453/text.txt";
   isHomograph = H(path1, path2);
   displayTest(path1, path2, isHomograph);
   assert(false, isHomograph);

   // Not Homograph (Don't test as if your in the ~ directory.)
   path1 = "pizza/is/really/yummy.txt";
   path2 = "pizza/is/really/~/yummy.txt";
   isHomograph = H(path1, path2);
   displayTest(path1, path2, isHomograph);
   assert(false, isHomograph);
}

void test_H_singleDot()
{
   // Homograph
   string path1 = "home/./././cookies.txt";
   string path2 = "home/cookies.txt";
   bool isHomograph = H(path1, path2);
   displayTest(path1, path2, isHomograph);
   assert(true, isHomograph);

   // Homograph
   path1 = "./user/cs453/text.txt";
   path2 = "././././user/./././cs453/./././text.txt";
   isHomograph = H(path1, path2);
   displayTest(path1, path2, isHomograph);
   assert(true, isHomograph);

   // Homograph
   path1 = "test.txt";
   path2 = "././././test.txt";
   isHomograph = H(path1, path2);
   displayTest(path1, path2, isHomograph);
   assert(true, isHomograph);

   // Not Homograph
   path1 = "././home/cookies.txt";
   path2 = "week05/cookies.txt";
   isHomograph = H(path1, path2);
   displayTest(path1, path2, isHomograph);
   assert(false, isHomograph);
}

void test_H_everythingTogether()
{
  // Homograph
  string path1 = "home/../home/./cs124/tictactoe.cpp";
  string path2 = "home/cs124/tictactoe.cpp";
  bool isHomograph = H(path1, path2);
  displayTest(path1, path2, isHomograph);
  assert(true, isHomograph);

  // Homograph
  path1 = "home/cs124/assign3/main.cpp";
  path2 = "~/home/../home/./././cs124/./././assign3/main.cpp";
  isHomograph = H(path1, path2);
  displayTest(path1, path2, isHomograph);
  assert(true, isHomograph);

  // Not Homograph
  path1 = "~/home/../home/../home/../home/./text.txt";
  path2 = "~/text.txt";
  isHomograph = H(path1, path2);
  displayTest(path1, path2, isHomograph);
  assert(false, isHomograph);

}

void test_H_reallyWeirdOnes()
{
  // Not Homograph
  string path1 = "home/.../test.text";
  string path2 = "home/../test.text";
  bool isHomograph = H(path1, path2);
  displayTest(path1, path2, isHomograph);
  assert(false, isHomograph);

  // Not Homograph
  path1 = "home/~/text.txt";
  path2 = "text.txt";
  isHomograph = H(path1, path2);
  displayTest(path1, path2, isHomograph);
  assert(false, isHomograph);

  // Not Homograph
  path1 = "//text.txt";
  path2 = "test.txt";
  isHomograph = H(path1, path2);
  displayTest(path1, path2, isHomograph);
  assert(false, isHomograph);

}

void displayTest(string path1, string path2, bool isHomograph)
{
  cout << "-------------------------------------" << endl;
  cout << "Comparing" << endl;
  cout << "\tPath 1: " << path1 << endl;
  cout << "\tPath 2: " << path2 << endl;

  if (isHomograph)
  {
    cout << "The paths are homographs\n";
  }
  else
  {
    cout << "The paths are not homographs\n";
  }

}
//*********************************************