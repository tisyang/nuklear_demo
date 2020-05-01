add_library(tinyfiledialogs tinyfiledialogs.c tinyfiledialogs.h)
if(WIN32)
target_link_libraries(tinyfiledialogs
    user32
    comdlg32
    ole32
)
endif()
