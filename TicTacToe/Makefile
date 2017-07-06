export OBJ_DIR  = obj
export SRC_PATH = `pwd`
export TARGET   = tictac
export CC       = gcc
export CPP      = g++

### Colored messages
export ECHO_ESCAPE=-e
export TEXT_FG_BLACK="\033[30m"
export TEXT_FG_RED="\033[31m"
export TEXT_FG_GREEN="\033[32m"
export TEXT_FG_ORANGE="\033[33m"
export TEXT_FG_BLUE="\033[34m"
export TEXT_FG_MAGENTA="\033[35m"
export TEXT_FG_CYAN="\033[36m"
export TEXT_FG_GRAY="\033[37m"
export TEXT_FG_DARK_GRAY="\033[30;1m"
export TEXT_FG_LIGHT_RED="\033[31;1m"
export TEXT_FG_LIGHT_GREEN="\033[32;1m"
export TEXT_FG_YELLOW="\033[33;1m"
export TEXT_FG_VIOLET="\033[34;1m"
export TEXT_FG_LIGHT_MAGENTA="\033[35;1m"
export TEXT_FG_LIGHT_CYAN="\033[36;1m"
export TEXT_FG_WHITE="\033[37;1m"
export TEXT_BG_BLACK="\033[40m"
export TEXT_BG_RED="\033[41m"
export TEXT_BG_GREEN="\033[42m"
export TEXT_BG_YELLOW="\033[43m"
export TEXT_BG_BLUE="\033[44m"
export TEXT_BG_MAGENTA="\033[45m"
export TEXT_BG_CYAN="\033[46m"
export TEXT_BG_GRAY="\033[47m"
export TEXT_NORM="\033[0m" # Back to normal text

C_SRCS = $(shell find $(SRC_PATH) -type f -name *.c -execdir test ! -f IGNORE ';' -print)
CPP_SRCS = $(shell find $(SRC_PATH) -type f -name *.cpp -execdir test ! -f IGNORE ';' -print)
INCLUDES = -I.
DEFINES  =
LIBS = -lc -lstdc++ -lm -ldl

all:	$(TARGET)

### Load dependecies
### ----------------
DEPS = $(wildcard $(OBJ_DIR)/*.d)
ifneq ($(strip $(DEPS)),)
include $(DEPS)
endif

### Compilation and dependecies generation.
### --------------------------------------

define COMPILE_C
@echo $(TEXT_BG_BLUE)$(TEXT_FG_BOLD_YELLOW)" C "$(TEXT_NORM)$(TEXT_FG_BOLD_CYAN)$< $(TEXT_NORM)
$(CO_SILENT)$(CC) -c -MD $(CFLAGS) $(if $(findstring 3rdparty,$(dir $<)),$(CFLAGS_3RD),) $(INCLUDES) $(DEFINES) -o $@ $<
endef

define COMPILE_CPP
@echo $(TEXT_BG_BLUE)$(TEXT_FG_BOLD_YELLOW)"C++"$(TEXT_NORM)$(TEXT_FG_BOLD_CYAN)$< $(TEXT_NORM)
$(CO_SILENT)$(CPP) -c -MD $(CPPFLAGS) $(if $(findstring 3rdparty,$(dir $<)),$(CFLAGS_3RD),) $(INCLUDES) $(DEFINES) -o $@ $<
endef

define DEPENDENCIES_C
@if [ ! -f $(@D)/$(<F:.c=.d) ]; then \
    sed 's/^$(@F):/$(@D)\/$(@F):/g' < $(<F:.c=.d) > $(@D)/$(<F:.c=.d); \
    rm -f $(<F:.c=.d); \
fi
endef

define DEPENDENCIES_CPP
@if [ ! -f $(@D)/$(<F:.cpp=.d) ]; then \
    sed 's/^$(@F):/$(@D)\/$(@F):/g' < $(<F:.cpp=.d) > $(@D)/$(<F:.cpp=.d); \
    rm -f $(<F:.cpp=.d); \
fi
endef

C_OBJS   = $(patsubst %.c,$(OBJ_DIR)/%.o,$(notdir $(C_SRCS)))
CPP_OBJS = $(patsubst %.cpp,$(OBJ_DIR)/%.o,$(notdir $(CPP_SRCS)))

.SECONDARY:	$(C_OBJS) $(CPP_OBJS)
.PHONY:	clean

### Target rules
### ------------

.ONESHELL:
$(OBJ_DIR)/%.o: %.cpp
		$(COMPILE_CPP)
		$(DEPENDENCIES_CPP)

$(OBJ_DIR)/%.o: %.c
		$(COMPILE_C)
		$(DEPENDENCIES_C)

$(TARGET): $(OBJ_DIR) $(C_OBJS) $(CPP_OBJS)
		@echo $(TEXT_BG_GREEN)$(TEXT_FG_BLACK)" A "$(TEXT_NORM)$(TEXT_FG_BOLD_GREEN)$@ $(TEXT_NORM)
		@rm -f $@
		$(CO_SILENT)$(CC) $(CFLAGS) $(DEFINES) -o $@ $(C_OBJS) $(CPP_OBJS) $(LIBS)

$(OBJ_DIR):
		$(CO_SILENT)mkdir $(OBJ_DIR)

clean:
		@echo $(TEXT_BG_RED)$(TEXT_FG_BOLD_WHITE)" Cleaning up... "$(TEXT_NORM)
		$(CO_SILENT)rm -fr $(OBJ_DIR)
		$(CO_SILENT)rm -f *~ *.d *.gdb core* *.so *.a $(TARGET)
