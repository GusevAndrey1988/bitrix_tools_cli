project('bitrix_tools_cli', 'cpp', version: '0.0.1', meson_version: '>=0.28.0')

conf_data = configuration_data()

if get_option('use_src_resources_dir')
  conf_data.set('APPLICATION_ETC_DIR', '../resources')
else
  conf_data.set('APPLICATION_ETC_DIR', '../etc/bitrix_tools_cli')
endif

cfg_file = configure_file(
  input: 'include/variables.h.in',
  output: 'variables.h',
  configuration: conf_data,
)

include_dir = include_directories('include')

boost_dep = dependency('boost', modules: ['program_options'], required: true)

nlohmann_json_dep = dependency('nlohmann_json', required: true)

cmake = import('cmake')

jinja2cpp_proj = cmake.subproject('jinja2cpp')
jinja2cpp_deps = jinja2cpp_proj.dependency('jinja2cpp')
fmt_deps = jinja2cpp_proj.dependency('fmt')

sources = [
  'src/main.cpp',
  'src/application.cpp',
  'src/command.cpp',
  'src/config_to_template_properties_mapper.cpp',
  'src/config.cpp',
  'src/template_property_value.cpp',
  'src/template.cpp',
  'src/work_location.cpp',
  'src/commands/init_cmd.cpp',
]

executable(
  'bitrix_tools_cli',
  sources,
  cfg_file,
  include_directories: [include_dir],
  dependencies: [boost_dep, nlohmann_json_dep, jinja2cpp_deps, fmt_deps],
  cpp_args: '-O',
  install: true,
)

install_subdir('resources/config', install_dir: 'etc/bitrix_tools_cli')
install_subdir('resources/templates', install_dir: 'etc/bitrix_tools_cli')