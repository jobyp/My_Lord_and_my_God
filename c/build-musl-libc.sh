#!/bin/bash

set -ex

pushd $HOME/src
if [[ -d musl ]]; then
    pushd musl
    git checkout master
    git pull --tags
    popd
else
    git clone git://git.musl-libc.org/musl
fi

pushd musl
git branch -D release || true
git checkout -b release $(git describe --tags --abbrev=0)
make distclean
[[ -d $HOME/musl ]] && rm -rf $HOME/musl
./configure --prefix=$HOME/musl --disable-shared --exec-prefix=$HOME --syslibdir=$HOME/musl/lib
make
make install
popd

popd

exit 0
