#include "RandomWordAPI.hpp"
#include "nlohmann/json.hpp"
#include <cpr/cpr.h>
#include <iostream>

std::vector<std::string> rwapi::RandomWordAPI::GetWordList(const int &number, const int &length, const std::string &lang)
{
    cpr::Response r = cpr::Get(cpr::Url{BASEURL + "?lang=" + lang + "&number=" + std::to_string(number) + "&length=" + std::to_string(length)});
    std::cout << r.text << std::endl;
    return std::vector<std::string>{};
}