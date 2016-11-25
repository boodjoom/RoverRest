#!/bin/sh
cd 3rdparty/QtWebApp
qmake QtWebApp.pro
make
sudo make install
cd ../..
qmake RoverRest.pro
make
sudo make install
