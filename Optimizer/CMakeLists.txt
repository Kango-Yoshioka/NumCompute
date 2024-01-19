add_library(Optimizer STATIC BaseOptimizer.cpp Status.cpp)
add_library(AGU::NumCompute::Optimizer ALIAS Optimizer)

# ヘッダーファイルのパスを指定
target_include_directories(Optimizer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(Optimizer PUBLIC AGU::NumCompute::Differential)