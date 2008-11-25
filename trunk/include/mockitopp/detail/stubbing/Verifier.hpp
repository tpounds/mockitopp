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
          * verify method is called within a specified range
          *
          * @param min minimum times method should be called
          * @param max maximum times method should be called
          */
         bool between(int min, int max) const
         {
            if(calls >= min && calls <= max)
               { return true; }
            return false;
         }

         /**
          * verify method is called at least (n) times
          *
          * @param times minimum number of times method should be called
          */
         bool atLeast(int times) const
            { return between(times, 0x7FFF); }

         /**
          * verify method is called at most (n) times
          *
          * @param times maximum number of times method should be called
          */
         bool atMost(int times) const
            { return between(0, times); }

         /**
          * verify method is called exactly (n) times
          *
          * @param times exact number of times method should be called
          */
         bool exactly(int times) const
            { return between(times, times); }

         /**
          * verify method is never called
          */
         bool never() const
            { return between(0, 0); }
      };
   } // namespace detail
} // namespace mockitopp

#endif //__MOCKITOPP_VERIFIER_HPP__
