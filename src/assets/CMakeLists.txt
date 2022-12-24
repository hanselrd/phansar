ph_add_file_pass(
  NAME assets-shaders-vertex
  GROUPS assets assets-shaders
  PRE_COMMANDS
    "${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/assets/shaders"
  COMMANDS
    $<$<PLATFORM_ID:Windows>:"\"$<TARGET_FILE:shaderc> -i ${bgfx_SOURCE_DIR}/bgfx/src --type vertex --varyingdef ${CMAKE_CURRENT_SOURCE_DIR}/shaders/varying.def.sc -f @INPUT_FILE@ -o ${CMAKE_BINARY_DIR}/assets/shaders/@INPUT_STEM@-dx9.bin --platform windows -p vs_3_0 -O 3\"">
    $<$<PLATFORM_ID:Windows>:"\"$<TARGET_FILE:shaderc> -i ${bgfx_SOURCE_DIR}/bgfx/src --type vertex --varyingdef ${CMAKE_CURRENT_SOURCE_DIR}/shaders/varying.def.sc -f @INPUT_FILE@ -o ${CMAKE_BINARY_DIR}/assets/shaders/@INPUT_STEM@-dx11.bin --platform windows -p vs_5_0 -O 3\"">
    "$<TARGET_FILE:shaderc> -i ${bgfx_SOURCE_DIR}/bgfx/src --type vertex --varyingdef ${CMAKE_CURRENT_SOURCE_DIR}/shaders/varying.def.sc -f @INPUT_FILE@ -o ${CMAKE_BINARY_DIR}/assets/shaders/@INPUT_STEM@-metal.bin --platform osx -p metal"
    "$<TARGET_FILE:shaderc> -i ${bgfx_SOURCE_DIR}/bgfx/src --type vertex --varyingdef ${CMAKE_CURRENT_SOURCE_DIR}/shaders/varying.def.sc -f @INPUT_FILE@ -o ${CMAKE_BINARY_DIR}/assets/shaders/@INPUT_STEM@-glsl.bin --platform linux"
    "$<TARGET_FILE:shaderc> -i ${bgfx_SOURCE_DIR}/bgfx/src --type vertex --varyingdef ${CMAKE_CURRENT_SOURCE_DIR}/shaders/varying.def.sc -f @INPUT_FILE@ -o ${CMAKE_BINARY_DIR}/assets/shaders/@INPUT_STEM@-spirv.bin --platform linux -p spirv"
    "$<TARGET_FILE:shaderc> -i ${bgfx_SOURCE_DIR}/bgfx/src --type vertex --varyingdef ${CMAKE_CURRENT_SOURCE_DIR}/shaders/varying.def.sc -f @INPUT_FILE@ -o ${CMAKE_BINARY_DIR}/assets/shaders/@INPUT_STEM@-essl.bin --platform android"
  GLOBS "shaders/vs_*.sc"
  SEQUENTIAL)

ph_add_file_pass(
  NAME assets-shaders-fragment
  GROUPS assets assets-shaders
  PRE_COMMANDS
    "${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/assets/shaders"
  COMMANDS
    $<$<PLATFORM_ID:Windows>:"\"$<TARGET_FILE:shaderc> -i ${bgfx_SOURCE_DIR}/bgfx/src --type fragment --varyingdef ${CMAKE_CURRENT_SOURCE_DIR}/shaders/varying.def.sc -f @INPUT_FILE@ -o ${CMAKE_BINARY_DIR}/assets/shaders/@INPUT_STEM@-dx9.bin --platform windows -p ps_3_0 -O 3\"">
    $<$<PLATFORM_ID:Windows>:"\"$<TARGET_FILE:shaderc> -i ${bgfx_SOURCE_DIR}/bgfx/src --type fragment --varyingdef ${CMAKE_CURRENT_SOURCE_DIR}/shaders/varying.def.sc -f @INPUT_FILE@ -o ${CMAKE_BINARY_DIR}/assets/shaders/@INPUT_STEM@-dx11.bin --platform windows -p ps_5_0 -O 3\"">
    "$<TARGET_FILE:shaderc> -i ${bgfx_SOURCE_DIR}/bgfx/src --type fragment --varyingdef ${CMAKE_CURRENT_SOURCE_DIR}/shaders/varying.def.sc -f @INPUT_FILE@ -o ${CMAKE_BINARY_DIR}/assets/shaders/@INPUT_STEM@-metal.bin --platform osx -p metal"
    "$<TARGET_FILE:shaderc> -i ${bgfx_SOURCE_DIR}/bgfx/src --type fragment --varyingdef ${CMAKE_CURRENT_SOURCE_DIR}/shaders/varying.def.sc -f @INPUT_FILE@ -o ${CMAKE_BINARY_DIR}/assets/shaders/@INPUT_STEM@-glsl.bin --platform linux"
    "$<TARGET_FILE:shaderc> -i ${bgfx_SOURCE_DIR}/bgfx/src --type fragment --varyingdef ${CMAKE_CURRENT_SOURCE_DIR}/shaders/varying.def.sc -f @INPUT_FILE@ -o ${CMAKE_BINARY_DIR}/assets/shaders/@INPUT_STEM@-spirv.bin --platform linux -p spirv"
    "$<TARGET_FILE:shaderc> -i ${bgfx_SOURCE_DIR}/bgfx/src --type fragment --varyingdef ${CMAKE_CURRENT_SOURCE_DIR}/shaders/varying.def.sc -f @INPUT_FILE@ -o ${CMAKE_BINARY_DIR}/assets/shaders/@INPUT_STEM@-essl.bin --platform android"
  GLOBS "shaders/fs_*.sc"
  SEQUENTIAL)

ph_add_file_pass(
  NAME assets-shaders-compute
  GROUPS assets assets-shaders
  PRE_COMMANDS
    "${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/assets/shaders"
  COMMANDS
    $<$<PLATFORM_ID:Windows>:"\"$<TARGET_FILE:shaderc> -i ${bgfx_SOURCE_DIR}/bgfx/src --type compute --varyingdef ${CMAKE_CURRENT_SOURCE_DIR}/shaders/varying.def.sc -f @INPUT_FILE@ -o ${CMAKE_BINARY_DIR}/assets/shaders/@INPUT_STEM@-dx11.bin --platform windows -p cs_5_0 -O 1\"">
    "$<TARGET_FILE:shaderc> -i ${bgfx_SOURCE_DIR}/bgfx/src --type compute --varyingdef ${CMAKE_CURRENT_SOURCE_DIR}/shaders/varying.def.sc -f @INPUT_FILE@ -o ${CMAKE_BINARY_DIR}/assets/shaders/@INPUT_STEM@-metal.bin --platform osx -p metal"
    "$<TARGET_FILE:shaderc> -i ${bgfx_SOURCE_DIR}/bgfx/src --type compute --varyingdef ${CMAKE_CURRENT_SOURCE_DIR}/shaders/varying.def.sc -f @INPUT_FILE@ -o ${CMAKE_BINARY_DIR}/assets/shaders/@INPUT_STEM@-glsl.bin --platform linux -p 430"
    "$<TARGET_FILE:shaderc> -i ${bgfx_SOURCE_DIR}/bgfx/src --type compute --varyingdef ${CMAKE_CURRENT_SOURCE_DIR}/shaders/varying.def.sc -f @INPUT_FILE@ -o ${CMAKE_BINARY_DIR}/assets/shaders/@INPUT_STEM@-spirv.bin --platform linux -p spirv"
    "$<TARGET_FILE:shaderc> -i ${bgfx_SOURCE_DIR}/bgfx/src --type compute --varyingdef ${CMAKE_CURRENT_SOURCE_DIR}/shaders/varying.def.sc -f @INPUT_FILE@ -o ${CMAKE_BINARY_DIR}/assets/shaders/@INPUT_STEM@-essl.bin --platform android"
  GLOBS "shaders/cs_*.sc"
  SEQUENTIAL)

foreach(
  asset_type
  "fonts"
  "maps"
  "models"
  "scripts"
  "textures"
  "tilesets")
  ph_add_file_pass(
    NAME assets-${asset_type}
    GROUPS assets
    PRE_COMMANDS
      "${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/assets/${asset_type}"
    COMMANDS
      "${CMAKE_COMMAND} -E copy_if_different @INPUT_FILE@ ${CMAKE_BINARY_DIR}/assets/${asset_type}/@INPUT_FILENAME@"
    GLOBS "${asset_type}/*")
endforeach()

install(DIRECTORY ${CMAKE_BINARY_DIR}/assets DESTINATION share)
