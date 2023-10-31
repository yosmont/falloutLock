#include "RandomWordAPI.hpp"
#include "nlohmann/json.hpp"
#include <cpr/cpr.h>
#include <iostream>

std::vector<std::string> rwapi::RandomWordAPI::GetWordList(const int &number, const int &length, const std::string &lang)
{
    cpr::Response r = cpr::Get(
        cpr::Url{BASEURL + "?lang=" + lang + "&number=" + std::to_string(number) + "&length=" + std::to_string(length)},
        cpr::Authentication{"user", "pass", cpr::AuthMode::BASIC},
        cpr::Parameters{}
    );
    std::cout << r.status_code << " - " << r.text << std::endl;
    nlohmann::json json{r.text};
    std::vector<std::string> ret{};
    for (auto elem : json) {
        ret.push_back(elem.get<std::string>());
    }
    return ret;
}