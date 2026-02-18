# Made With [Smile](https://github.com/vitorbetmann/smile)

#### Recreated classic games in C to deepen understanding of low-level programming and game architecture, triggering the development of the Smile library.
#### Shoutout to CS50's Introduction to Game Development for the great lessons and game assets.

---

### 🧱 Breakout
- Uses Smile's SceneManager, SaveLoad, and Particle System

[Play it on itch]()  

---


### 🐤 Flappy Bird
- Uses Smile's SceneManager
- Built a custom queue to manage pipes with a O(1) enqueue and dequeue operations.
- Applied tracked iteration optimization so the Bird only checks collision with the next pipe, reducing per-frame computation.

[Play it on itch](https://vitorbetmann.itch.io/fifty-bird)  

---

## 🕹️ Games

### 🟢 Pong (

- Does not use any Smile modules but kickstarted the journey.
- Created a Python script to generate a .cmake file listing all .c files, which is included in CMakeLists.txt to set the executable sources.

[Play it on itch](https://vitorbetmann.itch.io/pong)  

---
