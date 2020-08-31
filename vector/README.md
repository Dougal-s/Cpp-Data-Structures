# vector
Fully functional c++ vector

### Class Declaration
```c++
template <
	class T,
	size_t growth_factor = 2,
	class Allocator = std::allocator<T>
> class Vector;
```
### Member Types
| Member Type            | Definition                                           |
| ---------------------- | ---------------------------------------------------- |
| value_type             | T                                                    |
| allocator_type         | Allocator                                            |
| reference              | value_type&                                          |
| const_reference        | const value_type&                                    |
| pointer                | std::allocator_traits<allocator_type>::pointer       |
| const_pointer          | std::allocator_traits<allocator_type>::const_pointer |
| iterator               | T*                                                   |
| const_iterator         | const T*                                             |
| reverse_iterator       | std::reverse_iterator<iterator>                      |
| const_reverse_iterator | std::reverse_iterator<const_iterator>                |
| difference_type        | ptrdiff_t                                            |
| size_type              | size_t                                               |

### Member Functions
| Definition |  |
| - | - |
| `Vector()` | Constructs an empty vector |
| `explicit Vector(const allocator_type& alloc)` | Constructs an empty vector with the given allocator |
| `explicit Vector(size_t n, const allocator_type& alloc = allocator_type())` | Constructs the vector with n default constructed instances of T |
| `template <class InputIt> Vector(InputIt first, InputIt last, const allocator_type& alloc = allocator_type())` | Constructs the container with the contents of of the range [first, last) |
| `Vector(const Vector& x)` | Copy constructs the vector from x |
| `Vector(const Vector& x, const allocator_type& alloc)` | Copy constructs the vector from x with the allocator alloc |
| `Vector(Vector&& x)` | Move constructs the vector from x |
| `Vector(Vector&& x, const allocator_type& alloc)` | Move constructs the vector from x with the allocator alloc |
| `Vector(std::initializer_list<value_type> il, const allocator_type& alloc = allocator_type())` | Constructs the vector with the contents of il |
| `~Vector()` | Destructs the vector |
| | |
| `Vector& operator=(const Vector& x)` | Replaces the contents with using a copy assignment |
| `Vector& operator=(Vector&& x)` | Replaces the contents with using a move assignment|
| `Vector& operator=(std::initializer_list<value_type> il)` | Replaces the contents with the contents of il |
| | |
| `iterator begin()`<br>`const_iterator begin() const`<br>`const_iterator cbegin() const` | Returns an iterator to the start of the vector |
| `iterator end()`<br>`const_iterator end() const`<br>`const_iterator cend() const` | Returns an iterator pointing to one past the last element |
| `reverse_iterator rbegin()`<br>`const_reverse_iterator rbegin() const`<br>`const_reverse_iterator crbegin() const` | Returns a reverse iterator to the start of the vector |
| `reverse_iterator rend()`<br>`const_reverse_iterator rend() const`<br>`const_reverse_iterator crend() const` | Returns a reverse iterator pointing to one past the last element |
| | |
| `size_type size() const` | returns the size of the vector |
| `size_type max_size() const` | returns the maximum possible size of the vector |
| `void resize(size_type n)`<br>`void resize(size_type n, const value_type& val)` | resizes the vector to contain n elements |
| `size_type capacity() const` | returns the number of allocated elements |
| `bool empty() const` | returns true if the vector is empty |
| `void reserve(size_type n)` | increases the allocated capacity to hold n elements |
| `void shrink_to_fit()` | shrinks the allocated capacity to size() |
| | |
| `reference operator[](size_type n)`<br>`const_reference operator[](size_type n) const` | returns a reference to the nth element |
| `reference at(size_type n)`<br>`const_reference at(size_type n) const` | returns a reference to the nth element with bounds checking |
| `reference front()`<br>`const_reference front() const` | returns a reference to the first element |
| `reference back()`<br>`const_reference back() const` | returns a reference to the last element |
| `value_type* data()`<br>`const value_type* data() const` | returns a pointer to the beginning of array used internally |
| | |
| `template <class InputIt> void assign(InputIt first, InputIt last)` | replaces the contents with copies of the elements in range [first, last) |
| `void assign(size_type n, const value_type& val)` | replaces the contents with n copies of val |
| `void assign(std::initializer_list<value_type> il)` | replaces the contents with the contents of il |
| `void push_back(const value_type& val)`<br>`void push_back(value_type&& val)` | appends val to the end of the vector |
| `void pop_back()` | removes the last element in the vector |
| `iterator insert (const_iterator pos, const value_type& val)` | inserts a copy of val into the specified location |
| `iterator insert (const_iterator pos, size_type n, const value_type& val)` | inserts n instances of val into the specified location |
| `template <class InputIt> iterator insert (const_iterator pos, InputIt first, InputIt last)` | inserts the elements in range [first, last) into the specified location |
| `iterator insert (const_iterator pos, value_type&& val)` | moves val into the specified location |
| `iterator insert (const_iterator pos, std::initializer_list<value_type> il)` | inserts the contents of il into the specified location |
| `iterator erase(const_iterator pos)` | removes the specified element from the vector |
| `iterator erase(const_iterator first, const_iterator last)` | removes the elements in the range [first, last) from the vector |
| `void swap(Vector& x)` | swaps the contents of the vector with the contents of x |
| `void clear()` | removes all elements in the vector |
| `template <class... Args> iterator emplace(const_iterator pos, Args&&... args)` | constructs an element with arguments args at the specified position |
| `template <class... Args> iterator emplace_back(Args&&... args)` | constructs an element with arguments args at the end of the vector |
| `allocator_type get_allocator() const` | returns a copy of the allocator object used by the vector |

### Non-Member Functions
| Definition |  |
| - | - |
| `friend void swap(Vector& first, Vector& second)` | swaps the contents of the two vectors |


## Attribution
Much of the documentation is adapted from https://en.cppreference.com
