# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/lckfb/share/RK3566-libmali-gbm

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/lckfb/share/RK3566-libmali-gbm/build

# Include any dependencies generated for this target.
include CMakeFiles/gbm_es2_demo.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/gbm_es2_demo.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/gbm_es2_demo.dir/flags.make

CMakeFiles/gbm_es2_demo.dir/src/drm_device.c.o: CMakeFiles/gbm_es2_demo.dir/flags.make
CMakeFiles/gbm_es2_demo.dir/src/drm_device.c.o: ../src/drm_device.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lckfb/share/RK3566-libmali-gbm/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/gbm_es2_demo.dir/src/drm_device.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/gbm_es2_demo.dir/src/drm_device.c.o   -c /home/lckfb/share/RK3566-libmali-gbm/src/drm_device.c

CMakeFiles/gbm_es2_demo.dir/src/drm_device.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/gbm_es2_demo.dir/src/drm_device.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/lckfb/share/RK3566-libmali-gbm/src/drm_device.c > CMakeFiles/gbm_es2_demo.dir/src/drm_device.c.i

CMakeFiles/gbm_es2_demo.dir/src/drm_device.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/gbm_es2_demo.dir/src/drm_device.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/lckfb/share/RK3566-libmali-gbm/src/drm_device.c -o CMakeFiles/gbm_es2_demo.dir/src/drm_device.c.s

CMakeFiles/gbm_es2_demo.dir/src/egl_context.c.o: CMakeFiles/gbm_es2_demo.dir/flags.make
CMakeFiles/gbm_es2_demo.dir/src/egl_context.c.o: ../src/egl_context.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lckfb/share/RK3566-libmali-gbm/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/gbm_es2_demo.dir/src/egl_context.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/gbm_es2_demo.dir/src/egl_context.c.o   -c /home/lckfb/share/RK3566-libmali-gbm/src/egl_context.c

CMakeFiles/gbm_es2_demo.dir/src/egl_context.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/gbm_es2_demo.dir/src/egl_context.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/lckfb/share/RK3566-libmali-gbm/src/egl_context.c > CMakeFiles/gbm_es2_demo.dir/src/egl_context.c.i

CMakeFiles/gbm_es2_demo.dir/src/egl_context.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/gbm_es2_demo.dir/src/egl_context.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/lckfb/share/RK3566-libmali-gbm/src/egl_context.c -o CMakeFiles/gbm_es2_demo.dir/src/egl_context.c.s

CMakeFiles/gbm_es2_demo.dir/src/egl_stream_texture.c.o: CMakeFiles/gbm_es2_demo.dir/flags.make
CMakeFiles/gbm_es2_demo.dir/src/egl_stream_texture.c.o: ../src/egl_stream_texture.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lckfb/share/RK3566-libmali-gbm/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/gbm_es2_demo.dir/src/egl_stream_texture.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/gbm_es2_demo.dir/src/egl_stream_texture.c.o   -c /home/lckfb/share/RK3566-libmali-gbm/src/egl_stream_texture.c

CMakeFiles/gbm_es2_demo.dir/src/egl_stream_texture.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/gbm_es2_demo.dir/src/egl_stream_texture.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/lckfb/share/RK3566-libmali-gbm/src/egl_stream_texture.c > CMakeFiles/gbm_es2_demo.dir/src/egl_stream_texture.c.i

CMakeFiles/gbm_es2_demo.dir/src/egl_stream_texture.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/gbm_es2_demo.dir/src/egl_stream_texture.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/lckfb/share/RK3566-libmali-gbm/src/egl_stream_texture.c -o CMakeFiles/gbm_es2_demo.dir/src/egl_stream_texture.c.s

CMakeFiles/gbm_es2_demo.dir/src/gles_demo.c.o: CMakeFiles/gbm_es2_demo.dir/flags.make
CMakeFiles/gbm_es2_demo.dir/src/gles_demo.c.o: ../src/gles_demo.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lckfb/share/RK3566-libmali-gbm/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/gbm_es2_demo.dir/src/gles_demo.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/gbm_es2_demo.dir/src/gles_demo.c.o   -c /home/lckfb/share/RK3566-libmali-gbm/src/gles_demo.c

CMakeFiles/gbm_es2_demo.dir/src/gles_demo.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/gbm_es2_demo.dir/src/gles_demo.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/lckfb/share/RK3566-libmali-gbm/src/gles_demo.c > CMakeFiles/gbm_es2_demo.dir/src/gles_demo.c.i

CMakeFiles/gbm_es2_demo.dir/src/gles_demo.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/gbm_es2_demo.dir/src/gles_demo.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/lckfb/share/RK3566-libmali-gbm/src/gles_demo.c -o CMakeFiles/gbm_es2_demo.dir/src/gles_demo.c.s

CMakeFiles/gbm_es2_demo.dir/src/gles_demo/gles_camera.c.o: CMakeFiles/gbm_es2_demo.dir/flags.make
CMakeFiles/gbm_es2_demo.dir/src/gles_demo/gles_camera.c.o: ../src/gles_demo/gles_camera.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lckfb/share/RK3566-libmali-gbm/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object CMakeFiles/gbm_es2_demo.dir/src/gles_demo/gles_camera.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/gbm_es2_demo.dir/src/gles_demo/gles_camera.c.o   -c /home/lckfb/share/RK3566-libmali-gbm/src/gles_demo/gles_camera.c

CMakeFiles/gbm_es2_demo.dir/src/gles_demo/gles_camera.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/gbm_es2_demo.dir/src/gles_demo/gles_camera.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/lckfb/share/RK3566-libmali-gbm/src/gles_demo/gles_camera.c > CMakeFiles/gbm_es2_demo.dir/src/gles_demo/gles_camera.c.i

CMakeFiles/gbm_es2_demo.dir/src/gles_demo/gles_camera.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/gbm_es2_demo.dir/src/gles_demo/gles_camera.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/lckfb/share/RK3566-libmali-gbm/src/gles_demo/gles_camera.c -o CMakeFiles/gbm_es2_demo.dir/src/gles_demo/gles_camera.c.s

CMakeFiles/gbm_es2_demo.dir/src/gles_demo/gles_cube.c.o: CMakeFiles/gbm_es2_demo.dir/flags.make
CMakeFiles/gbm_es2_demo.dir/src/gles_demo/gles_cube.c.o: ../src/gles_demo/gles_cube.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lckfb/share/RK3566-libmali-gbm/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building C object CMakeFiles/gbm_es2_demo.dir/src/gles_demo/gles_cube.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/gbm_es2_demo.dir/src/gles_demo/gles_cube.c.o   -c /home/lckfb/share/RK3566-libmali-gbm/src/gles_demo/gles_cube.c

CMakeFiles/gbm_es2_demo.dir/src/gles_demo/gles_cube.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/gbm_es2_demo.dir/src/gles_demo/gles_cube.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/lckfb/share/RK3566-libmali-gbm/src/gles_demo/gles_cube.c > CMakeFiles/gbm_es2_demo.dir/src/gles_demo/gles_cube.c.i

CMakeFiles/gbm_es2_demo.dir/src/gles_demo/gles_cube.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/gbm_es2_demo.dir/src/gles_demo/gles_cube.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/lckfb/share/RK3566-libmali-gbm/src/gles_demo/gles_cube.c -o CMakeFiles/gbm_es2_demo.dir/src/gles_demo/gles_cube.c.s

CMakeFiles/gbm_es2_demo.dir/src/gles_demo/gles_triangle.c.o: CMakeFiles/gbm_es2_demo.dir/flags.make
CMakeFiles/gbm_es2_demo.dir/src/gles_demo/gles_triangle.c.o: ../src/gles_demo/gles_triangle.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lckfb/share/RK3566-libmali-gbm/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building C object CMakeFiles/gbm_es2_demo.dir/src/gles_demo/gles_triangle.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/gbm_es2_demo.dir/src/gles_demo/gles_triangle.c.o   -c /home/lckfb/share/RK3566-libmali-gbm/src/gles_demo/gles_triangle.c

CMakeFiles/gbm_es2_demo.dir/src/gles_demo/gles_triangle.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/gbm_es2_demo.dir/src/gles_demo/gles_triangle.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/lckfb/share/RK3566-libmali-gbm/src/gles_demo/gles_triangle.c > CMakeFiles/gbm_es2_demo.dir/src/gles_demo/gles_triangle.c.i

CMakeFiles/gbm_es2_demo.dir/src/gles_demo/gles_triangle.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/gbm_es2_demo.dir/src/gles_demo/gles_triangle.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/lckfb/share/RK3566-libmali-gbm/src/gles_demo/gles_triangle.c -o CMakeFiles/gbm_es2_demo.dir/src/gles_demo/gles_triangle.c.s

CMakeFiles/gbm_es2_demo.dir/src/gles_util/esShader.c.o: CMakeFiles/gbm_es2_demo.dir/flags.make
CMakeFiles/gbm_es2_demo.dir/src/gles_util/esShader.c.o: ../src/gles_util/esShader.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lckfb/share/RK3566-libmali-gbm/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building C object CMakeFiles/gbm_es2_demo.dir/src/gles_util/esShader.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/gbm_es2_demo.dir/src/gles_util/esShader.c.o   -c /home/lckfb/share/RK3566-libmali-gbm/src/gles_util/esShader.c

CMakeFiles/gbm_es2_demo.dir/src/gles_util/esShader.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/gbm_es2_demo.dir/src/gles_util/esShader.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/lckfb/share/RK3566-libmali-gbm/src/gles_util/esShader.c > CMakeFiles/gbm_es2_demo.dir/src/gles_util/esShader.c.i

CMakeFiles/gbm_es2_demo.dir/src/gles_util/esShader.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/gbm_es2_demo.dir/src/gles_util/esShader.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/lckfb/share/RK3566-libmali-gbm/src/gles_util/esShader.c -o CMakeFiles/gbm_es2_demo.dir/src/gles_util/esShader.c.s

CMakeFiles/gbm_es2_demo.dir/src/gles_util/esShapes.c.o: CMakeFiles/gbm_es2_demo.dir/flags.make
CMakeFiles/gbm_es2_demo.dir/src/gles_util/esShapes.c.o: ../src/gles_util/esShapes.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lckfb/share/RK3566-libmali-gbm/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building C object CMakeFiles/gbm_es2_demo.dir/src/gles_util/esShapes.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/gbm_es2_demo.dir/src/gles_util/esShapes.c.o   -c /home/lckfb/share/RK3566-libmali-gbm/src/gles_util/esShapes.c

CMakeFiles/gbm_es2_demo.dir/src/gles_util/esShapes.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/gbm_es2_demo.dir/src/gles_util/esShapes.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/lckfb/share/RK3566-libmali-gbm/src/gles_util/esShapes.c > CMakeFiles/gbm_es2_demo.dir/src/gles_util/esShapes.c.i

CMakeFiles/gbm_es2_demo.dir/src/gles_util/esShapes.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/gbm_es2_demo.dir/src/gles_util/esShapes.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/lckfb/share/RK3566-libmali-gbm/src/gles_util/esShapes.c -o CMakeFiles/gbm_es2_demo.dir/src/gles_util/esShapes.c.s

CMakeFiles/gbm_es2_demo.dir/src/gles_util/esTransform.c.o: CMakeFiles/gbm_es2_demo.dir/flags.make
CMakeFiles/gbm_es2_demo.dir/src/gles_util/esTransform.c.o: ../src/gles_util/esTransform.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lckfb/share/RK3566-libmali-gbm/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building C object CMakeFiles/gbm_es2_demo.dir/src/gles_util/esTransform.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/gbm_es2_demo.dir/src/gles_util/esTransform.c.o   -c /home/lckfb/share/RK3566-libmali-gbm/src/gles_util/esTransform.c

CMakeFiles/gbm_es2_demo.dir/src/gles_util/esTransform.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/gbm_es2_demo.dir/src/gles_util/esTransform.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/lckfb/share/RK3566-libmali-gbm/src/gles_util/esTransform.c > CMakeFiles/gbm_es2_demo.dir/src/gles_util/esTransform.c.i

CMakeFiles/gbm_es2_demo.dir/src/gles_util/esTransform.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/gbm_es2_demo.dir/src/gles_util/esTransform.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/lckfb/share/RK3566-libmali-gbm/src/gles_util/esTransform.c -o CMakeFiles/gbm_es2_demo.dir/src/gles_util/esTransform.c.s

CMakeFiles/gbm_es2_demo.dir/src/gles_util/esUtil.c.o: CMakeFiles/gbm_es2_demo.dir/flags.make
CMakeFiles/gbm_es2_demo.dir/src/gles_util/esUtil.c.o: ../src/gles_util/esUtil.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lckfb/share/RK3566-libmali-gbm/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building C object CMakeFiles/gbm_es2_demo.dir/src/gles_util/esUtil.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/gbm_es2_demo.dir/src/gles_util/esUtil.c.o   -c /home/lckfb/share/RK3566-libmali-gbm/src/gles_util/esUtil.c

CMakeFiles/gbm_es2_demo.dir/src/gles_util/esUtil.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/gbm_es2_demo.dir/src/gles_util/esUtil.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/lckfb/share/RK3566-libmali-gbm/src/gles_util/esUtil.c > CMakeFiles/gbm_es2_demo.dir/src/gles_util/esUtil.c.i

CMakeFiles/gbm_es2_demo.dir/src/gles_util/esUtil.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/gbm_es2_demo.dir/src/gles_util/esUtil.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/lckfb/share/RK3566-libmali-gbm/src/gles_util/esUtil.c -o CMakeFiles/gbm_es2_demo.dir/src/gles_util/esUtil.c.s

CMakeFiles/gbm_es2_demo.dir/src/usb_camera.c.o: CMakeFiles/gbm_es2_demo.dir/flags.make
CMakeFiles/gbm_es2_demo.dir/src/usb_camera.c.o: ../src/usb_camera.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lckfb/share/RK3566-libmali-gbm/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Building C object CMakeFiles/gbm_es2_demo.dir/src/usb_camera.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/gbm_es2_demo.dir/src/usb_camera.c.o   -c /home/lckfb/share/RK3566-libmali-gbm/src/usb_camera.c

CMakeFiles/gbm_es2_demo.dir/src/usb_camera.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/gbm_es2_demo.dir/src/usb_camera.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/lckfb/share/RK3566-libmali-gbm/src/usb_camera.c > CMakeFiles/gbm_es2_demo.dir/src/usb_camera.c.i

CMakeFiles/gbm_es2_demo.dir/src/usb_camera.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/gbm_es2_demo.dir/src/usb_camera.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/lckfb/share/RK3566-libmali-gbm/src/usb_camera.c -o CMakeFiles/gbm_es2_demo.dir/src/usb_camera.c.s

CMakeFiles/gbm_es2_demo.dir/main.c.o: CMakeFiles/gbm_es2_demo.dir/flags.make
CMakeFiles/gbm_es2_demo.dir/main.c.o: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lckfb/share/RK3566-libmali-gbm/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_13) "Building C object CMakeFiles/gbm_es2_demo.dir/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/gbm_es2_demo.dir/main.c.o   -c /home/lckfb/share/RK3566-libmali-gbm/main.c

CMakeFiles/gbm_es2_demo.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/gbm_es2_demo.dir/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/lckfb/share/RK3566-libmali-gbm/main.c > CMakeFiles/gbm_es2_demo.dir/main.c.i

CMakeFiles/gbm_es2_demo.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/gbm_es2_demo.dir/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/lckfb/share/RK3566-libmali-gbm/main.c -o CMakeFiles/gbm_es2_demo.dir/main.c.s

# Object files for target gbm_es2_demo
gbm_es2_demo_OBJECTS = \
"CMakeFiles/gbm_es2_demo.dir/src/drm_device.c.o" \
"CMakeFiles/gbm_es2_demo.dir/src/egl_context.c.o" \
"CMakeFiles/gbm_es2_demo.dir/src/egl_stream_texture.c.o" \
"CMakeFiles/gbm_es2_demo.dir/src/gles_demo.c.o" \
"CMakeFiles/gbm_es2_demo.dir/src/gles_demo/gles_camera.c.o" \
"CMakeFiles/gbm_es2_demo.dir/src/gles_demo/gles_cube.c.o" \
"CMakeFiles/gbm_es2_demo.dir/src/gles_demo/gles_triangle.c.o" \
"CMakeFiles/gbm_es2_demo.dir/src/gles_util/esShader.c.o" \
"CMakeFiles/gbm_es2_demo.dir/src/gles_util/esShapes.c.o" \
"CMakeFiles/gbm_es2_demo.dir/src/gles_util/esTransform.c.o" \
"CMakeFiles/gbm_es2_demo.dir/src/gles_util/esUtil.c.o" \
"CMakeFiles/gbm_es2_demo.dir/src/usb_camera.c.o" \
"CMakeFiles/gbm_es2_demo.dir/main.c.o"

# External object files for target gbm_es2_demo
gbm_es2_demo_EXTERNAL_OBJECTS =

../bin/gbm_es2_demo: CMakeFiles/gbm_es2_demo.dir/src/drm_device.c.o
../bin/gbm_es2_demo: CMakeFiles/gbm_es2_demo.dir/src/egl_context.c.o
../bin/gbm_es2_demo: CMakeFiles/gbm_es2_demo.dir/src/egl_stream_texture.c.o
../bin/gbm_es2_demo: CMakeFiles/gbm_es2_demo.dir/src/gles_demo.c.o
../bin/gbm_es2_demo: CMakeFiles/gbm_es2_demo.dir/src/gles_demo/gles_camera.c.o
../bin/gbm_es2_demo: CMakeFiles/gbm_es2_demo.dir/src/gles_demo/gles_cube.c.o
../bin/gbm_es2_demo: CMakeFiles/gbm_es2_demo.dir/src/gles_demo/gles_triangle.c.o
../bin/gbm_es2_demo: CMakeFiles/gbm_es2_demo.dir/src/gles_util/esShader.c.o
../bin/gbm_es2_demo: CMakeFiles/gbm_es2_demo.dir/src/gles_util/esShapes.c.o
../bin/gbm_es2_demo: CMakeFiles/gbm_es2_demo.dir/src/gles_util/esTransform.c.o
../bin/gbm_es2_demo: CMakeFiles/gbm_es2_demo.dir/src/gles_util/esUtil.c.o
../bin/gbm_es2_demo: CMakeFiles/gbm_es2_demo.dir/src/usb_camera.c.o
../bin/gbm_es2_demo: CMakeFiles/gbm_es2_demo.dir/main.c.o
../bin/gbm_es2_demo: CMakeFiles/gbm_es2_demo.dir/build.make
../bin/gbm_es2_demo: CMakeFiles/gbm_es2_demo.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/lckfb/share/RK3566-libmali-gbm/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_14) "Linking C executable ../bin/gbm_es2_demo"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/gbm_es2_demo.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/gbm_es2_demo.dir/build: ../bin/gbm_es2_demo

.PHONY : CMakeFiles/gbm_es2_demo.dir/build

CMakeFiles/gbm_es2_demo.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/gbm_es2_demo.dir/cmake_clean.cmake
.PHONY : CMakeFiles/gbm_es2_demo.dir/clean

CMakeFiles/gbm_es2_demo.dir/depend:
	cd /home/lckfb/share/RK3566-libmali-gbm/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/lckfb/share/RK3566-libmali-gbm /home/lckfb/share/RK3566-libmali-gbm /home/lckfb/share/RK3566-libmali-gbm/build /home/lckfb/share/RK3566-libmali-gbm/build /home/lckfb/share/RK3566-libmali-gbm/build/CMakeFiles/gbm_es2_demo.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/gbm_es2_demo.dir/depend

