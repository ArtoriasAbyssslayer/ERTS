# Covid_Trace_RPI4-APP
![RPI-THUMB](https://github.com/harryfilis/Covid_Trace_RPI4-APP/blob/master/Raspberry-Feature.png)
cross-compile with commands bellow 

Install deps:
```
sudo apt-get install libc6-armel-cross libc6-dev-armel-cross binutils-arm-linux-gnueabi libncurses5-dev build-essential bison flex libssl-dev bc
```

Install compiler:
```
sudo apt-get install gcc-arm-linux-gnueabi g++-arm-linux-gnueabi
```
Cross-compile example:
```
arm-linux-gnueabi-gcc hello.c -o hello 
```
flags needed are  in makefile  The makefile is a template on how to compile it with gcc instead of arm-linux-gcc cross-compiler if you dont upload the precompiled executable to the embedded system.
The project is not yet finished due to real-life problems.d
