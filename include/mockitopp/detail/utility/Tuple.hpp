#ifndef __MOCKITOPP_TUPLE_HPP__
#define __MOCKITOPP_TUPLE_HPP__

namespace mockitopp
{
   namespace detail
   {
      struct NullType
      {
         bool operator< (const NullType&) const
            { return false; }
      };

      /**
       * @author Trevor Pounds
       */
      template <
         typename T1 = NullType, typename T2 = NullType,
         typename T3 = NullType, typename T4 = NullType,
         typename T5 = NullType, typename T6 = NullType,
         typename T7 = NullType, typename T8 = NullType,
         typename T9 = NullType, typename T10 = NullType,
         typename T11 = NullType, typename T12 = NullType,
         typename T13 = NullType, typename T14 = NullType,
         typename T15 = NullType, typename T16 = NullType,
         typename T17 = NullType, typename T18 = NullType,
         typename T19 = NullType, typename T20 = NullType
         >
      struct Tuple
      {
         T1 t1; T2 t2;
         T3 t3; T4 t4;
         T5 t5; T6 t6;
         T7 t7; T8 t8;
         T9 t9; T10 t10;
         T11 t11; T12 t12;
         T13 t13; T14 t14;
         T15 t15; T16 t16;
         T17 t17; T18 t18;
         T19 t19; T20 t20;

         Tuple(T1 t1 = T1(), T2 t2 = T2(),
               T3 t3 = T3(), T4 t4 = T4(),
               T5 t5 = T5(), T6 t6 = T6(),
               T7 t7 = T7(), T8 t8 = T8(),
               T9 t9 = T9(), T10 t10 = T10(),
               T11 t11 = T11(), T12 t12 = T12(),
               T13 t13 = T13(), T14 t14 = T14(),
               T15 t15 = T15(), T16 t16 = T16(),
               T17 t17 = T17(), T18 t18 = T18(),
               T19 t19 = T19(), T20 t20 = T20())
            : t1(t1), t2(t2)
            , t3(t3), t4(t4)
            , t5(t5), t6(t6)
            , t7(t7), t8(t8)
            , t9(t9), t10(t10)
            , t11(t11), t12(t12)
            , t13(t13), t14(t14)
            , t15(t15), t16(t16)
            , t17(t17), t18(t18)
            , t19(t19), t20(t20)
            {}

         bool operator< (const Tuple& t) const
         {
            return
               t.t1 < t1 && t.t2 < t2 &&
               t.t3 < t3 && t.t4 < t4 &&
               t.t5 < t5 && t.t6 < t6 &&
               t.t7 < t7 && t.t8 < t8 &&
               t.t9 < t9 && t.t10 < t10 &&
               t.t11 < t11 && t.t12 < t12 &&
               t.t13 < t13 && t.t14 < t14 &&
               t.t15 < t15 && t.t16 < t16 &&
               t.t17 < t17 && t.t18 < t18 &&
               t.t19 < t19 && t.t20 < t20;
         }
      };
   } // namespace detail
} // namespace mockitopp

#endif //__MOCKITOPP_TUPLE_HPP__
