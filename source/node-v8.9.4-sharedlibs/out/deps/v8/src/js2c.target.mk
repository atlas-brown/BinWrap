# This file is generated by gyp; do not edit.

TOOLSET := target
TARGET := js2c
### Rules for action "js2c":
quiet_cmd__bpjs_bpjs_MPK_node_node_v8_9_4_sharedlibs_deps_v8_src_v8_gyp_js2c_target_js2c = ACTION _bpjs_bpjs_MPK_node_node_v8_9_4_sharedlibs_deps_v8_src_v8_gyp_js2c_target_js2c $@
cmd__bpjs_bpjs_MPK_node_node_v8_9_4_sharedlibs_deps_v8_src_v8_gyp_js2c_target_js2c = LD_LIBRARY_PATH=$(builddir)/lib.host:$(builddir)/lib.target:$$LD_LIBRARY_PATH; export LD_LIBRARY_PATH; cd $(srcdir)/deps/v8/src; mkdir -p $(obj)/gen; python ../tools/js2c.py "$(obj)/gen/libraries.cc" CORE js/macros.py messages.h js/prologue.js js/max-min.js js/v8natives.js js/array.js js/string.js js/typedarray.js js/collection.js js/weak-collection.js js/messages.js js/templates.js js/spread.js js/proxy.js debug/mirrors.js debug/debug.js debug/liveedit.js js/intl.js

$(obj)/gen/libraries.cc: obj := $(abs_obj)
$(obj)/gen/libraries.cc: builddir := $(abs_builddir)
$(obj)/gen/libraries.cc: TOOLSET := $(TOOLSET)
$(obj)/gen/libraries.cc: $(srcdir)/deps/v8/tools/js2c.py $(srcdir)/deps/v8/src/js/macros.py $(srcdir)/deps/v8/src/messages.h $(srcdir)/deps/v8/src/js/prologue.js $(srcdir)/deps/v8/src/js/max-min.js $(srcdir)/deps/v8/src/js/v8natives.js $(srcdir)/deps/v8/src/js/array.js $(srcdir)/deps/v8/src/js/string.js $(srcdir)/deps/v8/src/js/typedarray.js $(srcdir)/deps/v8/src/js/collection.js $(srcdir)/deps/v8/src/js/weak-collection.js $(srcdir)/deps/v8/src/js/messages.js $(srcdir)/deps/v8/src/js/templates.js $(srcdir)/deps/v8/src/js/spread.js $(srcdir)/deps/v8/src/js/proxy.js $(srcdir)/deps/v8/src/debug/mirrors.js $(srcdir)/deps/v8/src/debug/debug.js $(srcdir)/deps/v8/src/debug/liveedit.js $(srcdir)/deps/v8/src/js/intl.js FORCE_DO_CMD
	$(call do_cmd,_bpjs_bpjs_MPK_node_node_v8_9_4_sharedlibs_deps_v8_src_v8_gyp_js2c_target_js2c)

all_deps += $(obj)/gen/libraries.cc
action__bpjs_bpjs_MPK_node_node_v8_9_4_sharedlibs_deps_v8_src_v8_gyp_js2c_target_js2c_outputs := $(obj)/gen/libraries.cc

### Rules for action "js2c_bin":
quiet_cmd__bpjs_bpjs_MPK_node_node_v8_9_4_sharedlibs_deps_v8_src_v8_gyp_js2c_target_js2c_bin = ACTION _bpjs_bpjs_MPK_node_node_v8_9_4_sharedlibs_deps_v8_src_v8_gyp_js2c_target_js2c_bin $@
cmd__bpjs_bpjs_MPK_node_node_v8_9_4_sharedlibs_deps_v8_src_v8_gyp_js2c_target_js2c_bin = LD_LIBRARY_PATH=$(builddir)/lib.host:$(builddir)/lib.target:$$LD_LIBRARY_PATH; export LD_LIBRARY_PATH; cd $(srcdir)/deps/v8/src; mkdir -p $(obj)/gen; python ../tools/js2c.py "$(obj)/gen/libraries.cc" CORE js/macros.py messages.h js/prologue.js js/max-min.js js/v8natives.js js/array.js js/string.js js/typedarray.js js/collection.js js/weak-collection.js js/messages.js js/templates.js js/spread.js js/proxy.js debug/mirrors.js debug/debug.js debug/liveedit.js js/intl.js --startup_blob "$(obj)/gen/libraries.bin" --nojs

$(obj)/gen/libraries.bin: obj := $(abs_obj)
$(obj)/gen/libraries.bin: builddir := $(abs_builddir)
$(obj)/gen/libraries.bin: TOOLSET := $(TOOLSET)
$(obj)/gen/libraries.bin: $(srcdir)/deps/v8/tools/js2c.py $(srcdir)/deps/v8/src/js/macros.py $(srcdir)/deps/v8/src/messages.h $(srcdir)/deps/v8/src/js/prologue.js $(srcdir)/deps/v8/src/js/max-min.js $(srcdir)/deps/v8/src/js/v8natives.js $(srcdir)/deps/v8/src/js/array.js $(srcdir)/deps/v8/src/js/string.js $(srcdir)/deps/v8/src/js/typedarray.js $(srcdir)/deps/v8/src/js/collection.js $(srcdir)/deps/v8/src/js/weak-collection.js $(srcdir)/deps/v8/src/js/messages.js $(srcdir)/deps/v8/src/js/templates.js $(srcdir)/deps/v8/src/js/spread.js $(srcdir)/deps/v8/src/js/proxy.js $(srcdir)/deps/v8/src/debug/mirrors.js $(srcdir)/deps/v8/src/debug/debug.js $(srcdir)/deps/v8/src/debug/liveedit.js $(srcdir)/deps/v8/src/js/intl.js FORCE_DO_CMD
	$(call do_cmd,_bpjs_bpjs_MPK_node_node_v8_9_4_sharedlibs_deps_v8_src_v8_gyp_js2c_target_js2c_bin)

all_deps += $(obj)/gen/libraries.bin
action__bpjs_bpjs_MPK_node_node_v8_9_4_sharedlibs_deps_v8_src_v8_gyp_js2c_target_js2c_bin_outputs := $(obj)/gen/libraries.bin

### Rules for action "js2c_extras":
quiet_cmd__bpjs_bpjs_MPK_node_node_v8_9_4_sharedlibs_deps_v8_src_v8_gyp_js2c_target_js2c_extras = ACTION _bpjs_bpjs_MPK_node_node_v8_9_4_sharedlibs_deps_v8_src_v8_gyp_js2c_target_js2c_extras $@
cmd__bpjs_bpjs_MPK_node_node_v8_9_4_sharedlibs_deps_v8_src_v8_gyp_js2c_target_js2c_extras = LD_LIBRARY_PATH=$(builddir)/lib.host:$(builddir)/lib.target:$$LD_LIBRARY_PATH; export LD_LIBRARY_PATH; cd $(srcdir)/deps/v8/src; mkdir -p $(obj)/gen; python ../tools/js2c.py "$(obj)/gen/extras-libraries.cc" EXTRAS

$(obj)/gen/extras-libraries.cc: obj := $(abs_obj)
$(obj)/gen/extras-libraries.cc: builddir := $(abs_builddir)
$(obj)/gen/extras-libraries.cc: TOOLSET := $(TOOLSET)
$(obj)/gen/extras-libraries.cc: $(srcdir)/deps/v8/tools/js2c.py FORCE_DO_CMD
	$(call do_cmd,_bpjs_bpjs_MPK_node_node_v8_9_4_sharedlibs_deps_v8_src_v8_gyp_js2c_target_js2c_extras)

all_deps += $(obj)/gen/extras-libraries.cc
action__bpjs_bpjs_MPK_node_node_v8_9_4_sharedlibs_deps_v8_src_v8_gyp_js2c_target_js2c_extras_outputs := $(obj)/gen/extras-libraries.cc

### Rules for action "js2c_extras_bin":
quiet_cmd__bpjs_bpjs_MPK_node_node_v8_9_4_sharedlibs_deps_v8_src_v8_gyp_js2c_target_js2c_extras_bin = ACTION _bpjs_bpjs_MPK_node_node_v8_9_4_sharedlibs_deps_v8_src_v8_gyp_js2c_target_js2c_extras_bin $@
cmd__bpjs_bpjs_MPK_node_node_v8_9_4_sharedlibs_deps_v8_src_v8_gyp_js2c_target_js2c_extras_bin = LD_LIBRARY_PATH=$(builddir)/lib.host:$(builddir)/lib.target:$$LD_LIBRARY_PATH; export LD_LIBRARY_PATH; cd $(srcdir)/deps/v8/src; mkdir -p $(obj)/gen; python ../tools/js2c.py "$(obj)/gen/extras-libraries.cc" EXTRAS --startup_blob "$(obj)/gen/libraries-extras.bin" --nojs

$(obj)/gen/libraries-extras.bin: obj := $(abs_obj)
$(obj)/gen/libraries-extras.bin: builddir := $(abs_builddir)
$(obj)/gen/libraries-extras.bin: TOOLSET := $(TOOLSET)
$(obj)/gen/libraries-extras.bin: $(srcdir)/deps/v8/tools/js2c.py FORCE_DO_CMD
	$(call do_cmd,_bpjs_bpjs_MPK_node_node_v8_9_4_sharedlibs_deps_v8_src_v8_gyp_js2c_target_js2c_extras_bin)

all_deps += $(obj)/gen/libraries-extras.bin
action__bpjs_bpjs_MPK_node_node_v8_9_4_sharedlibs_deps_v8_src_v8_gyp_js2c_target_js2c_extras_bin_outputs := $(obj)/gen/libraries-extras.bin

### Rules for action "js2c_experimental_extras":
quiet_cmd__bpjs_bpjs_MPK_node_node_v8_9_4_sharedlibs_deps_v8_src_v8_gyp_js2c_target_js2c_experimental_extras = ACTION _bpjs_bpjs_MPK_node_node_v8_9_4_sharedlibs_deps_v8_src_v8_gyp_js2c_target_js2c_experimental_extras $@
cmd__bpjs_bpjs_MPK_node_node_v8_9_4_sharedlibs_deps_v8_src_v8_gyp_js2c_target_js2c_experimental_extras = LD_LIBRARY_PATH=$(builddir)/lib.host:$(builddir)/lib.target:$$LD_LIBRARY_PATH; export LD_LIBRARY_PATH; cd $(srcdir)/deps/v8/src; mkdir -p $(obj)/gen; python ../tools/js2c.py "$(obj)/gen/experimental-extras-libraries.cc" EXPERIMENTAL_EXTRAS

$(obj)/gen/experimental-extras-libraries.cc: obj := $(abs_obj)
$(obj)/gen/experimental-extras-libraries.cc: builddir := $(abs_builddir)
$(obj)/gen/experimental-extras-libraries.cc: TOOLSET := $(TOOLSET)
$(obj)/gen/experimental-extras-libraries.cc: $(srcdir)/deps/v8/tools/js2c.py FORCE_DO_CMD
	$(call do_cmd,_bpjs_bpjs_MPK_node_node_v8_9_4_sharedlibs_deps_v8_src_v8_gyp_js2c_target_js2c_experimental_extras)

all_deps += $(obj)/gen/experimental-extras-libraries.cc
action__bpjs_bpjs_MPK_node_node_v8_9_4_sharedlibs_deps_v8_src_v8_gyp_js2c_target_js2c_experimental_extras_outputs := $(obj)/gen/experimental-extras-libraries.cc

### Rules for action "js2c_experimental_extras_bin":
quiet_cmd__bpjs_bpjs_MPK_node_node_v8_9_4_sharedlibs_deps_v8_src_v8_gyp_js2c_target_js2c_experimental_extras_bin = ACTION _bpjs_bpjs_MPK_node_node_v8_9_4_sharedlibs_deps_v8_src_v8_gyp_js2c_target_js2c_experimental_extras_bin $@
cmd__bpjs_bpjs_MPK_node_node_v8_9_4_sharedlibs_deps_v8_src_v8_gyp_js2c_target_js2c_experimental_extras_bin = LD_LIBRARY_PATH=$(builddir)/lib.host:$(builddir)/lib.target:$$LD_LIBRARY_PATH; export LD_LIBRARY_PATH; cd $(srcdir)/deps/v8/src; mkdir -p $(obj)/gen; python ../tools/js2c.py "$(obj)/gen/experimental-extras-libraries.cc" EXPERIMENTAL_EXTRAS --startup_blob "$(obj)/gen/libraries-experimental-extras.bin" --nojs

$(obj)/gen/libraries-experimental-extras.bin: obj := $(abs_obj)
$(obj)/gen/libraries-experimental-extras.bin: builddir := $(abs_builddir)
$(obj)/gen/libraries-experimental-extras.bin: TOOLSET := $(TOOLSET)
$(obj)/gen/libraries-experimental-extras.bin: $(srcdir)/deps/v8/tools/js2c.py FORCE_DO_CMD
	$(call do_cmd,_bpjs_bpjs_MPK_node_node_v8_9_4_sharedlibs_deps_v8_src_v8_gyp_js2c_target_js2c_experimental_extras_bin)

all_deps += $(obj)/gen/libraries-experimental-extras.bin
action__bpjs_bpjs_MPK_node_node_v8_9_4_sharedlibs_deps_v8_src_v8_gyp_js2c_target_js2c_experimental_extras_bin_outputs := $(obj)/gen/libraries-experimental-extras.bin


### Rules for final target.
# Build our special outputs first.
$(obj).target/deps/v8/src/js2c.stamp: | $(action__bpjs_bpjs_MPK_node_node_v8_9_4_sharedlibs_deps_v8_src_v8_gyp_js2c_target_js2c_outputs) $(action__bpjs_bpjs_MPK_node_node_v8_9_4_sharedlibs_deps_v8_src_v8_gyp_js2c_target_js2c_bin_outputs) $(action__bpjs_bpjs_MPK_node_node_v8_9_4_sharedlibs_deps_v8_src_v8_gyp_js2c_target_js2c_extras_outputs) $(action__bpjs_bpjs_MPK_node_node_v8_9_4_sharedlibs_deps_v8_src_v8_gyp_js2c_target_js2c_extras_bin_outputs) $(action__bpjs_bpjs_MPK_node_node_v8_9_4_sharedlibs_deps_v8_src_v8_gyp_js2c_target_js2c_experimental_extras_outputs) $(action__bpjs_bpjs_MPK_node_node_v8_9_4_sharedlibs_deps_v8_src_v8_gyp_js2c_target_js2c_experimental_extras_bin_outputs)

# Preserve order dependency of special output on deps.
$(action__bpjs_bpjs_MPK_node_node_v8_9_4_sharedlibs_deps_v8_src_v8_gyp_js2c_target_js2c_outputs) $(action__bpjs_bpjs_MPK_node_node_v8_9_4_sharedlibs_deps_v8_src_v8_gyp_js2c_target_js2c_bin_outputs) $(action__bpjs_bpjs_MPK_node_node_v8_9_4_sharedlibs_deps_v8_src_v8_gyp_js2c_target_js2c_extras_outputs) $(action__bpjs_bpjs_MPK_node_node_v8_9_4_sharedlibs_deps_v8_src_v8_gyp_js2c_target_js2c_extras_bin_outputs) $(action__bpjs_bpjs_MPK_node_node_v8_9_4_sharedlibs_deps_v8_src_v8_gyp_js2c_target_js2c_experimental_extras_outputs) $(action__bpjs_bpjs_MPK_node_node_v8_9_4_sharedlibs_deps_v8_src_v8_gyp_js2c_target_js2c_experimental_extras_bin_outputs): | 

$(obj).target/deps/v8/src/js2c.stamp: TOOLSET := $(TOOLSET)
$(obj).target/deps/v8/src/js2c.stamp:  FORCE_DO_CMD
	$(call do_cmd,touch)

all_deps += $(obj).target/deps/v8/src/js2c.stamp
# Add target alias
.PHONY: js2c
js2c: $(obj).target/deps/v8/src/js2c.stamp

# Add target alias to "all" target.
.PHONY: all
all: js2c
