#! /bin/python

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
"fd" : "uint32_t ",
"new_id" : "",
"uint" : "uint32_t ",
"fixed" : "wl_fixed_t ",
"string" : "const char *",
"object" : "",
"array" : "struct wl_array *"
}

def get_class(interface, body):
	return "class " + interface + " : public Proxy\n{\n" + body + "};\n\n"

def get_guards(interface, body):
	guards = "#ifndef __"+interface.upper()+"_H_INCLUDED__\n"
	guards += "#define __"+interface.upper()+"_H_INCLUDED__\n\n"
	guards += "#include \"Proxy.h\"\n\n"
	guards += body
	guards += "#endif\n"
	return guards

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
	body = "marshal(" + interface.get('name').upper() + "_" + request.get('name').upper()
	for arg in request.findall('arg'):
		if arg.get("type") == "new_id":
			if arg.get("interface"):
				body = "return new " + get_object_name(arg.get("interface")) + \
									"(marshal_constructor(" + interface.get('name').upper() + "_" + request.get('name').upper() + ", "\
									"&" + arg.get("interface") + "_interface, NULL"
			else:
				body = "return marshal_constructor(" + interface.get('name').upper() + "_" + request.get('name').upper() + ", interface, name, interface->name, version"
		else:
			body += ", " + arg.get("name")
	if "return new" in body:
		body += ")"
	body += ");"
	return body

def get_request_v2(interface, request):
	name = request.get("name")
	function = ""
	arguments = ""

	if request.get("type") == "destructor":
		return function
	
	arguments = format_request_args(request)
	return_type = format_request_return(request)
	body = format_request_body(request)

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
			snippet += ", \n\t\t"
		snippet += interface.get("name").upper() + "_"
		snippet += enum.get("name").upper() + "_"
		snippet += entry.get("name").upper() + " = " + entry.get("value")
	snippet += "\n\t};\n"
	return snippet

for interface in root.findall('interface'):
	name = get_object_name(interface.get('name'))

	if name == "Display":
		continue

	body = "public:\n\tusing Proxy::Proxy;\n\n"

	for enum in interface.findall('enum'):
		body += get_enum(enum)

	for request in interface.findall('request'):
		body += get_request_v2(interface, request)

	header = open(args.libpath + "/" + name + ".h", 'w+')
	header.write(
				get_guards(name, 
				get_class(name, 
				body)))
