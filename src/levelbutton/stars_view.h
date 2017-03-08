#ifndef LEVELBUTTON_STARS_VIEW_H
#define LEVELBUTTON_STARS_VIEW_H

#include <cocos2d.h>
#include <ui/CocosGUI.h>

namespace levelbutton {

///
/// StarsView class.
///
class StarsView: public cocos2d::ui::Widget {
  std::vector<cocos2d::ui::ImageView*> stars_;
  float gap_ = 2;
public:
  CREATE_FUNC(StarsView);
  virtual ~StarsView() {}
  virtual bool init() override;
  virtual void AddStar();
  virtual void RemoveStar();
  virtual void RemoveAllStars();

protected:
  virtual void onSizeChanged() override;
  virtual void Layout();
  virtual void LayoutStar(unsigned int index, cocos2d::ui::ImageView *star);
  void ScaleStar(unsigned int index, cocos2d::ui::ImageView *star);
  void AlignStar(unsigned int index, cocos2d::ui::ImageView *star);
  cocos2d::Rect get_star_area(unsigned int index) const;
  cocos2d::Point get_star_origin(unsigned int index) const;
  float get_stars_size() const;
  float get_star_size() const;
  cocos2d::Size get_available_size() const;
};

}

#endif
