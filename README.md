# wlplus

### [Wayland](http://wayland.freedesktop.org/) C++ Bindings

Author: Ricardo Vieira <ricardo.vieira@tecnico.ulisboa.pt>

## Dependencies

 - waf (build)
 - wayland 1.5.0
 - python3
 - mesa-libgl

## Compiling

	$ waf configure build
	$ ./build/app


## Todo

 - find a new way to handle listeners and emit them with scanner
 - decide were to put externs wl_*_interface
 - rewritte scanner to be more readable
 - implement exceptions
