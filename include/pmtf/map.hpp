/*-*-c++-*-*/
/*
 * Copyright 2021 John Sallay
 *
 * SPDX-License-Identifier: LGPL-3.0
 *
 */
#pragma once

#include <pmtf/pmtf_generated.h>
#include <complex>
#include <iostream>
#include <map>
#include <memory>
#include <typeindex>
#include <typeinfo>
#include <vector>

#include <pmtf/base.hpp>
#include <pmtf/wrap.hpp>

// What if this was just a map?
// Then I wouldn't have a serialize function in it. and it wouldn't be derived from base.
/*
What should the class hierarchy be???
Presently we have a base and then several classes dervice from that.
I then define wrappers around pointers to those classes that make it 
easy to work with them.
Can I just cut out the middle man and have the wrapper class be the main class?
Then we don't need all of the static make functions.  It handles all of that for
us.  Can I do this in a useful way?
So I have a pmt base class and derive from that scalar, uniform vector, vector, and map.
In the scalar case and uniform vector case I can just store it.  The vector would need to store
variants or pointers.
1) pmt is pointer, classes are wrappers to make it convenient.
    Need one class and one wrapper for each type
2) pmt is class with data.  Polymorphism doesn't buy me anything here, because I am avoiding creating
    pointers.  I have to use variants.

Let's start with polymorphism.
I need the following set of classes.
scalar
    uniform_vector
    vector
    map
I need a wrapper class for each one.
I need a generator class that can produce any one of them.

*/

namespace pmtf {

class map : public base {
public:
    using traits = MapString::Traits;
    using type = typename traits::type;

    using key_type = std::string;
    using mapped_type = std::shared_ptr<base>;
    using value_type = std::pair<const key_type, mapped_type>;
    using reference = value_type&;
    using const_reference = const value_type&;
    using map_type = std::map<key_type, mapped_type>;

    map() {}
    ~map() {}

    /**************************************************************************
    * Iterators
    **************************************************************************/
    typename map_type::iterator begin() noexcept { return _map.begin(); }
    typename map_type::const_iterator begin() const noexcept { return _map.begin(); }
    typename map_type::iterator end() noexcept { return _map.end(); }
    typename map_type::const_iterator end() const noexcept { return _map.end(); }

    /**************************************************************************
    * Element Access
    **************************************************************************/
    mapped_type& at(const key_type& key) { return _map.at(key); }
    const mapped_type& at(const key_type& key ) const { return _map.at(key); }
    mapped_type& operator[]( const key_type& key) { return _map[key]; }

    constexpr Data data_type() override { return DataTraits<type>::enum_value; }

    void print(std::ostream& os) const {
        os << "{";
        for (const auto& [k, v]: *this) {
            os << k << ": ";
            v->print(os);
            os << ", ";
        }
        os << "}";
    } 
private:
    // This stores the actual data.
    map_type _map;

    //virtual void serialize_setup();

};

/*template <class T>
class map : public base
{
public:
    using key_type = std::string;
    using mapped_type = wrap;
    using value_type = std::pair<const key_type, mapped_type>;
    using reference = value_type&;
    using const_reference = const value_type&;
    using map_type = std::map<T, wrap>;

    typedef std::shared_ptr<map> sptr;
    static sptr make(const map_type& val)
    {
        return std::make_shared<map<T>>(val);
    }
    static sptr from_buffer(const uint8_t* buf, size_t size)
    {
        return std::make_shared<map<T>>(buf, size);
    }
    static sptr from_pmt(const pmtf::Pmt* fb_pmt)
    {
        return std::make_shared<map<T>>(fb_pmt);
    }*/

    /**************************************************************************
    * Constructors
    **************************************************************************/

    /**
     * @brief Construct a new pmt map object that is empty
     *
     * @param
     */
    //map();

    /**
     * @brief Construct a new pmt map object from a std::map
     *
     * @param val
     */
    //map(const map_type& val);
    /**
     * @brief Construct a new pmt map object from a map
     *
     * @param val
     */
    //map(const map& val);
    /**
     * @brief Construct a new pmt map object from a serialized flatbuffer
     *
     * @param buf
     * @param size
     */
    //map(const uint8_t* buf, size_t size);
    /**
     * @brief Construct a new pmt map object from a flatbuffers interpreted Pmt object
     *
     * @param fb_pmt
     */
    //map(const pmtf::Pmt* fb_pmt);

    /**************************************************************************
    * Copy Assignment
    **************************************************************************/
    //map& operator=(const map& other);
    //map& operator=(map&& other) noexcept;

    /**************************************************************************
    * Element Access
    **************************************************************************/
    //mapped_type& at(const key_type& key);
    //const mapped_type& at(const key_type& key ) const;
    //mapped_type& operator[]( const key_type& key);

    /**************************************************************************
    * Iterators
    **************************************************************************/
    /*typename map_type::iterator begin() noexcept { return _map.begin(); }
    typename map_type::const_iterator begin() const noexcept { return _map.begin(); }
    //typename std::map<T, pmt_sptr>::const_iterator begin() const noexcept { return _map.begin(); }
    typename map_type::iterator end() noexcept { return _map.end(); }
    typename map_type::const_iterator end() const noexcept { return _map.end(); }
    //typename const std::map<T, pmt_sptr>::iterator end() const noexcept { return _map.end(); }*/

    /**************************************************************************
    * Capacity
    **************************************************************************/
    /*bool empty() const noexcept { return _map.empty(); }
    size_t size() const noexcept { return _map.size(); }
    size_t max_size() const noexcept { return _map.max_size(); }
*/
    /**************************************************************************
    * Modifiers
    **************************************************************************/
  /*  


    flatbuffers::Offset<void> rebuild_data(flatbuffers::FlatBufferBuilder& fbb);

    void print(std::ostream& os) const {
        os << "{";
        for (const auto& [k, v]: *this) {
            os << k << ": " << v << ", "; 
        }
        os << "}";
    } 


private:
    // This stores the actual data.
    map_type _map;

    void fill_flatbuffer();
    virtual void serialize_setup();


};*/

/*map<std::string> get_map(const wrap& x) {
    if (x.ptr()->data_type() == Data::PmtMap)
        return map<std::string>(std::dynamic_pointer_cast<map<std::string>>(x.ptr()));
    else
        throw std::runtime_error("Cannot convert to map");
}*/

}
