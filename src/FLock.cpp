#include "FLock.hpp"
#include <signal.h>

#if 0
#include <libnotify/notify.h>
#endif


std::atomic_bool quit{false};

void SignalCallback(int s)
{
    (void)s;
    quit.store(true);
}

flock::FLock::FLock(void)
{
    signal(SIGINT, &SignalCallback);
    signal(SIGTERM, &SignalCallback);
    std::vector<std::string> v{"hello", "world", "words", "worms", "hacks", "babel", "eagle", "early", "fable", "nacho", "oasis", "yacks", "zakat", "cable", "babka", "babas", "abaca", "aalii", "aargh", "daals", "dados", "faces", "facet", "facia", "gadid", "gabby", "haafs", "haars", "habit", "hadal", "hacek", "icily", "jacks", "jabot"};
    _display.reset(new FLockDisplay{v});
}

void flock::FLock::GameLoop(void)
{
    for (int input{getch()}; !quit.load(); input = getch()) {
        switch (input) {
            case 10:
                ProcessTry();
                break;
            case 127:
                _display->Input((char)-1);
                break;
            default:
                _display->Input(input);
        }
    }
}

bool flock::FLock::IsBonusStr(std::string toCheck)
{
    std::string t[4]{{"{}"}, {"[]"}, {"<>"}, {"()"}};
    for (int i{0}; 4 > i; ++i)
        if (toCheck.front() == t[i][0] && toCheck.back() == t[i][1])
            return true;
    return false;
}

void flock::FLock::ProcessTry(void)
{
    std::string &currentInput{_display->GetInput()};
    bool valid{false};
    switch (isalpha(currentInput.front())) {
        case 0:
            if (IsBonusStr(currentInput))
                valid = true;
            break;
        default:
            for (char elem : currentInput)
                if (!isalpha(elem))
                    break;
            valid = true;
            break;
    }
    if (valid) {
        _display->SearchMatch(currentInput);
        if (IsBonusStr(currentInput))
            _display->Bonus();
    } else {
        _display->Output("Input Error");
    }
}