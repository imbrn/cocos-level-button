#include "stars_view.h"

namespace levelbutton {

bool StarsView::init() {
  if (!cocos2d::ui::Widget::init())
    return false;
  setCascadeOpacityEnabled(true);
  return true;
}

void StarsView::AddStar() {
  auto star = cocos2d::ui::ImageView::create("levelbutton/star.png");
  stars_.push_back(star);
  addChild(star);
  Layout();
}

void StarsView::RemoveStar() {
  auto star = stars_.back();
  stars_.pop_back();
  removeChild(star);
  Layout();
}

void StarsView::RemoveAllStars() {
  for (auto star : stars_)
    removeChild(star);
  stars_.clear();
  Layout();
}

void StarsView::onSizeChanged() {
  cocos2d::ui::Widget::onSizeChanged();
  Layout();
}

void StarsView::Layout() {
  for (unsigned int i = 0; i < stars_.size(); i++)
    LayoutStar(i, stars_[i]);
}

void StarsView::LayoutStar(unsigned int index, cocos2d::ui::ImageView *star) {
  ScaleStar(index, star);
  AlignStar(index, star);
}

void StarsView::ScaleStar(unsigned int index, cocos2d::ui::ImageView *star) {
  float scale_horz = get_star_size()  / star->getContentSize().width;
  float scale_vert = getContentSize().height / star->getContentSize().height;
  star->setScale(MIN(scale_horz, scale_vert));
}

void StarsView::AlignStar(unsigned int index, cocos2d::ui::ImageView *star) {
  auto area = get_star_area(index);
  star->setAnchorPoint({0.5, 0.5});
  star->setPosition({area.getMidX(), area.getMidY()});
}

cocos2d::Rect StarsView::get_star_area(unsigned int index) const {
  auto origin = get_star_origin(index);
  auto size = get_star_size();
  cocos2d::Rect area;
  area.origin = origin;
  area.size = cocos2d::Size{size, size};
  return area;
}

cocos2d::Point StarsView::get_star_origin(unsigned int index) const {
  float x = getContentSize().width /  2 - get_stars_size() / 2;
  x += get_star_size() * index;
  x += gap_ * index;
  return {x, 0};
}

float StarsView::get_stars_size() const {
  return (get_star_size() * stars_.size()) + (gap_ * (stars_.size() - 1));
}

float StarsView::get_star_size() const {
  auto available_size = get_available_size();
  return MIN(available_size.width / stars_.size(), available_size.height);
}

cocos2d::Size StarsView::get_available_size() const {
  float w = getContentSize().width - (gap_ * (stars_.size() - 1));
  float h = getContentSize().height;
  return { w, h };
}

}
