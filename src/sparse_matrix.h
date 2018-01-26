#pragma once

#include <map>
#include <utility>

namespace sm_helpers
{

    template<size_t dim, typename... Is>
    struct indexer {
        static auto index(Is... I)
        {
            return indexer<dim - 1, size_t, Is...>::index(dim - 1, I...);
        }
    };

    template<typename... Is>
    struct indexer<0, Is...> {
        static auto index(Is... I)
        {
            return std::make_tuple(I...);
        }
    };

    template<size_t dim>
    using loc_type = decltype(indexer<dim>::index());

    template<size_t dim, typename T>
    using map_type = std::map< sm_helpers::loc_type<dim>, T >;

    template<size_t u_dim, size_t dim, typename T, T def_val>
    struct loc_value {
    public:
        using map_type = sm_helpers::map_type<dim, T>;
        using loc_type = sm_helpers::loc_type<dim - u_dim>;
        using next_loc_value = loc_value<u_dim - 1, dim, T, def_val>;
        map_type& _matrix;
        loc_type _loc;

        loc_value(map_type& matrix, loc_type loc) : _matrix(matrix), _loc(loc) {}

        next_loc_value operator[](size_t n)
        {
            return next_loc_value{ _matrix, std::tuple_cat(_loc, std::make_tuple(n)) };
        }
    };

    template<size_t dim, typename T, T def_val>
    struct loc_value<0, dim, T, def_val> {
    public:
        using map_type = sm_helpers::map_type<dim, T>;
        using loc_type = sm_helpers::loc_type<dim>;
        using last_loc_value = loc_value<0, dim, T, def_val>;
        map_type& _matrix;
        loc_type _loc;

        loc_value(map_type& matrix, loc_type loc) : _matrix(matrix), _loc(loc) {}

        last_loc_value& operator=(const T& t)
        {
            auto f = _matrix.find(_loc);
            if (t != def_val)
                if (f == _matrix.end())
                    _matrix.emplace(std::make_pair(_loc, t));
                else
                    f->second = t;
            else if (f != _matrix.end())
                _matrix.erase(f);
            return *this;
        }

        operator T() const
        {
            auto f = _matrix.find(_loc);
            if (f == _matrix.end())
                return def_val;
            else
                return f->second;
        }
    };

}

template<size_t dim, typename T, T def_val>
class sparse_matrix : public sm_helpers::map_type<dim, T>
{
public:
    using loc_type = sm_helpers::loc_type<dim>;
    using next_loc_value = sm_helpers::loc_value<dim - 1, dim, T, def_val>;
    using last_loc_value = sm_helpers::loc_value<0, dim, T, def_val>;

    next_loc_value operator[](size_t n)
    {
        return next_loc_value(*this, std::make_tuple(n));
    }
    last_loc_value operator[](loc_type loc)
    {
        return last_loc_value(*this, loc);
    }
};
