#pragma once
#ifndef FLOCK_HPP_
#define FLOCK_HPP_

#include <atomic>
#include "FLockDisplay.hpp"
#include <memory>

namespace flock {
    class FLock {
        public:
            FLock(int number = 100, int length = 8);
            void GameLoop(void);
        private:
            bool IsBonusStr(std::string toCheck);
            void ProcessTry(void);
            std::unique_ptr<FLockDisplay> _display{nullptr};
    };
}

#endif /* FLOCK_HPP_ */