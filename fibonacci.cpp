#include <iostream>
#include <omp.h>
using namespace std;

long long fib(int n){
    if(n <= 1){
        return n;
    }

    long long x;
    long long y;

    #pragma omp task shared(x)
    x = fib(n-1);

    #pragma omp task shared(y)
    y = fib(n-2);

    #pragma omp taskwait
    return x+y;
}

int main(){
    int n;
    cout<<"enter n";
    cin>>n;

    long long result;

    #pragma omp parallel
    {
        #pragma omp single
        result =fib(n);
    }

    cout << "fib "<<n<<"= "<<result<<endl;
}