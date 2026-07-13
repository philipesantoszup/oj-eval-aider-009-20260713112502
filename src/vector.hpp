#ifndef SJTU_VECTOR_HPP
#define SJTU_VECTOR_HPP

#include "exceptions.hpp"

#include <climits>
#include <cstddef>

namespace sjtu
{
/**
 * a data container like std::vector
 * store data in a successive memory and support random access.
 */
template<typename T>
class vector
{
private:
    T* data = nullptr;
    size_t capacity = 0;
    size_t size_ = 0;
    
    void _reserve(size_t new_cap) {
        if (new_cap <= capacity) return;
        
        T* new_data = new T[new_cap];
        for (size_t i = 0; i < size_; ++i) {
            new_data[i] = data[i];
        }
        
        if (data) {
            delete[] data;
        }
        
        data = new_data;
        capacity = new_cap;
    }
    
    void _resize(size_t new_size) {
        if (new_size <= size_) {
            size_ = new_size;
            return;
        }
        
        _reserve(new_size);
        for (size_t i = size_; i < new_size; ++i) {
            new (data + i) T();
        }
        size_ = new_size;
    }

public:
	/**
	 * TODO
	 * a type for actions of the elements of a vector, and you should write
	 *   a class named const_iterator with same interfaces.
	 */
	/**
	 * you can see RandomAccessIterator at CppReference for help.
	 */
	class const_iterator;
	class iterator
	{
	// The following code is written for the C++ type_traits library.
	// Type traits is a C++ feature for describing certain properties of a type.
	// For instance, for an iterator, iterator::value_type is the type that the
	// iterator points to.
	// STL algorithms and containers may use these type_traits (e.g. the following
	// typedef) to work properly. In particular, without the following code,
	// @code{std::sort(iter, iter1);} would not compile.
	// See these websites for more information:
	// https://en.cppreference.com/w/cpp/header/type_traits
	// About value_type: https://blog.csdn.net/u014299153/article/details/72419713
	// About iterator_category: https://en.cppreference.com/w/cpp/iterator
	public:
		using difference_type = std::ptrdiff_t;
		using value_type = T;
		using pointer = T*;
		using reference = T&;
		using iterator_category = std::random_access_iterator_tag;

	private:
		/**
		 * TODO add data members
		 *   just add whatever you want.
		 */
		vector* vec;
		size_t index;
		
		iterator(vector* v, size_t idx) : vec(v), index(idx) {}
		
		friend class vector;

	public:
		/**
		 * return a new iterator which pointer n-next elements
		 * as well as operator-
		 */
		iterator operator+(const int &n) const
		{
			return iterator(vec, index + n);
		}
		iterator operator-(const int &n) const
		{
			return iterator(vec, index - n);
		}
		// return the distance between two iterators,
		// if these two iterators point to different vectors, throw invaild_iterator.
		int operator-(const iterator &rhs) const
		{
			if (vec != rhs.vec) {
				throw sjtu::invalid_iterator();
			}
			return index - rhs.index;
		}
		iterator& operator+=(const int &n)
		{
			index += n;
			return *this;
		}
		iterator& operator-=(const int &n)
		{
			index -= n;
			return *this;
		}
		/**
		 * TODO iter++
		 */
		iterator operator++(int) {
			iterator old = *this;
			++(*this);
			return old;
		}
		/**
		 * TODO ++iter
		 */
		iterator& operator++() {
			++index;
			return *this;
		}
		/**
		 * TODO iter--
		 */
		iterator operator--(int) {
			iterator old = *this;
			--(*this);
			return old;
		}
		/**
		 * TODO --iter
		 */
		iterator& operator--() {
			--index;
			return *this;
		}
		/**
		 * TODO *it
		 */
		T& operator*() const {
			return vec->data[index];
		}
		/**
		 * a operator to check whether two iterators are same (pointing to the same memory address).
		 */
		bool operator==(const iterator &rhs) const {
			return vec == rhs.vec && index == rhs.index;
		}
		bool operator==(const const_iterator &rhs) const {
			return vec == rhs.vec && index == rhs.index;
		}
		/**
		 * some other operator for iterator.
		 */
		bool operator!=(const iterator &rhs) const {
			return !(*this == rhs);
		}
		bool operator!=(const const_iterator &rhs) const {
			return !(*this == rhs);
		}
	};
	/**
	 * TODO
	 * has same function as iterator, just for a const object.
	 */
	class const_iterator
	{
	public:
		using difference_type = std::ptrdiff_t;
		using value_type = T;
		using pointer = T*;
		using reference = T&;
		using iterator_category = std::random_access_iterator_tag;

	private:
		const vector* vec;
		size_t index;
		
		const_iterator(const vector* v, size_t idx) : vec(v), index(idx) {}
		
		friend class vector;

	public:
		/**
		 * return a new iterator which pointer n-next elements
		 * as well as operator-
		 */
		const_iterator operator+(const int &n) const
		{
			return const_iterator(vec, index + n);
		}
		const_iterator operator-(const int &n) const
		{
			return const_iterator(vec, index - n);
		}
		// return the distance between two iterators,
		// if these two iterators point to different vectors, throw invaild_iterator.
		int operator-(const const_iterator &rhs) const
		{
			if (vec != rhs.vec) {
				throw sjtu::invalid_iterator();
			}
			return index - rhs.index;
		}
		const_iterator& operator+=(const int &n)
		{
			index += n;
			return *this;
		}
		const_iterator& operator-=(const int &n)
		{
			index -= n;
		 return *this;
		}
		/**
		 * TODO iter++
		 */
		const_iterator operator++(int) {
			const_iterator old = *this;
			++(*this);
			return old;
		}
		/**
		 * TODO ++iter
		 */
		const_iterator& operator++() {
			++index;
			return *this;
		}
		/**
		 * TODO iter--
		 */
		const_iterator operator--(int) {
			const_iterator old = *this;
			--(*this);
			return old;
		}
		/**
		 * TODO --iter
		 */
		const_iterator& operator--() {
			--index;
			return *this;
		}
		/**
		 * TODO *it
		 */
		const T& operator*() const {
			return vec->data[index];
		}
		/**
		 * a operator to check whether two iterators are same (pointing to the same memory address).
		 */
		bool operator==(const const_iterator &rhs) const {
			return vec == rhs.vec && index == rhs.index;
		}
		bool operator==(const iterator &rhs) const {
			return vec == rhs.vec && index == rhs.index;
		}
		/**
		 * some other operator for iterator.
		 */
		bool operator!=(const const_iterator &rhs) const {
			return !(*this == rhs);
		}
		bool operator!=(const iterator &rhs) const {
			return !(*this == rhs);
		}
	};
	/**
	 * TODO Constructs
	 * At least two: default constructor, copy constructor
	 */
	vector() : data(nullptr), capacity(0), size_(0) {}
	vector(const vector &other) : capacity(other.capacity), size_(other.size_) {
        if (capacity == 0) {
            data = nullptr;
            return;
        }
        data = new T[capacity];
        for (size_t i = 0; i < size_; ++i) {
            data[i] = other.data[i];
        }
    }
	/**
	 * TODO Destructor
	 */
	~vector() {
        if (data) {
            for (size_t i = 0; i < size_; ++i) {
                data[i].~T();
            }
            delete[] data;
        }
    }
	/**
	 * TODO Assignment operator
	 */
	vector &operator=(const vector &other) {
        if (this == &other) {
            return *this;
        }
        
        if (other.capacity > capacity) {
            if (data) {
                for (size_t i = 0; i < size_; ++i) {
                    data[i].~T();
                }
                delete[] data;
            }
            data = new T[other.capacity];
            capacity = other.capacity;
        }
        
        size_ = other.size_;
        for (size_t i = 0; i < size_; ++i) {
            data[i] = other.data[i];
        }
        
        return *this;
    }
	/**
	 * assigns specified element with bounds checking
	 * throw index_out_of_bound if pos is not in [0, size)
	 */
	T & at(const size_t &pos) {
        if (pos >= size_) {
            throw sjtu::index_out_of_bound();
        }
        return data[pos];
    }
	const T & at(const size_t &pos) const {
        if (pos >= size_) {
            throw sjtu::index_out_of_bound();
        }
        return data[pos];
    }
	/**
	 * assigns specified element with bounds checking
	 * throw index_out_of_bound if pos is not in [0, size)
	 * !!! Pay attentions
	 *   In STL this operator does not check the boundary but I want you to do.
	 */
	T & operator[](const size_t &pos) {
        return data[pos];
    }
	const T & operator[](const size_t &pos) const {
        return data[pos];
    }
	/**
	 * access the first element.
	 * throw container_is_empty if size == 0
	 */
	const T & front() const {
        if (size_ == 0) {
            throw sjtu::container_is_empty();
        }
        return data[0];
    }
	/**
	 * access the last element.
	 * throw container_is_empty if size == 0
	 */
	const T & back() const {
        if (size_ == 0) {
            throw sjtu::container_is_empty();
        }
        return data[size_ -  1];
    }
	/**
	 * returns an iterator to the beginning.
	 */
	iterator begin() {
        return iterator(this, 0);
    }
	const_iterator begin() const {
        return const_iterator(this, 0);
    }
	const_iterator cbegin() const {
        return const_iterator(this, 0);
    }
	/**
	 * returns an iterator to the end.
	 */
	iterator end() {
        return iterator(this, size_);
    }
	const_iterator end() const {
        return const_iterator(this, size_);
    }
	const_iterator cend() const {
        return const_iterator(this, size_);
    }
	/**
	 * checks whether the container is empty
	 */
	bool empty() const {
        return size_ == 0;
    }
	/**
	 * returns the number of elements
	 */
	size_t size() const {
        return size_;
    }
	/**
	 * returns the capacity of the container, i.e. the total number of elements that can be held
	 */
	size_t capacity() const {
        return capacity;
    }
	/**
	 * clears the contents
	 */
	void clear() {
        if (data) {
            for (size_t i = 0; i < size_; ++i) {
                data[i].~T();
            }
            delete[] data;
            data = nullptr;
        }
        size_ = 0;
        capacity = 0;
    }
	/**
	 * inserts value before pos
	 * returns an iterator pointing to the inserted value.
	 */
	iterator insert(iterator pos, const T &value) {
        if (pos.vec != this) {
            throw sjtu::invalid_iterator();
        }
        
        size_t index = pos.index;
        if (size_ >= capacity) {
            size_t new_cap = (capacity == 0) ? 1 : capacity * 2;
            _reserve(new_cap);
        }
        
        for (size_t i = size_; i > index; --i) {
            data[i] = data[i - 1];
        }
        data[index] = value;
        ++size_;
        
        return iterator(this, index);
    }
	/**
	 * inserts value at index ind.
	 * after inserting, this->at(ind) == value
	 * returns an iterator pointing to the inserted value.
	 * throw index_out_of_bound if ind > size (in this situation ind can be size because after inserting the size will increase 1.)
	 */
	iterator insert(const size_t &ind, const T &value) {
        if (ind > size_) {
            throw sjtu::index_out_of_bound();
        }
        
        return insert(iterator(this, ind), value);
    }
	/**
	 * removes the element at pos.
	 * return an iterator pointing to the following element.
	 * If the iterator pos refers the last element, the end() iterator is returned.
	 */
	iterator erase(iterator pos) {
        if (pos.vec != this) {
            throw sjtu::invalid_iterator();
        }
        
        if (pos.index >= size_) {
            return end();
        }
        
        for (size_t i = pos.index; i < size_ - 1; ++i) {
            data[i] = data[i + 1];
        }
        
        --size_;
        data[size_].~T();
        
        return iterator(this, pos.index);
    }
	/**
	 * removes the element with index ind.
	 * return an iterator pointing to the following element.
	 * throw index_out_of_bound if ind >= size
	 */
	iterator erase(const size_t &ind) {
        if (ind >= size_) {
            throw sjtu::index_out_of_bound();
        }
        
        return erase(iterator(this, ind));
    }
	/**
	 * adds an element to the end.
	 */
	void push_back(const T &value) {
        if (size_ >= capacity) {
            size_t new_cap = (capacity == 0) ? 1 : capacity * 2;
            _reserve(new_cap);
        }
        data[size_] = value;
        ++size_;
    }
	/**
	 * remove the last element from the end.
	 * throw container_is_empty if size() == 0
	 */
	void pop_back() {
        if (size_ == 0) {
            throw sjtu::container_is_empty();
        }
        --size_;
        data[size_].~T();
    }
};
}  // namespace sjtu
#endif
