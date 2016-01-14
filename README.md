# Epic TV Fighting

__Epic TV Fighting__ is a 2D fighting game.

The game was made in a month. The source code has not changed to preserve it's inital state. I only adjust some things to be able to compile the project on
my current hardware.

[A gif animation of the gameplay](http://imgur.com/LczLJqp.gif)

## Assets
__Epic TV Fighting__ is quite data-driven. 

### Localized strings
Localized strings can be found in `asset/text.localization`

### Credits
The informations seen in the credit screen are stored in `asset/credits.cred`

### Game settings
The game settings are stored in `asset/game.settings`

### Player 
Players are described in `.player` files.
This file stores the _name_ of the player, it's _health_, every _animation sequences_, it's _combotree_, it's _walking speed_, it's _jump spring force_, it's _texture_.

### Combotree
Combotrees are stored in `.combotree` files.
The combotree format store every player's attack combo. 

### Animation sequence
Animation sequences are stored in `.seq` files.
This file store the animation's _duration_ in ms, every _frames_ of the animations where each one store the frame's collision _hitbox_.

### Visual effects
Visual effects are stored in `.fx` files.
A visual effect is only a frame-by-frame animation.

This file stores the effect's _duration_ in ms, it's _lifetime_ in ms, it's _animation frames_, the _spritesheet_ to use, the _sound_ to play when the effect occures.

### Scenes
Scenes are stored in `.scene` files.
A scene is composed of an _ambiant music_, a _background image_, a _width_ and a _floor_ level.

## How to compile?
To compile _Epic TV Fighting_, you need these tools/libraries:
- A cpp compiler
- CMake
- SFML 2
- Shell

## Building steps
1. Clone the repository
2. Move into the project's directory
3. Create a new directory named _build_
4. Move into the _build_ directory
5. Run this command `cmake ..`
6. Run this command `make`
7. Move to the project's root directory
8. Run this command `./launch`
9. Enjoy
