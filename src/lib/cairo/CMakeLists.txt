project(mint-cairo)

include_directories(${MINT_INCLUDE_DIRS})

add_library(${PROJECT_NAME}
	MODULE
	cairo.cpp
)

set_target_properties(
	${PROJECT_NAME}
	PROPERTIES
	PREFIX lib
)

target_link_libraries(
	${PROJECT_NAME}
	mint::libmint
)

# Install
# install_library(${PROJECT_NAME} SUBDIR mint)
