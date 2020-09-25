aux_source_directory(./ DIR_SRC)
aux_source_directory(../gen-cpp DIR_SRC2)

find_package(Boost COMPONENTS system filesystem thread REQUIRED)

add_executable(thrift_client ${DIR_SRC} ${DIR_SRC2})

target_link_libraries(thrift_client ${Boost_LIBRARIES} -lthrift)