void mainMenu(int& selectedOption) {//                                          START MENU FUNC                                                                        
    InitWindow(screenWindth,screenHeight, "MainMenu");
    SetExitKey(KEY_F1);
    
    while(!WindowShouldClose()) {
    
        if(IsKeyPressed(KEY_UP)) {
            selectedOption--;
            if(selectedOption < 1) selectedOption = 1;
        } else if (IsKeyPressed(KEY_DOWN)) {
            selectedOption++;
            if (selectedOption > 7) selectedOption = 7;
        } else if (IsKeyPressed(KEY_ENTER)) {
            break;
        }
        
        BeginDrawing();
        ClearBackground(DARKGRAY);
        DrawText("Typing Tutor", 430, 150, 50, BLACK);
        DrawText("> Time", 500, 250, 30,(selectedOption == 1) ? MAROON : BLACK);
        DrawText("> Words", 500, 300, 30, (selectedOption == 2) ? MAROON : BLACK);
        DrawText("> Zen", 500, 350, 30, (selectedOption == 3) ? MAROON : BLACK);
        DrawText("> Mini", 500, 400, 30, (selectedOption == 4) ? MAROON : BLACK);
        DrawText("> Cpp test", 500, 450, 30, (selectedOption == 5) ? MAROON : BLACK);
        DrawText("> View best resuts", 500, 500, 30, (selectedOption == 6) ? MAROON : BLACK);
        DrawText("> Exit", 500, 550, 30, (selectedOption == 7) ? MAROON : BLACK);
        DrawText("> Typing Tutor beta 2\n  Bur_VV", 1020, 750, 12, DARKBROWN);
        EndDrawing();
    }
    CloseWindow();
    
}

bool ResultInit(const string& testType, int& outTime, int& outMistakesCt, int& outWordsPrMin, int& outSymbPrSec) { //RESULTH MENU
    int selectedOption = 1;

    InitWindow(screenWindth, screenHeight, "Result");
    while (!WindowShouldClose())
    {
        
        if(IsKeyPressed(KEY_UP)) {
            selectedOption--;
            if(selectedOption < 1) selectedOption = 1;
        } else if (IsKeyPressed(KEY_DOWN)) {
            selectedOption++;
            if (selectedOption > 3) selectedOption = 3;
        } else if (IsKeyPressed(KEY_ENTER)) {
            switch (selectedOption)
            {
            case 1:
                CloseWindow();
                return true;
            case 2:
                saveResulth(testType, outTime, outMistakesCt, outSymbPrSec, outWordsPrMin);
                break;
            case 3:
                CloseWindow();
                return false;
            default:
                break;
            }
        }

        BeginDrawing();
        ClearBackground(DARKGRAY);
        //Draw menu
            DrawText("> Repeat", 250, 250, 35,(selectedOption == 1) ? MAROON : BLACK);
            DrawText("> Save Resulth", 250, 300, 35, (selectedOption == 2) ? MAROON : BLACK);
            DrawText("> Exit in menu", 250, 350, 35, (selectedOption == 3) ? MAROON : BLACK);  

        //Draw Result
            DrawText(("Test type:   >"+ testType).c_str(), 650, 250, 35 , BLACK);
            DrawText(("Time:         >"+ to_string(outTime)).c_str(), 650, 300, 35, BLACK);
            DrawText(("Mistakes:    >"+ to_string(outMistakesCt)).c_str(), 650, 350, 35, BLACK);
            DrawText(("SPM:          >"+ to_string(outSymbPrSec)).c_str(), 650, 400, 35, BLACK);
            DrawText(("WPM:          >"+ to_string(outWordsPrMin)).c_str(), 650, 450, 35, BLACK);
        EndDrawing();
    }
    CloseWindow();
    return false;
}

void TimeTest() {//                                                             START TIME TEST FUNC
    
    bool repeatTest = false;
    do{
        vector<string> Text = OpenRandomText("texts.txt");
        vector<string> inputText = {""};

        InputTextTime input(inputText, Text);
        
        InitWindow(screenWindth, screenHeight, "Typing text");
        while(!WindowShouldClose() && input.ShouldTestContinue()) {
            input.Update();

            BeginDrawing();
            ClearBackground(DARKGRAY);
            input.DrawTime();
            input.Draw();
            EndDrawing();
        }
        CloseWindow();
        
        int outTime = static_cast<int>(input.getFinalTime());
        
        string strInputText = cvToStrFVecStr(inputText);
        string strText = cvToStrFVecStr(Text);

        int outMistakesCt = levenshteinDistance(strText, strInputText);
        int outSymbPrSec = symbolPerMinute(strInputText, outTime);
        int outWordsPrMin = wordsPrMinute(strInputText, outTime);
        
        repeatTest = ResultInit("Test Time", outTime, outMistakesCt, outWordsPrMin, outSymbPrSec);

    }while(repeatTest);
} 

void WordTest() {
    bool repeatTest = false;
    do{
        vector<string> Text = OpenRandomText("texts.txt");
        vector<string> inputText = {""};

        InputTextText input(inputText, Text);
        
        InitWindow(screenWindth, screenHeight, "Typing text");
        while(!WindowShouldClose() && input.ShouldTestContinue()) {
            input.Update();

            BeginDrawing();
            ClearBackground(DARKGRAY);
            input.DrawTime();
            input.Draw();
            EndDrawing();
        }
        CloseWindow();
        
        int outTime = static_cast<int>(input.getFinalTime());
        
        string strInputText = cvToStrFVecStr(inputText);
        string strText = cvToStrFVecStr(Text);

        int outMistakesCt = levenshteinDistance(strText, strInputText);
        int outSymbPrSec = symbolPerMinute(strInputText, outTime);
        int outWordsPrMin = wordsPrMinute(strInputText, outTime);
        
        repeatTest = ResultInit("Test Text", outTime, outMistakesCt, outWordsPrMin, outSymbPrSec);

    }while(repeatTest);
}

void Zen() {
    bool repeatTest = false;
    do{
        vector<string> inputText = {""};
        ZenTest input(inputText);
        InitWindow(screenWindth, screenHeight, "Typing text");
        while(!WindowShouldClose() && input.ShouldTestContinue()) {

            input.Update();

            BeginDrawing();
            ClearBackground(DARKGRAY);
            input.DrawTime();
            input.Draw();
            EndDrawing();
        }
        CloseWindow();
        
        int outTime = static_cast<int>(input.getFinalTime());

        string strInputText = cvToStrFVecStr(inputText);
        int outSymbPrSec = symbolPerMinute(strInputText, outTime);
        int outWordsPrMin = wordsPrMinute(strInputText, outTime);
        int mistakes = 0;

        cout << inputText[0]<< "\n\n\n";

        repeatTest = ResultInit("Test Zen", outTime, mistakes, outWordsPrMin, outSymbPrSec);
    }while(repeatTest);
}

void MiniTest() {
    bool repeatTest = false;
    do{
        vector<string> Text = OpenRandomText("textsMini.txt");
        vector<string> inputText = {""};

        InputTextText input(inputText, Text);
        
        InitWindow(screenWindth, screenHeight, "Typing text");
        while(!WindowShouldClose() && input.ShouldTestContinue()) {
            input.Update();

            BeginDrawing();
            ClearBackground(DARKGRAY);
            input.DrawTime();
            input.Draw();
            EndDrawing();
        }
        CloseWindow();
        
        int outTime = static_cast<int>(input.getFinalTime());
        
        string strInputText = cvToStrFVecStr(inputText);
        string strText = cvToStrFVecStr(Text);

        int outMistakesCt = levenshteinDistance(strText, strInputText);
        int outSymbPrSec = symbolPerMinute(strInputText, outTime);
        int outWordsPrMin = wordsPrMinute(strInputText, outTime);
        
        repeatTest = ResultInit("Test Mini", outTime, outMistakesCt, outWordsPrMin, outSymbPrSec);

    }while(repeatTest);
}

void ViewSavedResults() {
    int selectedOption = 0;
    ViewResulth Resulth(fileResulth, selectedOption);
    
    InitWindow(screenWindth, screenHeight, "View resulth");
    while(!WindowShouldClose()&& Resulth.shouldContinueWindow()) {
        Resulth.Update();

        BeginDrawing();
        ClearBackground(DARKGRAY);
        Resulth.Draw();

        EndDrawing();
    }
    CloseWindow();
}

void inputCppTest() {
    bool repeatTest = false;
    do{
        vector<string> Text = OpenRandomText("textsCpp.txt");
        vector<string> inputText = {""};

        InputCppCode input(inputText, Text);
        
        InitWindow(screenWindth, screenHeight, "Typing text");
        while(!WindowShouldClose() && input.ShouldTestContinue()) {
            input.Update();

            BeginDrawing();
            ClearBackground(DARKGRAY);
            input.Draw();
            EndDrawing();
        }
        CloseWindow();
        
        int outTime = static_cast<int>(input.getFinalTime());
        
        string strInputText = cvToStrFVecStr(inputText);
        string strText = cvToStrFVecStr(Text);

        int outMistakesCt = levenshteinDistance(strText, strInputText);
        int outSymbPrSec = symbolPerMinute(strInputText, outTime);
        int outWordsPrMin = wordsPrMinute(strInputText, outTime);
        
        repeatTest = ResultInit("Test Cpp", outTime, outMistakesCt, outWordsPrMin, outSymbPrSec);

    }while(repeatTest);
}
