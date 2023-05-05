BUILD = build

.PHONY: all clean

all: config build_code

build_code:
	meson compile -C $(BUILD)

config:
	[ ! -d "$(BUILD)" ] && meson setup $(BUILD) || meson setup --reconfigure $(BUILD)

test:
	meson test -C $(BUILD)

clean:
	rm -rf $(BUILD)
