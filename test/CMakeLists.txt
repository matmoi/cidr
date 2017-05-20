add_executable(unittest unittest.c)
target_link_libraries(unittest cidr)
install(TARGETS unittest DESTINATION bin)

add_executable(cidr_app cidr_app.c)
target_link_libraries(cidr_app cidr)
install(TARGETS cidr_app DESTINATION lib)
