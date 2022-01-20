#ifndef __VECTOR_HPP__
# define __VECTOR_HPP__

# include <memory>
# include <stdexcept>
# include <iterator.hpp>


namespace ft {
	
	template<class T, class Alloc = std::allocator<T> >
	class vector {

		public:

			/* typedef */

			typedef T                                         	value_type;
			typedef Alloc                                      	allocator_type;
			typedef typename allocator_type::reference        	reference;
			typedef typename allocator_type::const_reference  	const_reference;
			typedef typename allocator_type::pointer           	pointer;
			typedef typename allocator_type::const_pointer     	const_pointer;
			typedef typename allocator_type::size_type      	size_type;
			typedef random_access_iterator<value_type>			iterator;
			typedef random_access_iterator<iterator>			reverse_iterator;
			typedef const iterator								const_iterator;
			typedef const reverse_iterator						const_reverse_iterator;
			typedef std::ptrdiff_t								difference_type;
		
			/* Constructors */

			explicit vector(const allocator_type& alloc = allocator_type()) : _alloc(alloc), _vector(u_nullptr), _size(0), _capacity(0) {}

			explicit vector(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()) : _alloc(alloc), _vector(u_nullptr), _size(0), _capacity(0) {
				_vector = _alloc.allocate(n);
				for (size_type i = 0; i < n; i++) {
					_alloc.construct(_vector[i], val);
				}
			}

			template <class InputIterator> vector(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type())  :_alloc(alloc), _vector(u_nullptr), _size(0), _capacity(0) {
				difference_type n = std::distance(first, last);
				_vector = _alloc.allocate(n);
				for (size_type i = 0; i < n; i++) {
					_alloc.construct(_vector[i], *first);
				}
			}

			vector(const vector& x) : _alloc(x._alloc), _vector(x->begin()) {
				insert(x->begin(), x->begin(), x->end());
			}

			vector& operator=(const vector& x) {
				if (x == *this)
					return (*this);
				clear();
				insert(x->begin(), x->begin(), x->end());
				
				return (*this);
			}	

			/* Destructor */

			~vector(void) {
				clear();
				_alloc.deallocate(_vector, _capacity);
			}

			/* Iterators */

			iterator 		begin(void) { return _vector; }
			const_iterator 	begin(void) const { return _vector; }

			reverse_iterator 		rbegin(void) { return (reverse_iterator(end())); }
			const_reverse_iterator 	rbegin(void) const { return (reverse_iterator(end())); }

			reverse_iterator 		rend(void) { return (reverse_iterator(begin())); }
			const_reverse_iterator	rend(void) const { return (reverse_iterator(begin())); }

			iterator end(void) {
				if (empty())
					return (begin());
				return (_vector[_size - 1]);
			}
			const_iterator end(void) const {
				if (empty())
					return (begin());
				return (_vector[_size - 1]);
			}


			/* Capacity */

			size_type   size(void) const {
				return (_size);
			}
			size_type max_size(void) const { return (_alloc.max_size()); }
			size_type capacity(void) const { return _capacity; }
			bool empty(void) const { return (size() == 0); }
			
			void resize(size_type n, value_type val = value_type()) {
				if (n > max_size()) return;
				if (n > _capacity) reserve(n);
				
				if (n < _size) {
					for (size_type i = n; i < _size; i++)
						_alloc.destroy(_vector[n]);
					_alloc.deallocate(_vector[n], ((_size - 1) - n));
				}
				else
					insert(_vector[_size - 1], ((_size - 1) - n), val);
			}

			void reserve(size_type n) {
				if (n > max_size())
					throw std::length_error("vector::reserve n is greater than the maximum size (vector::max_size)");
				if (n <= _capacity) return;

				pointer	p_vector = _vector;
				_vector = _alloc.allocate(n);

				for (size_type i = 0; i < _size; i++) {
					_vector[i] = p_vector[i];
					_alloc.destroy(p_vector[i]);
				}
				if (_size > 0)
					_alloc.deallocate(p_vector, _capacity);
				_capacity = n;
			}

			/* Element access */

			reference operator[] (size_type n) { return *(_vector[n]); }
			const_reference operator[] (size_type n) const { return *(_vector[n]); }

			reference at (size_type n) {
				if (n >= (_size - 1))
					throw std::out_of_range("vector::at n is out of range.");
				return *(_vector[n]);
			}
			const_reference at (size_type n) const {
				if (n >= (_size - 1)) {
					throw std::out_of_range("vector::at n is out of range.");
				}
				return *(_vector[n]);
			}

			reference front(void) { return *(_vector[0]); }
			const_reference front(void) const { return *(_vector[0]); }

			reference back(void) { return *(_vector[_size - 1]); }
			const_reference back(void) const { return *(_vector[_size - 1]); }

			/* Modifiers */

			template <class InputIterator>
  			void assign(InputIterator first, InputIterator last) {
				clear();
				size_type n = std::distance(first - last);
				if (n > max_size()) return;
				if (n > _capacity)
					reserve(n);
			
				for (size_type i = 0; first != last; first++, i++)
					_alloc.construct(_vector[n], *first);
			}
			
			void assign(size_type n, const value_type& val) {
				clear();
				if (n > max_size()) return;
				if (n > _capacity)
					reserve(n);
				
				for (size_type i = 0; i < n; i++)
					_alloc.construct(_vector[n], val);
			}

			void push_back(const value_type& val) {
				if (_size == _capacity) {
					_capacity = _size > 0 ? _size * 2 : 1;
					reserve(_capacity);
				}
				_alloc.construct(_vector[_size], val);
			}

			void pop_back(void) {
				_alloc.destroy(back());
				_size--;
			}

			iterator insert(iterator position, const value_type& val) {
				(void)position;
				(void)val;
			}

			void insert(iterator position, size_type n, const value_type& val) {
				(void)position;
				(void)n;
				(void)val;
			}

			template <class InputIterator>
    		void insert(iterator position, InputIterator first, InputIterator last) {
				(void)position;
				(void)first;
				(void)last;
			}

			iterator erase(iterator position) {
				(void)position;
			}
			iterator erase(iterator first, iterator last) {
				(void)first;
				(void)last;
			}

			void swap(vector& x) {
				(void)x;
			}

			void clear(void) {}

			/* Allocator */


		private:
			allocator_type	_alloc;
			pointer			_vector;
			size_type		_size;
			size_type		_capacity;

	};

}

#endif