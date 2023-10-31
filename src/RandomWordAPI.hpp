#ifndef RWAPI_HPP_
#define RWAPI_HPP_

#include <vector>
#include <string>

namespace rwapi {
    class RandomWordAPI {
        public:
            static std::vector<std::string> GetWordList(const int &number, const int &length, const std::string &lang = "en");
        private:
            inline static const std::string BASEURL{"https://random-word-api.herokuapp.com/word"};
    };
}

#endif /* RWAPI_HPP_ */