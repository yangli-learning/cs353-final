#!/bin/sh

# export binary files

cd ..
rm -rf createVirtualNav.tar
tar -cvzf createVirtualNavBin.tar createVirtualNav/README createVirtualNav/createRemote/createRemoteClient createVirtualNav/createRemote/createRemoteServer createVirtualNav/createRemote/README createVirtualNav/createRemote/lib createVirtualNav/createVision/bin --exclude "*.svn*"
