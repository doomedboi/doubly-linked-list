#pragma once




namespace list {
	class list
	{
	private:
		struct Node
		{
			int val;
			Node* next, * prev;
			Node(int param) { next = prev = nullptr; val = param; }
			~Node() { next = prev = nullptr; };

		};

		class custom_iter {
			Node* _node;
		public:
			explicit custom_iter(Node* node = nullptr) : _node{ node } {}
			int operator*() const { if (_node) return _node->val; }
			custom_iter& operator++() {
				if (_node)
					_node = _node->next;
				return *this;
			}
			bool operator!=(const custom_iter& other) const { return _node != other._node; }
			bool operator==(const custom_iter& other) const { !(*this != other); }
		};

	public: 
		Node* head, * tail;
		size_t _size = 0;

	private:
		bool isborder(Node* node) const { return head == node || tail == node; }
		bool ishead(Node* node)   const { return head == node; }
		bool istail(Node* node)   const { return tail == node; }
		//remove selected node
		void remove(const Node* node)
		{
			if (node->prev)
				node->prev->next = node->next;
			else
				head = node->next;
			if (node->next)
				node->next->prev = node->prev;
			else
				tail = node->prev;
			_size--;
			delete node;
			node = nullptr;
		}
	public:
		list() { head = tail = nullptr; };
		~list() { destroy(); };


		custom_iter begin() const { return custom_iter{ head }; }
		custom_iter end()   const { return  custom_iter{ tail->next }; }
		
		//+
		bool empty() const 
		{ 
			return _size == 0; 
		}
		size_t size() const
		{
			return _size;
		}
		//+
		void destroy()
		{
			while (head) {
				auto tmp = head;
				head = head->next;
				delete tmp;
			}
			_size = 0;
		}
		//+
		void pop_back()
		{
			if (tail) {
				auto tmp = tail;
				tail = tail->prev;
				if (tail)
					tail->next = nullptr;
				else
					head = nullptr;
				delete tmp;
			}
			_size -= 1;
		}
		//+
		void pop_front()
		{
			if (head) {
				auto tmp = head;
				head = head->next;
				if (head)
					head->prev = nullptr;
				else
					tail = nullptr;
				delete tmp;
			}
			_size -= 1;
		}
		// +
		void push_front(int val) {
			auto elem = new Node(val);
			elem->prev = nullptr;
			elem->next = head;
			if (head)
				head->prev = elem;
			else
				tail = elem;
			head = elem;
			_size++;
		}
		// +
		void push_back(int val) {
			auto elem = new Node(val);
			elem->prev = tail;
			elem->next = nullptr;
			if (tail)
				tail->next = elem;
			else
				head = elem;
			tail = elem;
			_size++;
		}
		// + doesn't any secure checks
		void insert(const size_t idx, int val) {
			size_t i{ 0 }; auto tmp = head;
			for (; tmp && i < idx; tmp = tmp->next, i++)
				;
			if (!tmp)
				return;

			_size++;
			if (!tmp->next) {
				push_back(val);
				return;
			}
			if (!tmp->prev) {
				push_front(val);
				return;
			}
			auto node		= new Node(val);
			node->next		= tmp;
			node->prev		= tmp->prev;
			tmp->prev->next = node;
			tmp->prev		= node;	
		}

		// + original causes unbeh if tail doesn't exist
		int& back() { return tail->val; }
		//+
		int const& back() const { return tail->val; }
		//+
		int& front() { return head->val; }
		//+
		int const& front() const { return head->val; }
		//+
		template <class predict>
		void remove_if(predict pred)
		{
			auto _last = head;
			while (_last) {
				auto tmp = _last;
				if (pred(_last->val)) {
					_last = _last->next;
					remove(tmp);
				} else	
					_last = _last->next;
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
			if (node->next)
				remove(node->next);
		}
		// +
		void remove_before(const Node* node)
		{
			if (node->prev)
				remove(node->prev);
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
				nElem->prev = node;
				nElem->next = node->next;
				node->next  = nElem;
				_size++;
			}
		}
		// +
		void insert_before(Node* node, const int& _Elem)
		{
			if (ishead(node))
				push_front(_Elem);
			else 
				insert_after(node->prev, _Elem);
		}
		//param 1: stream | param 2: sep
		template <class stream, class separator>
		void print(stream& _Io, const separator& _Sep) {
			for (auto elem : *this)
				_Io << elem << _Sep;
		}
	};

}