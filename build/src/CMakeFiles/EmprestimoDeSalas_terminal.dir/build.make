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
include src/CMakeFiles/EmprestimoDeSalas_terminal.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include src/CMakeFiles/EmprestimoDeSalas_terminal.dir/compiler_depend.make

# Include the progress variables for this target.
include src/CMakeFiles/EmprestimoDeSalas_terminal.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/EmprestimoDeSalas_terminal.dir/flags.make

src/CMakeFiles/EmprestimoDeSalas_terminal.dir/codegen:
.PHONY : src/CMakeFiles/EmprestimoDeSalas_terminal.dir/codegen

src/CMakeFiles/EmprestimoDeSalas_terminal.dir/main.c.o: src/CMakeFiles/EmprestimoDeSalas_terminal.dir/flags.make
src/CMakeFiles/EmprestimoDeSalas_terminal.dir/main.c.o: /home/agil/dev/Facool/PI/emprestimoDeSalas/src/main.c
src/CMakeFiles/EmprestimoDeSalas_terminal.dir/main.c.o: src/CMakeFiles/EmprestimoDeSalas_terminal.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/agil/dev/Facool/PI/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object src/CMakeFiles/EmprestimoDeSalas_terminal.dir/main.c.o"
	cd /home/agil/dev/Facool/PI/build/src && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT src/CMakeFiles/EmprestimoDeSalas_terminal.dir/main.c.o -MF CMakeFiles/EmprestimoDeSalas_terminal.dir/main.c.o.d -o CMakeFiles/EmprestimoDeSalas_terminal.dir/main.c.o -c /home/agil/dev/Facool/PI/emprestimoDeSalas/src/main.c

src/CMakeFiles/EmprestimoDeSalas_terminal.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/EmprestimoDeSalas_terminal.dir/main.c.i"
	cd /home/agil/dev/Facool/PI/build/src && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/agil/dev/Facool/PI/emprestimoDeSalas/src/main.c > CMakeFiles/EmprestimoDeSalas_terminal.dir/main.c.i

src/CMakeFiles/EmprestimoDeSalas_terminal.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/EmprestimoDeSalas_terminal.dir/main.c.s"
	cd /home/agil/dev/Facool/PI/build/src && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/agil/dev/Facool/PI/emprestimoDeSalas/src/main.c -o CMakeFiles/EmprestimoDeSalas_terminal.dir/main.c.s

# Object files for target EmprestimoDeSalas_terminal
EmprestimoDeSalas_terminal_OBJECTS = \
"CMakeFiles/EmprestimoDeSalas_terminal.dir/main.c.o"

# External object files for target EmprestimoDeSalas_terminal
EmprestimoDeSalas_terminal_EXTERNAL_OBJECTS =

src/EmprestimoDeSalas_terminal: src/CMakeFiles/EmprestimoDeSalas_terminal.dir/main.c.o
src/EmprestimoDeSalas_terminal: src/CMakeFiles/EmprestimoDeSalas_terminal.dir/build.make
src/EmprestimoDeSalas_terminal: src/CMakeFiles/EmprestimoDeSalas_terminal.dir/compiler_depend.ts
src/EmprestimoDeSalas_terminal: include/liblimparTela.a
src/EmprestimoDeSalas_terminal: include/libloginFuncs.a
src/EmprestimoDeSalas_terminal: include/libreservasFuncs.a
src/EmprestimoDeSalas_terminal: include/liblimparTela.a
src/EmprestimoDeSalas_terminal: src/CMakeFiles/EmprestimoDeSalas_terminal.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/agil/dev/Facool/PI/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable EmprestimoDeSalas_terminal"
	cd /home/agil/dev/Facool/PI/build/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/EmprestimoDeSalas_terminal.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/EmprestimoDeSalas_terminal.dir/build: src/EmprestimoDeSalas_terminal
.PHONY : src/CMakeFiles/EmprestimoDeSalas_terminal.dir/build

src/CMakeFiles/EmprestimoDeSalas_terminal.dir/clean:
	cd /home/agil/dev/Facool/PI/build/src && $(CMAKE_COMMAND) -P CMakeFiles/EmprestimoDeSalas_terminal.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/EmprestimoDeSalas_terminal.dir/clean

src/CMakeFiles/EmprestimoDeSalas_terminal.dir/depend:
	cd /home/agil/dev/Facool/PI/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/agil/dev/Facool/PI/emprestimoDeSalas /home/agil/dev/Facool/PI/emprestimoDeSalas/src /home/agil/dev/Facool/PI/build /home/agil/dev/Facool/PI/build/src /home/agil/dev/Facool/PI/build/src/CMakeFiles/EmprestimoDeSalas_terminal.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : src/CMakeFiles/EmprestimoDeSalas_terminal.dir/depend

