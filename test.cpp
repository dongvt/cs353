#include <iostream>

using namespace std;

float ** testFunction() {
    float ** res = new float*[3];
    for(int i = 0; i<3;i++) {
        res[i] = new float[2];
        for(int k = 0; k<2;k++) 
            res[i][k] = 5.0F;
    }
    return res;
}

int main() {
    auto number = testFunction();

    for(int i = 0; i<3;i++) 
        cout << number[i][0] << endl;
}