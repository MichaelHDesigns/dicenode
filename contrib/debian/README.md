
Debian
====================
This directory contains files used to package dicenoded/dicenode-qt
for Debian-based Linux systems. If you compile dicenoded/dicenode-qt yourself, there are some useful files here.

## dicenode: URI support ##


dicenode-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install dicenode-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your dicenodeqt binary to `/usr/bin`
and the `../../share/pixmaps/dicenode128.png` to `/usr/share/pixmaps`

dicenode-qt.protocol (KDE)

