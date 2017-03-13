#include "button_view.h"

namespace levelbutton {

bool ButtonView::init() {
  if (!cocos2d::ui::Widget::init())
    return false;
  DoInit();
  return true;
}

void ButtonView::DoInit() {
  setCascadeOpacityEnabled(true);
  InitAvailableBackground();
  InitUnavailableBackground();
  InitAvailableLabel();
  InitUnavailableLabel();
  InitStars();
}

void ButtonView::InitAvailableBackground() {
  available_background_ = cocos2d::ui::ImageView::create("levelbutton/background.png");
  addChild(available_background_);
}

void ButtonView::InitUnavailableBackground() {
  unavailable_background_ = cocos2d::ui::ImageView::create("levelbutton/background-d.png");
  addChild(unavailable_background_);
}

void ButtonView::InitAvailableLabel() {
  available_label_ = cocos2d::ui::Text::create("", "fonts/levelbutton/font.ttf", 28);
  available_label_->setTextColor({0, 0, 0, 255});
  available_label_->setTextHorizontalAlignment(cocos2d::TextHAlignment::CENTER);
  available_label_->setTextVerticalAlignment(cocos2d::TextVAlignment::CENTER);
  available_label_->ignoreContentAdaptWithSize(true);
  addChild(available_label_);
}

void ButtonView::InitUnavailableLabel() {
  unavailable_label_ = cocos2d::ui::Text::create("", "fonts/levelbutton/font.ttf", 28);
  unavailable_label_->setTextColor({200, 200, 200, 255});
  unavailable_label_->setTextHorizontalAlignment(cocos2d::TextHAlignment::CENTER);
  unavailable_label_->setTextVerticalAlignment(cocos2d::TextVAlignment::CENTER);
  unavailable_label_->ignoreContentAdaptWithSize(true);
  addChild(unavailable_label_);
}

void ButtonView::InitStars() {
  stars_ = Stars::create();
  addChild(stars_);
}

void ButtonView::onSizeChanged() {
  cocos2d::ui::Widget::onSizeChanged();
  LayoutAvailableBackground();
  LayoutUnavailableBackground();
  LayoutAvailableLabel();
  LayoutUnavailableLabel();
  LayoutStars();
}

void ButtonView::LayoutAvailableBackground() {
  ScaleBackground(available_background_);
  AlignBackground(available_background_);
}

void ButtonView::LayoutUnavailableBackground() {
  ScaleBackground(unavailable_background_);
  AlignBackground(unavailable_background_);
}

void ButtonView::ScaleBackground(cocos2d::ui::ImageView *background) {
  float horz = getContentSize().width / background->getContentSize().width;
  float vert = getContentSize().height / background->getContentSize().height;
  background->setScale(MIN(horz, vert));
}

void ButtonView::AlignBackground(cocos2d::ui::ImageView *background) {
  background->setAnchorPoint({0.5, 0.5});
  background->setPosition({getContentSize().width/2, getContentSize().height/2});
}

void ButtonView::LayoutAvailableLabel() {
  ScaleLabel(available_label_);
  AlignLabel(available_label_);
}

void ButtonView::LayoutUnavailableLabel() {
  ScaleLabel(unavailable_label_);
  AlignLabel(unavailable_label_);
}

void ButtonView::ScaleLabel(cocos2d::ui::Text *label) {
  label->setTextAreaSize({getContentSize().width * 0.75f, getContentSize().height * 0.40f});
}

void ButtonView::AlignLabel(cocos2d::ui::Text *label) {
  label->setAnchorPoint({0, 0});
  label->setPosition({getContentSize().width * 0.12f, getContentSize().height * 0.37f});
}

void ButtonView::LayoutStars() {
  ScaleStars();
  AlignStars();
}

void ButtonView::ScaleStars() {
  float w = getContentSize().width * 0.75f;
  float h = getContentSize().height * 0.16f;
  stars_->setContentSize({w, h});
}

void ButtonView::AlignStars() {
  float x = getContentSize().width * 0.12f;
  float y = getContentSize().height * 0.20f;
  stars_->setAnchorPoint({0, 0});
  stars_->setPosition({x, y});
}

cocos2d::ui::ImageView *ButtonView::available_background() {
  return available_background_;
}

cocos2d::ui::ImageView *ButtonView::unavailable_background() {
  return unavailable_background_;
}

cocos2d::ui::Text *ButtonView::available_label() {
  return available_label_;
}

cocos2d::ui::Text *ButtonView::unavailable_label() {
  return unavailable_label_;
}

Stars *ButtonView::stars() {
  return stars_;
}

}
