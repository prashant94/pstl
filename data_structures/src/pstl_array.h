#pragma once

#include <iostream>
#include <iterator>
#include <cstddef>
#include <optional>
#include <cmath>
#include "commons.h"

namespace pstl
{
	template<typename T, size_t S>
	class array
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

		Iterator begin() { return Iterator(&m_data[0]); }
		Iterator end() { return Iterator(&m_data[this->size()]); }

		template<typename... Args>
		array(const Args& ...args)
			: m_data{ args... } { }

		array(const array& other)
			: m_data(other) { }

		constexpr int size() const { return S; }

		void fill(const T& data, std::optional<Iterator> first = std::optional<Iterator>{}, std::optional<Iterator> last = std::optional<Iterator>{})
		{
			Iterator first_internal = first.value_or(this->begin());
			Iterator last_internal = last.value_or(this->end());
			for (; first_internal != last_internal; first_internal++)
				*first_internal = data;
		}

		void reverse(std::optional<Iterator> first = std::optional<Iterator>{}, std::optional<Iterator> last = std::optional<Iterator>{})
		{
			Iterator first_internal = first.value_or(this->begin());
			Iterator last_internal = last.value_or(this->end()) - 1;
			T temp;
			for (; first_internal <= last_internal; first_internal++, last_internal--)
			{
				temp = *first_internal;
				*first_internal = *last_internal;
				*last_internal = temp;
			}
		}

		void swap(array& other, std::optional<Iterator> first = std::optional<Iterator>{}, std::optional<Iterator> last = std::optional<Iterator>{})
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

		void sort(std::optional<sort_method> method = std::optional<sort_method>{},
			std::optional<sort_order> order = std::optional<sort_order>{},
			std::optional<Iterator> first = std::optional<Iterator>{},
			std::optional<Iterator> last = std::optional<Iterator>{})
		{
			sort_method sort_method_internal = method.value_or(sort_method::selection);
			sort_order sort_order_internal = order.value_or(sort_order::ascending);
			Iterator first_internal = first.value_or(this->begin());
			Iterator last_internal = last.value_or(this->end());
			const auto lt = [](Iterator a, Iterator b) { return *a < *b; };
			const auto gt = [](Iterator a, Iterator b) { return *a > *b; };
			bool sort_condition = !(sort_order_internal == sort_order::ascending);
			T temp;
			switch (sort_method_internal)
			{
			case sort_method::selection:
				for (Iterator i = first_internal; i != last_internal; i++)
					for (Iterator j = i; j != last_internal; j++)
						if ((sort_condition ? +lt : +gt)(j, i))
						{
							temp = *i;
							*i = *j;
							*j = temp;
						}
			case sort_method::bubble:
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

		const void print() const
		{
			for (int i = 0; i < this->size(); i++)
				std::cout << m_data[i] << ", ";
			std::cout << std::endl;
		}

		T* data() { return m_data; }
		const T* data() const { return m_data; }

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

		friend bool operator ==(const array& a, const array& b) 
		{ 
			if (a.size() != b.size())
				return false;
			for (int i = 0; i < a.size(); i++)
				if (a[i] != b[i])
					return false;
			return true;
		};

		friend bool operator !=(const array& a, const array& b)
		{ 
			for (int i = 0; i < a.size(); i++)
				if (a[i] != b[i])
					return true;
			return false;
		};

	private:
		T m_data[S];
	};

	template<typename T, size_t S>
	std::ostream& operator <<(std::ostream& stream, array<T, S>& arr)
	{
		for (int i = 0; i < arr.size(); i++)
			stream << arr[i] << ", ";
		return stream;
	}

	template<typename T, size_t S>
	std::ostream& operator <<(std::ostream& stream, const array<T, S>& arr)
	{
		for (int i = 0; i < arr.size(); i++)
			stream << arr[i] << ", ";
		return stream;
	}
}



