project('piengine', 'cpp',
    default_options: [
        'cpp_std=c++23'
    ]
)

engine_source = [
	'src/file_ops.cpp',
	'src/iostream_out_ops.cpp',
	'src/main.cpp',
	'src/mesh.cpp',
	'src/script.cpp',
	'src/shader.cpp',
	'src/texture.cpp',

	'src/loaders/dds.cpp',

	'src/managers/camera.cpp',
	'src/managers/input.cpp',
	'src/managers/render.cpp',
	'src/managers/script.cpp',
	'src/managers/window.cpp',

	'src/renderobjects/meshobject.cpp',
	'src/renderobjects/renderobject.cpp',
]

engine_private_includes = [
	'src/include-private'
]

sdl2_dep = dependency('sdl2')
glew_dep = dependency('glew')
glfw_dep = dependency('glfw3')
glm_dep = dependency('glm')

lua_dep = dependency('lua')
sol2_dep = dependency('sol2')

executable('piengine', engine_source,
	include_directories : [ engine_private_includes ],
	dependencies : [ sdl2_dep, glew_dep, glfw_dep, glm_dep, lua_dep, sol2_dep ],
	cpp_args : ['-DSOL_ALL_SAFETIES_ON=1']
)
