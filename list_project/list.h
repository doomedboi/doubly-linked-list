#pragma once
namespace nonstl {
	template <class _Ty>
	class list
	{
	private:	 //
		struct Node
		{
			_Ty m_val;
			Node* m_next, * m_prev;
			Node(_Ty param) { m_next  = m_prev = nullptr; m_val = param; }
			~Node() { m_next = m_prev = nullptr; };

		};
		/*We do not use third-party header files. 
		If we want to use the initialization list and the compatibility of our iterator
		with the STL iterators, we need to include additional headers. e.g. <iterator>, initializer_list*/
		
		class custom_iter { //: public std::iterator<std::forward_iterator_tag, _Ty&> {
			Node* _node;
			Node* GetNode() { return _node; }
		public:
			explicit custom_iter(Node* node = nullptr) : _node{ node } {}
			_Ty operator*() const { if (_node) return _node->m_val; }
			custom_iter& operator++() {
				if (_node)
					_node = _node->m_next;
				return *this;
			}
			
			bool operator!=(const custom_iter& other) const { return _node != other._node; }
			bool operator==(const custom_iter& other) const { return !(*this != other); }
			
			friend class list<_Ty>;
		};
		
		
	private: 
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
		Node* forTailIter(	custom_iter _Iter) {
			Node* _node = _Iter.GetNode();
			if (!_node)
				_node = m_tail;

			return _node;
		}
		//removes selected node
		void remove(Node* _node)
		{
			
			if (_node->m_prev)
				_node->m_prev->m_next = _node->m_next;
			else
				m_head = _node->m_next;
			if (_node->m_next)
				_node->m_next->m_prev = _node->m_prev;
			else
				m_tail = _node->m_prev;
			m_size--;
			delete _node;
		}
		void swap(Node* _fir, Node* _sec)
		{
			if (_fir == _sec)
				return;

			auto oFirVal = _fir->m_val;
			_fir->m_val = _sec->m_val;
			_sec->m_val = oFirVal;
		}
		void insert_after(Node* _Node, const _Ty& _Elem)
		{
			if (istail(_Node))
				push_back(_Elem);
			else {
				auto nElem = new Node{ _Elem };
				nElem->m_prev = _Node;
				nElem->m_next = _Node->m_next;
				_Node->m_next->m_prev = nElem;
				_Node->m_next = nElem;
				m_size++;
			}
		}
		// ++
		void insert_before(Node* _Node, const _Ty& _Elem)
		{
			if (ishead(_Node))
				push_front(_Elem);
			else
				insert_after(_Node->m_prev, _Elem);
		}
		// ++
		void remove_after(const Node* _Node)
		{
			if (_Node->m_next)
				remove(_Node->m_next);
		}
		// ++
		void remove_before(const Node* _Node)
		{
			if (_Node->m_prev)
				remove(_Node->m_prev);
		}

	public:
		list()  { m_head = m_tail = nullptr; m_size = 0; };
		~list() { clear(); };
		list(const list& other)
		{
			m_head = m_tail = nullptr;
			if (other.size() == 0)
				return;

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
		custom_iter end()   const {
			if (!m_tail)
				return custom_iter{ m_tail };
			else
				return custom_iter{ m_tail->m_next };
		}
		
		bool empty() const 
		{ 
			return m_size == 0; 
		}
		size_t size() const
		{
			return m_size;
		}
		//++
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
			remove(m_tail);
		}
		//+
		void pop_front()
		{
			remove(m_head);
		}
		// +
		void push_front(_Ty _Val) {
			auto elem = new Node(_Val);
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
		void push_back(_Ty _Val) {
			auto elem = new Node(_Val);
			elem->m_prev = m_tail;
			elem->m_next = nullptr;
			if (m_tail)
				m_tail->m_next = elem;
			else
				m_head = elem;
			m_tail = elem;
			m_size++;
		}

		// updated
		void remove_after(custom_iter _Iter)
		{
			if (!_Iter.GetNode())
				return;
			remove(_Iter.GetNode()->m_next);
		}
		// updated
		void remove_before(custom_iter _Iter)
		{
			if (_Iter == this->begin())
				return;
			remove(forTailIter(_Iter)->m_prev);
		}
		// ++
		void insert(custom_iter _Iter, _Ty _Val) 
		{
			insert_before(forTailIter(_Iter), _Val);
		}

		// ++ original causes unbeh if tail doesn't exist
		_Ty& back() { return m_tail->m_val; }
		// ++
		_Ty const& back() const { return m_tail->m_val; }
		// ++
		_Ty& front() { return m_head->m_val; }
		// ++
		_Ty const& front() const { return m_head->m_val; }
		// updated remove by prediction (lambda | pointer to function)
		template <class predict>
		void remove_if(predict _Pred)
		{
			auto _last = m_head;
			while (_last) {
				auto tmp = _last;
				if (_Pred(_last->m_val)) {
					_last = _last->m_next;
					remove(tmp);
				} else	
					_last = _last->m_next;
			}
		}
		//++
		void remove(const _Ty& _Elem)
		{
			remove_if([&](_Ty x) {return x == _Elem; });
		}
		// ++
		
		// updated return iterator ( resulting or null )
		custom_iter find(const _Ty& _Elem)
		{
			for (auto _begin = begin(); _begin != end(); ++_begin)
				if (*_begin == _Elem)
					return _begin;
			return custom_iter();
		}
		// ++
		
		// updated
		void insert_after(custom_iter _Iter, const _Ty _Elem)
		{
			insert_after(forTailIter(_Iter), _Elem);
		}
		// updated
		void insert_before(custom_iter _Iter, const _Ty _Elem)
		{
			insert_before(forTailIter(_Iter), _Elem);
		}
		// updated
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
		// updated
		void erase(custom_iter _Iter)
		{
			remove(forTailIter(_Iter));
		}
		// think about that
		void erase(custom_iter _First, custom_iter _Last)
		{
			if (_First == _Last) {
				erase(_First);
				return;
			}
			//swap locals yeah
			if (*_First > *_Last) {
				auto tmp = _Last.GetNode();
				_Last = custom_iter{ _First.GetNode() };
				_First = custom_iter{ tmp };
			}

			auto tmp = _First;
			for (auto _it = _First; _it != _Last;) {
				_it = tmp;
				++tmp;
				erase(_it);
			}
		}
		//param 1: stream | param 2: sep
		template <class _Stream, class _Separator>
		void print(_Stream& _Io, const _Separator& _Sep) const {
			if (m_size == 0) return; 
			for (auto elem : *this)
				_Io << elem << _Sep;
		}
		// ++
		void swap(list& other)
		{
			if (this != &other) {
				auto _tmpHead = this->m_head;
				auto _tmpTail = this->m_tail;
				this->m_head = other.m_head;
				this->m_tail = other.m_tail;
				other.m_head = _tmpHead;
				other.m_tail = _tmpTail;
			}
		}
		
		// insert sort-based sort
		template <class _Predict >
		void sort(_Predict _Pred)
		{
			if (m_size == 0) return;

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
