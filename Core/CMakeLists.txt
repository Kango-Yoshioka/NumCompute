add_library(NumComputeCore STATIC Variable.cpp)
add_library(AGU::NumCompute::Core ALIAS NumComputeCore)

# ヘッダーファイルのパスを指定
target_include_directories(NumComputeCore PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
