# Description

Dummy project in C configure with a Jenkins CI pipeline that connects to sonnarcloud to check the quality of the code.

To install and configure the Jenkins server, please refer to [https://github.com/panizolledotangel/docker_jenkins_sonar_c](https://github.com/panizolledotangel/docker_jenkins_sonar_c)

# Requisites

* C compiler like gcc.
* Cmake ([https://cmake.org/](https://cmake.org/))

# Compile

```
mkdir build
cd build
cmake ..
make
```

# Pass the test

After compiling execute the next command from the build folder

```
ctest
```