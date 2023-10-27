#include <vector>
#include <string>
#include <ncurses.h>
#include "ConsoleBuffer.hpp"

#define LIFEMAX 4

namespace flock {
    int AddrLength(void);

    struct displayInfo {
        int addrSize{AddrLength()};
        int colsNb{2};
        int inputSize{13};
        int totalSpaceSize{(colsNb * 2) + 7};
        int dumpStartLine{5};
        int dumpLinesSize{LINES - 5};
        int dumpColsSize{(COLS - ((addrSize * colsNb) + inputSize + totalSpaceSize)) / 2};
        bool endWithASpace{(((COLS - ((addrSize * colsNb) + inputSize + totalSpaceSize)) % 2) == 1) ? true : false };
    };

    class FLockDisplay {
        public:
            FLockDisplay(const std::vector<std::string> wordList);
            void Input(char c);
            std::string &GetInput(void);
            int SearchMatch(std::string str);
        private:
            std::string GenDumpLine(const int &startID);
            void RefreshHeader(void);
            void RefreshLife(void);
            void RefreshDump(void);
            void RefreshInput(void);
            void RefreshAll(void) {RefreshHeader();RefreshLife();RefreshDump();RefreshInput();}

            displayInfo _dInfo{};
            const std::vector<std::string> _wordList;
            const int _psswrdID;
            int _lifeCounter{LIFEMAX};
            std::string _dumpStr{};
            ConsoleBuffer _consoleBuff;
    };
}