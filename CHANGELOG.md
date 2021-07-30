# Changelog

[comment]: <> (## Unreleased)

[comment]: <> (### Added)

[comment]: <> (### Changed)

[comment]: <> (### Removed)

## 1.2.0 - 31-07-2021

### Changed

- minimap fov rendered as convex shape.
- all useful variables and functions moved into `Player` class.
- render system (each object has its own color).
- some fixes and additions to  namespace `utl`.

## 1.1.1 - 28-07-2021

### Added 

- minimap of the world for debugging purposes.
- debug tools for `Player::look()` function.

### Changed

- fixed issue when the rays could pass through objects (`Player::look()`).

## 1.1.0 - 27-07-2021

### Added

-  `enumerated(...)` wrapper for range based loops.

### Changed 

- `World` render system (now it is based on rays and can render 3d picture).

## 1.0.0 - 24-07-2021

Now engine can render multiple wall and player with rays. The rays can stop at the boundaries of the walls.

### Added

- Basic `Window`, `Engine`, `World`, `Object`, `WorldObject`, `Polygon`, `Wall`, `Player` classes.
- namespace `utl` with all custom mathematics functions like `utl::castRayToBoundary(...)`.
