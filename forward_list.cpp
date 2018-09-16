/**
 * STL compliant c++ forward list
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

	Node() : next(), value() {}

	Node(Node* new_next) : next(new_next), value() {}

	Node* next;
	T* value;
};

// Iterator class

template <typename T>
class list_iterator {
public:

	// Member Classes

	using iterator_category = std::forward_iterator_tag;
	using value_type = T;
	using difference_type = ptrdiff_t;
	using pointer = value_type*;
	using reference = value_type&;
	
	// Member Functions
	
	// Constructors
	list_iterator() : m_node() {}
	
	explicit list_iterator(Node<value_type>* node) : m_node(node) {}
	
	list_iterator(const list_iterator& rhs) : m_node(rhs.m_node) {}
	
	
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
	
	value_type& operator*() {
		return *(m_node->value);
	}
	
	value_type* operator->() {
		return m_node.value;
	}
	
	bool operator==(list_iterator rhs) const {
		return m_node == rhs.m_node;
	}
	
	bool operator!=(list_iterator rhs) const {
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

template <typename T>
class list_const_iterator {
public:

	// Member Classes

	using iterator_category = std::forward_iterator_tag;
	using value_type = T;
	using difference_type = ptrdiff_t;
	using pointer = const value_type*;
	using reference = const value_type&;
	
	// Member Functions
	
	// Constructors
	list_const_iterator() : m_node() {}
	
	explicit list_const_iterator(Node<value_type>* node) : m_node(node) {}
	
	list_const_iterator(const list_iterator<value_type>& rhs) : m_node(rhs.m_node) {}
	
	list_const_iterator(const list_const_iterator& rhs) : m_node(rhs.m_node) {}
	
	
	// Destructor
	
	~list_const_iterator() = default;
	
	// Operators
	list_const_iterator& operator=(list_const_iterator&& rhs) {
		m_node = std::move(rhs.m_node);
		return *this;
	}
	
	list_const_iterator& operator=(const list_const_iterator& rhs) {
		m_node = rhs.m_node;
	}
	
	const value_type& operator*() const {
		return *(m_node->value);
	}
	
	list_const_iterator& operator++() {
		m_node = m_node->next;
		return *this;
	}
	
	list_const_iterator& operator++( int ) {
		list_iterator tmp(*this);
		m_node = m_node->next;
		return tmp;
	}
	
	value_type& operator*() {
		return *(m_node->value);
	}
	
	value_type* operator->() {
		return m_node.value;
	}
	
	bool operator==(list_const_iterator rhs) const {
		return m_node == rhs.m_node;
	}
	
	bool operator!=(list_const_iterator rhs) const {
		return m_node != rhs.m_node;
	}
	
	// Swap
	
	void swap(list_const_iterator& rhs) {
		std::swap(m_node, rhs.m_node);
	}
	
	friend void swap(list_const_iterator& lhs, list_const_iterator& rhs) {
		lhs.swap(rhs);
	}
	
private:
	const Node<value_type>* m_node;
};

template <typename T, typename Allocator = std::allocator<T>>
class Forward_list {

	using Alloc_traits = std::allocator_traits<Allocator>;
	using element_node = Node<T>;

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
	using const_iterator         = list_const_iterator<value_type>;

	// Member Functions
	
	
	
	Forward_list() : m_allocator() {
		m_head = new Node<value_type>;
	}
	
	explicit Forward_list(const allocator_type& alloc) : m_head(), m_allocator(alloc) {}
	
	Forward_list(size_type count, const value_type& val, const allocator_type& alloc) : m_allocator(alloc) {
		
	}
	
	explicit Forward_list(size_type count, const allocator_type& alloc = allocator_type()) : m_allocator(alloc) {
	
	}
	
	template <class InputIterator, class = typename std::enable_if<is_iterator<InputIterator>::value>::type>
	Forward_list(InputIterator first, InputIterator last, const allocator_type& alloc) : m_allocator(alloc) {
	
	}
	
	Forward_list(const Forward_list& other) : m_allocator() {
	
	}
	
	Forward_list(const Forward_list& other, const allocator_type& alloc) : m_allocator(alloc) {
	
	}
	
	Forward_list(Forward_list&& other) {
		m_head = other.m_head;
		m_allocator = other.m_allocator;
	}
	
	Forward_list(Forward_list&& other, const allocator_type& alloc) : m_allocator(alloc) {
		m_head = std::move(other.m_head);
		m_allocator = std::move(other.m_allocator);
	}
	
	Forward_list(std::initializer_list<value_type> il, const allocator_type& alloc = allocator_type()) : m_allocator(alloc) {
	
	}
	
	~Forward_list() {
		
	}
	
	Forward_list& operator=(const Forward_list& other) {
	
	}
	
	Forward_list& operator=(Forward_list&& other) {
		this->swap(other);
	}
	
	Forward_list& operator=(std::initializer_list<value_type> il) {
	
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
	
	// Iterators
	
	iterator before_begin() {
	
	}
	
	const_iterator before_begin() const {
	
	}
	
	const_iterator cbefore_begin() const {
	
	}
	
	iterator begin() {
		return iterator(m_head);
	}
	
	const_iterator begin() const {
		return const_iterator(m_head);
	}
	
	const_iterator cbegin() const {
		return const_iterator(m_head);
	}
	
	iterator end() {
		return nullptr;
	}
	
	const_iterator end() const {
	
	}
	
	const_iterator cend() const {
	
	}
	
	// Capacity
	
	bool empty() const {
		return m_head->next == nullptr;
	}
	
	size_type max_size() const {
		return Alloc_traits::max_size(m_allocator);
	}
	
	// Modifiers
	
	void clear() {
	
	}
	
	iterator insert_after(const_iterator pos, const value_type& val) {
	
	}
	
	iterator insert_after(const_iterator pos, value_type&& val) {
	
	}
	
	iterator insert_after(const_iterator pos, size_type count, const value_type& val) {
	
	}
	
	template <class InputIterator, class = typename std::enable_if<is_iterator<InputIterator>::value>::type>
	iterator insert_after(const_iterator pos, InputIterator first, InputIterator last) {
	
	}
	
	iterator insert_after(const_iterator pos, std::initializer_list<value_type> il) {
		
	}

	template <class... Args>
	iterator emplace_after(const_iterator pos, Args&&... args) {
	
	}
	
	iterator erase_after(const_iterator pos) {
	
	}
	
	iterator erase_after(const_iterator first, const_iterator last) {
		
	}
	
	void push_front(const value_type& val) {
		*(m_head->next) = Node(m_head->next);
		Alloc_traits::construct(m_allocator, m_head->next->value, val);
	}
	
	void push_front(value_type&& val) {
		m_head->next = new Node(m_head->next);
		//Alloc_traits::construct(m_allocator, m_head->next->value, std::move(val));
	}
	
	template <class... Args>
	reference emplace_front(Args&&... args) {
		*(m_head->next) = Node(m_head->next);
		Alloc_traits::construct(m_allocator, m_head->next->value, std::forward<Args>(args)...);
	}

	void pop_front() {
		
	}
	
	void resize(size_type count) {
	
	}
	
	void resize(size_type count, const value_type& val) {
	
	}
	
	void swap(Forward_list& other) {
	
	}
	
	// Operations
	
	void merge(Forward_list& other) {
	
	}
	
	void merge(Forward_list&& other) {
	
	}
	
	template <class Compare>
	void merge(Forward_list& other, Compare comp) {
	
	}
	
	template <class Compare>
	void merge(Forward_list&& other, Compare comp) {
	
	}
	
	void splice_after(const_iterator pos, Forward_list& other) {
	
	}
	
	void splice_after(const_iterator pos, Forward_list&& other) {
	
	}
	
	void splice_after( const_iterator pos, Forward_list& other, const_iterator it ) {
	
	}
                   
	void splice_after( const_iterator pos, Forward_list&& other, const_iterator it ) {
	
	}

	void splice_after( const_iterator pos, Forward_list& other, const_iterator first, const_iterator last ) {
	
	}

	void splice_after( const_iterator pos, Forward_list&& other, const_iterator first, const_iterator last ) {
	
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
	allocator_type m_allocator;
};

template< class T, class Alloc >
bool operator==( const Forward_list<T,Alloc>& lhs, const Forward_list<T,Alloc>& rhs ) {

}
                 
template< class T, class Alloc >
bool operator!=( const Forward_list<T,Alloc>& lhs, const Forward_list<T,Alloc>& rhs ) {

}
                 
template< class T, class Alloc >
bool operator<( const Forward_list<T,Alloc>& lhs, const Forward_list<T,Alloc>& rhs ) {

}
                
template< class T, class Alloc >
bool operator<=( const Forward_list<T,Alloc>& lhs, const Forward_list<T,Alloc>& rhs ) {

}
                 
template< class T, class Alloc >
bool operator>( const Forward_list<T,Alloc>& lhs, const Forward_list<T,Alloc>& rhs ) {

}
                
template< class T, class Alloc >
bool operator>=( const Forward_list<T,Alloc>& lhs, const Forward_list<T,Alloc>& rhs ) {

}

template< class T, class Alloc >
void swap( Forward_list<T,Alloc>& lhs, Forward_list<T,Alloc>& rhs ) {

}
