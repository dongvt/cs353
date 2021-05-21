#include <iostream>
#include <string>


int main(int argc, char * argv[]) 
{
    std::string path1;
    std::string path2;

    std::cout << "Insert first path" << std::endl;
    std::cin >> path1;

    std::cout << "Insert second path" << std::endl;
    std::cin >> path2;
    
    getTruePath(path1) == getTruePath(path2)
    //Call get true dire with Path1 and Path2

    return 0;
}

std::string getTruePath(std::string path) 
{
    std::string sDir = ""; //The current directory

    for (int i = 0; i < path.length() ;i++)
    {
        if(path[i] == '.')
        {
            //Here is when we find ../
            if (path[i + 1] == '.')
            {

            }
            else //The path begin with the current directory
                i++; //This is dummy to avoid errors
        }
    }
    return sDir;
}