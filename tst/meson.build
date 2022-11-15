cmocka = dependency('cmocka')

tests = {
	'tag': {
		'src': files(
			'../src/config.c',
			'../src/list.c',
			'../src/tag.c',
			),
		},
	'layout': {
		'src': files(
			'../src/layout.c',
			),
		'link_args': [
			'-Wl,--wrap=_river_layout_v3_push_view_dimensions',
			]
		},
	}

foreach name, params: tests
	exe = executable(
		name,
		'tst-@0@.c'.format(name),
		params['src'],
		include_directories: includes,
		dependencies: cmocka,
		link_args : params.get('link_args', ''),
		)
	test(name, exe, verbose: false)
endforeach

