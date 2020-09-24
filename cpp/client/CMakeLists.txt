aux_source_directory(./ DIR_SRC)

find_package(Boost COMPONENTS system filesystem thread REQUIRED)

add_executable(thrift_client ${DIR_SRC})

target_link_libraries(thrift_client ${Boost_LIBRARIES} -lthrift)