# High-Performance-Matrix-Multi

High Performance Matrix Multiplication

This repository follow my work in creating a high performance matrix multiplication class and method in C++. The motivation behind this project is that Machine learning mostly boils down to a couple of operations. One of those being the matrix multiplication operation which is essentially the dot product between two vectos. 

In this project, I used

* C++
* Threads Class
* Vectors Class


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


Conclusion:

As seen in Table 1, the parallel method outperformed that of the sequential method by a factor 5 to 11 when the matrix size was greater than 250; however, when the matrix size was smaller than 250, both methods achieved similliar results with the sequential beating the parallel method in some cases. This would make sense as perfomance is only achieved if the time gained from doing the mathematical operation in parallel is greater than the overhead added by the use of Threads.
