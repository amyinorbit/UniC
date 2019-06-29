add_library(UniC STATIC grapheme.c properties.c utf8.c counting.c)
target_include_directories(UniC PUBLIC ${PROJECT_SOURCE_DIR}/include)
install(TARGETS UniC DESTINATION lib)
