
Debian
====================
This directory contains files used to package instadexd/instadex-qt
for Debian-based Linux systems. If you compile instadexd/instadex-qt yourself, there are some useful files here.

## instadex: URI support ##


instadex-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install instadex-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your instadexqt binary to `/usr/bin`
and the `../../share/pixmaps/instadex128.png` to `/usr/share/pixmaps`

instadex-qt.protocol (KDE)

