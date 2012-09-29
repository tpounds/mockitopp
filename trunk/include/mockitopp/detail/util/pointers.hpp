#ifndef __MOCKITOPP_POINTERS_PTR__
#define __MOCKITOPP_POINTERS_PTR__

namespace mockitopp
{
   namespace detail
   {
      /**
       * The default deleter functor used by shared_ptr
       * to free the underlying allocated memory.
       *
       * @author Trevor Pounds
       */
      template <typename T>
      struct default_ptr_deleter
      {
         void operator() (T* ptr)
            { delete ptr; }
      };

      /**
       * A reference counting "smart" pointer similar to
       * the ones provided by boost, tr1, c++0x, etc.
       *
       * NOTE:
       *
       *   Concurrent usage is not supported since the
       *   reference counter is not modified atomically.
       *
       * @author Trevor Pounds
       */
      template <typename T, typename D = default_ptr_deleter<T> >
      class shared_ptr
      {
         public:

            shared_ptr()
               : _ptr_impl()
               {}

            shared_ptr(const shared_ptr& rhs)
               : _ptr_impl(rhs._ptr_impl)
               { __increment(); }

            explicit shared_ptr(T* raw_ptr)
               : _ptr_impl(new shared_ptr_impl(raw_ptr, 1))
               {}

            ~shared_ptr() { __decrement(); }

            bool operator==(const shared_ptr& rhs) const { return _ptr_impl == rhs._ptr_impl; }
            bool operator!=(const shared_ptr& rhs) const { return _ptr_impl != rhs._ptr_impl; }
            bool operator<(const shared_ptr& rhs)  const { return _ptr_impl < rhs._ptr_impl; }
            bool operator>(const shared_ptr& rhs)  const { return _ptr_impl > rhs._ptr_impl; }
            bool operator<=(const shared_ptr& rhs) const { return _ptr_impl <= rhs._ptr_impl; }
            bool operator>=(const shared_ptr& rhs) const { return _ptr_impl >= rhs._ptr_impl; }

            shared_ptr& operator=(const shared_ptr& rhs)
            {
               if(this != &rhs)
               {
                  __decrement();
                  _ptr_impl = rhs._ptr_impl;
                  __increment();
               }
               return *this;
            }

            T* get()        const { return (_ptr_impl) ? _ptr_impl->_raw_ptr : 0; }
            T& operator*()  const { return *get(); }
            T* operator->() const { return get(); }

         private:

            struct shared_ptr_impl
            {
               T*     _raw_ptr;
               size_t _count;

               shared_ptr_impl(T* raw_ptr = 0, size_t count = 0)
                  : _raw_ptr(raw_ptr)
                  , _count(count)
                  {}

               ~shared_ptr_impl()
                  { D()(_raw_ptr); }
            }* _ptr_impl;

            void __decrement()
            {
               if(_ptr_impl && --(_ptr_impl->_count) == 0)
                  { delete _ptr_impl; }
            }

            void __increment()
            {
               if(_ptr_impl)
                  { (_ptr_impl->_count)++; }
            }
      };

      /**
       * The default deleter functor used by shared_array
       * to free the underlying allocated memory.
       *
       * @author Trevor Pounds
       */
      template <typename T>
      struct default_array_deleter
      {
         void operator() (T* array)
            { delete[] array; }
      };

      /**
       * A reference counting "smart" array pointer similar
       * to the ones provided by boost, tr1, c++0x, etc.
       *
       * NOTE:
       *
       *   Concurrent usage is not supported since the
       *   reference counter is not modified atomically.
       *
       * @author Trevor Pounds
       */
      template <typename T, typename D = default_array_deleter<T> >
      class shared_array : public shared_ptr<T, D>
      {
         public:

            shared_array()
               : shared_ptr<T, D>()
               {}

            explicit shared_array(T* raw_ptr)
               : shared_ptr<T, D>(raw_ptr)
               {}

            T& operator[] (size_t i) const { return *(shared_array::get() + i); }
      };

      /**
       * A pointer that transfers ownership on copies and assignment.
       *
       * @author Trevor Pounds
       */
      template <typename T, typename D = default_ptr_deleter<T> >
      class owned_ptr
      {
         public:

            owned_ptr()
               : _ptr(0)
               {}

            owned_ptr(const owned_ptr& rhs)
               : _ptr((T*) ((size_t) rhs.release() | OWNER))
               {}

            explicit owned_ptr(T* ptr)
               : _ptr((T*) ((size_t) ptr | OWNER))
               {}

            ~owned_ptr() { __delete(); }

            owned_ptr& operator=(const owned_ptr& rhs)
            {
               if(this != &rhs)
               {
                  if(get() != rhs.get())
                     { __delete(); }
                  _ptr = rhs._ptr;
                  rhs.release();
               }
               return *this;
            }

            bool is_owner() const { return ((size_t) _ptr & OWNER) == OWNER; }

            T* get()        const { return (T*) ((size_t) _ptr & POINTER); }
            T& operator*()  const { return *get(); }
            T* operator->() const { return get(); }
            T* release()    const { return (_ptr = get()); }

         private:

            static const size_t OWNER   = 0x1;
            static const size_t POINTER = ~OWNER;

            mutable T* _ptr;

            void __delete()
            {
               if(is_owner())
               {
                  D()(get());
                  _ptr = 0;
               }
            }
      };

      /**
       * An array pointer that transfers ownership on copies and assignment.
       *
       * @author Trevor Pounds
       */
      template <typename T, typename D = default_array_deleter<T> >
      class owned_array : public owned_ptr<T, D>
      {
         public:

            owned_array()
               : owned_ptr<T, D>()
               {}

            explicit owned_array(T* ptr)
               : owned_ptr<T, D>(ptr)
               {}

            T& operator[] (size_t i) const { return *(owned_array::get() + i); }
      };
   } // namespace detail
} // namespace mockitopp

#endif //__MOCKITOPP_POINTERS_PTR__
