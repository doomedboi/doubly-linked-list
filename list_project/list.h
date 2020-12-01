#pragma once
//TODO: replace the original int type to template - based type
//then we will hold any type we ever want.
namespace nonstl {
	class list
	{
	private:
		struct Node
		{
			int m_val;
			Node* m_next, * m_prev;
			Node(int param) { m_next  = m_prev = nullptr; m_val = param; }
			~Node() { m_next = m_prev = nullptr; };

		};
		/*We do not use third-party header files. 
		If we want to use the initialization list and the compatibility of our iterator
		with the STL iterators, we need to connect additional headers. e.g. <iterator>, initializer_list*/
		class custom_iter {
			Node* _node;
		public:
			explicit custom_iter(Node* node = nullptr) : _node{ node } {}
			int operator*() const { if (_node) return _node->m_val; }
			custom_iter& operator++() {
				if (_node)
					_node = _node->m_next;
				return *this;
			}
			
			bool operator!=(const custom_iter& other) const { return _node != other._node; }
			bool operator==(const custom_iter& other) const { return !(*this != other); }
		};
		
		
	public: 
		Node  *m_head, * m_tail;
		size_t m_size = 0;

	private:
		// no increment and etc.
		list& operator++()				   = delete;
		list& operator--()				   = delete;
		list& operator*()				   = delete;
		list& operator+(const list& other) = delete;
	private:
		bool ishead(Node* node) const { return m_head == node; }
		bool istail(Node* node) const { return m_tail == node; }
		//removes selected node
		void remove(const Node* node)
		{
			if (node->m_prev)
				node->m_prev->m_next = node->m_next;
			else
				m_head = node->m_next;
			if (node->m_next)
				node->m_next->m_prev = node->m_prev;
			else
				m_tail = node->m_prev;
			m_size--;
			delete node;
			node = nullptr;
		}
		void swap(Node* _fir, Node* _sec)
		{
			if (_fir == _sec)
				return;

			auto oFirVal = _fir->m_val;
			_fir->m_val = _sec->m_val;
			_sec->m_val = oFirVal;

		}

	public:
		list()  { m_head = m_tail = nullptr; };
		~list() { clear(); };
		list(const list& other)
		{
			m_head = m_tail = nullptr;
			for (auto _Elem : other)
				push_back(_Elem);
		}	//+
		const list& operator=(const list& other)
		{
			if (this == &other)
				return *this;
			this->clear();
			for (auto _Elem : other)
				this->push_back(_Elem);
			return *this;
		}
		
		custom_iter begin() const { return  custom_iter{ m_head }; }
		custom_iter end()   const { return  custom_iter{ m_tail->m_next }; }
		
		bool empty() const 
		{ 
			return m_size == 0; 
		}
		size_t size() const
		{
			return m_size;
		}
		
		void clear()
		{
			while (m_head) {
				auto tmp = m_head;
				m_head = m_head->m_next;
				delete tmp;
			}
			m_size = 0;
		}
		//+
		void pop_back()
		{
			if (m_tail) {
				auto tmp = m_tail;
				m_tail = m_tail->m_prev;
				if (m_tail)
					m_tail->m_next = nullptr;
				else
					m_head = nullptr;
				delete tmp;
			}
			m_size -= 1;
		}
		//+
		void pop_front()
		{
			if (m_head) {
				auto tmp = m_head;
				m_head = m_head->m_next;
				if (m_head)
					m_head->m_prev = nullptr;
				else
					m_tail = nullptr;
				delete tmp;
			}
			m_size -= 1;
		}
		// +
		void push_front(int val) {
			auto elem = new Node(val);
			elem->m_prev = nullptr;
			elem->m_next = m_head;
			if (m_head)
				m_head->m_prev = elem;
			else
				m_tail = elem;
			m_head = elem;
			m_size++;
		}
		// +
		void push_back(int val) {
			auto elem = new Node(val);
			elem->m_prev = m_tail;
			elem->m_next = nullptr;
			if (m_tail)
				m_tail->m_next = elem;
			else
				m_head = elem;
			m_tail = elem;
			m_size++;
		}
		// + doesn't any secure checks
		void insert(const size_t idx, int val) {
			size_t i{ 0 }; auto tmp = m_head;
			for (; tmp && i < idx; tmp = tmp->m_next, i++)
				;
			if (!tmp)
				return;

			m_size++;
			if (!tmp->m_next) {
				push_back(val);
				return;
			}
			if (!tmp->m_prev) {
				push_front(val);
				return;
			}
			auto node		= new Node(val);
			node->m_next		= tmp;
			node->m_prev		= tmp->m_prev;
			tmp->m_prev->m_next = node;
			tmp->m_prev		= node;	
		}

		// + original causes unbeh if tail doesn't exist
		int& back() { return m_tail->m_val; }
		// +
		int const& back() const { return m_tail->m_val; }
		// +
		int& front() { return m_head->m_val; }
		// +
		int const& front() const { return m_head->m_val; }
		// +
		template <class predict>
		void remove_if(predict pred)
		{
			auto _last = m_head;
			while (_last) {
				auto tmp = _last;
				if (pred(_last->m_val)) {
					_last = _last->m_next;
					remove(tmp);
				} else	
					_last = _last->m_next;
			}
		}
		//+
		void remove(const int& _elem)
		{
			remove_if([&](int x) {return x == _elem; });
		}
		// +
		void remove_after(const Node* node)
		{
			if (node->m_next)
				remove(node->m_next);
		}
		// +
		void remove_before(const Node* node)
		{
			if (node->m_prev)
				remove(node->m_prev);
		}
		// +
		int  findf(const int& _Elem)
		{
			size_t i{ 0 };
			for (auto _begin = begin(); _begin != end(); ++_begin, i++)
				if (*_begin == _Elem)
					return i;
			return -1;
		}
		// +
		void insert_after(Node* node, const int& _Elem)
		{
			if (istail(node))
				push_back(_Elem);
			else {
				auto nElem  = new Node{ _Elem };
				nElem->m_prev = node;
				nElem->m_next = node->m_next;
				node->m_next  = nElem;
				m_size++;
			}
		}
		// +
		void insert_before(Node* node, const int& _Elem)
		{
			if (ishead(node))
				push_front(_Elem);
			else 
				insert_after(node->m_prev, _Elem);
		}
		// +
		void erase(size_t idx)
		{
			size_t i = 0;
			auto _begin = m_head;
			for (i = 0; i < idx && _begin; _begin = _begin->m_next, i++)
				;
			if (!_begin)
				return;
			remove(_begin);
		}
		//param 1: stream | param 2: sep
		template <class stream, class separator>
		void print(stream& _Io, const separator& _Sep) {
			for (auto elem : *this)
				_Io << elem << _Sep;
		}
		//
		void swap(list& other)
		{
			auto _tmpHead = this->m_head;
			auto _tmpTail = this->m_tail;
			this->m_head  = other.m_head;
			this->m_tail  = other.m_tail;
			other.m_head  = _tmpHead;
			other.m_tail  = _tmpTail;
		}
		
		// insert sort-based sort
		template <class _Predict >
		void sort(_Predict _Pred)
		{
			auto _begin = m_head->m_next;
			for (; _begin; _begin = _begin->m_next) {
				auto _sorFornode = _begin;
				while (_sorFornode->m_prev && _Pred(_sorFornode->m_prev->m_val, _sorFornode->m_val)) {
					swap(_sorFornode, _sorFornode->m_prev);
					_sorFornode = _sorFornode->m_prev;
				}
			}
		}
	};


}



	
