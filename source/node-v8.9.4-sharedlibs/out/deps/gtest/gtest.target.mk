# This file is generated by gyp; do not edit.

TOOLSET := target
TARGET := gtest
DEFS_Debug := \
	'-DDEBUG' \
	'-D_DEBUG' \
	'-DV8_ENABLE_CHECKS'

# Flags passed to all source files.
CFLAGS_Debug := \
	-pthread \
	-Wall \
	-Wextra \
	-Wno-unused-parameter \
	-m64 \
	-Wno-missing-field-initializers \
	-g \
	-O0

# Flags passed to only C files.
CFLAGS_C_Debug :=

# Flags passed to only C++ files.
CFLAGS_CC_Debug := \
	-fno-rtti \
	-fno-exceptions \
	-std=gnu++0x

INCS_Debug := \
	-I$(srcdir)/deps/gtest \
	-I$(srcdir)/deps/gtest/include

DEFS_Release :=

# Flags passed to all source files.
CFLAGS_Release := \
	-pthread \
	-Wall \
	-Wextra \
	-Wno-unused-parameter \
	-m64 \
	-Wno-missing-field-initializers \
	-O3 \
	-fno-omit-frame-pointer

# Flags passed to only C files.
CFLAGS_C_Release :=

# Flags passed to only C++ files.
CFLAGS_CC_Release := \
	-fno-rtti \
	-fno-exceptions \
	-std=gnu++0x

INCS_Release := \
	-I$(srcdir)/deps/gtest \
	-I$(srcdir)/deps/gtest/include

OBJS := \
	$(obj).target/$(TARGET)/deps/gtest/src/gtest-death-test.o \
	$(obj).target/$(TARGET)/deps/gtest/src/gtest-filepath.o \
	$(obj).target/$(TARGET)/deps/gtest/src/gtest-port.o \
	$(obj).target/$(TARGET)/deps/gtest/src/gtest-printers.o \
	$(obj).target/$(TARGET)/deps/gtest/src/gtest-test-part.o \
	$(obj).target/$(TARGET)/deps/gtest/src/gtest-typed-test.o \
	$(obj).target/$(TARGET)/deps/gtest/src/gtest.o \
	$(obj).target/$(TARGET)/deps/gtest/src/gtest_main.o

# Add to the list of files we specially track dependencies for.
all_deps += $(OBJS)

# CFLAGS et al overrides must be target-local.
# See "Target-specific Variable Values" in the GNU Make manual.
$(OBJS): TOOLSET := $(TOOLSET)
$(OBJS): GYP_CFLAGS := $(DEFS_$(BUILDTYPE)) $(INCS_$(BUILDTYPE))  $(CFLAGS_$(BUILDTYPE)) $(CFLAGS_C_$(BUILDTYPE))
$(OBJS): GYP_CXXFLAGS := $(DEFS_$(BUILDTYPE)) $(INCS_$(BUILDTYPE))  $(CFLAGS_$(BUILDTYPE)) $(CFLAGS_CC_$(BUILDTYPE))

# Suffix rules, putting all outputs into $(obj).

$(obj).$(TOOLSET)/$(TARGET)/%.o: $(srcdir)/%.cc FORCE_DO_CMD
	@$(call do_cmd,cxx,1)

# Try building from generated source, too.

$(obj).$(TOOLSET)/$(TARGET)/%.o: $(obj).$(TOOLSET)/%.cc FORCE_DO_CMD
	@$(call do_cmd,cxx,1)

$(obj).$(TOOLSET)/$(TARGET)/%.o: $(obj)/%.cc FORCE_DO_CMD
	@$(call do_cmd,cxx,1)

# End of this set of suffix rules
### Rules for final target.
LDFLAGS_Debug := \
	-pthread \
	-rdynamic \
	-m64

LDFLAGS_Release := \
	-pthread \
	-rdynamic \
	-m64

LIBS := \
	-lz \
	-lhttp_parser \
	-luv \
	-lcares \
	-lnghttp2 \
	-lcrypto \
	-lssl

$(obj).target/deps/gtest/libgtest.a: GYP_LDFLAGS := $(LDFLAGS_$(BUILDTYPE))
$(obj).target/deps/gtest/libgtest.a: LIBS := $(LIBS)
$(obj).target/deps/gtest/libgtest.a: TOOLSET := $(TOOLSET)
$(obj).target/deps/gtest/libgtest.a: $(OBJS) FORCE_DO_CMD
	$(call do_cmd,alink_thin)

all_deps += $(obj).target/deps/gtest/libgtest.a
# Add target alias
.PHONY: gtest
gtest: $(obj).target/deps/gtest/libgtest.a

# Add target alias to "all" target.
.PHONY: all
all: gtest

