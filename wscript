top = '.'
out = 'build'

def options(opt):
	opt.load('compiler_cxx')

def configure(cnf):
	cnf.load('compiler_cxx')
	cnf.check(features='cxx cxxprogram cxxshlib', cflags=['-Wall','-g', '-std=c++11'], defines=['var=foo'])
	cnf.check_cfg(package='wayland-client', args='--cflags --libs', uselib_store='SH_LIBS', mandatory=True)

	cnf.write_config_header('src/config.h')

def build(bld):
	bld(features='cxx cxxprogram', 
		source='src/main.cpp src/Window.cpp',
		cxxflags=['-Wall','-g', '-std=c++11', '-I../src/wlplus'],
		use=['SH_LIBS'],
		target='wl_term')
