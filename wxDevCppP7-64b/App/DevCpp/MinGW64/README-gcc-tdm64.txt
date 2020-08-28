=== TDM-GCC Compiler Suite for Windows ===
---           GCC 4.6 Series           ---
***    MinGW-w64 64/32-bit Edition     ***


This edition of TDM-GCC is a multilib bootstrap of GCC's x86_64-w64-mingw32
target, built to run on 32-bit or 64-bit Windows and generate binaries for
32-bit or 64-bit Windows.


BUGS:
Please do *not* report bugs in this edition of TDM-GCC to the standard MinGW
(32) mailing list or forums.

If you encounter any bugs with this edition of TDM-GCC, it is likely that they
will be inherent to the x86_64-w64-mingw32 GCC target or to the MinGW-w64
runtime API. As such, you are encouraged to report bugs to the tracker for the
MinGW-w64 project on SourceForge
(<http://sourceforge.net/tracker/?group_id=202880>). Once the issue has been
fixed in the mingw-w64 runtime or in GCC, file a feature request on the TDM-GCC
tracker (<http://sourceforge.net/tracker/?group_id=200665>) to update to the
fixed version.


>>>>> INSTALLATION

*** TDM/MinGW Installer ***

Using the TDM/MinGW installer is highly recommended; it can automatically
install TDM-GCC (or the official MinGW GCC) as well as all supplementary base
system packages. The installer uses a standard wizard interface with reasonable
defaults.

*** Manual Installation ***

Do not install TDM-GCC packages on top of a previous working GCC installation of
any kind.

You will need to download and unpack a set of archives. A minimal base set of
archives is required; there are also some additional components that are
optional, adding support for additional programming languages or GCC features.

TDM-GCC provides a ZIP-compressed version and a TAR.LZMA-compressed version of
each archive. Use whichever is easiest.

REQUIRED BASE:
 * gcc-core (gcc-4.6.1-tdm64-1-core)
 * binutils (binutils-2.21.53-20110731-tdm64-1)
 * mingw64-runtime (mingw64-runtime-tdm64-gcc46-svn4483)

OPTIONAL:
 * gcc-c++ (gcc-4.6.1-tdm64-1-c++) - C++ support
 * gcc-fortran (gcc-4.6.1-tdm64-1-fortran) - Fortran support
 * gcc-objc (gcc-4.6.1-tdm64-1-objc) - Objective-C/C++ support
 * gcc-openmp (gcc-4.6.1-tdm64-1-openmp) - OpenMP support
 * mingw32-make (make-3.82-5-mingw32-bin, libintl-0.17-1-mingw32-dll-8,
     libiconv-1.13.1-1-mingw32-dll-2) - GNU make for *-mingw32 GCC
 * gdb (gdb-7.3.1-tdm64-1) - GNU source-level debugger, for x86_64-w64-mingw32
     GCC
You'll need GDB particularly if you want to use an IDE with debugging support.

Unpack all the archives to an empty directory. You may choose any path, though
it is recommended that you avoid a path with any spaces in the folder names.
Finally, consider adding the bin subdirectory to your Windows PATH environment
variable.


>>>>> SUPPORT

Support for the x86_64-w64-mingw32 GCC target, as well as for any
incompatibilities in its runtime API, is provided where possible by the
MinGW-w64 project. The MinGW-w64 project provides multiple venues for support
including a mailing list, an IRC channel, a web-based discussion forum on
SourceForge, and a web-based issue tracker on SourceForge.

For more information about MinGW-w64, see the project's home page at
<http://mingw-w64.sourceforge.net/>.


>>>>> USAGE NOTES

*** 32-bit or 64-bit compilation ***

In this edition of TDM-GCC, you can use "-m32" and "-m64" to control whether
32-bit or 64-bit binaries are generated. By default (if neither -m32 nor -m64 is
specified), 64-bit binaries will be generated. In a 64-bit binary, all pointer
math is 64-bit by default, and the built-in "size_t" and "ptrdiff_t" types are
64 bits in size (some other types are larger also). Additionally, the following
preprocessor definitions will be in effect:
 * #define _WIN64 1 (also WIN64, __WIN64, and __WIN64__)
 * #define __MINGW64__ 1
 * #define __x86_64 1 (also __x86_64__)
 * #define __amd64 1 (also __amd64__)
Be sure to use "-m32" or "-m64" at both the compile stage and the link stage. 

*** Inline member functions and DLLs ***

[[[ IMPORTANT NOTE:
[[[ You will probably need to use "-fno-keep-inline-dllexport" when building
[[[ large DLLs with lots of inline member functions, such as the "wxWidgets"
[[[ library's monolithic DLL.

The GCC 4.5 series introduced a change in the way inline functions that are
members of classes are handled in DLLs. Before the 4.5 series, inline member
functions were *not* emitted in DLLs by default; in the 4.5 series and later,
they are.

Unfortunately, this change in behavior led to link-time problems with large
libraries (such as wxWidgets) that use precompiled headers and many inline
member functions, where the linker would run out of memory while trying to
generate the DLL.

In the GCC 4.6 series, therefore, the flag "-fno-keep-inline-dllexport" was
introduced, which allows you to disable the emission of inline functions in DLLs
and return to the old behavior.


*** LTO (Link-Time Optimization) ***

Every TDM-GCC release since 4.5.1 includes support for GCC's Link-Time
Optimizer. As long as GCC's own drivers (gcc, g++, etc.) are used at both
compile-time and link-time, and the "-flto" option is specified at both compile-
time and link-time, link-time optimization will be applied. See
<http://gcc.gnu.org/onlinedocs/gcc/Optimize-Options.html> for further details.

*** "Graphite" Loop Transformations ***

Every TDM-GCC release since 4.4.1 includes support for GCC's Graphite loop
transformation infrastructure. Support for these optimizations is currently
optional, and they are not enabled at any of the -O optimization levels. If you
are interested in using them, the relevant options are "-floop-interchange",
"-floop-strip-mine", and "-floop-block", and they are documented at
<http://gcc.gnu.org/onlinedocs/gcc/Optimize-Options.html>.

*** SJLJ unwinding ***

The x86_64-w64-mingw32 target of GCC only supports SJLJ (setjmp/longjmp) stack
frame unwinding. This means that any DLLs or executables you generate will not
be able to throw exceptions to or correctly handle exceptions from a compiler
that uses the more widespread Dwarf-2 stack frame unwinding (for example, the
standard MinGW 32-bit GCC).

Executables and DLLs that do not make use of exceptions should be compatible
with any recent GCC release for the same target and architecture. (Obviously,
this does not apply to mixing 32-bit and 64-bit binaries.)

*** Exceptions and DLLs ***

[[[ IMPORTANT NOTE:
[[[ TDM-GCC uses a statically-linked libstdc++ by default! To use the libstdc++
[[[ DLL, specify "-shared-libstdc++" on the command line.

The TDM releases of x86_64-w64-mingw32 GCC support propagating exceptions out
of shared libraries (DLLs) whether you use DLL versions or statically-linked
versions of the GCC runtime libraries. The statically-linked runtimes utilize
a shared memory region that will allow all TDM-GCC-compiled executables and DLLs
(for the same architecture) to propagate exceptions correctly. This method
incurs a small execution overhead as compared to the shared library method, but
has the very important benefit of not requiring you to redistribute extra DLLs
with your program.

By default, TDM-GCC creates executables and DLLs that use the statically-linked
runtimes, and does not require you to redistribute further DLLs. If you would
like to use the shared runtimes, you should add "-shared-libgcc" to the command
line, to use a shared version of libgcc, and additionally ensure that the shared
version of your language-specific runtime is being used. For C++, add
"-shared-libstdc++".

You cannot use a shared version of libgcc with a static version of a language-
specific runtime. The reverse -- static libgcc with shared language-specific
runtime -- should work fine.

IMPORTANT NOTE:
There has been an update to the license exception clause that permits you to
distribute programs that make use of the GCC runtime libraries without requiring
you to license your programs under the GPLv3. As always, please be familiar with
the terms of GCC's GPLv3 license and exception clauses, and do not redistribute
any portion of GCC, including its runtime DLLs, in any way except as granted by
the license. If you are unclear about which permissions are granted by the
license, please consult a lawyer and/or the Free Software Foundation
(<http://www.fsf.org/>).

A copy of the GPLv3 may be found in the file
COPYING-gcc-tdm.txt, and a copy of the runtime library exception clause may be
found in COPYING.RUNTIME-gcc-tdm.txt. In general, the runtime library exception
clause probably applies to any file found in the "lib" directory or its
subdirectories, and any DLL found in the "bin" directory -- but you should
consult the sources, available for download from the TDM-GCC project site on
SourceForge, if you are unsure.

*** OpenMP and pthreads-w32 ***

TDM-GCC has been built to allow the use of GCC's "-fopenmp" option for
generating parallel code as specified by the OpenMP API. (See
<http://gcc.gnu.org/onlinedocs/libgomp/> for details.) If you want to use
OpenMP in your programs, be sure to install the "openmp" optional package.

The OpenMP support in the TDM-GCC builds has received very little testing; if
you find build or packaging problems, please send a bug report (see BUGS above).

LibGOMP, GCC's implementation of OpenMP, currently only supports the use of the
POSIX Threads (pthreads) api for implementing its threading model. Because the
MinGW project itself doesn't distribute a pthreads implementation, the
"pthreads-win32" library, available from http://sourceware.org/pthreads-win32/,
is included in this distribution. If you aren't familiar with pthreads-win32,
please read the file "pthreads-win32-README" for more information, or the
documentation available at the website referenced above. pthreads-win32 is
distributed under the terms of the LGPL; see "COPYING.lib-gcc-tdm.txt" for
details.

In order to correctly compile code that utilizes OpenMP/libGOMP, you need to add
the "-fopenmp" option at compile time AND link time. By default, this will link
the standard C-cleanup DLL version of pthreads-win32 to your program, which
means that you will need to ensure that the file "pthreadGC2.dll" (for 32-bit
programs) or "pthreadGC2_64.dll" (for 64-bit programs) can be found by your
program. These DLLs are included in the "bin" subdirectory of the openmp
package. If you plan to distribute a program that relies on pthreads-win32, be
sure to understand and comply with the terms of the LGPL
(see COPYING.lib-gcc-tdm.txt).

"libpthread.a" is included in the "lib[32]" subdirectory of
the openmp package along with two other pthreads library files:
 - "libpthreadGC2-static.a" provides a static version of the pthreads-win32
     library, but it requires some additional non-POSIX-compliant startup code
     to be included in your program. See "pthreads-win32-README" for
     details.
 - "libpthreadGCE2.a" provides a version of the pthreads-win32 library with
     a somewhat safer response in the face of unexpected C++ exceptions.
     The creators of the pthreads-win32 library recommend, however, that this
     version not be used, because code written to rely on this is less portable.

*** Warnings and errors ***

GCC 4 represents a significant step forward in optimization capabilities, error
detection, and standards compliance, and this is more true than ever with the
most recent GCC releases. For you, the end user, this will mean that code which
compiled and ran without problems on previous GCC releases will almost certainly
exhibit some warnings and maybe even a few errors.

These meaningful warnings and errors are a very good thing, as they help the
programmer to write safer and more correct code. Unfortunately, there's also a
chance you might encounter incorrect warnings or errors, ICE's (internal
compiler errors, where the compiler makes a mistake and has to bail out), or
even miscompilations (where your code is incorrectly compiled and produces the
wrong result).

If you encounter an ICE while using a TDM-GCC build, feel free to file a bug
report (see BUGS above). With any other unexpected problem, you are urged to
work from the assumption that it stems from user error, and ensure that your
code is correct and standards-compliant.


>>>>> BUGS AND KNOWN ISSUES

-- There are currently no known TDM64-GCC-specific bugs. --

TDM-GCC for the x86_64-w64-mingw32 target is based on the work of the MinGW-w64
project, which is somewhat younger and less stable than the standard MinGW
32-bit project. This being the case, some bugs are to be expected. If you
encounter a bug that you are certain is in the GCC sources (such as an ICE), or
that is due to an issue in the building or packaging process, you are encouraged
to report it. Please visit the TDM-GCC Bugs Page at
<http://tdm-gcc.tdragon.net/bugs> for bug reporting instructions.


>>>>> LOCAL FIXES AND CHANGES

 - Includes a patch to make all search paths for headers, libraries and
     helper executables relative to the installation directory of the driver
     executables -- in other words, TDM-GCC is fully relocatable and does not
     search any absolute system paths.
 - Includes a patch to differentiate DLL names between the 32-bit and 64-bit
     GCC runtime libraries.
 - Includes a patch to allow libgomp to interoperate correctly with user-
     generated pthreads. See
     <http://sourceforge.net/tracker/?func=detail&aid=2921774&group_id=200665&atid=974439>.
 - Includes a patch to propagate exceptions out of DLLs without the need for
     shared runtime libraries.
 - Includes a patch which corrects backslash usage in header paths and fixes
     path problems when debugging. See
     <http://sourceforge.net/tracker/?func=detail&aid=2145427&group_id=200665&atid=974439>.
 - Includes a patch to keep GCC from erroneously using the CWD as the
     installation directory.
 - Configured with "--enable-fully-dynamic-string", which fixes a bug when
     passing empty std::string objects between DLLs and EXEs.
 - Includes a patch which reintegrates the code from libgcc_eh.a into libgcc.a
     and the libgcc DLL. As long as the shared memory region is used to handle
     exceptions in the static runtimes, this library is unnecessary, and it
     causes multiple definition errors for the symbols in it because it hasn't
     been added to binutils' exception libraries yet.

[The following patches are only necessary for the 4.5 series and have been
applied in the 4.6 sources]

 - Includes a patch backported from GCC 4.6 trunk to fix problems using LTO with
     virtual base classes in C++. (See
     <http://gcc.gnu.org/bugzilla/show_bug.cgi?id=46376>.)
 - Includes a patch to disable the forced generation of code for inline
     functions. This addresses a change in the GCC 4.5 vanilla sources from
     previous releases, which would cause disproportionately large object files
     in programs that expect the old behavior. The patch restores the old
     behavior, until such time as a more suitable response is found. For further
     info, see <http://gcc.gnu.org/bugzilla/show_bug.cgi?id=43601> and
     <http://gcc.gnu.org/viewcvs?view=revision&revision=147799>.


>>>>> SOURCE CODE

The source code for the TDM-GCC binary releases is available from the TDM-GCC
download page on SourceForge: <http://sourceforge.net/projects/tdm-gcc/files/>.
(The most up-to-date link to the download site will always be available at
<http://tdm-gcc.tdragon.net/>.)

The source is distributed in the form of the original ("vanilla") separate
source packages as downloaded, plus an additional "TDM Sources" package. The TDM
Sources package includes unified diffs of any changes made to the vanilla
sources, as well as the set of scripts used to build the binary releases.


>>>>> LICENSE

This edition of TDM-GCC is comprised of several distinct parts with respect to
licensing, namely:
 * GCC proper and its various language components,
 * The OpenMP support package including pthreads-w32,
 * The GNU binutils package,
 * The GNU source-level debugger (GDB), and
 * The MinGW-w64 runtime API.

The GCC proper packages in TDM-GCC contain binary distributions constituting a
work based on GCC, CLooG, PPL, MPC, libiconv, GMP, and MPFR. GCC itself, CLooG,
and PPL are each licensed under the GPLv3; for further details, see
"COPYING3-gcc-tdm.txt". MPC, libiconv, GMP, and MPFR are each licensed under the
LGPL, a somewhat more permissive version of the GPL; see
"COPYING3.LIB-gcc-tdm.txt". Finally, GCC's runtime libraries are licensed with
an additional exception clause; see "COPYING.RUNTIME-gcc-tdm.txt".

The OpenMP support package provides binary and source files based on GCC's
libgomp, which is licensed under the GPLv3 with an additional exception (see
"COPYING3-gcc-tdm.txt" and "COPYING.RUNTIME-gcc-tdm.txt"), and on pthreads-w32,
which is licensed under the LGPL (see "COPYING3.LIB-gcc-tdm.txt").

The GNU binutils package is a binary distribution licensed under the GPLv3; see
"COPYING3-gcc-tdm.txt".

The GDB package is a binary distribution licensed under the GPLv3; see
"COPYING3-gcc-tdm.txt". It is additionally based on the Expat XML Parser, whose
license is available in "COPYING-expat.txt".

The MinGW-w64 runtime API includes binary and source files that fall under a
variety of licenses (all of which are "GPLv3 compatible"); for further details,
see "COPYING.MinGW-w64.txt" (for non-runtime portions) and
"COPYING.MinGW-w64-runtime.txt" (for the runtime only).

The TDM-GCC distribution is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by the Free
Software Foundation; either version 3 of the License, or (at your option) any
later version.

TDM-GCC is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with
this program. If not, see <http://www.gnu.org/licenses/>.
