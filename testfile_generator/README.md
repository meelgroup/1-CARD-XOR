Steps to generate CARD-XOR files

1) The PBLib Fork is located at https://github.com/master-keying/pblib. Compile the source code.
    ``` 
    git clone git@github.com:master-keying/pblib.git
    cd pblib 
    git submodule update --init
    cmake -H. -Bbuild
    cmake --build build
    ```

2) Copy the `libpb.a` file from `build/` to `pblib/`.
    > cp build/libpb.a pblib/
3) Copy the ```cardxorconverter.cpp``` file to the ```pblib``` folder and compile.
    ``` 
    cp cardxorconverter.cpp pblib/
    g++ -std=c++11 cardxorconverter.cpp libpb.a  && mkdir testfiles && mv a.out testfiles/
    ```
4) Choose the encoding {ADDER, BDD, CARD}. Choose the number of variables you need in the cnf and the number of times
   you want to conduct the experiment.
    > ./a.out ENCODING NUMVAR NUMEXP

This executable generates *n x n* CNF files with *n* variables (projected) going through all the parameters discussed in the paper. 
