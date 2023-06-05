BUILD = build
SETUP_FLAGS = -Db_sanitize=address -Db_lundef=false

.PHONY: all build_code config test clean

all: build_code

build_code:
	meson compile -C $(BUILD)

config:
	[ ! -d "$(BUILD)" ] && meson setup $(SETUP_FLAGS) $(BUILD) || meson setup --reconfigure $(SETUP_FLAGS) $(BUILD)

test:
	meson test -C $(BUILD)

clean:
	meson compile -C $(BUILD) --clean
