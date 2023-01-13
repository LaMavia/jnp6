#ifndef PLAYER_H
#define PLAYER_H

#include <string>

class Player {
public:
  Player(std::string name) : name(name), money(1000), status("w grze") {}
  ~Player() = default;
  void setStatus(std::string newStatus) { 
    if (status == "*** bankrut ***") {
      return;
    }

    status = newStatus;
   }
  void giveMoney(unsigned int m) { money += m; }
  unsigned int takeMoney(unsigned int m) {
    if (m >= money) {
      auto res = money;
      
      money = 0;
      setStatus("*** bankrut ***");

      return res;
    } else {
      money -= m;

      return m;
    }
  }

  const std::string& getName() {
    return name;
  }

private:
  std::string name;
  unsigned int money;
  std::string status;
};

#endif