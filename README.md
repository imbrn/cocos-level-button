Cocos Level Button
===

[Cocos2d-x](http://cocos2d-x.org/) component to represent a campaign level button. It can be used to show a list of
levels in sequence, representing a campaign.


## Features

* Support to three states: available, unvailable, won (available with stars);

* Custom style;


## How to use

The level button expects some convetions for it to work:

### Default usage

```c++
// First you need a model to the button
levelbutton::Model model;
model.text = "20";
model.available = true;
model.solved = true;
model.rating = levelbutton::Rating::THREE;
  
// Create you button using a builder
auto button = levelbutton::ButtonBuilder(model)
    .Build();

my_scene->addChild(button);
```

### Custom usage

The `ButtonBuilder` can be used to create custom style for the `Button`.

### Resources:

#### Images:

*To represent the button background in the available state:*

* levelbutton/background.png

*To represent the button background in the unvailable state:*

* levelbutton/background-d.png

*For rating stars:*

* levelbutton/star.png

#### Fonts

*For the button label:*

* fonts/purisa/Purisa-Bold.ttf
