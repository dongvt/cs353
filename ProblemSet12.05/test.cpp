#include <iostream>
#include <string>

using namespace std;

int main() {
    string input = "ESFQQWSJKSYGAUGFLJSULWVSFAFLAESUQOALZSEJOADDASEDWYJSFVZWOSKGXSFSFUAWFLZMYMWFGLXSEADQSFVZSVGFUWTWWFOWSDLZQTMLSKWJAWKGXEAKXGJLMFWKZSVJWVMUWVZAELGOSFLLGSNGAVLZWEGJLAXAUSLAGFUGFKWIMWFLMHGFZAKVAKSKLWJKZWDWXLFWOGJDWSFKLZWUALQGXZAKXGJWXSLZWJKSFVLGGCMHZAKJWKAVWFUWSLKMDDANSFKAKDSFVFWSJUZSJDWKLGFKGMLZUSJGDAFSLZAKAKDSFVAKSNWJQKAFYMDSJGFWALUGFKAKLKGXDALLDWWDKWLZSFLZWKWSKSFVSFVAKSTGMLLZJWWEADWKDGFYALKTJWSVLZSLFGHGAFLWPUWWVKSIMSJLWJGXSEADWALAKKWHSJSLWVXJGELZWESAFDSFVTQSKUSJUWDQHWJUWHLATDWUJWWCGGRAFYALKOSQLZJGMYZSOADVWJFWKKGXJWWVKSFVKDAEWSXSNGJALWJWKGJLGXLZWESJKZZWFLZWNWYWLSLAGFSKEAYZLTWKMHHGKWVAKKUSFLGJSLDWSKLVOSJXAKZFGLJWWKGXSFQESYFALMVWSJWLGTWKWWFFWSJLZWOWKLWJFWPLJWEALQOZWJWXGJLEGMDLJAWKLSFVKSFVOZWJWSJWKGEWEAKWJSTDWXJSEWTMADVAFYKLWFSFLWVVMJAFYKMEEWJTQLZWXMYALANWKXJGEUZSJDWKLGFVMKLSFVXWNWJESQTWXGMFVAFVWWVLZWTJAKLDQHSDEWLLGTMLLZWOZGDWAKDSFVOALZLZWWPUWHLAGFGXLZAKOWKLWJFHGAFLSFVSDAFWGXZSJVOZALWTWSUZGFLZWKWSUGSKLAKUGNWJWVOALZSVWFKWMFVWJYJGOLZGXLZWKOWWLEQJLDWKGEMUZHJARWVTQLZWZGJLAUMDLMJAKLKGXWFYDSFVLZWKZJMTZWJWGXLWFSLLSAFKLZWZWAYZLGXXAXLWWFGJLOWFLQXWWLSFVXGJEKSFSDEGKLAEHWFWLJSTDWUGHHAUWTMJLZWFAFYLZWSAJOALZALKXJSYJSFUW";
    //try 10 keys, both positive and negative
    //charts  65-90 
    for (int k = 1; k <= 10;k++) {
        for(int i = 0; i < input.length(); i++) {
            input[i]++;
            if(input[i] > 90)
                input[i] = 65;
        }
        cout << k << "->" << input << endl << endl;       
    }
    return 0;
}