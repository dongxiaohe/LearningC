#include <iostream>
#include <cstring>

class Test {
    char *data;
public:
    Test(const char *p) {
        std::cout << "here 1" << std::endl;
        size_t size = std::strlen(p) + 1;
        data = new char[size];
        std::memcpy(data, p, size);
    }

    Test(const Test &p) {
        std::cout << "here 2" << std::endl;
        size_t size = std::strlen(p.data) + 1;
        data = new char[size];
        std::memcpy(data, p.data, size);
    }

    Test(Test &&p) {
        std::cout << "here 3" << std::endl;
        data = p.data;
        p.data = nullptr;
    }

    ~Test() {
        delete[] data;
    }

    char *getData() {
        return data;
    }
};

Test &&dummyTest() {
    return Test("123");
}

int main() {
    Test test1("123");
    std::cout << test1.getData() << std::endl;
    char init[30] = "this is init";
    char add[] = " added now";
    Test test2(strcat(init, add));
    std::cout << test2.getData() << std::endl;
    Test test3(test2);
    std::cout << test3.getData() << std::endl;
    Test test4(std::move(test3)); // Move return rreference so there is no deep copy
    std::cout << test4.getData() << std::endl;
    Test test5(dummyTest()); // a function return r reference so there is no deep copy
    std::cout << test5.getData() << std::endl;
}

