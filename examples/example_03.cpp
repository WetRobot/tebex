#include "./include/tebex/tebex.hpp"
#include "./include/tebex/tools/misc_utils.hpp"

int main() {
    // @doc README.md
    // - `./examples/example_03.cpp`: Extract data from
    //   "examples/data/input_03.md". 
    //   Results stay in-memory and are not written to filesystem.

    tebex::extract::extract(
        "examples/data/input_03.md",
        tebex::process::process_markdown,
        tebex::store::store_map_factory(),
        1
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
