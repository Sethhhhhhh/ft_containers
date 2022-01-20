#ifndef __ITERATOR_HPP__
# define __ITERATOR_HPP__

# include <cstddef>
# include <utils.hpp>

namespace ft {

	struct random_access_iterator_tag {};

	template <typename T>
	class random_access_iterator {

		public:
			typedef T         					value_type;
			typedef ptrdiff_t  					difference_type;
			typedef T*   						pointer;
			typedef T& 							reference;
			typedef random_access_iterator_tag	category;

			/* Constructor and Destructor */
			
			random_access_iterator(void) : _p(u_nullptr) {};
			random_access_iterator(random_access_iterator& it) : _p(it) {};
			random_access_iterator&	operator=(const random_access_iterator& it) {
				if (this == &it)
					return (*this);
				_p = it._p;
				return (*this);
			};
			virtual	~random_access_iterator(void) {};

			/* Operator */

			reference	operator*() const { return *_p; }
			pointer		operator->(void) const { return _p; }
			reference	operator[](difference_type n) const { return _p[n]; }

			random_access_iterator	operator+(difference_type n) const { return random_access_iterator(_p + n); }
			random_access_iterator	operator-(difference_type n) const { return random_access_iterator(_p - n); }

			random_access_iterator&	operator++(void) {
				++_p;
				return (*this);
			}
			random_access_iterator	operator++(int) {
				random_access_iterator	tmp(*this);
				++_p;
				return (tmp);
			}

			random_access_iterator&	operator--(void) {
				--_p;
				return (*this);
			}
			random_access_iterator	operator--(int) {
				random_access_iterator	tmp(*this);
				--_p;
				return (tmp);
			}
			
			random_access_iterator&	operator+=(difference_type n) {
				_p += n;
				return (*this);
			}
			random_access_iterator&	operator-=(difference_type n) {
				_p -= n;
				return (*this);
			}

			bool	operator==(const random_access_iterator& it) const { _p == it._p; }
			bool	operator!=(const random_access_iterator& it) const { _p != it._p; }
			bool	operator>(const random_access_iterator& it)  const { _p > it._p; }
			bool	operator<(const random_access_iterator& it)  const { _p < it._p; }
			bool	operator>=(const random_access_iterator& it) const { _p >= it._p; }
			bool	operator<=(const random_access_iterator& it) const { _p <= it._p; }

		private:
			pointer	_p;
	};

	template <typename Iterator>
	class reverse_iterator {

		public:
			typedef	Iterator									iterator_type;
			typedef	typename iterator_type::iterator_category	iterator_category;
			typedef	typename iterator_type::value_type			value_type;
			typedef	typename iterator_type::difference_type		difference_type;
			typedef	typename iterator_type::pointer				pointer;
			typedef	typename iterator_type::reference			reference;
		
			/* Constructor and Destructor */

			reverse_iterator(void) : _it() {}
			reverse_iterator(iterator_type it) : _it(it) {}
			virtual ~reverse_iterator(void) {}

			/* Base */
			iterator_type	base() const { return(_it); }

			/* Operator */

			reverse_iterator	operator-(difference_type n) const { return (reverse_iterator(_it + n)); }
			reverse_iterator	operator+(difference_type n) const { return (reverse_iterator(_it - n)); }

			reverse_iterator& operator++(void) {
				--_it;
				return (*this);
			}

			reverse_iterator  operator++(int) {
				reverse_iterator tmp = *this;
				--_it;
        		return tmp;
			}

			reverse_iterator& operator--(void) {
				++_it;
				return (*this);
			}

			reverse_iterator  operator--(int) {
				reverse_iterator tmp = *this;
				++_it;
        		return tmp;
			}

			reverse_iterator& operator+=(difference_type n) {
				_it -= n;
        		return (*this);
			}

			reverse_iterator& operator-=(difference_type n) {
				_it += n;
        		return (*this);
			}

			reference	operator*(void) const {
				iterator_type	tmp(_it);
				return (*(--tmp));
			}
			pointer operator->(void) const { return &(operator*()); }
			reference operator[](difference_type n) const { return (base()[-n - 1]); }

		private:
			iterator_type	_it;

	};

	template <class Iterator>
	bool operator==(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {
		return (lhs.base() == rhs.base());
	}

	template <class Iterator>
	bool operator!=(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {
		return (lhs.base() != rhs.base());
	}

	template <class Iterator>
	bool operator<(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {
		return (lhs.base() < rhs.base());
	}

	template <class Iterator>
	bool operator<=(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {
		return (lhs.base() <= rhs.base());
	}

	template <class Iterator>
	bool operator>(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {
		return (lhs.base() > rhs.base());
	}

	template <class Iterator>
	bool operator>=(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {
		return (lhs.base() >= rhs.base());
	}

	template <class Iterator>
	reverse_iterator<Iterator> operator+(typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator>& rev_it) {
		return reverse_iterator<Iterator>(rev_it.base() - n);
	}

	template <class Iterator>
	typename reverse_iterator<Iterator>::difference_type operator-(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {
		return (rhs.base() - lhs.base());
	}
}

# endif