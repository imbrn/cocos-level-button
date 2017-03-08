#ifndef LEVELBUTTON_BUTTON_MODEL_H
#define LEVELBUTTON_BUTTON_MODEL_H

#include <string>
#include "rating.h"
#include "button_model_observer.h"

namespace levelbutton {

///
/// ButtonModel class.
///
class ButtonModel {
  ButtonModelObserver *observer_ = nullptr;
  bool available_ = false;
  std::string text_ = "";
  Rating rating_ = Rating::ZERO;

public:
  ButtonModel();
  bool is_available() const;
  const std::string &text() const;
  Rating rating() const;
  void set_available(bool available);
  void set_text(const std::string &text);
  void set_rating(Rating rating);
  void set_observer(ButtonModelObserver *observer);
};

}

#endif
