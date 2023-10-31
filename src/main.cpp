#include <ctime>
#include <random>
#include "FLock.hpp"
#include "RandomWordAPI.hpp"

int main(int ac, char **av, char **env)
{
  (void)env;
  std::srand(std::time(nullptr));
  initscr();
  if (ac == 3) {
    flock::FLock fl{std::stoi(std::string{av[1]}), std::stoi(std::string{av[2]})};
    fl.GameLoop();
  } else {
    flock::FLock fl{};
    fl.GameLoop();
  }
  endwin();
}