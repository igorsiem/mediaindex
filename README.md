# MediaIndex README

## Overview

*MediaIndex* is a simple viewer / indexer for media files (e.g. images, video , audio). Currently at the proof-of-concept state, it provides a simple browsing / viewing GUI for images.

Future developments will incude the ability view other media times, manipulate files, and add searchable metadata.

## Build Notes

The build system is relatively simple, and based on `cmake` and `conan`. A `rake` file is provided for high-level developer functions. Run `rake -T` from the project root for a list of tasks.

### qLib

The [*qLib* library](https://github.com/igorsiem/qlib) is used for several low-level functions, including string conversions and logging. Eventually, qLib should be made available as a conan package (see below), but for now, it simply needs to be in the same directory as the *MediaIndex* checkout.

### Conan

Dependencies are managed using [conan.io](https://conan.io). In addition to the standard `conan-center` repo, `conan` should be configured with the following sources:

* catchorg https://api.bintray.com/conan/catchorg/Catch2 True

* qt https://api.bintray.com/conan/bincrafters/public-conan True

When using GCC, the conan profile being used (`~/.conan/profiles/default` by default) should be set to use the C++11 ABI, to resolve issues related to `std::string` (see [conan docs here](https://docs.conan.io/en/latest/howtos/manage_gcc_abi.html))

## License

Copyright Igor Siemienowicz 2018, 2019 Distributed under the Boost Software License Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at [LICENSE_1_0.txt](https://www.boost.org/LICENSE_1_0.txt))
