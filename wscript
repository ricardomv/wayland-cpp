top = '.'
out = 'build'

from waflib import TaskGen
TaskGen.declare_chain(
	name         = 'scanner',
	rule         = '../scanner.py ${SRC} ../src/wlplus',
	ext_in       = '.xml',
	reentrant    = False,
	before       = 'cxx',
	install_path = '')

def options(opt):
	opt.load('compiler_cxx')
	opt.add_option('--test_egl', action='store_true', default=False,
		help='Add egl test window')

def configure(cnf):
	cnf.load('compiler_cxx')
	cnf.check(features='cxx cxxprogram cxxshlib', cflags=['-Wall','-g', '-std=c++11'], defines=['var=foo'])
	cnf.check_cfg(package='wayland-client', args='--cflags --libs', uselib_store='SH_LIBS', mandatory=True)
	if cnf.options.test_egl:
		cnf.check_cfg(package='egl', args='--cflags --libs', mandatory=True)
		cnf.check_cfg(package='wayland-egl', args='--cflags --libs', uselib_store='EGL', mandatory=True)
		cnf.check_cfg(package='cairo-gl', args='--cflags --libs', uselib_store='EGL', mandatory=True)
	cnf.define('TEST_EGL', cnf.options.test_egl)
	cnf.env.TEST_EGL = cnf.options.test_egl

	cnf.write_config_header('config.h')

def build(bld):
	bld(source='protocol/wayland.xml')

	sources = 'src/main.cpp src/Window.cpp src/Input.cpp'
	if bld.env.TEST_EGL:
		sources += ' src/egl.cpp'
		pass
	bld(features='cxx cxxprogram',
		includes='./ src/wlplus',
		source=sources,
		cxxflags=['-Wall','-g', '-std=c++11'],
		use=['SH_LIBS', 'EGL'],
		target='app')
