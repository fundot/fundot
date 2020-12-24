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

#ifndef FUNDOT_SET_H
#define FUNDOT_SET_H

#include <cstddef>
#include <iterator>
#include <unordered_set>

namespace fundot {
template<typename T, typename Hash = std::hash<T>>
class UnorderedSet {
public:
    class Iterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = const value_type*;
        using reference = const value_type&;

        Iterator(typename std::unordered_set<T, Hash>::iterator set_iter)
            : set_iter_(set_iter)
        {
        }

        reference operator*() const { return *set_iter_; }
        pointer operator->() const { return &**this; }

        Iterator& operator++()
        {
            ++set_iter_;
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
            return set_iter_ == other.set_iter_;
        }

        bool operator!=(Iterator other) const
        {
            return set_iter_ != other.set_iter_;
        }

    private:
        typename std::unordered_set<T, Hash>::iterator set_iter_;
    };

    class ConstIterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = const value_type*;
        using reference = const value_type&;

        ConstIterator(typename std::unordered_set<T, Hash>::iterator set_iter)
            : set_iter_(set_iter)
        {
        }

        reference operator*() const { return *set_iter_; }
        pointer operator->() const { return &**this; }

        ConstIterator& operator++()
        {
            ++set_iter_;
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
            return set_iter_ == other.set_iter_;
        }

        bool operator!=(ConstIterator other) const
        {
            return set_iter_ != other.set_iter_;
        }

    private:
        typename std::unordered_set<T, Hash>::iterator set_iter_;
    };

    Iterator begin() { return Iterator(set_.begin()); }
    Iterator end() { return Iterator(set_.end()); }

    ConstIterator begin() const { return ConstIterator(set_.begin()); }
    ConstIterator end() const { return ConstIterator(set_.end()); }

    ConstIterator cbegin() const { return ConstIterator(set_.begin()); }
    ConstIterator cend() const { return ConstIterator(set_.end()); }

    void clear() { set_.clear(); }

    void emplace(const T& elem) { set_.emplace(elem); }

    void erase(const T& elem) { set_.erase(elem); }

    Iterator find(const T& key) { return Iterator(set_.find(key)); }
    ConstIterator find(const T& key) const
    {
        return ConstIterator(set_.find(key));
    }

    bool contains(const T& key) { return set_.find(key) != set_.end(); }

private:
    std::unordered_set<T, Hash> set_;
};

}  // namespace fundot

#endif
