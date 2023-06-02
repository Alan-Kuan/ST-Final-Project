BUILD = build

.PHONY: all build_code config test clean

all: build_code

build_code:
	meson compile -C $(BUILD)

config:
	[ ! -d "$(BUILD)" ] && meson setup $(BUILD) || meson setup --reconfigure $(BUILD)

test:
	meson test -C $(BUILD)

clean:
	meson compile -C $(BUILD) --clean
