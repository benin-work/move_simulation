#pragma once
#include <cassert>

namespace simple_math
{
	template< size_t M, typename T = double >
	class Vector
	{
	public:
		typedef T value_type;

	public:
		Vector() : data() {}

		// Set all components to e
		explicit Vector(const T& e);
		Vector(const T& x, const T& y);

		Vector& operator=(const Vector& other);
		Vector& operator=(const T& e);

		T& operator[](size_t index);
		const T& operator[](size_t index) const;

		T& at(size_t index);
		const T& at(size_t index) const;

		T& x();
		T& y();

		const T& x() const;
		const T& y() const;

		bool operator==(const Vector& other) const;
		bool operator!=(const Vector& other) const;

		// Scalar operations
		Vector operator*(const Vector& other) const;
		Vector operator/(const Vector& other) const;
		Vector operator+(const Vector& other) const;
		Vector operator-(const Vector& other) const;

		void operator*=(const Vector& other);
		void operator/=(const Vector& other);
		void operator+=(const Vector& other);
		void operator-=(const Vector& other);

		Vector operator*(const T other) const;
		Vector operator/(const T other) const;
		Vector operator+(const T other) const;
		Vector operator-(const T other) const;

		void operator*=(const T other);
		void operator/=(const T other);
		void operator+=(const T other);
		void operator-=(const T other);

		friend std::ostream& operator<< (std::ostream& os, const Vector& vector)
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
	Vector<M, T>::Vector(const T& e)
	{
		for (T& component: data)
			component = e;
	}

	template <size_t M, typename T>
	Vector<M, T>::Vector(const T& x, const T& y)
	{
		static_assert(M == 2, "Vector size construction error.");
		data[0] = x;
		data[1] = y;
	}

	template <size_t M, typename T>
	Vector<M, T>& Vector<M, T>::operator=(const Vector& other)
	{
		if (this != &other)
			memcpy(data, other.data, M * sizeof(T));
		return *this;
	}

	template <size_t M, typename T>
	Vector<M, T>& Vector<M, T>::operator=(const T& e)
	{
		for (T& component : data)
			component = e;
		return *this;
	}

	template <size_t M, typename T>
	T& Vector<M, T>::operator[](size_t index)
	{
		return at(index);
	}

	template <size_t M, typename T>
	const T& Vector<M, T>::operator[](size_t index) const
	{
		return at(index);
	}

	template <size_t M, typename T>
	T& Vector<M, T>::at(size_t index)
	{
		if (index >= M)
		{
			assert(!"at(), index out of range");
		}
		return data[index];
	}

	template <size_t M, typename T>
	const T& Vector<M, T>::at(size_t index) const
	{
		if (index >= M)
		{
			assert(!"at(), index out of range");
		}
		return data[index];
	}

	template <size_t M, typename T>
	T& Vector<M, T>::x()
	{
		return data[0];
	}

	template <size_t M, typename T>
	T& Vector<M, T>::y()
	{
		static_assert(M > 1, "Vector size should be > 1");
		return data[1];
	}

	template <size_t M, typename T>
	const T& Vector<M, T>::x() const
	{
		return data[0];
	}

	template <size_t M, typename T>
	const T& Vector<M, T>::y() const
	{
		static_assert(M > 1, "Vector size should be > 1");
		return data[1];
	}

	template <size_t M, typename T>
	bool Vector<M, T>::operator==(const Vector& other) const
	{
		return memcmp(data, other.data, sizeof(data)) == 0;
	}

	template <size_t M, typename T>
	bool Vector<M, T>::operator!=(const Vector& other) const
	{
		return !this->operator==(other);
	}

	template <size_t M, typename T>
	Vector<M, T> Vector<M, T>::operator*(const Vector& other) const
	{
		Vector< M, T > res;
		for (size_t index = 0; index < M; ++index)
			res.at(index) = at(index) * other.at(index);
		return res;
	}

	template <size_t M, typename T>
	Vector<M, T> Vector<M, T>::operator/(const Vector& other) const
	{
		Vector< M, T > res;
		for (size_t index = 0; index < M; ++index)
			res.at(index) = at(index) / other.at(index);
		return res;
	}

	template <size_t M, typename T>
	Vector<M, T> Vector<M, T>::operator-(const Vector& other) const
	{
		Vector< M, T > res;
		for (size_t index = 0; index < M; ++index)
			res.at(index) = at(index) - other.at(index);
		return res;
	}

	template <size_t M, typename T>
	void Vector<M, T>::operator*=(const Vector& other)
	{
		for (size_t index = 0; index < M; ++index)
			at(index) *= other.at(index);
	}

	template <size_t M, typename T>
	void Vector<M, T>::operator/=(const Vector& other)
	{
		for (size_t index = 0; index < M; ++index)
			at(index) /= other.at(index);
	}

	template <size_t M, typename T>
	void Vector<M, T>::operator+=(const Vector& other)
	{
		for (size_t index = 0; index < M; ++index)
			at(index) += other.at(index);
	}

	template <size_t M, typename T>
	void Vector<M, T>::operator-=(const Vector& other)
	{
		for (size_t index = 0; index < M; ++index)
			at(index) -= other.at(index);
	}

	template <size_t M, typename T>
	Vector<M, T> Vector<M, T>::operator*(const T other) const
	{
		Vector< M, T > res;
		for (size_t index = 0; index < M; ++index)
			res.at(index) = at(index) * other;
		return res;
	}

	template <size_t M, typename T>
	Vector<M, T> Vector<M, T>::operator/(const T other) const
	{
		Vector< M, T > res;
		for (size_t index = 0; index < M; ++index)
			res.at(index) = at(index) / other;
		return res;
	}

	template <size_t M, typename T>
	Vector<M, T> Vector<M, T>::operator+(const T other) const
	{
		Vector< M, T > res;
		for (size_t index = 0; index < M; ++index)
			res.at(index) = at(index) + other;
		return res;
	}

	template <size_t M, typename T>
	Vector<M, T> Vector<M, T>::operator-(const T other) const
	{
		Vector< M, T > res;
		for (size_t index = 0; index < M; ++index)
			res.at(index) = at(index) - other;
		return res;
	}

	template <size_t M, typename T>
	void Vector<M, T>::operator*=(const T other)
	{
		for (size_t index = 0; index < M; ++index)
			at(index) *= other;
	}

	template <size_t M, typename T>
	void Vector<M, T>::operator/=(const T other)
	{
		for (size_t index = 0; index < M; ++index)
			at(index) /= other;
	}

	template <size_t M, typename T>
	void Vector<M, T>::operator+=(const T other)
	{
		for (size_t index = 0; index < M; ++index)
			at(index) += other;
	}

	template <size_t M, typename T>
	void Vector<M, T>::operator-=(const T other)
	{
		for (size_t index = 0; index < M; ++index)
			at(index) -= other;
	}

	template <size_t M, typename T>
	Vector<M, T> Vector<M, T>::operator+(const Vector& other) const
	{
		Vector< M, T > res;
		for (size_t index = 0; index < M; ++index)
			res.at(index) = at(index) + other.at(index);
		return res;
	}
}
