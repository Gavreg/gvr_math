// Гаврилов А.Г.
// 27.12.2024
#pragma once

#include <cmath>
#include <cstring>
#include <initializer_list>
#include <utility>
#include <array>

#include <iostream>

namespace gvr
{


template <typename T, size_t N, typename Derived_Vector>
class Base_Vector
{

    std::array <T, N> m_data;
private:

    friend class Base_Vector;

    template <size_t M, typename type_of_other>
    constexpr void copy_data(size_t& offset, const Base_Vector<T,M, type_of_other>& other)
    {
        for (size_t i = 0; i < other.m_data.size(); ++i)
            m_data[offset++] = other.m_data[i];
    }

    constexpr void copy_data(size_t& offset, const T& data)
    {
        m_data[offset++] = data;
    }

    template <typename U>
    constexpr static size_t get_size()
    {
        if constexpr (requires {U::size(); })
            return U::size();
        else
            return 1;
    }

public:

    Base_Vector() :m_data{ 0 } { static_assert(std::is_arithmetic<T>(), "Wrong Vector Type!"); };
    

    ~Base_Vector() = default;



    constexpr static auto size()
    {
        return N;
    }


    const T& operator[](size_t i) const
    {
        assert(i < N);

        return m_data[i];
    }

    T& operator[](size_t i)
    {
        assert(i < N);

        return m_data[i];
    }

    template <typename ...Args>
    Base_Vector(Args... args) : m_data{ 0 }
    {
        static_assert(std::is_arithmetic<T>(), "Wrong Vector Type!");

        constexpr size_t total_size = 0 + (get_size<Args>() + ...);

		static_assert(total_size <= N, "Wrong vector size!");

        size_t offset = 0;
        (copy_data(offset, args), ...);
    }
    
    constexpr auto operator+(const Derived_Vector& other)
    {
        Derived_Vector __new;
        for (auto i = 0; i < N; ++i)
            __new.m_data[i] = m_data[i] + other.m_data[i];
        return __new;
    }

    constexpr auto operator-(const Derived_Vector& other)
    {
        Derived_Vector __new;
        for (auto i = 0; i < N; ++i)
            __new.m_data[i] = m_data[i] - other.m_data[i];
        return __new;
    }

    constexpr auto operator*(const Derived_Vector& other)
    {
        Derived_Vector __new;
        for (auto i = 0; i < N; ++i)
            __new.m_data[i] = m_data[i] * other.m_data[i];
        return __new;
    }

    constexpr T L1Norm()
    {
        T s = 0;
        for (size_t i = 0; i < N; ++i)
        {
            s += abs( m_data[i]);
        }
        return s;
    }

    constexpr auto L2Norm()
    {
        using product_type = decltype (std::declval<T>() * std::declval<T>());
        product_type s = 0;
        for (size_t i = 0; i < N; ++i)
        {
            s += m_data[i] * m_data[i];
        }
        return sqrt(s);
    }

    constexpr auto length()
    {
        return L2Norm();
    }
};

template <typename T, size_t N>
class Vector : public Base_Vector<  T, N, Vector<T,N>   >
{
	using this_vector = Vector<T, N>;
public:
	Vector() : Base_Vector<T, N, this_vector>() {};
    
	template <typename ...Args>
	Vector(Args... args) : Base_Vector<T, N, this_vector >(args...) {};


};

}

// Вектор с операциями суммы, скалярного умножения и векторного умножения
class Vector3
{
    double* coords;

  public:
    double x() const
    {
        return coords[0];
    }
    double y() const
    {
        return coords[1];
    }
    double z() const
    {
        return coords[2];
    }

    // Конструкторы
#pragma region Constructors

    Vector3()
    {
        coords = new double[3];
    }

    Vector3(double x, double y, double z=0) : Vector3()
    {
        coords[0] = x;
        coords[1] = y;
        coords[2] = z;
    }


    Vector3(std::initializer_list<double> list) : Vector3()
    {
        coords[0] = *(list.begin());
        coords[1] = *(list.begin() + 1);
        coords[2] = *(list.begin() + 2);
    }

    // Конструктор копий
    Vector3(const Vector3& vec) : Vector3()
    {
        std::memcpy(coords, vec.coords, 3 * sizeof(double));
    }

    // Конструктор перемещения
    Vector3(Vector3&& vec) noexcept : coords(nullptr)
    {
        std::swap(coords, vec.coords);
    }

#pragma endregion

    ~Vector3()
    {
        delete[] coords;
    }

    // Математические операции
#pragma region Operators

    void setCoords(double x, double y, double z)
    {
        coords[0] = x;
        coords[1] = y;
        coords[2] = z;
    }

    Vector3 operator+(const Vector3& vec) const
    {
        Vector3 newV;
        newV.coords[0] = coords[0] + vec.coords[0];
        newV.coords[1] = coords[1] + vec.coords[1];
        newV.coords[2] = coords[2] + vec.coords[2];
        return newV;
    }

    Vector3 operator-(const Vector3& vec) const
    {
        Vector3 newV;
        newV.coords[0] = coords[0] - vec.coords[0];
        newV.coords[1] = coords[1] - vec.coords[1];
        newV.coords[2] = coords[2] - vec.coords[2];
        return newV;
    }

    Vector3 operator-() const
    {
        return {-coords[0], -coords[1], -coords[2]};
    }
    Vector3 operator+() const
    {
        return *this;
    }

    template <typename T> Vector3 operator*(const T k) const
    {
        Vector3 newV;
        newV.coords[0] = coords[0] * k;
        newV.coords[1] = coords[1] * k;
        newV.coords[2] = coords[2] * k;
        return newV;
    }

    template <typename T> Vector3 operator/(const T k) const
    {
        Vector3 newV;
        newV.coords[0] = coords[0] / k;
        newV.coords[1] = coords[1] / k;
        newV.coords[2] = coords[2] / k;
        return newV;
    }

    Vector3& operator=(const Vector3& vec)
    {
        if (this == &vec) return *this; 

        std::memcpy(coords, vec.coords, 3 * sizeof(double));
        return *this;
    }

    Vector3& operator=(Vector3&& vec)
    {
        if (&vec == this) return *this;
        
        coords = vec.coords;
        vec.coords = nullptr;
        return *this;
    }

    double length() const
    {
        return (sqrt(coords[0] * coords[0] + coords[1] * coords[1] + coords[2] * coords[2]));
    }

    Vector3 normalize()
    {
        Vector3 newV;
        double l = length();
        newV.setCoords(coords[0] / l, coords[1] / l, coords[2] / l);
        return newV;
    }

    //векторное произведение
    Vector3 operator^(const Vector3& v) const
    {
        Vector3 V;
        V.setCoords(coords[1] * v.coords[2] - coords[2] * v.coords[1],
                    coords[2] * v.coords[0] - coords[0] * v.coords[2],
                    coords[0] * v.coords[1] - coords[1] * v.coords[0]);
        return V;
    }

    //скалярное произведение
    double operator&(const Vector3& v) const
    {
        return coords[0] * v.coords[0] + coords[1] * v.coords[1] + coords[2] * v.coords[2];
    }

    //покомпонентное произведение
    Vector3 operator%(const Vector3& v) const
    {
        Vector3 newV;
        newV.setCoords( coords[0] * v.coords[0],  coords[1] * v.coords[1],coords[2] * v.coords[2]);
        return newV;
    }

    double &operator[](int i)
    {
        return coords[i];
    }

    const double& operator[](int i) const
    {
        return coords[i];
    }

    const double* operator()() const
    {
        return (coords);
    }
    template <typename T> friend Vector3 operator*(const T arg, const Vector3& v);

    template <typename T> friend Vector3 operator/(const T arg, const Vector3& v);

    static Vector3 Z()
    {
        return {0, 0, 1};
    }
    static Vector3 X()
    {
        return {0, 1, 0};
    }
    static Vector3 Y()
    {
        return {1, 0, 0};
    }

#pragma endregion
};

// Перегрузка для стандартных типов
template <typename T> Vector3 operator*(T arg, const Vector3& v)
{
    return Vector3(v.coords[0] * arg, v.coords[1] * arg, v.coords[2] * arg);
}

template <typename T> Vector3 operator/(T arg, const Vector3& v)
{
    return Vector3(v.coords[0] / arg, v.coords[1] / arg, v.coords[2] / arg);
}
