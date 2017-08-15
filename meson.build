project('freertos', 'c')

sdir = 'lib/freertos-9.0.0/'

freertos_src = files([
	sdir + 'croutine.c',
	sdir + 'event_groups.c',
	sdir + 'list.c',
	sdir + 'queue.c',
	sdir + 'tasks.c',
	sdir + 'timers.c',
	sdir + 'portable/MemMang/heap_3.c',
	'src/freertos_init.c',
])

freertos_inc = [
	'include',
	sdir + 'include',	
]

freertos_port = meson.get_cross_property('freertos_port')

freertos_src += files(sdir + '/portable/' + freertos_port + '/port.c')
freertos_inc += sdir + '/portable/' + freertos_port

freertos_inc = include_directories(freertos_inc)

freertos_lib = static_library('freertos',
	sources : freertos_src,
	include_directories : freertos_inc
)

freertos_dep = declare_dependency(
	include_directories : freertos_inc,
	link_with : freertos_lib
)