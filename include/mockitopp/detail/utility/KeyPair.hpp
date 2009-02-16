#ifndef __MOCKITOPP_KEY_PAIR_HPP__
#define __MOCKITOPP_KEY_PAIR_HPP__

namespace mockitopp
{
   namespace detail
   {
      template <typename K, typename V>
      struct KeyPair
      {
         K key;
         V value;

         KeyPair(const K& key, const V& value)
            : key(key)
            , value(value)
            {}
      };

      template <typename K1, typename V1, typename K2, typename V2>
      inline bool operator== (const KeyPair<K1, V1>& lhs, KeyPair<K2, V2> rhs)
         { return lhs.key == rhs.key; }

      template <typename K1, typename V1, typename K2>
      inline bool operator== (const KeyPair<K1, V1>& lhs, const K2& rhs)
         { return lhs.key == rhs; }
   } // namespace detail
} // namespace mockitopp

#endif //__MOCKITOPP_KEY_PAIR_HPP__
