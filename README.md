Cocos Level Button
===

[Cocos2d-x](http://cocos2d-x.org/) component to represent a campaign level button.


## Features

* Two states: available, unvailable.

* Rating stars;

* Custom style;


## How to use

### Resources:

The level button component expects some resources in your path:

#### Images:

*To represent the button background in the available state:*

* levelbutton/background.png

*To represent the button background in the unvailable state:*

* levelbutton/background-d.png

*For rating stars:*

* levelbutton/star.png

#### Fonts

*For the button label:*

* fonts/levelbutton/font.ttf

## Default usage

```c++

// Create and configure the button.
auto button = levelbutton::Button::create();
button->model().set_text("20");
button->model().set_available(true);
button->model().set_rating(levelbutton::Rating::TWO);

my_scene->addChild(button);
```
