#include "ConsoleBuffer.hpp"

flock::ConsoleBuffer::ConsoleBuffer(int height, int width) :
    _h{height},
    _w{width}
{
    for (int i{0}; _h > i; ++i)
        _buff.push_back("");
    NewLine(true);
}

void flock::ConsoleBuffer::AddToInput(std::string input)
{
    _currentInput += input;
    AddText(input);
}

void flock::ConsoleBuffer::RemoveToInput(void)
{
    if (_currentInput.size() != 0) {
        _currentInput.pop_back();
        _buff.back().pop_back();
    }
}

void flock::ConsoleBuffer::WriteOutput(std::string output)
{
    _currentInput = "";
    NewLine();
    AddText(output);
    NewLine(true);
}

void flock::ConsoleBuffer::NewLine(bool isStartInput)
{
    _buff.erase(_buff.begin());
    if (isStartInput)
        _buff.push_back(">");
    else
        _buff.push_back("");
}

void flock::ConsoleBuffer::AddText(std::string txt)
{
    for (size_t i{0}; txt.size() > i; ++i) {
        if (_w <= _buff.back().size())
            NewLine();
        _buff.back() += txt[i];
    }
}
