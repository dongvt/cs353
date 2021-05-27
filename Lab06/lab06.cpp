/***********************************************************************
* Program:
*    Lab 06, SQL Injection Mitigation
*    Brother Wilson, CS453
* Authors:
*    Derek Washburn, Govert Carreno, Abhishek Humagain, Josh Nestman
*    Davi Neves, Robert Jones
* Summary:
*    This program is a simple authetication code. It prompts the user  
*    for two inputs, username and password. It then builds a single string   
*    (an SQL query) to authenticate the user against a SQL database. 
*    
************************************************************************/

#include <iostream>
#include <string>

//Templates
std::string weak();
std::string strong();
std:: string genQuery(std::string user, std::string pass);

/*************************************************************
 * MAIN
 * Prompts the user for two inputs, username and password. 
 * It calls genQuery() to build a single string   
 * (an SQL query) to authenticate the user against a database.
 *************************************************************/
int main() 
{
    std::string username, password, query, queryTest1;

    std::cout << "Enter your username: ";
    std::getline(std::cin , username);
    std::cout << "Enter your password: ";
    std::getline(std::cin , password);
    query = genQuery(username,password);
    queryTest1 = testUser(username,password);
    
    std::cout << query;
    std::cout << queryTest1;
    return 0;
}

/****************************************************
 * GENQUERY
 * Receives two strings user and password and builds 
 * one single string (an SQL query) 
*****************************************************/
std::string genQuery(std::string user, std::string pass)
{
    std::string query = "SELECT userName FROM users WHERE userName= \'" 
                      + user 
                      + "\' AND password = \'" 
                      + pass
                      + "\'"; 

    return query;
}

/****************************************************
 * Test 1
 * Calls genQuery passes two strings user and password 
 * return one single string (an SQL query) 
*****************************************************/
std::string testUser()
{
    std::string username, password, query;

    //test1: dneves
    username = dneves;
    password = 1234_D2;

    query = genQuery(username,password);
    std::cout << query;

    return query;
}
