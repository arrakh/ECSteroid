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
### Entities
### Components
### Systems
### Events

# Improvement Notes
_Last updated: 16/6/2023_
- Serializable components for entity
- A component that is created from a definition component should live side by side with the definition
- (not sure if possible) Require attribute and another attribute that prevents from being added outside of systems
- In-game Debug tool:
  - Hierarchy viewer
  - Component inspector
  - System inspector
- Systems should be decoupled from entt::registry
  - This is possible by introducing a "service"? layer that systems can take a handle on
- On-demand assets should be preloaded before entering scenes
  - Can be made as services if we introduce service layer
- Should make extension functions to convert float and angle to Box2D world floats and radians
- Should have static Screen (or service?) class to reference width and height dynamically
- There seems to be a lot of systems that require a definition component to construct another component (eg: Box2DPhysicsSystem, SFMLSpriteSystem, etc). There has got to be a better way.
  - using entt's on_construct doesn't seem to be allowed (assertion failed), definitely for a good reason