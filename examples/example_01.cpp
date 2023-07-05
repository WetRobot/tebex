#include "./include/tebex/tebex.hpp"

int main() {
    // @doc README.md
    // - `./examples/example_01.cpp`: Extracts data from
    //   "examples/data/input_01.cpp" into separate text files by key.
    tebex::extract::extract(
        "examples/data/input_01.cpp",
        tebex::process::process_comment_blocks_factory(),
        "./tebex_output/",
        1
    );
    return 0;
}
