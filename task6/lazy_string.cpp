#include "lazy_string.h"
#include <iostream>
#include <memory> // for smart pointer
#include <stdexcept> // for out_of_range

using namespace std;

lazy_string::lstr_char &lazy_string::lstr_char::operator=(char c) {
    if ((*lstr).to_lstr.use_count() > 0) {
        (*lstr).first = 0;
        (*lstr).to_lstr = make_shared<string>((*lstr).to_lstr).substr((*lstr).first, (*lstr).size_lstr));
    }
    (*(*lstr).to_lstr)[(*lstr).first + pos] = c;
}

lazy_string::lstr_char::lstr_char(lazy_string *lstr_new, size_t pos_new) {
    lstr = lstr_new;
    pos = pos_new;
};

lazy_string::lstr_char::operator char() const {
    return (*(*lstr).to_lstr)[(*lstr).first + pos];
}

lazy_string::operator string() {
    return (*to_lstr).substr(first, size_lstr);
}

lazy_string::lazy_string() {
    to_lstr = make_shared<string>("");
    first = size_lstr = 0;
}

lazy_string::lazy_string(const string &str) {
    to_lstr = make_shared<string>(str);
    first = 0;
    size_lstr = str.size();
}

lazy_string::lazy_string(const shared_ptr<string> lstr, size_t first_new, size_t size_new) {
    to_lstr = lstr;
    first = first_new;
    size_lstr = size_new;
}

size_t lazy_string::size() const {
    return size_lstr;
}

size_t lazy_string::length() const {
    return size_lstr;
}

lazy_string lazy_string::substr(size_t pos, size_t count) {
    if (pos > size_lstr)
        throw out_of_range("lazy_string(method substr): great value for the position");
    else {
        if (pos + count > size_lstr)
            return lazy_string(to_lstr, first + pos, size_lstr - pos);
        else
            return lazy_string(to_lstr, first + pos, count);
    }
};

lazy_string::lstr_char lazy_string::at(size_t pos) {
    if (pos >= size_lstr)
        throw out_of_range("lazy_string(method at): great value for the position");
    return lstr_char(this, pos);
}

const char &lazy_string::at(size_t pos) const {
    if (pos >= size_lstr)
        throw out_of_range("lazy_string(method at): great value for the position");
    return (*to_lstr)[first + pos];
}

lazy_string::lstr_char lazy_string::operator[](size_t pos) {
    if (pos >= size_lstr)
        throw out_of_range("great index");
    return lstr_char(this, pos);
}

const char &lazy_string::operator[](size_t pos) const {
    if (pos >= size_lstr)
        throw out_of_range("great index");
    return (*to_lstr)[first + pos];
}

istream &operator>>(istream &in, lazy_string &lstr) {
    shared_ptr<string> str = make_shared<string>();
    in >> *str;
    lstr.to_lstr = str;
    lstr.first = 0;
    lstr.size_lstr = (*str).size();
    return in;
}

ostream &operator<<(ostream &out, lazy_string &lstr) {
    for (size_t i = 0; i < lstr.size(); i++)
        out << lstr[lstr.first + i];
    return out;
}


