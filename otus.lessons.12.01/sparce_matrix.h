#pragma once

#include <map>
#include <vector>

template<size_t dim, typename T, T def_val>
class sparce_matrix {
public:
    template <size_t... Is>
    static auto loc_type_helper(std::index_sequence<Is...>) { return std::make_tuple(Is...); }

    using loc_type = decltype(loc_type_helper(std::make_index_sequence<dim>{}));
    using map_type = std::map<loc_type, T>;
    map_type _matrix;

    template<size_t u_dim>
    struct loc_value{
    public:
        using loc_type = decltype(loc_type_helper(std::make_index_sequence<dim - u_dim>{}));
        map_type& _matrix;
        loc_type _loc;

        loc_value(map_type& matrix, loc_type loc) : _matrix(matrix), _loc(loc) {}

        loc_value<u_dim - 1> operator[](size_t n) {
            return loc_value<u_dim - 1>{_matrix, std::tuple_cat(_loc, std::make_tuple(n))};
        }
    };

    template<>
    struct loc_value<0> {
    public:
        using loc_type = decltype(loc_type_helper(std::make_index_sequence<dim>{}));
        map_type& _matrix;
        loc_type _loc;

        loc_value(map_type& matrix, loc_type loc) : _matrix(matrix), _loc(loc) {}

        loc_value<0>& operator=(const T& t) {
            auto f = _matrix.find(_loc);
            if (t != def_val)
                _matrix.insert_or_assign(_loc, t);
            else if (f != _matrix.end())
                _matrix.erase(f);
            return *this;
        }

        loc_value<0>& operator=(const loc_value<0>& lv) {
            T t = lv;
            auto f = _matrix.find(_loc);
            if (t != def_val)
                _matrix.insert_or_assign(_loc, t);
            else if (f != _matrix.end())
                _matrix.erase(f);
            return *this;
        }
        
        operator T() const {
            auto f = _matrix.find(_loc);
            if (f == _matrix.end())
                return def_val;
            else
                return f->second;
        }
    };

    loc_value<dim - 1> operator[](size_t n) {
        return loc_value<dim - 1>(_matrix, std::make_tuple(n));
    }

    auto begin() { return _matrix.begin(); }
    auto end() { return _matrix.end(); }
    size_t size() { return _matrix.size(); }
};