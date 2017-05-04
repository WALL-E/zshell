#!/bin/bash

# install package
command -v wget > /dev/null|| yum install wget

if [ ! -d "./bin" ]; then
  mkdir bin
fi

cd bin
if [ ! -f "qshell" ]; then
  wget http://oerp142a4.bkt.clouddn.com/qshell
  chmod +x qshell
fi

if [ ! -f "zshell" ]; then
  wget http://oerp142a4.bkt.clouddn.com/zshell
  chmod +x zshell
fi
