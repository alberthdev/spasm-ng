#!/bin/bash
getversion() {
	if [ -f version_base.h ];then
		VERSION=`cat version_base.h | head -n 1 | cut -f3 -d' ' | tr -d '"'`
	else
		VERSION="v0.1-alpha.1"
	fi
	if [ -d ".git" ]; then
		test -z "$FORCE_NO_GIT" && which git 2>&1 >/dev/null
		if [ "$?" = "0" ];then
			git describe --exact-match --tags HEAD 2>/dev/null >/dev/null
			if [ "$?" = "0" ];then
				echo "$VERSION"
			else
				echo "$VERSION.git"`date "+%Y%m%d"`
			fi
		else
			echo "$VERSION"
		fi
	else
		echo "$VERSION"
	fi
}

if [ "$1" = "set" ];then
	echo '#define SPASM_NG_VERSION "'`getversion`'"' > version.h
	which git 2>&1 >/dev/null && git describe --exact-match --tags HEAD 2>/dev/null
	if [ ! "$?" = "0" ];then
		echo '#define SPASM_NG_GITREV "'`git rev-parse --short HEAD`'"' >> version.h
	fi
elif [ "$1" = "dpkg" ];then
	getversion | sed -r 's/^.{1}//' | sed 's/[-]/~/' | sed 's/[.]git/+git/' | sed -e ':begin;s/[.]//2;t begin'
else
	getversion
	which git 2>&1 >/dev/null && git describe --exact-match --tags HEAD 2>/dev/null >/dev/null
	if [ ! "$?" = "0" ];then
		test -z "$FORCE_NO_GIT" && echo "Git revision: "`git rev-parse --short HEAD`
	fi
fi
