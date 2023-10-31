#include "RandomWordAPI.hpp"
#include "nlohmann/json.hpp"
#include <iostream>

std::vector<std::string> rwapi::RandomWordAPI::GetWordList(const int &number, const int &length, const std::string &lang)
{
    std::array<char, 128> buff{};
    std::string cli{"curl \"" + BASEURL + "?lang=" + lang + "&number=" + std::to_string(number) + "&length=" + std::to_string(length) + "\""};
    std::unique_ptr<FILE, decltype(&pclose)> pipe{popen(cli.c_str(), "r"), pclose};
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    std::string cliRet{};
    while (nullptr != fgets(buff.data(), buff.size(), pipe.get())) {
        cliRet += buff.data();
    }
    std::vector<std::string> ret{};
    for (int i{0}; number > i; ++i) {
        std::string currentWord{};
        for (int j{0}; length > j; ++j) {
            int pos{2 + ((length + 3) * i) + j};
            if (cliRet.size() <= (size_t)pos)
                return ret;
            currentWord += cliRet[pos];
        }
        ret.push_back(currentWord);
    }
    return ret;
}