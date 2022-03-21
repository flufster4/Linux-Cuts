install:
	gcc main.c -o lc `pkg-config --cflags --libs gtk+-3.0`
	sudo touch /usr/share/applications/lc.desktop
	sudo echo "[Desktop Entry]" > /usr/share/applications/lc.desktop
	sudo echo "Exec=/usr/bin/lc %f" >> /usr/share/applications/lc.desktop
	sudo echo "TryExec=/usr/bin/lc" >> /usr/share/applications/lc.desktop
	sudo echo "Name=Linux Cuts Dev" >> /usr/share/applications/lc.desktop
	sudo echo "Terminal=false" >> /usr/share/applications/lc.desktop
	sudo echo "Type=Application" >> /usr/share/applications/lc.desktop
	sudo echo "MimeType=text/lnk;" >> /usr/share/applications/lc.desktop
	sudo echo "Icon=/usr/share/icons/lc.png" >> /usr/share/applications/lc.desktop
	sudo echo "shortcut/lnk=lc.desktop" >> /usr/share/applications/defaults.list
	
	sudo mv ./lc /usr/bin/lc
	sudo mv ./shortcut.xml /usr/share/mime/packages/shortcut.xml
	sudo mv ./icon.png /usr/share/icons/lc.png
	sudo update-mime-database /usr/share/mime
	
clean:
	sudo rm /usr/share/applications/lc.desktop
	sudo rm /usr/bin/lc
	sudo mv /usr/share/mime/packages/shortcut.xml ./shortcut.xml
	sudo mv /usr/share/icons/lc.png ./icon.png
	sudo update-mime-database /usr/share/mime
	
pkg:
	sudo apt-get install make
	sudo apt-get install libgtk-3-dev
