#include<vector>
#include<string>

#include "./include/tebex/tebex.hpp"

int main() {
    // @doc README.md
    // - `./doc/make_readme.cpp`: A tiny c++ programme to populate `README.md`.
    std::vector<std::string> ho   = {"@doc"};
    std::vector<std::string> hf_h = {"@docstart"};
    std::vector<std::string> hf_f = {"@docstop"};
    std::vector<std::string> e    = {};
    std::vector<std::string> file_paths = {
        "include/tebex/tebex.hpp",
        "include/tebex/tools/extract.hpp"
    };

    tebex::extract::extract(
        file_paths,
        "[/][*]",
        "[*][/]",
        "//",
        ho,
        hf_h,
        hf_f,
        e,
        "./",
        true,
        false,
        false,
        0
    );
    
    tebex::extract::extract(
        "./doc/make_readme.sh",
        "",
        "",
        "#",
        ho,
        hf_h,
        hf_f,
        e,
        "./"
    );

    std::vector<std::string> more_file_paths = {
        "./doc/make_readme.cpp",
        "./examples/example_01.cpp",
        "./examples/example_02.cpp",
        "./examples/example_03.cpp"
    };
    tebex::extract::extract(
        more_file_paths,
        "[/][*]",
        "[*][/]",
        "//",
        ho,
        hf_h,
        hf_f,
        e,
        "./",
        true,
        true,
        true,
        0
    );
    

    return(0);
}
