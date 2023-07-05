#include "./include/tebex/tebex.hpp"

int main() {
    // @doc README.md
    // - `./examples/example_02.cpp`: Extract data from both
    //   "examples/data/input_01.cpp" and "examples/data/input_02.cpp"
    //   in one call. Results go into text files.
    tebex::extract::extract(
       {"examples/data/input_01.cpp", "examples/data/input_02.cpp"},
        tebex::process::process_comment_blocks_factory(),
        "./tebex_output/",
        1
    );
    return 0;
}
