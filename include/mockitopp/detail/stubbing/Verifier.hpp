#ifndef __MOCKITOPP_VERIFIER_HPP__
#define __MOCKITOPP_VERIFIER_HPP__

namespace mockitopp
{
   namespace detail
   {
      struct Verifier
      {
         int calls;

         /**
          * verify method invocation is never called
          *
          * @param ptr2member method to be verify
          */
         bool between(int min, int max) const
         {
            if(calls >= min && calls <= max)
               { return true; }
            return false;
         }

         /**
          * verify method invocation occurs at least (n) times
          *
          * @param ptr2member method to be verify
          * @param times minimum number of times method should be called
          */
         bool atLeast(int times) const
            { return between(times, 0x7FFF); }

         /**
          * verify method invocation occurs at most (n) times
          *
          * @param ptr2member method to be verify
          * @param times maximum number of times method should be called
          */
         bool atMost(int times) const
            { return between(0, times); }

         /**
          * verify method invocation exactly (n) times
          *
          * @param times exact number of times method should be called
          */
         const bool exactly(int times) const
            { return between(times, times); }

         /**
          * verify method invocation is never called
          */
         bool never() const
            { return between(0, 0); }
      };
   } // namespace detail
} // namespace mockitopp

#endif //__MOCKITOPP_VERIFIER_HPP__
