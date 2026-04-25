# указывайте последнюю доступную вам версию CMake

cmake_minimum_required(VERSION 3.14)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# название проекта
project(Algorithms-and-Data-Structures)

# затем следует список инструкций для подключения проектов из подкаталогов

include(cmake/function.cmake)         # подхватываем функции, реализованные в файле function.cmake
                                      # для простоты мы объединили наборы команд для создания статической библиотеки
								      # и для создания исполняемого проекта в отдельные функции

add_subdirectory(lib_easy_example)    # подключаем дополнительный CMakeLists.txt из подкаталога с именем lib_easy_example
add_subdirectory(lib_point) 
add_subdirectory(lib_circle)
add_subdirectory(lib_point3D) 
add_subdirectory(lib_sphere) 
add_subdirectory(lib_TVector) 
add_subdirectory(lib_algorithms) 
add_subdirectory(lib_stack)
add_subdirectory(lib_queue)
add_subdirectory(lib_list)
add_subdirectory(lib_DoubleList)
add_subdirectory(lib_DSU)
add_subdirectory(lib_ListStack)
add_subdirectory(lib_ListQueue)
add_subdirectory(lib_Expression)
add_subdirectory(lib_Monom)
add_subdirectory(lib_Polynom) 
add_subdirectory(lib_SkipList)
add_subdirectory(lib_ITable)
add_subdirectory(lib_UnsortedListTable)
add_subdirectory(lib_UnsortedVecTable)
add_subdirectory(lib_SortedVecTable)
add_subdirectory(lib_tree)
add_subdirectory(lib_UnsortedTreeTable)
add_subdirectory(lib_BSTree)
add_subdirectory(lib_SortedTreeTable)
add_subdirectory(lib_heap)
add_subdirectory(lib_PriorityQueue)
add_subdirectory(lib_HashTable)
add_subdirectory(lib_HashTableC)
add_subdirectory(lib_AVLTree)
add_subdirectory(lib_ListGraph)
add_subdirectory(main)                # подключаем дополнительный CMakeLists.txt из подкаталога с именем main

option(BTEST "build test?" ON)        # указываем подключаем ли google-тесты (ON или YES) или нет (OFF или NO)

if(BTEST)                             # если тесты подключены         
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    add_subdirectory("third_party/gtest" EXCLUDE_FROM_ALL)
    enable_testing()
    add_subdirectory(tests)
endif()


