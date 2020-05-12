# Trabalho 3

Augusto César Bisognin - Sistemas de Informação

[OpenMPDemoABC.cpp](OpenMPDemoABC.cpp)

## Exemplo de saída

```
Each thread should add its char to the array n times (n=20)
Correct results should total exactly nThreads*nTimes chars
Case 1: no mutex, default scheduling (expecting wrong results)
BCABCBABCABCABCABCABCABCABCABCABCABCABCABCABCABABACBCBC-CA-A
A=19 B=20 C=19 
Case 2: same as case 1 (possibly getting different results due to scheduling)
BCABCABCABCABCABCABCBACBACBACBACBACBACBACBACBACBACBACBCAB--A
A=19 B=20 C=19 
Case 3: using mutex (expecting correct results)
ACBBBBBBBBBBBBBBBBBBBBAAAAAAAAAAAAAAAAAAACCCCCCCCCCCCCCCCCCC
A=20 B=20 C=20 
```

PS: não entendi se era só isso, mas é a mesma função `main()` do outro programa, portanto a saída é idêntica. Aí aparece o resultado das três executações (duas sem controle da região crítica e uma com o resultado correto).

## "Mutex" do OMP

[OMP_SET_LOCK()](https://computing.llnl.gov/tutorials/openMP/#OMP_SET_LOCK)