# Define the prefix to this directory.
# Note: The name must be unique within this build and should be
#       based on the root of the project
HAL_SRC_GCC_PATH = $(TARGET_HAL_PATH)/src/gcc

# if we are being compiled with platform as a dependency, then also include
# implementation headers.
ifneq (,$(findstring platform,$(DEPENDENCIES)))
INCLUDE_DIRS += $(HAL_SRC_GCC_PATH)
endif

ifneq (,$(findstring hal,$(MAKE_DEPENDENCIES)))

# additional libraries required by gcc build
ifeq ($(MAKE_OS),WINDOWS)
LIBS += boost_system-mt ws2_32 mswsock
LDFLAGS += -static
flavor=-mt
else
LIBS += boost_system
LDFLAGS += -lc
flavor=
endif
LIBS += boost_program_options$(flavor) boost_random$(flavor) boost_thread$(flavor)

LIB_DIRS += $(BOOST_ROOT)/stage/lib

# gcc HAL is different for test driver and test subject
ifeq "$(SPARK_TEST_DRIVER)" "1"
HAL_TEST_FLAVOR+=-driver
endif



endif



