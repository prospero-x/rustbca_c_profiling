
# Directory where cargo run --release was run to build RustBCA. User-specific.
RUSTBCA_BUILD_DIR = ~/RustBCA

# These should change (in the future)
RUSTBCA_HEADER_DIR = $(RUSTBCA_BUILD_DIR)
RUSTBCA_LIB_DIR    = $(RUSTBCA_BUILD_DIR)/target/release

# These should NOT change
RUSTBCA_HEADER = $(RUSTBCA_HEADER_DIR)/RustBCA.h
RUSTBCA_LIB    = $(RUSTBCA_LIB_DIR)/liblibRustBCA.so

SRC = profile_rustbca_lib.cpp
BIN = profile_rustbca_lib

$(BIN): $(SRC) $(RUSTBCA_LIB) $(RUSTBCA_HEADER)
	g++ -o $(BIN) $(SRC) -I $(RUSTBCA_HEADER_DIR) $(RUSTBCA_LIB)

clean:
	@rm -rf $(BIN)
