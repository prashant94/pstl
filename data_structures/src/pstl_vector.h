#pragma once

#include <iostream>
#include <iterator>
#include <cstddef>
#include <optional>
#include <cmath>
#include "commons.h"

namespace pstl

{
	template<typename T>
	class vector
	{
	public:
		struct Iterator
		{
		public:
			using iterator_category = std::forward_iterator_tag;
			using difference_type = std::ptrdiff_t;
			using value_type = T;
			using pointer = value_type*;
			using reference = value_type&;

			Iterator(pointer ptr)
				: m_ptr(ptr) {}

			reference operator *() const { return *m_ptr; }
			pointer operator ->() const { return m_ptr; }

			Iterator& operator ++()
			{
				m_ptr++;
				return *this;
			}

			Iterator operator ++(int)
			{
				Iterator tmp = *this;
				++(*this);
				return tmp;
			}

			Iterator& operator --()
			{
				m_ptr--;
				return *this;
			}

			Iterator operator --(int)
			{
				Iterator tmp = *this;
				--(*this);
				return tmp;
			}

			Iterator operator +(int incr)
			{
				m_ptr = m_ptr + incr;
				return *this;
			}

			Iterator operator -(int decr)
			{
				m_ptr = m_ptr - decr;
				return *this;
			}

			friend bool operator ==(const Iterator& a, const Iterator& b) { return a.m_ptr == b.m_ptr; };
			friend bool operator !=(const Iterator& a, Iterator& b) { return a.m_ptr != b.m_ptr; };
			friend bool operator <=(const Iterator& a, const Iterator& b) { return a.m_ptr <= b.m_ptr; };
			friend bool operator >=(const Iterator& a, Iterator& b) { return a.m_ptr >= b.m_ptr; };
			friend bool operator >(const Iterator& a, Iterator& b) { return a.m_ptr > b.m_ptr; };
			friend bool operator <(const Iterator& a, Iterator& b) { return a.m_ptr < b.m_ptr; };

		private:
			pointer m_ptr;
		};

		Iterator begin() { return Iterator(m_data); }
		Iterator end() { return Iterator(m_data + m_size); }

		void reverse(std::optional<Iterator> first = std::optional<Iterator>{}, std::optional<Iterator> last = std::optional<Iterator>{})
		{
			Iterator first_internal = first.value_or(this->begin());
			Iterator last_internal = last.value_or(this->end()) - 1;
			T temp;
			for (; first_internal < last_internal; first_internal++, last_internal--)
			{
				temp = *first_internal;
				*first_internal = *last_internal;
				*last_internal = temp;
			}
		}

		void swap(vector& other, std::optional<Iterator> first = std::optional<Iterator>{}, std::optional<Iterator> last = std::optional<Iterator>{})
		{
			Iterator first_internal = first.value_or(this->begin());
			Iterator last_internal = last.value_or(this->end()) - 1;
			int distance = std::distance(this->begin(), first_internal);
			Iterator other_first = other.begin() + distance;
			T temp;
			for (; first_internal != last_internal; first_internal++, other_first++)
			{
				temp = *first_internal;
				*first_internal = *other_first;
				*other_first = temp;
			}
		}

		void sort(std::optional<pstl::sort_method> method = std::optional<pstl::sort_method>{},
			std::optional<pstl::sort_order> order = std::optional<pstl::sort_order>{},
			std::optional<Iterator> first = std::optional<Iterator>{},
			std::optional<Iterator> last = std::optional<Iterator>{})
		{
			pstl::sort_method sort_method_internal = method.value_or(pstl::sort_method::selection);
			pstl::sort_order sort_order_internal = order.value_or(pstl::sort_order::ascending);
			Iterator first_internal = first.value_or(this->begin());
			Iterator last_internal = last.value_or(this->end());
			const auto lt = [](Iterator a, Iterator b) { return *a < *b; };
			const auto gt = [](Iterator a, Iterator b) { return *a > *b; };
			bool sort_condition = !(sort_order_internal == pstl::sort_order::ascending);
			T temp;
			switch (sort_method_internal)
			{
			case pstl::sort_method::selection:
				for (Iterator i = first_internal; i != last_internal; i++)
					for (Iterator j = i; j != last_internal; j++)
						if ((sort_condition ? +lt : +gt)(j, i))
						{
							temp = *i;
							*i = *j;
							*j = temp;
						}
			case pstl::sort_method::bubble:
				for (Iterator i = first_internal; i != last_internal; i++)
					for (Iterator j = first_internal; j <= i; j++)
						if ((sort_condition ? +lt : +gt)(j, i))
						{
							temp = *i;
							*i = *j;
							*j = temp;
						}
			}

		}

		vector()
		{
			reallocate(2);
		}

		template<typename... Args>
		vector(const Args& ...args)
		{
			if (sizeof...(args) >= m_capacity)
				reallocate(sizeof...(args) + m_capacity / 2);
			for (auto item : { args... })
				push_back(std::forward<T>(item));
		}

		~vector()
		{
			clear();
			::operator delete(m_data, m_capacity * sizeof(T));
		}

		void push_back(const T&& value)
		{
			if (m_size >= m_capacity)
				reallocate(m_capacity + m_capacity / 2);
			m_data[m_size++] = std::move(value);
		}

		template<typename... Args>
		void emplace_back(Args&&... args)
		{
			if (m_size >= m_capacity)
				reallocate(m_capacity + m_capacity / 2);
			new(&m_data[m_size++]) T(std::forward<Args>(args)...);
		}

		void pop_back()
		{
			if (m_size > 0)
			{
				m_size--;
				m_data[m_size].~T();
			}
		}

		void clear()
		{
			for (size_t i = 0; i < m_size; i++)
				m_data[i].~T();
			m_size = 0;
		}

		void print()
		{
			for (int i = 0; i < m_size; i++)
				std::cout << m_data[i] << ", ";
			std::cout << std::endl;
		}

		const size_t size() const
		{
			return m_size;
		}

		const size_t capacity() const
		{
			return m_capacity;
		}

		T& operator [](int index)
		{
			index = std::abs(index) <= this->size() ? index : index % this->size();
			return index >= 0 ? m_data[index] : m_data[this->size() + index];
		}

		const T& operator [](int index) const
		{
			index = std::abs(index) <= this->size() ? index : index % this->size();
			return index >= 0 ? m_data[index] : m_data[this->size() + index];
		}

		friend bool operator ==(const vector& a, const vector& b)
		{
			if (a.size() != b.size())
				return false;
			for (int i = 0; i < a.size(); i++)
				if (a[i] != b[i])
					return false;
			return true;
		};

		friend bool operator !=(const vector& a, const vector& b)
		{
			for (int i = 0; i < a.size(); i++)
				if (a[i] != b[i])
					return true;
			return false;
		};


	private:
		void reallocate(size_t new_capacity)
		{
			T* new_data = (T*)::operator new(new_capacity * sizeof(T));
			if (new_capacity < m_size)
				m_size = new_capacity;
			for (size_t i = 0; i < m_size; i++)
				new_data[i] = std::move(m_data[i]);
			for (size_t i = 0; i < m_size; i++)
				m_data[i].~T();
			::operator delete(m_data, m_capacity * sizeof(T));
			m_data = new_data;
			m_capacity = new_capacity;
		}

	private:
		T* m_data = nullptr;
		size_t m_size;
		size_t m_capacity;
	};

	template<typename T>
	std::ostream& operator <<(std::ostream& stream, vector<T>& vec)
	{
		for (int i = 0; i < vec.size(); i++)
			stream << vec[i] << ", ";
		return stream;
	}

	template<typename T>
	std::ostream& operator <<(std::ostream& stream, const vector<T>& vec)
	{
		for (int i = 0; i < vec.size(); i++)
			stream << vec[i] << ", ";
		return stream;
	}
}