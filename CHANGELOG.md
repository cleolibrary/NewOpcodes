# CHANGELOG

## v2.5

### Features

- Update to latest plugin-sdk (old version used custom build from 2013-2014)
- Add automatic release publishing
- Update to Visual Studio 2022 and remove hardcoded file paths

### Fixes

- Fixed a potential string handling issue that could occur with long texture names.
- Fixed TXD lookup using the texture name instead of the TXD name.
- Fixed sprite draw commands using the wrong color
- Fixed alpha being applied to objects that aren't RenderWare atomics.
- Fixed a cleanup issue in TxdManager::CleanAll caused by validating the wrong TXD slot.
- Fixed 0D4F (SET_STRUCT_FIELD) writing garbage instead of the intended number value

## v2.0-2.1 - August 27, 2014

- disabled opcodes

```text
0D62: set_car 0@ remap_texture 1@
0D63: set_car 0@ color PRIMARY_COLOR RGB 255 255 255
0D67: set_audiostream 0@ position_time 30.0
0D68: 1@ = get_audiostream 0@ position_time
0D69: 1@ = set_audiostream 0@ effect AUDIOSTREAMEFFECT_ECHO priority 0
0D6A: remove_audiostream 0@ effect 1@
0D6B: set_audiostream_effect 0@ parameters_from_buf 1@
0D6C: get_audiostream_effect 0@ parameters_to_buf 1@
0D6D: reset_audiostream_effect 0@
0D6E: set_audiostream 0@ attribute AUDIOSTREAMATTR_PAN to -1.0
0D6F: 1@ = get_audiostream 0@ attribute AUDIOSTREAMATTR_PAN
0D70: set_3d_audiostream 0@ _3d_attributes_mode 3DAUDIOSTREAM3DMODE_NORMAL min -1.0 max -1.0 iangle -1 oangle -1 outvol -1.0
0D71: get_3d_audiostream 0@ _3d_attributes_mode_to 1@ min_to 2@ max_to 3@ iangle_to NULL oangle_to NULL outvol_to NULL
```

- added opcodes

```text
0D74: 1@ = component 0@ parent_component
0D75: 1@ = component 0@ num_objects
0D76: 1@ = component 0@ object 0
0D77: object_atomic 0@ hide 1
0D78: 2@ = get_object 0@ atomic_flag 1@
0D79: set_object %1d% atomic_flag %2d% state %3d%
0D7A: 1@ = get_object 0@ num_materials // IF and SET
0D7B: 1@ = get_object 0@ material 0 texture // IF and SET
0D7C: 0@ = load_texture_dds_from "image.dds" // IF and SET
0D7D: clean_loaded_texture 0@
0D7E: draw_sprite_with_texture 0@ at_cornerA 100.0 100.0 cornerB 300.0 300.0 color 255 255 255 255 angle 0.0
0D7F: draw_gradient_sprite_with_texture 0@ at_cornerA 100.0 100.0 cornerB 300.0 300.0 colors 255 255 255 255  255 255 255 255  255 255 255 255  255 255 255 255 angle 0.0
```
