#ifndef LEVELBUTTON_STARS_H
#define LEVELBUTTON_STARS_H

#include <cocos2d.h>
#include <ui/CocosGUI.h>
#include "stars_view.h"
#include "stars_model.h"
#include "stars_model_observer.h"

namespace levelbutton {

///
/// Stars class.
///
class Stars: public cocos2d::ui::Widget, public StarsModelObserver {
  StarsModel model_;
  StarsView *view_ = nullptr;

public:
  static Stars *create(const StarsModel &model);
  static Stars *create();
  Stars(const StarsModel &model);
  virtual ~Stars() {}
  virtual bool init() override;

  const StarsModel &model() const;
  StarsModel &model();
  void set_model(const StarsModel &model);

protected:
  virtual void onSizeChanged() override;
  virtual void OnQuantityChanged() override;

private:
  void DoInit();
  void InitView();
  void Update();
  void RemoveStars();
  void AddStars();
};

}

#endif
