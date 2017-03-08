#include "stars_model.h"

namespace levelbutton {

StarsModel::StarsModel(unsigned int quantity): quantity_(quantity) {}

StarsModel::StarsModel(): StarsModel(0) {}

unsigned int StarsModel::quantity() const {
  return quantity_;
}

void StarsModel::set_quantity(unsigned int quantity) {
  quantity_ = quantity;
  if (observer_) observer_->OnQuantityChanged();
}

void StarsModel::set_observer(StarsModelObserver *observer) {
  observer_ = observer;
}

}
