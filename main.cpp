#include<iostream>
#include<fstream>
#include<iomanip>
#include<string>
#include<sstream>
#include<cctype>
#include<filesystem>

#include<algorithm>

#include<vector>
#include<map>

#include<ctime>
#include<cstdlib>
#include<chrono>

#include<raylib.h>
using namespace std;
namespace fs = std::filesystem;

#include"struct.hpp"
#include"globals.hpp"
#include"methods.hpp"
#include"classes.hpp"
#include"func.hpp"


int main() {
    srand(static_cast<unsigned int>(time(0)));
    SetTargetFPS(60);
    SetExitKey(KEY_F1);
    int selectMenuOption = 1;
    do {
        mainMenu(selectMenuOption);
        switch (selectMenuOption)
        {
        case 1:
            TimeTest();
            
            break;
        case 2:
            WordTest();
            
            break;
        case 3: 
            Zen();
            
            break;
        case 4:
            MiniTest();
            
            break;
        case 5:
            inputCppTest();
            
            break;
        case 6: 
            ViewSavedResults();
            
            break;
        default:
            break;
        }
    }while(selectMenuOption != 7);

    return 0;
}