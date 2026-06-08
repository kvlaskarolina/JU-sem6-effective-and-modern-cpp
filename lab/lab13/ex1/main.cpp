
import emcpp.vector;
import <iostream>;
import <string>;

int main() {
    using namespace emcpp;

    std::cout << "--- Testing Int Vector ---" << std::endl;
    using VInt = Vector<int, 10, SafePolicy>;
    VInt v{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    VInt x(v);
    VInt y{4, 4, 2, 5, 3, 2, 3, 4, 2, 1};

    std::cout << "Lazy operations:\n";
    VInt z = v + x + 3 * y - 2 * x; 
    std::cout << "Result Vector z: " << z << std::endl;

    try {
        std::cout << "Attempting invalid access..." << std::endl;
        int bad = z[100]; 
    } catch (const std::out_of_range& e) {
        std::cout << "Caught expected error: " << e.what() << std::endl;
    }

    std::cout << "\n--- Testing String Vector ---" << std::endl;
    using VStr = Vector<std::string, 3, SafePolicy>;
    VStr s1{"Hello", "Modern", "C++"};
    std::cout << "Strings: " << s1 << std::endl;

    return 0;
}