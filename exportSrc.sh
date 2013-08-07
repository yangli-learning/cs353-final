#!/bin/sh

# export  source 
find . ! -print | egrep '~$|\._|\#*\#|.bak$' |xargs rm -f
cd ..
rm -rf createVirtualNav.tar
tar -cvzf createVirtualNav.tar createVirtualNav  --exclude "*.svn*" --exclude "createVision/bin/*NonReactive"


