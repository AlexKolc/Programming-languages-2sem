//
// Created by Сашуля on 19.05.2016.
//

#include "format.h"

using namespace std;

namespace Format {
    string char_seq(char c, unsigned n) {
        string outcome = "";
        for (unsigned i = 0; i < n; i++)
            outcome += c;
        return outcome;
    }

    string check_specifier(const string &fmt, unsigned &pos, bool flag) {
        string outcome = "";
        for (; pos < fmt.length();) {
            while (pos < fmt.length() && fmt[pos] != '%') outcome += fmt[pos++];
            if (pos == fmt.length() - 1)
                throw invalid_argument("Format cann't be '%%'");
            if (pos == fmt.length()) {
                if (flag)
                    throw invalid_argument("Format cann't have a number of arguments.(many)");
                return outcome;
            }
            if (fmt[pos + 1] == '%')
                outcome += '%', pos += 2;
            else {
                pos++;
                if (!flag)
                    throw out_of_range("Format cann't have a number of arguments.(few)");
                break;
            }
        }
        return outcome;
    }

    string format_impl(const string &fmt, unsigned pos, unsigned outprint) {
        return check_specifier(fmt, pos, 0);
    }

    string nullptr_exception(nullptr_t force) {
        return "nullptr";
    }
}

