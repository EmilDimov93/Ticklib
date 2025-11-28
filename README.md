# Ticklib

A 3D library with windows.h that can be used to display and manipulate triangulated .obj files

## Quick Start

See [QUICKSTART.md](QUICKSTART.md) for minimal setup instructions.

## Functions

All functions start with the prefix tl

#### tlInit

Initializes the window and environment

No arguments

#### tlWindowOpen

Checks if window should close

No arguments

#### tlClearBackground

Sets all pixels to one color

Arguments:
- uint32_t color

#### tlAddMesh

Adds a mesh to the scene. The filename becomes the name of the mesh and the triangles are set to the given color

Arguments:
- std::string filePath
- Position3 position
- uint32_t color

#### tlDrawMeshes

Draws all meshes added to the scene. Must be called every frame. The argument specifies whether the triangles drawn are filled

Arguments:
- bool trianglesFilled

#### tlGetFps

Returns the current Frames Per Second

#### tlSetCameraSpeed

The camera is handled automatically, but you can change the movement speed with this function

Arguments:
- float newSpeed

#### tlSetFov

Set the Field Of View of the camera

Arguments
- float newFov

#### tlMoveMesh

Moves a mesh by the given delta. Mesh can be specified by name

Arguments Overload 1:
- uint32_t index
- Position3 delta

Arguments Overload 2:
- std::string name
- Position3 delta

#### tlRotateMesh

Rotates a mesh by the given delta. Mesh can be specified by name

Arguments Overload 1:
- uint32_t index
- Rotation3 rotation

Arguments Overload 2:
- std::string name
- Rotation3 rotation

#### tlScaleMesh

Scales a mesh by the given scale factor. Scale factor can either be a float for all axes, or specified for each axis separately by using the overload with Scale3 argument. Mesh can be specified by name

Arguments Overload 1:
- uint32_t index
- float scale

Arguments Overload 2:
- std::string name
- float scale

Arguments Overload 3:
- uint32_t index
- Scale3 scale

Arguments Overload 4:
- std::string name
- Scale3 scale

#### tlIsDown

Checks if a key or mouse button is down. Returns true while down

Arguments Overload 1:
- TLMouseBtn btn

Arguments Overload 2:
- TLKey key

#### tlIsUp

Checks if a key or mouse button is up. Returns true while up

Arguments Overload 1:
- TLMouseBtn btn

Arguments Overload 2:
- TLKey key

#### tlIsPressed

Checks if a key or mouse button has just been pressed. Returns true only on the first frame when pressed

Arguments Overload 1:
- TLMouseBtn btn

Arguments Overload 2:
- TLKey key

#### tlIsReleased

Checks if a key or mouse button has just been released. Returns true only on the first frame when released

Arguments Overload 1:
- TLMouseBtn btn

Arguments Overload 2:
- TLKey key

#### tlGetMousePos

Returns the current mouse position

No arguments

## Definitions

### Structures

#### Position2

Structure with floats x and y

#### Position3

Structure with floats x, y and z

#### Scale3

Structure with floats x, y and z

#### Rotation2

Structure with floats pitch and yaw

#### Rotation3

Structure with floats pitch, yaw and roll

#### Size2

Structure with ints w and h

#### Size3

Structure with ints w, h and d

#### Triangle

Structure with an array of 3 Position3 objects serving as the vertices of a triangle. Also has a color field

#### Vec4

Structure with floats x, y, z and w

### Constants

#### TL_DEFAULT_CAMERA_SPEED

Used to return to the default camera speed with tlSetCameraSpeed()

#### TL_DEFAULT_FOV

Used to return to the default field of view with tlSetFov

#### TL_MOUSE_BTN_COUNT

The amount of mouse buttons

#### TL_KEY_COUNT

The amount of keyboard keys

#### Colors

All colors start with the prefix COLOR_ and resume with the color in capital letters(example: COLOR_WHITE)

Included colors: white, black, red, green, blue, light blue, yellow, cyan, magenta, orange, purple, pink, brown, gray, light gray, dark gray

### Enums

#### KeyState

Includes 4 key states:
- KEY_STATE_DOWN
- KEY_STATE_UP
- KEY_STATE_PRESSED
- KEY_STATE_RELEASED

#### TLMouseBtn

Contains all mouse buttons. Used in input functions

- TL_MOUSE_BTN_LEFT
- TL_MOUSE_BTN_RIGHT

...

#### TLKey

Contains all keyboard keys. Used in input functions

- TL_KEY_A
- TL_KEY_B

...