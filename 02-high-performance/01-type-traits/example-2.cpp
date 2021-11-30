#include <string.h>
#include <iostream>
#include <type_traits>

namespace my
{
    template <typename I1, typename I2, bool b>
    I2 copy_imp(I1 first, I1 last, I2 out, const std::integral_constant<bool, b> &)
    {
        while (first != last)
        {
            *out = *first;
            ++out;
            ++first;
        }

        std::cout << "elementwise." << std::endl;
        return out;
    }

    template <typename T>
    T *copy_imp(const T *first, const T *last, T *out, const std::true_type &)
    {

        memcpy(out, first, (last - first) * sizeof(T));
        std::cout << "bitwise." << std::endl;
        return out + (last - first);
    }

    template <typename I1, typename I2>
    I2 copy(I1 first, I1 last, I2 out)
    {
        typedef typename std::iterator_traits<I1>::value_type value_type;
        // makes the decision which implementation of my::copy_imp is applied
        return copy_imp(first, last, out, std::is_trivially_copy_assignable<value_type>()); 
    }
}

const int arraySize = 1000;

// intialize all elements to 0
int intArray[arraySize] = {
    0,
};
int intArray2[arraySize] = {
    0,
};

int *pArray = intArray;
const int *pArray2 = intArray2;

int main()
{
    std::cout << std::endl;

    std::cout << "Copying pArray ";

    my::copy(pArray2, pArray2 + arraySize, pArray);

    std::cout << "\n"
              << "Copying intArray ";

    my::copy(intArray2, intArray2 + arraySize, intArray);
}