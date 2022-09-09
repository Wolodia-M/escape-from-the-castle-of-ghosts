#!/bin/sh

#print installer text
echo "This installer unpack game and can install all required SDL2 components"
#check user input
echo "Press 2 to install SDL2 or 1 to skip this step"
read var
#if input = 2
if [ $var -gt 1 ]
then
#install sdl2
echo "You nedd to grant root because it install SDL2 and all other components"
sudo apt install libsdl2-dev libsdl2-2.0-0 -y;
sudo apt install libjpeg-dev libwebp-dev libtiff5-dev libsdl2-image-dev libsdl2-image-2.0-0 -y;
sudo apt install libmikmod-dev libfishsound1-dev libsmpeg-dev liboggz2-dev libflac-dev libfluidsynth-dev libsdl2-mixer-dev libsdl2-mixer-2.0-0 -y;
fi
#unpack game
tar -xvzf build_linux.tar.gz
mv builds/linux/data $(pwd)/
mv builds/linux/media $(pwd)/
mv builds/linux/escape-from-the-castle-of-ghosts $(pwd)/
mv builds/linux/uninstall.sh $(pwd)/
#remove archive
rm build_linux.tar.gz
rm -r builds
#end of installation
echo "Instalation complete"
rm -r install.sh