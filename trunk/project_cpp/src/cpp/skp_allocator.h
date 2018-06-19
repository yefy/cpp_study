#include <stdio.h>
#include <stdlib.h>
#include <memory>

namespace skp {

template <int __inst>
class __malloc_alloc_template {
public:

    static void* allocate(size_t __n)
    {
        printf("skp allocate \n");
        void* __result = ::malloc(__n);
        return __result;
    }

    static void deallocate(void* __p, size_t /* __n */)
    {
        printf("skp deallocate \n");
        ::free(__p);
    }

    static void* reallocate(void* __p, size_t /* old_sz */, size_t __new_sz)
    {
        printf("skp reallocate \n");
        void* __result = ::realloc(__p, __new_sz);
        return __result;
    }
};

typedef __malloc_alloc_template<0> malloc_alloc;
typedef malloc_alloc alloc;

template <class _Tp>
class allocator {
    typedef alloc _Alloc;          // The underlying allocator.
public:
    typedef size_t     size_type;
    typedef ptrdiff_t  difference_type;
    typedef _Tp*       pointer;
    typedef const _Tp* const_pointer;
    typedef _Tp&       reference;
    typedef const _Tp& const_reference;
    typedef _Tp        value_type;

    template <class _Tp1> struct rebind {
        typedef allocator<_Tp1> other;
    };

    allocator()  {printf("skp allocator() 111 \n");}
    allocator(const allocator&)  {printf("skp allocator() 222 \n");}
    template <class _Tp1> allocator(const allocator<_Tp1>&)  {printf("skp allocator() 333 \n");}
    ~allocator()  {printf("skp ~allocator() \n");}

    pointer address(reference __x) const { return &__x; }
    const_pointer address(const_reference __x) const { return &__x; }

    // __n is permitted to be 0.  The C++ standard says nothing about what
    // the return value is when __n == 0.
    _Tp* allocate(size_type __n, const void* = 0) {
        return __n != 0 ? static_cast<_Tp*>(_Alloc::allocate(__n * sizeof(_Tp)))
                        : 0;
    }

    // __p is not permitted to be a null pointer.
    void deallocate(pointer __p, size_type __n)
    { _Alloc::deallocate(__p, __n * sizeof(_Tp)); }

    size_type max_size() const
    { return size_t(-1) / sizeof(_Tp); }

    //void construct(pointer __p, const _Tp& __val) { new(__p) _Tp(__val); }
    //void destroy(pointer __p) { __p->~_Tp(); }

#if __cplusplus >= 201103L
    template<typename _Up, typename... _Args>
    void
    construct(_Up* __p, _Args&&... __args)
    { ::new((void *)__p) _Up(std::forward<_Args>(__args)...); }

    template<typename _Up>
    void
    destroy(_Up* __p) { __p->~_Up(); }
#else
    // _GLIBCXX_RESOLVE_LIB_DEFECTS
    // 402. wrong new expression in [some_] allocator::construct
    void
    construct(pointer __p, const _Tp& __val)
    { ::new((void *)__p) _Tp(__val); }

    void
    destroy(pointer __p) { __p->~_Tp(); }
#endif


};

template<>
class allocator<void> {
public:
    typedef size_t      size_type;
    typedef ptrdiff_t   difference_type;
    typedef void*       pointer;
    typedef const void* const_pointer;
    typedef void        value_type;

    template <class _Tp1> struct rebind {
        typedef allocator<_Tp1> other;
    };
};


template <class _T1, class _T2>
inline bool operator==(const allocator<_T1>&, const allocator<_T2>&)
{
    return true;
}

template <class _T1, class _T2>
inline bool operator!=(const allocator<_T1>&, const allocator<_T2>&)
{
    return false;
}


template<class T>
T* make_data()
{
    return new T();
}

template<class T, class U>
T* make_data(U&& u)
{
    return new T(std::forward<U>(u));
}

template<class T, class... U>
T* make_data(U&&... u)
{
    return new T(std::forward<U>(u)...);
}

template<class T, class U>
std::unique_ptr<T> make_unique(U&& u)
{
    return std::unique_ptr<T>(new T(std::forward<U>(u)));
}

template<class T, class... U>
std::unique_ptr<T> make_unique(U&&... u)
{
    return std::unique_ptr<T>(new T(std::forward<U>(u)...));
}


}
