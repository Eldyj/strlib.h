#!/usr/bin/bash
echo "Getting versions..."
version_web=$(curl https://raw.githubusercontent.com/Myshiak/strlib.h/main/strlib.h | grep STRLIB_VERSION | awk '{ print $3 }')
if [[ -z $version_web ]]
then
	echo "Updating failed: invalid version on github"
	exit 1
fi
vwlen=$(expr length "$version_web")
version_web=${version_web:1:$((vwlen-2))}
version_file=$(cat strlib.h | grep STRLIB_VERSION | awk '{ print $3 }')
if [[ -z $version_file ]]
then
	echo "Updating failed: invalid version in the file 'strlib.h'"
	exit 1
fi
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
			chmod +x Makefile
			trgos=$(uname -o)
			fprefix="/usr/local"
			sudo=sudo
			[[ "$trgos" == Android ]] && fprefix=$PREFIX && sudo=
			if [[ -f $fprefix/lib/libstrlib.a ]] && [[ -f $fprefix/include/strlib.h ]]
			then
				if [[ -f libstrlib.a ]] && [[ -f strlib.o ]]
				then
					clean=clean
				fi
				$sudo make $clean reinstall
			fi
			version_file=$(cat strlib.h | grep STRLIB_VERSION | awk '{ print $3 }')
			if [[ -n $version_file ]]
			then
				vflen=$(expr length "$version_file")
				version_file=${version_file:1:$((vflen-2))}
			else
				false
			fi
		}
    } && echo "Successfully updated to version $version_file"
fi
