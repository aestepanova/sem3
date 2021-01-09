#ifndef OTHER_VECTOR
#define OTHER_VECTOR

#include <memory>

template <class T>
class other_iterator;

template <class T>
class other_vector {
private:
    const static int min_cap = 4;
    size_t capacity;
    size_t s;
    T* data;
    std::allocator<T> allocator;
public:
    other_vector() :s(0), capacity(min_cap), data(allocator.allocate(min_cap)) {}
    other_vector(const other_vector<T>&);
    other_vector(other_vector<T>&&);
    ~other_vector();
    size_t size() const { return s; }
    bool empty() { return !s; }
    void resize(size_t);//
    void push_back(const T&);
    void push_back(T&&);
    other_vector<T>& operator =(const other_vector<T>&);
    other_vector<T>& operator =(other_vector<T>&&);
    const T& operator [](int i) const;
    T& operator [](int i);
    other_iterator<T> erase(other_iterator<T>);
    size_t erase(size_t position);
    void clear();
    friend class other_iterator<T>;
    typedef other_iterator<T> iterator;
    other_iterator<T> begin() const { return other_iterator<T>(data); }
    other_iterator<T> end() const { return other_iterator<T>(data + s); }
};

template <class T>
class other_iterator {
private:
    T* it;
public:
    other_iterator() :it(0) {}
    other_iterator(T* a) :it(a) {}
    other_iterator(const other_iterator<T>& p) { it = p.it; }
    ~other_iterator() {}
    other_iterator<T> operator +(const size_t) const;
    other_iterator<T> operator -(const size_t) const;
    other_iterator<T>& operator +=(const size_t);
    other_iterator<T>& operator -=(const size_t);
    other_iterator<T>& operator ++();
    other_iterator<T> operator ++(int);
    bool operator <(const other_iterator<T> a) const { return it < a.it; }
    bool operator >(const other_iterator<T> a) const { return it > a.it; }
    bool operator <=(const other_iterator<T> a) const { return it <= a.it; }
    bool operator >=(const other_iterator<T> a) const { return it >= a.it; }
    bool operator !=(const other_iterator<T> a) const { return it != a.it; }
    bool operator ==(const other_iterator<T> a) const { return it == a.it; }
    T& operator *() { return *it; }
    T* operator ->() { return it; }
};



template <class T>
other_vector<T>::other_vector(const other_vector<T>& a) {
    data = allocator.allocate(a.capacity);
    s = a.s;
    for (size_t i = 0; i < s; i++)
        data[i] = a.data[i];
}

template <class T>
other_vector<T>::other_vector(other_vector<T>&& a) {
    data = a.data;
    s = a.s;
    capacity = a.capacity;
}

template <class T>
other_vector<T>::~other_vector() {
    if (capacity > 0)
        allocator.deallocate(data, capacity);
}

template <class T>
void other_vector<T>::resize(size_t new_capacity) {
    if (new_capacity != capacity) {
        capacity = new_capacity;
        T* buf = data;
        data = allocator.allocate(new_capacity);
        if (s > new_capacity)
            s = new_capacity;
        for (size_t i = 0; i < s; i++)
            data[i] = std::move(buf[i]);
        delete[] buf;
    }
}

template <class T>
void other_vector<T>::push_back(const T& val) {
    if (capacity == s)
        resize(capacity + min_cap);
    data[s] = val;
    s++;
}

template <class T>
void other_vector<T>::push_back(T&& a) {
    if (capacity == s)
        resize(capacity + min_cap);
    data[s] = std::move(a);
    s++;
}

template <class T>
other_vector<T>& other_vector<T>::operator =(const other_vector<T>& a) {//??? ?????
    resize(a.capacity);
    std::copy(a.begin(), a.end(), data);
    return *this;
}

template <class T>
other_vector<T>& other_vector<T>::operator =(other_vector<T>&& a) {
    T* buf = data;
    int sbuf = s, scap = capacity;
    data = a.data;
    capacity = a.capacity;
    s = a.s;
    a.data = buf;
    a.capacity = scap;
    a.s = sbuf;
    return *this;
}

template <class T>
const T& other_vector<T>::operator[](int i) const {
    if (i < 0 || i >= s)
        throw std::runtime_error("Wrong index");
    return data[i];
}

template <class T>
T& other_vector<T>::operator[](int i) {
    if (i < 0 || i >= s)
        throw std::runtime_error("Wrong index");
    return data[i];
}

template <class T>
other_iterator<T> other_vector<T>::erase(other_iterator<T> position) {
    for (other_iterator<T> i = position; i != end() - 1; i++) {
        *i = *(i + 1);
    }
    s--;
    return position;
}

template <class T>
size_t other_vector<T>::erase(size_t position) {
    s--;
    for (size_t i = position; i < s; i++) {
        data[i] = data[i + 1];
    }
    return position;
}

template <class T>
void other_vector<T>::clear() {
    if (capacity > 0) {
        allocator.deallocate(data, capacity);
        s = 0;
        capacity = 0;
    }
}




template <class T>
other_iterator<T> other_iterator<T>::operator +(const size_t i) const {
    other_iterator<T> res(*this);
    res.it += i;
    return res;
}

template <class T>
other_iterator<T> other_iterator<T>::operator -(const size_t i) const {
    other_iterator<T> res(*this);
    res.it -= i;
    return res;
}

template <class T>
other_iterator<T>& other_iterator<T>::operator +=(const size_t i) {
    it += i;
    return *this;
}

template <class T>
other_iterator<T>& other_iterator<T>::operator -=(const size_t i) {
    it -= i;
    return *this;
}

template <class T>
other_iterator<T>& other_iterator<T>::operator ++() {
    it++;
    return *this;
}

template <class T>
other_iterator<T> other_iterator<T>::operator ++(int) {
    other_iterator<T> res(*this);
    it++;
    return res;
}
#endif