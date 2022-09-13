wayland_client = dependency('wayland-client')

wayland_scanner = find_program('wayland-scanner')

wayland_scanner_code = generator(
	wayland_scanner,
	output: '@BASENAME@-protocol.c',
	arguments: ['private-code', '@INPUT@', '@OUTPUT@'],
	)

wayland_scanner_client = generator(
	wayland_scanner,
	output: '@BASENAME@-client-protocol.h',
	arguments: ['client-header', '@INPUT@', '@OUTPUT@'],
	)

xml_files = files(
	'river-layout-v3.xml',
	)

proto_src_files = []
proto_header_files = []

foreach xml : xml_files
	proto_src_files += wayland_scanner_code.process(xml)
	proto_header_files += wayland_scanner_client.process(xml)
endforeach

lib_client_protos = static_library(
	'client_protos',
	proto_src_files + proto_header_files,
	dependencies: [wayland_client]
	)

client_protos = declare_dependency(
	link_with: lib_client_protos,
	sources: proto_header_files,
	)
