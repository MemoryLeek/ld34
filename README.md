# Ludum Dare #34 (Jam)
Go to http://www.ludumdare.com/compo/ludum-dare-34/?action=preview&uid=7989 for a full description of the game.

## Compiling the source

We're using the following libraries in the game:
- [SFML 2](http://www.sfml-dev.org/)
- [nlohmann/json](https://github.com/nlohmann/json) (included as a git submodule, no need to install)

Since we both used Qt Creator we went with the default .pro/qmake build system, this means that you have to have `qmake` installed to compile this, even though we didn't use Qt itself.

### Linux
	git clone --recursive https://github.com/MemoryLeek/ld34.git
	cd ld34
	qmake
	make

The compiled binary will be put in the bin directory. This should also be your working directory when starting the game.
