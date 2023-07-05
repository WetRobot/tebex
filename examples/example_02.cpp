
#include<vector>
#include<string>

#include "./include/tebex/tebex.hpp"

int main() {
    // @doc README.md
    // - `./examples/example_02.cpp`: Extract doxygen comments in
    //   `./examples/data/input_02.cpp` into separate text files --- though
    //   some clean-up work remains. Also, multiple function definitions
    //   in the same file would currently be a problem as arguments with
    //   the same name would be inserted into the same tebex_output file.
    std::vector<std::string> ho   = {"@"};
    std::vector<std::string> hf_h = {};
    std::vector<std::string> hf_f = {};
    std::vector<std::string> e    = {};
    tebex::extract::extract(
        "./examples/data/input_02.cpp",
        "[/][*]",
        "[*][/]",
        "//",
        ho,
        hf_h,
        hf_f,
        e,
        "./tebex_output/",
        true,
        false,
        false,
        0
    );
    return(0);
}
