/***********************************************************************
* Program:
*    Lab 07, Memory Organizarion
*    Brother Wilson, CS453
* Authors:
*    Derek Washburn, Govert Carreno, Abhishek Humagain, Josh Nestman
*    Davi Neves, Robert Jones
* Summary:
*    This program explores how our compiler utilizes the call stack and 
*    the heap segments of memory. 
*
************************************************************************/

#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

void one(long number);
void two(long number);
void pass() { cout << "You pass :)\n"; }
void fail() { cout << "You've failed :(\n"; }
const char * passMessage = ":)";
const char * failMessage = ":(";

/**********************************************
 * MAIN : The top of the callstack.
 **********************************************/
int main()
{
   char text[8] = "*MAIN**";
   long number = 123456;
   void (*pointerFunction)() = fail;
   const char * message = failMessage;

   // display the initial values of the local variables
   cout << "main() : " << (void *)main << endl;
   cout << "\ttext:             " << text              << endl;
   cout << "\tnumber:           " << number            << endl;
   cout << "\tmessage:          " << message           << endl;
   cout << "\tfunction pointer: ";
   pointerFunction();

   // call the other functions
   one(number + 111111);     // 234567

   // display the new values of the local variables
   cout << "main() - after\n";
   cout << "\ttext:             " << text              << endl;
   cout << "\tnumber:           " << number            << endl;
   cout << "\tmessage:          " << message           << endl;
   cout << "\tfunction pointer: ";
   pointerFunction();

   return 0;
}

/************************************************
 * CONVERT TO STRING
 * Convert the data from p into a human-readable string
 * by removing all the unprintable characters and replacing
 * them with a dot
 ***********************************************/
string displayCharArray(const char * p)
{
   string output;
   for (int i = 0; i < 8; i++)
       output += string(" ") + (p[i] >= ' ' && p[i] <= 'z' ? p[i] : '.');
   return output;
}

/**********************************************
 * ONE : The next item on the call stack
 **********************************************/
void one(long number)               // 234567
{
   char text[8] = "**ONE**";

   cout << "one() : " << (void *)one << endl;
   cout << "\tmessage: " << (void *)failMessage << endl;
   cout << "\tfail():  " << (void *)fail        << endl;

   two(number + 111111);    // 345678
}

/**********************************************
 * TWO : The bottom of the call stack
 **********************************************/
void two(long number)              // 345678
{
   // start your display of the stack from this point
   long bow = number + 111111;     // 456789
   char text[8] = "**TWO**";
   long * pLong = NULL;
   char * pChar = NULL;

   // header for our table. Use these setw() offsets in your table
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

   char * current;
   for (long i = 40; i >= -4; i--)   // You may need to change 24 to another number
   {
      ////////////////////////////////////////////////
      // Insert code here to display the callstack
      current = (char*)((char*) &bow + 8 * i);

      cout << '[' << setw(2) << i << ']'
         << setw(15) << (void*)current
         << setw(20) << hex << showbase << *(long*)current
         << setw(20) << dec << *(long*)current
         << setw(18) << displayCharArray(current) << endl;
      //
      ////////////////////////////////////////////////
   }

   ////////////////////////////////////////////////
   // Insert code here to change the variables in main()
   
   pChar = (char *) &bow; //The address converted to char pointer
   //Look in each address for *MAIN**
   while (string(++pChar) != "*MAIN**"){
   }
   cout << pChar << (void *)pChar << endl;

   // change text in main() to "*main**"

   //connot convert string to char pointer easier, so, change one by one
   pChar[1] = 'm';
   pChar[2] = 'a';
   pChar[3] = 'i';
   pChar[4] = 'n';

   cout << pChar << endl;

   // change number in main() to 654321

   pLong = (long *) &bow;
   while(*pLong != 123456)
   {
      pLong++; //increment the pointer address by one byte
   }
   cout << *pLong << endl;
   //once found just change the value in that address
   *pLong = 654321;
   cout << *pLong << endl;

   // change pointerFunction in main() to point to pass
   pLong = (long *) &bow;
   while(*pLong != (long long)fail) //This time we look for the function, so convert the addres to long pointer again
   {
      pLong++; //increment the pointer address by one byte
   }
   cout << *pLong << endl;
   //once found, just change the value in that address
   *pLong = (long long)pass;

   cout << *pLong << endl;
   // change message in main() to point to passMessage
   
   pLong = (long *) &bow;
   while(*pLong != (long long)failMessage) //failMessage is a global variable so it shiuold be available here.
   {
      pLong++; //increment the pointer address by one byte
   }
   
   pChar = (char *) *pLong; //Convert the pLong value to char and be able to print and check
   cout << string(pChar)<< endl;
   //once found, just change the value in that address
   *pLong = (long long)passMessage; //convert the pointer to long and store it in pLong
                              //Since pLong is pointing to the same value than message in main is pointing
                              //It should change the message value too.

   pChar = (char *) *pLong;
   cout << string(pChar)<< endl;
   //
   ////////////////////////////////////////////////
}