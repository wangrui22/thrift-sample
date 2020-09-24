aux_source_directory(./ DIR_SRC)

find_package(Boost COMPONENTS system filesystem thread REQUIRED)

add_executable(thrift_server ${DIR_SRC})

target_link_libraries(thrift_server gen-cpp ${Boost_LIBRARIES} -lthrift)