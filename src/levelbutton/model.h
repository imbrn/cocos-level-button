#ifndef LEVELBUTTON_MODEL_H
#define LEVELBUTTON_MODEL_H

#include "rating.h"
#include <string>

namespace levelbutton {

///
/// Model struct.
///
struct Model {
  bool available = false;
  bool solved = false;
  std::string text = "";
  Rating rating = Rating::ZERO;
};

}

#endif
