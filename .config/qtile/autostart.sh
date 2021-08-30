#! /bin/bash 
lxsession &
picom --experimental-backends --config ~/.picom.conf &
nitrogen --restore &
urxvtd -q -o -f &
/usr/bin/emacs --daemon &
volumeicon &
nm-applet &
