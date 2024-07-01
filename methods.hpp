vector<string> OpenRandomText(const string& filename) {//                                             OPEN RAND TEXT

    string text;
    ifstream file(filename);
  // ----- просили дописать
    if (!file.is_open()) {
        cout << "Файл не открылся ошибка";
    }
  // ----- 
    int randText = (rand()%5)*10;    //  <- 5 - количество тестов в файле
    string line;
    for(int i = 0; i < randText; i++) {
        getline(file, line);
    }

    int lineNumber = 0;
    while(std::getline(file, line) && lineNumber < 7) {
        if(line == "") break;
        text += line + "\n";
        lineNumber++;
    }

    file.close();

    vector<string> lines;
    stringstream ss(text);
    while (getline(ss, line, '\n'))
    {
        lines.push_back(line);
    }
    return lines;
}

string cvToStrFVecStr(const vector<string>& orgText) {
    string newText;

    for(int i = 0; i < orgText.size();i++) {
        newText += orgText[i];
    }
    return newText;
}

int levenshteinDistance(const string& s1, const string& s2) {
    int m = min(s1.size(), s2.size());
    
    vector<vector<int>> dp(m + 1, vector<int>(m + 1, 0));

    for (int i = 0; i <= m; i++)
        dp[i][0] = i;
    for (int j = 0; j <= m; j++)
        dp[0][j] = j;
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= m; j++) {
            int cost = (s1[i - 1] == s2[j - 1]) ? 0 : 1;
            dp[i][j] = min({dp[i - 1][j] + 1, dp[i][j - 1] + 1, dp[i - 1][j - 1] + cost});
        }
    }

    return dp[m][m];
}

int symbolPerMinute(const string& text, const int time) {
    return text.size()*60/time;
}

int wordsPrMinute(const string& text, const int time) {
    int count = 1;
    for(int i = 0;i < text.size();i++) {
        if(text[i] == ' ') count ++;
    }
    if(text[text.size()] != ' ') count ++;
    return count*60/time;
}

void WriteTime() {
    fstream file(filename, ios::in | ios::out | ios::binary);

    if (!file.is_open()) {
        ofstream newFile(filename, ios::binary); // Если файл не существует, создаем его
        if (!newFile.is_open()) {
            cerr << "Unable to open file for writing" << endl;
            return;
        }
        time_t currentTime = time(nullptr);
        tm* currentTimeInfo = localtime(&currentTime);
        newFile << put_time(currentTimeInfo, "%Y %m %d %H %M %S") << endl;
        newFile.close();
        return;
    }

    // Записываем время в начало файла
    file.seekp(0, ios::beg);
    time_t currentTime = time(nullptr);
    tm* currentTimeInfo = localtime(&currentTime);
    file << put_time(currentTimeInfo, "%Y %m %d %H %M %S") << endl;
    file.close();
}

bool CanSave() {
    ifstream file(filename, ios::binary);
    if (!file.is_open()) {
        return true; // Файл не существует, значит можно записывать
    }

    // Чтение времени последней записи
    string line;
    getline(file, line);
    tm fileTime = {};
    istringstream iss(line);
    iss >> get_time(&fileTime, "%Y %m %d %H %M %S");
    time_t fileTimestamp = mktime(&fileTime);
    time_t currentTime = time(nullptr);

    file.close();

    return (difftime(currentTime, fileTimestamp) > 20);
}

void savedResulthBin(const DataTest& data) {
    if (CanSave()) {
        // Обновляем время последней записи в начале файла
        WriteTime();

        ofstream file(filename, ios::binary | ios::app); // Открываем в бинарном режиме для добавления

        if (!file.is_open()) {
            cerr << "Unable to open file for writing" << endl;
            return;
        }

        // Получаем текущее время
        time_t currentTime = time(nullptr);
        tm* currentTimeInfo = localtime(&currentTime);
        ostringstream oss;
        oss << put_time(currentTimeInfo, "%Y %m %d %H %M %S");
        string currentTimeStr = oss.str();

        // Записываем длину и данные строки testName
        size_t size = data.testName.size();
        file.write(reinterpret_cast<const char*>(&size), sizeof(size));
        file.write(data.testName.c_str(), size);

        // Записываем целочисленные значения
        file.write(reinterpret_cast<const char*>(&data.time), sizeof(data.time));
        file.write(reinterpret_cast<const char*>(&data.mistake), sizeof(data.mistake));
        file.write(reinterpret_cast<const char*>(&data.SPM), sizeof(data.SPM));
        file.write(reinterpret_cast<const char*>(&data.WPM), sizeof(data.WPM));

        // Записываем длину и данные строки date
        size = data.date.size();
        file.write(reinterpret_cast<const char*>(&size), sizeof(size));
        file.write(data.date.c_str(), size);

        // Записываем текущее время
        size = currentTimeStr.size();
        file.write(reinterpret_cast<const char*>(&size), sizeof(size));
        file.write(currentTimeStr.c_str(), size);

        file.close();
    } else {
        cout << "Data not saved. Please wait for 20 seconds since the last save." << endl;
    }
}

void saveResulth(const string& testType, int& TestTime, int Mistakes, int& SPM, int& WPM){
    DataTest data;
    data.mistake = Mistakes;
    data.SPM = SPM;
    data.WPM = WPM;
    data.testName = testType;
    data.time = TestTime;
    savedResulthBin(data);
    return;
}

bool isDataTestEmpty(const DataTest& data) {
    return data.testName.empty() &&
           data.time == 0 &&
           data.mistake == 0 &&
           data.SPM == 0 &&
           data.WPM == 0 &&
           data.date.empty() &&
           data.recordTime.empty();
}

vector<DataTest> loadResultsFromBin(const string& filename) {
    vector<DataTest> results;
    ifstream file(filename, ios::binary);

    if (!file.is_open()) {
        cerr << "Unable to open file for reading" << endl;
        return results;
    }
    
    // Пропускаем время (первая строка)
    string line;
    getline(file, line);

    while (file.peek() != EOF) {
        DataTest data;
        size_t size;

        // Читаем длину и данные строки testName
        file.read(reinterpret_cast<char*>(&size), sizeof(size));
        if (file.eof()) break;
        data.testName.resize(size);
        file.read(&data.testName[0], size);

        // Читаем целочисленные значения
        file.read(reinterpret_cast<char*>(&data.time), sizeof(data.time));
        file.read(reinterpret_cast<char*>(&data.mistake), sizeof(data.mistake));
        file.read(reinterpret_cast<char*>(&data.SPM), sizeof(data.SPM));
        file.read(reinterpret_cast<char*>(&data.WPM), sizeof(data.WPM));

        // Читаем длину и данные строки date
        file.read(reinterpret_cast<char*>(&size), sizeof(size));
        data.date.resize(size);
        file.read(&data.date[0], size);

        // Читаем длину и данные строки recordTime
        file.read(reinterpret_cast<char*>(&size), sizeof(size));
        data.recordTime.resize(size);
        file.read(&data.recordTime[0], size);

        results.push_back(data);
    }

    file.close();
    return results;
}

vector<DataTest> getBestResultsByTestType() {
    vector<DataTest> results = loadResultsFromBin(filename);
    map<string, DataTest> bestResults;
    vector<string> testTypes = {"Test Time", "Test Text", "Test Zen", "Test Mini", "Test Cpp"};

    for (const auto& testType : testTypes) {
        bestResults[testType] = DataTest();
    }

    // Поиск лучших результатов
    for (const auto& result : results) {
        if (find(testTypes.begin(), testTypes.end(), result.testName) != testTypes.end()) {
            if (bestResults[result.testName].SPM < result.SPM || bestResults[result.testName].testName.empty()) {
                bestResults[result.testName] = result;
            }
        }
    }

    vector<DataTest> topResults;
    for (const auto& testType : testTypes) {
        topResults.push_back(bestResults[testType]);
    }

    return topResults;
}