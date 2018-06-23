from jinja2 import Environment, FileSystemLoader
import xml.etree.ElementTree as etree
import getopt
import sys

# Path data
template_prefix = 'templates'
config_file = sys.argv[1]
output_prefix = sys.argv[2]

# Load Jinja 2
file_loader = FileSystemLoader('.')
env = Environment(loader=file_loader,trim_blocks=True)

# Parse XML
tree= etree.parse(config_file)
m_root = tree.getroot()
m_opname = m_root.tag
m_prefix = output_prefix

op_dynamic_c = env.get_template('templates/base.c')
output = op_dynamic_c.render(prefix=m_prefix,opname=m_opname,root=m_root)
filename = '%s.c' % output_prefix
f = open(filename, 'w')
f.write(output)
op_dynamic = env.get_template('templates/base.h')
output = op_dynamic.render(prefix=m_prefix,opname=m_opname,root=m_root)
filename = '%s.h' % output_prefix
f = open(filename, 'w')
f.write(output)

