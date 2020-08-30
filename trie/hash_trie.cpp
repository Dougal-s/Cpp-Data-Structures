/**
 * Linked hash trie
 */
 #include <utility>
 #include <functional>
 #include <stdexcept>

namespace ds {

	template <class T>
	struct Node {
		T* val = nullptr;
		Node<T>* parent = nullptr;
		Node<T>* l_child = nullptr;
		Node<T>* r_child = nullptr;
	};

	template <class Key, class T>
	class hash_trie {
	public:
		typedef Node<T> node_type;

		hash_trie() {}

		hash_trie(hash_trie&& other) { this->swap(other); }

		hash_trie& operator=(hash_trie&& other) { this->swap(other); }

		T& at(const Key& key) {
			node_type* node = find(key);
			if (!node->val) { throw std::out_of_range("ds::hash_trie::at"); }
			return *node->val;
		}

		const T& at(const Key& key) const {
			node_type* node = find(key);
			if (!node->val) { throw std::out_of_range("ds::hash_trie::at"); }
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
			destroy(m_root.l_child);
			destroy(m_root.r_child);
			m_size = 0;
		}

		node_type* insert(const Key& key, const T& val) { return emplace(key, val); }

		node_type* insert(const Key& key, T&& val) { return emplace(key, val); }

		template <class... Args>
		node_type* emplace(const Key& key, Args&&... args) {
			node_type* current = &m_root;
			for (size_t hashed = std::hash<Key>{}(key); hashed; hashed >>= 1) {
				node_type*& child = (hashed&1) ? current->r_child : current->l_child;
				if (!child) child = new node_type();
				current = child;
			}
			current->val = new T(std::forward<Args>(args)...);
			++m_size;

			return current;
		}

		void erase(node_type* node) {
			if (!node) throw std::invalid_argument("ds::hash_trie::erase");
			while (!(node->l_child && node->r_child) && !node->val)
				node = node->parent;

			if (node->parent->l_child == node)
				node->parent->l_child = nullptr;
			else
				node->parent->r_child = nullptr;

			destroy(node);

			--m_size;
		}

		void erase(const Key& key) { erase(find(key)); }

		void swap(hash_trie& other) {
			std::swap(m_root, other.m_root);
			std::swap(m_size, other.m_size);
		}

		node_type* find(const Key& key) {
			node_type* current = &m_root;
			for (size_t hashed = std::hash<Key>{}(key); hashed && current; hashed >>= 1)
				current = (hashed&1) ? current->r_child : current->l_child;
			return current;
		}

		const node_type* find(const Key& key) const {
			node_type* current = &m_root;
			for (size_t hashed = std::hash<Key>{}(key); hashed && current; hashed >>= 1)
				current = (hashed&1) ? current->r_child : current->l_child;
			return current;
		}

		~hash_trie() { clear(); }

	private:
		node_type m_root;
		size_t m_size;

		void destroy(node_type* root) {
			if (!root) return;
			destroy(root->l_child);
			destroy(root->r_child);

			if (root->val)
				delete root->val;
			delete root;
		}
	};
}

namespace std {
	template <class Key, class T>
	void swap(ds::hash_trie<Key, T>& lhs, ds::hash_trie<Key, T>& rhs) {
		lhs.swap(rhs);
	}
}
