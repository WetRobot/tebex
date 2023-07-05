
#include<vector>
#include<string>

#include "./include/tebex/tebex.hpp"

int main() {
    // @doc README.md
    // - `./examples/example_03.cpp`: You can actually use `tebex` for other
    //   purposes also though this was not on purpose. Here is shown how you
    //   can separate `./examples/data/input_02.md` into separate files by
    //   section.
    std::vector<std::string> ho   = {"[#]+"};
    std::vector<std::string> hf_h = {};
    std::vector<std::string> hf_f = {};
    std::vector<std::string> e    = {};
    tebex::extract::extract(
        "./examples/data/input_02.md",
        "",
        "",
        "^",
        ho,
        hf_h,
        hf_f,
        e,
        "./tebex_output/",
        false,
        false,
        false,
        0
    );
    return(0);
}
