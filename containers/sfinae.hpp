template <typename T, typename = typename T::iterator>

template <typename T>
void printContainer(T container, typename T::iterator* = nullptr)
{
    ...
}


template <bool condition, typename Type>
struct EnableIf;
 
template <typename Type>
struct EnableIf<true, Type>
{
    using type = Type;
};
