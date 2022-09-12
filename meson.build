project(
	'river-xmonadwm',
	'c',
	version: '0.0.1',
	default_options: [
		'c_std=gnu17',
		'warning_level=3',
		'werror=true',
		],
	)

wayland_client = dependency('wayland-client')

cc = meson.get_compiler('c')

add_project_arguments(cc.get_supported_arguments([
	'-Wno-unused-parameter',
	'-Wold-style-definition',
	'-Wstrict-prototypes',
	]), language: 'c')

src = [
	'src/main.c',
	]

subdir('pro')

executable(
	meson.project_name(),
	src,
	include_directories: include_directories('inc'),
	dependencies: client_protos,
	install: true,
	)
