#include<vector>
#include<string>
#include<regex>

#include "./include/tebex/tebex.hpp"

int main() {
    // @doc README.md
    // ## Example .cpp scripts
    // 
    // - `./doc/make_readme.cpp`: A tiny c++ programme to populate `README.md`.

    std::vector<std::vector<std::string>>
    file_path_sets = {
        {
            "include/tebex/tebex.hpp",
            "include/tebex/tools/extract.hpp"
        },
        {
            "./doc/make_readme.sh"
        },
        {
            "./doc/make_readme.cpp",
            "./examples/example_01.cpp",
            "./examples/example_02.cpp",
            "./examples/example_03.cpp",
            "./examples/example_04.cpp"
        }
    };

    // @TODO
    // process_comment_blocks_factory: Figure out a way to set
    // out_storeable = true when using @start-@stop tags even for
    // lines that are not comment lines. Maybe a separate call
    // of tebex::extract::extract?
    for (int i = 0; i < file_path_sets.size(); i++) {
        std::vector<std::string>& file_path_set = file_path_sets[i];
        tebex::extract::extract(
            file_path_set,
            tebex::process::process_comment_blocks_factory(
                std::regex("^[ ]*/{2,}.*$"),
                std::regex("^[ ]*/[*].*$"),
                std::regex("^[ ]*[*]/.*$"),
                std::regex("^[ /*]*@(doc[a-z]*)[ ]*(.+)$"),
                std::regex("^[ ]*[/*]+"),

                {"@doc"},
                {"@docstart"},
                {"@docstop"},
                {}
            ),
            "./tmp/",
            0
        );
    }
    
    return(0);
}
