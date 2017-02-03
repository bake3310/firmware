# here_files is a non-recursive file search. target_files is recursive.
here_files = $(patsubst $(SOURCE_PATH)/%,%,$(wildcard $(SOURCE_PATH)/$1/$2))

INCLUDE_DIRS += $(SOURCE_PATH)/app/rs485bridge
INCLUDE_DIRS += $(SOURCE_PATH)/lib/inc
INCLUDE_DIRS += $(SOURCE_PATH)/app/fallback
INCLUDE_DIRS += $(SOURCE_PATH)/platform/wiring
INCLUDE_DIRS += $(SOURCE_PATH)/platform/spark
INCLUDE_DIRS += $(SOURCE_PATH)/platform/spark/modules
INCLUDE_DIRS += $(SOURCE_PATH)/platform/spark/modules/OneWire
INCLUDE_DIRS += $(SOURCE_PATH)/platform/spark/modules/Ticks
INCLUDE_DIRS += $(SOURCE_PATH)/platform/spark/modules/RS485
INCLUDE_DIRS += $(SOURCE_PATH)/app

CSRC += $(call target_files,app/rs485bridge,*.c)
CPPSRC += $(call target_files,app/rs485bridge,*.cpp)

# CSRC += $(call target_files,lib/src,*.c)
# CPPSRC += $(call target_files,lib/src,*.cpp)

# CSRC += $(call target_files,platform/wiring/,*.c)
# CPPSRC += $(call target_files,platform/wiring/,*.cpp)

CPPSRC += platform/spark/modules/Board.cpp
CPPSRC += platform/spark/modules/RS485/RS485.cpp
CPPSRC += platform/wiring/TicksWiring.cpp

ifeq ($(BOOST_ROOT),)
$(error BOOST_ROOT not set. Download boost and add BOOST_ROOT to your environment variables.)
endif
CFLAGS += -I$(BOOST_ROOT)

LIBS_DIR = $(SOURCE_PATH)/platform/spark/libs
include $(LIBS_DIR)/libs.mk

CFLAGS += -fdata-sections

GIT_VERSION = $(shell cd $(SOURCE_PATH); git describe --long)
$(info using $(GIT_VERSION) as build name)
CFLAGS += -DBUILD_NAME="$(GIT_VERSION)"

CFLAGS += -Wall 
CPPFLAGS += -Woverloaded-virtual

# the following warnings can help find opportunities for impromevent in virtual functions
# they are disabled in the default build, because the dependencies (particle firmware, flashee) have many violations 

# Warn when virtual functions are overriden without override/override final specifier (requires gcc 5.1)
# CPPFLAGS += -Wsuggest-override
# Warn when functions and classes can be marked final
# CPPFLAGS += -Wsuggest-final-types
# CPPFLAGS += -Wsuggest-final-methods

CSRC := $(filter-out $(CEXCLUDES),$(CSRC))
CPPSRC := $(filter-out $(CPPEXCLUDES),$(CPPSRC)) 

