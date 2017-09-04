INCLUDE_DIRS += $(SOURCE_PATH)/platform/wiring
INCLUDE_DIRS += $(SOURCE_PATH)/platform/spark

ifeq ($(BOOST_ROOT),)
$(error BOOST_ROOT not set. Download boost and add BOOST_ROOT to your environment variables.)
endif
CFLAGS += -I$(BOOST_ROOT)

CPPFLAGS += -std=gnu++14

CSRC += $(call target_files,app/msgpack,*.c)
CPPSRC += $(call target_files,app/msgpack,*.cpp)

CEXCLUDES += $(call target_files,app/msgpack/test,*.c)
CPPEXCLUDES += $(call target_files,app/msgpack/test,*.cpp)

CSRC := $(filter-out $(CEXCLUDES),$(CSRC))
CPPSRC := $(filter-out $(CPPEXCLUDES),$(CPPSRC))  