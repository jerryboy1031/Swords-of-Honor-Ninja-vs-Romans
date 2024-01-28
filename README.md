# Swords-of-Honor-Ninja-vs-Romans
### A video game written in Allegro5 and C language



My two teammates and I came up with the game set together, for example, what's a fighting game be like, what are essential functions or elements in the game. Then, we had spending total a week collaborating to make this happened.

There's no part that I am completely responsible, but I had helped other teammate debug, fixed fundamental problems, and finished almost 95% of "character.c" file. "character.c" file may be the most important and difficult file in this game, and the lines of code is the biggest, too.

[**Swords-of-Honor-Ninja-vs-Romans**](https://github.com/jerryboy1031/Swords-of-Honor-Ninja-vs-Romans/edit/main) is a video game. It features a beautiful game scene,  delicated actions, and two characters: a Ninja and Romans soldier, fighting until one of them is dead. 
What's more, the tints (i.e. hurt tint) and actions are beyond description.

It is **authored by** [**Ginés Hidalgo**](https://www.gineshidalgo.com), [**Zhe Cao**](https://people.eecs.berkeley.edu/~zhecao), [**Tomas Simon**](http://www.cs.cmu.edu/~tsimon), [**Shih-En Wei**](https://scholar.google.com/citations?user=sFQD3k4AAAAJ&hl=en), [**Yaadhav Raaj**](https://www.raaj.tech), [**Hanbyul Joo**](https://jhugestar.github.io), **and** [**Yaser Sheikh**](http://www.cs.cmu.edu/~yaser). It is **maintained by** [**Ginés Hidalgo**](https://www.gineshidalgo.com) **and** [**Yaadhav Raaj**](https://www.raaj.tech). OpenPose would not be possible without the [**CMU Panoptic Studio dataset**](http://domedb.perception.cs.cmu.edu). We would also like to thank all the people who [have helped OpenPose in any way](doc/09_authors_and_contributors.md).



<p align="center">
    <img src=".github/media/pose_face_hands.gif" width="480">
    <br>
    <sup>Authors <a href="https://www.gineshidalgo.com" target="_blank">Ginés Hidalgo</a> (left) and <a href="https://jhugestar.github.io" target="_blank">Hanbyul Joo</a> (right) in front of the <a href="http://domedb.perception.cs.cmu.edu" target="_blank">CMU Panoptic Studio</a></sup>
</p>



## Contents
1. [Results](#results)
2. [Features](#features)
3. [Contributors](#contributors)
4. [Installation](#installation)
5. [Quick Start Overview](#quick-start-overview)
6. [Send Us Feedback!](#send-us-feedback)
7. [Citation](#citation)
8. [License](#license)



## Results
### Game scene
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
- GamePlay
- GameOver


## Contributors
- [**陳佳俊**](https://github.com/jerryboy1031)
- [**練韋辰**]
- [**高茝媛**]

## Installation
If you want to use OpenPose without installing or writing any code, simply [download and use the latest Windows portable version of OpenPose](doc/installation/0_index.md#windows-portable-demo)!

Otherwise, you could [build OpenPose from source](doc/installation/0_index.md#compiling-and-running-openpose-from-source). See the [installation doc](doc/installation/0_index.md) for all the alternatives.



## Quick Start Overview
Simply use the OpenPose Demo from your favorite command-line tool (e.g., Windows PowerShell or Ubuntu Terminal). E.g., this example runs OpenPose on your webcam and displays the body keypoints:
```
# Ubuntu
./build/examples/openpose/openpose.bin
```
```
:: Windows - Portable Demo
bin\OpenPoseDemo.exe --video examples\media\video.avi
```

You can also add any of the available flags in any order. E.g., the following example runs on a video (`--video {PATH}`), enables face (`--face`) and hands (`--hand`), and saves the output keypoints on JSON files on disk (`--write_json {PATH}`).
```
# Ubuntu
./build/examples/openpose/openpose.bin --video examples/media/video.avi --face --hand --write_json output_json_folder/
```
```
:: Windows - Portable Demo
bin\OpenPoseDemo.exe --video examples\media\video.avi --face --hand --write_json output_json_folder/
```

Optionally, you can also extend OpenPose's functionality from its Python and C++ APIs. After [installing](doc/installation/0_index.md) OpenPose, check its [official doc](doc/00_index.md) for a quick overview of all the alternatives and tutorials.



## Send Us Feedback!
Our library is open source for research purposes, and we want to improve it! So let us know (create a new GitHub issue or pull request, email us, etc.) if you...
1. Find/fix any bug (in functionality or speed) or know how to speed up or improve any part of OpenPose.
2. Want to add/show some cool functionality/demo/project made on top of OpenPose. We can add your project link to our [Community-based Projects](doc/10_community_projects.md) section or even integrate it with OpenPose!


## License
OpenPose is freely available for free non-commercial use, and may be redistributed under these conditions. Please, see the [license](./LICENSE) for further details. Interested in a commercial license? Check this [FlintBox link](https://cmu.flintbox.com/#technologies/b820c21d-8443-4aa2-a49f-8919d93a8740). For commercial queries, use the `Contact` section from the [FlintBox link](https://cmu.flintbox.com/#technologies/b820c21d-8443-4aa2-a49f-8919d93a8740) and also send a copy of that message to [Yaser Sheikh](mailto:yaser@cs.cmu.edu).
