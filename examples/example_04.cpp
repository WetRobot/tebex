#include "./include/tebex/tebex.hpp"
#include "./include/tebex/tools/misc_utils.hpp"

int main() {
    // @doc README.md
    // - `./examples/example_04.cpp`: Extract data from both
    //   "examples/data/input_01.cpp" and "examples/data/input_02.cpp".
    //   Results stay in-memory and are not written to filesystem.

    auto process_fun = tebex::process::process_comment_blocks_factory();
    auto store_fun = tebex::store::store_map_factory();
    tebex::extract::extract(
    //    {"examples/data/input_01.cpp", "examples/data/input_02.cpp"},
       "examples/data/input_02.cpp",
        process_fun,
        store_fun,
        2
    );

    tebex::store::store_map_get_type
        t = tebex::store::store_map_get();
    utils::print(
        std::get<0>(t),
        "std::get<0>(t)"
    );
    utils::print(
        std::get<1>(t),
        "std::get<1>(t)"
    );
    return 0;
}
