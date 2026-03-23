MAKE_FLAGS += -j

BIN_NAME := arcade

SRC := $(wildcard src/*.cpp)
SRC += $(wildcard src/*/*.cpp)

SRC_SFML := $(wildcard src/Graphic/SFML/*.cpp)

BUILD_DIR := .build

CXXFLAGS += -Wall -Wextra -Werror=write-strings
CXXFLAGS += -Wno-unused-parameter -Wunused-result
CXXFLAGS += -Wp,-U_FORTIFY_SOURCE -Wcast-qual
CXXFLAGS += -Wformat=2 -Wshadow -fno-builtin -Wno-unused-command-line-argument 
CXXFLAGS += -Wstrict-aliasing=0 -Wunreachable-code
CXXFLAGS += -Wwrite-strings -Werror=format-nonliteral -Werror=return-type
CXXFLAGS += -std=c++20 -iquote src/Core -iquote src/Game -iquote src/Graphic

SFML_LDFLAGS += $(shell pkg-config --cflags --libs sfml-graphics sfml-window sfml-system)

include utils.mk

.PHONY: _start all
_start: all

CXX = clang++

# call mk-profile release, SRC, additional CFLAGS
define mk-profile

NAME_$(strip $1) := $4
OBJ_$(strip $1) := $$($(strip $2):%.cpp=$$(BUILD_DIR)/$(strip $1)/%.o)

$$(BUILD_DIR)/$(strip $1)/%.o: %.cpp
	@ mkdir -p $$(dir $$@)
	@ $$(COMPILE.cpp) $$(CXXFLAGS) $(strip $3) $$< -o $$@
	@ $$(LOG_TIME) "$$(C_GREEN) CC $$(C_PURPLE) $$(notdir $$@) $$(C_RESET)"

$$(NAME_$(strip $1)): $$(OBJ_$(strip $1))
	@ $$(LINK.cpp) $$(OBJ_$(strip $1)) $$(LDFLAGS) $$(LDLIBS) $(strip $3) -o $$@
	@ $$(LOG_TIME) "$$(C_BLUE) LD $$(C_PURPLE) $$(notdir $$@) $$(C_RESET)"
	@ $$(LOG_TIME) "$$(C_GREEN) OK  Compilation finished $$(C_RESET)"

endef

$(eval $(call mk-profile, core, SRC, , $(BIN_NAME)))
$(eval $(call mk-profile, sfml, SRC_SFML, $(SFML_LDFLAGS) -shared -fPIC, lib/arcade_sfml.so))
$(eval $(call mk-profile, debug, SRC, -D DEBUG_MODE -lasan -fanalyzer -g3, debug))
$(eval $(call mk-profile, test, SRC, , test))

core: $(NAME_core)

graphicals: $(NAME_sfml)

all: $(NAME_core) $(NAME_sfml)

tests: $(NAME_test)
	@ bash tests/run_all.sh

format:
	@ find ./ -name "*.cpp" -type f -exec clang-format -i {} ";"
	@ find ./ -name "*.hpp" -type f -exec clang-format -i {} ";"
	@ $(LOG_TIME) "$(C_BLUE) CF $(C_GREEN) Code formated  $(C_RESET)"

check_format:
	@ find ./ -name "*.cpp" -type f -exec clang-format --dry-run --Werror {} ";" 2>&1 | wc -m | grep 0 > /dev/null
	@ find ./ -name "*.hpp" -type f -exec clang-format --dry-run --Werror {} ";" 2>&1 | wc -m | grep 0 > /dev/null
	@ $(LOG_TIME) "$(C_BLUE) CF $(C_GREEN) Code formated  $(C_RESET)"

clean:
	@ $(RM) $(OBJ)
	@ $(LOG_TIME) "$(C_YELLOW) RM $(C_PURPLE) $(OBJ) $(C_RESET)"

fclean:
	@ $(RM) -r $(NAME_release) $(NAME_debug) $(BUILD_DIR)
	@ $(LOG_TIME) "$(C_YELLOW) RM $(C_PURPLE) $(NAME_release) $(NAME_debug) \
		$(C_RESET)"

.NOTPARALLEL: re
re:	fclean all

.PHONY: all clean fclean re

PREFIX ?=
BINDIR ?= $(PREFIX)/bin
