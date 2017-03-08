#ifndef LEVELBUTTON_BUTTON_MODEL_OBSERVER_H
#define LEVELBUTTON_BUTTON_MODEL_OBSERVER_H

namespace levelbutton {

///
/// ButtonModelObserver class.
///
class ButtonModelObserver {
public:
  virtual ~ButtonModelObserver() {}
  virtual void OnTextChanged() {}
  virtual void OnAvailabilityChanged() {}
  virtual void OnRatingChanged() {}
};

}

#endif
