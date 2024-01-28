# Swords-of-Honor-Ninja-vs-Romans
### A video game written in Allegro5 and C language

[**Swords-of-Honor-Ninja-vs-Romans**](https://github.com/jerryboy1031/Swords-of-Honor-Ninja-vs-Romans/edit/main) is a video game. It features a beautiful game scene,  delicated actions, and two characters: a Ninja and Romans soldier, fighting until one of them is dead. 
What's more, the tints (i.e. hurt tint) and actions are beyond description.

It is **authored by** [**陳佳俊**](https://github.com/jerryboy1031), **練韋辰**, and **高茝媛**. It is **maintained by** [**陳佳俊**](https://github.com/jerryboy1031). This project would not be possible without all these members. We would also like to thank all the people who have helped OpenPose in any way.


<p align="center">
    <img src=".vs/IMG_2466.JPG" width="300">
    <br>
    <sup>Authors 陳佳俊(left), 練韋辰(mid), and 高茝媛(right)
    </sup>
</p>



## Contents
1. [Results](#results)
2. [Features](#features)
3. [Contributors](#contributors)
4. [Installation](#installation)
6. [Send Us Feedback!](#send-us-feedback)
7. [Citation](#citation)
8. [License](#license)



## Results
### Gameplay
<p align="center">
    <img src=".github/media/dance_foot.gif" width="300">
    <br>
    <sup>Testing OpenPose: (Left) <a href="https://www.youtube.com/watch?v=2DiQUX11YaY" target="_blank"><i>Crazy Uptown Funk flashmob in Sydney</i></a> video sequence. (Center and right) Authors <a href="https://www.gineshidalgo.com" target="_blank">Ginés Hidalgo</a> and <a href="http://www.cs.cmu.edu/~tsimon" target="_blank">Tomas Simon</a> testing face and hands</sup>
</p>


## Features
**Main Functionality**:
- **2D real-time multi-person keypoint detection**:
    - 15, 18 or **25-keypoint body/foot keypoint estimation**, including **6 foot keypoints**. **Runtime invariant to number of detected people**.
    - **2x21-keypoint hand keypoint estimation**. **Runtime depends on number of detected people**. See [**OpenPose Training**](https://github.com/CMU-Perceptual-Computing-Lab/openpose_train) for a runtime invariant alternative.
    - **70-keypoint face keypoint estimation**. **Runtime depends on number of detected people**. See [**OpenPose Training**](https://github.com/CMU-Perceptual-Computing-

- **Fondamental units**:
    -  start
    -  exit
    -  icon
- **Fondamental game scenes**:
    -  menu
    -  gameplay
    -  gameover
- **Main units**
  - characters
    - ninja
    - Romans soldier
<p align="center">
    <img src="image/move1.png" width="100">
    <img src="image/move21.png" width="100">
    <br>
</p>

- **Qualification**
  - health bar (HP)

- **Qualification**
  - health bar (HP)

- **Gameplay**
  - Interaction (fighting)
  - Character sound effects (swinging swords, jumping)
  - MENU sound effects
  - Game start sound effect
  - Game ending sound effect
  - Special effects of being injured (character turns red)
  - Boundary setting

- **Moving of Character**
  -  moves horizontally
  -  horizontal acceleration
  -  vertical jump
  -  attack with a sword
    
### Concept figures
- Menu
- <p align="center">
    <img src=".vs/Menu.png" width="300">
    <br>
</p>
- GamePlay
- <p align="center">
    <img src=".vs/GamePlay.png" width="300">
    <br>
</p>
- GameOver
- <p align="center">
    <img src=".vs/GameOver.png" width="300">
    <br>
</p>


## Contributors
- [**陳佳俊**](https://github.com/jerryboy1031)
- **練韋辰**
- **高茝媛**
  
My two teammates and I came up with the game set together, for example, what's a fighting game be like, what are essential functions or elements in the game. Then, we had spending total a week collaborating to make this happened.

There's no part that I am completely responsible, but I had helped other teammate debug, fixed fundamental problems, and finished almost 95% of "character.c" file. "character.c" file may be the most important and difficult file in this game, and the lines of code is the biggest, too.


## Send Us Feedback!
Our library is open source for research purposes, and we want to improve it! So let us know (create a new GitHub issue or pull request, email us, etc.) if you...
1. Find/fix any bug (in functionality or speed) or know how to speed up or improve any part of OpenPose.
2. Want to add/show some cool functionality/demo/project made on top of it. We can add your project link to our project.

## License
OpenPose is freely available for free non-commercial use, and may be redistributed under these conditions. Please, see the [license](./LICENSE) for further details.
