#include "stars.h"

namespace levelbutton {

Stars *Stars::create(const StarsModel &model) {
  Stars *obj = new Stars(model);
  if (obj->init()) {
    obj->autorelease();
    return obj;
  } else {
    delete obj;
    return nullptr;
  }
}

Stars *Stars::create() {
  return create(StarsModel());
}

Stars::Stars(const StarsModel &model): model_(model) {
  model_.set_observer(this);
}

bool Stars::init() {
  if (!cocos2d::ui::Widget::init())
    return false;
  DoInit();
  return true;
}

void Stars::DoInit() {
  InitView();
  Update();
}

void Stars::InitView() {
  view_ = StarsView::create();
  view_->setAnchorPoint({0, 0});
  view_->setPosition({0, 0});
  addChild(view_);
}

const StarsModel &Stars::model() const {
  return model_;
}

StarsModel &Stars::model() {
  return model_;
}

void Stars::set_model(const StarsModel &model) {
  model_.set_observer(nullptr);
  model_ = model;
  model_.set_observer(this);
  Update();
}

void Stars::onSizeChanged() {
  cocos2d::ui::Widget::onSizeChanged();
  view_->setContentSize(getContentSize());
}

void Stars::OnQuantityChanged() {
  Update();
}

void Stars::Update() {
  RemoveStars();
  AddStars();
}

void Stars::RemoveStars() {
  view_->RemoveAllStars();
}

void Stars::AddStars() {
  for (unsigned int i = 0; i < model_.quantity(); i++)
    view_->AddStar();
}

}
