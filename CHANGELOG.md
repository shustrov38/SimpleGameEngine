# Changelog

[comment]: <> (## Unreleased)

[comment]: <> (### Added)

[comment]: <> (### Changed)

[comment]: <> (### Removed)

## 1.1.0 - 27-07-2021

### Added

- enumerated wrapper for range based loops

### Changed 

- world render system (now it is based on rays and can render 3d picture)

## 1.0.0 - 24-07-2021

Now engine can render multiple wall and player with rays. The rays can stop at the boundaries of the walls.

### Added

- Basic `Window`, `Engine`, `World`, `Object`, `WorldObject`, `Polygon`, `Wall`, `Player` classes.
- namespace `utl` with all custom mathematics functions like `utl::castRayToBoundary(...)`.
