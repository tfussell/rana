#include <algorithm>
#include <iterator>
#include <ostream>
#include <stdexcept>

#include "value.hpp"

namespace rana {

value::array_range value::iter_array()
{
    assert_type(type::array_t);
    return {array_begin(), array_end()};
}

value::const_array_range value::iter_array() const
{
    assert_type(type::array_t);
    return {array_cbegin(), array_cend()};
}

value::object_range value::iter_object()
{
    assert_type(type::object_t);
    return {object_begin(), object_end()};
}

value::const_object_range value::iter_object() const
{
    assert_type(type::object_t);
    return {object_cbegin(), object_cend()};
}

const value value::null(value::type::null_t);
const value value::array(value::type::array_t);
const value value::object(value::type::object_t);
const value value::invalid(value::type::invalid_t);

void value::clear()
{
    type original_type = type_;
    set_type(type::null_t);
    set_type(original_type);
}

value::value() : type_(type::invalid_t), number_value_(0), container_(nullptr), size_(0), count_(0), max_load_factor_(0.75)
{
}

value::value(type t) : value()
{
    set_type(t);
}

value::value(const value &rhs) : value(rhs.type_)
{
    size_ = rhs.size_;
    count_ = rhs.count_;
    if(size_ > 0)
    {
        container_ = new container_value[size_];
        std::copy(rhs.container_, rhs.container_ + rhs.size_, container_);
    }
    max_load_factor_ = rhs.max_load_factor_;
    string_value_ = rhs.string_value_;
    number_value_ = rhs.number_value_;
}

value::value(std::initializer_list<value> ilist) : value(type::array_t)
{
    for(auto &v : ilist)
    {
        append(v);
    }
}

value::value(std::initializer_list<std::pair<std::string, value>> ilist) : value(type::object_t)
{
    for(auto &v : ilist)
    {
        insert(v.first, v.second);
    }
}

value::value(bool b) : value(b ? type::true_t : type::false_t)
{
}

value::value(int i) : value(type::number_t)
{
    number_value_ = i;
}

value::value(double d) : value(type::number_t)
{
    number_value_ = d;
}

value::value(const char *s) : value(type::string_t)
{
    string_value_ = s;
}

value::value(const std::string &s) : value(type::string_t)
{
    string_value_ = s;
}

value::~value()
{
    clear();
}

value value::copy() const
{
    return value(*this);
}

bool value::empty() const
{
    return size() == 0;
}

std::size_t value::size() const
{
    if(is_container())
    {
        return count_;
    }
    
    throw std::runtime_error("invalid operation");
}
    
value::reference value::at(std::size_t index)
{
    assert_type(type::array_t);
    
    if(index >= count_)
    {
        throw std::out_of_range("out of range");
    }
    
    return container_[index].second;
}
    
value::const_reference value::at(std::size_t index) const
{
    assert_type(type::array_t);
    
    if(index >= count_)
    {
        throw std::out_of_range("out of range");
    }
    return container_[index].second;
}

value::reference value::at(const std::string &key)
{
    assert_type(type::object_t);
    
    auto match = find(key);
    
    if(match == object_end())
    {
        throw std::out_of_range("no element found with specified key");
    }
    
    return match->second;
}

value::const_reference value::at(const std::string &key) const
{
    assert_type(type::object_t);

    auto match = find(key);
    
    if(match == object_end())
    {
        throw std::out_of_range("no element found with specified key");
    }
    
    return match->second;
}

value &value::operator()(const value &v)
{
    assert_type(type::array_t);
    append(v);
    return *this;
}

value value::operator()(const value &v) const
{
    assert_type(type::array_t);
    value copy = *this;
    copy.append(v);
    return copy;
}

value &value::operator()(const std::string &key, const value &value)
{
    assert_type(type::object_t);
    insert(key, value);
    return *this;
}

value value::operator()(const std::string &key, const value &v) const
{
    assert_type(type::object_t);
    value copy = *this;
    copy.insert(key, v);
    return copy;
}

void value::insert(const std::string &key, const value &v)
{
    assert_type(type::object_t);
    (*this)[key] = v;
}

value &value::operator=(value rhs)
{
    swap(*this, rhs);
    return *this;
}

value &value::operator=(std::initializer_list<value> ilist)
{
    value temp(ilist);
    swap(*this, temp);
    return *this;
}

void swap(value &first, value &second)
{
    using std::swap;
    
    swap(first.type_, second.type_);
    swap(first.string_value_, second.string_value_);
    swap(first.number_value_, second.number_value_);
    swap(first.container_, second.container_);
    swap(first.size_, second.size_);
    swap(first.count_, second.count_);
    swap(first.max_load_factor_, second.max_load_factor_);
}

value::value(value &&other) : value()
{
    swap(*this, other);
}

void value::append(const value &v)
{
    assert_type(type::array_t);
    
    if(count_ + 1 > size_)
    {
        grow();
    }
    
    container_[count_++].second = v;
}

value::reference value::operator[](std::size_t index)
{
    assert_type(type::array_t);
    return container_[index].second;
}

value::const_reference value::operator[](std::size_t index) const
{
    assert_type(type::array_t);
    return container_[index].second;
}

value &value::operator[](const std::string &key)
{
    assert_type(type::object_t);
    
    auto match = find(key);
    
    if(match != object_end())
    {
        return match->second;
    }

    reserve(count_ + 1);
    
    size_type index = hash(key);
    size_type end = index == 0 ? size_ - 1 : index - 1;
    
    while(container_[index].second.is_valid() && !key_equal_(container_[index].first, key) && index != end)
    {
        index++;
        
        if(index == size_)
        {
            index = 0;
        }
    }
    
    container_value &found = container_[index];
    
    if(!found.second.is_valid())
    {
        count_++;
        found = std::make_pair(key, value::null);
    }
    
    return found.second;
}

const value &value::operator[](const std::string &key) const
{
    assert_type(type::object_t);
    return at(key);
}

void value::assert_type(type t) const
{
    if(type_ != t)
    {
        std::string type_string;
        
        switch(type_)
        {
            case type::null_t: type_string = "null"; break;
            case type::true_t: type_string = "true"; break;
            case type::false_t: type_string = "false"; break;
            case type::number_t: type_string = "number"; break;
            case type::string_t: type_string = "string"; break;
            case type::array_t: type_string = "array"; break;
            case type::object_t: type_string = "object"; break;
            case type::invalid_t: type_string = "invalid"; break;
        }
        
        throw std::runtime_error("operation not supported for type " + type_string);
    }
}

void value::set_type(type t)
{
    if(type_ == t)
    {
        return;
    }
    
    switch(type_)
    {
        case type::array_t:
            if(container_ != nullptr)
            {
                delete[] container_;
            }
            container_ = nullptr;
            size_ = 0;
            count_ = 0;
            break;
        case type::object_t:
            if(container_ != nullptr)
            {
                delete[] container_;
            }
            container_ = nullptr;
            size_ = 0;
            count_ = 0;
            break;
        case type::number_t:
            number_value_ = 0;
            break;
        case type::string_t:
            string_value_.clear();
            break;
        case type::true_t:
        case type::false_t:
        case type::null_t:
        case type::invalid_t:
            break;
    }
    
    type_ = t;
}

std::ostream &operator<<(std::ostream &os, const value& v)
{
    if(v.type_ == value::type::number_t)
    {
        os << v.number_value_;
    }
    else if(v.type_ == value::type::null_t)
    {
        os << "null";
    }
    else if(v.type_ == value::type::false_t)
    {
        os << "false";
    }
    else if(v.type_ == value::type::true_t)
    {
        os << "true";
    }
    else if(v.type_ == value::type::string_t)
    {
        os << "\"" << v.string_value_ << "\"";
    }
    else if(v.type_ == value::type::object_t)
    {
        os << "{";
        std::size_t i = 0;
        
        for(auto &v2 : v.iter_object())
        {
            os << "\"" << v2.first << "\" : " << v2.second;
            
            if(++i < v.size())
            {
                os << ", ";
            }
        }
        
        os << "}";
    }
    else if(v.type_ == value::type::array_t)
    {
        os << "[";
        
        for(std::size_t i = 0; i < v.size(); i++)
        {
            os << v[i];
            
            if(i < v.size() - 1)
            {
                os << ", ";
            }
        }
        
        os << "]";
    }
    
    return os;
}

value::object_iterator value::find(const std::string &key)
{
    if(size_ == 0)
    {
        return object_end();
    }
    
    auto index = hash(key);
    size_type end_index = index == 0 ? size_ - 1 : index - 1;
    
    while(container_[index].second.is_valid() && !key_equal_(container_[index].first, key) && index != end_index)
    {
        index++;
        
        if(index == size_)
        {
            index = 0;
        }
    }
    
    container_value &found = container_[index];
    
    if(found.second.is_valid() && key_equal_(found.first, key))
    {
        return object_iterator(container_, index, size_);
    }
    
    return object_end();
}

value::const_object_iterator value::find(const std::string &key) const
{
    if(size_ == 0)
    {
        return object_end();
    }
    
    auto index = hash(key);
    size_type end_index = index == 0 ? size_ - 1 : index - 1;
    
    while(container_[index].second.is_valid() && !key_equal_(container_[index].first, key) && index != end_index)
    {
        index++;
        
        if(index == size_)
        {
            index = 0;
        }
    }
    
    if(container_[index].second.is_valid() && key_equal_(container_[index].first, key))
    {
        return const_object_iterator(container_, index, size_);
    }
    
    return object_end();
}
    
} // namespace rana
