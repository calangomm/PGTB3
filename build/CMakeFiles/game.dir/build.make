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
CMAKE_SOURCE_DIR = /home/isel/GIT/PGTB3

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/isel/GIT/PGTB3/build

# Include any dependencies generated for this target.
include CMakeFiles/game.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/game.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/game.dir/flags.make

CMakeFiles/game.dir/src/game_logic/game_logic.c.o: CMakeFiles/game.dir/flags.make
CMakeFiles/game.dir/src/game_logic/game_logic.c.o: ../src/game_logic/game_logic.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/isel/GIT/PGTB3/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/game.dir/src/game_logic/game_logic.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/game.dir/src/game_logic/game_logic.c.o   -c /home/isel/GIT/PGTB3/src/game_logic/game_logic.c

CMakeFiles/game.dir/src/game_logic/game_logic.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/game.dir/src/game_logic/game_logic.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/isel/GIT/PGTB3/src/game_logic/game_logic.c > CMakeFiles/game.dir/src/game_logic/game_logic.c.i

CMakeFiles/game.dir/src/game_logic/game_logic.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/game.dir/src/game_logic/game_logic.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/isel/GIT/PGTB3/src/game_logic/game_logic.c -o CMakeFiles/game.dir/src/game_logic/game_logic.c.s

CMakeFiles/game.dir/src/main.c.o: CMakeFiles/game.dir/flags.make
CMakeFiles/game.dir/src/main.c.o: ../src/main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/isel/GIT/PGTB3/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/game.dir/src/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/game.dir/src/main.c.o   -c /home/isel/GIT/PGTB3/src/main.c

CMakeFiles/game.dir/src/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/game.dir/src/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/isel/GIT/PGTB3/src/main.c > CMakeFiles/game.dir/src/main.c.i

CMakeFiles/game.dir/src/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/game.dir/src/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/isel/GIT/PGTB3/src/main.c -o CMakeFiles/game.dir/src/main.c.s

CMakeFiles/game.dir/src/ui/ui.c.o: CMakeFiles/game.dir/flags.make
CMakeFiles/game.dir/src/ui/ui.c.o: ../src/ui/ui.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/isel/GIT/PGTB3/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/game.dir/src/ui/ui.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/game.dir/src/ui/ui.c.o   -c /home/isel/GIT/PGTB3/src/ui/ui.c

CMakeFiles/game.dir/src/ui/ui.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/game.dir/src/ui/ui.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/isel/GIT/PGTB3/src/ui/ui.c > CMakeFiles/game.dir/src/ui/ui.c.i

CMakeFiles/game.dir/src/ui/ui.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/game.dir/src/ui/ui.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/isel/GIT/PGTB3/src/ui/ui.c -o CMakeFiles/game.dir/src/ui/ui.c.s

CMakeFiles/game.dir/src/utils/utils.c.o: CMakeFiles/game.dir/flags.make
CMakeFiles/game.dir/src/utils/utils.c.o: ../src/utils/utils.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/isel/GIT/PGTB3/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/game.dir/src/utils/utils.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/game.dir/src/utils/utils.c.o   -c /home/isel/GIT/PGTB3/src/utils/utils.c

CMakeFiles/game.dir/src/utils/utils.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/game.dir/src/utils/utils.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/isel/GIT/PGTB3/src/utils/utils.c > CMakeFiles/game.dir/src/utils/utils.c.i

CMakeFiles/game.dir/src/utils/utils.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/game.dir/src/utils/utils.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/isel/GIT/PGTB3/src/utils/utils.c -o CMakeFiles/game.dir/src/utils/utils.c.s

# Object files for target game
game_OBJECTS = \
"CMakeFiles/game.dir/src/game_logic/game_logic.c.o" \
"CMakeFiles/game.dir/src/main.c.o" \
"CMakeFiles/game.dir/src/ui/ui.c.o" \
"CMakeFiles/game.dir/src/utils/utils.c.o"

# External object files for target game
game_EXTERNAL_OBJECTS =

game: CMakeFiles/game.dir/src/game_logic/game_logic.c.o
game: CMakeFiles/game.dir/src/main.c.o
game: CMakeFiles/game.dir/src/ui/ui.c.o
game: CMakeFiles/game.dir/src/utils/utils.c.o
game: CMakeFiles/game.dir/build.make
game: /usr/lib/x86_64-linux-gnu/libSDL2.so
game: /usr/lib/x86_64-linux-gnu/libSDL2_ttf.so
game: /usr/lib/x86_64-linux-gnu/libSDL2_image.so
game: CMakeFiles/game.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/isel/GIT/PGTB3/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking C executable game"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/game.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/game.dir/build: game

.PHONY : CMakeFiles/game.dir/build

CMakeFiles/game.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/game.dir/cmake_clean.cmake
.PHONY : CMakeFiles/game.dir/clean

CMakeFiles/game.dir/depend:
	cd /home/isel/GIT/PGTB3/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/isel/GIT/PGTB3 /home/isel/GIT/PGTB3 /home/isel/GIT/PGTB3/build /home/isel/GIT/PGTB3/build /home/isel/GIT/PGTB3/build/CMakeFiles/game.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/game.dir/depend

