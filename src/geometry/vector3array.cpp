/**
 * @file geometry/vector3array.cpp
 * @author Mika Haarahiltunen
 */

#include <geometry/vector3array.h>

#include <algorithm>
#include <cstring>

#include <geometry/transform3.h>

Vector3Array::~Vector3Array()
{
    delete [] vertices_;
}

Vector3Array::Vector3Array(const int size)
:   vertices_(0),
    size_(size)
{
    GEOMETRY_RUNTIME_ASSERT(size > 0);
    vertices_ = new Vector3[size];
}

Vector3Array::Vector3Array(const Vector3Array& other)
:   vertices_(0),
    size_(other.size_)
{
    vertices_ = new Vector3[size_];
    std::memcpy(vertices_, other.vertices_, size_ * sizeof(Vector3));
}

Vector3Array& Vector3Array::operator =(const Vector3Array& other)
{
    if (size_ == other.size_)
    {
        std::memcpy(vertices_, other.vertices_, size_ * sizeof(Vector3));
    }
    else
    {
        Vector3Array(other).swap(*this);
    }

    return *this;
}

Vector3& Vector3Array::operator [](const int index)
{
    GEOMETRY_RUNTIME_ASSERT(index >= 0 && index < size_);
    return vertices_[index];
}

const Vector3 Vector3Array::operator [](const int index) const
{
    GEOMETRY_RUNTIME_ASSERT(index >= 0 && index < size_);
    return vertices_[index];
}

Vector3* Vector3Array::data()
{
    return vertices_;
}

const Vector3* Vector3Array::data() const
{
    return vertices_;
}

float* Vector3Array::componentData()
{
    return vertices_->data();
}

const float* Vector3Array::componentData() const
{
    return vertices_->data();
}

Vector3Array::Iterator Vector3Array::begin()
{
    return vertices_;
}

Vector3Array::ConstIterator Vector3Array::begin() const
{
    return vertices_;
}

Vector3Array::Iterator Vector3Array::end()
{
    return vertices_ + size_;
}

Vector3Array::ConstIterator Vector3Array::end() const
{
    return vertices_ + size_;
}

int Vector3Array::size() const
{
    return size_;
}

const Extents3 Vector3Array::extents() const
{
    Extents3 extents;

    for (int i = 0; i < size_; ++i)
    {
        extents.growToContain(vertices_[i]);
    }

    return extents;
}

const Extents3 Vector3Array::extents(const Transform3& transform) const
{
    Extents3 extents;

    for (int i = 0; i < size_; ++i)
    {
        const Vector3 p = transform.applyForward(vertices_[i]);
        extents.growToContain(p);
    }

    return extents;
}

void Vector3Array::transformBy(const Transform3& transform)
{
    transform.applyForward(vertices_, vertices_ + size_, vertices_);
}

void Vector3Array::translateBy(const Vector3& translation)
{
    for (int i = 0; i < size_; ++i)
    {
        vertices_[i] += translation;
    }
}

void Vector3Array::rotateBy(const Matrix3x3& rotation)
{
    for (int i = 0; i < size_; ++i)
    {
        vertices_[i] = product(vertices_[i], rotation);
    }
}

void Vector3Array::scaleBy(const float scaling)
{
    GEOMETRY_RUNTIME_ASSERT(scaling > 0.0f);

    for (int i = 0; i < size_; ++i)
    {
        vertices_[i] *= scaling;
    }
}

void Vector3Array::fill(const Vector3& v)
{
    std::fill(begin(), end(), v);
}

void Vector3Array::swap(Vector3Array& other)
{
    std::swap(vertices_, other.vertices_);
    std::swap(size_, other.size_);
}
