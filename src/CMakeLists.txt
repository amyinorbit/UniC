add_library(UniC STATIC grapheme.c)
target_include_directories(UniC PUBLIC ${PROJECT_SOURCE_DIR}/include)
install(TARGETS UniC DESTINATION lib)
