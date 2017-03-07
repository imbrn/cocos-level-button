#ifndef LEVELBUTTON_BUTTON_H
#define LEVELBUTTON_BUTTON_H

#include <cocos2d.h>
#include <ui/CocosGUI.h>
#include <array>
#include <vector>
#include "model.h"

namespace levelbutton {

class ButtonBuilder;

///
/// Button class.
///
class Button: public cocos2d::ui::Widget {
  friend class ButtonBuilder;
  Model model_;
  cocos2d::ui::ImageView *available_background_ = nullptr;
  cocos2d::ui::ImageView *unavailable_background_ = nullptr;
  cocos2d::ui::Text *available_label_ = nullptr;
  cocos2d::ui::Text *unavailable_label_ = nullptr;
  std::array<cocos2d::ui::ImageView*, 3> stars_;
  std::vector<cocos2d::ui::ImageView*> visible_stars_;
  float last_scale_ = 1;

private:
  Button(const ButtonBuilder &builder);
  void CreateStars(const ButtonBuilder &builder);

public:
  virtual ~Button() {}
  virtual bool init() override;

  const Model &model() const;
  void set_model(const Model &model);

protected:
  virtual void onSizeChanged() override;
  virtual void onPressStateChangedToNormal() override;
  virtual void onPressStateChangedToPressed() override;

private:
  void DoInit();
  void InitStars();

  void OnModelChanged();
  void UpdateValues();
  void PositionComponents();
  void PositionBackground(cocos2d::ui::Widget *background);
  void ScaleBackground(cocos2d::ui::Widget *background);
  void AlignBackground(cocos2d::ui::Widget *background);
  void PositionLabel(cocos2d::ui::Widget *label);
  void ScaleLabel(cocos2d::ui::Widget *label);
  void AlignLabel(cocos2d::ui::Widget *label);
  void PositionStars();
  void ScaleStars();
  void AlignStars();
  float AlignStar(cocos2d::ui::Widget *star, float x, float y);
  void UpdateStars();
  void UpdateState();
  void SetWon();
  void SetAvailable();
  void SetUnavailable();
  void ShowStars();
  void HideStars();

  unsigned int visible_stars_quantity() const;

  cocos2d::Rect get_visible_stars_area() const;
  cocos2d::Point get_visible_stars_origin() const;
  cocos2d::Size get_visible_stars_size() const;
  float get_star_scale(cocos2d::ui::Widget *star) const;
  cocos2d::Rect get_stars_area() const;
  cocos2d::Rect get_label_area() const;
};

///
/// ButtonBuilder class.
///
class ButtonBuilder {
  Model model_;
  cocos2d::ui::ImageView *available_background_ = nullptr;
  cocos2d::ui::ImageView *unavailable_background_ = nullptr;
  cocos2d::ui::Text *available_label_ = nullptr;
  cocos2d::ui::Text *unavailable_label_ = nullptr;
  std::array<cocos2d::ui::ImageView*, 3> stars_;

public:
  ButtonBuilder(const Model &model);
  ButtonBuilder();
  virtual ~ButtonBuilder();
  ButtonBuilder &set_available_background(cocos2d::ui::ImageView *background);
  ButtonBuilder &set_unavailable_background(cocos2d::ui::ImageView *background);
  ButtonBuilder &set_available_label(cocos2d::ui::Text *label);
  ButtonBuilder &set_unavailable_label(cocos2d::ui::Text *label);
  ButtonBuilder &set_star(unsigned int index, cocos2d::ui::ImageView *star);

  Button *Build() const;
  Model BuildModel() const;
  cocos2d::ui::ImageView *BuildAvailableBackground() const;
  cocos2d::ui::ImageView *BuildUnavailableBackground() const;
  cocos2d::ui::Text *BuildAvailableLabel() const;
  cocos2d::ui::Text *BuildUnavailableLabel() const;
  cocos2d::ui::ImageView *BuildStar(unsigned int index) const;

private:
  void ClearStars();

  cocos2d::ui::ImageView *CreateDefaultAvailableBackground() const;
  cocos2d::ui::ImageView *CreateDefaultUnavailableBackground() const;
  cocos2d::ui::Text *CreateDefaultAvailableLabel() const;
  cocos2d::ui::Text *CreateDefaultUnavailableLabel() const;
  cocos2d::ui::ImageView *CreateDefaultStar(unsigned int index) const;

  void ReleaseStar(unsigned int index);
};

}

#endif
