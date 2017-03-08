#ifndef LEVELBUTTON_BUTTON_VIEW_H
#define LEVELBUTTON_BUTTON_VIEW_H

#include <cocos2d.h>
#include <ui/CocosGUI.h>
#include "stars.h"

namespace levelbutton {

///
/// ButtonView class.
///
class ButtonView: public cocos2d::ui::Widget {
  cocos2d::ui::ImageView *available_background_ = nullptr;
  cocos2d::ui::ImageView *unavailable_background_ = nullptr;
  cocos2d::ui::Text *available_label_ = nullptr;
  cocos2d::ui::Text *unavailable_label_ = nullptr;
  Stars *stars_ = nullptr;
  
public:
  CREATE_FUNC(ButtonView);
  virtual ~ButtonView() {}
  virtual bool init() override;
  cocos2d::ui::ImageView *available_background();
  cocos2d::ui::ImageView *unavailable_background();
  cocos2d::ui::Text *available_label();
  cocos2d::ui::Text *unavailable_label();
  Stars *stars();

protected:
  virtual void onSizeChanged() override;

private:
  void DoInit();
  void InitAvailableBackground();
  void InitUnavailableBackground();
  void InitAvailableLabel();
  void InitUnavailableLabel();
  void InitStars();

  void LayoutAvailableBackground();
  void LayoutUnavailableBackground();
  void ScaleBackground(cocos2d::ui::ImageView *background);
  void AlignBackground(cocos2d::ui::ImageView *background);
  void LayoutAvailableLabel();
  void LayoutUnavailableLabel();
  void ScaleLabel(cocos2d::ui::Text *label);
  void AlignLabel(cocos2d::ui::Text *label);
  void LayoutStars();
  void ScaleStars();
  void AlignStars();
};

}

#endif
