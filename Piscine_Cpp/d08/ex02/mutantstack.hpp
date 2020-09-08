// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   mutantstack.hpp                                    :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: root </var/mail/root>                      +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/07/10 15:05:10 by root              #+#    #+#             //
//   Updated: 2018/07/10 17:34:55 by root             ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef MUTANTSTACK_HPP
# define MUTANTSTACK_HPP

# include <stack>

template<typename T>
class MutantStack: public std::stack<T>
{
public:
	MutantStack(): _data(0), _size(0) {}
	MutantStack(MutantStack const & src) { *this = src; }
	MutantStack & operator=(MutantStack const & rhs) {
		if (this != &rhs)
		{
			this->_data = rhs._data;
			this->_size = rhs._size;
		}
		return *this;
	}
	~MutantStack() {}

	bool		empty() const { return this->_size == 0; }
	std::size_t	size() const { return this->_size; }
	T &			top() { return this->_data[0]; }
	void		push( T const & val) {
		T	*ptr = this->_data;

		this->_data = new T[this->_size + 1];
		this->_data[0] = val;
		for (std::size_t i = 0; i < this->_size; i++) {
			this->_data[i + 1] = ptr[i];
		}
		this->_size++;
		delete ptr;
	}
	void		pop() {
		T	*ptr = this->_data;

		if (this->_size == 0)
			return ;
		if (this->_size == 1)
			this->_data = 0;
		else
		{
			this->_data = new T[this->_size - 1];
			for (std::size_t i = 1; i < this->_size; i++) {
				this->_data[i - 1] = ptr[i];
			}
		}
		this->_size--;
		delete ptr;
	}

	class iterator
	{
	public:
		typedef iterator self_type;
		typedef T value_type;
		typedef T& reference;
		typedef T* pointer;
		typedef std::forward_iterator_tag iterator_category;
		typedef int difference_type;
		iterator(T* ptr = 0) : _ptr(ptr) {}
		iterator operator++() { _ptr++; return *this; } // PREFIX
		iterator operator++(int) { iterator retval = *this; _ptr++; return retval; } // POSTFIX
		iterator operator--() { _ptr--; return *this; }
		iterator operator--(int) { iterator retval = *this; _ptr--; return retval; }
		bool operator==(const iterator & rhs) const { return _ptr == rhs._ptr; }
		bool operator!=(const iterator & rhs) const { return _ptr != rhs._ptr; }
		reference operator*() const { return *_ptr; }
	private:
		T*		_ptr;
	};
	iterator begin() { return iterator(_data); }
	iterator end() { return iterator(_data + _size); }

private:
	T			*_data;
	std::size_t	_size;
};

#endif
