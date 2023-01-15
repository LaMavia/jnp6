#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>


/*
  Ten plik udostępnia wyjątki wykorzystywane przez klasę WorldCup2022
  do sprawdzania warunków początkowych.
*/
class TooManyDiceException : public std::exception{
  virtual const char* what() const throw() 
  { 
    return "Za dużo kostek w grze!"; 
  } 
};

class TooFewDiceException : public std::exception{
  virtual const char* what() const throw() 
  { 
    return "Za mało kostek w grze!"; 
  } 
};

class TooManyPlayersException : public std::exception{
  virtual const char* what() const throw() 
  { 
    return "Za dużo graczy w grze!"; 
  }
};

class TooFewPlayersException : public std::exception{
  virtual const char* what() const throw() 
  { 
    return "Za mało graczy w grze!"; 
  }
};

#endif //EXCEPTIONS_H