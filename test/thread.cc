#include <thread>
#include <iostream>
#include <chrono>
#include <mutex>
#include <iomanip>      // for std::setw(), std::left, std::right.
#include <vector>
void counter(int n){
    for (int i = 0; i < n; i++) {
        std::cout << "Thread id: " << std::this_thread::get_id() << "\t";
        std::cout << "Value: " << i << std::endl;
        std::flush(std::cout);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

int main(int argc, char const *argv[]) {

    std::vector<int> l;
    l.push_back(1);
    l.push_back(-1);

    std::vector<int> n;
    n.push_back(0);
    n.push_back(1);

    // +-------------------------------+ DEBUG USE +-------------------------------+ //
    // Race condition
    // std::thread t1{counter, 20};
    // std::thread t2{counter, 12};
    // counter(30);
    // t1.join();
    // t2.join();
    // +-------------------------------+ DEBUG END +-------------------------------+ //
    
    const int num_iter = 10000000;
    int i = 0;

    // +-------------------------------+ DEBUG USE +-------------------------------+ //
    // Without mutex
    std::thread t3([&]() {
        for(int j = 0; j < num_iter; j++){
            i--;
        }
    });
    std::thread t4([&]() {
        for(int j = 0; j < num_iter; j++){
            i++;
        }
    });
    t3.join();
    t4.join();
    std::cout << "Value of i(Without mutex):\t" << std::right << std::setw(10) << i << std::endl;
    // +-------------------------------+ DEBUG END +-------------------------------+ //
    
    // +-------------------------------+ DEBUG USE +-------------------------------+ //
    // With mutex
    i = 0; // reset i
    std::mutex iMultex;
    std::thread t5([&]() {
        for(int j = 0; j < num_iter; j++){
            iMultex.lock();
            i--;
            iMultex.unlock();
        }
    });
    std::thread t6([&]() {
        for(int j = 0; j < num_iter; j++){
            iMultex.lock();
            i++;
            iMultex.unlock();
        }
    });
    t5.join();
    t6.join();
    std::cout << "Value of i(With mutex):   \t" << std::right << std::setw(10) << i << std::endl;
    // +-------------------------------+ DEBUG END +-------------------------------+ //
    return 0;
}

