/*
 * HilbertCurve.h
 *
 *  Created on: Jul 15, 2023
 *      Author: Nathan
 */

#ifndef PRIORI_MAPPING_HILBERTCURVE_H_
#define PRIORI_MAPPING_HILBERTCURVE_H_

#include <iterator>

namespace priori{

	template<class T>
	struct HilbertIterator;

	template<class T>
	class HilbertCurve{
	public:
		T** matrix;
		unsigned int length, order;

		HilbertCurve(int length);
		HilbertCurve(T* arr, int length);
		~HilbertCurve();

		HilbertIterator<T> begin();
		HilbertIterator<T> end();

		T& get(int pos);
		T& operator[](int pos);
	};

	template<class T>
	struct HilbertIterator{
		using iterator_category = std::random_access_iterator_tag;
		using difference_type = int;
		using value_type = T;
		using pointer = T*;
		using reference = T&;

		HilbertCurve<T> curve;
		unsigned int pos;

		HilbertIterator();
		HilbertIterator(HilbertCurve<T>* curve, unsigned int pos);

		T& operator*() const;
		T* operator->();
		T& operator[](int n);

		bool operator==(const HilbertIterator<T> &other) const;
		bool operator!=(const HilbertIterator<T> &other) const;
		bool operator<(const HilbertIterator<T> &other) const;
		bool operator<=(const HilbertIterator<T> &other) const;
		bool operator>(const HilbertIterator<T> &other) const;
		bool operator>=(const HilbertIterator<T> &other) const;

		HilbertIterator<T>& operator++();
		HilbertIterator<T>& operator++(int);
		HilbertIterator<T>& operator--();
		HilbertIterator<T>& operator--(int);

		HilbertIterator<T> operator+(int n);
		template<T> friend HilbertIterator<T> operator+(int n, const HilbertIterator<T> it);
		HilbertIterator<T>& operator+=(int n);
		HilbertIterator<T> operator-(int n);
		template<T> friend HilbertIterator<T> operator-(int n, const HilbertIterator<T> it);
		HilbertIterator<T>& operator-=(int n);
	};

}

#endif /* PRIORI_MAPPING_HILBERTCURVE_H_ */
