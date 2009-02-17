#ifndef __MOCKITOPP_MATCHER_HPP__
#define __MOCKITOPP_MATCHER_HPP__

namespace mockitopp
{
   namespace matcher
   {
      template <typename T>
      struct Matcher
      {
         virtual Matcher* clone() const = 0;

         virtual bool operator== (const T& rhs) const = 0;
      };
   } // namespace matcher
} // namespace mockitopp

#endif //__MOCKITOPP_MATCHER_HPP__
