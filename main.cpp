#include <iostream>
#include <functional>
#include <memory>
#include <cstddef>
#include <algorithm>

//#define ARR_SIZE 40

template <typename T>
class marcinVector {
public:
    marcinVector()
        : data(std::make_unique<T[]>(40)), arr_size(40), elem_count(0)
    {
    }

    marcinVector(const marcinVector& vec)
        : data(std::make_unique<T[]>(vec.arr_size)), arr_size(vec.arr_size), elem_count(vec.elem_count)
    {
        std::copy_n(vec.data.get(), vec.arr_size, data.get());
    }

    friend void swap(marcinVector& first, marcinVector& second)
    {
        using std::swap;
        swap(first.data, second.data);
        swap(first.arr_size, second.arr_size);
    }

    marcinVector& operator=(const marcinVector& vec)
    {
        std::swap(*this, vec);
        return *this;
    }
    marcinVector (marcinVector&& vec) noexcept
        : marcinVector()
    {
        swap(*this, vec);
    }
//    marcinVector& operator=(const marcinVector& a) {return *this;}

    auto getArrSize() const { /*std::cout << arr_size << std::endl;*/ return arr_size; }

    auto getElemCount() const { /*std::cout << elem_count << std::endl;*/ return elem_count; }


    auto begin() const { return data.get(); }

    auto end() const {
        if (getElemCount() == 0)
            return data.get();
        else
            return &data[elem_count];
    }

    void push_back(const T& val) {
        if(arr_size > elem_count + 1)
        {
            data[elem_count] = val;
            elem_count += 1;
        }
    }

    T& operator[] (int idx) { return data[idx]; }

    void printVec(const marcinVector<T>& vec) {
        std::for_each( vec.begin(), vec.end(), [] (const auto & elem) { std::cout << elem << " ";});
    }

    ~marcinVector() = default;
private:
    std::unique_ptr<T[]> data;
    std::size_t arr_size{};
    std::size_t elem_count{};
};

int main() {
    marcinVector<int> myVec;
    myVec.push_back(100);
    myVec.push_back(200);
    myVec.printVec(myVec);

    auto var = 300;
    myVec[1] = var;

    myVec.printVec(myVec);

    auto myVec3(myVec);

    myVec3.printVec(myVec3);

    return 0;
}