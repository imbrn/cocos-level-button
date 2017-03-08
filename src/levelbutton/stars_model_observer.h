#ifndef LEVELBUTTON_STARS_MODEL_OBSERVER_H
#define LEVELBUTTON_STARS_MODEL_OBSERVER_H

namespace levelbutton {

///
/// StarsModelObserver class.
///
class StarsModelObserver {
public:
  virtual ~StarsModelObserver() {}
  virtual void OnQuantityChanged() {}
};

}

#endif
