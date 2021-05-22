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

//Function declarations
std::string getTruePath(std::string path);
std::string normalizePath(std::string path);
int initialSlashCount(std::string path);

/*******************************************
* main() will prompt the user for two different
* file paths. Afterwhich, it will then normalize
* both paths and validate whether they are
* homographs or not.
********************************************/
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

/*******************************************
* getTruePath() will be passed a file path
* and return a path that does not contain
* relative path symbols such as '..'
* It does this by utilizing the current path
* to fill in the relative path with the proper
* file names and locations
********************************************/
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

        if (path[i] == '.')
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
            else if (path[i + 1] == separator) //The path begin with the current directory
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

/*******************************************
* normalizePath() will take a path and replace
* any back or forward slash with a normal 
* seperator, '\\'
* This function will be utilized to ensure that
* all paths being worked on are in the same 
* format, which includes transforming the path 
* to all lowercase letters
********************************************/
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

/*******************************************
* initialSlashCount will simply return the
* initial number of slashes a given path
* contains
********************************************/
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
