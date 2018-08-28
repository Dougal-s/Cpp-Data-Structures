/**
 * STL compliant c++ vector
 *
 * @author Dougal Stewart
 * @version 0.1 18/8/18
 */

#include <iostream>

#include <stddef.h>
#include <memory>
#include <initializer_list>
#include <iterator>
 
template<typename T, typename = void>
struct is_iterator {
   static constexpr bool value = false;
};

template<typename T>
struct is_iterator<T, typename std::enable_if<!std::is_same<typename std::iterator_traits<T>::value_type, void>::value>::type> {
   static constexpr bool value = true;
};




template <typename T, typename Alloc = std::allocator<T>>
class Vector {

	using Alloc_traits = std::allocator_traits<Alloc>;

public:

	// Member classes
	
	using value_type             = T;
	using allocator_type         = Alloc;
	using reference              = value_type&;
	using const_reference        = const value_type&;
	using pointer                = typename std::allocator_traits<allocator_type>::pointer;
	using const_pointer          = typename std::allocator_traits<allocator_type>::const_pointer;
	
	using iterator               = T*;
	using const_iterator         = const T*;
	
	using reverse_iterator       = std::reverse_iterator<iterator>;
	using const_reverse_iterator = std::reverse_iterator<const_iterator>;
	
	using difference_type        = ptrdiff_t;
	using size_type              = size_t;

	// Member Functions
	
	Vector() : m_start(), m_end(), m_end_of_storage(), m_allocator() {}
	
	explicit Vector(const allocator_type& alloc) : m_start(), m_end(), m_end_of_storage(), m_allocator(alloc) {}
	
	explicit Vector(size_type n, const allocator_type& alloc = allocator_type()) : m_allocator(alloc)  {
		m_start = allocate(n);
		m_end = m_start + n;
		m_end_of_storage = m_end;
	}
	
	Vector(size_type n, const value_type& val, const allocator_type& alloc = allocator_type()) : m_allocator(alloc) {
		m_start = allocate(n);
		m_end = std::uninitialized_fill_n(m_start, n, val);
		m_end_of_storage = m_end;
	}
	
	template <class InputIterator, class = typename std::enable_if<is_iterator<InputIterator>::value>::type>
	Vector(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type()) : m_allocator(alloc) {
		m_start = allocate(std::distance(first, last));
		m_end = std::uninitialized_copy(first, last, m_start);
		m_end_of_storage = m_end;
	}
	
	Vector(const Vector& x) {
		m_start = allocate(x.size());
		m_end = std::uninitialized_copy(x.begin(), x.end(), m_start);
		m_end_of_storage = m_end;
	}
	
	Vector(const Vector& x, const allocator_type& alloc) : m_allocator(alloc) {
		m_start = allocate(x.size());
		m_end = std::uninitialized_copy(x.begin(), x.end(), m_start);
		m_end_of_storage = m_end;
	}
	
	Vector(Vector&& x) {
		*this = std::move(x);
	}
	
	Vector(Vector&& x, const allocator_type& alloc) : m_allocator(alloc) {
		*this = std::move(x);
	}
	
	Vector(std::initializer_list<value_type> il, const allocator_type& alloc = allocator_type()) : m_allocator(alloc){
		m_start = allocate(il.size());
		m_end = std::uninitialized_copy(il.begin(), il.end(), m_start);
		m_end_of_storage = m_end;
	}
	
	
	~Vector() {
		std::destroy(m_start, m_end);
		deallocate(m_start, m_end_of_storage - m_start);
	}
	
	
	Vector& operator=(const Vector& x) {
		if (this != &x) {
			if (x.size() > capacity()) {
				Vector tmp(x);
				this->swap(tmp);
			} else {
				std::destroy(m_start, m_end);
				m_end = std::uninitialized_copy(x.begin(), x.end(), m_start);
			}
		}
		return *this;
	}
	
	Vector& operator=(Vector&& x) {
		if (x.size() > capacity()) {
			this->swap(x);
		} else {
			std::destroy(m_start, m_end);
			m_end = std::uninitialized_move(x.m_start, x.m_end, m_start);
		}
		
		return *this;
	}
	
	Vector& operator=(std::initializer_list<value_type> il) {
		this->assign(il);
		return *this;
	}
	
	// Iterators
	
	iterator begin() {
		return iterator(m_start);
	}
	
	const_iterator begin() const {
		return const_iterator(m_start);
	}
	
	iterator end() {
		return iterator(m_end);
	}
	
	const_iterator end() const {
		return const_iterator(m_end);
	}
	
	reverse_iterator rbegin() {
		return reverse_iterator(begin());
	}
	
	const_reverse_iterator rbegin() const {
		return const_reverse_iterator(begin());
	}
	
	reverse_iterator rend() {
		return reverse_iterator(end());
	}
	
	const_reverse_iterator rend() const {
		return const_reverse_iterator(end());
	}
	
	const_iterator cbegin() const {
		return const_iterator(m_start);
	}
	
	const_iterator cend() const {
		return const_iterator(m_end);
	}
	
	const_reverse_iterator crbegin() const {
		return const_reverse_iterator(begin());
	}
	
	const_reverse_iterator crend() const {
		return const_reverse_iterator(end());
	}
	
	// Capacity
	
	size_type size() const {
		return m_end - m_start;
	}
	
	size_type max_size() const {
		return Alloc_traits::max_size(m_allocator);
	}
	
	void resize(size_type n) {
		if (n > size()) {
			reserve(n);
			std::uninitialized_default_construct(m_end, m_start+n);
		} else {
			std::destroy(m_start + n, m_end);
		}
		
		m_end = m_start + n;
	}
	
	void resize(size_type n, const value_type& val) {
		if (n > size()) {
			reserve(n);
			std::uninitialized_fill(m_end, m_start+n, val);
		} else {
			std::destroy(m_start + n, m_end);
		}
		
		m_end = m_start + n;
	}
	
	size_type capacity() const {
		return m_end_of_storage - m_start;
	}
	
	bool empty() const {
		return m_start == m_end;
	}
	
	/**
	 * increases capacity of vector to n if n is greater than the current capacity
	 */
	void reserve(size_type n) {
		if (n > capacity())
			reallocate(n);
	}
	
	/**
	 * sets the capacity of the vector equal to its size
	 */
	void shrink_to_fit() {
		reallocate(size());
	}
	
	// Element access
	
	reference operator[](size_type n) {
		return m_start[n];
	}
	
	const_reference operator[](size_type n) const {
		return m_start[n];
	}
	
	reference at(size_type n) {
		if (n >= size()) {
			throw std::out_of_range("Vector: input out of range");
		}
		
		return m_start[n];
	}
	const_reference at(size_type n) const {
		if (n >= size()) {
			throw std::out_of_range("Vector: input out of range");
		}
		
		return m_start[n];
	}
	
	reference front() {
		return *m_start;
	}
	
	const_reference front() const {
		return *m_start;
	}
	
	reference back() {
		return *(m_end-1);
	}
	
	const_reference back() const {
		return *(m_end-1);
	}
	
	value_type* data() {
		return m_start;
	}
	
	const value_type* data() const {
		return m_start;
	}
	
	// Modifiers
	
	/**
	 * sets the vector equal to the contents between the two iterators
	 */
	template <class InputIterator, class = typename std::enable_if<is_iterator<InputIterator>::value>::type>
	void assign(InputIterator first, InputIterator last) {
		std::destroy(m_start, m_end);
		if(std::distance(first, last) > capacity()) {
			m_end = m_start;
			reallocate(std::distance(first, last));
		}
		m_end = std::uninitialized_copy(first, last, m_start);
	}
	
	/**
	 * Sets the size of the vector to n and sets the contents equal to val
	 */
	void assign(size_type n, const value_type& val) {
		std::destroy(m_start, m_end);
		reserve(n);
		m_end = std::uninitialized_fill_n(m_start, n, val);
	}
	
	/**
	 * sets the contents of the vector equal to il
	 */
	void assign(std::initializer_list<value_type> il) {
		std::destroy(m_start, m_end);
		
		if (il.size() > capacity()) {
			m_end = m_start;
			reallocate(il.size());
		}
		
		m_end = std::uninitialized_copy(il.begin(), il.end(), m_start);
	}
	
	/**
	 * adds element val to the back of the vector
	 */
	void push_back(const value_type& val) {
		emplace_back(val);
	}
	
	/**
	 * adds element val to the back of the vector
	 */
	void push_back(value_type&& val) {
		emplace_back(std::move(val));
	}
	
	/**
	 * removes element at the back of the array
	 */
	void pop_back() {
		if (size() != 0) {
			Alloc_traits::destroy(m_allocator, m_end-1);
			m_end--;
		}
	}
	
	iterator insert (const_iterator position, const value_type& val) {
		return emplace(position, val);
	}
	
	iterator insert (const_iterator position, size_type n, const value_type& val) {

		difference_type offset = position-begin();
		
		if (m_end + n > m_end_of_storage) {
			if (empty()) {
				create_storage(n);
			} else {
				reallocate(std::max(2*capacity(), size() + n));
			}
		}
		
		iterator new_position = begin() + offset;
		
		m_end = std::uninitialized_move(iterator(new_position), iterator(m_end), iterator(new_position+n));
		
		std::uninitialized_fill_n(new_position, n, val);
		
		return new_position;
	}
	
	template <class InputIterator, class = typename std::enable_if<is_iterator<InputIterator>::value>::type>
	iterator insert (const_iterator position, InputIterator first, InputIterator last) {

		difference_type offset = position-begin();
		difference_type input_size = std::distance(first, last);
		
		if (m_end + input_size > m_end_of_storage) {
			if (empty()) {
				create_storage(input_size);
			} else {
				reallocate(std::max(2*capacity(), size() + input_size));
			}
		}
		
		iterator new_position = begin() + offset;
		
		m_end = std::uninitialized_move(iterator(new_position), iterator(m_end), iterator(new_position+input_size));
		
		std::uninitialized_copy(first, last, new_position);
		
		return new_position;
	}
	
	iterator insert (const_iterator position, value_type&& val) {
		return emplace(position, std::move(val));
	}
	
	iterator insert (const_iterator position, std::initializer_list<value_type> il) {

		difference_type offset = position-begin();
		
		if (m_end + il.size() > m_end_of_storage) {
			if (empty()) {
				create_storage(il.size());
			} else {
				reallocate(std::max(2*capacity(), size() + il.size()));
			}
		}
		
		iterator new_position = begin() + offset;
		
		m_end = std::uninitialized_move(iterator(new_position), iterator(m_end), iterator(new_position+il.size()));
		
		std::uninitialized_copy(il.begin(), il.end(), new_position);
		
		return new_position;
	}
	
	/**
	 * removes element pointed to by position from the vector
	 */
	iterator erase(const_iterator position) {
		Alloc_traits::destroy(m_allocator, position);
		m_end = std::uninitialized_move(iterator(position+1), end(), iterator(position));
	}
	
	/**
	 * @brief removes elements [first, last)
	 * @param first first element to be removed
	 * @param last element after the last to be removed
	 */
	iterator erase(const_iterator first, const_iterator last) {
		std::destroy(first, last);
		m_end = std::uninitialized_move(iterator(last), end(), iterator(first));
	}
	
	
	/**
	 * swaps the contents of two vectors
	 */
	void swap(Vector& x) {
		std::swap(m_start, x.m_start);
		std::swap(m_end, x.m_end);
		std::swap(m_end_of_storage, x.m_end_of_storage);
		std::swap(m_allocator, x.m_allocator);
	}
	
	/**
	 * destroy all elements in vector and sets size to zero
	 */
	void clear() {
		std::destroy(m_start, m_end);
		m_end = m_start;
	}
	
	/**
	 * @brief inserts an element at position and constructs it with arguments args
	 * @param position to insert element
	 * @param args arguments to use when constructing the new element
	 */
	template <class... Args>
	iterator emplace(const_iterator position, Args&&... args) {

		difference_type offset = position-begin();
		
		if (m_end == m_end_of_storage) {
			if (empty()) {
				create_storage(1);
			} else {
				reallocate(2*capacity());
			}
		}
		
		iterator new_position = begin() + offset;
		
		m_end = std::uninitialized_move(iterator(new_position), iterator(m_end), iterator(new_position+1));
		
		Alloc_traits::construct(m_allocator, new_position, args...);
		
		return new_position;
	}
	
	/**
	 * @brief adds an element to the end of the vector and constructs it with arguments args
	 * @param args arguments that will be used to construct the element 
	 */
	template <class... Args>
	void emplace_back(Args&&... args) {
		if (m_end == m_end_of_storage) {
			if (empty()) {
				create_storage(1);
			} else {
				reallocate(2*capacity());
			}
		}
		
		Alloc_traits::construct(m_allocator, m_end, args...);
		m_end++;
	}
	
	// Allocator

	/**
	 * returns a copy of the allocator object used by the vector
	 */
	allocator_type get_allocator() const {
		return m_allocator;
	}
	
	// Non-member functions
	
	friend void swap(Vector& first, Vector& second) {
		first.swap(second);
	}

private:

	pointer m_start;
	pointer m_end;
	pointer m_end_of_storage;

	allocator_type m_allocator;
	
	/**
	 * @brief allocates an array of size n
	 * @param n size of the array to be allocated
	 * @return pointer to the start of the allocated array
	 */
	pointer allocate(size_type n) {
		return n != 0 ? Alloc_traits::allocate(m_allocator, n) : pointer();
	}
	
	/**
	 * @brief deallocates an array of size n pointed to by p
	 * @param p pointer to array to be deallocated
	 * @param n size of the array pointed to by p
	 */
	void deallocate(pointer p, size_type n) {
		if (p) {
			Alloc_traits::deallocate(m_allocator, p, n);
		}
	}
	
	
	/**
	 * @brief changes the size of the internal array to n
	 * @param new array size
	 */
	void reallocate(size_type n) {
		pointer new_start          = allocate(n);
		pointer new_end            = std::uninitialized_move(m_start, m_end, new_start);
		pointer new_end_of_storage = new_start + n;
		
		deallocate(m_start, m_end_of_storage - m_start);
		
		m_start          = new_start;
		m_end            = new_end;
		m_end_of_storage = new_end_of_storage;
	}
	
	void create_storage(size_type n) {
		m_start = allocate(n);
		m_end = m_start;
		m_end_of_storage = m_start + n;
	}
};


