#!/bin/sh
###############################################################
#1. 根据proto文件生成.cc和.h文件 这里仅支持C++
#2. 说明：目录下面全部的*.proto文件都会生成相应的.cc和.h
#
# author      date         modify reason
# cuipf     2015-07-15     create
##############################################################

SRC_DIR=./
DST_DIR=../

if [ $# -eq 0 ]; then
	#C++
	protoc -I=$SRC_DIR --cpp_out=$DST_DIR $SRC_DIR/*.proto
else
	if [ "x$1" = "xjava"  ]; then
		mkdir -p $DST_DIR/java
		protoc -I=$SRC_DIR --java_out=$DST_DIR/java/ $SRC_DIR/*.proto
	elif [ "x$1" = "xpython" ]; then
		#PYTHON
		mkdir -p $DST_DIR/python
		protoc -I=$SRC_DIR --python_out=$DST_DIR/python/ $SRC_DIR/*.proto
	else
		#C++
		mkdir -p $DST_DIR/cpp
		protoc -I=$SRC_DIR --cpp_out=$DST_DIR/cpp/ $SRC_DIR/*.proto
	fi
fi

exit 0
