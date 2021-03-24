# DarisaLLCSample

## Prerequisites

* OpenCV

Download libraries from https://mega.nz/file/PkxiFJyD#AqfYPKGa-sskwXYNDAOP2RP_WbfvPPDM8M9hFNn6HH4
and extract the contents into the `blocks/OpenCV4` folder.

```
unzip CinderOpenCV4-macos-4.5.1.zip -d blocks/Cinder-OpenCV4
```

## Building Cinder

```
cd cinder
mkdir build
cd build
cmake ..
make -j
```

## Building the sample application

```
mkdir build
cd build
cmake ..
make -j
```

## Running the sample application

```
make run
```
