#include "button.h"

namespace levelbutton {

Button *Button::create(const ButtonModel &model) {
  Button *obj = new Button(model);
  if (obj->init()) {
    obj->autorelease();
    return obj;
  } else {
    delete obj;
    return nullptr;
  }
}

Button *Button::create() {
  return create(ButtonModel());
}

Button::Button(const ButtonModel &model): model_(model) {
  model_.set_observer(this);
}

bool Button::init() {
  if (!cocos2d::ui::Widget::init())
    return false;
  DoInit();
  return true;
}

void Button::DoInit() {
  setTouchEnabled(true);
  setCascadeOpacityEnabled(true);
  InitView();
  OnTextChanged();
  OnAvailabilityChanged();
  OnRatingChanged();
}

void Button::InitView() {
  view_ = ButtonView::create();
  view_->setAnchorPoint({0, 0});
  view_->setPosition({0, 0});
  addChild(view_);
}

const ButtonModel &Button::model() const {
  return model_;
}

ButtonModel &Button::model() {
  return model_;
}

void Button::set_model(const ButtonModel &model) {
  model_.set_observer(nullptr);
  model_ = model;
  model_.set_observer(this);
}

void Button::onSizeChanged() {
  cocos2d::ui::Widget::onSizeChanged();
  view_->setContentSize(getContentSize());
}

void Button::OnTextChanged() {
  view_->available_label()->setString(model_.text());
  view_->unavailable_label()->setString(model_.text());
}

void Button::OnAvailabilityChanged() {
  if (model_.is_available())
    SetAvailable();
  else
    SetUnavailable();
}

void Button::onPressStateChangedToNormal() {
  cocos2d::ui::Widget::onPressStateChangedToNormal();
  setScale(last_scale_);
}

void Button::onPressStateChangedToPressed() {
  cocos2d::ui::Widget::onPressStateChangedToPressed();
  last_scale_ = getScale();
  setScale(last_scale_ * 1.075f);
}

void Button::SetAvailable() {
  view_->available_background()->setVisible(true);
  view_->available_label()->setVisible(true);
  view_->unavailable_background()->setVisible(false);
  view_->unavailable_label()->setVisible(false);
  view_->stars()->setVisible(true);
}

void Button::SetUnavailable() {
  view_->available_background()->setVisible(false);
  view_->available_label()->setVisible(false);
  view_->unavailable_background()->setVisible(true);
  view_->unavailable_label()->setVisible(true);
  view_->stars()->setVisible(false);
}

void Button::OnRatingChanged() {
  view_->stars()->model().set_quantity(RatingAsUint(model_.rating()));
}

unsigned int Button::RatingAsUint(Rating rating) const {
  switch (rating) {
    case Rating::THREE: return 3;
    case Rating::TWO: return 2;
    case Rating::ONE: return 1;
    default: return 0;
  }
}

}
