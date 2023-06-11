# ECSTeroid
an Asteroid game using ECS, developed using C++, EnTT, Box2D, and SFML libraries. This project was built with careful consideration of efficient and scalable design principles, while also maintaining simplicity in changing or adding new content to the game.

## Improvement Notes
- Systems should be decoupled from entt::registry
  - This is possible by introducing a "service"? layer that systems can take a handle on
- On-demand assets should be preloaded before entering scenes
  - Can be made as services if we introduce service layer
