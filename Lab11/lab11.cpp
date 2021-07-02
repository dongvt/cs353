#include <iostream>
#include <iomanip>
#include <string>
#include <cctype>
#include <math.h>

//templates
double computeCombinations(std::string password);
int computeBits(double combinations);

/**
 * MAIN
 * Driver function
 * */
int main() {
    std::string password = "";
    double combinations = 0;
    std::cout << "Insert password: ";
    std::cin >> password;
    combinations = computeCombinations(password);
    std::cout << std::fixed << std::setprecision(0);
    std::cout << "Possible combinations: " << combinations << std::endl;
    std::cout << "That is equivalent to a key of " << computeBits(combinations) << " bits";
}

/**
 * computeCombinations
 * PARAMS: Password
 * 
 * Computes the number of possible combinations for a given set
 * of characters in a given password
 * */
double computeCombinations(std::string password) {
    int characters = 0;
    //flags for each one (to add to the conbination just once)
    bool upper =  true; 
    bool lower =  true;
    bool symbol = true;
    bool number = true;

    for (int i = 0; i < password.length();i++) {
        if(upper && isupper(password[i])){
            characters += 26;
            upper = false;
        }
        if(lower && islower(password[i])){
            characters += 26;
            lower = false;
        }
        if(symbol && !isalnum(password[i])){
            characters += 32;
            symbol = false;
        }
        if(number && isdigit(password[i])){
            characters += 10;
            number = false;
        }
    }

    //The formula to compute this is: numberOfPosibleChars^passwordLength
    return pow(characters,password.length());
}

/**
 * computeBits
 * PARAM: combinations: a number of possible combinations
 * 
 * Computes the number of bits required for a key of a given password
 * */
int computeBits(double combinations) {
    int bit = 0;

    //incremeent until we pass the possble combinations
    while(pow(2,bit) <= combinations) bit++;

    //as in the reading: we substract 1
    return bit - 1;
}
