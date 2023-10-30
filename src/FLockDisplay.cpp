#include "FLockDisplay.hpp"
#include <sstream>
#include <iomanip>
#include <stdlib.h>
#include <random>
#include <ctime>
#include <algorithm>
#include <boost/algorithm/string.hpp>
#include <iterator>
#include <signal.h>

#include <iostream>

#include <unistd.h>

int flock::AddrLength(void)
{
    static int length{-1};
    if (-1 == length) {
        void *ptr{malloc(1)};
        std::ostringstream oss;
        oss  << ptr;
        free(ptr);
        length = oss.str().size();
    }
    return length;
}

flock::FLockDisplay::FLockDisplay(const std::vector<std::string> wordList) : 
    _wordList{wordList}, 
    _psswrdID{std::rand() % (int)wordList.size()},
    _consoleBuff{_dInfo.dumpLinesSize, _dInfo.inputSize}
{
    int dumpSize{(int)(((_dInfo.dumpColsSize * _dInfo.dumpLinesSize * _dInfo.colsNb) - (_wordList[0].length() * _wordList.size())) + _wordList.size())};
    std::vector<int> wordID{};
    for (size_t i{0}; _wordList.size() > i; ++i) {
        int rng{std::rand() % dumpSize};
        while (std::find(wordID.begin(), wordID.end(), rng) != wordID.end())
            rng = std::rand() % dumpSize;
        wordID.push_back(rng);
    }
    std::sort(wordID.begin(), wordID.end());
    int currentWordID{0};
    std::string garbageChar{"!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~"};
    for (int  i{0}; dumpSize > i; ++i) {
        if (i == wordID[currentWordID]) {
            _dumpStr += _wordList[currentWordID];
            ++currentWordID;
        } else
            _dumpStr += garbageChar[std::rand() % garbageChar.size()];
    }
    RefreshAll();
    return;

    std::cout << COLS << std::endl
        << LINES << std::endl;
    std::cout << _dInfo.addrSize << std::endl 
        << _dInfo.colsNb << std::endl 
        << _dInfo.dumpColsSize << std::endl 
        << _dInfo.dumpLinesSize << std::endl 
        << _dInfo.endWithASpace << std::endl 
        << _dInfo.inputSize << std::endl 
        << _dInfo.totalSpaceSize << std::endl
        << dumpSize << std::endl;
    //std::cout << _dumpStr << std::endl;

    for (size_t id{0}; _dumpStr.size() > id; id += _dInfo.dumpColsSize) {
        std::cout << GenDumpLine(id) << " ";
        id += _dInfo.dumpColsSize;
        std::cout << GenDumpLine(id)
            << "   >Entry denied" << std::endl;
    }
}

void flock::FLockDisplay::Input(char c)
{
    if ((char)-1 == c)
        _consoleBuff.RemoveToInput();
    else
        _consoleBuff.AddToInput(c);
    RefreshInput();
}

void flock::FLockDisplay::Output(std::string str)
{
    _consoleBuff.WriteOutput(str);
    RefreshInput();
}

std::string &flock::FLockDisplay::GetInput(void)
{
    return _consoleBuff.GetCurrentInput();
}

int flock::FLockDisplay::SearchMatch(std::string str)
{
    std::transform(str.begin(), str.end(), str.begin(), ::tolower);
    size_t pos{_dumpStr.find(str)};
    if (std::string::npos != pos) {
        for (size_t i{0}; str.size() > i; ++i)
            _dumpStr[pos + i] = '_';
        RefreshDump();
        auto it = std::find(_wordList.begin(), _wordList.end(), str);
        if (_wordList.end() == it)
            return -2;
        int id = std::distance(_wordList.begin(), it);
        if (id == _psswrdID) {
            _consoleBuff.WriteOutput("correct");
            RefreshInput();
            kill(getpid(), SIGINT);
            return -3;
        }
        --_lifeCounter;
        RefreshLife();
        if (!_lifeCounter) {
            _consoleBuff.WriteOutput("incorrect");
            RefreshInput();
            kill(getpid(), SIGINT);
            return -4;
        }
        _out.push_back(id);
        int matchCounter{0};
        for (size_t i{0}; _wordList[_psswrdID].size() > i; ++i)
            if ((_wordList[_psswrdID])[i] == (_wordList[id])[i])
                ++matchCounter;
        _consoleBuff.WriteOutput(std::to_string(matchCounter) + "/" + std::to_string(_wordList[_psswrdID].size()) + " correct");
        RefreshInput();
        return matchCounter;
    } else {
        _consoleBuff.WriteOutput("Input Error");
        RefreshInput();
        return -1;
    }
}

void flock::FLockDisplay::Bonus(void)
{
    BonusOption opt{(BonusOption)((int)(std::rand() % BonusOption::TOTAL))};
    int id{std::rand() % (int)(_wordList.size())};
    switch (opt) {
        case LIFERESET:
            _lifeCounter = LIFEMAX;
            RefreshLife();
            _consoleBuff.WriteOutput("reset");
            RefreshInput();
            return;
        case REMOVEDUD:
            while (id == _psswrdID || _out.end() != std::find(_out.begin(), _out.end(), id))
                id = std::rand() % _wordList.size();
            SearchMatch(_wordList[id]);
            _consoleBuff.WriteOutput("dud removed");
            RefreshInput();
            return;
        case NONE:
        case TOTAL:
        default:
            _consoleBuff.WriteOutput("N/A");
            RefreshInput();
            return;
    }
}

std::string flock::FLockDisplay::GenDumpLine(const int &startID)
{
    std::string line{};
    std::ostringstream addr{};
    addr << (void *)(&(_dumpStr[startID]));
    line += addr.str() + " ";
    for (int i{0}; _dInfo.dumpColsSize > i; ++i)
        line += _dumpStr[i + startID];
    std::transform(line.begin(), line.end(), line.begin(), ::toupper);
    line[1] = 'x';
    return line;
}

void flock::FLockDisplay::RefreshHeader(void)
{
    mvaddstr(0,0,"ROBCO INDUSTRIES (TM) TERMLINK PROTOCOL");
    mvaddstr(1,0,"ENTER PASSWORD NOW");
    refresh();
}

void flock::FLockDisplay::RefreshLife(void)
{
    std::string out{std::to_string(_lifeCounter) + " ATTEMPT(S) LEFT: "};
    for (int i{0}; _lifeCounter > i; ++i)
        out += "# ";
    for (int i{0}; (LIFEMAX - _lifeCounter) > i; ++i)
        out += "_ ";
    mvaddstr(3,0,out.c_str());
    refresh();
}

void flock::FLockDisplay::RefreshDump(void)
{
    for (int i{0}; _dInfo.colsNb > i; ++i) {
        int colsStart{(_dInfo.dumpColsSize + _dInfo.addrSize + 2) * i};
        for (int j{0}; _dInfo.dumpLinesSize > j; ++j) {
            mvaddstr(j + _dInfo.dumpStartLine, colsStart, GenDumpLine((j * _dInfo.dumpColsSize) + (_dInfo.dumpColsSize * _dInfo.dumpLinesSize * i)).c_str());
        }
    }
    refresh();
}

void flock::FLockDisplay::RefreshInput(void)
{
    int endSpace{3};
    int colsStart{(COLS - _dInfo.inputSize) - endSpace};
    mvaddch(LINES - 1, COLS - endSpace, ' ');
    for (int i{0}; _dInfo.dumpLinesSize > i; ++i)
        for (int j{0}; _dInfo.inputSize > j; ++j)
            mvaddch(i + _dInfo.dumpStartLine, colsStart + j, ' ');
    for (int i{0}; _dInfo.dumpLinesSize > i; ++i) {
        mvaddstr(i + _dInfo.dumpStartLine, colsStart, _consoleBuff.GetBuff()[i].c_str());
    }
    refresh();
}