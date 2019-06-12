# qStub README

## Overview

The *qStub* distribution is a basic implementation of a simple Qt-based
windowing app to simplify the process of getting a qPrise-style project
started.

## Usage Notes

Starting a project using *qStub* is simply a matter of copying the files
in the qStub checkout and updating the "Config" section at the top of the
Rakefile. There *may* be some fiddling with conan installations (see below),
but everything should just build 'as is'.

Don't forget to edit this README for your new project!

## Build Notes

### qLib

*qStub* uses *qLib* for several low-level functions, including string
conversions and logging. Eventually, qLib should be made available as a conan
package (see below), but for now, it simply needs to be in the same directory as the
*qStub* checkout (or the project derived from *qStub*).

### Conan

Dependencies are managed using [conan.io](https://conan.io). In addition to
the standard `conan-center` repo, `conan` should be configured with the
following sources:

* catchorg https://api.bintray.com/conan/catchorg/Catch2 True

* qt https://api.bintray.com/conan/bincrafters/public-conan True

When using GCC, the conan profile being used (`~/.conan/profiles/default` by
default) should be set to use the C++11 ABI, to resolve issues related to
`std::string` (see [conan docs
here](https://docs.conan.io/en/latest/howtos/manage_gcc_abi.html))

## License

Copyright Igor Siemienowicz 2018, 2019
Distributed under the Boost Software License, Version 1.0. (See accompanying
file LICENSE_1_0.txt or copy at
[LICENSE_1_0.txt](https://www.boost.org/LICENSE_1_0.txt))
