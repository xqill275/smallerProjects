#include <iostream>
#include <string>
#include <vector>
#include <ctime>
using namespace std;

vector<char> getChrArray(string alphaList) {
    vector<char> charArray;
    int length = alphaList.length();
    for (int i = 1; i < length; i++) {
        charArray.push_back(alphaList.at(i));
    }
    return charArray;
}


int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cout << "usage: " << argv[0] << " <settings> <len of password>" << std::endl;
    }
    int passwordLen = 0;
    string alphaList;
    string lower = "abcdefghijklmonpqrstuvwxyz";
    string upper = "ABCDEFGHIJKLMONPRSTUVWXYZ";
    string num = "01234567890";
    string symbol = "!£$%^&*()_-=+[{]};:'@#~,<.>?|";
    string passWord;
    for (int x = 1; x < argc; x++) {
        string arg = argv[x];

        if (arg == "-a") {
            alphaList += lower;
        } else if (arg == "-A") {
            alphaList += upper;
        } else if (arg == "-s") {
            alphaList += symbol;
        } else if (arg == "-n") {
            alphaList += num;
        } else {
            passwordLen = stoi(arg);
        }
    }
    srand(time(NULL));
    vector<char>charArray = getChrArray(alphaList);
    for (int c = 0; c < passwordLen; c++) {
        int randIndex = rand() % charArray.size();
        passWord += charArray[randIndex];
    }
    std::cout << passWord << std::endl;
    return 0;
}

