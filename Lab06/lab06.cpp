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
std::string genQuery(std::string user, std::string pass);
std::string getQueryWeak(std::string user, std::string pass);
std::string getQueryStrong(std::string user, std::string pass);

std::string strongFilter(std::string str);
std::string weakFilter(std::string str);

std::string removeWord(std::string str, std::string word);

/*************************************************************
 * MAIN
 * Prompts the user for two inputs, username and password. 
 * It calls genQuery() to build a single string   
 * (an SQL query) to authenticate the user against a database.
 *************************************************************/
int main()
{
    std::string username, password, query, qStrong, qWeak;

    std::cout << "Enter your username: ";
    std::getline(std::cin, username);
    std::cout << "Enter your password: ";
    std::getline(std::cin, password);

    query = genQuery(username, password);
    qStrong = getQueryStrong(username, password);
    qWeak = getQueryWeak(username, password);

    std::cout << "Vulnerable: " << query << std::endl;
    std::cout << "Strong: " << qStrong << std::endl;
    std::cout << "Weak: " << qWeak << std::endl;

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
 * getQueryWeak
 * Filter the input from spaces, semicolons, 
 * and the keywords sourroneded by spaces: UNION, AND, OR
*****************************************************/
std::string getQueryWeak(std::string user, std::string pass)
{
    std::string query = "";
    user = weakFilter(user);
    pass = weakFilter(pass);
    query = genQuery(user, pass);
    return query;
}

/****************************************************
 * getQueryStrong
 * INPUT: string user, string password
 * OUTPUT: one single string (an SQL query) with string
 * mitigation applyed
 * **************************************************/
std::string getQueryStrong(std::string user, std::string pass)
{
    std::string query = "";
    user = strongFilter(user);
    pass = strongFilter(pass);
    query = genQuery(user, pass);
    return query;
}

/****************************************************
 * strongFilter
 * deletes characters different to: a to z, A to Z, 0 to 9,
 * and the following set of special characters:
 * ! # $ * ?
 * INPUT: string str (a single string)
 * OUTPUT: one single filtered string 
*****************************************************/
std::string strongFilter(std::string str)
{
    std::string filteredStr = "";
    for (int i = 0; i < str.length(); i++)
    {
        char ch = str[i];
        if ((
                (ch <= 'z' && ch >= 'a') || //Lower case
                (ch <= 'Z' && ch >= 'A') || //Upper case
                (isdigit(ch)) || //Digits
                ch == '!' ||                //Special characters
                ch == '#' ||
                ch == '$' ||
                ch == '*' ||
                ch == '?')) 
        {
            filteredStr += ch;
        }
    }
    return filteredStr;
}

/****************************************************
 * weakFilter
 * Filter the input from spaces, semicolons, dashes 
 * and the keywords sourroneded by spaces: UNION, AND, OR
 * INPUT: string str (a single string)
 * OUTPUT: one single filtered string 
*****************************************************/
std::string weakFilter(std::string str)
{
    std::string filteredStr = "";

    //Deleting keywords 
    //Keywords wont work if they are no sorrunded by spaces
    //However, we delete them as part of the known vulneravilities
    str = removeWord(str," UNION ");
    str = removeWord(str," OR ");
    str = removeWord(str," AND ");

    str = removeWord(str," union ");
    str = removeWord(str," or ");
    str = removeWord(str," and ");
    //We can do more homograph, but this is a weak filter

    //Deleting semicolons and spaces
    for (int i = 0; i < str.length(); i++)
    {
        char ch = str[i];
        if (ch != ' ' && ch != ';' && ch != '-')
        {
            filteredStr += ch;
        }
    }
    
    return filteredStr;
}

/**
 * removeWord
 * From: https://www.geeksforgeeks.org/remove-a-given-word-from-a-string/
 * 
 **/
std::string removeWord(std::string str, std::string word)
{

    if (str.find(word) != std::string::npos)
    {
        size_t p = -1;

        std::string tempWord = word + " ";
        while ((p = str.find(word)) != std::string::npos)
            str.replace(p, tempWord.length(), "");

        tempWord = " " + word;
        while ((p = str.find(word)) != std::string::npos)
            str.replace(p, tempWord.length(), "");
    }

    return str;
}
