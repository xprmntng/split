# What to name the target executable
target = split

# Where to look for source files
source_dir = ./src
# Where to look for header files
include_dir = ./include
# Where to place intermediary build artifacts
build_dir = ./build
# Where to place resulting executable
output_dir = ./bin

# Which compiler we'll used to build the project
compiler = g++
# Which C++ standard to target
cxx_standard = c++23
# Flags to pass the compiler when building intermediary artifacts (.o files)
compiler_flags = -I $(include_dir) -std=$(cxx_standard) -Wall -Wextra -MMD -MP

# Compile a list of paths to .cpp files
cxx_sources := $(shell find $(source_dir) -type f -name "*.cpp")
# Turn the list of paths to .cpp files into a list of paths to output files (.o)
# `%` acts as a wildcard
cxx_targets := $(cxx_sources:$(source_dir)/%.cpp=$(build_dir)/%.o)
# Turn the list of paths to .o files into a list of paths to dependency files (.d)
cxx_dependencies := $(cxx_targets:%.o=%.d)

all: $(output_dir)/$(target)

clean:
	@rm -rf $(build_dir)/* $(output_dir)/*

# Compile each .cpp file into a .o file. Creates directories if they don't already exist
# % - wildcard
# $@ - Output file path (item left of the colon)
# $< - Input file path (item right of the colon)
# $(@D) - Path to the parent directory of the output file
$(build_dir)/%.o: $(source_dir)/%.cpp
	@mkdir --parents $(@D)
	$(compiler) $(compiler_flags) -c $< -o $@

# Build the target executable by linking all of the compiled .o files
$(output_dir)/$(target): $(cxx_targets)
	@mkdir --parents $(@D)
	$(compiler) $(cxx_targets) -o $(output_dir)/$(target)

# Track dependency (.d) files, which will catch if a header file changes
-include $(cxx_dependencies)

# Prevent Make from getting confused if a target name conflicts with these
.PHONY: all clean
