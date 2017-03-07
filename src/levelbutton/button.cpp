#include "button.h"

namespace levelbutton {

Button::Button(const ButtonBuilder &builder): model_(builder.BuildModel()) {
  available_background_ = builder.BuildAvailableBackground();
  unavailable_background_ = builder.BuildUnavailableBackground();
  available_label_ = builder.BuildAvailableLabel();
  unavailable_label_ = builder.BuildUnavailableLabel();
  CreateStars(builder);
}

void Button::CreateStars(const ButtonBuilder &builder) {
  for (unsigned int i = 0; i < stars_.size(); i++)
    stars_[i] = builder.BuildStar(i);
}

bool Button::init() {
  if (!cocos2d::ui::Widget::init())
    return false;
  DoInit();
  OnModelChanged();
  return true;
}

void Button::DoInit() {
  setTouchEnabled(true);
  addChild(available_background_);
  addChild(unavailable_background_);
  addChild(available_label_);
  addChild(unavailable_label_);
  InitStars();
}

void Button::InitStars() {
  for (auto star : stars_)
    addChild(star);
}

void Button::OnModelChanged() {
  UpdateValues();
  PositionComponents();
  UpdateState();
}

void Button::UpdateValues() {
  available_label_->setString(model_.text);
  unavailable_label_->setString(model_.text);
  UpdateStars();
}

void Button::UpdateStars() {
  unsigned int amount = visible_stars_quantity();
  visible_stars_.clear();
  for (unsigned int i = 0; i < amount; i++)
    visible_stars_.push_back(stars_[i]);
}

unsigned int Button::visible_stars_quantity() const {
  switch (model_.rating) {
    case Rating::THREE: return 3;
    case Rating::TWO: return 2;
    case Rating::ONE: return 1;
    default: return 0;
  }
}

void Button::PositionComponents() {
  PositionBackground(available_background_);
  PositionBackground(unavailable_background_);
  PositionLabel(available_label_);
  PositionLabel(unavailable_label_);
  PositionStars();
}

void Button::PositionBackground(cocos2d::ui::Widget *background) {
  ScaleBackground(background);
  AlignBackground(background);
}

void Button::ScaleBackground(cocos2d::ui::Widget *background) {
  float h = getContentSize().width / background->getContentSize().width;
  float v = getContentSize().height / background->getContentSize().height;
  background->setScale(MIN(h, v));
}

void Button::AlignBackground(cocos2d::ui::Widget *background) {
  background->setAnchorPoint({0.5, 0.5});
  background->setPosition({getContentSize().width/2, getContentSize().height/2});
}

void Button::PositionLabel(cocos2d::ui::Widget *label) {
  ScaleLabel(label);
  AlignLabel(label);
}

void Button::ScaleLabel(cocos2d::ui::Widget *label) {
  auto area = get_label_area();
  float h = area.size.width / label->getContentSize().width;
  float v = area.size.height / label->getContentSize().height;
  label->setScale(MIN(h, v));
}

void Button::AlignLabel(cocos2d::ui::Widget *label) {
  auto area = get_label_area();
  label->setAnchorPoint({0.5, 0.5});
  label->setPosition({area.getMidX(), area.getMidY()});
}

void Button::PositionStars() {
  ScaleStars();
  AlignStars();
}

void Button::ScaleStars() {
  for (auto star : visible_stars_)
    star->setScale(get_star_scale(star));
}

void Button::AlignStars() {
  auto area = get_visible_stars_area();
  float x = area.origin.x;
  for (auto star : visible_stars_)
    x = AlignStar(star, x, area.origin.y);
}

float Button::AlignStar(cocos2d::ui::Widget *star, float x, float y) {
  star->setAnchorPoint({0, 0});
  star->setPosition({x, y});
  return star->getBoundingBox().getMaxX() + 2;
}

cocos2d::Rect Button::get_visible_stars_area() const {
  auto origin = get_visible_stars_origin();
  auto size = get_visible_stars_size();
  return { origin, size };
}

cocos2d::Point Button::get_visible_stars_origin() const {
  auto stars_area = get_stars_area();
  auto visible_size = get_visible_stars_size();
  float x = stars_area.origin.x + (stars_area.size.width / 2 - visible_size.width / 2);
  float y = stars_area.origin.y;
  return { x, y };
}

cocos2d::Size Button::get_visible_stars_size() const {
  float width = 0;
  for (auto star : visible_stars_)
    width += star->getBoundingBox().size.width + 2;
  return { width - 2, get_stars_area().size.height };
}

float Button::get_star_scale(cocos2d::ui::Widget *star) const {
  return get_stars_area().size.height / star->getContentSize().height;
}

cocos2d::Rect Button::get_stars_area() const {
  return {
    getContentSize().width * 0.12f,
    getContentSize().height * 0.20f,
    getContentSize().width * 0.75f,
    getContentSize().height * 0.17f
  };
}

cocos2d::Rect Button::get_label_area() const {
  return {
    getContentSize().width * 0.12f,
    getContentSize().height * 0.12f,
    getContentSize().width * 0.75f,
    getContentSize().height * 0.80f
  };
}

void Button::UpdateState() {
  if (model_.available) {
    if (model_.solved) SetWon();
    else SetAvailable();
  } else {
    SetUnavailable();
  }
}

void Button::SetWon() {
  setEnabled(true);
  setTouchEnabled(true);
  available_background_->setVisible(true);
  available_label_->setVisible(true);
  unavailable_background_->setVisible(false);
  unavailable_label_->setVisible(false);
  ShowStars();
}

void Button::SetAvailable() {
  setEnabled(true);
  available_background_->setVisible(true);
  available_label_->setVisible(true);
  unavailable_background_->setVisible(false);
  unavailable_label_->setVisible(false);
  HideStars();
}

void Button::SetUnavailable() {
  setEnabled(false);
  available_background_->setVisible(false);
  available_label_->setVisible(false);
  unavailable_background_->setVisible(true);
  unavailable_label_->setVisible(true);
  HideStars();
}

void Button::ShowStars() {
  HideStars();
  for (auto star : visible_stars_)
    star->setVisible(true);
}

void Button::HideStars() {
  for (auto star : stars_)
    star->setVisible(false);
}

void Button::onSizeChanged() {
  cocos2d::ui::Widget::onSizeChanged();
  PositionComponents();
}

void Button::onPressStateChangedToNormal() {
  setScale(last_scale_);
}

void Button::onPressStateChangedToPressed() {
  last_scale_ = getScale();
  setScale(last_scale_ * 1.10f);
}

const Model &Button::model() const {
  return model_;
}

void Button::set_model(const Model &model) {
  model_ = model;
  OnModelChanged();
}


ButtonBuilder::ButtonBuilder(const Model &model): model_(model) {
  for (unsigned int i = 0; i < stars_.size(); i++)
    stars_[i] = nullptr;
}

ButtonBuilder::ButtonBuilder(): ButtonBuilder(Model()) {}

ButtonBuilder::~ButtonBuilder() {
  set_available_background(nullptr);
  set_unavailable_background(nullptr);
  set_available_label(nullptr);
  set_unavailable_label(nullptr);
  ClearStars();
}

void ButtonBuilder::ClearStars() {
  for (unsigned int i = 0; i < stars_.size(); i++)
    set_star(i, nullptr);
}

ButtonBuilder &ButtonBuilder::set_available_background(cocos2d::ui::ImageView *background) {
  if (available_background_) available_background_->release();
  available_background_ = background;
  return *this;
}

ButtonBuilder &ButtonBuilder::set_unavailable_background(cocos2d::ui::ImageView *background) {
  if (unavailable_background_) unavailable_background_->release();
  unavailable_background_ = background;
  return *this;
}

ButtonBuilder &ButtonBuilder::set_available_label(cocos2d::ui::Text *label) {
  if (available_label_) available_label_->release();
  available_label_ = label;
  return *this;
}

ButtonBuilder &ButtonBuilder::set_unavailable_label(cocos2d::ui::Text *label) {
  if (unavailable_label_) unavailable_label_->release();
  unavailable_label_ = label;
  return *this;
}

ButtonBuilder &ButtonBuilder::set_star(unsigned int index, cocos2d::ui::ImageView *star) {
  ReleaseStar(index);
  stars_[index] = star;
  return *this;
}

void ButtonBuilder::ReleaseStar(unsigned int index) {
  auto star = stars_[index];
  if (star) star->release();
  stars_[index] = nullptr;
}

Button *ButtonBuilder::Build() const {
  Button *obj = new Button(*this);
  if (obj->init()) {
    obj->autorelease();
    return obj;
  } else {
    delete obj;
    return nullptr;
  }
}

Model ButtonBuilder::BuildModel() const {
  return model_;
}

cocos2d::ui::ImageView *ButtonBuilder::BuildAvailableBackground() const {
  if (available_background_) return (cocos2d::ui::ImageView*)available_background_->clone();
  else return CreateDefaultAvailableBackground();
}

cocos2d::ui::ImageView *ButtonBuilder::BuildUnavailableBackground() const {
  if (unavailable_background_) return (cocos2d::ui::ImageView*)unavailable_background_->clone();
  else return CreateDefaultUnavailableBackground();
}

cocos2d::ui::Text *ButtonBuilder::BuildAvailableLabel() const {
  if (available_label_) return (cocos2d::ui::Text*)available_label_->clone();
  else return CreateDefaultAvailableLabel();
}

cocos2d::ui::Text *ButtonBuilder::BuildUnavailableLabel() const {
  if (unavailable_label_) return (cocos2d::ui::Text*)unavailable_label_->clone();
  else return CreateDefaultUnavailableLabel();
}

cocos2d::ui::ImageView *ButtonBuilder::BuildStar(unsigned int index) const {
  if (stars_[index]) return (cocos2d::ui::ImageView*)stars_[index]->clone();
  else return CreateDefaultStar(index);
}

cocos2d::ui::ImageView *ButtonBuilder::CreateDefaultAvailableBackground() const {
  return cocos2d::ui::ImageView::create("levelbutton/background.png");
}

cocos2d::ui::ImageView *ButtonBuilder::CreateDefaultUnavailableBackground() const {
  return cocos2d::ui::ImageView::create("levelbutton/background-d.png");
}

cocos2d::ui::Text *ButtonBuilder::CreateDefaultAvailableLabel() const {
  auto label = cocos2d::ui::Text::create("", "fonts/purisa/Purisa-Bold.ttf", 38);
  label->setTextColor(cocos2d::Color4B::BLACK);
  return label;
}

cocos2d::ui::Text *ButtonBuilder::CreateDefaultUnavailableLabel() const {
  auto label = cocos2d::ui::Text::create("", "fonts/purisa/Purisa-Bold.ttf", 38);
  label->setTextColor({200, 200, 200, 255});
  return label;
}

cocos2d::ui::ImageView *ButtonBuilder::CreateDefaultStar(unsigned int index) const {
  return cocos2d::ui::ImageView::create("levelbutton/star.png");
}

}
