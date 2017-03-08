#ifndef LEVELBUTTON_BUTTON_H
#define LEVELBUTTON_BUTTON_H

#include "button_view.h"
#include "button_model.h"
#include "button_model_observer.h"

namespace levelbutton {

///
/// Button class.
///
class Button: public cocos2d::ui::Widget, public ButtonModelObserver {
  ButtonModel model_;
  ButtonView *view_ = nullptr;
  float last_scale_ = 1;
  
public:
  static Button *create(const ButtonModel &model);
  static Button *create();
  Button(const ButtonModel &model);
  virtual ~Button() {}
  virtual bool init() override;

  const ButtonModel &model() const;
  ButtonModel &model();
  void set_model(const ButtonModel &model);

protected:
  virtual void onSizeChanged() override;
  virtual void OnTextChanged() override;
  virtual void OnAvailabilityChanged() override;
  virtual void OnRatingChanged() override;
  virtual void onPressStateChangedToNormal() override;
  virtual void onPressStateChangedToPressed() override;

private:
  void DoInit();
  void InitView();
  void SetAvailable();
  void SetUnavailable();
  unsigned int RatingAsUint(Rating rating) const;
};

}

#endif
