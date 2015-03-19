This library was primarily developed against GCC but should be portable across newer C++ compilers. That said it may not work on all toolchains due to dependencies on the compiler's virtual table ABI implementation and support for fairly old meta-template programming techniques.  This page will serve as a cross-reference of known supported compilers.  If you do not see your compiler listed, forward me the working status (yes/no & version) so I can update this page accordingly.

## [GCC](http://gcc.gnu.org/) ##
| **version** | **works** | **notes** |
|:------------|:----------|:----------|
|2.9.5|???|Not Tested|
|3.0.x|Yes|g++ (3.0.4)|
|3.1.x|Yes|g++ (3.1.1)|
|3.2.x|Yes|g++ (3.2, 3.2.3)|
|3.3.x|Yes|g++ (3.3.6)|
|3.4.x|Yes|g++ (3.4.6)|
|4.0.x|Yes|g++ (4.0.4)|
|4.1.x|Yes|g++ (4.1.2)|
|4.2.x|Yes|g++ (4.2.4)|
|4.3.x|Yes|g++ (4.3.3, 4.3.5)|
|4.4.x|Yes|g++ (4.4.0, 4.4.5)|
|4.5.x|Yes|g++ (4.5.1)|

## [Microsoft Visual C++](http://msdn.microsoft.com/en-us/visualc) ##
| **version** | **works** | **notes** |
|:------------|:----------|:----------|
|6.0|No|cl.exe (12.00.8168), link.exe (6.00.8168), no template partial specialization<a href='#ref1'><sup>[1]</sup></a>|
|7.0 (.Net 2002)|No|cl.exe (13.00.9466), link.exe (7.00.9466), no template partial specialization<a href='#ref1'><sup>[1]</sup></a>|
|7.1 (.Net 2003)|Yes|cl.exe (13.10.6030), link.exe (7.10.6030)|
|8.0 (2005)|Yes|cl.exe (14.00.50727.42), link.exe (8.00.50727.42)|
|9.0 (2008)|Yes|cl.exe (15.00.3072.01), link.exe (9.00.30727.01)|

## [MinGW](http://www.mingw.org/) ##
| **version** | **works** | **notes** |
|:------------|:----------|:----------|
|3.4.x|Yes|g++ (3.4.5 [r3](https://code.google.com/p/mockitopp/source/detail?r=3)), w32api (3.13)|

## References ##
  1. <a><a href='http://support.microsoft.com/kb/240866'>BUG: ERROR C2989 and C2988 on Class Template Partial Specializations (KB240866)</a></a>