project('freertos', 'c')

conf_data = configuration_data()
conf_data.set('configTOTAL_HEAP_SIZE', get_option('total_heap_size'))
conf_data.set('configTICK_RATE_HZ', get_option('tick_rate_hz'))
conf_data.set('configCPU_CLOCK_HZ', get_option('cpu_clock_hz'))

sdir = 'upstream/'

freertos_inc = ['upstream/include', '.']
freertos_src = files([
	sdir + 'croutine.c',
	sdir + 'event_groups.c',
	sdir + 'list.c',
	sdir + 'queue.c',
	sdir + 'tasks.c',
	sdir + 'timers.c',
	'src/freertos_atomics_gcc.c',
	'src/freertos_print.c',
])

if (get_option('total_heap_size') > 0)
	freertos_src += files([
		sdir + 'portable/MemMang/heap_4.c',
		'src/malloc.c',
	])
	conf_data.set('configSUPPORT_DYNAMIC_ALLOCATION', 1)
	if(get_option('app_alloc_heap'))
		conf_data.set('configAPPLICATION_ALLOCATED_HEAP', 1)
	endif
endif

if (get_option('num_locks') > 0)
	freertos_src += files(['src/freertos_lock.c'])
	conf_data.set('NUM_LOCKS', get_option('num_locks'))
endif

configure_file(output : 'freertos_config.h', configuration: conf_data)

freertos_deps = []
freertos_deps += dependency('start', fallback: ['start', 'start_dep'])
freertos_deps += dependency('libc', fallback: ['picolibc', 'picolibc_dep'])

if get_option('arch') == 'c21'
	freertos_src += files(sdir + 'portable/' + freertos_port + '/portasm.c')
endif

if get_option('arch') == 'c21' or get_option('arch') == 'e70'
	freertos_src += files(['src/e70/port_same70.c'])
	freertos_src += files(['src/freertos_hooks.c'])
	freertos_port = meson.get_external_property('freertos_port')
	freertos_src += files(sdir + 'portable/' + freertos_port + '/port.c')
	freertos_inc += sdir + 'portable/' + freertos_port
	freertos_inc += 'src/' + get_option('arch')
elif get_option('arch') == 'zynq'
	freertos_src += files(['src/zynq/port.c', 'src/zynq/portZynq7000.c'])
	freertos_inc += 'src/zynq'
else
	error('Must explicitly specify freertos:arch')
endif

freertos_inc = include_directories(freertos_inc)

freertos_lib = static_library('freertos',
	include_directories : freertos_inc,
	sources : freertos_src,
	dependencies: freertos_deps,
)

freertos_dep = declare_dependency(
	include_directories : freertos_inc,
	link_with : freertos_lib,
)

freertos_dep_whole = declare_dependency(
	include_directories : freertos_inc,
	link_whole : freertos_lib,
)
