#pragma once
#include <cassert>

namespace simple_math
{
	template< size_t M, typename T = double >
	class BaseVector
	{
	public:
		typedef T value_type;

	public:
		BaseVector() : data() {}

		// Set all components to e
		explicit BaseVector(const T& e);
		BaseVector(const T& x, const T& y);

		BaseVector& operator=(const BaseVector& other);
		BaseVector& operator=(const T& e);

		T& operator[](size_t index);
		const T& operator[](size_t index) const;

		T& at(size_t index);
		const T& at(size_t index) const;

		T& x();
		T& y();

		const T& x() const;
		const T& y() const;

		bool operator==(const BaseVector& other) const;
		bool operator!=(const BaseVector& other) const;

		// Scalar operations
		BaseVector operator*(const BaseVector& other) const;
		BaseVector operator/(const BaseVector& other) const;
		BaseVector operator+(const BaseVector& other) const;
		BaseVector operator-(const BaseVector& other) const;

		void operator*=(const BaseVector& other);
		void operator/=(const BaseVector& other);
		void operator+=(const BaseVector& other);
		void operator-=(const BaseVector& other);

		BaseVector operator*(const T other) const;
		BaseVector operator/(const T other) const;
		BaseVector operator+(const T other) const;
		BaseVector operator-(const T other) const;

		void operator*=(const T other);
		void operator/=(const T other);
		void operator+=(const T other);
		void operator-=(const T other);

		friend std::ostream& operator<< (std::ostream& os, const BaseVector& vector)
		{
			const std::ios::fmtflags flags = os.flags();
			const std::streamsize prec = os.precision();

			os.setf(std::ios::right, std::ios::adjustfield);
			os.precision(3);
			os << "[";
			for (size_t index = 0; index < M; ++index)
				os << vector.at(index) << (index + 1 < M ? ";" : "]");
			os.precision(prec);
			os.setf(flags);
			return os;
		}

		// Components storage
		T data[M];
	};

	template <size_t M, typename T>
	BaseVector<M, T>::BaseVector(const T& e)
	{
		for (T& component: data)
			component = e;
	}

	template <size_t M, typename T>
	BaseVector<M, T>::BaseVector(const T& x, const T& y)
	{
		static_assert(M == 2, "BaseVector size construction error.");
		data[0] = x;
		data[1] = y;
	}

	template <size_t M, typename T>
	BaseVector<M, T>& BaseVector<M, T>::operator=(const BaseVector& other)
	{
		if (this != &other)
			memcpy(data, other.data, M * sizeof(T));
		return *this;
	}

	template <size_t M, typename T>
	BaseVector<M, T>& BaseVector<M, T>::operator=(const T& e)
	{
		for (T& component : data)
			component = e;
		return *this;
	}

	template <size_t M, typename T>
	T& BaseVector<M, T>::operator[](size_t index)
	{
		return at(index);
	}

	template <size_t M, typename T>
	const T& BaseVector<M, T>::operator[](size_t index) const
	{
		return at(index);
	}

	template <size_t M, typename T>
	T& BaseVector<M, T>::at(size_t index)
	{
		if (index >= M)
		{
			assert(!"at(), index out of range");
		}
		return data[index];
	}

	template <size_t M, typename T>
	const T& BaseVector<M, T>::at(size_t index) const
	{
		if (index >= M)
		{
			assert(!"at(), index out of range");
		}
		return data[index];
	}

	template <size_t M, typename T>
	T& BaseVector<M, T>::x()
	{
		return data[0];
	}

	template <size_t M, typename T>
	T& BaseVector<M, T>::y()
	{
		static_assert(M > 1, "BaseVector size should be > 1");
		return data[1];
	}

	template <size_t M, typename T>
	const T& BaseVector<M, T>::x() const
	{
		return data[0];
	}

	template <size_t M, typename T>
	const T& BaseVector<M, T>::y() const
	{
		static_assert(M > 1, "BaseVector size should be > 1");
		return data[1];
	}

	template <size_t M, typename T>
	bool BaseVector<M, T>::operator==(const BaseVector& other) const
	{
		return memcmp(data, other.data, sizeof(data)) == 0;
	}

	template <size_t M, typename T>
	bool BaseVector<M, T>::operator!=(const BaseVector& other) const
	{
		return !this->operator==(other);
	}

	template <size_t M, typename T>
	BaseVector<M, T> BaseVector<M, T>::operator*(const BaseVector& other) const
	{
		BaseVector< M, T > res;
		for (size_t index = 0; index < M; ++index)
			res.at(index) = at(index) * other.at(index);
		return res;
	}

	template <size_t M, typename T>
	BaseVector<M, T> BaseVector<M, T>::operator/(const BaseVector& other) const
	{
		BaseVector< M, T > res;
		for (size_t index = 0; index < M; ++index)
			res.at(index) = at(index) / other.at(index);
		return res;
	}

	template <size_t M, typename T>
	BaseVector<M, T> BaseVector<M, T>::operator-(const BaseVector& other) const
	{
		BaseVector< M, T > res;
		for (size_t index = 0; index < M; ++index)
			res.at(index) = at(index) - other.at(index);
		return res;
	}

	template <size_t M, typename T>
	void BaseVector<M, T>::operator*=(const BaseVector& other)
	{
		for (size_t index = 0; index < M; ++index)
			at(index) *= other.at(index);
	}

	template <size_t M, typename T>
	void BaseVector<M, T>::operator/=(const BaseVector& other)
	{
		for (size_t index = 0; index < M; ++index)
			at(index) /= other.at(index);
	}

	template <size_t M, typename T>
	void BaseVector<M, T>::operator+=(const BaseVector& other)
	{
		for (size_t index = 0; index < M; ++index)
			at(index) += other.at(index);
	}

	template <size_t M, typename T>
	void BaseVector<M, T>::operator-=(const BaseVector& other)
	{
		for (size_t index = 0; index < M; ++index)
			at(index) -= other.at(index);
	}

	template <size_t M, typename T>
	BaseVector<M, T> BaseVector<M, T>::operator*(const T other) const
	{
		BaseVector< M, T > res;
		for (size_t index = 0; index < M; ++index)
			res.at(index) = at(index) * other;
		return res;
	}

	template <size_t M, typename T>
	BaseVector<M, T> BaseVector<M, T>::operator/(const T other) const
	{
		BaseVector< M, T > res;
		for (size_t index = 0; index < M; ++index)
			res.at(index) = at(index) / other;
		return res;
	}

	template <size_t M, typename T>
	BaseVector<M, T> BaseVector<M, T>::operator+(const T other) const
	{
		BaseVector< M, T > res;
		for (size_t index = 0; index < M; ++index)
			res.at(index) = at(index) + other;
		return res;
	}

	template <size_t M, typename T>
	BaseVector<M, T> BaseVector<M, T>::operator-(const T other) const
	{
		BaseVector< M, T > res;
		for (size_t index = 0; index < M; ++index)
			res.at(index) = at(index) - other;
		return res;
	}

	template <size_t M, typename T>
	void BaseVector<M, T>::operator*=(const T other)
	{
		for (size_t index = 0; index < M; ++index)
			at(index) *= other;
	}

	template <size_t M, typename T>
	void BaseVector<M, T>::operator/=(const T other)
	{
		for (size_t index = 0; index < M; ++index)
			at(index) /= other;
	}

	template <size_t M, typename T>
	void BaseVector<M, T>::operator+=(const T other)
	{
		for (size_t index = 0; index < M; ++index)
			at(index) += other;
	}

	template <size_t M, typename T>
	void BaseVector<M, T>::operator-=(const T other)
	{
		for (size_t index = 0; index < M; ++index)
			at(index) -= other;
	}

	template <size_t M, typename T>
	BaseVector<M, T> BaseVector<M, T>::operator+(const BaseVector& other) const
	{
		BaseVector< M, T > res;
		for (size_t index = 0; index < M; ++index)
			res.at(index) = at(index) + other.at(index);
		return res;
	}
}
