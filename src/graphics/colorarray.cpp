/**
 * @file graphics/colorarray.cpp
 * @author Mika Haarahiltunen
 */

#include <graphics/colorarray.h>

#include <algorithm>

#include <graphics/color.h>
#include <graphics/runtimeassert.h>

ColorArray::~ColorArray()
{
    delete [] colors_;
}

ColorArray::ColorArray(const int size)
:   colors_(0),
    size_(size)
{
    GRAPHICS_RUNTIME_ASSERT(size > 0);
    colors_ = new Color[size];
}

ColorArray::ColorArray(const ColorArray& other)
:   colors_(0),
    size_(other.size_)
{
    colors_ = new Color[size_];
    std::memcpy(colors_, other.colors_, size_ * sizeof(Color));
}

ColorArray& ColorArray::operator=(const ColorArray& other)
{
    if (size_ == other.size_)
    {
        std::memcpy(colors_, other.colors_, size_ * sizeof(Color));
    }
    else
    {
        ColorArray(other).swap(*this);
    }

    return *this;
}

Color& ColorArray::operator [](const int index)
{
    GRAPHICS_RUNTIME_ASSERT(index >= 0 && index < size_);
    return colors_[index];
}

const Color ColorArray::operator [](const int index) const
{
    GRAPHICS_RUNTIME_ASSERT(index >= 0 && index < size_);
    return colors_[index];
}

Color* ColorArray::data()
{
    return colors_;
}

const Color* ColorArray::data() const
{
    return colors_;
}

float* ColorArray::componentData()
{
    return colors_->data();
}

const float* ColorArray::componentData() const
{
    return colors_->data();
}

ColorArray::Iterator ColorArray::begin()
{
    return colors_;
}

ColorArray::ConstIterator ColorArray::begin() const
{
    return colors_;
}

ColorArray::Iterator ColorArray::end()
{
    return colors_ + size_;
}

ColorArray::ConstIterator ColorArray::end() const
{
    return colors_ + size_;
}

int ColorArray::size() const
{
    return size_;
}

void ColorArray::fill(const Color& c)
{
    std::fill(begin(), end(), c);
}

void ColorArray::swap(ColorArray& other)
{
    std::swap(colors_, other.colors_);
    std::swap(size_, other.size_);
}
