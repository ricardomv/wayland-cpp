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

	cnf.check_cfg(package='egl', args='--cflags --libs', mandatory=True)
	cnf.check_cfg(package='wayland-egl', args='--cflags --libs', uselib_store='EGL', mandatory=True)
	cnf.check_cfg(package='gl', args='--cflags --libs', uselib_store='EGL', mandatory=True)
	cnf.check_cfg(package='ftgl', args='--cflags --libs', uselib_store='EGL', mandatory=True)

	cnf.write_config_header('config.h')

def build(bld):
	bld(source='protocol/wayland.xml')

	bld(features='cxx cxxprogram',
		includes='./ src/wlplus',
		source='src/main.cpp src/Window.cpp src/Input.cpp src/Egl.cpp',
		cxxflags=['-Wall','-g', '-std=c++11'],
		use=['SH_LIBS', 'EGL'],
		target='app')
