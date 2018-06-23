# c_xml_generation

A Jinja2 based C code generator for dynamic data storage and xml report production on embedded systems.

## What it is

This is code generation tool intended to ease the writing of repetitive xml generation code. I did it to become more robust against specification changes.

## Requeriments

You need to install *Python* (3.3 or later) and its package *Jinja2* in order to use the code generator.

The target C code relies on *libxml2* (2.6) for the report generation, so you will need to install that library too. Note that you dont actually need to generate the code in your target machine.

## Usage

Let's take the provided example structure:
    
    $ python build.py example/example_xml_struct.xml example_xml_cogeden

Will take 'example_xml_struct.xml' as an input structure defining the desired xml data and output the code to 'example_xml_codegen.h' and 'example_xml_codegen.c'.

You can use the example to learn how to write your own xml templates. I will write a short tutorial on the different available options in the near future.

## Sample project

The code generator comes with a small self-test project build on top of the generated code. To compile, you will need to install *CMake*.

    $ mkdir build;cd build
    $ cmake ../
    $ make
