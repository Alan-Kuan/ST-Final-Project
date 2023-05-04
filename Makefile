.PHONY: all clean

all: configure build_code

build_code:
	meson compile -C build

configure:
	[ ! -d "build/" ] && meson setup build || :

clean:
	rm -rf build
