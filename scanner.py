#! /usr/bin/env python3

import argparse
parser = argparse.ArgumentParser()
parser.add_argument("protocol", help="XML protocol description")
parser.add_argument("libpath", help="header files output directory")
args = parser.parse_args()

import xml.etree.ElementTree as etree
tree = etree.parse(args.protocol)
root = tree.getroot()

def get_object_name(interface):
	interface = interface.lstrip("wl_")
	interface = interface.split("_")
	name = ""
	for word in interface:
		name += word.capitalize()
	return name

types = {	
"int" : "int32_t ",
"fd" : "int32_t ",
"new_id" : "",
"uint" : "uint32_t ",
"fixed" : "wl_fixed_t ",
"string" : "const char *",
"object" : "",
"array" : "struct wl_array *"
}

CLASS = '''
class %(name)s : public Proxy
{
public:
	struct %(interface)s *cobj;
	%(name)s(struct wl_proxy *proxy)
			: Proxy(proxy)
			, cobj((struct %(interface)s *)proxy) {
		interface_ = &%(interface)s_interface;
	}
%(body)s
};
'''

GUARDS = '''
#ifndef __%(interface)s_H_INCLUDED__
#define __%(interface)s_H_INCLUDED__

#include "Proxy.hpp"
%(class)s
#endif
'''

def format_request_return(request):
	ret_type = "void "
	for arg in request.findall('arg'):
		if arg.get("type") == "new_id":
			if arg.get("interface"):
				ret_type = get_object_name(arg.get("interface"))+ " *"

			else:
				ret_type = "struct wl_proxy *"
	return ret_type

def format_request_args(request):
	first = True
	arguments = ""
	for arg in request.findall('arg'):
		if arg.get("type") == "new_id":
			if not arg.get("interface"):
				arguments += ", const struct wl_interface *interface, uint32_t version"
			continue

		if first:
			first = False
		else:
			arguments += ", "

		if arg.get("type") == "object":
			arguments += get_object_name(arg.get("interface"))+ " *"
		else:
			arguments += types[arg.get("type")] 
		arguments += arg.get("name")
	return arguments

def format_request_body(request):
	body = "marshal(" + request.get('name').upper()
	for arg in request.findall('arg'):
		if arg.get("type") == "new_id":
			body = "return "
			if arg.get("interface"):
				body += "new " + get_object_name(arg.get("interface")) + "("
			body += "marshal_constructor(" + request.get('name').upper()
			if arg.get("interface"):
				body += ", &" + arg.get("interface") + "_interface, NULL"
			else:
				body += ", interface, name, interface->name, version"
		else:
			body += ", " + arg.get("name")
			if arg.get("type") == "object":
				body += "? " + arg.get("name") + "->cobj" + ": NULL"
	if "return new" in body:
		body += ")"
	body += ");"
	return body

def get_request(interface, request):
	name = request.get("name")
	function = ""
	arguments = ""

	arguments = format_request_args(request)
	return_type = format_request_return(request)
	body = format_request_body(request)

	if (request.get("type") == "destructor"):
		function = "\t~" + get_object_name(interface.get('name')) + "() {\n"
	else:
		function = "\t" + return_type + name + "(" + arguments + ") {\n"
	function += "\t\t" + body + "\n"
	function += "\t}\n"
	return function

def get_enum(enum):
	snippet = "\tenum " + enum.get("name") + " {\n\t\t"
	first = True
	for entry in enum.findall('entry'):
		if first:
			first = False
		else:
			snippet += ",\n\t\t"
		snippet += enum.get("name").upper() + "_"
		snippet += entry.get("name").upper() + " = " + entry.get("value")
	snippet += "\n\t};\n"
	return snippet

def get_requests_enum(interface):
	body = "private:\n"
	body += "\tenum requests {\n\t\t"
	first = True
	for request in interface.findall('request'):
		if first:
			first = False
		else:
			body += ",\n\t\t"
		body += request.get("name").upper()
	body += "\n\t};\n"
	return body

def get_events(interface):
	body = "\tstruct listener {\n"
	for event in interface.findall('event'):
		arguments = ""
		for arg in event.findall('arg'):
			arguments += ",\n\t\t\t\t\t"
			if arg.get("type") == "new_id" or arg.get("type") == "object":
				arguments += "struct " + arg.get("interface") + " *"
			else:
				arguments += types[arg.get("type")]
			arguments += arg.get("name")
		body += "\t\tvoid (*" + event.get("name") + ")(void *data,\n\t\t\t\t\tstruct "
		body += interface.get("name") + " *" + interface.get("name") + arguments + ");\n"
	body += "\t};\n"
	return body

for interface in root.findall('interface'):
	name = get_object_name(interface.get('name'))

	if name == "Display":
		continue

	body = ""
	for request in interface.findall('request'):
		body += get_request(interface, request)

	for enum in interface.findall('enum'):
		body += get_enum(enum)

	if interface.find('event'):
		body += get_events(interface)

	if interface.find('request'):
		body += get_requests_enum(interface)

	header = open(args.libpath + "/" + name + ".hpp", 'w+')
	header.write(GUARDS %
				{
				"interface": interface.get('name').upper(),
				"class": CLASS %
					{
					"name": name,
					"interface": interface.get('name'),
					"body": body
					}
				})
