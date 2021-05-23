/***********************************************************************
* Program:
*    Week 13, Homographs
*    Brother Wilson, CS453
* Authors:
*    Derek Washburn
* Summary:
*    This program prompts the user to enter two file paths.
*    The paths are compared, taking special characters such as
*    ".", "..", and "~" into account, and the program informs the
*    user whether the two paths are homographs of each other.
************************************************************************/
#include <iostream>
#include <string>
#include <stdio.h> // defines FILENAME_MAX for current directory
#include <algorithm>

#ifdef WINDOWS
#include <direct.h>
#define GetCurrentDir _getcwd
static const char separator = '/';
#else
#include <unistd.h>
#define GetCurrentDir getcwd
static const char separator = '\\';
#endif

//Templates
std::string getTruePath(std::string path);
std::string normalizePath(std::string path);
int initialSlashCount(std::string path);

/**
 * MAIN
 * Prompts the user for two file paths. The paths are
 * compared, and the user is informed whether they are
 * homographs.
 */
int main()
{
    std::string path1;
    std::string path2;

    std::cout << "Insert first path" << std::endl;
    std::cin >> path1;

    std::cout << "Insert second path" << std::endl;
    std::cin >> path2;

    //Normalize strings acorting to operating system
    path1 = normalizePath(path1);
    path2 = normalizePath(path2);

    std::cout << "The paths are " << ((getTruePath(path1) == getTruePath(path2)) ? "" : "NOT") << " homographs" << std::endl;

    return 0;
}

/**
 * GETTRUEPATH
 * Applies the navigation instructions signified by
 * ".", "..", and "~" symbols. "." means the current
 * directory, ".." means the previous directory,
 * and "~" means the root directory.
 */
std::string getTruePath(std::string path)
{
    char cCurrentPath[FILENAME_MAX];
    GetCurrentDir(cCurrentPath, FILENAME_MAX);

    std::string sDir(cCurrentPath); //The default directory
    //normalize current directory
    sDir = normalizePath(sDir);

    int slashCount = initialSlashCount(sDir);

    for (int i = 0; i < path.length(); i++)
    {
        if (i == 0 && path[0] != separator)
        {
            path = separator + path;
            slashCount--;
        }

        if (path[i] == '.' || path[i] == '~')
        {
            //Here is when we find ../ (parent operator) 
            if (path[i + 1] == '.')
            {
                i += 2;

                int tSlash = 0;
                std::string tDir = "";
                int dirIterator = 0;

                while (tSlash < slashCount)
                {
                    if (sDir[dirIterator] == separator)
                        tSlash++;
                    tDir += sDir[dirIterator++];
                }
                sDir = tDir;

                //decrement directories
                slashCount--;
            }
            else if (path[i + 1] == separator || path[i] == '~') //The path begins with the current directory
            {
                i++;
            }
            continue; //Next for iteration
        }
        if (path[i] == separator)
            slashCount++;

        sDir += path[i];
    }
    return sDir;
}

/**
 * NORMALIZEPATH
 * Canonizes the file paths by converting
 * all letters to lowercase and converting
 * slash symbols to a unified format, since slash
 * symbols in a file path are different depending
 * on the operating system.
 */
std::string normalizePath(std::string path)
{
    for (int i = 0; i < path.length(); i++)
    {
        if (path[i] == '/' || path[i] == '\\')
            path[i] = separator;
    }

    //Transforming to lowercase
    std::transform(path.begin(), path.end(), path.begin(),
                   [](unsigned char c)
                   { return std::tolower(c); });

    return path;
}

/**
 * INITIALSLASHCOUNT
 * Returns the number of slash symbols used in
 * the file path.
 */
int initialSlashCount(std::string path)
{
    int count = 0;
    for (int i = 0; i < path.length(); i++)
    {
        if (path[i] == separator)
            count++;
    }

    return count;
}
