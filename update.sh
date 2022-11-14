#!/usr/bin/bash
echo "Getting versions..."
version_web=$(curl https://raw.githubusercontent.com/Myshiak/strlib.h/main/strlib.h | grep STRLIB_VERSION | awk '{ print $3 }')
vwlen=$(expr length "$version_web")
version_web=${version_web:1:$((vwlen-2))}
version_file=$(cat strlib.h | grep STRLIB_VERSION | awk '{ print $3 }')
vflen=$(expr length "$version_file")
version_file=${version_file:1:$((vflen-2))}
if [[ $version_file == $version_web ]]
then
    echo "Nothing to update"
else
    {
        cd ..
        rm -rf strlib.h
        git clone https://github.com/Myshiak/strlib.h.git && {
			cd strlib.h
			chmod +x update.sh
			fprefix="/usr/local"
			[[ "$(uname -o)" == Android ]] && fprefix=$PREFIX
			if [[ -f $fprefix/lib/libstrlib.a ]] && [[ -f $fprefix/include/strlib.h ]]
			then
				sudo make uninstall
				sudo make install
			fi
			version_file=$(cat strlib.h | grep STRLIB_VERSION | awk '{ print $3 }')
			vflen=$(expr length "$version_file")
			version_file=${version_file:1:$((vflen-2))}
		}
    } && echo "Successfully updated to version $version_file"
fi
