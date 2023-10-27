#include <atomic>
#include "BindToC.hpp"
#include "FLockDisplay.hpp"
#include <memory>

namespace flock {
    class FLock {
        public:
            FLock(void);
            void GameLoop(void);
        private:
            void SignalCallback(int s) {(void)s;_quit.store(true);};
            bool IsBonusStr(std::string toCheck);
            void ProcessTry(void);
            btc::BindMethod<decltype(&FLock::SignalCallback)> _signalFToC{*this, &FLock::SignalCallback};
            std::atomic_bool _quit{false};
            std::unique_ptr<FLockDisplay> _display{nullptr};
    };
}