#ifndef __PYSTR_H__
#define __PYSTR_H__

#include <cassert>
#include <string>
#include <array>

namespace scl {

    std::vector<std::string> strSplit(std::string_view s, std::string_view delim = " ") {
        std::vector<std::string> ret;
        for (std::size_t pos1 = 0, pos2 = s.find(delim); pos2 != std::string_view::npos;) {
            if (pos2 != pos1) {
                ret.emplace_back(s.substr(pos1, pos2 - pos1));
            }
            pos1 = pos2 + delim.size();
            pos2 = s.find(delim, pos1);
        }
        return ret;
    }

    std::string strip(const std::string& s, std::string_view delim = " \n\r\t") {
        constexpr int len = 1 << 8;
        std::array<bool, len> destroy = {};
        // destroy.fill(false);
        for (char c : delim) {
            destroy[c] = true;
        }

        const int n = s.size();
        int l = 0;
        while (l < n && destroy[s[l]]) {
            ++l;
        }
        int r = n - 1;
        while (r >= l && destroy[s[r]]) {
            --r;
        }

        assert(r + 1 == l || l <= r);
        if (r + 1 == l) {
            return "";
        } else {
            return s.substr(l, r - l + 1);
        }
    }

    std::string lstrip(const std::string& s, std::string_view delim = " \n\r\t") {
        constexpr int len = 1 << 8;
        std::array<bool, len> destroy = {};
        // destroy.fill(false);
        for (char c : delim) {
            destroy[c] = true;
        }

        const int n = s.size();
        int l = 0;
        while (l < n && destroy[s[l]]) {
            ++l;
        }

        if (l == n) {
            return "";
        } else {
            return s.substr(l);
        }
    }

    std::string rstrip(const std::string& s, std::string_view delim = " \n\r\t") {
        constexpr int len = 1 << 8;
        std::array<bool, len> destroy = {};
        // destroy.fill(false);
        for (char c : delim) {
            destroy[c] = true;
        }

        const int n = s.size();
        int r = n - 1;
        while (r >= 0 && destroy[s[r]]) {
            --r;
        }

        if (r == -1) {
            return "";
        } else {
            return s.substr(0, r + 1);
        }
    }

}  // namespace scl

#endif  // __PTSTR_H__