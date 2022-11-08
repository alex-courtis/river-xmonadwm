cmocka = dependency('cmocka')

tests = {
	'tag': {
		'src': files(
			'../src/log.c',
			'../src/list.c',
			'../src/tag.c',
			),
		},
	'test1': {
		'src': files(
			'../src/src1.c',
			),
		},
	'test2': {
		'src': files(
			'../src/src2.c',
			),
		'link_args': [
			'-Wl,--wrap=add',
			]
		},
	}

foreach name, params: tests
	exe = executable(
		name,
		'@0@.c'.format(name),
		params['src'],
		include_directories: includes,
		dependencies: [cmocka, client_protos],
		link_args : params.get('link_args', ''),
		)
	test(name, exe, verbose: true)
endforeach

