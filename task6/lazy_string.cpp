#include "lazy_string.h"
#include <iostream>
#include <stdexcept>

lazy_string::operator std::string() {
    return str.substr(first, size_str);
}

lazy_string::lazy_string() {
    str = std::string();
    first = size_str = 0;
}

lazy_string::lazy_string(const std::string &str_new) {
    str = str_new;
    first = 0;
    size_str = str.size();
}

lazy_string::lazy_string(const lazy_string &lstr, size_t first_new, size_t size_new) {
    str = lstr.str;
    first = first_new;
    size_str = size_new;
}

size_t lazy_string::size() const {
    return size_str;
}

size_t lazy_string::length() const {
    return size_str;
}

lazy_string lazy_string::substr(size_t pos, size_t count) {
    if (pos > size_str)
        throw std::out_of_range("lazy_string(method substr): great value for the position");
    else {
        if (pos + count > size_str)
            return lazy_string(str, first + pos, size_str - pos);
        else
            return lazy_string(str, first + pos, count);
    }
};

const char &lazy_string::at(size_t pos) const {
    if (pos >= size_str)
        throw std::out_of_range("lazy_string(method at): great value for the position");
    return str[first + pos];
}

const char &lazy_string::operator[](size_t pos) const {
    return at(pos);
}

std::istream &operator>>(std::istream &in, lazy_string &lstr) {
    in >> lstr.str;
    lstr.first = 0;
    lstr.size_str = lstr.str.size();
    return in;
}

std::ostream &operator<<(std::ostream &out, lazy_string &lstr) {
    for (size_t pos = lstr.first, i = 0; i < lstr.size_str; ++pos, ++i)
        out << lstr[pos];
    return out;
}