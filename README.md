**File Detection**

Cross platform library to detect changes in file system

**Usage**


```
//Use save command to save check point of the file system

FileDetection.exe save "G:/Data"

//Use detect command to detect file changes since last saved check point

FileDetection.exe detect "G:/Data"
```

**Compiling**

You need modern C++ compiler which support C++ 17 and PicoSHA2 library (https://github.com/okdshin/PicoSHA2)

**Library**

The header file are located at ``include`` folder and source file are located at ``src`` folder. Look at ``Main.cpp`` as an example on how to use the library.

**Windows System**

For Windows you can use the Microsoft's vcpkg package manager to install dependency by ``.\vcpkg.exe install picosha`` 




