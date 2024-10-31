# BinWrap: Hybrid Protection Against Native Node.js Add-ons
> Presenting BinWrap a framework that applies across the whole stack of node applications in order to isolate the execution of potentially-vulnerable,
third-party native add-ons.

Quick Jump: [Installation](#installation) | [Run](#run) | [Repo Structure](#repo-stracture) | [Documentation](#documentation)

## Installation
## Node
The version used for the modifications in 8.9.4. Start by first creating
the installation location for the custom Node.js environment. We advice
to not use the default location of **configure** script, since it will install
the modified Node.js gloabally.

###Configure
Change directory to Node source:
```
cd binwrap/source/node-v8.9.4-sharedlibs
```

Configure Node.js with the following command:
```
./configure --prefix=/home/<user>/path/to/node-install
```
If you want to configure Node with shared libraries, in order to
enhance the accuracy of SysFilter tool. Use the following options
in configure script: 
```
./configure --prefix=/home/<user>/path/to/node-install --shared-http-parser --shared-libuv --shared-openssl --shared-zlib --shared-cares
```

###Compile 
After successfully configuring the make file, compile the source of node:
```
make -j <number_of_cores-1>
```
## Run

## Example

## Repo Stracture

This repo hosts all the different components of the BinWrap paper. This repo is stractured as follows:

* [Source Code]()
* [Vulnerabilities]()
* [Example]()

## Documentation

* [Paper]()
