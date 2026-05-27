project(mint-cairo)

include_directories(${MINT_INCLUDE_DIRS})

add_library(
	mint-cairo-lib-module-cairo
MODULE
	cairo.cpp
)

set_target_properties(
	mint-cairo-lib-module-cairo
PROPERTIES
	PREFIX lib
	OUTPUT_NAME mint-cairo
)

target_link_libraries(
	mint-cairo-lib-module-cairo
PRIVATE
	mint::mint
	PkgConfig::CAIRO
)

# Install
install(
	TARGETS mint-cairo-lib-module-cairo
	LIBRARY COMPONENT runtime DESTINATION ${MINT_LIBRARY_INSTALL_DIR}/mint
	ARCHIVE COMPONENT runtime DESTINATION ${MINT_LIBRARY_INSTALL_DIR}/mint
	RUNTIME COMPONENT runtime DESTINATION ${MINT_LIBRARY_INSTALL_DIR}/mint
)
