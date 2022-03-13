# llvm-pass-skeleton

This is a fork of https://github.com/sampsyo/llvm-pass-skeleton repo for Cornell CS6120 - 
Advanced Compilers class taught by Andrian Sampson.

## What's New
So far, an extra pass that constructs a method call graph is added.

Build:

    $ cd llvm-pass-skeleton
    $ mkdir build
    $ cd build
    $ cmake ..
    $ make
    $ cd ..

Run the Call Graph example:

    $ clang -flegacy-pass-manager -Xclang -load -Xclang \
    $ llvm-pass-skeleton/build/callgraph/libCallGraphPass.so Test.c something.c
