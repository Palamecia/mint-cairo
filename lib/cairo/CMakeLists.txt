project(module-cairo)

set(${PROJECT_NAME}_LIB
	cairo.mn
)

add_custom_target(${PROJECT_NAME}
	SOURCES
	${${PROJECT_NAME}_LIB}
)

# Install
mint_install_modules(${${PROJECT_NAME}_LIB} SUBDIR cairo)
