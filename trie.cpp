/**
 * Linked Trie
 */
 #include <utility>

namespace ds {

	template <class Digit, class T>
	struct Node {
		Digit* digit = nullptr;
		T* val = nullptr;
		Node<Digit, T>* parent = nullptr;
		Node<Digit, T>* child = nullptr;
		Node<Digit, T>* next = nullptr;
	};

	template <class Key, class T>
	class trie {
	public:
		typedef typename Key::value_type digit_type;
		typedef Node<digit_type, T> node_type;

		trie() {}

		trie(trie&& other) { this->swap(other); }

		trie& operator=(trie&& other) { this->swap(other); }

		T& at(const Key& key) {
			node_type* node = find(key);
			if (!node->val) { throw std::out_of_range("trie::at"); }
			return *node->val;
		}

		const T& at(const Key& key) const {
			node_type* node = find(key);
			if (!node->val) { throw std::out_of_range("trie::at"); }
			return *node->val;
		}

		T& operator[](const Key& key) {
			node_type* node = find(key);
			if (!node->val) { emplace(key); }
			return *find(key)->val;
		}

		node_type* top() { return &m_root; }

		bool empty() const { return m_root.child; }

		size_t size() const { return m_size; }

		void clear() {
			for (node_type* child = m_root.child; child;)
				child = destroy(child);

			m_size = 0;
		}

		node_type* insert(const Key& key, const T& val) { return emplace(key, val); }

		node_type* insert(const Key& key, T&& val) { return emplace(key, val); }

		template <class... Args>
		node_type* emplace(const Key& key, Args&&... args) {
			node_type* current = &m_root;
			for (const auto& digit : key) {
				node_type* parent = current;
				bool found = false;
				for (node_type* child = current->child; child; child = child->next) {
					if (*child->digit == digit) {
						current = child;
						found = true;
						break;
					}
				}

				if (!found) {
					current->child = new node_type{new digit_type(digit), nullptr, parent, nullptr, current->child};
					current = current->child;
				}
			}

			if (current->val)
				delete current->val;
			current->val = new T(std::forward<Args>(args)...);

			++m_size;

			return current;
		}

		void erase(node_type* node) {
			if (!node) throw std::invalid_argument("trie::erase");
			node_type* current = node;
			node_type* parent = current->parent;
			delete current->val;
			current->val = nullptr;
			while (parent && !current->child && !current->val) {
				delete current->digit;

				node_type before_begin = {nullptr, nullptr, nullptr, nullptr, parent->child};

				for (node_type *prev = &before_begin, *it = prev->next; it;) {
					if (it == current) {
						prev->next = current->next;
						delete current;
						parent->child = before_begin.next;
						break;
					}
					prev = it;
					it = it->next;
				}

				parent = parent->parent;
				current = parent;
			}
			--m_size;
		}

		void erase(const Key& key) { erase(find(key)); }

		void swap(trie& other) {
			std::swap(m_root, other.m_root);
			std::swap(m_size, other.m_size);
		}

		node_type* find(const Key& key) {
			node_type* current = &m_root;
			for (const auto& digit : key) {
				bool found = false;
				for (node_type* child = current->child; child; child = child->next) {
					if (*child->digit == digit) {
						current = child;
						found = true;
						break;
					}
				}

				if (!found) return nullptr;
			}

			return current;
		}

		const node_type* find(const Key& key) const {
			node_type* current = &m_root;
			for (const auto& digit : key) {
				bool found = false;
				for (node_type* child = current->child; child; child = child->next) {
					if (*child->digit == digit) {
						current = child;
						found = true;
						break;
					}
				}

				if (!found) return nullptr;
			}

			return current;
		}

		~trie() { clear(); }

	private:
		node_type m_root;
		size_t m_size;

		node_type* destroy(node_type* root) {
			for (node_type* child = root->child; child;) {
				child = destroy(child);
			}

			node_type* next = root->next;
			if (root->val)
				delete root->val;
			delete root->digit;
			delete root;
			return next;
		}
	};
}

namespace std {
	template <class Key, class T>
	void swap(ds::trie<Key, T>& lhs, ds::trie<Key, T>& rhs) {
		lhs.swap(rhs);
	}
}
