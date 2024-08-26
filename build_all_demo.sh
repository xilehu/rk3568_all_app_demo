#/bin/sh


VAR_VAL="$1"

if [ "$VAR_VAL" = "clean" ]; then  
    rm -rf  build lib bin
    exit 0
fi

if [ ! -d "build" ]; then
    mkdir build
else 
    rm -rf build/*
fi

cd build
cmake ..
make






