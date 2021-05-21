#include <iostream>
#include <string>

int main() 
{
    std::string path1;
    std::string path2;

    std::cout << "Insert first path" << std::endl;
    std::cin >> path1;

    std::cout << "Insert second path" << std::endl;
    std::cin >> path2;

    std::cout << "Now there is the comparison";

    return 0;
}

std::string getTruePath(std::string path) 
{
    std::string sDir = ""; //Simple directory without aditions

    int numSlashes = 0;

    for (int i = 0; i < path.length() ;i++)
    {
        if(path[i] == '.')
        {
            if (path[i + 1] == '.')
            {
                
            }
            else
                i++;
        }
    }
}