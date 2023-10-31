#include <ctime>
#include <random>
#include "FLock.hpp"
#include "RandomWordAPI.hpp"

int main(void){
  std::srand(std::time(nullptr));
  rwapi::RandomWordAPI::GetWordList(10, 5);
  initscr();
  flock::FLock fl{};
  fl.GameLoop();
  endwin();
}