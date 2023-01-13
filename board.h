#ifndef BOARD_H
#define BOARD_H

#include <iterator>
#include <map>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "field.h"
#include "player.h"

class Board {
public:
  Board() : fields({}), positions({}) {}
  void addField(std::shared_ptr<Field> f) { fields.push_back(f); }

private:
  std::vector<std::shared_ptr<Field>> fields;
  std::map<const std::string &, size_t> positions;
};

#endif /* BOARD_H */