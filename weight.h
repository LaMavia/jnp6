#ifndef WEIGHT_H
#define WEIGHT_H

#include <exception>

/*
    Enum reprezentujący możliwe rodzaje meczy.
*/
enum Weight { Friendly, Deciding, Final };
double doubleOfWeight(const Weight &w) {
  switch (w) {
  case Weight::Friendly:
    return 1.0;
  case Weight::Deciding:
    return 2.5;
  case Weight::Final:
    return 4.0;
  default:
    throw std::exception{};
  }
}

#endif /* WEIGHT_H */