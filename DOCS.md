# Documentation

## Functions

All functions start with the prefix `tl`.

### tlInit

Initializes the window and environment.

**No arguments**

### tlWindowOpen

Checks if window should close. Returns a boolean.

**No arguments**

### tlClearBackground

Sets all pixels to one color.

**Arguments:**
- `tlColor color`

### tlAddMesh

Adds a mesh to the scene. The filename becomes the name of the mesh and the triangles are set to the given color.

Returns the index of the new mesh in the list.

**Arguments:**
- `std::string filePath`
- `Position3 position`
- `tlColor color`

### tlDrawMeshes

Draws all meshes added to the scene. Must be called every frame. The argument specifies whether the triangles drawn are filled.

**Arguments:**
- `bool trianglesFilled`

### tlGetFps

Returns the current Frames Per Second.

### tlSetCameraSpeed

The camera is handled automatically, but you can change the movement speed with this function.

**Arguments:**
- `float newSpeed`

### tlSetFov

Set the Field Of View of the camera.

**Arguments:**
- `float newFov`

### tlMoveMesh

Moves a mesh by the given delta. Mesh can be specified by name.

**Arguments Overload 1:**
- `uint32_t index`
- `Position3 deltaPos`

**Arguments Overload 2:**
- `std::string name`
- `Position3 deltaPos`

### tlRotateMesh

Rotates a mesh by the given delta. Mesh can be specified by name.

**Arguments Overload 1:**
- `uint32_t index`
- `Rotation3 deltaRot`

**Arguments Overload 2:**
- `std::string name`
- `Rotation3 deltaRot`

### tlScaleMesh

Scales a mesh by a uniform value or a non-uniform Scale3. Mesh can be specified by name.

**Arguments Overload 1:**
- `uint32_t index`
- `float deltaScale`

**Arguments Overload 2:**
- `std::string name`
- `float deltaScale`

**Arguments Overload 3:**
- `uint32_t index`
- `Scale3 deltaUniformScale`

**Arguments Overload 4:**
- `std::string name`
- `Scale3 deltaUniformScale`

### tlIsDown

Checks if a key or mouse button is down. Returns true while down.

**Arguments Overload 1:**
- `TLMouseBtn btn`

**Arguments Overload 2:**
- `TLKey key`

### tlIsUp

Checks if a key or mouse button is up. Returns true while up.

**Arguments Overload 1:**
- `TLMouseBtn btn`

**Arguments Overload 2:**
- `TLKey key`

### tlIsPressed

Checks if a key or mouse button has just been pressed. Returns true only on the first frame when pressed.

**Arguments Overload 1:**
- `TLMouseBtn btn`

**Arguments Overload 2:**
- `TLKey key`

### tlIsReleased

Checks if a key or mouse button has just been released. Returns true only on the first frame when released.

**Arguments Overload 1:**
- `TLMouseBtn btn`

**Arguments Overload 2:**
- `TLKey key`

### tlGetMousePos

Returns the current mouse position.

**No arguments**

## Definitions

### tlColor

Type for RGBA colors in format 0xAARRGGBB

### Structures

#### Position2

Structure with floats x and y.

#### Position3

Structure with floats x, y and z.

#### Scale3

Structure with floats x, y and z.

#### Rotation3

Structure with floats pitch, yaw and roll.

### Colors

All colors are in the namespace `TlColors`.

Included colors: white, black, red, green, blue, light blue, yellow, cyan, magenta, orange, purple, pink, brown, gray, light gray, dark gray.

### Enums

#### TLMouseBtn

Contains all mouse buttons. Used in input functions.

- TL_MOUSE_BTN_LEFT
- TL_MOUSE_BTN_RIGHT
- ...

#### TLKey

Contains all keyboard keys. Used in input functions.

- TL_KEY_A
- TL_KEY_B
- ...