message(STATUS "Configuring for platform Windows/MSVC.")

set(WIN32_COMPILE_DEFS
    WIN32                       # Windows system
    UNICODE                     # Use unicode
    _UNICODE                    # Use unicode
    _SCL_SECURE_NO_WARNINGS     # Calling any one of the potentially unsafe methods in the Standard C++ Library
    _CRT_SECURE_NO_DEPRECATE    # Disable CRT deprecation warnings
)

set(DEFAULT_COMPILE_DEFS_DEBUG
    ${WIN32_COMPILE_DEFS}
    _DEBUG                      # Debug build
)

set(DEFAULT_COMPILE_DEFS_RELEASE
    ${WIN32_COMPILE_DEFS}
    NDEBUG                      # Release build
)

option(OPTION_RELEASE_LTCG "Enable whole program optimization / link time code generation in Release builds" OFF)

set(WIN32_COMPILE_FLAGS

      /MP           # -> build with multiple processes

      /nologo       # -> no logo
      /Zc:wchar_t   # -> treat wchar_t as built-in type: yes
      /Zc:forScope  # -> force conformance in for loop scope: Yes
    # /Gm           # -> enable minimal rebuild
      /fp:precise   # -> floating point model: precise
    # /fp:fast      # -> floating point model: fast
    # /arch:SSE2    # -> enable enhanced instruction set: streaming simd extensions 2

    # /wd####       # -> disable warning C####
    # /wd4702       # -> unreachable code
      /wd4273       # -> Two definitions in a file differ in their use of dllimport.
    # /wd4100       # -> 'identifier' : unreferenced formal parameter
    # /wd4127       # -> conditional expression is constant
      /wd4251       # -> 'identifier' : class 'type' needs to have dll-interface to be used by clients of class 'type2'
      /wd4267       # -> 'var' : conversion from 'size_t' to 'type', possible loss of data
      /wd4503       # -> decorated name length exceeded, name was truncated

      /W3           # -> warning level 3
    # /W4           # -> warning level 4
      /WX           # -> treat warnings as errors

    # /MD           # -> runtime library: multithreaded dll
    # /MDd          # -> Runtime Library: Multithreaded Debug DLL
	
      /bigobj
)

# http://support.microsoft.com/kb/154419
# "Programs that use the Standard C++ library must be compiled 
#  with C++ exception handling enabled."

#if(NOT OPTION_ERRORS_AS_EXCEPTION)
#   # disable exception handling -> /EHs-c- does not remove CXX flags
#   string(REPLACE "/EHsc" "" CMAKE_CXX_FLAGS_MODIFIED ${CMAKE_CXX_FLAGS}) 
#   string(REPLACE "/GX" ""  CMAKE_CXX_FLAGS_MODIFIED ${CMAKE_CXX_FLAGS_MODIFIED}) 
#   unset(CMAKE_CXX_FLAGS CACHE)
#   set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS_MODIFIED} CACHE TYPE STRING)
#endif()

set(DEFAULT_COMPILE_FLAGS
    ${WIN32_COMPILE_FLAGS}
    $<$<CONFIG:Debug>:   
      /MDd
      /RTC1         # -> Runtime error checks
    # /RTCc   
      /Od           # -> Optimization: none
      # /GS-          # -> buffer security check: no 
      # /GL           # -> whole program optimization: enable link-time code generation
      # /GF           # -> enable string pooling
      /GR           # -> runtime type information
    # /GS           # -> buffer security check
    # /GF-          # -> enable string pooling
      /Zi           # -> debug information format: program database
    >
    $<$<CONFIG:Release>: 
      /MD /O2
      # /Ox           # -> optimization: full optimization 
      # /Ob2          # -> inline function expansion: any suitable
    # /Oi           # -> enable intrinsic functions: yes
    # /Ot           # -> favor size or speed: favor fast code
    # /Oy           # -> omit frame pointers: yes
      # /GS-          # -> buffer security check: no 
      # /GL           # -> whole program optimization: enable link-time code generation
      # /GF           # -> enable string pooling
      /GR           # -> runtime type information
    >
)

if (OPTION_RELEASE_LTCG)
    list(APPEND DEFAULT_COMPILE_FLAGS $<$<CONFIG:Release>: /GL > )
endif()

set(WIN32_LINKER_FLAGS
    "/NOLOGO /NXCOMPAT /DYNAMICBASE"
    # NOLOGO                                            -> suppress logo
    # INCREMENTAL:NO                                    -> enable incremental linking: no
    # MANIFEST                                          -> generate manifest: yes
    # MANIFESTUAC:"level='asInvoker' uiAccess='false'"  -> uac execution level: asinvoker, uac bypass ui protection: false
    # NXCOMPAT                                          -> data execution prevention (dep): image is compatible with dep
    # DYNAMICBASE:NO                                    -> randomized base address: disable image randomization
)

set(DEFAULT_LINKER_FLAGS_DEBUG
    "${WIN32_LINKER_FLAGS} /DEBUG"
    # DEBUG        -> create debug info
)

set(DEFAULT_LINKER_FLAGS_RELEASE
    "${WIN32_LINKER_FLAGS} /OPT:REF /OPT:ICF"
    # OPT:REF      -> references: eliminate unreferenced data
    # OPT:ICF      -> enable comdat folding: remove redundant comdats
    # LTCG         -> link time code generation: use link time code generation
    # DELAY:UNLOAD -> delay loaded dll: support unload
)

if(OPTION_RELEASE_LTCG)
    set(DEFAULT_LINKER_FLAGS_RELEASE "${DEFAULT_LINKER_FLAGS_RELEASE} /LTCG")
endif()

# Add platform specific libraries for linking
set(EXTRA_LIBS "")
