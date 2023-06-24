# ECSTeroid
an Asteroid game using ECS, developed using C++, EnTT, Box2D, and SFML libraries. This project was built with careful consideration of efficient and scalable design principles, while also maintaining code readability and simplicity in changing or adding new content to the game.

# Features
### Game
To Be Added

### Engine
- Simple event system

Libraries used:
- SFML for Rendering
- Box2D for Physics
- EnTT for ECS

# Engine Principles
The engine is divided into 5 crucial parts: Scenes, Entities, Components, Systems, and Events.

To Be Added below
### Scenes
### Services
### Entities
### Components
### Systems
### Events

# Project Roadmap
- ~~External Library Implementations~~
- ~~Base Engine Architecture~~
- In-Game Mechanics
  - ~~Simple Player Movement~~
  - ~~Wrap Around System~~
  - Shooting and Damage Mechanic
  - Asteroid Splitting Mechanic
  - Health and Score UI
  - Difficulty Progression
  - Game Over State
- Service Layer
- Audio System
- Scene Management
- Main Menu
  - Button Entity
  - UI Design
- Simple Tweening System
- Game Particles

# Improvement Notes
_Last updated: 24/6/2023_
- Serializable components for entity
- A component that is created from a definition component should live side by side with the definition
- (not sure if possible) Require attribute and another attribute that prevents from being added outside of systems
- In-game Debug tool:
  - Hierarchy viewer
  - Component inspectory
  - System inspector
- Systems should be decoupled from entt::registry
  - ~~This is possible by introducing a "service"? layer that systems can take a handle on~~ 
  - The above is invalid because a "Service" layer should exist above scenes and on the application layer, and registry should exist only in the scene layer.
- Should be service:
  - TextureService to pre-load on-demand texture
  - SFMLScreen for anything window-related
  - SceneManager to do anything scene related like switching scenes
  - InputService to handle keybindings, detection, etc.
  - AudioService to load and handle audio playback 
- Should make extension functions to convert float and angle to Box2D world floats and radians
- Should have static Screen (or service?) class to reference width and height dynamically
- There seems to be a lot of systems that require a definition component to construct another component (eg: Box2DPhysicsSystem, SFMLSpriteSystem, etc). There has got to be a better way.
  - using entt's on_construct doesn't seem to be allowed (assertion failed), definitely for a good reason