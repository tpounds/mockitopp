#ifndef __MOCKITOPP_STUB_HPP__
#define __MOCKITOPP_STUB_HPP__

#include <mockitopp/detail/stubbing/OngoingStubbing.hpp>
#include <mockitopp/detail/utility/HorribleCast.hpp>

namespace mockitopp
{
   namespace detail
   {
      template <int OFFSET, typename T> struct StubImpl;

      template <int OFFSET, typename R, typename C >
      struct StubImpl<OFFSET, R (C::*)()>
      {
         void* __PAD_FOR_MOCK_vptr;
         OngoingStubbing<R (C::*)()>*
            __PAD_FOR_MOCK_spys[50];

         R invoke()
            { return __PAD_FOR_MOCK_spys[OFFSET]->invoke(); }
      };

      template <int OFFSET, typename R, typename C , typename A0>
      struct StubImpl<OFFSET, R (C::*)(A0)>
      {
         void* __PAD_FOR_MOCK_vptr;
         OngoingStubbing<R (C::*)(A0)>*
            __PAD_FOR_MOCK_spys[50];

         R invoke(A0 a0)
            { return __PAD_FOR_MOCK_spys[OFFSET]->invoke(a0); }
      };

      template <int OFFSET, typename R, typename C , typename A0, typename A1>
      struct StubImpl<OFFSET, R (C::*)(A0, A1)>
      {
         void* __PAD_FOR_MOCK_vptr;
         OngoingStubbing<R (C::*)(A0, A1)>*
            __PAD_FOR_MOCK_spys[50];

         R invoke(A0 a0, A1 a1)
            { return __PAD_FOR_MOCK_spys[OFFSET]->invoke(a0, a1); }
      };

      template <int OFFSET, typename R, typename C , typename A0, typename A1, typename A2>
      struct StubImpl<OFFSET, R (C::*)(A0, A1, A2)>
      {
         void* __PAD_FOR_MOCK_vptr;
         OngoingStubbing<R (C::*)(A0, A1, A2)>*
            __PAD_FOR_MOCK_spys[50];

         R invoke(A0 a0, A1 a1, A2 a2)
            { return __PAD_FOR_MOCK_spys[OFFSET]->invoke(a0, a1, a2); }
      };

      template <int OFFSET, typename R, typename C , typename A0, typename A1, typename A2, typename A3>
      struct StubImpl<OFFSET, R (C::*)(A0, A1, A2, A3)>
      {
         void* __PAD_FOR_MOCK_vptr;
         OngoingStubbing<R (C::*)(A0, A1, A2, A3)>*
            __PAD_FOR_MOCK_spys[50];

         R invoke(A0 a0, A1 a1, A2 a2, A3 a3)
            { return __PAD_FOR_MOCK_spys[OFFSET]->invoke(a0, a1, a2, a3); }
      };

      template <int OFFSET, typename R, typename C , typename A0, typename A1, typename A2, typename A3, typename A4>
      struct StubImpl<OFFSET, R (C::*)(A0, A1, A2, A3, A4)>
      {
         void* __PAD_FOR_MOCK_vptr;
         OngoingStubbing<R (C::*)(A0, A1, A2, A3, A4)>*
            __PAD_FOR_MOCK_spys[50];

         R invoke(A0 a0, A1 a1, A2 a2, A3 a3, A4 a4)
            { return __PAD_FOR_MOCK_spys[OFFSET]->invoke(a0, a1, a2, a3, a4); }
      };

      template <int OFFSET, typename R, typename C , typename A0, typename A1, typename A2, typename A3, typename A4, typename A5>
      struct StubImpl<OFFSET, R (C::*)(A0, A1, A2, A3, A4, A5)>
      {
         void* __PAD_FOR_MOCK_vptr;
         OngoingStubbing<R (C::*)(A0, A1, A2, A3, A4, A5)>*
            __PAD_FOR_MOCK_spys[50];

         R invoke(A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5)
            { return __PAD_FOR_MOCK_spys[OFFSET]->invoke(a0, a1, a2, a3, a4, a5); }
      };

      template <int OFFSET, typename R, typename C , typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6>
      struct StubImpl<OFFSET, R (C::*)(A0, A1, A2, A3, A4, A5, A6)>
      {
         void* __PAD_FOR_MOCK_vptr;
         OngoingStubbing<R (C::*)(A0, A1, A2, A3, A4, A5, A6)>*
            __PAD_FOR_MOCK_spys[50];

         R invoke(A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6)
            { return __PAD_FOR_MOCK_spys[OFFSET]->invoke(a0, a1, a2, a3, a4, a5, a6); }
      };

      template <int OFFSET, typename R, typename C , typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7>
      struct StubImpl<OFFSET, R (C::*)(A0, A1, A2, A3, A4, A5, A6, A7)>
      {
         void* __PAD_FOR_MOCK_vptr;
         OngoingStubbing<R (C::*)(A0, A1, A2, A3, A4, A5, A6, A7)>*
            __PAD_FOR_MOCK_spys[50];

         R invoke(A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7)
            { return __PAD_FOR_MOCK_spys[OFFSET]->invoke(a0, a1, a2, a3, a4, a5, a6, a7); }
      };

      template <int OFFSET, typename R, typename C , typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8>
      struct StubImpl<OFFSET, R (C::*)(A0, A1, A2, A3, A4, A5, A6, A7, A8)>
      {
         void* __PAD_FOR_MOCK_vptr;
         OngoingStubbing<R (C::*)(A0, A1, A2, A3, A4, A5, A6, A7, A8)>*
            __PAD_FOR_MOCK_spys[50];

         R invoke(A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8)
            { return __PAD_FOR_MOCK_spys[OFFSET]->invoke(a0, a1, a2, a3, a4, a5, a6, a7, a8); }
      };

      template <int OFFSET, typename R, typename C , typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9>
      struct StubImpl<OFFSET, R (C::*)(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9)>
      {
         void* __PAD_FOR_MOCK_vptr;
         OngoingStubbing<R (C::*)(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9)>*
            __PAD_FOR_MOCK_spys[50];

         R invoke(A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9)
            { return __PAD_FOR_MOCK_spys[OFFSET]->invoke(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9); }
      };


      template <typename M>
      struct Stub
      {
         static void* getInstance(M ptr2member)
         {
            Stub s;
            return (s.*reinterpret_cast<void* (Stub::*)()>(ptr2member))();
         }

         virtual void* invoke_proxy0() { return horrible_cast<void*>(&StubImpl<0, M>::invoke); }
         virtual void* invoke_proxy1() { return horrible_cast<void*>(&StubImpl<1, M>::invoke); }
         virtual void* invoke_proxy2() { return horrible_cast<void*>(&StubImpl<2, M>::invoke); }
         virtual void* invoke_proxy3() { return horrible_cast<void*>(&StubImpl<3, M>::invoke); }
         virtual void* invoke_proxy4() { return horrible_cast<void*>(&StubImpl<4, M>::invoke); }
         virtual void* invoke_proxy5() { return horrible_cast<void*>(&StubImpl<5, M>::invoke); }
         virtual void* invoke_proxy6() { return horrible_cast<void*>(&StubImpl<6, M>::invoke); }
         virtual void* invoke_proxy7() { return horrible_cast<void*>(&StubImpl<7, M>::invoke); }
         virtual void* invoke_proxy8() { return horrible_cast<void*>(&StubImpl<8, M>::invoke); }
         virtual void* invoke_proxy9() { return horrible_cast<void*>(&StubImpl<9, M>::invoke); }
         virtual void* invoke_proxy10() { return horrible_cast<void*>(&StubImpl<10, M>::invoke); }
         virtual void* invoke_proxy11() { return horrible_cast<void*>(&StubImpl<11, M>::invoke); }
         virtual void* invoke_proxy12() { return horrible_cast<void*>(&StubImpl<12, M>::invoke); }
         virtual void* invoke_proxy13() { return horrible_cast<void*>(&StubImpl<13, M>::invoke); }
         virtual void* invoke_proxy14() { return horrible_cast<void*>(&StubImpl<14, M>::invoke); }
         virtual void* invoke_proxy15() { return horrible_cast<void*>(&StubImpl<15, M>::invoke); }
         virtual void* invoke_proxy16() { return horrible_cast<void*>(&StubImpl<16, M>::invoke); }
         virtual void* invoke_proxy17() { return horrible_cast<void*>(&StubImpl<17, M>::invoke); }
         virtual void* invoke_proxy18() { return horrible_cast<void*>(&StubImpl<18, M>::invoke); }
         virtual void* invoke_proxy19() { return horrible_cast<void*>(&StubImpl<19, M>::invoke); }
         virtual void* invoke_proxy20() { return horrible_cast<void*>(&StubImpl<20, M>::invoke); }
         virtual void* invoke_proxy21() { return horrible_cast<void*>(&StubImpl<21, M>::invoke); }
         virtual void* invoke_proxy22() { return horrible_cast<void*>(&StubImpl<22, M>::invoke); }
         virtual void* invoke_proxy23() { return horrible_cast<void*>(&StubImpl<23, M>::invoke); }
         virtual void* invoke_proxy24() { return horrible_cast<void*>(&StubImpl<24, M>::invoke); }
         virtual void* invoke_proxy25() { return horrible_cast<void*>(&StubImpl<25, M>::invoke); }
         virtual void* invoke_proxy26() { return horrible_cast<void*>(&StubImpl<26, M>::invoke); }
         virtual void* invoke_proxy27() { return horrible_cast<void*>(&StubImpl<27, M>::invoke); }
         virtual void* invoke_proxy28() { return horrible_cast<void*>(&StubImpl<28, M>::invoke); }
         virtual void* invoke_proxy29() { return horrible_cast<void*>(&StubImpl<29, M>::invoke); }
         virtual void* invoke_proxy30() { return horrible_cast<void*>(&StubImpl<30, M>::invoke); }
         virtual void* invoke_proxy31() { return horrible_cast<void*>(&StubImpl<31, M>::invoke); }
         virtual void* invoke_proxy32() { return horrible_cast<void*>(&StubImpl<32, M>::invoke); }
         virtual void* invoke_proxy33() { return horrible_cast<void*>(&StubImpl<33, M>::invoke); }
         virtual void* invoke_proxy34() { return horrible_cast<void*>(&StubImpl<34, M>::invoke); }
         virtual void* invoke_proxy35() { return horrible_cast<void*>(&StubImpl<35, M>::invoke); }
         virtual void* invoke_proxy36() { return horrible_cast<void*>(&StubImpl<36, M>::invoke); }
         virtual void* invoke_proxy37() { return horrible_cast<void*>(&StubImpl<37, M>::invoke); }
         virtual void* invoke_proxy38() { return horrible_cast<void*>(&StubImpl<38, M>::invoke); }
         virtual void* invoke_proxy39() { return horrible_cast<void*>(&StubImpl<39, M>::invoke); }
         virtual void* invoke_proxy40() { return horrible_cast<void*>(&StubImpl<40, M>::invoke); }
         virtual void* invoke_proxy41() { return horrible_cast<void*>(&StubImpl<41, M>::invoke); }
         virtual void* invoke_proxy42() { return horrible_cast<void*>(&StubImpl<42, M>::invoke); }
         virtual void* invoke_proxy43() { return horrible_cast<void*>(&StubImpl<43, M>::invoke); }
         virtual void* invoke_proxy44() { return horrible_cast<void*>(&StubImpl<44, M>::invoke); }
         virtual void* invoke_proxy45() { return horrible_cast<void*>(&StubImpl<45, M>::invoke); }
         virtual void* invoke_proxy46() { return horrible_cast<void*>(&StubImpl<46, M>::invoke); }
         virtual void* invoke_proxy47() { return horrible_cast<void*>(&StubImpl<47, M>::invoke); }
         virtual void* invoke_proxy48() { return horrible_cast<void*>(&StubImpl<48, M>::invoke); }
         virtual void* invoke_proxy49() { return horrible_cast<void*>(&StubImpl<49, M>::invoke); }
      };
   } // namespace detail
} // namespace mockitopp

#endif //__MOCKITOPP_STUB_HPP__
