# Linux-Cuts
A simple shortcut manager for unix systems.

## Install
To install Linux-Cuts download the .zip file and extract it, inside you should see four files: main.c, icon.png, makefile, and shortcut.xml. If ANY of the files are missing redownload the zip file (If they are not included in the zip on your second download please submit a bug report via Issuses tab). After you extacted the files, open a terminal in the folder and run the command `sudo apt install make` after that run `sudo make pkg` and `sudo make install`. After running the command search for a app called "Linux Cuts" (you might need to restart). If you get a error follow the directions in the Errors section.

## Errors
If you get ANY errors make sure that you ran `sudo make pkg` and have installed make by running `sudo apt install make`. If you get any errors after running `sudo make pkg` make sure you downloaded all the files: main.c, icon.png, makefile, and shortcut.xml. If any of the files are missing please redownload the zip file. If you encounter any internal errors please submit error report via Issues tab.

## Uninstall
To uninstall Linux-Cuts you will need to open a terminal in the folder were you extracted the zip files to and run the command `sudo make clean`. Done, if you wish to install linux cuts again please follow the directions in the Install section.
