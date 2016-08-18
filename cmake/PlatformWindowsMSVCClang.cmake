message(STATUS "Configuring for platform Windows/MSVC/Clang.")

set(DEFAULT_COMPILE_DEFS
    WIN32                       # Windows system
    _WINDOWS
    # UNICODE                     # Use unicode
    # _UNICODE                    # Use unicode
    _SCL_SECURE_NO_WARNINGS     # Calling any one of the potentially unsafe methods in the Standard C++ Library
    _CRT_SECURE_NO_DEPRECATE    # Disable CRT deprecation warnings
)

set(DEFAULT_COMPILE_DEFS_DEBUG
    ${DEFAULT_COMPILE_DEFS}
    _DEBUG                      # Debug build
)

set(DEFAULT_COMPILE_DEFS_RELEASE
    ${DEFAULT_COMPILE_DEFS}
    NDEBUG                      # Release build
)


set(DEFAULT_COMPILE_FLAGS
    # CMake defaults
    -fms-extensions
    -fms-compatibility
    -frtti
    -fexceptions

      -std=c++14
    # -pthread      # -> use pthread library
      # -pipe         # -> use pipes
      -Wall         # -> 
      -Wextra       # -> 
      -Werror       # ->
      -fPIC         # -> use position independent code
      
      # -Wno-unknown-warning-option
      -Wno-unknown-pragmas
      -Wno-reinterpret-base-class 
      -Wno-overloaded-virtual
      -Wno-inconsistent-missing-override

      -Wreturn-type
      -Wno-unused-parameter
      -Wno-unused-variable
      # -Wno-unused-but-set-variable
      -Wno-microsoft
      -Wno-deprecated-declarations
      -Wno-pointer-bool-conversion
      -Wno-missing-braces
      -Wno-invalid-constexpr # for Qt, QRgba64 fromRgba64(quint64 c)

    # -Werror=return-type -> missing returns in functions and methods are handled as errors which stops the compilation
    # -Wshadow      # -> e.g. when a parameter is named like a member, too many warnings, disabled for now
    
    
    $<$<CONFIG:Debug>:
        # -gline-tables-only
        -g
        -O0
        -fno-inline
        /MDd
    >
    
    $<$<CONFIG:Release>:
        # -O3
        /MD
    >
)

set(DEFAULT_LINKER_FLAGS_DEBUG
    ""
)

set(DEFAULT_LINKER_FLAGS_RELEASE
    ""
)
