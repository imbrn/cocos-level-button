#include "button_model.h"

namespace levelbutton {

ButtonModel::ButtonModel() {}

bool ButtonModel::is_available() const {
  return available_;
}

const std::string &ButtonModel::text() const {
  return text_;
}

Rating ButtonModel::rating() const {
  return rating_;
}

void ButtonModel::set_available(bool available) {
  available_ = available;
  if (observer_) observer_->OnAvailabilityChanged();
}

void ButtonModel::set_text(const std::string &text) {
  text_ = text;
  if (observer_) observer_->OnTextChanged();
}

void ButtonModel::set_rating(Rating rating) {
  rating_ = rating;
  if (observer_) observer_->OnRatingChanged();
}

void ButtonModel::set_observer(ButtonModelObserver *observer) {
  observer_ = observer;
}

}
