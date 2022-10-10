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

cc = meson.get_compiler('c')

add_project_arguments(cc.get_supported_arguments([
	'-Wno-empty-translation-unit',
	'-Wno-unused-parameter',
	'-Wold-style-definition',
	'-Wstrict-prototypes',
	]), language: 'c')

includes = [include_directories('inc')]

subdir('src')
subdir('pro')
subdir('tst')
subdir('doc')

executable(
	meson.project_name(),
	src_files,
	include_directories: includes,
	dependencies: client_protos,
	install: true,
	)
