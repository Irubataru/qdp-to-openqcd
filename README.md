# QDP to OpenQCD

## Running

```
qdp_to_chroma [input_config] [output_config]
 - [input_config]  the QDP config stored in the SciDAC file format (.lime)
 - [output_config] name of the output file stored in the OpenQCD file format
```

Converts a configuration stored in the SciDAC file format (also known as
[lime](https://github.com/usqcd-software/c-lime)) to the file format output by
the [openQCD](http://luscher.web.cern.ch/luscher/openQCD/) software.

The input file is currently assumed to be created by the hmc program in
[chroma](https://github.com/JeffersonLab/chroma). This is because of the XML
path to the string containing the lattice sizes is of a certain format. This
will be extended in the future. Because the lattice size of openQCD is a compile
time constant, this must be set to the same values as the configuration one
wishes to import prior to compilation. The program only runs in serial, and
running it in parallel will cause the program to abort.

## Building

Simply type `make` to create the executable, which will be created in
`bin/qdp_to_chroma`. The program requires a compiled version of
[qdpxx](https://github.com/usqcd-software/qdpxx) as well as an implementation of
MPI and the source files of openQCD.

The following environment variables will help the compilation:

 - `CXX`: the C++ compiler
 - `CC`: the C compiler
 - `QDP_DIR`: location where QDP is compiled
 - `OPENQCD_DIR`: location of OpenQCD source files
 - `MPI_DIR`: location of MPI header files
