This is a small script used to profile the RustBCA C library, specifically the `compound_tagged_bca_list_c` function.


### Building
Change `RUSTBCA_BUILD_DIR` in the Makefile to reflect the directory where RustBCA is built. As of 6/11/22, Makefile expected `RustBCA.h` to be in `$RUSTBCA_BUILD_DIR` and `liblibRustBCA.so` to be in `$RUSTBCA_BUILD_DIR/target/release`.

### Running
Modify `nincident` and `E_eV` in `profile_rustbca_lib.cpp` to play with runtime. Then run:
```
./profile_rustbca_lib
```

