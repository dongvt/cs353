/***********************************************************************
* Program:
*    Lab 08, Memory Injection - VULNERABILITIES & EXPLOITS
*    Brother Wilson, CS453
* Authors:
*    Derek Washburn, Govert Carreno, Abhishek Humagain, Josh Nestman
*    Davi Neves, Robert Jones
* Summary:
*    This program explores the vulnerabilities and exploits related to 
*    memory injection attacks. 
*
************************************************************************/

#include <iostream>
#include <iomanip>
#include <string.h>
#include <string>
using namespace std;

//Templates
void displayCallStack(long *p, const int numLongs);
string displayCharArray(const char *p);

// ARRAY INDEX
void arrayVulnerability(int userInput);
void arrayWorking();
void arrayExploit();

//Pointer Subterfuge
void pSubterfugeVulnerability();
void pSubterfugeWorking();
void pSubterfugeExploit();

// ARC 
void ARCVulnerability(int position, long input);
void ARCWorking();
void ARCExploit();
void ARCSafe();
void ARCDangerous();

// VTable
void vTableWorking();
void vTableExploit();

// Stack 
void stackVulnerability(char *inputPassword, int size);
void stackWorking();
void stackExploit();

// Heap
void heapVulnerability(char *input, int size);
void heapWorking();
void heapExploit();

// Integer Overflow
void integerVulnerability(string sentence);
void integerWorking();
void integerExploit();

// ANSI-Unicode conversion
void ANSIVulnerability(int *grades, int size);
void ANSIWorking();
void ANSIExploit();

//VTable
class Vulnerability
{
public:
  virtual void safe();
  virtual void dangerous();
  virtual void set(int index, long value);

private:
  long buffer[1];
};

class Vulnerability2 : public Vulnerability
{
};

/*******************************************
* Sets the value at an index in the buffer. 
********************************************/
void Vulnerability::set(int index, long value)
{
  buffer[index] = value;
  cout << "Setting " << value << " in index " << index << ".\n";
}
/*******************************************
* Represents a safe method. 
********************************************/
void Vulnerability::safe()
{
  cout << "This method is safe.\n";
}
/*******************************************
* Represents an unsafe method. 
********************************************/
void Vulnerability::dangerous()
{
  cout << "This method is dangerous.\n";
}
/*******************************************
* Example of using set without a vulnerability.
********************************************/
void vtableWorking()
{
  Vulnerability v;
  v.set(1, 0);
  cout << "Successfully changed data in buffer\n";
}
/*******************************************
* Example of exploiting the vulernablilty. 
********************************************/
void vtableExploit()
{
  cout << "Executing exploit. Program is about to crash.\n";
  Vulnerability v;
  v.set(345324, 3);
}

// MAIN
int main()
{

  cout << "Which vulnerability would you like to test?" << endl
       << "[1] Array Index" << endl 
       << "[2] Pointer subterfuge" << endl
       << "[3] ARC Injection" << endl
       << "[4] VTable Spraying" << endl 
       << "[5] Stack Smashing" << endl
       << "[6] Heap Spraying" << endl
       << "[7] Integer Overflow" << endl
       << "[8] ANSI-Unicode Conversion" << endl;
  string input;
  int vulnerabilityOption;

  while (true)
  {
    cout << "Option: ";
    getline(cin, input);

    if (input.length() == 1)
    {
      vulnerabilityOption = input[0] - '0';

      switch (vulnerabilityOption)
      {
      case (1):
        arrayWorking();
        arrayExploit();
        break;
      case (2):
        pSubterfugeWorking();
        pSubterfugeExploit();
        break;
      case (3):
        ARCWorking();
        ARCExploit();
        break;
      case (4):
        vtableWorking();
        vtableExploit();
        break;
      case (5):
        stackWorking();
        stackExploit();
        break;
      case (6):
        heapWorking();
        heapExploit();
        break;
      case (7):
        integerWorking();
        integerExploit();
        break;
      case (8):
        ANSIWorking();
        ANSIExploit();
        break;
      default:
        cout << "Invalid option, please try again" << endl;
        continue;
      }

      cout << endl;
      break;
    }

    cout << "Invalid option, please try again" << endl;
  }
}

/*************************************
 * ARRAY VULNERABILTY
 * 1. There must be an array and an array index variable.
 * 2. The array index variable must be reachable through external input.
 * 3. There must not be bounds checking on the array index variable.
 ****************************************/
void arrayVulnerability(int userInput)
{
  int array[3];
  bool authenticated = false;

  cout << "Authenticating User... \n";

  array[userInput] = -1;
  if (authenticated == true)
  {
    cout << "You have been succesfully authenticated!" << endl;
  }
  else
  {
    cout << "You shall not pass!!!" << endl;
  }
}

/**************************************
 * ARRAY WORKING
 * Call arrayVulnerability() in a way that does
 * not yield unexpected behavior
 *************************************/
void arrayWorking()
{
  cout << "Array Indexing Working:\n";
  arrayVulnerability(0);
  cout << endl;
}

/**************************************
 * ARRAY EXPLOIT
 * 1. The attacker provides an array index value outside the
 *    expected range.
 * 2. The attacker must be able to provide input or redirect
 *    existing input into the array at the index he provided.
 * 3. The injected value must alter program state in a way
 *    that is desirable to the attacker.
 *************************************/
void arrayExploit()
{
  cout << "Array Index Exploit:\n";
  arrayVulnerability(-1);
}

/************************************
* Arc-Injection
* 1. There must be a function pointer used in the code.
* 2. Through some vulnerability, there must be a way for user input to
*    overwrite the function pointer. This typically happens through a stack
*    buffer vulnerability.
* 3. After the memory is overwritten, the function pointer must be
*    dereferenced.
************************************/
void ARCSafe()
{
  cout << "ARCSafe succesfully called" << endl;
}

void ARCDangerous()
{
  cout << "ARCDangerous called" << endl;
}

void ARCVulnerability(int position, long input)
{
  long buffer[1];
  void (*pointerFunction)() = ARCSafe;
  buffer[position] = input;

  pointerFunction();
}

/**************************************
 * ARC WORKING
 * Call ARCVulnerability() in a way that does
 * not yield unexpected behavior
 *************************************/
void ARCWorking()
{
  cout << endl
       << "Function working as intended" << endl;
  ARCVulnerability(0, 1);
}

/**************************************
 * ARRAY EXPLOIT
 * 1. The attacker must exploit a vulnerability allowing 
 *    unintended access to the pointer.
 * 2. The attacker must be able to provide a new pointer 
 *    referring to data altering the normal flow of the program.
 *************************************/
void ARCExploit()
{
  cout << "Function exploited" << endl;
  //cout << (void *) ARCDangerous << endl;
  ARCVulnerability(1, 4208288);
}

/*************************************
 * Pointer Subterfuge Vulnerability
 * There must be a pointer used in the code.
 * Through some vulnerability, there must be a way for user input to overwrite the pointer.
 * After the pointer is overwritten, the pointer must be dereferenced.
 **************************************/
void pSubterfugeVulnerability(long *aBuff, int size)
{

  char *pointer = "The original text";
  long buffer[1] = {25};
  //overwrite
  for (int i = 0; i < size; i++)
  {
    buffer[i] = aBuff[i];
  }
  cout << pointer << endl;
}

/***********************************************************
 * Pointer Subterfuge Working
 * Use the vulneravility without exploiting it
 ***********************************************************/
void pSubterfugeWorking()
{
  long list[1] = {16};
  pSubterfugeVulnerability(list, 1);
}

/***********************************************************
 * Pointer Subterfuge Exploitation
 * 1. The attacker must exploit a vulnerability allowing
 * unintended access to the pointer
 * 2. The attacker must be able to provide a new pointer
 * referring to data altering the normal flow of the program
 ***********************************************************/
void pSubterfugeExploit()
{
  long list[2] = {16, (long)"new injected text"};
  pSubterfugeVulnerability(list, 2);
}

/************************************************************************
 * HEAP VULNERABILITY
 *  1. There must be two adjacent heap buffers.
 *  2. The first buffer must be reachable through external input.
 *  3. The mechanism to fill the buffer from the external input must not
 *  correctly check for the buffer size.
 *  4. The second buffer must be released before the first.
 *  5. The first buffer must be overrun (extend beyond the intended limits of
 *  the array).
 ***************************************************************************/

void heapVulnerability(char *input, int size)
{
  char *buffer1 = new char[4];
  char *buffer2 = new char[4];

  for (int i = 0; i < size; i++)
  {
    buffer1[i] = input[i];
  }
  displayCallStack((long *)buffer2, 30); //Breaks the callstack
  cout << buffer2 << endl;
  delete[] buffer2;
  delete[] buffer1;
}
/*************************************
 * HEAP WORKING
 ***********************************/
void heapWorking()
{
  char *shortHash = "Hi!!";
  heapVulnerability(shortHash, 4);
}
/*************************************
 * HEAP EXPLOIT
 * 1. The attacker must provide more data into the outwardly facing
 *    heap buffer than the buffer is designed to hold
 * 2. The attacker must know the layout of the Memory Control Block (MCB)
 *    (essentially a linked list) residing just after the buffer
 * 3. The attacker must provide a new MCB containing both the location
 *    of the memory overwrite and the new data to be overwritten
 ***********************************/
void heapExploit()
{
  char *exploitInput = "this is just a longer text";
  heapVulnerability(exploitInput, 26);
}

/**************************************
 * STACK VULNERABILITY
 * 1. There must be a buffer (such as an array) on
 * the stack.
 * 2. The buffer must be reachable from an external
 * input.
 * 3. The mechanism to fill the buffer from the
 * external input must not
 * correctly check for the buffer size.
 * 4. A buffer overrun (extend beyond the intended
 * limits of the array) must
 * extend to the return address on the stack.
 * 
 *************************************/
void stackVulnerability(char *inputPassword, int size)
{

  bool check = false;
  char *storedPassword = "secret"; //6

  cout << &check << endl
       << &storedPassword - 1 << endl
       << &storedPassword + 1 << endl
       << &storedPassword << endl
       << check;

  for (int i = 0; i < size; i++)
  {
    storedPassword[i] = inputPassword[i];
  }

  if(check) {
    cout << "access granted" << endl;
  }
}

/**************************************
 * STACK Working
 * Generates a safe string and
 * calls stackVulnerability()
 *************************************/
void stackWorking()
{
  char inputPassword[6] = "Happy";
  stackVulnerability(inputPassword, 6);
  cout << " stored!\n";
}

/**************************************
 * STACK EXPLOIT
 * Generates a string that contains an
 * instruction leading to a different
 * return address. This string is
 * passed into stackVulnerability()
 *************************************/
void stackExploit()
{
  char *inputPassword = "xxxxx11";
  //cout << "Stack Danger Address: " << (void*) ARCExploit;
  stackVulnerability(inputPassword, 8);
  cout << " stored.\n";
}

/**************************************
 * ANSI-Unicode Conversion - ANSIVulnerability
 * 1. There must be a buffer where the basetype is greater than one. 
 * 2. Validation of the buffer must check the size of the buffer 
 *    rather than the number of elements in the buffer.
 *************************************/
void ANSIVulnerability(int *grades, int size)
{
  //Copy a student's grades into a score card
  int *myGrades = new int[4];

  cout << "New Copy of my Score Card:" << endl;
  for (int i = 0; i < size; i++)
  {
    myGrades[i] = grades[i];
    cout << myGrades[i] << endl;
  }
}
/**************************************
 * ANSI-Unicode Conversion - ANSIWorking
 * Carefully distinguish between sizeBuffer and numElements. The former is the size in bytes while the latter is the number of elements in the buffer.

 *************************************/
void ANSIWorking()
{
  cout << "ANSI-Unicode Conversion Working" << endl;

  int grades[2] = {89, 95};
  int size = sizeof(grades);

  ANSIVulnerability(grades, size);

  cout << "Size of the buffer: " << sizeof(grades) << endl;
  cout << "Number of elements in the array: " << sizeof(grades) / sizeof(grades)[0] << endl
       << endl;
}
/**************************************
 * ANSI-Unicode Conversion - ANSIExploit
 * 1. The attacker must provide more than half as much data into the outwardly facing buffer as it is designed to hold. 2. From here, a variety of injection attacks are possible. The most likely candidates are stack smashing or heap smashing. In the example below the function ANSIExploit has 4 elements in the array myGrades, not the size of the array (16 bytes). The end result is a buffer overrun of 12 bytes.
*************************************/
void ANSIExploit()
{
  cout << "Exploitation of Vulnerable ANSI-Unicode Conversion" << endl;

  int grades[4] = {89, 95, 105, 111};
  int size = sizeof(grades);

  ANSIVulnerability(grades, size);

  cout << "Size of the buffer: " << sizeof(grades) << endl;
  cout << "Number of elements in the array: " << sizeof(grades) / sizeof(grades)[0] << endl
       << endl;

  //When the function ANSIVulnerability(list) is called and the array with 8 elements is sent to the vulnerable loop, a buffer overrun happens.

  //for(int i = 0; i < sizeof(grades);i++){
  //  myGrades[i] = grades[i];
  //  cout << myGrades[i] << endl;
  //}
}

/**************************************
 * Integer Overflow
 * When the size of a value exceeds the 
 * amount a data type can hold.
 *************************************/
void integerVulnerability(string sentence)
{
  short count = sentence.length();
  char upper[50];

  for (int i = 0; i < count; i++)
  {
    upper[i] = toupper(sentence[i]);
    cout << upper[i];
  }
  cout << endl;
}

/**************************************
 * Integer Overflow Working
 *************************************/
void integerWorking()
{
  string text = "Hello World!";
  integerVulnerability(text);
}

/**************************************
 * Integer Overflow Exploit
 *************************************/
void integerExploit()
{
  string text = "Lorem ipsum dolor sit amet consectetur, adipisicing elit. Debitis praesentium architecto fuga, explicabo magni iure nam placeat dolor voluptatum iste nihil exercitationem officia omnis, molestias molestiae delectus laboriosam ratione maiores. Lorem ipsum dolor sit amet consectetur, adipisicing elit. Debitis praesentium architecto fuga, explicabo magni iure nam placeat dolor voluptatum iste nihil exercitationem officia omnis, molestias molestiae delectus laboriosam ratione maiores. Lorem ipsum dolor.";

  integerVulnerability(text);
}

//A modification of the lab07 two function
void displayCallStack(long *pointer, const int numLongs)
{

  cout << '[' << setw(2) << 'i' << ']'
       << setw(15) << "address"
       << setw(20) << "hexadecimal"
       << setw(20) << "decimal"
       << setw(18) << "characters"
       << endl;
  cout << "----+"
       << "---------------+"
       << "-------------------+"
       << "-------------------+"
       << "-----------------+\n";

  // set the pointer's value (numLongs - 1)*sizeof(long)
  // up in the stack
  pointer = pointer + (numLongs - 1);
  for (int i = numLongs; i >= -4; i--)
  {
    pointer--;

    cout << '[' << setw(2) << i << ']'
         << setw(15) << (void *)pointer
         << setw(20) << hex << showbase << *pointer
         << setw(20) << dec << *pointer
         << setw(18) << displayCharArray((char *)pointer) << endl;
  }
}

//From lab07
string displayCharArray(const char *p)
{
  string output;
  for (int i = 0; i < 8; i++)
    output += string(" ") + (p[i] >= ' ' && p[i] <= 'z' ? p[i] : '.');
  return output;
}
