# Examples
There're 2 directories, examples for "translator" are put at `specs`
while examples for "test execution" are put at `tests`.

## `specs`
The "translator" is a standalone program that can translate the spec file defined in YAML format into a C++ template ready for our BDD framework.

Since the built translator is placed in the build directory of meson, which is located in the root of the project,
we provided a script `run.sh` for you to reference the program.

To translate a spec file, just run `./run.sh <spec.yml> [output.cpp]`,
and the C++ template will be generated at the given path.
If the path is not given, then `a.cpp` will be created instead.

After the template is generated, test developers can then write tests in the template.

This is the output of one of the examples:
![translator-output.png](/assets/translator-output.png)


## `tests`
There're some examples prepared in `tests`, to see the execution results,
one can run `make` first to compile those tests.

Since the test programs are dynamically linked to our `cppbdd` library,
we have to set `LD_LIBRARY_PATH` to tell the system where the library is.
Thus, we also provided `run.sh` for executing the compiled tests.

To run a test program, just run `./run.sh <test>` and the results will be shown.

This is the output of one of the examples:
![test-output.png](/assets/test-output.png)
