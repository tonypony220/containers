// Common interface for interaction with STL
// containers and algorithms. You can manually change
// allocation algorithm with different 'AllocationStrategy'
//
// In this implementation was not implented 'adress' and 'max_size'
// unnecessary functions for.

template<typename T, class AllocationStrategy>
class Allocator
{
    static_assert(!std::is_same_v<T, void>, "Type of the allocator can not be void");
public:
    using value_type = T;

    template<typename U, class AllocStrategy>
    friend class Allocator;
    
    template<typename U>
    struct rebind
    {
        using other = Allocator<U, AllocationStrategy>;
    };
public:
    Allocator() = default;
    
    explicit Allocator(AllocationStrategy& strategy) noexcept : m_allocatio_strategy(&strategy) {}
    
    Allocator(const Allocator& other) noexcept : m_allocation_strategy(other.m_allocation_strategy) {}
    
    template<typename U>
    Allocator(const Allocator<U, AllocationStrategy>& other) noexcept : m_allocation_strategy(other.m_allocation_strategy) {}
    
    T* allocate(std::size_t count_objects)
    {
        assert(m_allocation_strategy && "Not initialized allocation strategy");
        return static_cast<T*>(m_allocation_strategy->allocate(count_objects * sizeof(T)));
    }
    
    void deallocate(void* memory_ptr, std::size_t count_objects)
    {
        assert(m_allocation_strategy && "Not initialized allocation strategy");
        m_allocation_strategy->deallocate(memory_ptr, count_objects * sizeof(T));
    }
    
    template<typename U, typename... Args>
    void construct(U* ptr, Args&&... args)
    {
        new (reinterpret_cast<void*>(ptr)) U { std::forward<Args>(args)... };
    }
    
    template<typename U>
    void destroy(U* ptr)
    {
        ptr->~U();
    }
private:
    AllocationStrategy* m_allocation_strategy = nullptr;
};

template<typename T, typename U, class AllocationStrategy>
bool operator==(const Allocator<T, AllocationStrategy>& lhs, const Allocator<U, AllocationStrategy>& rhs)
{
    return lhs.m_allocation_strategy == rhs.m_allocation_strategy;
}

template<typename T, typename U, class AllocationStrategy>
bool operator!=(const Allocator<T, AllocationStrategy>& lhs, const Allocator<U, AllocationStrategy>& rhs)
{
    return !(lhs == rhs);
}n
