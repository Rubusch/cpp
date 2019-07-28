#!/bin/bash

die()
{
    echo "ERROR: $1"
    exit 1
}

FILES=($(find . -type d))


## testing clang
for MAKEFILE in "./MAKE_clang/Makefile" "./MAKE_gcc/Makefile"; do
    [[ -f "$MAKEFILE" ]] || die "no such Makefile '$MAKEFILE'"
    for item in ${FILES[*]:1}; do

        ## exclude allocation and deallocation - don't contain code!
        [[ -n "$(echo "$item"| grep MAKE)" ]] && continue
        [[ -n "$(echo "$item"| grep N3664)" ]] && continue
        [[ -n "$(echo "$item"| grep N3778)" ]] && continue

        [[ -d "$item" ]] || die "no such directory '$item'"
        cp "${MAKEFILE}" "${item}"

        pushd . > /dev/null
        cd "$item"

        echo -n "TESTING in "
        pwd

        make
        ./main.exe || die "'${item}' failed"
        make clean

        echo
        popd > /dev/null
    done
done

echo "READY."
