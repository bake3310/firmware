
$(MAKECMDGOALS) : run_make

.PHONY: run_make

unexport CC
unexport CXX

mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
current_dir := $(notdir $(patsubst %/,%,$(dir $(mkfile_path))))


PARTICLE_FIRMWARE?=firmware

APP ?= controller
BREWPIROOT = $(abspath $(current_dir)/../../..)
SPARKDIR = $(BREWPIROOT)/platform/spark
APPDIR=$(BREWPIROOT)/app/$(APP)
# include exported definitions for the app now
include $(BREWPIROOT)/app/$(APP)/env.mk
include $(PARTICLE_FIRMWARE)/build/platform-id.mk

run_make:
	@$(MAKE) -e -C $(PARTICLE_FIRMWARE)/main \
	APPDIR=$(APPDIR) \
	EXTRA_CFLAGS=-D_SYS_WAIT_H_ \
	TARGET_DIR=$(SPARKDIR)/target/$(APP)-$(PLATFORM) \
	BUILD_PATH_BASE=$(SPARKDIR)/target \
	BREWPIROOT=$(BREWPIROOT) \
	$(MAKEOVERRIDES) $(MAKECMDGOALS) 
