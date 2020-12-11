/**
 * MIT License

 * Copyright (c) 2020 Jiacheng Huang

 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:

 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.

 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef FUNDOT_VECTOR_H
#define FUNDOT_VECTOR_H

#include <cstddef>
#include <vector>

namespace fundot {
template<typename T>
class Vector {
public:
    class Iterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = value_type*;
        using reference = value_type&;

        Iterator(typename std::vector<T>::iterator vect_iter)
            : vect_iter_(vect_iter)
        {
        }

        reference operator*() const { return *vect_iter_; }
        pointer operator->() const { return &**this; }

        Iterator& operator++()
        {
            ++vect_iter_;
            return *this;
        }

        Iterator operator++(int)
        {
            Iterator temp = *this;
            ++(*this);
            return temp;
        }

        bool operator==(Iterator other) const
        {
            return vect_iter_ == other.vect_iter_;
        }

        bool operator!=(Iterator other) const
        {
            return vect_iter_ != other.vect_iter_;
        }

    private:
        typename std::vector<T>::iterator vect_iter_;
    };

    class ConstIterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = const value_type*;
        using reference = const value_type&;

        ConstIterator(typename std::vector<T>::const_iterator vect_iter)
            : vect_iter_(vect_iter)
        {
        }

        reference operator*() const { return *vect_iter_; }
        pointer operator->() const { return &**this; }

        ConstIterator& operator++()
        {
            ++vect_iter_;
            return *this;
        }

        ConstIterator operator++(int)
        {
            ConstIterator temp = *this;
            ++(*this);
            return temp;
        }

        bool operator==(ConstIterator other) const
        {
            return vect_iter_ == other.vect_iter_;
        }

        bool operator!=(ConstIterator other) const
        {
            return vect_iter_ != other.vect_iter_;
        }

    private:
        typename std::vector<T>::const_iterator vect_iter_;
    };

    Iterator begin() { return Iterator(vect_.begin()); }
    Iterator end() { return Iterator(vect_.end()); }

    ConstIterator begin() const { return ConstIterator(vect_.begin()); }
    ConstIterator end() const { return ConstIterator(vect_.end()); }

    ConstIterator cbegin() const { return ConstIterator(vect_.begin()); }
    ConstIterator cend() const { return ConstIterator(vect_.end()); }

    T& operator[](std::size_t idx) { return vect_[idx]; }
    T operator[](std::size_t idx) const { return vect_[idx]; }

    T& front() { return vect_.front(); }
    T front() const { return vect_.front(); }

    T& back() { return vect_.back(); }
    T back() const { return vect_.back(); }

    std::size_t size() const { return vect_.size(); }

    void clear() { vect_.clear(); }
    void pushBack(const T& elem) { vect_.push_back(elem); }
    void popBack() { vect_.pop_back(); }

private:
    std::vector<T> vect_;
};

}  // namespace fundot

#endif
