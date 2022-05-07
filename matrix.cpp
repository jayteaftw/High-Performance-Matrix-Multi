#include <iostream>
#include <thread>
#include <algorithm>
#include <vector>
#include <chrono>
#include <fstream>

using namespace std::chrono;

using namespace std;
class Matrix{

     int* data;
     int rows;
     int columns;

public:

    Matrix(int _n, int _m): rows(_n), columns(_m){
        data = new int[rows * columns];

        //init the data array to zero
        fill(data, data + rows*columns, 0);

    }

    void set_value(int i, int j, int value){
        data[i*columns + j] = value;
    }

    void set_all(int value){
        fill(data, data + rows*columns, value);
    }

    void print(){
        for(int i = 0; i < this->rows; i++){
            for(int j = 0; j < this->columns; j++){
                cout<<data[i+j]<<" ";
            }
            cout<<endl;
        }
    }


    static void multiply(Matrix *x, Matrix *y, Matrix *results){

        if(!(x->columns == y->rows))
            cout << "Error: Invalid Dimension of Matrix for Multiplication"<<endl;

        int r = results->rows * results->columns;

        for(int i = 0; i < r; i++){
            for(int j = 0; j < x->columns; j++){
                int row = (i /results->columns)*x->columns + j;
                int column = i % results->rows + j*y->columns;
                results->data[i] = x->data[row ] * y->data[ column];
            }
        }
    }

    static void parallel_multiply(Matrix *x, Matrix *y, Matrix *results){
        struct process_data_chunk{

            void operator()(Matrix *x, Matrix *y, Matrix *results, int start_index, int end_index){

                for(int i = start_index; i < end_index; i++){
                    for(int j = 0; j < x->columns; j++){
                        int row = (i /results->columns)*x->columns + j;
                        int column = i % results->rows + j*y->columns;
                        results->data[i] = x->data[row ] * y->data[ column];
                    }
                }

            }

        };

        int length = results->rows * results->columns;

        if(!length) return;

        int min_per_thread = 10000;
        int max_threads = (length + min_per_thread - 1) / min_per_thread;
        int hardware_threads = thread::hardware_concurrency();
        int num_threads = min(hardware_threads != 0 ? hardware_threads : 2, max_threads);
        int block_size = length / num_threads;
        vector<thread> threads(num_threads - 1);
        int block_start = 0;
        int block_end = 0;

        {

            for(unsigned long i = 0; i < (num_threads -1); i++){

                block_start = i * block_size;
                block_end = block_start + block_size;
                threads[i] = thread(process_data_chunk(), results, x, y, block_start, block_end);

            }
            process_data_chunk()(results, x, y, block_end, length);

            for(int i=0; i<threads.size(); ++i)
                if(threads[i].joinable())
                        threads[i].join();


            

        }

    }
};



int main(){

    vector<int> matrix_sizes = {10, 50, 100, 250, 500, 1000, 2000};
    string out_string; 
    for(vector<int>::iterator ptr = matrix_sizes.begin(); ptr < matrix_sizes.end(); ptr++ ){

        int matrix_size = *ptr;
        Matrix A(matrix_size, matrix_size);
        Matrix B(matrix_size, matrix_size);
        Matrix C(matrix_size, matrix_size);
        Matrix D(matrix_size, matrix_size);

        A.set_all(1);
        B.set_all(1);

        
       
        
        unsigned long duration_par = 0;
        unsigned long duration_seq = 0;
        int test_length = 5;
        for(int i = 0; i<test_length; i++){
            auto start = high_resolution_clock::now();
            Matrix::multiply(&A, &B, &C);
            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<microseconds>(stop - start);
            cout<<"Matrix Size " << to_string(matrix_size) <<", Sequential Matrix Mult "<< duration.count() << endl;
            duration_seq += duration.count();


            start = high_resolution_clock::now();
            Matrix::parallel_multiply(&A, &B, &D);
            stop = high_resolution_clock::now();
            duration = duration_cast<microseconds>(stop - start);
            cout<<"Matrix Size " << to_string(matrix_size) <<", Parallel Matrix Mult "<< duration.count() << endl<<endl;
            duration_par += duration.count();

        }
        out_string += "Matrix Size " + to_string(matrix_size)+ ", Sequential Matrix Mult\n Time:" + to_string(duration_seq/test_length) + "\n"; 
        out_string += "Matrix Size " + to_string(matrix_size)+ ", Parallel Matrix Mult\n Time:" + to_string(duration_par/test_length) + "\n\n";
    }
    cout<<out_string;

    ofstream myfile("results.txt");
    if(myfile.is_open())
        myfile<<out_string; 

    return 0;
}