# libcpputils

C++ library

## To init library

```zsh
bdep init -C ~/repos/c++/build2/build2builds/gcc-debug \
@gcc-debug cc  config.cxx="g++ -ggdb -Og" \
config.cxx.coptions="-Wall -Wextra -Weffc++ -pedantic -pedantic-errors \
-fno-omit-frame-pointer -fsanitize=address -fsanitize=undefined  \
" config.cxx.poptions="-DDEBUG" \
config.cxx.libs="-lpthread" \
config.bin.ar=gcc-ar config.bin.ranlib=gcc-ranlib \
config.cxx.loptions="-fuse-ld=lld -fsanitize=address -fsanitize=undefined"
```
