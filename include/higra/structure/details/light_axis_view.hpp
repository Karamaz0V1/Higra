//
// Created by user on 5/13/18.
//

#pragma once

namespace hg {

    namespace details {


        template<bool vectorial, typename T>
        struct light_axis_view {

            using value_type = typename T::value_type;
            using self_type = light_axis_view<vectorial, T>;

            static const bool is_vectorial = vectorial;

            template<typename T1 = self_type>
            light_axis_view(T &data, std::size_t position = 0, typename std::enable_if_t<T1::is_vectorial> * = 0) :
                    m_data(data),
                    m_stride(data.size() / data.shape()[0]),
                    m_position(position) {

            }

            template<typename T1 = self_type>
            light_axis_view(T &data, std::size_t position = 0, typename std::enable_if_t<!T1::is_vectorial> * = 0) :
                    m_data(data),
                    m_stride(1),
                    m_position(position) {
            }

            void set_position(std::size_t i) {
                m_position = i;
            }

            template<typename T1=self_type>
            auto begin(typename std::enable_if_t<T1::is_vectorial> * = 0) {
                return m_data.storage_begin() + m_position * m_stride;
            }

            template<typename T1=self_type>
            auto begin(typename std::enable_if_t<!T1::is_vectorial> * = 0) {
                return m_data.storage_begin() + m_position;
            }

            template<typename T1=self_type>
            auto end(typename std::enable_if_t<T1::is_vectorial> * = 0) {
                return m_data.storage_begin() + (m_position + 1) * m_stride;
            }

            template<typename T1=self_type>
            auto end(typename std::enable_if_t<!T1::is_vectorial> * = 0) {
                return m_data.storage_begin() + (m_position + 1);
            }

            template<typename T1=self_type>
            auto begin(typename std::enable_if_t<T1::is_vectorial> * = 0) const {
                return m_data.storage_begin() + m_position * m_stride;
            }

            template<typename T1=self_type>
            auto begin(typename std::enable_if_t<!T1::is_vectorial> * = 0) const {
                return m_data.storage_begin() + m_position;
            }

            template<typename T1=self_type>
            auto end(typename std::enable_if_t<T1::is_vectorial> * = 0) const {
                return m_data.storage_begin() + (m_position + 1) * m_stride;
            }

            template<typename T1=self_type>
            auto end(typename std::enable_if_t<!T1::is_vectorial> * = 0) const {
                return m_data.storage_begin() + (m_position + 1);
            }

            template<bool vectorial2, typename T2>
            self_type &operator=(const light_axis_view<vectorial2, T2> &rhs) {
                static_assert(vectorial == vectorial2, "Mixing vectorial and non vectorial soft axis view!");
                assign(*this, rhs);
                return (*this);
            }

            self_type &operator=(const self_type &rhs) {
                assign(*this, rhs);
                return (*this);
            }

            template<bool vectorial2, typename T2, typename combinator_t, typename T1=self_type>
            std::enable_if_t<T1::is_vectorial> combine(const light_axis_view<vectorial2, T2> &rhs, combinator_t fun) {
                static_assert(T1::is_vectorial == vectorial2, "Mixing vectorial and non vectorial soft axis view!");
                auto r = rhs.begin();
                auto v = begin();
                for (; v != end(); v++, r++) {
                    *v = fun(*v, *r);
                }
            }

            template<bool vectorial2, typename T2, typename combinator_t, typename T1=self_type>
            std::enable_if_t<!T1::is_vectorial> combine(const light_axis_view<vectorial2, T2> &rhs, combinator_t fun) {
                static_assert(T1::is_vectorial == vectorial2, "Mixing vectorial and non vectorial soft axis view!");
                *begin() = fun(*begin(), *(rhs.begin()));
            }


        private:

            template<typename T1, typename T2>
            std::enable_if_t<T1::is_vectorial> assign(T1 &lhs, const T2 &rhs) {
                static_assert(T1::is_vectorial == T2::is_vectorial,
                              "Mixing vectorial and non vectorial soft axis view!");
                auto r = rhs.begin();
                auto v = lhs.begin();
                for (; v != end(); v++, r++) {
                    *v = *r;
                }
            }

            template<typename T1, typename T2>
            std::enable_if_t<!T1::is_vectorial> assign(T1 &lhs, const T2 &rhs) {
                static_assert(T1::is_vectorial == T2::is_vectorial,
                              "Mixing vectorial and non vectorial soft axis view!");
                *lhs.begin() = *rhs.begin();
            }

            T &m_data;
            std::size_t m_stride;
            std::size_t m_position;
        };
    }

    template<bool vectorial = true, typename T>
    auto make_light_axis_view(T &e, std::size_t position = 0) {
        return details::light_axis_view<vectorial, T>(e, position);
    }

}