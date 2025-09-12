@echo off
setlocal

REM Detect glslc path from VULKAN_SDK if available
if defined VULKAN_SDK (
    set "GLSLC=%VULKAN_SDK%\Bin\glslc.exe"
) else (
    echo [WARN] VULKAN_SDK not defined, using glslc from PATH.
    set "GLSLC=glslc.exe"
)

"%GLSLC%" shader.vert -o vert.spv
"%GLSLC%" shader.frag -o frag.spv
"%GLSLC%" shadow.vert -o shadow_vert.spv
"%GLSLC%" shadow.frag -o shadow_frag.spv

pause
