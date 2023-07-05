#ifndef tebex_HPP
#define tebex_HPP

#include "./tools/extract.hpp"

/*
@doc README.md

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

*/

namespace tebex {
    namespace args = args;
    namespace process = process;
    namespace store = store;
    namespace extract = extract;
}

#endif
