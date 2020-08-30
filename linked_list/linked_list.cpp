/**
 * STL compliant c++ linked list
 *
 * @author Dougal Stewart
 * @version 0.1 18/8/18
 */

#include <stddef.h>
#include <memory>
#include <initializer_list>
#include <iterator>
#include <utility>
 
template<typename T, typename = void>
struct is_iterator {
   static constexpr bool value = false;
};

template<typename T>
struct is_iterator<T, typename std::enable_if<!std::is_same<typename std::iterator_traits<T>::value_type, void>::value>::type> {
   static constexpr bool value = true;
};

template<typename T>
struct Node {
	Node* next;
	Node* previous;
	T* value;
};

// Iterator class

template <typename T>
class list_iterator {
public:

	// Member Classes

	using iterator_category = std::bidirectional_iterator_tag;
	using value_type = T;
	using difference_type = ptrdiff_t;
	using pointer = value_type*;
	using reference = value_type&;
	
	// Member Functions
	
	// Constructors
	list_iterator() : m_node() {}
	
	list_iterator(list_iterator&& rhs) : m_node(std::move(rhs.m_node)) {}
	
	list_iterator(const list_iterator& rhs) : m_node(rhs.m_node) {}
	
	list_iterator(const Node<value_type>* rhs) : m_node(rhs) {}
	
	
	// Destructor
	
	~list_iterator() = default;
	
	// Operators
	list_iterator& operator=(list_iterator&& rhs) {
		m_node = std::move(rhs.m_node);
		return *this;
	}
	
	list_iterator& operator=(const list_iterator& rhs) {
		m_node = rhs.m_node;
	}
	
	const value_type& operator*() const {
		return *(m_node->value);
	}
	
	list_iterator& operator++() {
		m_node = m_node->next;
		return *this;
	}
	
	list_iterator& operator++( int ) {
		list_iterator tmp(*this);
		m_node = m_node->next;
		return tmp;
	}
	
	list_iterator& operator--() {
		m_node = m_node->previous;
		return *this;
	}
	
	list_iterator& operator--( int ) {
		list_iterator tmp(this);
		m_node = m_node->previous;
		return tmp;
	}
	
	reference operator*() {
		return *(m_node->value);
	}
	
	reference operator->() {
		return m_node.value;
	}
	
	bool operator==(const list_iterator& rhs) const {
		return m_node == rhs.m_node;
	}
	
	bool operator!=(const list_iterator& rhs) const {
		return m_node != rhs.m_node;
	}
	
	// Swap
	
	void swap(list_iterator& rhs) {
		std::swap(m_node, rhs.m_node);
	}
	
	friend void swap(list_iterator& lhs, list_iterator& rhs) {
		lhs.swap(rhs);
	}
	
private:
	Node<value_type>* m_node;
};

template <typename T, typename Allocator = std::allocator<T>>
class List {
public:

	// Member Classes

	using value_type             = T;
	using allocator_type         = Allocator;
	using size_type              = size_t;
	using difference_type        = ptrdiff_t;
	using reference              = value_type&;
	using const_reference        = const value_type&;
	using pointer                = typename std::allocator_traits<allocator_type>::pointer;
	using const_pointer          = typename std::allocator_traits<allocator_type>::const_pointer;
	using iterator               = list_iterator<value_type>;
	using const_iterator         = list_iterator<const value_type>;
	using reverse_iterator       = std::reverse_iterator<iterator>;
	using const_reverse_iterator = std::reverse_iterator<const_iterator>;

	// Member Functions
	
	List() : m_head(), m_end(), m_size(), m_allocator() {}
	
	explicit List(const allocator_type& alloc) : m_head(), m_end(), m_size(), m_allocator(alloc) {}
	
	List(size_type count, const value_type& val, const allocator_type& alloc) : m_allocator(alloc) {
		
	}
	
	explicit List(size_type count, const allocator_type& alloc = allocator_type()) : m_allocator(alloc) {
	
	}
	
	template <class InputIterator, class = typename std::enable_if<is_iterator<InputIterator>::value>::type>
	List(InputIterator first, InputIterator last, const allocator_type& alloc) : m_allocator(alloc) {
	
	}
	
	List(const List& other) : m_allocator() {
	
	}
	
	List(const List& other, const allocator_type& alloc) : m_allocator(alloc) {
	
	}
	
	List(List&& other) : m_allocator() {
	
	}
	
	List(List&& other, const allocator_type& alloc) : m_allocator(alloc) {
	
	}
	
	List(std::initializer_list<value_type> il, const allocator_type& alloc = allocator_type()) : m_allocator(alloc) {
	
	}
	
	~List() {
	
	}
	
	List& operator=(const List& other) {
		
	}
	
	List& operator=(List&& other) {
	
	}
	
	List& operator=(std::initializer_list<value_type> il) {
	
	}
	
	void assign(size_type count, const value_type& val) {
	
	}
	
	template <class InputIterator, class = typename std::enable_if<is_iterator<InputIterator>::value>::type>
	void assign(InputIterator first, InputIterator last) {
	
	}
	
	void assign(std::initializer_list<value_type> il) {
	
	}
	
	allocator_type get_allocator() const {
		return m_allocator;
	}
	
	// Element Access
	
	reference front() {
	
	}
	
	const_reference front() const {
	
	}
	
	reference back() {
	
	}
	
	const_reference back() const {
	
	}
	
	// Iterators
	
	iterator begin() {
	
	}
	
	const_iterator begin() const {
	
	}
	
	const_iterator cbegin() const {
	
	}
	
	iterator end() {
	
	}
	
	const_iterator end() const {
		
	}
	
	const_iterator cend() const {
		
	}

	reverse_iterator rbegin() {
	
	}
	
	const_reverse_iterator rbegin() const {
	
	}
	
	const_reverse_iterator crbegin() const {
	
	}
	
	reverse_iterator rend() {
	
	}

	const_reverse_iterator rend() const {
	
	}
	
	const_reverse_iterator crend() const {
	
	}
	
	// Capacity
	
	bool empty() const {
		return m_head == m_end;
	}
	
	size_type size() const {
		return m_size;
	}
	
	size_type max_size() const {
	
	}
	
	// Modifiers
	
	void clear() {
	
	}
	
	iterator insert(const_iterator pos, const value_type& val) {
	
	}
	
	iterator insert(const_iterator pos, value_type&& val) {
	
	}
	
	iterator insert(const_iterator pos, size_type count, const value_type&) {
	
	}
	
	template <class InputIterator, class = typename std::enable_if<is_iterator<InputIterator>::value>::type>
	iterator insert(const_iterator pos, InputIterator first, InputIterator last) {
	
	}
	
	iterator insert(const_iterator pos, std::initializer_list<value_type> il) {
	
	}
	
	template <class... Args>
	iterator emplace(const_iterator pos, Args&&... args) {
	
	}
	
	iterator erase(const_iterator pos) {
	
	}
	
	iterator erase(const_iterator first, const_iterator last) {
	
	}
	
	void push_back(const value_type& val) {
	
	}

	void push_back(value_type&& val) {
	
	}
	
	template <class... Args>
	reference emplace_back(Args&&... args) {
	
	}
	
	void pop_back() {
	
	}

	void push_front(const value_type& val) {
	
	}
	
	void push_front(value_type&& val) {
	
	}
	
	template <class... Args>
	reference emplace_front(Args&&... args) {
	
	}
	
	void pop_front() {
	
	}
	
	void resize(size_type count) {
	
	}
	
	void resize(size_type count, const value_type& val) {
	
	}
	
	void swap(List& other) {
		std::swap(this->m_head, other.m_head);
		std::swap(this->m_end, other.m_end);
		std::swap(this->m_size, other.m_size);
	}
	
	// Operations
	
	void merge(List& other) {
	
	}
	
	void merge(List&& other) {
	
	}
	
	template <class Compare>
	void merge(List& other, Compare comp) {
	
	}
	
	template <class Compare>
	void merge(List&& other, Compare comp) {
	
	}
	
	void splice(const_iterator pos, List& other) {
	
	}
	
	void splice(const_iterator pos, List&& other) {
	
	}
	
	void splice(const_iterator pos, List& other, const_iterator it) {
	
	}
	
	void splice(const_iterator pos, List&& other, const_iterator it) {
	
	}
	
	void splice(const_iterator pos, List& other, const_iterator first, const_iterator last) {
	
	}
	
	void splice(const_iterator pos, List&& other, const_iterator first, const_iterator last) {
	
	}
	
	size_type remove(const value_type& val) {
	
	}
	
	template <class UnaryPredicate>
	size_type remove_if(UnaryPredicate p) {
	
	}
	
	void reverse() {
	
	}

	size_type unique() {
	
	}
	
	template <class BinaryPredicate>
	size_type unique(BinaryPredicate p) {
	
	}
	
	void sort() {
	
	}
	
	template <class Compare>
	void sort(Compare comp) {
	
	}
	
private:
	Node<value_type>* m_head;
	Node<value_type>* m_end;
	size_type m_size;
	allocator_type m_allocator;
	
};

template< class T, class Alloc >
bool operator==( const List<T,Alloc>& lhs, const List<T,Alloc>& rhs ) {

}

template< class T, class Alloc >
bool operator!=( const List<T,Alloc>& lhs, const List<T,Alloc>& rhs ) {

}

template< class T, class Alloc >
bool operator<( const List<T,Alloc>& lhs, const List<T,Alloc>& rhs ) {

}

template< class T, class Alloc >
bool operator<=( const List<T,Alloc>& lhs, const List<T,Alloc>& rhs ) {

}

template< class T, class Alloc >
bool operator>( const List<T,Alloc>& lhs, const List<T,Alloc>& rhs ) {

}

template< class T, class Alloc >
bool operator>=( const List<T,Alloc>& lhs, const List<T,Alloc>& rhs ) {

}

template < class T, class Alloc >
void swap(List<T,Alloc>& lhs, List<T, Alloc>& rhs) {

}
