# 1-CARD-XOR
Scripts and data for *("Phase Transition Behavior of Cardinality and XOR Constraints")[https://www.ijcai.org/proceedings/2019/0162.pdf]*, IJCAI-19

1) pb-experiments folder has the graphs used in the paper and some more. 

2) file generator scripts- In C++. To compile use command 
> g++ -std=c++11 cardxorconverter.cpp libpblib.a
This file generates *n x n* CNF files with *n* variables(projected) going through all the parameters discussed in the paper. 

Our experiments were run with (CryptoMiniSAT5)[https://github.com/msoos/cryptominisat]


