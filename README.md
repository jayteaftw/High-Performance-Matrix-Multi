# High-Performance-Matrix-Multi

High Performance Matrix Multiplication

This repository follows my work in creating a high performance matrix multiplication class and method in C++. The motivation behind this project is that Machine learning models mostly boils down to a couple of operations. One of those being the matrix multiplication operation which is essentially the dot product between two vectors. In project, I wanted to learn more about paralleism and how it can be used to increase performance.

In this project, I used

* C++
* Threads Class
* Vectors Class
* Parallelism


Table 1: Comparing Sequential and Parallel Multiplication Operations

| Matrix Size | Sequential (ms) | Parallel (ms) | Ratio  |
| ----------- | --------------- | ------------- | ------ |
| 10 x 10     | 3               | 3             | 1      |
| 50 x 50     | 342             | 364           | 0.94   |
| 100 x 100   | 2984            | 2817          | 1.059  |
| 250 x 250   | 44787           | 8029          | 5.578  |
| 500 x 500   | 354098          | 34852         | 10.16  |
| 1000 x 1000 | 3021767         | 263086        | 11.486 |
| 2000 x 2000 | 23860284        | 2219230       | 10.752 |


## Conclusion:

As seen in Table 1, the parallel method outperformed that of the sequential method by a factor 5 to 11 when the matrix size was greater than 250; however, when the matrix size was smaller than 250, both methods achieved similliar results with the sequential beating the parallel method in some cases. This would make sense because perfomance is only achieved if the time gained from performing the mathematical operations in parallel is greater than that of the overhead added by the use of Threads. As the matrix size shrinks, the number of operations descreses while the thread's overhead stays fixed leading to some cases no perfomance is gained through parallelism.
