#ifndef __MOCKITOPP_FUNCTION_HPP__
#define __MOCKITOPP_FUNCTION_HPP__

namespace mockitopp
{
   namespace detail
   {
      /**
       * @author Trevor Pounds
       */
      struct Function
      {
         template <typename T>
         static int getOffset(T ptr2member)
         {
            Function f;
            return (f.*reinterpret_cast<int (Function::*)()>(ptr2member))();
         }

         virtual int offset0() { return 0; }
         virtual int offset1() { return 1; }
         virtual int offset2() { return 2; }
         virtual int offset3() { return 3; }
         virtual int offset4() { return 4; }
         virtual int offset5() { return 5; }
         virtual int offset6() { return 6; }
         virtual int offset7() { return 7; }
         virtual int offset8() { return 8; }
         virtual int offset9() { return 9; }
         virtual int offset10() { return 10; }
         virtual int offset11() { return 11; }
         virtual int offset12() { return 12; }
         virtual int offset13() { return 13; }
         virtual int offset14() { return 14; }
         virtual int offset15() { return 15; }
         virtual int offset16() { return 16; }
         virtual int offset17() { return 17; }
         virtual int offset18() { return 18; }
         virtual int offset19() { return 19; }
         virtual int offset20() { return 20; }
         virtual int offset21() { return 21; }
         virtual int offset22() { return 22; }
         virtual int offset23() { return 23; }
         virtual int offset24() { return 24; }
         virtual int offset25() { return 25; }
         virtual int offset26() { return 26; }
         virtual int offset27() { return 27; }
         virtual int offset28() { return 28; }
         virtual int offset29() { return 29; }
         virtual int offset30() { return 30; }
         virtual int offset31() { return 31; }
         virtual int offset32() { return 32; }
         virtual int offset33() { return 33; }
         virtual int offset34() { return 34; }
         virtual int offset35() { return 35; }
         virtual int offset36() { return 36; }
         virtual int offset37() { return 37; }
         virtual int offset38() { return 38; }
         virtual int offset39() { return 39; }
         virtual int offset40() { return 40; }
         virtual int offset41() { return 41; }
         virtual int offset42() { return 42; }
         virtual int offset43() { return 43; }
         virtual int offset44() { return 44; }
         virtual int offset45() { return 45; }
         virtual int offset46() { return 46; }
         virtual int offset47() { return 47; }
         virtual int offset48() { return 48; }
         virtual int offset49() { return 49; }
      };

   } // namespace detail
} // namespace mockitopp

#endif //__MOCKITOPP_FUNCTION_HPP__
