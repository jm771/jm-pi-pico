add_executable(server)
FILE(GLOB server_sources debug_server/*.c)
target_sources(server PRIVATE ${server_sources})
target_include_directories(server PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/..
	${CMAKE_CURRENT_LIST_DIR}/../access_point
        ${CMAKE_CURRENT_LIST_DIR}/../access_point/dhcpserver
        ${CMAKE_CURRENT_LIST_DIR}/../access_point/dnsserver
		 ${CMAKE_CURRENT_LIST_DIR}/../server
		  ${CMAKE_CURRENT_LIST_DIR}/../light_programs
)
