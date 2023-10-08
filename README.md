# ECSTeroid
an Asteroid game using ECS, developed using C++, EnTT, Box2D, and SFML libraries. This project was built with careful consideration of efficient and scalable design principles, while also maintaining code readability and simplicity in changing or adding new content to the game.

# About
### Game
Dodge and destroy as many asteroids as you can!
Press **[SPACE]** to shoot, and press **[WASD]** to move! 

### Engine
- Simple Event System
- ECS-based Tween System

Libraries used:
- SFML for Rendering
- Box2D for Physics
- EnTT for ECS

# Project Roadmap
- ~~External Library Implementations~~
- ~~Base Engine Architecture~~
- In-Game Mechanics
  - ~~Simple Player Movement~~
  - ~~Wrap Around System~~
  - ~~Shooting and Damage Mechanic~~
  - ~~Asteroid Splitting Mechanic~~
  - ~~Health and Score UI~~
  - Difficulty Progression
  - ~~Game Over State~~
- ~~Service Layer~~
  - ~~SFMLTextureService~~
  - ~~SFMLFontService~~
  - ~~SFMLAudioService~~
- ~~Audio System~~
- ~~Scene Management~~
- ~~IWindow~~
- Main Menu
  - ~~Button Entity~~
  - UI Design

# Improvement Notes
_Last updated: 2023/8/2_
- Shouldn't unload from destructor
- Extract the architecture here into a framework. What's needed:
  - Application must be inheritable to describe scenes and services
  - Scenes shouldn't be handled by Application, should be handled by a SceneHandler
  - Services Dependency Injection system
  - SFML handled through an IWindow (which exists and overridable through application)
- Refactor UI and Collision Systems to use inheritance to prevent repeating code
  - Everything in the UI folder should derive from a UISystem
- Serializable components for entity
- (not sure if possible) add "Require" attribute and another attribute that prevents components from being added outside of systems
- Go through all code and replace magic numbers with consts
- In-game Debug tool:
  - Hierarchy viewer
  - Component inspector
  - System inspector
- Systems should be decoupled from entt::registry
  - ~~This is possible by introducing a "service"? layer that systems can take a handle on~~ 
  - The above is invalid because a "Service" layer should exist above scenes and on the application layer, and registry should exist only in the scene layer.
- Should be service:
  - SFMLScreen for anything window-related
  - InputService to handle keybindings, detection, etc.
- Should make extension functions to convert float and angle to Box2D world floats and radians
- Should have static Screen (or service?) class to reference width and height dynamically
- There seems to be a lot of systems that require a definition component to construct another component (eg: Box2DPhysicsSystem, SFMLSpriteSystem, etc). There has got to be a better way.
  - using entt's on_construct doesn't seem to be allowed (assertion failed), definitely for a good reason
  - A component that is created from a definition component should live side by side with the definition