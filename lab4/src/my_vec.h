#ifndef OTHER_VECTOR
#define OTHER_VECTOR

#include <memory>

namespace lab4 {

///Custom iterator
    template<class T>
    class vec_it;


///Custom Vector class that is used in table

    template<class T>
    class my_vec {
    private:
        const static int min_cap = 4;
        size_t capacity; // вместимость
        size_t s; // текущее количество элементов
        T *data;
        std::allocator<T> allocator;
    public:
        /// \brief Initializing constructor
        my_vec() : s(0), capacity(min_cap), data(allocator.allocate(min_cap)) {}

        /// \brief A copy constructor
        my_vec(const my_vec<T> &);

        /// \brief Moving constructor
        my_vec(my_vec<T> &&);

        ~my_vec();

        size_t size() const { return s; }

        bool empty() { return !s; }

        void resize(size_t);

        /*!
            Adds an element to the end of the vector by copying
            */
        void push_back(const T &);

        /*!
            Adds an element to the end of the vector by moving
            */
        void push_back(T &&);

        /*!
            Overloaded copy assignment operator
            */
        my_vec<T> &operator=(const my_vec<T> &);

        /*!
            Overloaded assignment operator by moving
            */
        my_vec<T> &operator=(my_vec<T> &&);

        /*!
            Overloaded index access operator for reading
            */
        const T &operator[](int i) const;

        /*!
            Overloaded index access operator for reading and modifying
            */
        T &operator[](int i);

        /*!
            Removes an element from a vector by iterator
            */
        vec_it<T> erase(vec_it<T>);

        /*!
            Clears the vector
            */
        void clear();

        friend class vec_it<T>;

        typedef vec_it<T> iterator;

        vec_it<T> begin() const { return vec_it<T>(data); }

        vec_it<T> end() const { return vec_it<T>(data + s); }
    };

    template<class T>
    class vec_it {
    private:
        T *it;
    public:
        vec_it() : it(0) {}

        vec_it(T *a) : it(a) {}

        vec_it(const vec_it<T> &p) { it = p.it; }

        ~vec_it() {}

        vec_it<T> operator+(size_t) const;

        vec_it<T> operator-(size_t) const;

        vec_it<T> &operator+=(size_t);

        vec_it<T> &operator-=(size_t);

        vec_it<T> &operator++();

        vec_it<T> operator++(int);

        bool operator<(const vec_it<T> a) const { return it < a.it; }

        bool operator>(const vec_it<T> a) const { return it > a.it; }

        bool operator<=(const vec_it<T> a) const { return it <= a.it; }

        bool operator>=(const vec_it<T> a) const { return it >= a.it; }

        bool operator!=(const vec_it<T> a) const { return it != a.it; }

        bool operator==(const vec_it<T> a) const { return it == a.it; }

        T &operator*() { return *it; }

        T *operator->() { return it; }
    };


    template<class T>
    my_vec<T>::my_vec(const my_vec<T> &a) {
        data = allocator.allocate(a.capacity);
        s = a.s;
        for (size_t i = 0; i < s; i++)
            data[i] = a.data[i];
    }

    template<class T>
    my_vec<T>::my_vec(my_vec<T> &&a) {
        data = a.data;
        s = a.s;
        capacity = a.capacity;
    }

    template<class T>
    my_vec<T>::~my_vec() {
        if (capacity > 0)
            allocator.deallocate(data, capacity);
    }

    template<class T>
    void my_vec<T>::resize(size_t new_capacity) {
        if (new_capacity != capacity) {
            capacity = new_capacity;
            T *buf = data;
            data = allocator.allocate(new_capacity);
            if (s > new_capacity)
                s = new_capacity;
            for (size_t i = 0; i < s; i++)
                data[i] = std::move(buf[i]);
            delete[] buf;
        }
    }

    template<class T>
    void my_vec<T>::push_back(const T &val) {
        if (capacity == s)
            resize(capacity + min_cap);
        data[s] = val;
        s++;
    }

    template<class T>
    void my_vec<T>::push_back(T &&a) {
        if (capacity == s)
            resize(capacity + min_cap);
        data[s] = std::move(a);
        s++;
    }

    template<class T>
    my_vec<T> &my_vec<T>::operator=(const my_vec<T> &a) {
        resize(a.capacity);
        std::copy(a.begin(), a.end(), data);
        return *this;
    }

    template<class T>
    my_vec<T> &my_vec<T>::operator=(my_vec<T> &&a) {
        T *buf = data;
        int sbuf = s, scap = capacity;
        data = a.data;
        capacity = a.capacity;
        s = a.s;
        a.data = buf;
        a.capacity = scap;
        a.s = sbuf;
        return *this;
    }

    template<class T>
    const T &my_vec<T>::operator[](int i) const {
        if (i < 0 || i >= s)
            throw std::runtime_error("Wrong index");
        return data[i];
    }

    template<class T>
    T &my_vec<T>::operator[](int i) {
        if (i < 0 || i >= s)
            throw std::runtime_error("Wrong index");
        return data[i];
    }

    template<class T>
    vec_it<T> my_vec<T>::erase(vec_it<T> position) {
        for (vec_it<T> i = position; i != end() - 1; i++) {
            *i = *(i + 1);
        }
        s--;
        return position;
    }


    template<class T>
    void my_vec<T>::clear() {
        if (capacity > 0) {
            allocator.deallocate(data, capacity);
            s = 0;
            capacity = 0;
        }
    }


    template<class T>
    vec_it<T> vec_it<T>::operator+(const size_t i) const {
        vec_it<T> res(*this);
        res.it += i;
        return res;
    }

    template<class T>
    vec_it<T> vec_it<T>::operator-(const size_t i) const {
        vec_it<T> res(*this);
        res.it -= i;
        return res;
    }

    template<class T>
    vec_it<T> &vec_it<T>::operator+=(const size_t i) {
        it += i;
        return *this;
    }

    template<class T>
    vec_it<T> &vec_it<T>::operator-=(const size_t i) {
        it -= i;
        return *this;
    }

    template<class T>
    vec_it<T> &vec_it<T>::operator++() {
        it++;
        return *this;
    }

    template<class T>
    vec_it<T> vec_it<T>::operator++(int) {
        vec_it<T> res(*this);
        it++;
        return res;
    }
}
#endif