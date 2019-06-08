/**
 * Array based binary heap
 */
#include <cstddef>
#include <initializer_list>
#include <iterator>
#include <utility>
#include <vector>

namespace ds {
	template <typename Iterator>
	void up_heap(Iterator first, Iterator last) {
		const size_t size = std::distance(first, last);
		for (size_t index = size; index > 1 && first[index/2-1] < first[index-1]; index /= 2)
			std::swap(first[index/2-1], first[index-1]);
	}

	template <typename Iterator>
	void down_heap(Iterator first, Iterator last) {
		const size_t size = std::distance(first, last);
		size_t index = 1;
		while (2*index < size) {
			const size_t max_child = first[2*index-1] < first[2*index] ? 2*index : 2*index-1;
			if (first[max_child] < first[index-1]) {break;}
			std::swap(first[max_child], first[index-1]);
			index = max_child+1;
		}

		if (2*index == size && first[index-1] < first[2*index-1])
			std::swap(first[index-1], first[2*index-1]);
	}

	template<typename Iterator>
	void make_heap(Iterator first, Iterator last) {
		for (Iterator back = first; back != last;)
			ds::up_heap(first, ++back);
	}

	template<typename Iterator>
	void sort_heap(Iterator first, Iterator last) {
		for (Iterator back = last; back != first;) {
			std::swap(*first, *--back);
			ds::down_heap(first, back);
		}
	}

	template<typename Iterator>
	void heap_sort(Iterator first, Iterator last) {
		ds::make_heap(first, last);
		ds::sort_heap(first, last);
	}

	template<typename T, typename Container = std::vector<T>>
	class binary_heap {
	public:
		typedef typename Container::value_type value_type;
		typedef typename Container::size_type size_type;
		typedef typename Container::difference_type difference_type;
		typedef typename Container::reference reference;
		typedef typename Container::const_reference const_reference;
		typedef typename Container::pointer pointer;
		typedef typename Container::const_pointer const_pointer;
		typedef typename Container::iterator iterator;
		typedef typename Container::const_iterator const_iterator;
		typedef typename Container::reverse_iterator reverse_iterator;
		typedef typename Container::const_reverse_iterator const_reverse_iterator;

		// Constructors, Destructors and Assignment

		binary_heap() = default;

		explicit binary_heap(size_type n) : m_data(n) {}

		binary_heap(size_type n, const T& value) : m_data(n, value) {}

		template<typename Iterator>
		binary_heap(Iterator first, Iterator last) : m_data(first, last) {
			ds::make_heap(m_data.begin(), m_data.end());
		}

		binary_heap(const binary_heap& other) : m_data(other.m_data) {}

		binary_heap(binary_heap&& other) : m_data(other.m_data) {}

		binary_heap(std::initializer_list<T> il) : m_data(il) {
			ds::make_heap(m_data.begin(), m_data.end());
		}

		binary_heap(Container&& cont) : m_data(cont) {
			ds::make_heap(m_data.begin(), m_data.end());
		}

		~binary_heap() = default;

		binary_heap& operator=(const binary_heap& other) {
			m_data = other.m_data;
			return *this;
		}

		binary_heap& operator=(binary_heap&& other) {
			m_data = std::move(other.m_data);
		}

		binary_heap& operator=(std::initializer_list<T> il) {
			m_data = il;
			ds::make_heap(m_data.begin(), m_data.end());
		}

		template<typename Iterator>
		void assign(Iterator first, Iterator last) {
			m_data.assign(first, last);
			ds::make_heap(m_data.begin(), m_data.end());
		}

		void assign(std::initializer_list<T> il) {
			m_data = il;
			ds::make_heap(m_data.begin(), m_data.end());
		}

		// Element access

		reference at(size_type pos) {
			return m_data.at(pos);
		}

		const_reference at(size_type pos) const {
			return m_data.at(pos);
		}

		reference operator[](size_type pos) {
			return m_data[pos];
		}

		const_reference operator[](size_type pos) const {
			return m_data[pos];
		}

		reference top() {
			return m_data.front();
		}

		const_reference top() const {
			return m_data.front();
		}

		T* data() {
			return m_data.data();
		}

		const T* data() const {
			return m_data.data();
		}

		// Iterators

		iterator begin() {
			return m_data.begin();
		}

		const_iterator begin() const {
			return m_data.begin();
		}

		const_iterator cbegin() const {
			return m_data.cbegin();
		}

		iterator end() {
			return m_data.end();
		}

		const_iterator end() const {
			return m_data.end();
		}

		const_iterator cend() const {
			return m_data.cend();
		}

		reverse_iterator rbegin() {
			return m_data.rbegin();
		}

		const_reverse_iterator rbegin() const {
			return m_data.rbegin();
		}

		const_reverse_iterator crbegin() const {
			return m_data.crbegin();
		}

		reverse_iterator rend() {
			return m_data.rend();
		}

		const_reverse_iterator rend() const {
			return m_data.rend();
		}

		const_reverse_iterator crend() const {
			return m_data.crend();
		}

		// Capacity

		bool empty() const {
			return m_data.empty();
		}

		size_type size() const {
			return m_data.size();
		}

		size_type max_size() const {
			return m_data.max_size();
		}

		size_type height() const {
			return ceil(log2(size()+1));
		}

		void reserve(size_type new_cap) {
			m_data.reserve(new_cap);
		}

		size_type capacity() const {
			return m_data.capacity();
		}

		void shrink_to_fit() {
			m_data.shrink_to_fit();
		}

		// Modifiers

		void clear() {
			m_data.clear();
		}

		void push(const value_type& val) {
			m_data.push_back(val);
			ds::up_heap(m_data.begin(), m_data.end());
		}

		template <class... Args>
		void emplace(Args&&... args) {
			m_data.emplace_back(std::forward<Args>(args)...);
			ds::up_heap(m_data.begin(), m_data.end());
		}

		value_type pop() {
			value_type returnVal = std::move(m_data.front());
			std::swap(m_data.front(), m_data.back());
			m_data.pop_back();
			ds::down_heap(m_data.begin(), m_data.end());
			return returnVal;
		}

		void resize(size_type new_size) {
			m_data.resize(new_size);
		}

		void swap(binary_heap& other) {
			std::swap(m_data, other.m_data);
		}

	private:
		Container m_data;
	};
}

namespace std {
	template<class T>
	void swap(ds::binary_heap<T>& lhs, ds::binary_heap<T>& rhs) {
		lhs.swap(rhs);
	}
}
