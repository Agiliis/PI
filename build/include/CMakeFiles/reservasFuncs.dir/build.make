# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.31

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/agil/dev/Facool/PI/emprestimoDeSalas

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/agil/dev/Facool/PI/build

# Include any dependencies generated for this target.
include include/CMakeFiles/reservasFuncs.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include include/CMakeFiles/reservasFuncs.dir/compiler_depend.make

# Include the progress variables for this target.
include include/CMakeFiles/reservasFuncs.dir/progress.make

# Include the compile flags for this target's objects.
include include/CMakeFiles/reservasFuncs.dir/flags.make

include/CMakeFiles/reservasFuncs.dir/codegen:
.PHONY : include/CMakeFiles/reservasFuncs.dir/codegen

include/CMakeFiles/reservasFuncs.dir/reservasFuncs/reservasFuncs.c.o: include/CMakeFiles/reservasFuncs.dir/flags.make
include/CMakeFiles/reservasFuncs.dir/reservasFuncs/reservasFuncs.c.o: /home/agil/dev/Facool/PI/emprestimoDeSalas/include/reservasFuncs/reservasFuncs.c
include/CMakeFiles/reservasFuncs.dir/reservasFuncs/reservasFuncs.c.o: include/CMakeFiles/reservasFuncs.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/agil/dev/Facool/PI/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object include/CMakeFiles/reservasFuncs.dir/reservasFuncs/reservasFuncs.c.o"
	cd /home/agil/dev/Facool/PI/build/include && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT include/CMakeFiles/reservasFuncs.dir/reservasFuncs/reservasFuncs.c.o -MF CMakeFiles/reservasFuncs.dir/reservasFuncs/reservasFuncs.c.o.d -o CMakeFiles/reservasFuncs.dir/reservasFuncs/reservasFuncs.c.o -c /home/agil/dev/Facool/PI/emprestimoDeSalas/include/reservasFuncs/reservasFuncs.c

include/CMakeFiles/reservasFuncs.dir/reservasFuncs/reservasFuncs.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/reservasFuncs.dir/reservasFuncs/reservasFuncs.c.i"
	cd /home/agil/dev/Facool/PI/build/include && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/agil/dev/Facool/PI/emprestimoDeSalas/include/reservasFuncs/reservasFuncs.c > CMakeFiles/reservasFuncs.dir/reservasFuncs/reservasFuncs.c.i

include/CMakeFiles/reservasFuncs.dir/reservasFuncs/reservasFuncs.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/reservasFuncs.dir/reservasFuncs/reservasFuncs.c.s"
	cd /home/agil/dev/Facool/PI/build/include && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/agil/dev/Facool/PI/emprestimoDeSalas/include/reservasFuncs/reservasFuncs.c -o CMakeFiles/reservasFuncs.dir/reservasFuncs/reservasFuncs.c.s

# Object files for target reservasFuncs
reservasFuncs_OBJECTS = \
"CMakeFiles/reservasFuncs.dir/reservasFuncs/reservasFuncs.c.o"

# External object files for target reservasFuncs
reservasFuncs_EXTERNAL_OBJECTS =

include/libreservasFuncs.a: include/CMakeFiles/reservasFuncs.dir/reservasFuncs/reservasFuncs.c.o
include/libreservasFuncs.a: include/CMakeFiles/reservasFuncs.dir/build.make
include/libreservasFuncs.a: include/CMakeFiles/reservasFuncs.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/agil/dev/Facool/PI/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C static library libreservasFuncs.a"
	cd /home/agil/dev/Facool/PI/build/include && $(CMAKE_COMMAND) -P CMakeFiles/reservasFuncs.dir/cmake_clean_target.cmake
	cd /home/agil/dev/Facool/PI/build/include && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/reservasFuncs.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
include/CMakeFiles/reservasFuncs.dir/build: include/libreservasFuncs.a
.PHONY : include/CMakeFiles/reservasFuncs.dir/build

include/CMakeFiles/reservasFuncs.dir/clean:
	cd /home/agil/dev/Facool/PI/build/include && $(CMAKE_COMMAND) -P CMakeFiles/reservasFuncs.dir/cmake_clean.cmake
.PHONY : include/CMakeFiles/reservasFuncs.dir/clean

include/CMakeFiles/reservasFuncs.dir/depend:
	cd /home/agil/dev/Facool/PI/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/agil/dev/Facool/PI/emprestimoDeSalas /home/agil/dev/Facool/PI/emprestimoDeSalas/include /home/agil/dev/Facool/PI/build /home/agil/dev/Facool/PI/build/include /home/agil/dev/Facool/PI/build/include/CMakeFiles/reservasFuncs.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : include/CMakeFiles/reservasFuncs.dir/depend

