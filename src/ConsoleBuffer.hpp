#include <vector>
#include <string>
#include <ncurses.h>

namespace flock {
    class ConsoleBuffer {
        public:
            ConsoleBuffer(int height, int width);
            void AddToInput(char input) {AddToInput(std::string{input});}
            void AddToInput(std::string input);
            void RemoveToInput(void);
            void WriteOutput(std::string output);
            std::string &GetCurrentInput(void) {return _currentInput;}
            //std::string &GetCurrentInput(void) {return _currentInput;}
            std::vector<std::string> GetBuff(void) {return _buff;}
        private:
            void NewLine(bool isStartInput = false);
            void AddText(std::string txt);

            const int _h, _w;
            std::vector<std::string> _buff{};
            std::string _currentInput{};
    };
}