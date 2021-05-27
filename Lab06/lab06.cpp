/**
 * 
 * 
 * 
 * 
 * 
 * 
 * */

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
