# main file name
OBJECT = main.cpp engine.cpp engine/grid.cpp
# compiller flags
CFLAGS = -std=c++20
WCFLAGS = -std=c++20 -Ix86_64-w64-mingw32/include/SDL2
# linker flags
LFLAGS = `sdl2-config --cflags --libs` -lSDL2 -lSDL2_mixer -lSDL2_image
WLFLAGS = -static-libstdc++ -static-libgcc -lSDL2 -lSDL2_mixer -lSDL2_image
#path to directory with devlopment data of SDL2, SDL2_mixer, SDL2_image
SDLPATH = /home/wolodiam/developmentInC++/SDL2/x86_64-w64-mingw32/
#extended linker flags for windows
EXTWLFLAGS = -I$(SDLPATH)include/ -L$(SDLPATH)lib/
#extended compiler flags
EXTWCFLAGS =
# end flags
DFLAGS = -g
# executable name
APP_NAME = escape-from-the-castle-of-ghosts
# scripts
# build app for all platforms
all : $(OBJECT)
#	Build for linux and windows
	make build
	make build_win
#	Remove old builds
	rm -r builds/windows
	rm -r builds/linux
#	Make place for new builds
	mkdir builds/windows
	mkdir builds/linux
#	Move executables to corect places
	mv $(APP_NAME) builds/linux
#	Move data and media folder to builds folders
	cp -r media builds/linux
	cp -r data builds/linux
#	Make linux installer
#	Move install.sh and unsinstall.sh to linux build folder
	cp -r builddata/install.sh builds/linux
	cp -r builddata/uninstall.sh builds/linux
#	Make tar.gz of linux build
	tar -czf builds/linux/build_linux.tar.gz builds/linux/$(APP_NAME) builds/linux/data builds/linux/media builds/linux/uninstall.sh
#	Remove temporary files (leave only archive and install.sh)
	rm -r builds/linux/media
	rm -r builds/linux/data
	rm -r builds/linux/$(APP_NAME)
	rm -r builds/linux/uninstall.sh
#	Make windows installer
#	Make .zip of windows build
	cp builddata/install.txt $(PWD)/
	zip -r build_win.zip data media $(APP_NAME).exe install.txt
#	Remove temporary files (leave only archive)
	rm -r $(APP_NAME).exe
	rm -r install.txt
#	Move zip to correct directory
	mv build_win.zip builds/windows
# build and run app
dev_test : $(OBJECT)
	g++ $(OBJECT) $(CFLAGS) $(LFLAGS) -o $(APP_NAME)
	$(CURDIR)/$(APP_NAME)
build_test : $(OBJECT)
	make build
	make build_win
	make clear
#debug
debug : $(OBJECT)
	g++ $(OBJECT) $(CFLAGS) $(DFLAGS) $(LFLAGS) -o $(APP_NAME)
	gdb $(CURDIR)/$(APP_NAME)
# internal command, not use manually
build : $(OBJECT)
	g++ $(OBJECT) $(CFLAGS) $(LFLAGS) -o $(APP_NAME)
build_win : $(OBJECT)
	x86_64-w64-mingw32-g++ $(OBJECT) $(WCFLAGS) $(EXTWCFLAGS)  $(EXTWLFLAGS) $(WLFLAGS) -o $(APP_NAME)
# clean builded app
clear : $(OBJECT)
	rm $(CURDIR)/$(APP_NAME)
	rm $(CURDIR)/$(APP_NAME).exe
