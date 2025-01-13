#!/bin/bash
wid=$(gdbus call --session --dest org.gnome.Shell \
--object-path /org/gnome/Shell/Extensions/Windows \
--method org.gnome.Shell.Extensions.Windows.List |
grep -o -P '\"title\":\"core_temp\".*?\"id\":[[:digit:]]*' |
grep -o -P '(?<=\"id\":)[[:digit:]]*')
gdbus call --session --dest org.gnome.Shell \
--object-path /org/gnome/Shell/Extensions/Windows \
--method org.gnome.Shell.Extensions.Windows.Move ${wid} $1 $2  > /dev/null