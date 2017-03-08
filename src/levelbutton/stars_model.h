#ifndef LEVELBUTTON_STARS_MODEL_H
#define LEVELBUTTON_STARS_MODEL_H

#include "stars_model_observer.h"

namespace levelbutton {

///
/// StarsModel class.
///
class StarsModel {
  StarsModelObserver *observer_ = nullptr;
  unsigned int quantity_ = 0;

public:
  StarsModel(unsigned int quantity);
  StarsModel();
  virtual ~StarsModel() {}
  unsigned int quantity() const;
  void set_quantity(unsigned int quantity);
  void set_observer(StarsModelObserver *observer);
};

}

#endif
