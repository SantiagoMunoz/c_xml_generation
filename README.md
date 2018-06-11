# c_xml_generation

A Jinja2 based C code generator for dynamic data storage and xml report production on embedded systems.

## What it is


## Requeriments

You need to install *Python* (3.3 or later) and its package *Jinja2* in order to use the code generator.

The target C code relies on *libxml2* (2.6) for the report generation, so you will need to install that library too. Note that you dont actually need to generate the code in your target machine.

## Sample project

The code generator comes with a small self-test project build on top of the generated code. To compile, you will need to install *CMake*.

    $ mkdir build;cd build
    $ cmake ../
    $ make
