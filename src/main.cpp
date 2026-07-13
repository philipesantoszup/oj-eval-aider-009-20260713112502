#include "vector.hpp"
#include "exceptions.hpp"
#include <iostream>

int main() {
    // Add test code here to verify the implementation
    try {
        sjtu::vector<int> v;
        v.push_back(1);
        v.push_back(2);
        v.push_back(3);
        
        std::cout << "Vector size: " << v.size() << std::endl;
        std::cout << "Vector capacity: " << v.capacity() << std::endl;
        
        for (size_t i = 0; i < v.size(); ++i) {
            std::cout << v[i] << " ";
        }
        std::cout << std::endl;
        
        v.pop_back();
        std::cout << "After pop_back, vector size: " << v.size() << std::endl;
        
        sjtu::vector<int> v2 = v;
        std::cout << "After copy constructor, vector size: " << v2.size() << std::endl;
        
        v.clear();
        std::cout << "After clear, vector size: " << v.size() << std::endl;
        
    } catch (const sjtu::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
    
    return 0;
}
