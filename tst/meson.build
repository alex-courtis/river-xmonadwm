cmocka = dependency('cmocka')

tests = {
	'tag': {
		'src': files(
			'../src/config.c',
			'../src/list.c',
			'../src/tag.c',
			),
		},
	'arrange': {
		'src': files(
			'../src/arrange.c',
			'../src/list.c',
			),
		},
	'arrange-master-stack': {
		'src': files(
			'../src/arrange.c',
			'../src/list.c',
			),
		},
	'arrange-views': {
		'src': files(
			'../src/arrange.c',
			'../src/list.c',
			),
		},
	}

foreach name, params: tests
	exe = executable(
		name,
		'tst-@0@.c'.format(name),
		params['src'],
		include_directories: includes,
		dependencies: [cmocka, client_protos],
		c_args : '-Wno-unused-function',
		link_args : params.get('link_args', ''),
		)
	test(name, exe, verbose: false)
endforeach

