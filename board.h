#ifndef BOARD_H
#define BOARD_H

#include <exception>
#include <iterator>
#include <memory>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include "field.h"
#include "player.h"
#include "resetable.h"

/*
  Plansza pamięta jakie pola występują w grze w odpowiedniej kolejności 
  oraz gdzie znajduje się dany gracz i go przemieszcza. 
*/
class Board : public Resetable {
public:
  Board() : fields({}), positions() {}
  void addField(std::shared_ptr<Field> f) { fields.push_back(f); }
  void addPlayer(Player &p) { positions.insert({p.getName(), 0}); }
  /*
    Sprawdza, czy gracz może ruszyć się z obecnego pola.
  */
  bool canPlayerMove(const Player &p) {
    auto name = p.getName();
    auto pos = positions[name];

    return fields[pos]->canMove(p);
  }
  /*
    Zmienia pozycję gracza `p` o `dPosition` pól.
  */
  void movePlayer(Player &p, size_t dPosition) {
    auto name = p.getName();
    auto pos = positions[name];
    auto nFields = fields.size();

    fields[pos]->onLeave(p);
    while (dPosition > 1) {
      pos = (pos + 1) % nFields;
      dPosition--;
      fields[pos]->onPass(p);
    }

    pos = (pos + 1) % nFields;
    fields[pos]->onStay(p);
    positions[name] = pos;
  }

  std::string getPlayerStatus(Player &p) {
    return fields[positions[p.getName()]]->giveStatus(p);
  }

  std::string getPlayerFieldName(Player &p) {
    return fields[positions[p.getName()]]->getName();
  }

  void reset() {
    fields.clear();
    positions.clear();
  }

private:
  std::vector<std::shared_ptr<Field>> fields;
  std::unordered_map<std::string, size_t> positions;
};

#endif /* BOARD_H */