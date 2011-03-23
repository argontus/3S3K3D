/**
 * @file geometry/vector2array.cpp
 * @author Mika Haarahiltunen
 */

#include <geometry/vector2array.h>

// TODO: get rid of this #include
#include <algorithm>

#include <cstring>

#include <geometry/transform2.h>

Vector2Array::~Vector2Array()
{
    delete [] vertices_;
}

Vector2Array::Vector2Array(const int size)
:   vertices_(0),
    size_(size)
{
    GEOMETRY_RUNTIME_ASSERT(size > 0);
    vertices_ = new Vector2[size];
}

Vector2Array::Vector2Array(const Vector2Array& other)
:   vertices_(0),
    size_(other.size_)
{
    vertices_ = new Vector2[size_];
    std::memcpy(vertices_, other.vertices_, size_ * sizeof(Vector2));
}

Vector2Array& Vector2Array::operator =(const Vector2Array& other)
{
    if (size_ == other.size_)
    {
        std::memcpy(vertices_, other.vertices_, size_ * sizeof(Vector2));
    }
    else
    {
        Vector2Array(other).swap(*this);
    }

    return *this;
}

Vector2& Vector2Array::operator [](const int index)
{
    GEOMETRY_RUNTIME_ASSERT(index >= 0 && index < size_);
    return vertices_[index];
}

const Vector2 Vector2Array::operator [](const int index) const
{
    GEOMETRY_RUNTIME_ASSERT(index >= 0 && index < size_);
    return vertices_[index];
}

Vector2* Vector2Array::data()
{
    return vertices_;
}

const Vector2* Vector2Array::data() const
{
    return vertices_;
}

float* Vector2Array::componentData()
{
    return vertices_->data();
}

const float* Vector2Array::componentData() const
{
    return vertices_->data();
}

Vector2Array::Iterator Vector2Array::begin()
{
    return vertices_;
}

Vector2Array::ConstIterator Vector2Array::begin() const
{
    return vertices_;
}

Vector2Array::Iterator Vector2Array::end()
{
    return vertices_ + size_;
}

Vector2Array::ConstIterator Vector2Array::end() const
{
    return vertices_ + size_;
}

int Vector2Array::size() const
{
    return size_;
}

const Extents2 Vector2Array::extents() const
{
    return Extents2(begin(), end());
}

const Extents2 Vector2Array::extents(const Transform2& transform) const
{
    Extents2 extents;

    for (int i = 0; i < size_; ++i)
    {
        const Vector2 p = transform.applyForward(vertices_[i]);
        extents.enclose(p);
    }

    return extents;
}

void Vector2Array::transformBy(const Transform2& transform)
{
    transform.applyForward(vertices_, vertices_ + size_, vertices_);
}

void Vector2Array::translateBy(const Vector2& translation)
{
    for (int i = 0; i < size_; ++i)
    {
        vertices_[i] += translation;
    }
}

void Vector2Array::rotateBy(const Matrix2x2& rotation)
{
    for (int i = 0; i < size_; ++i)
    {
        vertices_[i] = vertices_[i] * rotation;
    }
}

void Vector2Array::scaleBy(const float scaling)
{
    GEOMETRY_RUNTIME_ASSERT(scaling > 0.0f);

    for (int i = 0; i < size_; ++i)
    {
        vertices_[i] *= scaling;
    }
}

void Vector2Array::fill(const Vector2& v)
{
    std::fill(begin(), end(), v);
}

void Vector2Array::swap(Vector2Array& other)
{
    std::swap(vertices_, other.vertices_);
    std::swap(size_, other.size_);
}
