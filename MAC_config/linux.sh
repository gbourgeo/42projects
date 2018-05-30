#/bin/bash 

cp /media/sf_42/MAC_config/.* .
cp -r /media/sf_42/MAC_config/usr_share_emacs_site-lisp/* /usr/share/emacs/site-lisp/.
apt-get install -y emacs gcc nasm gdb make build-essential dkms zsh git
sh /media/cdrom/VBoxLinuxAdditions.run
reboot

