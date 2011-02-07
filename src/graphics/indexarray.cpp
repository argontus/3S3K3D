/**
 * @file graphics/indexarray.cpp
 * @author Mika Haarahiltunen
 */

#include <graphics/indexarray.h>

#include <algorithm>
#include <cstring>

#include <graphics/runtimeassert.h>

IndexArray::~IndexArray()
{
    delete [] indices_;
}

IndexArray::IndexArray(const int size)
:   indices_(0),
    size_(size)
{
    GRAPHICS_RUNTIME_ASSERT(size > 0);
    indices_ = new uint32_t[size];
}

IndexArray::IndexArray(const IndexArray& other)
:   indices_(0),
    size_(other.size_)
{
    indices_ = new uint32_t[size_];
    std::memcpy(indices_, other.indices_, size_ * sizeof(uint32_t));
}

IndexArray& IndexArray::operator=(const IndexArray& other)
{
    if (size_ == other.size_)
    {
        std::memcpy(indices_, other.indices_, size_ * sizeof(uint32_t));
    }
    else
    {
        IndexArray(other).swap(*this);
    }

    return *this;
}

uint32_t& IndexArray::operator [](const int index)
{
    GRAPHICS_RUNTIME_ASSERT(index >= 0 && index < size_);
    return indices_[index];
}

uint32_t IndexArray::operator [](const int index) const
{
    GRAPHICS_RUNTIME_ASSERT(index >= 0 && index < size_);
    return indices_[index];
}

uint32_t* IndexArray::data()
{
    return indices_;
}

const uint32_t* IndexArray::data() const
{
    return indices_;
}

IndexArray::Iterator IndexArray::begin()
{
    return indices_;
}

IndexArray::ConstIterator IndexArray::begin() const
{
    return indices_;
}

IndexArray::Iterator IndexArray::end()
{
    return indices_ + size_;
}

IndexArray::ConstIterator IndexArray::end() const
{
    return indices_ + size_;
}

int IndexArray::size() const
{
    return size_;
}

void IndexArray::swap(IndexArray& other)
{
    std::swap(indices_, other.indices_);
    std::swap(size_, other.size_);
}
