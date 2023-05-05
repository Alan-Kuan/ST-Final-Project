.PHONY: all clean

all: config build_code

build_code:
	meson compile -C build

config:
	[ ! -d "build/" ] && meson setup build || meson setup --reconfigure build

clean:
	rm -rf build
