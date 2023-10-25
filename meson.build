project('piengine', 'cpp',
    default_options: [
        'cpp_std=c++23'
    ]
)

engine_source = [
	'src/main.cpp',
	'src/file_ops.cpp',
	'src/mesh.cpp',
	'src/shader.cpp',

	'src/loaders/dds.cpp'
]

engine_private_includes = [
	'src/include-private'
]

sdl2_dep = dependency('sdl2')
glew_dep = dependency('glew')
glfw_dep = dependency('glfw3')
glm_dep = dependency('glm')

executable('piengine', engine_source,
	include_directories : [ engine_private_includes ],
	dependencies : [ sdl2_dep, glew_dep, glfw_dep, glm_dep ]
)