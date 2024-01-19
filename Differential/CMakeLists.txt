add_library(Differential STATIC Differential.cpp OptDifferentiator.cpp)
add_library(AGU::NumCompute::Differential ALIAS Differential)

# ヘッダーファイルのパスを指定
target_include_directories(Differential PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(Differential PUBLIC AGU::NumCompute::Core)