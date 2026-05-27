project(module-cairo)

add_custom_target(
	mint-cairo-module-cairo
SOURCES
	cairo.mn
)

# Install
get_target_property(${PROJECT_NAME}_SOURCES mint-cairo-module-cairo SOURCES)
install(
	FILES ${${PROJECT_NAME}_SOURCES}
	COMPONENT runtime DESTINATION ${MINT_MODULES_INSTALL_DIR}/codec
)
