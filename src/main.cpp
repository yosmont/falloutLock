#include <ctime>
#include <random>
#include "FLock.hpp"

int main(void){
  std::srand(std::time(nullptr));
  initscr();
  flock::FLock fl{};
  fl.GameLoop();
  endwin();
}