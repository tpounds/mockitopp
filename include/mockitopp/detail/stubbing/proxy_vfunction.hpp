#ifndef __MOCKITOPP_PROXY_VFUNCTION_HPP__
#define __MOCKITOPP_PROXY_VFUNCTION_HPP__

#include <mockitopp/detail/stubbing/dynamic_vfunction.hpp>
#include <mockitopp/detail/util/horrible_cast.hpp>

namespace mockitopp
{
   namespace detail
   {
      template <int OFFSET, typename T> struct proxy_vfunction;

      template <int OFFSET, typename R, typename C >
      struct proxy_vfunction<OFFSET, R (C::*)()>
      {
         void* __PAD_FOR_MOCK_vptr;
         dynamic_vfunction<R (C::*)()>*
            __PAD_FOR_MOCK_spys[50];

         R invoke()
            { return __PAD_FOR_MOCK_spys[OFFSET]->invoke(); }
      };

      template <int OFFSET, typename R, typename C , typename A0>
      struct proxy_vfunction<OFFSET, R (C::*)(A0)>
      {
         void* __PAD_FOR_MOCK_vptr;
         dynamic_vfunction<R (C::*)(A0)>*
            __PAD_FOR_MOCK_spys[50];

         R invoke(A0 a0)
            { return __PAD_FOR_MOCK_spys[OFFSET]->invoke(a0); }
      };

      template <int OFFSET, typename R, typename C , typename A0, typename A1>
      struct proxy_vfunction<OFFSET, R (C::*)(A0, A1)>
      {
         void* __PAD_FOR_MOCK_vptr;
         dynamic_vfunction<R (C::*)(A0, A1)>*
            __PAD_FOR_MOCK_spys[50];

         R invoke(A0 a0, A1 a1)
            { return __PAD_FOR_MOCK_spys[OFFSET]->invoke(a0, a1); }
      };

      template <int OFFSET, typename R, typename C , typename A0, typename A1, typename A2>
      struct proxy_vfunction<OFFSET, R (C::*)(A0, A1, A2)>
      {
         void* __PAD_FOR_MOCK_vptr;
         dynamic_vfunction<R (C::*)(A0, A1, A2)>*
            __PAD_FOR_MOCK_spys[50];

         R invoke(A0 a0, A1 a1, A2 a2)
            { return __PAD_FOR_MOCK_spys[OFFSET]->invoke(a0, a1, a2); }
      };

      template <int OFFSET, typename R, typename C , typename A0, typename A1, typename A2, typename A3>
      struct proxy_vfunction<OFFSET, R (C::*)(A0, A1, A2, A3)>
      {
         void* __PAD_FOR_MOCK_vptr;
         dynamic_vfunction<R (C::*)(A0, A1, A2, A3)>*
            __PAD_FOR_MOCK_spys[50];

         R invoke(A0 a0, A1 a1, A2 a2, A3 a3)
            { return __PAD_FOR_MOCK_spys[OFFSET]->invoke(a0, a1, a2, a3); }
      };

      template <int OFFSET, typename R, typename C , typename A0, typename A1, typename A2, typename A3, typename A4>
      struct proxy_vfunction<OFFSET, R (C::*)(A0, A1, A2, A3, A4)>
      {
         void* __PAD_FOR_MOCK_vptr;
         dynamic_vfunction<R (C::*)(A0, A1, A2, A3, A4)>*
            __PAD_FOR_MOCK_spys[50];

         R invoke(A0 a0, A1 a1, A2 a2, A3 a3, A4 a4)
            { return __PAD_FOR_MOCK_spys[OFFSET]->invoke(a0, a1, a2, a3, a4); }
      };

      template <int OFFSET, typename R, typename C , typename A0, typename A1, typename A2, typename A3, typename A4, typename A5>
      struct proxy_vfunction<OFFSET, R (C::*)(A0, A1, A2, A3, A4, A5)>
      {
         void* __PAD_FOR_MOCK_vptr;
         dynamic_vfunction<R (C::*)(A0, A1, A2, A3, A4, A5)>*
            __PAD_FOR_MOCK_spys[50];

         R invoke(A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5)
            { return __PAD_FOR_MOCK_spys[OFFSET]->invoke(a0, a1, a2, a3, a4, a5); }
      };

      template <int OFFSET, typename R, typename C , typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6>
      struct proxy_vfunction<OFFSET, R (C::*)(A0, A1, A2, A3, A4, A5, A6)>
      {
         void* __PAD_FOR_MOCK_vptr;
         dynamic_vfunction<R (C::*)(A0, A1, A2, A3, A4, A5, A6)>*
            __PAD_FOR_MOCK_spys[50];

         R invoke(A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6)
            { return __PAD_FOR_MOCK_spys[OFFSET]->invoke(a0, a1, a2, a3, a4, a5, a6); }
      };

      template <int OFFSET, typename R, typename C , typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7>
      struct proxy_vfunction<OFFSET, R (C::*)(A0, A1, A2, A3, A4, A5, A6, A7)>
      {
         void* __PAD_FOR_MOCK_vptr;
         dynamic_vfunction<R (C::*)(A0, A1, A2, A3, A4, A5, A6, A7)>*
            __PAD_FOR_MOCK_spys[50];

         R invoke(A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7)
            { return __PAD_FOR_MOCK_spys[OFFSET]->invoke(a0, a1, a2, a3, a4, a5, a6, a7); }
      };

      template <int OFFSET, typename R, typename C , typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8>
      struct proxy_vfunction<OFFSET, R (C::*)(A0, A1, A2, A3, A4, A5, A6, A7, A8)>
      {
         void* __PAD_FOR_MOCK_vptr;
         dynamic_vfunction<R (C::*)(A0, A1, A2, A3, A4, A5, A6, A7, A8)>*
            __PAD_FOR_MOCK_spys[50];

         R invoke(A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8)
            { return __PAD_FOR_MOCK_spys[OFFSET]->invoke(a0, a1, a2, a3, a4, a5, a6, a7, a8); }
      };

      template <int OFFSET, typename R, typename C , typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9>
      struct proxy_vfunction<OFFSET, R (C::*)(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9)>
      {
         void* __PAD_FOR_MOCK_vptr;
         dynamic_vfunction<R (C::*)(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9)>*
            __PAD_FOR_MOCK_spys[50];

         R invoke(A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9)
            { return __PAD_FOR_MOCK_spys[OFFSET]->invoke(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9); }
      };


      template <typename M>
      struct proxy_vfunction_factory
      {
         static void* get(M ptr2member)
         {
            proxy_vfunction_factory s;
            return (s.*reinterpret_cast<void* (proxy_vfunction_factory::*)()>(ptr2member))();
         }

         virtual void* offset0() { return horrible_cast<void*>(&proxy_vfunction<0, M>::invoke); }
         virtual void* offset1() { return horrible_cast<void*>(&proxy_vfunction<1, M>::invoke); }
         virtual void* offset2() { return horrible_cast<void*>(&proxy_vfunction<2, M>::invoke); }
         virtual void* offset3() { return horrible_cast<void*>(&proxy_vfunction<3, M>::invoke); }
         virtual void* offset4() { return horrible_cast<void*>(&proxy_vfunction<4, M>::invoke); }
         virtual void* offset5() { return horrible_cast<void*>(&proxy_vfunction<5, M>::invoke); }
         virtual void* offset6() { return horrible_cast<void*>(&proxy_vfunction<6, M>::invoke); }
         virtual void* offset7() { return horrible_cast<void*>(&proxy_vfunction<7, M>::invoke); }
         virtual void* offset8() { return horrible_cast<void*>(&proxy_vfunction<8, M>::invoke); }
         virtual void* offset9() { return horrible_cast<void*>(&proxy_vfunction<9, M>::invoke); }
         virtual void* offset10() { return horrible_cast<void*>(&proxy_vfunction<10, M>::invoke); }
         virtual void* offset11() { return horrible_cast<void*>(&proxy_vfunction<11, M>::invoke); }
         virtual void* offset12() { return horrible_cast<void*>(&proxy_vfunction<12, M>::invoke); }
         virtual void* offset13() { return horrible_cast<void*>(&proxy_vfunction<13, M>::invoke); }
         virtual void* offset14() { return horrible_cast<void*>(&proxy_vfunction<14, M>::invoke); }
         virtual void* offset15() { return horrible_cast<void*>(&proxy_vfunction<15, M>::invoke); }
         virtual void* offset16() { return horrible_cast<void*>(&proxy_vfunction<16, M>::invoke); }
         virtual void* offset17() { return horrible_cast<void*>(&proxy_vfunction<17, M>::invoke); }
         virtual void* offset18() { return horrible_cast<void*>(&proxy_vfunction<18, M>::invoke); }
         virtual void* offset19() { return horrible_cast<void*>(&proxy_vfunction<19, M>::invoke); }
         virtual void* offset20() { return horrible_cast<void*>(&proxy_vfunction<20, M>::invoke); }
         virtual void* offset21() { return horrible_cast<void*>(&proxy_vfunction<21, M>::invoke); }
         virtual void* offset22() { return horrible_cast<void*>(&proxy_vfunction<22, M>::invoke); }
         virtual void* offset23() { return horrible_cast<void*>(&proxy_vfunction<23, M>::invoke); }
         virtual void* offset24() { return horrible_cast<void*>(&proxy_vfunction<24, M>::invoke); }
         virtual void* offset25() { return horrible_cast<void*>(&proxy_vfunction<25, M>::invoke); }
         virtual void* offset26() { return horrible_cast<void*>(&proxy_vfunction<26, M>::invoke); }
         virtual void* offset27() { return horrible_cast<void*>(&proxy_vfunction<27, M>::invoke); }
         virtual void* offset28() { return horrible_cast<void*>(&proxy_vfunction<28, M>::invoke); }
         virtual void* offset29() { return horrible_cast<void*>(&proxy_vfunction<29, M>::invoke); }
         virtual void* offset30() { return horrible_cast<void*>(&proxy_vfunction<30, M>::invoke); }
         virtual void* offset31() { return horrible_cast<void*>(&proxy_vfunction<31, M>::invoke); }
         virtual void* offset32() { return horrible_cast<void*>(&proxy_vfunction<32, M>::invoke); }
         virtual void* offset33() { return horrible_cast<void*>(&proxy_vfunction<33, M>::invoke); }
         virtual void* offset34() { return horrible_cast<void*>(&proxy_vfunction<34, M>::invoke); }
         virtual void* offset35() { return horrible_cast<void*>(&proxy_vfunction<35, M>::invoke); }
         virtual void* offset36() { return horrible_cast<void*>(&proxy_vfunction<36, M>::invoke); }
         virtual void* offset37() { return horrible_cast<void*>(&proxy_vfunction<37, M>::invoke); }
         virtual void* offset38() { return horrible_cast<void*>(&proxy_vfunction<38, M>::invoke); }
         virtual void* offset39() { return horrible_cast<void*>(&proxy_vfunction<39, M>::invoke); }
         virtual void* offset40() { return horrible_cast<void*>(&proxy_vfunction<40, M>::invoke); }
         virtual void* offset41() { return horrible_cast<void*>(&proxy_vfunction<41, M>::invoke); }
         virtual void* offset42() { return horrible_cast<void*>(&proxy_vfunction<42, M>::invoke); }
         virtual void* offset43() { return horrible_cast<void*>(&proxy_vfunction<43, M>::invoke); }
         virtual void* offset44() { return horrible_cast<void*>(&proxy_vfunction<44, M>::invoke); }
         virtual void* offset45() { return horrible_cast<void*>(&proxy_vfunction<45, M>::invoke); }
         virtual void* offset46() { return horrible_cast<void*>(&proxy_vfunction<46, M>::invoke); }
         virtual void* offset47() { return horrible_cast<void*>(&proxy_vfunction<47, M>::invoke); }
         virtual void* offset48() { return horrible_cast<void*>(&proxy_vfunction<48, M>::invoke); }
         virtual void* offset49() { return horrible_cast<void*>(&proxy_vfunction<49, M>::invoke); }
      };
   } // namespace detail
} // namespace mockitopp

#endif //__MOCKITOPP_PROXY_VFUNCTION_HPP__
