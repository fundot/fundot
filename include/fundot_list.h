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

#ifndef FUNDOT_LIST_H
#define FUNDOT_LIST_H

#include <cstddef>
#include <list>

namespace fundot {
template<typename T>
class List {
public:
    class Iterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = value_type*;
        using reference = value_type&;

        Iterator(typename std::list<T>::iterator lst_iter) : lst_iter_(lst_iter)
        {
        }

        reference operator*() const { return *lst_iter_; }
        pointer operator->() const { return &**this; }

        Iterator& operator++()
        {
            ++lst_iter_;
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
            return lst_iter_ == other.lst_iter_;
        }

        bool operator!=(Iterator other) const
        {
            return lst_iter_ != other.lst_iter_;
        }

    private:
        typename std::list<T>::iterator lst_iter_;
    };

    class ConstIterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = const value_type*;
        using reference = const value_type&;

        ConstIterator(typename std::list<T>::const_iterator lst_iter)
            : lst_iter_(lst_iter)
        {
        }

        reference operator*() const { return *lst_iter_; }
        pointer operator->() const { return &**this; }

        ConstIterator& operator++()
        {
            ++lst_iter_;
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
            return lst_iter_ == other.lst_iter_;
        }

        bool operator!=(ConstIterator other) const
        {
            return lst_iter_ != other.lst_iter_;
        }

    private:
        typename std::list<T>::const_iterator lst_iter_;
    };

    Iterator begin() { return Iterator(lst_.begin()); }
    Iterator end() { return Iterator(lst_.end()); }

    ConstIterator begin() const { return ConstIterator(lst_.begin()); }
    ConstIterator end() const { return ConstIterator(lst_.end()); }

    ConstIterator cbegin() const { return ConstIterator(lst_.begin()); }
    ConstIterator cend() const { return ConstIterator(lst_.end()); }

    T& operator[](std::size_t idx) { return lst_[idx]; }
    T operator[](std::size_t idx) const { return lst_[idx]; }

    T& front() { return lst_.front(); }
    T front() const { return lst_.front(); }

    T& back() { return lst_.back(); }
    T back() const { return lst_.back(); }

    std::size_t size() const { return lst_.size(); }

    void clear() { lst_.clear(); }
    void pushBack(const T& elem) { lst_.push_back(elem); }
    void popBack() { lst_.pop_back(); }

private:
    std::list<T> lst_;
};

}  // namespace fundot

#endif
