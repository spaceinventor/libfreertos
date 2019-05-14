project('freertos', 'c')

conf_data = configuration_data()
conf_data.set('configTOTAL_HEAP_SIZE', get_option('total_heap_size'))
configure_file(output : 'freertos_config.h', configuration: conf_data)

sdir = 'lib/freertos-10.2.0/'

freertos_src = files([
	sdir + 'croutine.c',
	sdir + 'event_groups.c',
	sdir + 'list.c',
	sdir + 'queue.c',
	sdir + 'tasks.c',
	sdir + 'timers.c',
	sdir + 'portable/MemMang/heap_4.c',
	'src/freertos_hooks.c',
])

freertos_inc = [
	'.',
	'include',
	sdir + 'include',	
]

freertos_deps = dependency('start', fallback: ['start', 'start_dep'])

freertos_port = meson.get_cross_property('freertos_port')

freertos_src += files(sdir + 'portable/' + freertos_port + '/port.c')
freertos_inc += sdir + 'portable/' + freertos_port

freertos_inc = include_directories(freertos_inc)

freertos_lib = static_library('freertos',
	include_directories : freertos_inc,
	sources : freertos_src,
	dependencies: freertos_deps,
)

freertos_dep = declare_dependency(
	include_directories : freertos_inc,
	link_whole : freertos_lib,
)
