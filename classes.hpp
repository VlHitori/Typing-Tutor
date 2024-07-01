class TextBase {
public:
    TextBase(vector<string>& inputT)
        : inputT(inputT) {}

    virtual ~TextBase() = default;

    virtual void Draw() {
        // Draw input text
        for (size_t i = 0; i < inputT.size(); i++) {
            DrawText(inputT[i].c_str(), screenWindth / 6, screenHeight / 2 + 30 * i, 30, MAROON);
        }
        // Draw cursor
        float textWidth = MeasureText(inputT[cursor.Y].c_str(), 30);
        DrawRectangle(screenWindth / 6 + textWidth, screenHeight / 2 + 30 * cursor.Y, 2, 30, BLACK);
    }

    virtual void Update() = 0;

    virtual bool ShouldTestContinue() const = 0;

    virtual float getFinalTime() const = 0;

protected:
    
    vector<string>& inputT;
    Cursor cursor;

    char ShiftKeyToSpecialChar(int key) {
        switch(key) {
            case KEY_SPACE: return ' ';
            case KEY_MINUS: return '_';
            case KEY_EQUAL: return '+';
            case KEY_LEFT_BRACKET: return '{';
            case KEY_RIGHT_BRACKET: return '}';
            case KEY_SEMICOLON: return ':';
            case KEY_APOSTROPHE: return '"';
            case KEY_COMMA: return '<';
            case KEY_PERIOD: return '>';
            case KEY_SLASH: return '?';
            case KEY_BACKSLASH: return '|';
            case KEY_GRAVE: return '~';
            case 57: return '(';
            case 48: return ')';
            case 55: return '&';
            case 53: return '%';
            default: return static_cast<char>(key);
        }
    }

    char KeyToSpecialChar(int key) {
        switch (key) {
            case KEY_SPACE: return ' ';
            case KEY_MINUS: return '-';
            case KEY_EQUAL: return '=';
            case KEY_LEFT_BRACKET: return '[';
            case KEY_RIGHT_BRACKET: return ']';
            case KEY_SEMICOLON: return ';';
            case KEY_APOSTROPHE: return '\'';
            case KEY_COMMA: return ',';
            case KEY_PERIOD: return '.';
            case KEY_SLASH: return '/';
            case KEY_BACKSLASH: return '\\';
            case KEY_GRAVE: return '`';
            case KEY_BACK: return '\b';
            
            default: return static_cast<char>(key);
        }
    }
};

class InputTextTime : public TextBase {
public:
    InputTextTime(vector<string>& inputT, const vector<string>& lines)
        : TextBase(inputT), lines(lines) {}
    void DrawTime() {
        DrawText(TextFormat("Time: %.f seconds", testTime - Time), screenWindth/3, screenHeight/3, 35, BLACK);
        for (size_t i = 0; i < lines.size(); i++) {
            DrawText(lines[i].c_str(), screenWindth / 6, screenHeight / 2 + 30 * i, 30, GRAY);
        }
    }
    void Update() override {
        if(isTestGo) Time = difftime(time(nullptr), startTime);

        int key = GetKeyPressed();
        switch(key)
        {
        case KEY_BACKSPACE:
            if (!inputT[cursor.Y].empty()) {
                inputT[cursor.Y].pop_back();
                cursor.X--;
            } else {
                if (cursor.Y != 0) {
                    inputT.erase(inputT.begin() + cursor.Y);
                    cursor.Y--;
                }
                cursor.X = inputT[cursor.Y].size();
            }
            break;
        case KEY_SPACE:
            if (lines[cursor.Y].size() <= inputT[cursor.Y].size()) {
                inputT.push_back({""}); 
                cursor.Y++;
                cursor.X = 0;
            } else {
                inputT[cursor.Y].push_back(' ');
                cursor.X++;
            }
            break;
        default:
            if (key > 0 && key < 256) {
                bool shiftPressed = IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT);
                
                if (!isTestGo) {
                    isTestGo = true;
                    startTime = time(nullptr);
                }

                if (shiftPressed) {
                    inputT[cursor.Y].insert(inputT[cursor.Y].begin() + cursor.X, static_cast<char>(toupper(ShiftKeyToSpecialChar(key))));
                    cursor.X++;
                } else {
                    inputT[cursor.Y].insert(inputT[cursor.Y].begin() + cursor.X, static_cast<char>(tolower(KeyToSpecialChar(key))));
                    cursor.X++;
                }
            }
            break;
        }
    }
    bool ShouldTestContinue() const override {
        return inputT.size() <= lines.size() && (Time < testTime);
    }
    float getFinalTime() const override {
        
        if (isTestGo) {
            return difftime(time(nullptr), startTime);
        } else {
            return 0;
        }
    }
private:
    const int testTime = 50;
    bool isTestGo = false;
    time_t startTime = 0;
    float Time = 0;
    const vector<string>& lines;
};

class InputTextText : public TextBase {
public:
    InputTextText(vector<string>& inputT, const vector<string>& lines)
        : TextBase(inputT), lines(lines) {}

    void DrawTime() {
        DrawText(TextFormat("Time: %.f seconds", Time), screenWindth/3, screenHeight/3, 35, BLACK);
        for (size_t i = 0; i < lines.size(); i++) {
            DrawText(lines[i].c_str(), screenWindth / 6, screenHeight / 2 + 30 * i, 30, GRAY);
        }
    }

    void Update() override {
        if(isTestStart) Time = difftime(time(nullptr), startTime);

        int key = GetKeyPressed();
        switch(key)
        {
        case KEY_BACKSPACE:
            if (!inputT[cursor.Y].empty()) {
                inputT[cursor.Y].pop_back();
                cursor.X--;
            } else {
                if (cursor.Y != 0) {
                    inputT.erase(inputT.begin() + cursor.Y);
                    cursor.Y--;
                }
                cursor.X = inputT[cursor.Y].size();
            }
            break;
        case KEY_SPACE:
            if (lines[cursor.Y].size() <= inputT[cursor.Y].size()) {
                inputT.push_back({""}); 
                cursor.Y++;
                cursor.X = 0;
            } else {
                inputT[cursor.Y].push_back(' ');
                cursor.X++;
            }
            break;
        default:
            if (key > 0 && key < 256) {
                bool shiftPressed = IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT);
                
                if (!isTestStart) {
                    isTestStart = true;
                    startTime = time(nullptr);
                }

                if (shiftPressed) {
                    inputT[cursor.Y].insert(inputT[cursor.Y].begin() + cursor.X, static_cast<char>(toupper(ShiftKeyToSpecialChar(key))));
                    cursor.X++;
                } else {
                    inputT[cursor.Y].insert(inputT[cursor.Y].begin() + cursor.X, static_cast<char>(tolower(KeyToSpecialChar(key))));
                    cursor.X++;
                }
            }
            break;
        }        
    }
    bool ShouldTestContinue() const override {
        return (inputT.size() <= lines.size());
    }
    float getFinalTime() const override {
        if(isTestStart) {
            return difftime(time(nullptr), startTime);
        } else {
            return 0.0f;
        }
    }

private:
    bool isTestStart = false;
    bool isTestEnd = false;
    time_t startTime = 0;
    float Time = 0;
    const vector<string> lines;
};

class ZenTest : public TextBase{
public:
    ZenTest(vector<string>& inputT) 
        : TextBase(inputT) {}
    void DrawTime() {
        DrawText(TextFormat("Time: %.f seconds", Time), screenWindth/3, screenHeight/3, 35, BLACK);
        DrawText("Tap F1 to End test", screenWindth/3+5, screenHeight/3+35, 20, GRAY);
    }
    

    void Update() override {
        if(isTestStart) Time = difftime(time(nullptr), startTime);

        int key = GetKeyPressed();
        switch(key)
        {
        case KEY_BACKSPACE :
            if (!inputT[cursor.Y].empty()) {
                inputT[cursor.Y].pop_back();
                cursor.X--;
            } else {
                if (cursor.Y != 0) {
                    inputT.erase(inputT.begin() + cursor.Y);
                    cursor.Y--;
                }
                cursor.X = inputT[cursor.Y].size();
            }
            break;
        case KEY_SPACE:
            if(MeasureText(inputT[cursor.Y].c_str(), 30) < (screenWindth-(screenWindth/3))) {
                inputT[cursor.Y].push_back(' ');
                cursor.X++;
            } else {
                inputT.push_back({""}); 
                cursor.Y++;
                cursor.X = 0;
            }
            break;
        case KEY_ENTER: 
            inputT.push_back({""}); 
            cursor.Y++;
            cursor.X = 0;
            break;
        case KEY_F1:
            sldTestCont = false;
            break;
        default:
            if (key > 0 && key < 256) {
                bool shiftPressed = IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT);
                
                if (!isTestStart) {
                    isTestStart = true;
                    startTime = time(nullptr);
                }

                if (shiftPressed) {
                    inputT[cursor.Y].insert(inputT[cursor.Y].begin() + cursor.X, static_cast<char>(toupper(ShiftKeyToSpecialChar(key))));
                    cursor.X++;
                } else {
                    inputT[cursor.Y].insert(inputT[cursor.Y].begin() + cursor.X, static_cast<char>(tolower(KeyToSpecialChar(key))));
                    cursor.X++;
                }
            }
            break;
        }
    } 

    bool ShouldTestContinue() const override {
        return sldTestCont;
    }
    float getFinalTime() const override {
        if(isTestStart) {
            return difftime(time(nullptr), startTime);
        } else {
            return 0.0f;
        }
    }
private:
    float Time = 0;
    time_t startTime = 0;
    bool sldTestCont = true;
    bool isTestStart = false;

};

class ViewResulth {
public:
    ViewResulth(const string& fileResulth, int& selectOpt):fileResulth(fileResulth), selectOpt(selectOpt) {
        bestResults = getBestResultsByTestType();
    }
    void Update() {
        int key = GetKeyPressed();
        switch (key)
        {
        case KEY_UP:
            selectOpt --;
            break;
        case KEY_DOWN:
            selectOpt ++;
            break;
        case KEY_ENTER:
            if(selectOpt = 5) shouldContinue = false;
        default:
            break;
        }
        if (selectOpt < 0) selectOpt = 0;
        if (selectOpt > 5) selectOpt = 5;

    }
    void Draw() {
        DrawText("BestResults", 500, 150, 40, BLACK);
        DrawText("> Time Test", 250, 250, 35, (selectOpt == 0) ? MAROON : BLACK);
        DrawText("> Word Test", 250, 300, 35, (selectOpt == 1) ? MAROON : BLACK);
        DrawText("> Zen Test ", 250, 350, 35, (selectOpt == 2) ? MAROON : BLACK);
        DrawText("> Mini Test", 250, 400, 35, (selectOpt == 3) ? MAROON : BLACK);
        DrawText("> Cpp Test ", 250, 450, 35, (selectOpt == 4) ? MAROON : BLACK);
        DrawText("> Exit ", 250, 500, 35, (selectOpt == 5) ? MAROON : BLACK);

        if (selectOpt < 5 ) {

            if(isDataTestEmpty(bestResults[selectOpt])) {
                DrawText("No Test Completed", 650, 350, 35, BLACK);
            } else {
                DrawText(("Test Type:   >" + bestResults[selectOpt].testName).c_str(), 650, 250, 35, BLACK);
                DrawText(("Time:        >" + to_string(bestResults[selectOpt].time)).c_str(), 650, 300, 35, BLACK);
                DrawText(("Mistakes:    >" + to_string(bestResults[selectOpt].mistake)).c_str(), 650, 350, 35, BLACK);
                DrawText(("SPM:         >" + to_string(bestResults[selectOpt].SPM)).c_str(), 650, 400, 35, BLACK);
                DrawText(("WPM:         >" + to_string(bestResults[selectOpt].WPM)).c_str(), 650, 450, 35, BLACK);
            } 
        }
    }
    bool shouldContinueWindow() {
        return shouldContinue;
    }
private:
    const string fileResulth;
    ifstream file;
    vector<string> results;
    vector<DataTest> bestResults;
    int& selectOpt;
    bool shouldContinue = true;
};

class InputCppCode : public TextBase {
public:
    InputCppCode(vector<string>& inputT, const vector<string>& lines)
        : TextBase(inputT), lines(lines) {}

    void Draw() override {

        // Draw time
        DrawText(TextFormat("Time: %.f seconds", Time), screenWindth / 3, screenHeight / 3, 35, BLACK);
        
        // Draw reference code
        for (size_t i = 0; i < lines.size(); i++) {
            DrawText(lines[i].c_str(), screenWindth / 6, screenHeight / 2 + 30 * i, 30, GRAY);
        }

        TextBase::Draw();
    }

    void Update() override {
        if (isTestGo) Time = difftime(time(nullptr), startTime);

        int key = GetKeyPressed();
        switch(key) {
        case KEY_BACKSPACE:
            if (!inputT[cursor.Y].empty()) {
                inputT[cursor.Y].pop_back();
                cursor.X--;
            } else {
                if (cursor.Y != 0) {
                    inputT.erase(inputT.begin() + cursor.Y);
                    cursor.Y--;
                }
                cursor.X = inputT[cursor.Y].size();
            }
            break;
        case KEY_ENTER:
        case KEY_KP_ENTER:
            if (lines[cursor.Y].size() <= inputT[cursor.Y].size()) {
                inputT.push_back({""}); 
                cursor.Y++;
                cursor.X = 0;
            }
            break;
        case KEY_TAB:
            inputT[cursor.Y].append("    ");
            cursor.X += 4;
            break;
        default:
            if (key > 0 && key < 256) {
                bool shiftPressed = IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT);
                
                if (!isTestGo) {
                    isTestGo = true;
                    startTime = time(nullptr);
                }

                if (shiftPressed) {
                    inputT[cursor.Y].insert(inputT[cursor.Y].begin() + cursor.X, static_cast<char>(toupper(ShiftKeyToSpecialChar(key))));
                    cursor.X++;
                } else {
                    inputT[cursor.Y].insert(inputT[cursor.Y].begin() + cursor.X, static_cast<char>(tolower(KeyToSpecialChar(key))));
                    cursor.X++;
                }
            }
            break;
        }
    }

    bool ShouldTestContinue() const override {
        // Test ends when all lines are input or time is up
        return inputT.size() <= lines.size();
    }

    float getFinalTime() const override {
        if (isTestGo) {
            return difftime(time(nullptr), startTime);
        } else {
            return 0.0f;
        }
    }

private:
    bool isTestGo = false;
    time_t startTime = 0;
    float Time = 0;
    const vector<string>& lines;
};
