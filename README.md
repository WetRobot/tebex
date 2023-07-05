
# `tebex` --- Text Block EXtractor

## Using this library

Simply include this library as a sub-dir in your project and `include`
`./include/tebex/tebex.hpp` in your code. E.g. in a directory structure

```
my_project
    my_file.hpp
    tebex/
        include/
            tebex/
                tebex.hpp
                ...
```

you can use this line in `my_file.hpp`:

```
#include "./tebex/include/tebex/tebex.hpp"
```

 ## Features

 The main feature of this library is extraction of documentation
 contained within comments. This library does not prepare .html or other
 documents for you --- it simply extracts what you have written into
 comments into a location of your choice. Normally you would extract
 documentation from your comments into text files and produce
 a larger document out of the smaller ones. This README.md has been
 produced simply by extracting documentation comments from source files
 directly into the README.md.

 ## Main functions

 You may only need `tebex::extract::extract` or one of its signatures,
 which currently vary wrt. the first argument (`file_path` / `file_paths`)
 and arg `store`.

 ### Single file, arbitrary store callback function `store`
 ```

 @brief
 Extract blocks of text from a file.
 @param file_path
 Path to file from which to extract documentation.
 @param process
 Storage method, here an arbitrary callback function.
 Must have arguments
     const std::string&  line,
     std::string&        out_block_type,
     std::string&        out_key,
     bool&               out_storeable,
     std::string&        out_line
 @param store
 Storage method, here an arbitrary callback function.
 Must have arguments
     const std::string& key,
     const std::string& line,
     const int& line_no
 @param verbosity
 For debugging.
 @details
 There are three types of blocks of text:
 - "start-stop":
   Those defined by both a starting and stopping line. The starting
   and stopping lines look different.
    E.g. `{"@start", "text", "@stop"}`.
 - "boundary":
   Those limited by two "boundary" delimiters --- that is, two similar
   lines of text. E.g. `{"@boundary", "text", "@boundary"}`.
 - "start-only":
   Those that start after the starting line and stop at the next block's
   starting line. E.g. `{"@startonly", "text", "@startonly", "text"}`.
 ```


 ### Single file, write results into text files in directory `store`
 ```

 @brief
 Extract commented documentation from a single text file.
 Write extracted texts into dir `./tebex_output/` ---
 one file for each key.
 @param file_path
 Path to file from which to extract documentation.
 @param process
 Storage method, here an arbitrary callback function.
 Must have arguments
     const std::string&  line,
     std::string&        out_block_type,
     std::string&        out_key,
     bool&               out_storeable,
     std::string&        out_line
 @param store
 Storage method, here a path to an existing directory.
 @param verbosity
 For debugging.
 ```


 ### Multiple files, `store` templated out
 ```

 @brief
 Process multiple files with one function call. It simply loops over
 the texts. `store` is templated.
 @param file_paths
 One or more file paths to process.
 @param process
 See documents for functions that process only a single file.
 @param store
 Templated, see documents for functions that process only a single file.
 @param verbosity
 For debugging.
 ```

 ## Example .cpp scripts
 
 - `./doc/make_readme.cpp`: A tiny c++ programme to populate `README.md`.
 - `./examples/example_01.cpp`: Extracts data from
   "examples/data/input_01.cpp" into separate text files by key.
 - `./examples/example_02.cpp`: Extract data from both
   "examples/data/input_01.cpp" and "examples/data/input_02.cpp"
   in one call. Results go into text files.
 - `./examples/example_03.cpp`: Extract data from
   "examples/data/input_03.md". 
   Results stay in-memory and are not written to filesystem.
 - `./examples/example_04.cpp`: Extract data from both
   "examples/data/input_01.cpp" and "examples/data/input_02.cpp".
   Results stay in-memory and are not written to filesystem.
    {"examples/data/input_01.cpp", "examples/data/input_02.cpp"},
