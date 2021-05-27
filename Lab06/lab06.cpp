/***********************************************************************
* Program:
*    Lab 06, SQL Injection Mitigation
*    Brother Wilson, CS453
* Authors:
*    Derek Washburn, Govert Carreno, Abhishek Humagain, Josh Nestman
*    Davi Neves, Robert Jones
* Summary:
*    
*    
*    
************************************************************************/

#include <iostream>
#include <string>

std::string weak();
std::string strong();

int main() 
{
    std::string user,pass;

    std::cout << "User: ";
    std::getline(std::cin , user);
    std::cout << "Password: ";
    std::getline(std::cin , pass);

    std::string query = "SELECT userId,userName FROM users WHERE userName= \'" 
                      + user 
                      + "\' AND password = \'" 
                      + pass
                      + "\'"; 

    std::cout << query;

    return 0;
}
