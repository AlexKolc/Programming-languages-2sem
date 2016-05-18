#ifndef LAZY_STRING_H
#define LAZY_STRING_H

#include <string>
#include <istream>
#include <ostream>
#include <memory> // for smart pointer

using namespace std;

class lazy_string {
    struct lstr_char {
        friend class lazy_string;

        lstr_char &operator=(char c);

        operator char() const;

    private:
        lstr_char(lazy_string *lstr, size_t pos);

        size_t pos;
        lazy_string * lstr;
    };

private:
    size_t first, size_lstr;
    shared_ptr<string> to_lstr;

    lazy_string(const shared_ptr<string> lstr, size_t first_new, size_t size_new);

public:
    /**
     * Creates std::string using Copy-on-Write method from this lasy_string.
     *
     * @return Object instance std::string.
     */
    operator string();

    /**
     * Construct empty lazy_string.
     */

    lazy_string();

    /**
     * Construct new lazy_string from std::string.
     *
     * @param str a std::string.
     */

    lazy_string(const string &str);

    /**
     * Returns the length of the string.
     *
     * @return The length of the string.
     */
    size_t size() const;

    size_t length() const;

    /**
     * Returns a new constructed std::string object
     * with it's value initialized to a copy of a
     * substring of this object.
     *
     * @param pos Position of the first character to be copied as a substring.
     * @param count number of characters to include in the substring.
     * @return A lazy_string object with a substring of this object
     *     or empty string, if pos = size().
     */

    lazy_string substr(size_t pos = 0, size_t count = string::npos);

    /**
     * Returns a reference to the character at pos position in the string.
     *
     * @param pos Value with the position of a character within the string.
     * @return The character at the specified position in the string.
     */

    lstr_char at(size_t pos);

    const char &at(size_t pos) const;

    /**
     * Returns a reference to the character at position pos in the string.
     *
     * @param pos Value with the position of a character within the string.
     * @return The character at the specified position in the string.
     */

    lstr_char operator[](size_t pos);

    const char &operator[](size_t pos) const;

    /**
     * Extracts a string from the input stream in, storing the sequence in lstr,
     * which is overwritten.
     *
     * @param in istream object from which characters are extracted.
     * @param lstr lazy_string object where the extracted content is stored.
     * @return The same as param in.
     */

    friend istream &operator>>(istream &in, lazy_string &lstr);

    /**
     * Inserts the sequence of characters that conforms value of lstr into out.
     *
     * @param out ostream object where characters are inserted.
     * @param lstr lazy_string object with the content to insert.
     * @return The same as parameter out.
     */

    friend ostream &operator<<(ostream &out, lazy_string &lstr);

};

#endif //LAZY_STRING_H
