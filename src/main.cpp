#include <ctime>
#include <random>
#include "FLock.hpp"
#include "RandomWordAPI.hpp"

int main(void){
  std::srand(std::time(nullptr));
#if 0
  rwapi::RandomWordAPI::GetWordList(10, 5);
  exit(0);
#endif
  initscr();
  flock::FLock fl{};
  fl.GameLoop();
  endwin();
}